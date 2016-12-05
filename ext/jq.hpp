#ifndef __JQ_HPP__
#define __JQ_HPP__

#include <string>
#include <stdexcept>

#include <nan.h>

#include "jq_wrapper.hpp"

namespace node_jq_ext {
  using v8::Local;
  using v8::Object;
  using v8::Value;
  using v8::Function;
  using v8::FunctionCallbackInfo;
  using v8::Persistent;

  class Jq : public Nan::ObjectWrap {
    public:
      std::string getCode();

      static void Init(Local<Object> exports);

    private:
      jq_state* jq;
      struct jv_parser* parser;
      std::string code;

      explicit Jq(const std::string&);
      ~Jq();

      static void New(const Nan::FunctionCallbackInfo<Value>&);
      static void Parse(const Nan::FunctionCallbackInfo<Value>&);
      static Nan::Persistent<Function> constructor;
  };
}

#endif // __JQ_HPP__

