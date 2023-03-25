/**
 * \file
 * \brief Файл с описанием простого двоичного типа данных BINARY языка EXPRESS
 * (ГОСТ Р ИСО 10303-11-2009, 8.1.7; ГОСТ Р ИСО 10303-21, 6.3)
 */

namespace express {

  /** 
   * \brief Простой тип \ref express::BINARY "BINARY --- двоичное значение" (ГОСТ Р ИСО 10303-11-2009, 8.1.7)
   *
   * \anchor p11_s8_1_7
   *
   * \ref express::STRING "8.1.7 Двоичный тип данных"
   *
   * Областью определения типа данных \ref express::BINARY "BINARY" являются последовательности битов, каждый
   * из которых представляется 0 или 1.
   \verbatim
     Синтаксис:
      181 binary_type = BINARY [ width_spec ] .
      341 width_spec = '(' width ')' [ FIXED ] .
      340 width = numeric_expression .
   \endverbatim
   * Тип данных \ref express::BINARY "BINARY" может иметь как фиксированную, так и переменную длину (число битов). Если
   * конкретно не указана фиксированная длина (посредством зарезервированного слова FIXED в
   * определении), то тип данных \ref express::BINARY "BINARY" имеет переменную длину.
   *
   * Областью определения типа данных \ref express::BINARY "BINARY" фиксированной длины является множество всех
   * последовательностей битов длины, точно указанной в определении типа.
   *
   * Областью определения типа данных \ref express::BINARY "BINARY" переменной длины является множество всех
   * последовательностей битов длины меньшей или равной максимальной длине, указанной в определении типа. Если
   * длина не указана, то областью определения является множество всех последовательностей битов без
   * ограничения на длину этих последовательностей.
   *
   * Адресация к частям последовательности битов и отдельным битам может осуществляться
   * посредством подстрочных индексов, как описано в 12.3.
   *
   * Правило: значением выражения <B>width</B> должно быть положительное целое число.
   *
   * <B><I>Пример --- Данный фрагмент может быть использован для хранения информации о шрифте символов:</I>
   <PRE>
     ENTITY character;
     representation : ARRAY [1:20] OF BINARY (8) FIXED ;
     END_ENTITY;
   </PRE> </B>
   */
  class BINARY : public SIMPLE {

  private:

    /**
     * \brief Значение типа BINARY --- последовательность бит
     */
    std::vector<unsigned char> _b;

  protected:

    /** 
     *\brief Получить принадлёжность типа данных к одной из групп
     * \return тип данных в виде элемента перечисления OBJTYPE.
     */
    virtual OBJTYPE objtype() const override;

  public:

    /**
     * \brief Конструктор типа BINARY, имеющего неопределённое (<B>?</B>) значение
     */
    BINARY();

    /**
     * \brief Копирующий конструктор типа BINARY
     */
    BINARY(const BINARY& rhs);

    /** \brief Деструктор --- по умолчанию */
    virtual ~BINARY() = default;

    /**
     * \brief Оператор присвоения типа BINARY
     */
    BINARY& operator=(const BINARY& rhs);

    /**
     * \brief Проверка равенства значения или экземпляра с неизвестным типом
     * 
     * \param [in] rhs Объект, с которым выполняется сравнение.
     * \param [in] compare_value true, если сравниваются значения и false, если экземпляры.
     * \return результат проверки равенства значений или экземпляров.
     *
     * Неизвестный тип передан как ссылка на базовый тип GENERIC.
     */
    virtual LOGICAL is_equal(const GENERIC& rhs, bool compare_value) const override;

    /**
     * \brief Проверка равенства значения значений бинарного типа BINARY (или дочерних типов)
     * с бинарным типом BINARY (или дочерними типами)
     * \param rhs [in] Сравниваемый бинарный тип BINARY.
     * \return Логическое выражение типа LOGICAL --- результат сравнения значений бинарного
     * типа BINARY и rhs.
     */
    LOGICAL is_binary_value_equal(const BINARY& rhs) const;

    /**
     * \brief Проверить совместимость  бинарного типа с некоторым типом.
     *
     * \param [in] rhs Тип, с которым будет произведено сравнение, переданный в виде ссылки
     * на тип GENERIC.
     * \return результат сравнения типов в виде перечисления COMPAT.
     */
    virtual COMPAT check_compatibility(const GENERIC& rhs) const override;
  };

  class BINARY_FIXED : public BINARY {

  public:
    /**
     * \brief Конструктор типа BINARY_FIXED, имеющего неопределённое (<B>?</B>) значение
     */
    BINARY_FIXED() : BINARY() {
    }

    /** \brief Деструктор --- по умолчанию */
    virtual ~BINARY_FIXED() = default;
  };
}
