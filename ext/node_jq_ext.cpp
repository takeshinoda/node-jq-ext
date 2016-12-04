
#include "node_jq_ext.hpp"

namespace node_jq_ext {
  using v8::FunctionCallbackInfo;
  using v8::Isolate;
  using v8::Local;
  using v8::Object;
  using v8::Value;
  using v8::String;

  void testFunction(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "hoge"));
  }

  void initAll(Local<Object> exports) {
    JqWrapper::Init(exports);
    NODE_SET_METHOD(exports, "test", testFunction);
  }

  NODE_MODULE(node_jq_ext, initAll)
}

