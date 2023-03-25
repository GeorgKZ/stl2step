/**
 * \file
 *
 * \brief Файл с определениями функций класса BOOLEAN, соответствующего ГОСТ Р ИСО 10303-11-2009, п.8.1.5
 *
 * Здесь определены функции, реализующие функции-члены класса BOOLEAN, соответствующего булевому типу
 * данных языка EXPRESS.
 */

#include "stdafx.h"
#include "express.h"

namespace express {

  /**
   * \file
   * Для типа BOOLEAN определены следующие члены-методы (функции):<BR><BR>
   */

  /**
   * \file
   * Конструкторы (неопределённого значения, копирующий и конструктор из значения)
   * и оператор присваивания:
   */

  /**
   * \file
   * * \copybrief express::BOOLEAN::BOOLEAN()
   */
  BOOLEAN::BOOLEAN() {
    append_to_parent_type_list();
  }

  /**
   * \file
   * * \copybrief express::BOOLEAN::BOOLEAN(const express::BOOLEAN&)
   */
  BOOLEAN::BOOLEAN(const BOOLEAN& src) : LOGICAL(src) {
    append_to_parent_type_list();

    if (src.is_unknown()) {
      throw exception{__MYFUNCNAME__, "BOOLEAN must not have value 'UNKNOWN'"};
    }
  }

  /**
   * \file
   * * \copybrief express::BOOLEAN::BOOLEAN(express::LOGICAL::value)
   */
  BOOLEAN::BOOLEAN(BOOLEAN::value src) : LOGICAL(src) {
    append_to_parent_type_list();
  }

  /**
   * \file
   * * \copybrief express::BOOLEAN::operator=(const express::BOOLEAN&)
   */
  BOOLEAN& BOOLEAN::operator=(const BOOLEAN& rhs) {
    if (this != std::addressof(rhs)) {
      if (!rhs.is_determinated()) {
        determinated = false;
        _l = FALSE;
      } else {
        determinated = true;
        _l = rhs.get_value();
        if (rhs.is_unknown()) {
          throw exception{__MYFUNCNAME__, "BOOLEAN must not have value 'UNKNOWN'"};
        }
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
   * * \copybrief express::BOOLEAN::is_unknown()
   */
  bool BOOLEAN::is_unknown() const {
    if (!determinated) {
      return false;
    }
    if (_l == LOGICAL::UNKNOWN) {
      throw exception{__MYFUNCNAME__, "BOOLEAN must not have value 'UNKNOWN'"};
    }
    return false;
  }

  /**
   * \file
   * * \copybrief express::BOOLEAN::objtype() const
   */
  constexpr GENERIC::OBJTYPE BOOLEAN::objtype() const {
    return OBJTYPE::OBJ_SIMPLE | OBJTYPE::OBJ_BOOLEAN;
  }

#if 0
  /**
   * \file
   * * \copybrief express::BOOLEAN::print_value() const
   */
  std::string BOOLEAN::print_value() const {
    if (_l == UNKNOWN) {
      throw exception{ __MYFUNCNAME__, "BOOLEAN must have value 'TRUE' or 'FALSE'" };
    }
    return print_enum_value(LOGICAL::value_str, std::size(LOGICAL::value_str), static_cast<size_t>(_l));
  }
#endif
}