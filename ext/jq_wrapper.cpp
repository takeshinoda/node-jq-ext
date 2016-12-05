#include "jq_wrapper.hpp"

namespace node_jq_ext {

  static void jq_err_cb(void *data, jv msg) {
    msg = jq_format_error(msg);
    JqWrapper* jw = (JqWrapper*)data;
    std::string errmsg(jv_string_value(msg));
    jw->addCompileErrMsg(errmsg);
    jv_free(msg);
  }

  JqWrapper::JqWrapper(const std::string& code): jq(NULL), code(code) {}
  JqWrapper::~JqWrapper() {
    if (this->jq) jq_teardown(&this->jq);
  }

  std::string JqWrapper::execute(const std::string& input) throw(std::logic_error) {
    this->initialize();
    this->compile(input);

    std::string buf;
    this->parse(buf, input);

    return buf;
  }

  void JqWrapper::initialize() throw(std::logic_error) {
    std::string err;
    this->compile_err_msg = err;
    if (!this->jq) {
      this->jq = jq_init();

      if (!this->jq)
        throw std::logic_error("Failed jq_init()");

      jq_set_error_cb(this->jq, jq_err_cb, (void*)this);
    }
  }

  void JqWrapper::addCompileErrMsg(const std::string& msg) {
    this->compile_err_msg.append(msg);
  }

  void JqWrapper::compile(const std::string& input) throw(std::logic_error) {
    int compile = jq_compile(this->jq, this->code.c_str());
    if (compile == 0) {
      if (this->compile_err_msg.length() > 1)
        throw std::logic_error(this->compile_err_msg);
      else
        throw std::logic_error("Failed jq_compile()");
    }
  }

  void JqWrapper::jq_process(std::string& buf, ::jv value) {
    jq_start(this->jq, value, 0);
    ::jv jq_ret;

    while (::jv_is_valid(jq_ret = jq_next(jq))) {
      ::jv dumped = jv_dump_string(jq_ret, 0);
      std::string str(::jv_string_value(dumped));
      buf.append(str);
    }

    jv_free(jq_ret);
  }

  void JqWrapper::parse(std::string& buf, const std::string& input) throw(std::logic_error) {
    this->jv = jv_parser_new(0);
    if (!this->jv) throw std::logic_error("Failed jv_parser_new()");

    jv_parser_set_buf(this->jv, input.c_str(), input.size(), 0);

    ::jv value;
    while (::jv_is_valid(value = jv_parser_next(this->jv))) {
      jq_process(buf, value);
    }

    if (::jv_invalid_has_msg(::jv_copy(value))) {
      ::jv msg = jv_invalid_get_msg(value);
      std::string errmsg(::jv_string_value(msg));
      jv_free(msg);
      throw InvalidError(errmsg);
    }
    else {
      jv_free(value);
    }
  }
}

