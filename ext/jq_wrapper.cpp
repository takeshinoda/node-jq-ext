
#include "jq_wrapper.hpp"

namespace node_jq_ext {
  using v8::Context;
  using v8::Function;
  using v8::FunctionCallbackInfo;
  using v8::FunctionTemplate;
  using v8::Isolate;
  using v8::Local;
  using v8::Number;
  using v8::Object;
  using v8::Persistent;
  using v8::String;
  using v8::Value;

  Persistent<Function> JqWrapper::constructor;

  JqWrapper::JqWrapper(const std::string& code) : code(code){
  }

  JqWrapper::~JqWrapper() {
  }

  void JqWrapper::Init(Local<Object> exports) {
    Isolate* isolate = exports->GetIsolate();

    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "JqWrapper"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // Prototype
    NODE_SET_PROTOTYPE_METHOD(tpl, "parse", Parse);

    constructor.Reset(isolate, tpl->GetFunction());
    exports->Set(String::NewFromUtf8(isolate, "JqWrapper"), tpl->GetFunction());
  }

  void JqWrapper::New(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.IsConstructCall()) {
      // Invoked as constructor: `new MyObject(...)`
      Local<String> code = args[0]->IsUndefined() ? String::NewFromUtf8(isolate, ".") : args[0]->ToString();
      v8::String::Utf8Value code_(code);
      JqWrapper* jqw = new JqWrapper(*code_);
      jqw->Wrap(args.This());
      args.GetReturnValue().Set(args.This());
    } else {
      // Invoked as plain function `MyObject(...)`, turn into construct call.
      const int argc = 1;
      Local<Value> argv[argc] = { args[0] };
      Local<Context> context = isolate->GetCurrentContext();
      Local<Function> cons = Local<Function>::New(isolate, constructor);
      Local<Object> result = cons->NewInstance(context, argc, argv).ToLocalChecked();
      args.GetReturnValue().Set(result);
    }
  }

  void JqWrapper::Parse(const FunctionCallbackInfo<Value>& args) {
    Local<String> input = args[0]->ToString();
    args.GetReturnValue().Set(input);
  }
}

