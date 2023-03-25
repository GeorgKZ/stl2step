/**
 * \file
 * \brief Файл с описанием простого типа данных SIMPLE языка EXPRESS
 * (ГОСТ Р ИСО 10303-11-2009, 8.1)
 */

namespace express {

  /**
   * \brief Простой тип данных EXPRESS (\ref p11_s8_1 "ГОСТ Р ИСО 10303-11-2009, п.8.1")
   *
   * \ref express::SIMPLE "Простые типы данных" определяют области определения элементарных единиц данных в языке
   * EXPRESS. To есть они не могут быть разделены на элементы, распознаваемые в языке EXPRESS.
   * Простыми типами данных являются
   * \ref express::NUMBER "NUMBER" (числовой),
   * \ref express::REAL "REAL" (действительный),
   * \ref express::INTEGER "INTEGER" (целочисленный),
   * \ref express::STRING "STRING" (строковый),
   * \ref express::BOOLEAN "BOOLEAN" (булев),
   * \ref express::LOGICAL "LOGICAL" (логический) и
   * \ref express::BINARY "BINARY" (двоичный).
   */
  class SIMPLE : public GENERIC {

  protected:

    /**
     * \brief Получить тип данных
     * \return тип данных в виде элемента перечисления OBJTYPE
     */
    virtual constexpr OBJTYPE objtype() const override {
      return OBJTYPE::OBJ_SIMPLE;
    }

  public:

    /** \brief Конструктор, включающий возможность создания неопределённого типа */
    SIMPLE(bool Determinated = true) : GENERIC(Determinated) {
    }

    /** \brief Деструктор --- по умолчанию */
    virtual ~SIMPLE() = default;
  };
}