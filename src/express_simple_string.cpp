/**
 * \file
 *
 * \brief Файл с определениями функций класса STRING, соответствующего ГОСТ Р ИСО 10303-11-2009, п.8.1.6
 *
 * Здесь определены функции, реализующие функции-члены класса STRING, соответствующего строковому типу
 * данных языка EXPRESS.
 */

#include "stdafx.h"
#include "express.h"

namespace express {

  /**
   * \file
   * * \copybrief express::STRING::objtype() const
   */
  GENERIC::OBJTYPE STRING::objtype() const {
    return OBJTYPE::OBJ_SIMPLE | OBJTYPE::OBJ_STRING;
  }

  GENERIC::COMPAT STRING::check_compatibility(const GENERIC& rhs) const {
    if (is_string() && rhs.is_string()) {
      return COMPAT::COMPAT_SAME;
    }
    return COMPAT::COMPAT_NONE;

  }

  /**
   * \file
   * * \copybrief express::STRING::is_equal(const express::GENERIC&, bool) const
   */
  LOGICAL STRING::is_equal(const GENERIC& rhs, [[maybe_unused]] bool compare_value) const {
    if (!determinated || !rhs.is_determinated()) {
      return UNKNOWN;
    }

    if (rhs.is_string()) {

      return _s == dynamic_cast<const STRING&>(rhs)._s ? LOGICAL::TRUE : LOGICAL::FALSE;
    }
    throw exception{ __MYFUNCNAME__, "rhs (%s) must be compatible to 'this' (%s)", rhs.get_type_name().c_str(), get_type_name().c_str() };
  }
}