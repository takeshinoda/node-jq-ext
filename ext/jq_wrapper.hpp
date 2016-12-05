#ifndef __JQ_WRAPPER_HPP__
#define __JQ_WRAPPER_HPP__

#include <string>
#include <stdexcept>

extern "C" {
  #include <jq.h>
}

namespace node_jq_ext {

  class InvalidError : public std::logic_error {
    public:
      InvalidError(const std::string& message) : logic_error(message) {}
  };

  class JqWrapper {
    public:
      JqWrapper(const std::string&);
      ~JqWrapper();

      void addCompileErrMsg(const std::string&);
      std::string execute(const std::string&) throw(std::logic_error);

    private:
      jq_state* jq;
      jv_parser* jv;
      std::string code;
      std::string compile_err_msg;

      void jq_process(std::string&, ::jv);
      void parse(std::string&, const std::string&) throw(std::logic_error);
      void compile(const std::string&) throw(std::logic_error);
      void initialize() throw(std::logic_error);
  };
}

#endif // __JQ_WRAPPER_HPP__

