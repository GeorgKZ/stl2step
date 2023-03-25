/**
 * \file
 * \brief Файл с определениями функций класса NUMBER, соответствующего ГОСТ Р ИСО 10303-11-2009, п.8.1.1
 *
 * Здесь определены функции, реализующие функции-члены класса NUMBER, соответствующему числовому типу
 * данных языка EXPRESS.
 */

#include "stdafx.h"
#include "express.h"

namespace express {

  integer_type real_to_integer(real_type rhs) {
    if (rhs >= static_cast<real_type>(std::numeric_limits<integer_type>::max())) {
      throw exception{__MYFUNCNAME__, "real_type source is bigger than maximal possible integer_type" };
    }
    if (rhs <= static_cast<real_type>(std::numeric_limits<integer_type>::lowest())) {
      throw exception{__MYFUNCNAME__, "real_type source is smaller than minimal possible (negative) integer_type" };
    }
#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4244)
    return static_cast<integer_type>(rhs);
#pragma warning( pop ) 
#elif defined(__GNUC__) || defined(__DOXYGEN__)
//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-W...."
    return static_cast<integer_type>(rhs);
//#pragma GCC diagnostic pop
#elif
# error Unknown C++ compiler
#endif
  }

  int real_to_int(real_type rhs) {
    if (rhs >= std::numeric_limits<int>::max()) {
      throw exception{__MYFUNCNAME__, "real_type source is bigger than maximal possible int" };
    }
    if (rhs <= std::numeric_limits<int>::lowest()) {
      throw exception{__MYFUNCNAME__, "real_type source is smaller than minimal possible (negative) int" };
    }
#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4244)
    return static_cast<int>(rhs);
#pragma warning( pop ) 
#elif defined(__GNUC__) || defined(__DOXYGEN__)
//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-W...."
    return static_cast<int>(rhs);
//#pragma GCC diagnostic pop
#elif
# error Unknown C++ compiler
#endif
  }

  real_type integer_to_real(integer_type rhs) {
#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4244)
    return static_cast<real_type>(rhs);
#pragma warning( pop ) 
#elif defined(__GNUC__) || defined(__DOXYGEN__)
//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wunused-parameter"
    return static_cast<real_type>(rhs);
//#pragma GCC diagnostic pop
#elif
# error Unknown C++ compiler
#endif
  }



  /**
   * \file
   * Для типа NUMBER определены следующие члены-методы (функции):<BR><BR>
   */

  /**
   * \file
   * Конструкторы (неопределённого значения, копирующий (из базового и дочерних
   * типов) и конструктор из значения) и оператор присваивания:
   */

  /**
   * \file
   * * \copybrief express::NUMBER::NUMBER()
   */
  NUMBER::NUMBER() : SIMPLE(false) {
    append_to_parent_type_list();
    _n = 0.0;
#ifdef TRACE_NUMBER
    printf("%s\n", __MYFUNCNAME__);
#endif
  }

  /**
   * \file
   * * \copybrief express::NUMBER::NUMBER(const express::NUMBER&)
   */
  NUMBER::NUMBER(const NUMBER& src) : SIMPLE() {

#ifdef TRACE_NUMBER
    printf("%s\n", __MYFUNCNAME__);
#endif

    append_to_parent_type_list();
    if (!src.determinated) {
      determinated = false;
      _n = 0.0;
    }
    else {
      _n = src.get_number_value();
    }
  }

  /**
   * \file
   * * \copybrief express::NUMBER::NUMBER(express::real_type)
   */
  NUMBER::NUMBER(real_type src) {
    append_to_parent_type_list();
    _n = static_cast<number_type>(src);

#ifdef TRACE_NUMBER
    printf("%s\n", __MYFUNCNAME__);
#endif
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator=(const express::NUMBER&)
   */
  NUMBER& NUMBER::operator=(const NUMBER& rhs) {
    if (this != std::addressof(rhs)) {
      if (rhs.determinated) {
        determinated = true;
        _n = rhs.get_number_value();
      }
      else {
        determinated = false;
        _n = 0;
      }
    }

#ifdef TRACE_NUMBER
    printf("%s: %s = %s\n", __MYFUNCNAME__, print_value().c_str(), rhs.print_value().c_str());
#endif

    return *this;
  }

  /**
   * \file
   * Получение значения и свойств типа, вывод значения типа в виде строки:
   */

  /**
   * \file
   * * \copybrief express::NUMBER::get_number_value() const
   */
  number_type NUMBER::get_number_value() const {
    if (!determinated) {
      throw exception{__MYFUNCNAME__, "can not get indeterminate (?) value"};
    }
    return _n;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::get_integer_value() const
   */
  integer_type NUMBER::get_integer_value() const {
    throw exception{__MYFUNCNAME__, "pure virtual function called by class '%s'", get_type_name().c_str()};
  }

  /**
   * \file
   * * \copybrief express::NUMBER::get_number_precision() const
   */
  unsigned NUMBER::get_number_precision() const {
    return std::numeric_limits<number_type>::digits10 - 1;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::objtype() const
   */
  GENERIC::OBJTYPE NUMBER::objtype() const {
    return OBJTYPE::OBJ_SIMPLE | OBJTYPE::OBJ_NUMBER;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::check_compatibility(const express::GENERIC&) const
   */
  GENERIC::COMPAT NUMBER::check_compatibility(const GENERIC& rhs) const
  {
    if ((is_number()) && (rhs.is_number())) {
      return COMPAT::COMPAT_SAME;
    }
    if ((is_number()) && (rhs.is_real())) {
      return COMPAT::COMPAT_BACKWARD;
    }
    if ((is_number()) && (rhs.is_integer())) {
      return COMPAT::COMPAT_BACKWARD;
    }

    if ((is_real()) && (rhs.is_number())) {
      return COMPAT::COMPAT_FORWARD;
    }
    if ((is_real()) && (rhs.is_real())) {
      return COMPAT::COMPAT_SAME;
    }
    if ((is_real()) && (rhs.is_integer())) {
      return COMPAT::COMPAT_BACKWARD;
    }

    if ((is_integer()) && (rhs.is_number())) {
      return COMPAT::COMPAT_FORWARD;
    }
    if ((is_integer()) && (rhs.is_real())) {
      return COMPAT::COMPAT_FORWARD;
    }
    if ((is_integer()) && (rhs.is_integer())) {
      return COMPAT::COMPAT_SAME;
    }
    return COMPAT::COMPAT_NONE;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::print_value() const
   */
  std::string NUMBER::print_value() const {
#if defined(TRACE_NUMBER) || defined(TRACE_REAL) || defined(TRACE_INTEGER) || \
    defined(TRACE_LOGICAL) || defined(TRACE_BOOLEAN) || defined(TRACE_STRING) || defined(TRACE_BINARY) || \
    defined(TRACE_AGGREGATE) || defined(TRACE_ARRAY) || defined(TRACE_LIST)  || defined(TRACE_SET) 
    if (!determinated) {
      return std::string("INDETERMINATED");
    }
    real_type x = get_number_value();
    if (abs(x) < std::numeric_limits<real_type>::min()) {
      return std::string("0.0");
    } else {
      int sign = x < 0 ? -1 : 1;
      int exponent = real_to_int(log10(abs(x)));
      real_type mantissa = abs(x) * pow(10.0, static_cast<int>(get_number_precision()) - exponent - 1);
      std::string mant;
      for (int i = 0; i < get_number_precision(); ++i) {
        if (i == get_number_precision() - 1) mant.insert(mant.begin(), '.');

        real_type m_next = mantissa / 10.0;
#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4244)
        mant.insert(mant.begin(), static_cast<int>(std::trunc(mantissa) - std::trunc(m_next) * 10.0) + '0');
#pragma warning( pop ) 
#elif defined(__GNUC__) || defined(__DOXYGEN__)
        mant.insert(mant.begin(), static_cast<int>(std::trunc(mantissa) - std::trunc(m_next) * 10.0) + '0');
#elif
# error Unknown C++ compiler
#endif
        mantissa = m_next;
      }
      char Buff1[50];
      sprintf(Buff1, "%i", exponent);
      char Buff2[50];
      sprintf(Buff2, "<%u>", get_number_precision());
      return std::string(sign > 0 ? "+" : "-") + mant + std::string("E") + std::string(Buff1) + std::string(Buff2);
    }
#else

    if (!determinated) {
      throw exception{__MYFUNCNAME__, "value may not be indeterminate (?)"};
    }

    char Buff[50];

#if defined(_MSC_VER)
    sprintf_s(Buff, sizeof(Buff), "%.7f", get_number_value());
#elif defined(__GNUC__) || defined(__DOXYGEN__)
    sprintf(Buff, "%.7f", get_number_value());
#elif
#error Unknown C++ compiler
#endif

    return std::string(Buff);
#endif /* TRACE */
  }

  /**
   * \file
   * Арифметические операторы:
   */

  /**
   * \file
   * * \copybrief express::NUMBER::operator+() const
   */
  REAL NUMBER::operator+() const {
    REAL out;
    if (determinated) {
      out = _n;
    }

#ifdef TRACE_NUMBER
    printf("%s: %s = +%s\n", __MYFUNCNAME__, out.print_value().c_str(), print_value().c_str());
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator-() const
   */
  REAL NUMBER::operator-() const {
    REAL out;
    if (determinated) {
      out = -_n;
    }

#ifdef TRACE_NUMBER
    printf("%s: %s = -%s\n", __MYFUNCNAME__, out.print_value().c_str(), print_value().c_str());
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator+(const express::NUMBER&) const
   */
  REAL NUMBER::operator+(const NUMBER& rhs) const {
    REAL out;
    if (determinated && rhs.determinated) {
      out = get_number_value() + rhs.get_number_value();
    }

#ifdef TRACE_NUMBER
    printf("%s: %s = %s + %s\n", __MYFUNCNAME__, out.print_value().c_str(), print_value().c_str(), rhs.print_value().c_str());
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator+(express::real_type) const
   */
  REAL NUMBER::operator+(real_type rhs) const {
    REAL out;
    if (determinated) {
      out = get_number_value() + rhs;
    }

#ifdef TRACE_NUMBER
    printf("%s: %s = %s + %f\n", __MYFUNCNAME__, out.print_value().c_str(), print_value().c_str(), rhs);
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator+(const express::REAL&,const express::NUMBER&)
   */
  REAL operator+(const REAL& lhs, const NUMBER& rhs) {
    REAL out;
    if (lhs.determinated && rhs.determinated) {
      out = lhs.get_number_value() + rhs.get_number_value();
    }

#ifdef TRACE_NUMBER
    printf("%s: %s = %s + %s\n", __MYFUNCNAME__, out.print_value().c_str(), lhs.print_value().c_str(), rhs.print_value().c_str());
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator-(const express::NUMBER&) const
   */
  REAL NUMBER::operator-(const NUMBER& rhs) const {
    REAL out;
    if (determinated && rhs.determinated) {
      out = get_number_value() - rhs.get_number_value();
    }

#ifdef TRACE_NUMBER
    printf("%s: %s = %s - %s\n", __MYFUNCNAME__, out.print_value().c_str(), print_value().c_str(), rhs.print_value().c_str());
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator-(express::real_type) const
   */
  REAL NUMBER::operator-(real_type rhs) const {
    REAL out;
    if (determinated) {
      out = get_number_value() - rhs;
    }

#ifdef TRACE_NUMBER
    printf("%s: %s = %s - %f\n", __MYFUNCNAME__, out.print_value().c_str(), print_value().c_str(), rhs);
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator-(const express::REAL&,const express::NUMBER&)
   */
  REAL operator-(const REAL& lhs, const NUMBER& rhs) {
    REAL out;
    if (lhs.determinated && rhs.determinated) {
      out = lhs.get_number_value() - rhs.get_number_value();
    }

#ifdef TRACE_NUMBER
    printf("%s: %s = %s - %s\n", __MYFUNCNAME__, out.print_value().c_str(), lhs.print_value().c_str(), rhs.print_value().c_str());
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator*(const express::NUMBER&) const
   */
  REAL NUMBER::operator*(const NUMBER& rhs) const {
    REAL out;
    if (determinated && rhs.determinated) {
      out = get_number_value() * rhs.get_number_value();
    }

#ifdef TRACE_NUMBER
    printf("%s: %s = %s * %s\n", __MYFUNCNAME__, out.print_value().c_str(), print_value().c_str(), rhs.print_value().c_str());
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator*(express::real_type) const
   */
  REAL NUMBER::operator*(real_type rhs) const {
    REAL out;
    if (determinated) {
      out = get_number_value() * rhs;
    }

#ifdef TRACE_NUMBER
    printf("%s: %s = %s * %f\n", __MYFUNCNAME__, out.print_value().c_str(), print_value().c_str(), rhs);
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator*(const express::REAL&,const express::NUMBER&)
   */
  REAL operator*(const REAL& lhs, const NUMBER& rhs) {
    REAL out;
    if (lhs.determinated && rhs.determinated) {
      out = lhs.get_number_value() * rhs.get_number_value();
    }

#ifdef TRACE_NUMBER
    printf("%s: %s = %s * %s\n", __MYFUNCNAME__, out.print_value().c_str(), lhs.print_value().c_str(), rhs.print_value().c_str());
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator/(const express::NUMBER&) const
   */
  REAL NUMBER::operator/(const NUMBER& rhs) const {
    REAL out;
    if (determinated && rhs.is_determinated()) {
      out = get_number_value() / rhs.get_number_value();
    }

#ifdef TRACE_NUMBER
    printf("%s: %s = %s / %s\n", __MYFUNCNAME__, out.print_value().c_str(), print_value().c_str(), rhs.print_value().c_str());
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator/(express::real_type) const
   */
  REAL NUMBER::operator/(real_type rhs) const {
    REAL out;
    if (determinated) {
      out = get_number_value() / rhs;
    }

#ifdef TRACE_NUMBER
    printf("%s: %s = %s / %f\n", __MYFUNCNAME__, out.print_value().c_str(), print_value().c_str(), rhs);
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator/(const express::REAL&,const express::NUMBER&)
   */
  REAL operator/(const REAL& lhs, const NUMBER& rhs) {
    REAL out;
    if (lhs.determinated && rhs.is_determinated()) {
      out = lhs.get_number_value() / rhs.get_number_value();
    }

#ifdef TRACE_NUMBER
    printf("%s: %s = %s / %s\n", __MYFUNCNAME__, out.print_value().c_str(), lhs.print_value().c_str(), rhs.print_value().c_str());
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator<<(const express::NUMBER&) const
   */
  REAL NUMBER::operator<<(const NUMBER& rhs) const {
    REAL out;
    if (is_determinated() && rhs.is_determinated()) {
      out = pow(get_number_value(), rhs.get_number_value());
    }

#ifdef TRACE_NUMBER
    printf("%s: %s = %s ** %s\n", __MYFUNCNAME__, out.print_value().c_str(), print_value().c_str(), rhs.print_value().c_str());
#endif

    return out;
  }


  /**
   * \file
   * * \copybrief express::NUMBER::operator<<(express::real_type) const
   */
  REAL NUMBER::operator<<(real_type rhs) const {
    REAL out;
    if (is_determinated()) {
      out = pow(get_number_value(), rhs);
    }

#ifdef TRACE_NUMBER
    printf("%s: %s = %s ** %f\n", __MYFUNCNAME__, out.print_value().c_str(), print_value().c_str(), rhs);
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator<<(express::real_type,express::const express::NUMBER&)
   */
  REAL operator<<(real_type lhs, const NUMBER& rhs) {
    REAL out;
    if (rhs.is_determinated()) {
      out = pow(lhs, rhs.get_number_value());
    }

#ifdef TRACE_NUMBER
    printf("%s: %s = %f ** %s\n", __MYFUNCNAME__, out.print_value().c_str(), lhs, rhs.print_value().c_str());
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator<<(const express::INTEGER,express::const express::NUMBER&)
   */
  REAL operator<<(const INTEGER& lhs, const NUMBER& rhs) {
    REAL out;
    if (lhs.is_determinated() && rhs.is_determinated()) {
      out = pow(lhs.get_number_value(), rhs.get_number_value());
    }

#ifdef TRACE_NUMBER
    printf("%s: %s = %f ** %s\n", __MYFUNCNAME__, out.print_value().c_str(), lhs.print_value().c_str(), rhs.print_value().c_str());
#endif

    return out;
  }



  /**
   * \file
   * * \copybrief express::NUMBER::operator>>(const express::NUMBER&) const
   */
  INTEGER NUMBER::operator>>(const NUMBER& rhs) const {
    INTEGER out;
    if (determinated && rhs.is_determinated()) {
      integer_type a =     is_integer() ?      get_integer_value() : real_to_integer(    get_number_value());
      integer_type b = rhs.is_integer() ?  rhs.get_integer_value() : real_to_integer(rhs.get_number_value());
      out = a / b;
    }

#ifdef TRACE_NUMBER
    printf("%s: %s = %s DIV %s\n", __MYFUNCNAME__, out.print_value().c_str(), print_value().c_str(), rhs.print_value().c_str());
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator>>(express::real_type) const
   */
  INTEGER NUMBER::operator>>(real_type rhs) const {
    INTEGER out;
    if (determinated) {
      integer_type a = is_integer() ? get_integer_value() : real_to_integer(    get_number_value());
      out = a / real_to_integer(rhs);
    }

#ifdef TRACE_NUMBER
    printf("%s: %s = %s DIV %f\n", __MYFUNCNAME__, out.print_value().c_str(), print_value().c_str(), rhs);
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator>>(const express::REAL,const express::NUMBER&)
   */
  INTEGER operator>>(const REAL& lhs, const NUMBER& rhs) {
    INTEGER out;
    if (lhs.determinated && rhs.is_determinated()) {
      integer_type a = lhs.is_integer() ? lhs.get_integer_value() : real_to_integer(lhs.get_number_value());
      integer_type b = rhs.is_integer() ? rhs.get_integer_value() : real_to_integer(rhs.get_number_value());
      out = a / b;
    }

#ifdef TRACE_NUMBER
    printf("%s: %s = %s DIV %s\n", __MYFUNCNAME__, out.print_value().c_str(), lhs.print_value().c_str(), rhs.print_value().c_str());
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator%(const express::NUMBER&) const
   */
  INTEGER NUMBER::operator%(const NUMBER& rhs) const {
    INTEGER out;
    if (determinated && rhs.is_determinated()) {
      integer_type a =     is_integer() ?     get_integer_value() : real_to_integer(    get_number_value());
      integer_type b = rhs.is_integer() ? rhs.get_integer_value() : real_to_integer(rhs.get_number_value());
      out = a % b;
    }

#ifdef TRACE_NUMBER
    printf("%s: %s = %s MOD %s\n", __MYFUNCNAME__, out.print_value().c_str(), print_value().c_str(), rhs.print_value().c_str());
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator%(express::real_type) const
   */
  INTEGER NUMBER::operator%(real_type rhs) const {
    INTEGER out;
    if (determinated) {
      integer_type a = is_integer() ? get_integer_value() : real_to_integer(get_number_value());
      out = a % real_to_integer(rhs);
    }

#ifdef TRACE_NUMBER
    printf("%s: %s = %s MOD %f\n", __MYFUNCNAME__, out.print_value().c_str(), print_value().c_str(), rhs);
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator%(const express::REAL,const express::NUMBER&)
   */
  INTEGER operator%(const REAL& lhs, const NUMBER& rhs) {
    INTEGER out;
    if (lhs.is_determinated() && rhs.is_determinated()) {
      integer_type a = lhs.is_integer() ?  lhs.get_integer_value() : real_to_integer(lhs.get_number_value());
      integer_type b = rhs.is_integer() ?  rhs.get_integer_value() : real_to_integer(rhs.get_number_value());
      out = a % b;
    }

#ifdef TRACE_NUMBER
    printf("%s: %s = %s MOD %s\n", __MYFUNCNAME__, out.print_value().c_str(), lhs.print_value().c_str(), rhs.print_value().c_str());
#endif

    return out;
  }

  /**
   * \file
   * Проверки равенства экземпляров ':=:' и отношений значений:
   */

  /**
   * \file
   * * \copybrief express::NUMBER::is_equal(const express::GENERIC&, bool) const
   */
  LOGICAL NUMBER::is_equal(const GENERIC& rhs, [[maybe_unused]] bool compare_value) const {
    if (!determinated || !rhs.is_determinated()) {
      return UNKNOWN;
    }
    if (is_number() || is_real() || is_integer()) {
      return is_number_value_equal(dynamic_cast<const NUMBER&>(rhs));
    }
    throw exception{ __MYFUNCNAME__, "rhs (%s) must be compatible to 'this' (%s)", rhs.get_type_name().c_str(), get_type_name().c_str() };
  }

  /**
   * \file
   * * \copybrief express::NUMBER::is_number_value_equal(const express::NUMBER&) const
   */
  LOGICAL NUMBER::is_number_value_equal(const NUMBER& rhs) const {
    if (!determinated || !rhs.is_determinated()) {
      return UNKNOWN;
    }

    int out = (is_integer() && rhs.is_integer()) ?
      INTEGER::compare(get_integer_value(), rhs.get_integer_value()) :
      REAL::compare(get_number_value(), get_number_precision(), rhs.get_number_value(),
        rhs.get_number_precision());

#ifdef TRACE_NUMBER
    printf("%s: %s (%s<%u>) = %s (%s<%u>) -> %s\n", __MYFUNCNAME__,
     print_value().c_str(), get_type_name().c_str(), get_number_precision(),
     rhs.print_value().c_str(), rhs.get_type_name().c_str(), rhs.get_number_precision(),
     out == 0 ? "TRUE" : "FALSE");
#endif

    return out == 0 ? TRUE : FALSE;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator==(const express::NUMBER&, express::real_type) const
   */
  LOGICAL operator==(const NUMBER& lhs, real_type rhs) {
    if (!lhs.is_determinated()) {
      return UNKNOWN;
    }
    rhs = REAL::round(rhs, REAL::precision_max);
    int out = REAL::compare(lhs.get_number_value(), lhs.get_number_precision(),
      rhs, REAL::precision_max);

#ifdef TRACE_NUMBER
    printf("%s: %s (%s<%u>) = %f (number_type) -> %s\n", __MYFUNCNAME__,
      print_value().c_str(), lhs.get_type_name().c_str(), lhs.get_number_precision(),
      rhs, out == 0 ? "TRUE" : "FALSE");
#endif

    return out == 0 ? TRUE : FALSE;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator==(express::real_type, const express::NUMBER&)
   */
  LOGICAL operator==(real_type lhs, const NUMBER& rhs) {
    if (!rhs.is_determinated()) {
      return UNKNOWN;
    }
    return rhs.is_number_value_equal(lhs);
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator!=(const express::NUMBER&, express::real_type)
   */
  LOGICAL operator!=(const NUMBER& lhs, real_type rhs) {
    return ! lhs.is_number_value_equal(rhs);
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator!=(express::real_type, const express::NUMBER&)
   */
  LOGICAL operator!=(real_type lhs, const NUMBER& rhs) {
    return ! rhs.is_number_value_equal(lhs);
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator>(const express::NUMBER&) const
   */
  LOGICAL NUMBER::operator>(const NUMBER& rhs) const {
    if (!determinated || !rhs.is_determinated()) {
      return UNKNOWN;
    }
    int out = (is_integer() && rhs.is_integer()) ?
      INTEGER::compare(get_integer_value(), rhs.get_integer_value()) :
      REAL::compare(get_number_value(), get_number_precision(),
      rhs.get_number_value(), rhs.get_number_precision());

#ifdef TRACE_NUMBER
    printf("%s: %s (%s<%u>) > %s (%s<%u>) -> %s\n", __MYFUNCNAME__,
     print_value().c_str(), get_type_name().c_str(), get_number_precision(),
     rhs.print_value().c_str(), rhs.get_type_name().c_str(), rhs.get_number_precision(),
     out > 0 ? "TRUE" : "FALSE");
#endif
    
    return out > 0 ? TRUE : FALSE;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator>(express::real_type) const
   */
  LOGICAL NUMBER::operator>(real_type rhs) const {
    if (!determinated) {
      return UNKNOWN;
    }
    int out = REAL::compare(get_number_value(), get_number_precision(),
      rhs, REAL::precision_max);

#ifdef TRACE_NUMBER
    printf("%s: %s (%s<%u>) > %f (number_type) -> %s\n", __MYFUNCNAME__,
      print_value().c_str(), get_type_name().c_str(), get_number_precision(),
      rhs,
      out > 0 ? "TRUE" : "FALSE");
#endif

    return out > 0 ? TRUE : FALSE;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator>(express::real_type, const express::NUMBER&)
   */
  LOGICAL operator>(real_type lhs, const NUMBER& rhs) {
    if (!rhs.is_determinated()) {
      return UNKNOWN;
    }
    return ! (rhs >= lhs);
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator>=(const express::NUMBER&) const
   */
  LOGICAL NUMBER::operator>=(const NUMBER& rhs) const {
    if (!determinated || !rhs.is_determinated()) {
      return UNKNOWN;
    }
    int out = (is_integer() && rhs.is_integer()) ?
      INTEGER::compare(get_integer_value(), rhs.get_integer_value()) :
      REAL::compare(get_number_value(), get_number_precision(),
      rhs.get_number_value(), rhs.get_number_precision());

#ifdef TRACE_NUMBER
    printf("%s: %s (%s<%u>) >= %s (%s<%u>) -> %s\n", __MYFUNCNAME__,
     print_value().c_str(), get_type_name().c_str(), get_number_precision(),
     rhs.print_value().c_str(), rhs.get_type_name().c_str(), rhs.get_number_precision(),
     out >= 0 ? "TRUE" : "FALSE");
#endif
    
    return out >= 0 ? TRUE : FALSE;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator>=(express::real_type) const
   */
  LOGICAL NUMBER::operator>=(real_type rhs) const {
    if (!determinated) {
      return UNKNOWN;
    }
    int out = REAL::compare(get_number_value(), get_number_precision(),
      rhs, REAL::precision_max);

#ifdef TRACE_NUMBER
    printf("%s: %s (%s<%u>) >= %f (number_type) -> %s\n", __MYFUNCNAME__,
      print_value().c_str(), get_type_name().c_str(), get_number_precision(),
      rhs,
      out >= 0 ? "TRUE" : "FALSE");
#endif

    return out >= 0 ? TRUE : FALSE;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator>=(express::real_type, const express::NUMBER&)
   */
  LOGICAL operator>=(real_type lhs, const NUMBER& rhs) {
    if (!rhs.is_determinated()) {
      return UNKNOWN;
    }
    return ! (rhs > lhs);
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator<(const express::NUMBER&) const
   */
  LOGICAL NUMBER::operator<(const NUMBER& rhs) const {
    if (!determinated || !rhs.is_determinated()) {
      return UNKNOWN;
    }
    return ! (*this >= rhs);
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator<(express::real_type) const
   */
  LOGICAL NUMBER::operator<(real_type rhs) const {
    if (!determinated) {
      return UNKNOWN;
    }
    return ! (*this >= rhs);
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator<(express::real_type, const express::NUMBER&)
   */
  LOGICAL operator<(real_type lhs, const NUMBER& rhs) {
    if (!rhs.is_determinated()) {
      return UNKNOWN;
    }
    return rhs > lhs;
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator<=(const express::NUMBER&) const
   */
  LOGICAL NUMBER::operator<=(const NUMBER& rhs) const {
    if (!determinated || !rhs.is_determinated()) {
      return UNKNOWN;
    }
    return ! (*this > rhs);
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator<=(express::real_type) const
   */
  LOGICAL NUMBER::operator<=(real_type rhs) const {
    if (!determinated) {
      return UNKNOWN;
    }
    return ! (*this > rhs);
  }

  /**
   * \file
   * * \copybrief express::NUMBER::operator<=(express::real_type, const express::NUMBER&)
   */
  LOGICAL operator<=(real_type lhs, const NUMBER& rhs) {
    if (!rhs.is_determinated()) {
      return UNKNOWN;
    }
    return rhs >= lhs;
  }
}
