/**
 * \file
 *
 * \brief Файл с определениями функций, реализующих обработку ошибок
 */

#include "stdafx.h"
#include "express.h"

namespace express {

  std::string convert_name(const char* name) {

//#if defined(__GNUC__) || defined(__DOXYGEN__)
//    /* Для GCC выполнить преобразование имени класса Demangle */
//    int status;
//    std::string new_name(abi::__cxa_demangle(name, 0, 0, &status));
//#else
    std::string new_name(name);
//#endif
    std::string toErase1("express::");
    for (;;) {
      size_t pos = new_name.find(toErase1);
      if (pos == std::string::npos) break;
      new_name.erase(pos, toErase1.length());
    }
    std::string toErase2("class ");
    for (;;) {
      size_t pos = new_name.find(toErase2);
      if (pos == std::string::npos) break;
      new_name.erase(pos, toErase2.length());
    }
    std::string toErase3("__cdecl");
    for (;;) {
      size_t pos = new_name.find(toErase3);
      if (pos == std::string::npos) break;
      new_name.erase(pos, toErase3.length());
    }
    return new_name;
  }

  exception::exception(char const* fname, char const* fmt, ...) noexcept : std::runtime_error("Express exception") {
    va_list ap;
    va_start(ap, fmt);
    errmsg =  vformat(fmt, ap);
    va_end(ap);
    funcname = convert_name(fname);
  }

  std::string exception::vformat(const char *format, va_list args) const {
    va_list copy;
    va_copy(copy, args);
    auto len = std::vsnprintf(nullptr, 0, format, copy);
    va_end(copy);

    if (len >= 0) {
        std::string s(static_cast<unsigned>(len + 1), '\0');
        std::vsnprintf(&s[0], s.size(), format, args);
        s.resize(static_cast<size_t>(len));
        return s;
    }

    const auto err = errno;
    const auto ec = std::error_code(err, std::generic_category());
    throw std::system_error(ec);
  }


  const char* exception::what() const throw() {
    return errmsg.c_str();
  }

  const char* exception::where() const throw() {
    return funcname.c_str();
  }
}