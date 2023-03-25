/**
 * \file
 *
 * \brief Файл с определениями функций класса INTEGER, соответствующего ГОСТ Р ИСО 10303-11-2009, п.8.1.3
 *
 * Здесь определены функции, реализующие функции-члены класса INTEGER, соответствующему целочисленному
 * типу данных языка EXPRESS.
 */

#include "stdafx.h"
#include "express.h"

namespace express {

  /**
   * \file
   * Для типа INTEGER определены следующие члены-методы (функции):<BR><BR>
   */

  /**
   * \file
   * Конструкторы (неопределённого значения, копирующий и конструктор из значения)
   * и операторы присваивания:
   */

  /**
   * \file
   * * \copybrief express::INTEGER::INTEGER()
   */
  INTEGER::INTEGER() : REAL() {
    append_to_parent_type_list();
    _i = 0;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::INTEGER(const express::INTEGER&)
   */
  INTEGER::INTEGER(const INTEGER& src) : REAL() {
    append_to_parent_type_list();
    if (!src.determinated) {
      determinated = false;
      _i = 0;
    } else {
      determinated = true;
      _i = src.get_integer_value();
    }

#ifdef TRACE_INTEGER
    printf("%s\n", __MYFUNCNAME__);
#endif

  }

  /**
   * \file
   * * \copybrief express::INTEGER::INTEGER(express::integer_type)
   */
  INTEGER::INTEGER(integer_type src) : REAL() {
    append_to_parent_type_list();
    determinated = true;
    _i = src;

#ifdef TRACE_INTEGER
    printf("%s\n", __MYFUNCNAME__);
#endif

  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator=(const express::INTEGER&)
   */
  INTEGER& INTEGER::operator=(const INTEGER& rhs) {
    if (this != std::addressof(rhs)) {
      if (rhs.determinated) {
        determinated = true;
        _i = rhs.get_integer_value();
      }
      else {
        determinated = false;
        _i = 0;
      }
    }

#ifdef TRACE_INTEGER
    printf("%s: %s = %s\n", __MYFUNCNAME__, print_value().c_str(), rhs.print_value().c_str());
#endif

    return *this;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator=(express::integer_type)
   */
  INTEGER& INTEGER::operator=(integer_type rhs) {
    determinated = true;
    _i = rhs;

#ifdef TRACE_INTEGER
    printf("%s: %s = %lli\n", __MYFUNCNAME__, print_value().c_str(), rhs);
#endif

    return *this;
  }

  /**
   * \file
   * Получение значения и свойств типа, вывод значения типа в виде строки:
   */

  /**
   * \file
   * * \copybrief express::INTEGER::get_number_value() const
   */
  number_type INTEGER::get_number_value() const {
    if (!determinated) {
      throw exception{__MYFUNCNAME__, "can not get indeterminate (?) value"};
    }
    return integer_to_real(_i);
  }

  /**
   * \file
   * * \copybrief express::INTEGER::get_integer_value() const
   */
  integer_type INTEGER::get_integer_value() const {
    if (!determinated) {
      throw exception{__MYFUNCNAME__, "can not get indeterminate (?) value"};
    }
    return _i;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::get_number_precision() const
   */
  unsigned INTEGER::get_number_precision() const {
    return std::numeric_limits<integer_type>::digits10 - 1;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::objtype() const
   */
  constexpr GENERIC::OBJTYPE INTEGER::objtype() const {
    return OBJTYPE::OBJ_SIMPLE | OBJTYPE::OBJ_INTEGER;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::print_value() const
   */
  std::string INTEGER::print_value() const {

    if (!determinated) {
#if defined(TRACE_NUMBER) || defined(TRACE_REAL) || defined(TRACE_INTEGER) || \
    defined(TRACE_LOGICAL) || defined(TRACE_BOOLEAN) || defined(TRACE_STRING) || defined(TRACE_BINARY) || \
    defined(TRACE_AGGREGATE) || defined(TRACE_ARRAY) || defined(TRACE_LIST)  || defined(TRACE_SET) 
      return std::string("INDETERMINATED");
#else
      throw exception{__MYFUNCNAME__, "value may not be indeterminate (?)"};
#endif
    }

    char Buff[50];

#if defined(_MSC_VER)
    sprintf_s(Buff, sizeof(Buff), "%lli", _i);
#elif defined(__GNUC__) || defined(__DOXYGEN__)
    sprintf(Buff, "%lli", _i);
#elif
#error Unknown C++ compiler
#endif
    return std::string(Buff);
  }

  /**
   * \file
   * Арифметические операторы:
   */

  /**
   * \file
   * * \copybrief express::INTEGER::operator+() const
   */
  INTEGER INTEGER::operator+() const {
    INTEGER out;
    if (determinated) {
      out = get_integer_value();
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator-() const
   */
  INTEGER INTEGER::operator-() const {
    INTEGER out;
    if (determinated) {
      out = -get_integer_value();
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator+(const express::INTEGER&) const
   */
  INTEGER INTEGER::operator+(const INTEGER& rhs) const {
    INTEGER out;
    if (determinated && rhs.is_determinated()) {
      out = get_integer_value() + rhs.get_integer_value();
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator+(express::integer_type) const
   */
  INTEGER INTEGER::operator+(integer_type rhs) const {
    INTEGER out;
    if (determinated) {
      out = get_integer_value() + rhs;
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator+(int) const
   */
  INTEGER INTEGER::operator+(int rhs) const {
    INTEGER out;
    if (determinated) {
      out = get_integer_value() + rhs;
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator+(express::integer_type,const express::INTEGER&)
   */
  INTEGER operator+(integer_type lhs, const INTEGER& rhs) {
    INTEGER out;
    if (rhs.is_determinated()) {
      out = lhs + rhs.get_integer_value();
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator+(int,const express::INTEGER&)
   */
  INTEGER operator+(int lhs, const INTEGER& rhs) {
    INTEGER out;
    if (rhs.is_determinated()) {
      out = lhs + rhs.get_integer_value();
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator+(express::real_type,const express::INTEGER&)
   */
  REAL operator+(real_type lhs, const INTEGER& rhs) {
    REAL out;
    if (rhs.is_determinated()) {
      out = lhs + static_cast<real_type>(rhs.get_integer_value());
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator-(const express::INTEGER&) const
   */
  INTEGER INTEGER::operator-(const INTEGER& rhs) const {
    INTEGER out;
    if (determinated && rhs.is_determinated()) {
      out = get_integer_value() - rhs.get_integer_value();
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator-(express::integer_type) const
   */
  INTEGER INTEGER::operator-(integer_type rhs) const {
    INTEGER out;
    if (determinated) {
      out = get_integer_value() - rhs;
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator-(int) const
   */
  INTEGER INTEGER::operator-(int rhs) const {
    INTEGER out;
    if (determinated) {
      out = get_integer_value() - rhs;
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator-(express::integer_type,const express::INTEGER&)
   */
  INTEGER operator-(integer_type lhs, const INTEGER& rhs) {
    INTEGER out;
    if (rhs.determinated) {
      out = lhs - rhs.get_integer_value();
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator-(int,const express::INTEGER&)
   */
  INTEGER operator-(int lhs, const INTEGER& rhs) {
    INTEGER out;
    if (rhs.is_determinated()) {
      out = lhs - rhs.get_integer_value();
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator-(express::real_type,const express::INTEGER&)
   */
  REAL operator-(real_type lhs, const INTEGER& rhs) {
    REAL out;
    if (rhs.is_determinated()) {
      out = lhs - static_cast<real_type>(rhs.get_integer_value());
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator*(const express::INTEGER&) const
   */
  INTEGER INTEGER::operator*(const INTEGER& rhs) const {
    INTEGER out;
    if (determinated && rhs.is_determinated()) {
      out = _i * rhs.get_integer_value();
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator*(express::integer_type) const
   */
  INTEGER INTEGER::operator*(integer_type rhs) const {
    INTEGER out;
    if (determinated) {
      out = _i * rhs;
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator*(int) const
   */
  INTEGER INTEGER::operator*(int rhs) const {
    INTEGER out;
    if (determinated) {
      out = _i * rhs;
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator*(express::integer_type,const express::INTEGER&)
   */
  INTEGER operator*(integer_type lhs, const INTEGER& rhs) {
    INTEGER out;
    if (rhs.is_determinated()) {
      out = lhs * rhs.get_integer_value();
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator*(int,const express::INTEGER&)
   */
  INTEGER operator*(int lhs, const INTEGER& rhs) {
    INTEGER out;
    if (rhs.is_determinated()) {
      out = lhs * rhs.get_integer_value();
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator*(express::real_type,const express::INTEGER&)
   */
  REAL operator*(real_type lhs, const INTEGER& rhs) {
    REAL out;
    if (rhs.is_determinated()) {
      out = lhs * static_cast<real_type>(rhs.get_integer_value());
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator/(const express::INTEGER&) const
   */
  REAL INTEGER::operator/(const INTEGER& rhs) const {
    REAL out;
    if (determinated && rhs.is_determinated()) {
      out = integer_to_real(_i) / rhs.get_number_value();
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator/(express::integer_type) cosnt
   */
  REAL INTEGER::operator/(integer_type rhs) const {
    REAL out;
    if (determinated) {
      out = integer_to_real(_i) / integer_to_real(rhs);
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator/(int) cosnt
   */
  REAL INTEGER::operator/(int rhs) const {
    REAL out;
    if (determinated) {
      out = integer_to_real(_i) / integer_to_real(rhs);
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator/(express::integer_type,const express::INTEGER&)
   */
  REAL operator/(integer_type lhs, const INTEGER& rhs) {
    REAL out;
    if (rhs.is_determinated()) {
      out = integer_to_real(lhs) / rhs.get_number_value();
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator/(int,const express::INTEGER&)
   */
  REAL operator/(int lhs, const INTEGER& rhs) {
    REAL out;
    if (rhs.is_determinated()) {
      out = integer_to_real(lhs) / rhs.get_number_value();
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator/(express::real_type,const express::INTEGER&)
   */
  REAL operator/(real_type lhs, const INTEGER& rhs) {
    REAL out;
    if (rhs.is_determinated()) {
      out = lhs / rhs.get_number_value();
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator<<(const express::INTEGER&) const
   */
  INTEGER INTEGER::operator<<(const INTEGER& rhs) const {
    INTEGER out;
    if (is_determinated() && rhs.is_determinated()) {
      out = real_to_integer(pow(get_integer_value(), rhs.get_integer_value()));
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator<<(express::integer_type) const
   */
  INTEGER INTEGER::operator<<(integer_type rhs) const {
    INTEGER out;
    if (is_determinated()) {
      out = real_to_integer(pow(get_integer_value(), rhs));
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator<<(int) const
   */
  INTEGER INTEGER::operator<<(int rhs) const {
    INTEGER out;
    if (is_determinated()) {
      out = real_to_integer(pow(get_integer_value(), rhs));
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator<<(express::real_type) const
   */
  REAL INTEGER::operator<<(real_type rhs) const {
    REAL out;
    if (is_determinated()) {
      out = pow(get_integer_value(), rhs);
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator<<(express::integer_type,const express::INTEGER&)
   */
  INTEGER operator<<(integer_type lhs, const INTEGER& rhs) {
    INTEGER out;
    if (rhs.is_determinated()) {
      out = real_to_integer(pow(lhs, rhs.get_integer_value()));
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator<<(int,const express::INTEGER&)
   */
  INTEGER operator<<(int lhs, const INTEGER& rhs) {
    INTEGER out;
    if (rhs.is_determinated()) {
      out = real_to_integer(pow(lhs, rhs.get_integer_value()));
    }
    return out;
  }

  /**
   * \file
   * * \copybrief express::INTEGER::operator<<(express::real_type,const express::INTEGER&)
   */
  REAL operator<<(real_type lhs, const INTEGER& rhs) {
    REAL out;
    if (rhs.is_determinated()) {
      out = pow(lhs, rhs.get_integer_value());
    }
    return out;
  }

  /**
   * \file
   * Проверки равенства экземпляров ':=:' и отношений значений:
   */

  /**
   * \file
   * * \copybrief express::INTEGER::compare(express::integer_type,express::integer_type)
   */
  int INTEGER::compare(integer_type lhs, integer_type rhs) {
    if (lhs > rhs) return 1;
    else if (lhs < rhs) return -1;
    else return 0;
  }
}