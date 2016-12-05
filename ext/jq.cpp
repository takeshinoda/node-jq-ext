
#include "jq.hpp"

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
  using v8::Exception;

  Nan::Persistent<Function> Jq::constructor;

  Jq::Jq(const std::string& code) : code(code){
  }

  Jq::~Jq() {
  }

  void Jq::Init(Local<Object> exports) {
    Nan::HandleScope scope;

    // Prepare constructor template
    Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("Jq").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // Prototype
    Nan::SetPrototypeMethod(tpl, "parse", Parse);

    constructor.Reset(tpl->GetFunction());
    exports->Set(Nan::New("Jq").ToLocalChecked(), tpl->GetFunction());
  }

  void Jq::New(const Nan::FunctionCallbackInfo<Value>& info) {
    if (info.IsConstructCall()) {
      // Invoked as constructor: `new MyObject(...)`
      Local<String> code = info[0]->IsUndefined() ? Nan::New(".").ToLocalChecked() : info[0]->ToString();

      Local<Object> _this = info.This();
      _this->Set(Nan::New("code").ToLocalChecked(), code);
      info.GetReturnValue().Set(_this);
    } else {
      // Invoked as plain function `MyObject(...)`, turn into construct call.
      const int argc = 1;
      Local<Value> argv[argc] = { info[0] };
      Local<Function> cons = Nan::New<Function>(constructor);
      info.GetReturnValue().Set(cons->NewInstance(argc, argv));
    }
  }

  void Jq::Parse(const Nan::FunctionCallbackInfo<Value>& info) {
    String::Utf8Value input(info[0]->ToString());
    String::Utf8Value code(info.This()->Get(Nan::New("code").ToLocalChecked()));

    std::string _input(*input);
    std::string _code(*code);
    std::string _result;

    JqWrapper _jq_wrapper(_code);
    try {
      _result = _jq_wrapper.execute(_input);
    }
    catch (std::logic_error& _e) {
      Nan::ThrowError(_e.what());
      return;
    }
    info.GetReturnValue().Set(Nan::New(_result.c_str()).ToLocalChecked());
  }
}

