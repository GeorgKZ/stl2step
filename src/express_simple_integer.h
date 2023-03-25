/**
 * \file
 * \brief Файл с описанием простого целочисленного типа данных INTEGER языка EXPRESS
 * (ГОСТ Р ИСО 10303-11-2009, 8.1.3; ГОСТ Р ИСО 10303-21, 6.3)
 */

namespace express {

  /** 
   * \brief Простой тип \ref express::INTEGER "INTEGER" --- Целое число (ГОСТ Р ИСО 10303-11-2009, 8.1.3)
   *
   * \anchor p11_s8_1_3
   *
   * \ref express::INTEGER "8.1.3 Целочисленный тип данных"
   *
   * Областью определения типа данных \ref express::INTEGER "INTEGER" являются все целые числа. Данный тип данных
   * является конкретизацией типа данных \ref express::REAL "REAL".
   \verbatim
     Синтаксис:
     241 integer_type = INTEGER.
   \endverbatim
   * <B><I>Пример --- В данном примере целочисленный тип данных использован для представления атрибута
   * с именем</I> nodes. <I>Областью определения данного атрибута являются все целые числа без каких-либо
   * ограничений.</I></B>
   <PRE>
       ENTITY foo;
         nodes : INTEGER;
         ...
       END_ENTITY;
   </PRE>
   */
  class INTEGER : public REAL {

  private:

    /**
     * \brief Значение для числа типа INTEGER
     *
     * Целочисленное число, хранящее значение числа типа INTEGER
     */
    integer_type _i;

  protected:

    /**
     *\brief Получить принадлёжность типа данных к одной из групп
     * \return тип данных в виде элемента перечисления OBJTYPE.
     */
    virtual constexpr OBJTYPE objtype() const override;


  public:

    /**
     * \file
     * Для типа INTEGER определены следующие члены-методы (функции):<BR><BR>
     */

    /**
     *\file
     * Конструкторы (неопределённого значения, копирующий и конструктор из значения),
     * деструктор и операторы присваивания своего типа и значения.
     */

    /**
     * \brief Конструктор числа типа INTEGER по умолчанию, имеющего неопределённое
     * (<B>?</B>) значение
     */
    INTEGER();

    /**
     * \brief Копирующий конструктор числового типа INTEGER
     * \param [in] src Объект-источник --- число типа INTEGER.
     */
    INTEGER(const INTEGER& src);

    /**
     * \brief Конструктор числового типа INTEGER из значения integer_type
     * \param [in] src Источник --- числовое значение, которое будет присвоено.
     */
    INTEGER(integer_type src);

    /**
     * \brief Деструктор числового типа INTEGER --- по умолчанию
     */
    virtual ~INTEGER() = default;

    /**
     * \brief Оператор присваивания числового типа INTEGER
     * \param [in] rhs Объект-источник --- число типа INTEGER.
     *
     * При выполнении присваивания проводится проверка на самоприсваивание.
     */
    INTEGER& operator=(const INTEGER& rhs);

    /**
     * \brief Оператор присваивания значения integer_type;
     * \param [in] rhs Источник --- числовое значение, которое будет присвоено.
     */
    INTEGER& operator=(integer_type rhs);

    /**
     * \file
     * Получение значения и свойств типа, вывод значения типа в виде строки.
     */

    /**
     * \brief Преобразование числа типа INTEGER к значению типа number_type
     * \return значение числа типа INTEGER в виде типа number_type.
     */
    virtual number_type get_number_value() const override;

    /**
     * \brief Получить количество значащих цифр значения числа типа INTGER
     * \return количество значащих цифр значения числа типа INTEGER.
     */
    virtual unsigned get_number_precision() const override;

    /**
     * \brief Преобразование числа типа INTEGER к значению типа integer_type
     * \return значение числа типа INTEGER в виде типа integer_type.
     */
    virtual integer_type get_integer_value() const override;

    /**
     * \brief Вывод значения целочисленного типа INTEGER (ГОСТ Р ИСО 10303-21, 6.3.1, 10.1.1.1).
     *
     * <B>ГОСТ Р ИСО 10303-21, 6.3.1 Целое (Integer)</B>
     *
     * Целое должно быть закодировано как последовательность из одной или нескольких цифр,
     * согласно таблице 2, которой может (но необязательно) предшествовать <I>знак плюс</I> “+” или
     * <I>минус</I> “-”. Целое должно быть выражено в десятичном основании. Если целое не имеет знака,
     * его считают положительным.
     *
     * <B>ГОСТ Р ИСО 10303-21, 10.1.1.1 Тип данных \ref express::INTEGER "INTEGER" (целое)</B>
     *
     * Значения данных в EXPRESS типа \ref INTEGER отображаются в структуру обмена как целочисленный
     * тип данных. Состав целочисленного типа данных описан в 6.3.1.
     */
    virtual std::string print_value() const override;

    /**
     * \file
     * Арифметические операторы:
     *
     * * Унарный знак.
     */

    /**
     * \brief Унарный плюс числа типа INTEGER
     * \return число типа INTEGER, равное результату сложения числа типа INTGER с нулём.
     */
    INTEGER operator+() const;

    /**
     * \brief Унарный минус числа INTEGER
     * \return число типа INTEGER, равное результату вычитания числа типа INTEGER из нуля.
     */
    INTEGER operator-() const;

    /**
     * \file
     * * Сложение с числом типа INTEGER, а также со значением.
     */

    /**
     * \brief Сложение числа типа INTEGER с числом типа INTEGER
     * \param [in] rhs Число типа INTEGER, с которым складивается число типа INTEGER.
     * \return число типа INTEGER --- результат сложения числа типа INTEGER с аргументом.
     */
    INTEGER operator+(const INTEGER& rhs) const;

    /**
     * \brief Сложение числа типа INTEGER со значением типа integer_type
     * \param [in] rhs Значение типа integer_type, с которым складивается число типа INTEGER.
     * \return число типа INTEGER ---  результат сложения числа типа INTEGER с аргументом.
     */
    INTEGER operator+(integer_type rhs) const;

    /**
     * \brief Сложение числа типа INTEGER со значением типа int
     * \param [in] rhs Значение типа int, с которым складивается число типа INTEGER.
     * \return число типа INTEGER ---  результат сложения числа типа INTEGER с аргументом.
     */
    INTEGER operator+(int rhs) const;

    /**
     * \brief Сложение значения integer_type с числом типа INTEGER
     * \param [in] lhs Значение типа integer_type, первое слагаемое.
     * \param [in] rhs Число типа INTEGER, второе слагаемое.
     * \return число типа INTEGER --- результат сложения слагаемых.
     */
    friend INTEGER operator+(integer_type lhs, const INTEGER& rhs);

    /**
     * \brief Сложение значения int с числом типа INTEGER
     * \param [in] lhs Значение типа int, первое слагаемое.
     * \param [in] rhs Число типа INTEGER, второе слагаемое.
     * \return число типа INTEGER --- результат сложения слагаемых.
     */
    friend INTEGER operator+(int lhs, const INTEGER& rhs);

    /**
     * \brief Сложение значения типа real_type с числом типа INTEGER
     * \param [in] lhs Значение типа real_type, первое слагаемое.
     * \param [in] rhs Число типа INTEGER, второе слагаемое.
     * \return число типа REAL --- результат сложения слагаемых.
     */
    friend REAL operator+(real_type lhs, const INTEGER& rhs);

    /**
     * \file
     * * Вычитание числа типа INTGER, а также значения.
     */

    /**
     * \brief Вычитание из числа типа INTEGER числа типа INTEGER
     * \param [in] rhs Число типа INTEGER, которое вычитается из числа типа INTEGER.
     * \return число типа INTEGER --- результат вычитания из числа типа INTEGER аргумента.
     */
    INTEGER operator-(const INTEGER& rhs) const;

    /**
     * \brief Вычитание из числа типа INTEGER значения типа integer_type
     * \param [in] rhs Значение типа integer_type, которое вычитается из числа типа INTEGER.
     * \return число типа INTEGER --- результат вычитания из числа типа INTEGER аргумента.
     */
    INTEGER operator-(integer_type rhs) const;

    /**
     * \brief Вычитание из числа типа INTEGER значения типа int
     * \param [in] rhs Значение типа int, которое вычитается из числа типа INTEGER.
     * \return число типа INTEGER --- вычитания из числа типа INTEGER аргумента.
     */
    INTEGER operator-(int rhs) const;

    /**
     * \brief Вычитание числа типа INTEGER из значения integer_type
     * \param [in] lhs Значение типа integer_type, уменьшаемое.
     * \param [in] rhs Число типа INTEGER, вычитаемое.
     * \return число типа INTEGER --- результат вычитания вычитаемого из уменьшаемого.
     */
    friend INTEGER operator-(integer_type lhs, const INTEGER& rhs);

    /**
     * \brief Вычитание из значения int числа типа INTEGER
     * \param [in] lhs Значение типа int, уменьшаемое.
     * \param [in] rhs Число типа INTEGER, вычитаемое.
     * \return число типа INTEGER --- результат вычитания вычитаемого из уменьшаемого.
     */
    friend INTEGER operator-(int lhs, const INTEGER& rhs);

    /**
     * \brief Вычитание из значения типа real_type числа типа INTEGER
     * \param [in] lhs Значение типа real_type, уменьшаемое.
     * \param [in] rhs Число типа INTEGER, вычитаемое.
     * \return число типа INTEGER --- результат вычитания вычитаемого из уменьшаемого.
     */
    friend REAL operator-(real_type lhs, const INTEGER& rhs);

    /**
     * \file
     * * Умножение на число типа INTEGER, а также на значение.
     */

    /**
     * \brief Умножение числа типа INTEGER на число типа INTEGER
     * \param [in] rhs Число типа INTEGER, на которое умножается число типа INTEGER.
     * \return число типа INTEGER --- результат умножения числа типа INTEGER на аргумент.
     */
    INTEGER operator*(const INTEGER& rhs) const;

    /**
     * \brief Умножение числа типа INTEGER на значение типа integer_type
     * \param [in] rhs Значение типа integer_type, на которое умножается число типа INTEGER.
     * \return число типа INTEGER ---  результат умножения числа типа INTEGER на аргумент.
     */
    INTEGER operator*(integer_type rhs) const;

    /**
     * \brief Умножение числа типа INTEGER на значение типа int
     * \param [in] rhs Значение типа int, на которое умножается число типа INTEGER.
     * \return число типа INTEGER ---  результат умножения числа типа INTEGER на аргумент.
     */
    INTEGER operator*(int rhs) const;

    /**
     * \brief Умножение значения типа integer_type на число типа INTEGER
     * \param [in] lhs Значение типа integer_type, первый множитель.
     * \param [in] rhs Число типа INTEGER, второй множитель.
     * \return число типа INTEGER --- результат умножения множителей.
     */
    friend INTEGER operator*(integer_type lhs, const INTEGER& rhs);

    /**
     * \brief Умножение значения типа int на число типа INTEGER
     * \param [in] lhs Значение типа int, первый множитель.
     * \param [in] rhs Число типа INTEGER, второй множитель.
     * \return число типа INTEGER --- результат умножения множителей.
     */
    friend INTEGER operator*(int lhs, const INTEGER& rhs);

    /**
     * \brief Умножение значения типа real_type на число типа INTEGER
     * \param [in] lhs Значение типа real_type, первый множитель.
     * \param [in] rhs Число типа INTEGER, второй множитель.
     * \return число типа REAL --- результат умножения множителей.
     */
    friend REAL operator*(real_type lhs, const INTEGER& rhs);

    /**
     * \file
     * * Деление на число типа INTEGER, а также на значение.
     */

    /**
     * \brief Деление числа типа INTEGER на число типа INTEGER
     * \param [in] rhs Число типа INTEGER, на которое делится число типа INTEGER.
     * \return число типа REAL --- результат деления числа типа INTEGER на аргумент.
     */
    REAL operator/(const INTEGER& rhs) const;

    /**
     * \brief Деление числа типа INTEGER на значение типа integer_type
     * \param [in] rhs Значение типа integer_type, на которое делится число типа INTEGER.
     * \return число типа REAL ---  результат деления числа типа INTEGER на аргумент.
     */
    REAL operator/(integer_type rhs) const;

    /**
     * \brief Деление числа типа INTEGER на значение типа int
     * \param [in] rhs Значение типа int, на которое делится число типа INTEGER.
     * \return число типа REAL ---  результат деления числа типа INTEGER на аргумент.
     */
    REAL operator/(int rhs) const;

    /**
     * \brief Деление значения типа integer_type на число типа INTEGER
     * \param [in] lhs Значение типа integer_type, делимое.
     * \param [in] rhs Число типа INTEGER, делитель.
     * \return число типа REAL --- результат деления делимого на делитель.
     */
    friend REAL operator/(integer_type lhs, const INTEGER& rhs);

    /**
     * \brief Деление значения типа int на число типа INTEGER
     * \param [in] lhs Значение типа int, делимое.
     * \param [in] rhs Число типа INTEGER, делитель.
     * \return число типа REAL --- результат деления делимого на делитель.
     */
    friend REAL operator/(int lhs, const INTEGER& rhs);

    /**
     * \brief Деление значения типа real_type на число типа INTEGER
     * \param [in] lhs Значение типа real_type, делимое.
     * \param [in] rhs Число типа INTEGER, делитель.
     * \return число типа REAL --- результат деления делимого на делитель.
     */
    friend REAL operator/(real_type lhs, const INTEGER& rhs);

    /**
     * \file
     * * Возведение в степень числа типа INTEGER, а также значения
     * (используется оператор '<<', соответствующий оператору '**' в языке EXPRESS).
     */

    /**
     * \brief Возведение числа типа INTEGER в степень числа типа INTEGER
     * \param [in] rhs Число типа INTEGER, степень.
     * \return результат возведения показателя в степень.
     */
    INTEGER operator<<(const INTEGER& rhs) const;

    /**
     * \brief Возведение числа типа INTEGER в степень значения integer_type
     * \param [in] rhs Значение типа integer_type, степень.
     * \return результат возведения показателя в степень.
     */
    INTEGER operator<<(integer_type rhs) const;

    /**
     * \brief Возведение числа типа INTEGER в степень значения int
     * \param [in] rhs Значение типа int, степень.
     * \return результат возведения показателя в степень.
     */
    INTEGER operator<<(int rhs) const;

    /**
     * \brief Возведение числа типа INTEGER в степень значения real_type
     * \param [in] rhs Значение типа real_type, степень.
     * \return результат возведения показателя в степень.
     */
    REAL operator<<(real_type rhs) const;

    /**
     * \brief Возведение значения типа integer_type в степень числа типа INTEGER
     * \param [in] lhs Значение типа integer_type, показатель.
     * \param [in] rhs Число типа INTEGER, степень.
     * \return результат возведения показателя в степень.
     */
    friend INTEGER operator<<(integer_type lhs, const INTEGER& rhs);

    /**
     * \brief Возведение значения типа int в степень числа типа INTEGER
     * \param [in] lhs Значение типа int, показатель.
     * \param [in] rhs Число типа INTEGER, степень.
     * \return результат возведения показателя в степень.
     */
    friend INTEGER operator<<(int lhs, const INTEGER& rhs);

    /**
     * \brief Возведение значения real_type в степень числа типа INTEGER 
     * \param [in] lhs Значение типа real_type, показатель.
     * \param [in] rhs Число типа INTEGER, степень.
     * \return результат возведения показателя в степень.
     */
    friend REAL operator<<(real_type lhs, const INTEGER& rhs);

    /**
     * \file
     * * Проверки равенства экземпляров ':=:' и отношений значений.
     */

    /**
     * \brief Проверка отношения значений типа integer_type
     * \param [in] lhs Значение типа integer_type.
     * \param [in] rhs Значение типа integer_type.
     * \return 0, если lhs == rhs, 1, если lhs > rhs, -1, если lhs < rhs.
     */
     static int compare(integer_type lhs, integer_type rhs);
  };
}