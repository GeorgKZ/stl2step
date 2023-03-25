/**
 * \file
 *
 * \brief Файл с определениями функций класса LOGICAL, соответствующего ГОСТ Р ИСО 10303-11-2009, п.8.1.5
 *
 * Здесь определены функции, реализующие функции-члены класса LOGICAL, соответствующему логическому
 * типу данных языка EXPRESS.
 */

#include "stdafx.h"
#include "express.h"

namespace express {

  /**
   * \file
   * Для типа LOGICAL определены следующие члены-методы (функции):<BR><BR>
   */

  /**
   * \file
   * Конструкторы (неопределённого значения, копирующий и конструктор из значения)
   * и оператор присваивания:
   */

  /**
   * \file
   * * \copybrief express::LOGICAL::LOGICAL()
   */
  LOGICAL::LOGICAL() : SIMPLE(false), _l(UNKNOWN) {
    append_to_parent_type_list();
  }

  /**
   * \file
   * * \copybrief express::LOGICAL::LOGICAL(const express::LOGICAL&)
   */
  LOGICAL::LOGICAL(const LOGICAL& src) : SIMPLE(), _l(src.get_value()) {
    append_to_parent_type_list();
  }

  /**
   * \file
   * * \copybrief express::LOGICAL::LOGICAL(express::LOGICAL::value)
   */
  LOGICAL::LOGICAL(LOGICAL::value src) : _l(src) {
    append_to_parent_type_list();
  }

  /**
   * \file
   * * \copybrief express::LOGICAL::operator=(const express::LOGICAL&)
   */
  LOGICAL& LOGICAL::operator=(const LOGICAL& rhs) {
    if (this != std::addressof(rhs)) {
      if (rhs.determinated) {
        determinated = true;
        _l = rhs._l;
      }
      else {
        determinated = false;
        _l = UNKNOWN;
      }
    }
    return *this;
  }

  /**
   * \file
   * Получение значения типа, вывод значения типа в виде строки:
   */

  /**
   * \file
   * * \copybrief express::LOGICAL::is_true()
   */
  bool LOGICAL::is_true() const {
    if (!determinated) {
      return false;
    }
    return _l == TRUE;
  }

  /**
   * \file
   * * \copybrief express::LOGICAL::is_false()
   */
  bool LOGICAL::is_false() const {
    if (!determinated) {
      return false;
    }
    return _l == FALSE;
  }

  /**
   * \file
   * * \copybrief express::LOGICAL::is_unknown()
   */
  bool LOGICAL::is_unknown() const {
    if (!determinated) {
      return false;
    }
    return _l == UNKNOWN;
  }

  /**
   * \file
   * * \copybrief express::LOGICAL::get_value() const
   */
  LOGICAL::value LOGICAL::get_value() const {
    return _l;
  }

  /**
   * \file
   * * \copybrief express::LOGICAL::objtype() const
   */
  constexpr GENERIC::OBJTYPE LOGICAL::objtype() const {
    return OBJTYPE::OBJ_SIMPLE | OBJTYPE::OBJ_LOGICAL;
  }

  /**
   * \file
   * * \copybrief express::LOGICAL::check_compatibility(const express::GENERIC&) const
   */
  GENERIC::COMPAT LOGICAL::check_compatibility(const GENERIC& rhs) const
  {
    if (is_logical() && rhs.is_logical()) {
      return COMPAT::COMPAT_SAME;
    }
    if (is_boolean() && rhs.is_logical()) {
      return COMPAT::COMPAT_FORWARD;
    }
    if (is_logical() && rhs.is_boolean()) {
      return COMPAT::COMPAT_BACKWARD;
    }
    return COMPAT::COMPAT_NONE;
  }

  /**
   * \file
   * * \copybrief express::LOGICAL::print_value() const
   */
  std::string LOGICAL::print_value() const {
    return print_enum_value(LOGICAL::value_str, std::size(LOGICAL::value_str), static_cast<size_t>(_l));
  }

  /**
   * \file
   * Логические операции (отрицание, пересечение, объединение...):
   */

  /**
   * \file
   * * \copybrief express::LOGICAL::operator!() const
   */
  LOGICAL LOGICAL::operator !() const {
    LOGICAL a(    is_determinated() ?     get_value() : UNKNOWN);

    switch(a._l) {
      case LOGICAL::TRUE:    return LOGICAL::FALSE;
      case LOGICAL::FALSE:   return LOGICAL::TRUE;
      case LOGICAL::UNKNOWN: return LOGICAL::UNKNOWN;
      default:
        /* Unknown LOGICAL value */
        assert(0);
        return LOGICAL::UNKNOWN;
    }
  }

  /**
   * \file
   * * \copybrief express::LOGICAL::operator&&(const express::LOGICAL&) const
   */
  LOGICAL LOGICAL::operator &&(const LOGICAL& rhs) const {
    LOGICAL a(    is_determinated() ?     get_value() : UNKNOWN);
    LOGICAL b(rhs.is_determinated() ? rhs.get_value() : UNKNOWN);
   
    if (a._l == LOGICAL::TRUE    && b.is_true())    return LOGICAL::TRUE;
    if (a._l == LOGICAL::TRUE    && b.is_unknown()) return LOGICAL::UNKNOWN;
    if (a._l == LOGICAL::TRUE    && b.is_false())   return LOGICAL::FALSE;
                                                   
    if (a._l == LOGICAL::UNKNOWN && b.is_true())    return LOGICAL::UNKNOWN;
    if (a._l == LOGICAL::UNKNOWN && b.is_unknown()) return LOGICAL::UNKNOWN;
    if (a._l == LOGICAL::UNKNOWN && b.is_false())   return LOGICAL::FALSE;
                                                   
    if (a._l == LOGICAL::FALSE   && b.is_true())    return LOGICAL::FALSE;
    if (a._l == LOGICAL::FALSE   && b.is_unknown()) return LOGICAL::FALSE;
    if (a._l == LOGICAL::FALSE   && b.is_false())   return LOGICAL::FALSE;

    throw exception{__MYFUNCNAME__, "internal error, combination of *this = %s and rhs = %s", this->print_value().c_str(), rhs.print_value().c_str()};
  }

  /**
   * \file
   * * \copybrief express::LOGICAL::operator||(const express::LOGICAL&) const
   */
  LOGICAL LOGICAL::operator ||(const LOGICAL& rhs) const {
    LOGICAL a(    is_determinated() ?     get_value() : UNKNOWN);
    LOGICAL b(rhs.is_determinated() ? rhs.get_value() : UNKNOWN);
    
    if (a._l == LOGICAL::TRUE    && b._l == LOGICAL::TRUE)    return LOGICAL::TRUE;
    if (a._l == LOGICAL::TRUE    && b._l == LOGICAL::UNKNOWN) return LOGICAL::TRUE;
    if (a._l == LOGICAL::TRUE    && b._l == LOGICAL::FALSE)   return LOGICAL::TRUE;

    if (a._l == LOGICAL::UNKNOWN && b._l == LOGICAL::TRUE)    return LOGICAL::TRUE;
    if (a._l == LOGICAL::UNKNOWN && b._l == LOGICAL::UNKNOWN) return LOGICAL::UNKNOWN;
    if (a._l == LOGICAL::UNKNOWN && b._l == LOGICAL::FALSE)   return LOGICAL::UNKNOWN;

    if (a._l == LOGICAL::FALSE   && b._l == LOGICAL::TRUE)    return LOGICAL::TRUE;
    if (a._l == LOGICAL::FALSE   && b._l == LOGICAL::UNKNOWN) return LOGICAL::UNKNOWN;
    if (a._l == LOGICAL::FALSE   && b._l == LOGICAL::FALSE)   return LOGICAL::FALSE;

    throw exception{__MYFUNCNAME__, "internal error, combination of *this = %s and rhs = %s", this->print_value().c_str(), rhs.print_value().c_str()};
  }

  /**
   * \file
   * * \copybrief express::LOGICAL::operator^(const express::LOGICAL&) const
   */
  LOGICAL LOGICAL::operator ^(const LOGICAL& rhs) const {
    LOGICAL a(    is_determinated() ?     get_value() : UNKNOWN);
    LOGICAL b(rhs.is_determinated() ? rhs.get_value() : UNKNOWN);
    
    if (a._l == LOGICAL::TRUE    && b._l == LOGICAL::TRUE)    return LOGICAL::FALSE;
    if (a._l == LOGICAL::TRUE    && b._l == LOGICAL::UNKNOWN) return LOGICAL::UNKNOWN;
    if (a._l == LOGICAL::TRUE    && b._l == LOGICAL::FALSE)   return LOGICAL::TRUE;

    if (a._l == LOGICAL::UNKNOWN && b._l == LOGICAL::TRUE)    return LOGICAL::UNKNOWN;
    if (a._l == LOGICAL::UNKNOWN && b._l == LOGICAL::UNKNOWN) return LOGICAL::UNKNOWN;
    if (a._l == LOGICAL::UNKNOWN && b._l == LOGICAL::FALSE)   return LOGICAL::UNKNOWN;

    if (a._l == LOGICAL::FALSE   && b._l == LOGICAL::TRUE)    return LOGICAL::TRUE;
    if (a._l == LOGICAL::FALSE   && b._l == LOGICAL::UNKNOWN) return LOGICAL::UNKNOWN;
    if (a._l == LOGICAL::FALSE   && b._l == LOGICAL::FALSE)   return LOGICAL::FALSE;

    throw exception{__MYFUNCNAME__, "internal error, combination of *this = %s and rhs = %s", this->print_value().c_str(), rhs.print_value().c_str()};
  }

  /**
   * \file
   * Проверки равенства и отношений значений:
   */

  /**
   * \file
   * * \copybrief express::LOGICAL::is_equal(const express::GENERIC&, bool) const
   */
  LOGICAL LOGICAL::is_equal(const GENERIC& rhs, [[maybe_unused]] bool compare_value) const {
    if (!determinated || !rhs.is_determinated()) {
      return UNKNOWN;
    }
    if (rhs.is_logical() || rhs.is_boolean()) {
      return is_logical_value_equal(dynamic_cast<const LOGICAL&>(rhs));
    }
    throw exception{ __MYFUNCNAME__, "rhs (%s) must be compatible to 'this' (%s)", rhs.get_type_name().c_str(), get_type_name().c_str() };
  }

  /**
   * \file
   * * \copybrief express::LOGICAL::is_logical_value_equal(const express::LOGICAL&) const
   */
  LOGICAL LOGICAL::is_logical_value_equal(const LOGICAL& rhs) const {
    if (!determinated || !rhs.is_determinated()) {
      return LOGICAL::UNKNOWN;
    }

    if      (_l == LOGICAL::TRUE    && rhs.is_true())    return LOGICAL::TRUE;
    else if (_l == LOGICAL::TRUE    && rhs.is_unknown()) return LOGICAL::FALSE;
    else if (_l == LOGICAL::TRUE    && rhs.is_false())   return LOGICAL::FALSE;

    else if (_l == LOGICAL::UNKNOWN && rhs.is_true())    return LOGICAL::FALSE;
    else if (_l == LOGICAL::UNKNOWN && rhs.is_unknown()) return LOGICAL::TRUE;
    else if (_l == LOGICAL::UNKNOWN && rhs.is_false())   return LOGICAL::FALSE;

    else if (_l == LOGICAL::FALSE   && rhs.is_true())    return LOGICAL::FALSE;
    else if (_l == LOGICAL::FALSE   && rhs.is_unknown()) return LOGICAL::FALSE;
    else if (_l == LOGICAL::FALSE   && rhs.is_false())   return LOGICAL::TRUE;

    throw exception{__MYFUNCNAME__, "internal error, combination of *this = %s and rhs = %s", this->print_value().c_str(), rhs.print_value().c_str()};
  }

  /**
   * \file
   * * \copybrief express::LOGICAL::operator>(const express::LOGICAL&) const
   */
  LOGICAL LOGICAL::operator>(const LOGICAL& rhs) const {
    if (!determinated || !rhs.determinated) {
      return LOGICAL::UNKNOWN;
    }
    if      (_l == LOGICAL::TRUE    && rhs.is_true())    return LOGICAL::FALSE;
    else if (_l == LOGICAL::TRUE    && rhs.is_unknown()) return LOGICAL::TRUE;
    else if (_l == LOGICAL::TRUE    && rhs.is_false())   return LOGICAL::TRUE;

    else if (_l == LOGICAL::UNKNOWN && rhs.is_true())    return LOGICAL::FALSE;
    else if (_l == LOGICAL::UNKNOWN && rhs.is_unknown()) return LOGICAL::FALSE;
    else if (_l == LOGICAL::UNKNOWN && rhs.is_false())   return LOGICAL::TRUE;

    else if (_l == LOGICAL::FALSE   && rhs.is_true())    return LOGICAL::FALSE;
    else if (_l == LOGICAL::FALSE   && rhs.is_unknown()) return LOGICAL::FALSE;
    else if (_l == LOGICAL::FALSE   && rhs.is_false())   return LOGICAL::FALSE;

    throw exception{__MYFUNCNAME__, "internal error, combination of *this = %s and rhs = %s", this->print_value().c_str(), rhs.print_value().c_str()};
  }

  /**
   * \file
   * * \copybrief express::LOGICAL::operator>=(const express::LOGICAL&) const
   */
  LOGICAL LOGICAL::operator>=(const LOGICAL& rhs) const {
    if (!determinated || !rhs.determinated) {
      return LOGICAL::UNKNOWN;
    }

    if      (_l == LOGICAL::TRUE    && rhs.is_true())    return LOGICAL::TRUE;
    else if (_l == LOGICAL::TRUE    && rhs.is_unknown()) return LOGICAL::TRUE;
    else if (_l == LOGICAL::TRUE    && rhs.is_false())   return LOGICAL::TRUE;

    else if (_l == LOGICAL::UNKNOWN && rhs.is_true())    return LOGICAL::FALSE;
    else if (_l == LOGICAL::UNKNOWN && rhs.is_unknown()) return LOGICAL::TRUE;
    else if (_l == LOGICAL::UNKNOWN && rhs.is_false())   return LOGICAL::TRUE;

    else if (_l == LOGICAL::FALSE   && rhs.is_true())    return LOGICAL::FALSE;
    else if (_l == LOGICAL::FALSE   && rhs.is_unknown()) return LOGICAL::FALSE;
    else if (_l == LOGICAL::FALSE   && rhs.is_false())   return LOGICAL::TRUE;

    throw exception{__MYFUNCNAME__, "internal error, combination of *this = %s and rhs = %s", this->print_value().c_str(), rhs.print_value().c_str()};
  }

  /**
   * \file
   * * \copybrief express::LOGICAL::operator<(const express::LOGICAL&) const
   */
  LOGICAL LOGICAL::operator<(const LOGICAL& rhs) const {
    if (!determinated || !rhs.determinated) {
      return LOGICAL::UNKNOWN;
    }

    if      (_l == LOGICAL::TRUE    && rhs.is_true())    return LOGICAL::FALSE;
    else if (_l == LOGICAL::TRUE    && rhs.is_unknown()) return LOGICAL::FALSE;
    else if (_l == LOGICAL::TRUE    && rhs.is_false())   return LOGICAL::FALSE;
                                                         
    else if (_l == LOGICAL::UNKNOWN && rhs.is_true())    return LOGICAL::TRUE;
    else if (_l == LOGICAL::UNKNOWN && rhs.is_unknown()) return LOGICAL::FALSE;
    else if (_l == LOGICAL::UNKNOWN && rhs.is_false())   return LOGICAL::FALSE;
                                                         
    else if (_l == LOGICAL::FALSE   && rhs.is_true())    return LOGICAL::TRUE;
    else if (_l == LOGICAL::FALSE   && rhs.is_unknown()) return LOGICAL::TRUE;
    else if (_l == LOGICAL::FALSE   && rhs.is_false())   return LOGICAL::FALSE;

    throw exception{__MYFUNCNAME__, "internal error, combination of *this = %s and rhs = %s", this->print_value().c_str(), rhs.print_value().c_str()};
  }

  /**
   * \file
   * * \copybrief express::LOGICAL::operator<=(const express::LOGICAL&) const
   */
  LOGICAL LOGICAL::operator<=(const LOGICAL& rhs) const {
    if (!determinated || !rhs.is_determinated()) {
      return LOGICAL::UNKNOWN;
    }

    if      (_l == LOGICAL::TRUE    && rhs.is_true())    return TRUE;
    else if (_l == LOGICAL::TRUE    && rhs.is_unknown()) return FALSE;
    else if (_l == LOGICAL::TRUE    && rhs.is_false())   return FALSE;
                                                         
    else if (_l == LOGICAL::UNKNOWN && rhs.is_true())    return TRUE;
    else if (_l == LOGICAL::UNKNOWN && rhs.is_unknown()) return TRUE;
    else if (_l == LOGICAL::UNKNOWN && rhs.is_false())   return FALSE;
                                                         
    else if (_l == LOGICAL::FALSE   && rhs.is_true())    return TRUE;
    else if (_l == LOGICAL::FALSE   && rhs.is_unknown()) return TRUE;
    else if (_l == LOGICAL::FALSE   && rhs.is_false())   return TRUE;

    throw exception{__MYFUNCNAME__, "internal error, combination of *this = %s and rhs = %s", this->print_value().c_str(), rhs.print_value().c_str()};
  }
}