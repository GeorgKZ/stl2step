/**
 * \file
 * \brief Файл с описанием констант языка EXPRESS (ГОСТ Р ИСО 10303-11-2009, 14)
 */

namespace express {

  /**
   * \brief CONST CONST_E (ГОСТ Р ИСО 10303-11-2009, 14.1)
   *
   * \ref express::CONST_E "14.1 Константа e"
   *
   * \ref express::CONST_E "CONST_E" является константой типа \ref express::REAL "REAL",
   * являющегося основанием функции натурального логарифма (<B>ln</B>). Значение данной константы задаётся
   * следующей математической формулой
   *
   * \f[
     e = \sum_{i=0}^{\infty}i!^{-1}.
   * \f] 
   */
   extern const REAL CONST_E;

  /**
   * \brief CONST FALSE (ГОСТ Р ИСО 10303-11-2009, 14.3)
   *
   * \ref express::FALSE "14.3 Константа FALSE"
   *
   * Константа \ref express::FALSE "FALSE" является константой типа \ref express::LOGICAL "LOGICAL",
   * представляющей логическое понятие «ложь». Данная константа
   * совместима с типами данных \ref express::BOOLEAN "BOOLEAN" и \ref express::LOGICAL "LOGICAL".
   */
  extern const BOOLEAN FALSE;

  /**
   * \brief CONST PI (ГОСТ Р ИСО 10303-11-2009, 14.4)
   *
   * \ref express::PI "14.4 Константа PI"
   *
   * Константа \ref express::PI "PI" является константой типа \ref express::REAL "REAL",
   * представляющей математическую
   * величину \f$ \pi \f$, представляющую отношение длины окружности к её диаметру.
   */
  extern const REAL PI;

  /**
   * \brief CONST TRUE (ГОСТ Р ИСО 10303-11-2009, 14.6)
   *
   * \ref express::TRUE "14.6 Константа TRUE"
   *
   * Константа \ref express::TRUE "TRUE" является константой типа \ref express::LOGICAL "LOGICAL",
   * представляющей логическое понятие «истина». Данная константа
   * совместима с типами данных \ref express::BOOLEAN "BOOLEAN" и \ref express::LOGICAL "LOGICAL".
   */
  extern const BOOLEAN TRUE;

  /**
   * \brief CONST UNKNOWN (ГОСТ Р ИСО 10303-11-2009, 14.7)
   *
   * \ref express::UNKNOWN "14.7 Константа UNKNOWN"
   *
   * Константа \ref express::UNKNOWN "UNKNOWN" является константой типа \ref express::LOGICAL "LOGICAL",
   * обозначающей недостаточность имеющейся информации для оценки логического условия. Данная константа
   * совместима с типом данных \ref express::LOGICAL "LOGICAL", но несовместима с типом данных \ref express::BOOLEAN "BOOLEAN".
   */
  extern const LOGICAL UNKNOWN;
}
