#ifndef __JQ_WRAPPER_HPP__
#define __JQ_WRAPPER_HPP__

#include <string>
#include <stdexcept>

#include <node.h>
#include <node_object_wrap.h>

#include <jq.h>


namespace node_jq_ext {
  using v8::Local;
  using v8::Object;
  using v8::Value;
  using v8::Function;
  using v8::FunctionCallbackInfo;
  using v8::Persistent;

  class JqWrapper : public node::ObjectWrap {
    public:
      std::string getCode();

      static void Init(Local<Object> exports);

    private:
      jq_state* jq;
      std::string code;

      explicit JqWrapper(const std::string&);
      ~JqWrapper();

      static void New(const FunctionCallbackInfo<Value>&);
      static void Parse(const FunctionCallbackInfo<Value>&);
      static Persistent<Function> constructor;
  };
}

#endif // __JQ_WRAPPER_HPP__

