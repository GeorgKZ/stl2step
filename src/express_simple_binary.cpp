/**
 * \file
 *
 * \brief Файл с определениями функций класса BINARY, соответствующего ГОСТ Р ИСО 10303-11-2009, п.8.1.7
 *
 * Здесь определены функции, реализующие функции-члены класса BINARY, соответствующего бинарному типу
 * данных языка EXPRESS.
 */

#include "stdafx.h"
#include "express.h"

namespace express {

  /**
   * \file
   * Для типа BINARY определены следующие члены-методы (функции):<BR><BR>
   */

  /**
   * \file
   * Конструкторы (неопределённого значения, копирующий и конструктор из значения)
   * и оператор присваивания:
   */

  /**
   * \file
   * * \copybrief express::BINARY::BINARY()
   */
  BINARY::BINARY() : SIMPLE(false) {
    append_to_parent_type_list();
  }

  /**
   * \file
   * * \copybrief express::BINARY::BINARY(const express::BINARY&)
   */
  BINARY::BINARY(const BINARY& rhs) : SIMPLE() {
    append_to_parent_type_list();

    if (!rhs.is_determinated()) {
      determinated = false;
    } else {
      determinated = false;
      _b = rhs._b;
    }
  }

  /**
   * \file
   * * \copybrief express::BINARY::operator=(const express::BINARY&)
   */
  BINARY& BINARY::operator=(const BINARY& rhs) {
    if (this != std::addressof(rhs)) {
      if (!rhs.is_determinated()) {
        determinated = false;
        _b.clear();
      } else {
        determinated = true;
        _b = rhs._b;
      }
    }
    return *this;
  }

  LOGICAL BINARY::is_equal(const GENERIC& rhs, [[maybe_unused]] bool compare_value) const {
    if (is_binary() && rhs.is_binary()) {
      return is_binary_value_equal(dynamic_cast<const BINARY&>(rhs));
    }
    throw exception{ __MYFUNCNAME__, "rhs (%s) must be compatible to 'this' (%s)", rhs.get_type_name().c_str(), get_type_name().c_str() };
  }

  LOGICAL BINARY::is_binary_value_equal(const BINARY& rhs) const {
    if (!is_determinated() || !rhs.is_determinated()) {
      return UNKNOWN;
    }
    return _b == rhs._b ? TRUE : FALSE;
  }

  GENERIC::COMPAT BINARY::check_compatibility(const GENERIC& rhs) const {
    if (is_binary() && rhs.is_binary()) {
      return COMPAT::COMPAT_SAME;
    }
    return COMPAT::COMPAT_NONE;
  }

  /**
   * \file
   * Получение значения типа, вывод значения типа в виде строки:
   */

  /**
   * \file
   * * \copybrief express::BINARY::objtype() const
   */
  GENERIC::OBJTYPE BINARY::objtype() const {
    return OBJTYPE::OBJ_SIMPLE | OBJTYPE::OBJ_BINARY;
  }
}