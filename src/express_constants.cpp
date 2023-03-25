/**
 * \file
 *
 * \brief Файл с определениями констант, соответствующих ГОСТ Р ИСО 10303-11-2009, п.14
 *
 * Здесь определены встроенные константы языка EXPRESS.
 */

#include "stdafx.h"
#include "express.h"

namespace express {

  /* 14.1 */
  const REAL CONST_E = 2.71828182845904523536;

  /* 14.2 */
//  const GENERIC INDET(false);

  /* 14.3 */
  const BOOLEAN FALSE = BOOLEAN::FALSE;

  /* 14.4 */
  const REAL PI = 3.14159265358979323846;

  /* 14.6 */
  const BOOLEAN TRUE = BOOLEAN::TRUE;

  /* 14.7 */
  const LOGICAL UNKNOWN = LOGICAL::UNKNOWN;
}