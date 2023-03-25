/**
 * \file
 * \brief Файл с описанием простого числового типа данных NUMBER языка EXPRESS
 * (ГОСТ Р ИСО 10303-11-2009, \ref p11_s8_1 "8.1.1"; ГОСТ Р ИСО 10303-21, 6.3)
 */

namespace express {

  /**
   * \brief Преобразование типа real_type в integer_type
   * \param rhs [in] Значение типа real_type.
   * \return значение типа integer_type.
   */
  integer_type real_to_integer(real_type rhs);

  /**
   * \brief Преобразование типа real_type в int
   * \param rhs [in] Значение типа real_type.
   * \return значение типа int.
   */
  int real_to_int(real_type rhs);

  /**
   * \brief Преобразование типа integer_type в real_type
   * \param rhs [in] Значение типа integer_type.
   * \return значение типа real_type.
   */
  real_type integer_to_real(integer_type rhs);

  /** 
   * \brief Простой тип \ref express::NUMBER "NUMBER" --- Числовой тип данных (ГОСТ Р ИСО 10303-11-2009, 8.1.1)
   *
   * \anchor p11_s8_1_1
   *
   * \ref express::NUMBER "8.1.1 Числовой тип данных"
   *
   * Областью определения типа данных \ref express::NUMBER "NUMBER" являются все числовые значения в языке EXPRESS.
   * Числовой тип данных должен использоваться, когда не важно более конкретное представление чисел.
   \verbatim
     Синтаксис:
      261 number_type = NUMBER .
   \endverbatim
   * <B><I>Пример --- Поскольку контекст параметра</I> size <I>(размер) может быть неизвестен, то и не
   * известно как его правильно представить. Например, численность толпы на футбольном матче
   * может выражаться целым числом (тип данных</I> \ref express::INTEGER "INTEGER"<I>), а площадь поля -
   * действительным (тип данных</I> \ref express::REAL "REAL"<I>).</I>
   <PRE>
       size : NUMBER ;
   </PRE> </B>
   * <SMALL>Примечание --- В последующих редакциях настоящего стандарта могут быть введены новые
   * конкретизации типа данных \ref express::NUMBER "NUMBER", например, комплексные числа.</SMALL>
   */
  class NUMBER : public SIMPLE {

  private:

    /**
     * \brief Значение для числа типа NUMBER
     *
     * Число с плавающей запятой, хранящее значение числа типа NUMBER
     */
    number_type _n;

  protected:

    /**
     *\brief Получить принадлёжность типа данных к одной из групп
     * \return тип данных в виде элемента перечисления OBJTYPE.
     */
    virtual GENERIC::OBJTYPE objtype() const override;

  public:


    /**
     * \file
     * Для типа NUMBER определены следующие члены-методы (функции):<BR><BR>
     */

    /**
     * \file
     * Конструкторы (неопределённого значения, копирующий (из базового и дочерних
     * типов) и конструктор из значения), деструктор и оператор присваивания
     * своего типа.
     */

    /**
     * \brief Конструктор числа типа NUMBER по умолчанию, имеющего неопределённое
     * (<B>?</B>) значение
     */
    NUMBER();

    /**
     * \brief Конструктор числового типа NUMBER из числового типа NUMBER, REAL или INTEGER,
     * переданного через ссылку на тип NUMBER
     * \param [in] src Объект-источник --- число типа NUMBER, REAL или INTEGER, переданное
     * через ссылку на тип NUMBER.
     */
    NUMBER(const NUMBER& src);

    /**
     * \brief Конструктор числового типа NUMBER из значения real_type
     * \param [in] src Источник --- числовое значение, которое будет присвоено.
     */
    NUMBER(real_type src);

    /**
     * \brief Деструктор числового типа NUMBER --- по умолчанию
     */
    virtual ~NUMBER() = default;

    /**
     * \brief Оператор присваивания числового типа NUMBER, REAL или INTEGER, переданного
     * через ссылку на тип NUMBER
     * \param [in] rhs Объект-источник --- число типа NUMBER, REAL или INTEGER, переданное
     * через ссылку на тип NUMBER.
     *
     * При выполнении присваивания проводится проверка на самоприсваивание.
     */
    NUMBER& operator=(const NUMBER& rhs);

    /**
     * \file
     * Получение значения и свойств типа, вывод значения типа в виде строки.
     */

    /**
     * \brief Преобразование числа типа NUMBER к значению типа number_type
     * \return значение числа типа NUMBER в виде типа number_type.
     */
    virtual number_type get_number_value() const;

    /**
     * \brief Преобразование целочисленного дочернего типа к значению типа integer_type
     * \return значение числа целочисленного типа в виде типа integer_type.
     */
    virtual integer_type get_integer_value() const;

    /**
     * \brief Получить количество значащих цифр мантиссы значения числа типа NUMBER
     * \return количество значащих цифр мантиссы значения числа типа NUMBER.
     */
    virtual unsigned get_number_precision() const;

    /**
     * \brief Проверить совместимость числового типа с некоторым типом.
     *
     * \param [in] rhs Тип, с которым будет произведено сравнение, переданный в виде ссылки
     * на тип GENERIC.
     * \return результат сравнения типов в виде перечисления COMPAT.
     */
    virtual COMPAT check_compatibility(const GENERIC& rhs) const override;

    /**
     * \brief Вывод значения числового типа NUMBER (ГОСТ Р ИСО 10303-21, 10.1.1.7).
     *
     * <B>ГОСТ Р ИСО 10303-21, 10.1.1.7 Тип данных \ref express::NUMBER "NUMBER" (числовой)</B>
     *
     * Значения данных в EXPRESS типа \ref express::NUMBER "NUMBER" должны быть отображены в структуру обмена
     * как вещественный тип данных. Формирование вещественного типа данных --- по 6.3.2:
     *
     * <B>ГОСТ Р ИСО 10303-21, 6.3.2 Вещественное (\ref express::REAL "REAL")</B>
     *
     * Вещественное должно быть закодировано, как указано в таблице 2:
     \verbatim
       REAL = [SIGN] DIGIT { DIGIT } “.” { DIGIT } [ “E” [SIGN] DIGIT { DIGIT } ] .
     \endverbatim
     * Код должен состоять из десятичной мантиссы, за которой (необязательно) следует десятичный
     * показатель степени. Десятичная мантисса состоит в порядке следования из необязательного
     * <I>знака плюс</I> “+” или <I>минус</I> “--”, последовательности из одной или более цифр,
     * <I>точки</I> “.”, последовательности из нуля или нескольких цифр. Десятичный показатель
     * степени состоит из <I>прописной буквы E</I>, за которой следует необязательный <I>знак
     * плюс</I> “+” или <I>минус</I> “--” с одной или несколькими цифрами.
     *
     * <B>ГОСТ Р ИСО 10303-21, 10.1.1.5 Тип данных \ref express::REAL "REAL" (вещественный)</B>
     *
     * Значения данных в EXPRESS типа \ref express::REAL "REAL" должны быть отображены в структуру обмена как
     * вещественный тип данных. В 6.3.2 описано содержание вещественного типа данных.
     *
     * \return строку, содержащую отображение числового типа для структуры обмена.
     *
     */
    virtual std::string print_value() const override;

    /**
     * \file
     * Арифметические операторы:
     *
     * * Унарный знак.
     */

    /**
     * \brief Унарный плюс числа типа NUMBER
     * \return число типа REAL, равное результату сложения числа типа NUMBER с нулём.
     */
    REAL operator+() const;

    /**
     * \brief Унарный минус числа типа NUMBER
     * \return число типа REAL, равное результату вычитания числа типа NUMBER из нуля.
     */
    REAL operator-() const;

    /**
     * \file
     * * Сложение с числом типа NUMBER (и дочерними типами), а также со значением.
     */

    /**
     * \brief Сложение числа типа NUMBER с числом типа NUMBER, REAL или INTEGER, переданного
     * через ссылку на тип NUMBER
     * \param [in] rhs Число типа NUMBER, REAL или INTEGER, переданное
     * через ссылку на тип NUMBER, с которым складивается число типа NUMBER.
     * \return число типа REAL --- результат сложения числа типа NUMBER с аргументом.
     */
    REAL operator+(const NUMBER& rhs) const;

    /**
     * \brief Сложение числа типа NUMBER со значением типа real_type
     * \param [in] rhs Значение типа real_type, с которым складывается число типа NUMBER.
     * \return число типа REAL --- результат сложения числа типа NUMBER с аргументом.
     */
    REAL operator+(real_type rhs) const;

    /**
     * \brief Сложение числа типа REAL с числом типа NUMBER
     * \param [in] lhs Число типа REAL или INTEGER, переданное через ссылку на тип
     * REAL --- первое слагаемое.
     * \param [in] rhs Число типа NUMBER, REAL или INTEGER, переданное
     * через ссылку на тип NUMBER --- второе слагаемое.
     * \return число типа REAL --- результат сложения слагаемых.
     */
    friend REAL operator+(const REAL& lhs, const NUMBER& rhs);

    /**
     * \file
     * * Вычитание числа типа NUMBER (и дочерних типов), а также значения.
     */

    /**
     * \brief Вычитание из числа типа NUMBER числа типа NUMBER, REAL или INTEGER, переданного
     * через ссылку на тип NUMBER
     * \param [in] rhs Число типа NUMBER, REAL или INTEGER, переданное
     * через ссылку на тип NUMBER, которое вычитается из числа типа NUMBER.
     * \return число типа REAL --- результат вычитания из числа типа NUMBER аргумента.
     */
    REAL operator-(const NUMBER& rhs) const;

    /**
     * \brief Вычитание из числа типа NUMBER значения типа real_type
     * \param [in] rhs Значение типа real_type, которое вычитается из числа типа NUMBER.
     * \return число типа REAL --- результат вычитания из числа типа NUMBER с аргумента.
     */
    REAL operator-(real_type rhs) const;

    /**
     * \brief Вычитание из числа типа REAL числа типа NUMBER
     * \param [in] lhs Число типа REAL или INTEGER, переданное через ссылку на тип
     * REAL --- уменьшаемое.
     * \param [in] rhs Число типа NUMBER, REAL или INTEGER, переданное
     * через ссылку на тип NUMBER --- вычитаемое.
     * \return число типа REAL --- результат вычитания вычитаемого из уменьшаемого.
     */
    friend REAL operator-(const REAL& lhs, const NUMBER& rhs);

    /**
     * \file
     * * Умножение на число типа NUMBER (и дочерние типы), а также значения.
     */

    /**
     * \brief Умножение числа типа NUMBER на число типа NUMBER, REAL или INTEGER, переданного
     * через ссылку на тип NUMBER
     * \param [in] rhs Число типа NUMBER, REAL или INTEGER, переданное
     * через ссылку на тип NUMBER, на которое умножается число типа NUMBER.
     * \return число типа REAL --- результат умножения числа типа NUMBER на аргумент.
     */
    REAL operator*(const NUMBER& rhs) const;

    /**
     * \brief Умножение числа типа NUMBER на значение типа real_type
     * \param [in] rhs Значение типа real_type, на котрое умножается число типа NUMBER.
     * \return число типа REAL --- результат умножения числа типа NUMBER на аргумент.
     */
    REAL operator*(real_type rhs) const;

    /**
     * \brief Умножение числа типа REAL на число типа NUMBER
     * \param [in] lhs Число типа REAL или INTEGER, переданное через ссылку на тип
     * REAL --- первый множитель.
     * \param [in] rhs Число типа NUMBER, REAL или INTEGER, переданное
     * через ссылку на тип NUMBER --- второй множитель.
     * \return число типа REAL --- результат умножения множителей.
     */
    friend REAL operator*(const REAL& lhs, const NUMBER& rhs);

    /**
     * \file
     * * Деление на число типа NUMBER (и дочерние типы), а также значения.
     */

    /**
     * \brief Деление числа типа NUMBER на число типа NUMBER, REAL или INTEGER, переданного
     * через ссылку на тип NUMBER
     * \param [in] rhs Число типа NUMBER, REAL или INTEGER, переданное
     * через ссылку на тип NUMBER, на которое делится число типа NUMBER.
     * \return число типа REAL --- результат деления числа типа NUMBER на аргумент.
     */
    REAL operator/(const NUMBER& rhs) const;

    /**
     * \brief Деление числа типа NUMBER на значение типа real_type
     * \param [in] rhs Значение типа real_type, на котрое делится число типа NUMBER.
     * \return число типа REAL --- результат деления числа типа NUMBER на аргумент.
     */
    REAL operator/(real_type rhs) const;

    /**
     * \brief Деление числа типа REAL на число типа NUMBER
     * \param [in] lhs Число типа REAL или INTEGER, переданное через ссылку на тип
     * REAL --- делимое.
     * \param [in] rhs Число типа NUMBER, REAL или INTEGER, переданное
     * через ссылку на тип NUMBER --- делитель.
     * \return число типа REAL --- результат деления делимого на делитель.
     */
    friend REAL operator/(const REAL& lhs, const NUMBER& rhs);

    /**
     * \file
     * * Возведение в степень числа типа NUMBER (и дочерних типов), а также значения
     * (используется оператор '<<', соответствующий оператору '**' в языке EXPRESS).
     */

    /**
     * \brief Возведение числа типа NUMBER в степень числа типа NUMBER
     * \param [in] rhs Число типа NUMBER, REAL или INTEGER, переданное
     * через ссылку на тип NUMBER --- степень.
     * \return число типа REAL --- результат возведения числа типа NUMBER в степень.
     */
    REAL operator<<(const NUMBER& rhs) const;

    /**
     * \brief Возведение числа типа NUMBER в степень значения real_type
     * \param [in] rhs Значение типа real_type --- степень.
     * \return число типа REAL --- результат возведения числа типа NUMBER в степень.
     */
    REAL operator<<(real_type rhs) const;

    /**
     * \brief Возведение значения типа real_type в степень числа типа NUMBER
     * \param [in] lhs Значение типа real_type, показатель.
     * \param [in] rhs Число типа NUMBER, степень.
     * \return число типа REAL --- результат возведения показателя в степень.
     */
    friend REAL operator<<(real_type lhs, const NUMBER& rhs);

    /**
     * \brief Возведение значения числа типа INTEGER в степень числа типа NUMBER
     * \param [in] lhs Число типа INTEGER, показатель.
     * \param [in] rhs Число типа NUMBER, степень.
     * \return число типа REAL --- результат возведения показателя в степень.
     */
    friend REAL operator<<(const INTEGER& lhs, const NUMBER& rhs);

    /**
     * \file
     * * Целочисленное деление на число типа NUMBER (и дочерние типы), а также на значение.
     */

    /**
     * \brief Целочисленное деление DIV числа типа NUMBER на число типа NUMBER, REAL или INTEGER,
     * переданного через ссылку на тип NUMBER
     * \param [in] rhs Число типа NUMBER, REAL или INTEGER, переданное
     * через ссылку на тип NUMBER, на которое делится число типа NUMBER.
     * \return число типа INTEGER --- результат целочисленного деления числа типа NUMBER на аргумент.
     */
    INTEGER operator>>(const NUMBER& rhs) const;

    /**
     * \brief Целочисленное деление DIV числа типа NUMBER на значение типа real_type
     * \param [in] rhs Значение типа real_type, на котрое делится число типа NUMBER.
     * \return число типа INTEGER --- результат целочисленного деления числа типа NUMBER на аргумент.
     */
    INTEGER operator>>(real_type rhs) const;

    /**
     * \brief Целочисленное деление DIV числа типа REAL на число типа NUMBER
     * \param [in] lhs Число типа REAL или INTEGER, переданное через ссылку на тип
     * REAL --- делимое.
     * \param [in] rhs Число типа NUMBER, REAL или INTEGER, переданное
     * через ссылку на тип NUMBER --- делитель.
     * \return число типа INTEGER --- результат целочисленного деления делимого на делитель.
     */
    friend INTEGER operator>>(const REAL& lhs, const NUMBER& rhs);

    /**
     * \file
     * * Остаток от деления на число типа NUMBER (и дочерние типы), а также на значение.
     */

    /**
     * \brief Остаток от деления по модулю MOD числа типа NUMBER на число типа NUMBER,
     * REAL или INTEGER, переданного через ссылку на тип NUMBER
     * \param [in] rhs Число типа NUMBER, REAL или INTEGER, переданное
     * через ссылку на тип NUMBER, на которое делится число типа NUMBER.
     * \return число типа INTEGER --- остаток от деления числа типа NUMBER на аргумент.
     */
    INTEGER operator%(const NUMBER& rhs) const;

    /**
     * \brief Остаток от деления по модулю числа типа NUMBER на значение типа real_type
     * \param [in] rhs Значение типа real_type, на котрое делится число типа NUMBER.
     * \return число типа INTEGER --- остаток от деления числа типа NUMBER на аргумент.
     */
    INTEGER operator%(real_type rhs) const;

    /**
     * \brief Остаток от деления по модулю MOD числа типа REAL на число типа NUMBER
     * \param [in] lhs Число типа REAL или INTEGER, переданное через ссылку на тип
     * REAL --- делимое.
     * \param [in] rhs Число типа NUMBER, REAL или INTEGER, переданное
     * через ссылку на тип NUMBER --- делитель.
     * \return число типа INTEGER --- остаток от деления делимого на делитель.
     */
    friend INTEGER operator%(const REAL& lhs, const NUMBER& rhs);

    /**
     * \file
     * * Проверка равенства значений '=' с числом типа NUMBER (и дочерними типами) и со значением.
     */

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
     * \brief Проверка равенства значений '=' числа типа NUMBER (или дочерних типов)
     * с числом типа NUMBER, REAL или INTEGER, переданного через ссылку на тип NUMBER
     * \param [in] rhs Число типа NUMBER, REAL или INTEGER, переданное
     * через ссылку на тип NUMBER.
     * \return Логическое выражение типа LOGICAL --- результат сравнения значений числа и rhs.
     */
    LOGICAL is_number_value_equal(const NUMBER& rhs) const;


    /**
     * \brief Проверка равенства значений '=' числа типа NUMBER (или дочерних типов) со
     * значением типа real_type
     * \param [in] lhs Число типа NUMBER, REAL или INTEGER, переданное
     * через ссылку на тип NUMBER.
     * \param [in] rhs Значение типа real_type.
     * \return Логическое выражение типа LOGICAL --- результат сравнения значений lhs и rhs.
     */
    friend LOGICAL operator==(const NUMBER& lhs, real_type rhs);

    /**
     * \file
     * * Проверка неравенства значений '<>' с числом типа NUMBER (и дочерними типами) и со значением.
     */

    /**
     * \brief Проверка неравенства значений '<>' числа типа NUMBER со значением real_type
     * \param [in] lhs Число типа NUMBER, REAL или INTEGER, переданное
     * через ссылку на тип NUMBER.
     * \param [in] rhs Значение типа real_type.
     * \return Логическое выражение типа LOGICAL --- результат сравнения значений lhs и rhs.
     */
    friend LOGICAL operator!=(const NUMBER& lhs, real_type rhs);

    /**
     * \brief Проверка неравенства значений '<>' значения типа real_type с числом типа NUMBER, REAL
     * или INTEGER, переданного через ссылку на тип NUMBER
     * \param [in] lhs Значение типа real_type.
     * \param [in] rhs Число типа NUMBER, REAL или INTEGER, переданное
     * через ссылку на тип NUMBER.
     * \return Логическое выражение типа LOGICAL --- результат сравнения значений значения x
     * и числа y.
     */
    friend LOGICAL operator!=(real_type lhs, const NUMBER& rhs);

    /**
     * \file
     * * Проверка отношения значений '>' с числом типа NUMBER (и дочерними типами) и со значением.
     */

    /**
     * \brief Проверка отношения значений '>' числа типа NUMBER (или дочерних типов)
     * с числом типа NUMBER, REAL или INTEGER, переданного через ссылку на тип NUMBER
     * \param [in] rhs Число типа NUMBER, REAL или INTEGER, переданное
     * через ссылку на тип NUMBER.
     * \return Логическое выражение типа LOGICAL --- результат сравнения значений данного
     * числа и rhs.
     */
    LOGICAL operator>(const NUMBER& rhs) const;

    /**
     * \brief Проверка отношения значений '>' числа типа NUMBER (или дочерних типов) со
     * значением типа real_type
     * \param [in] rhs Значение типа real_type.
     * \return Логическое выражение типа LOGICAL --- результат сравнения значений данного
     * числа и rhs.
     */
    LOGICAL operator>(real_type rhs) const;

    /**
     * \brief Проверка отношения значений '>' значения real_type с числом типа NUMBER, REAL
     * или INTEGER, переданного через ссылку на тип NUMBER
     * \param [in] lhs Значение типа real_type.
     * \param [in] rhs Число типа NUMBER, REAL или INTEGER, переданное
     * через ссылку на тип NUMBER.
     * \return Логическое выражение типа LOGICAL --- результат сравнения значений значения x
     * и числа y.
     */
    friend LOGICAL operator>(real_type lhs, const NUMBER& rhs);

    /**
     * \file
     * * Проверка отношения значений '>=' с числом типа NUMBER (и дочерними типами) и со значением.
     */

    /**
     * \brief Проверка отношения значений '>=' числа типа NUMBER (или дочерних типов)
     * с числом типа NUMBER, REAL или INTEGER, переданного через ссылку на тип NUMBER
     * \param [in] rhs Число типа NUMBER, REAL или INTEGER, переданное
     * через ссылку на тип NUMBER.
     * \return Логическое выражение типа LOGICAL --- результат сравнения значений данного
     * числа и rhs.
     */
    LOGICAL operator>=(const NUMBER& rhs) const;

    /**
     * \brief Проверка отношения значений '>=' числа типа NUMBER (или дочерних типов) со
     * значением типа real_type
     * \param [in] rhs Значение типа real_type.
     * \return Логическое выражение типа LOGICAL --- результат сравнения значений данного
     * числа и rhs.
     */
    LOGICAL operator>=(real_type rhs) const;

    /**
     * \brief Проверка отношения значений '>=' значения real_type с числом типа NUMBER, REAL
     * или INTEGER, переданного через ссылку на тип NUMBER
     * \param [in] lhs Значение типа real_type.
     * \param [in] rhs Число типа NUMBER, REAL или INTEGER, переданное
     * через ссылку на тип NUMBER.
     * \return Логическое выражение типа LOGICAL --- результат сравнения значений значения x
     * и числа y.
     */
    friend LOGICAL operator>=(real_type lhs, const NUMBER& rhs);

    /**
     * \file
     * * Проверка отношения значений '<=' с числом типа NUMBER (и дочерними типами) и со значением.
     */

    /**
     * \brief Проверка отношения значений '<' числа типа NUMBER (или дочерних типов)
     * с числом типа NUMBER, REAL или INTEGER, переданного через ссылку на тип NUMBER
     * \param [in] rhs Число типа NUMBER, REAL или INTEGER, переданное
     * через ссылку на тип NUMBER.
     * \return Логическое выражение типа LOGICAL --- результат сравнения значений данного
     * числа и rhs.
     */
    LOGICAL operator<(const NUMBER& rhs) const;

    /**
     * \brief Проверка отношения значений '<' числа типа NUMBER (или дочерних типов) со
     * значением типа real_type
     * \param [in] rhs Значение типа real_type.
     * \return Логическое выражение типа LOGICAL --- результат сравнения значений данного
     * числа и rhs.
     */
    LOGICAL operator<(real_type rhs) const;

    /**
     * \brief Проверка отношения значений '<' значения real_type с числом типа NUMBER, REAL
     * или INTEGER, переданного через ссылку на тип NUMBER
     * \param [in] lhs Значение типа real_type.
     * \param [in] rhs Число типа NUMBER, REAL или INTEGER, переданное
     * через ссылку на тип NUMBER.
     * \return Логическое выражение типа LOGICAL --- результат сравнения значений значения x
     * и числа y.
     */
    friend LOGICAL operator<(real_type lhs, const NUMBER& rhs);

    /**
     * \file
     * * Проверка отношения значений '<=' с числом типа NUMBER (и дочерними типами) и со значением.
     */

    /**
     * \brief Проверка отношения значений '<=' числа типа NUMBER (или дочерних типов)
     * с числом типа NUMBER, REAL или INTEGER, переданного через ссылку на тип NUMBER
     * \param [in] rhs Число типа NUMBER, REAL или INTEGER, переданное
     * через ссылку на тип NUMBER.
     * \return Логическое выражение типа LOGICAL --- результат сравнения значений данного
     * числа и rhs.
     */
    LOGICAL operator<=(const NUMBER& rhs) const;

    /**
     * \brief Проверка отношения значений '<=' числа типа NUMBER (или дочерних типов) со
     * значением типа real_type
     * \param [in] rhs Значение типа real_type.
     * \return Логическое выражение типа LOGICAL --- результат сравнения значений данного
     * числа и rhs.
     */
    LOGICAL operator<=(real_type rhs) const;

    /**
     * \brief Проверка отношения значений '<=' значения real_type с числом типа NUMBER, REAL
     * или INTEGER, переданного через ссылку на тип NUMBER
     * \param [in] lhs Значение типа real_type.
     * \param [in] rhs Число типа NUMBER, REAL или INTEGER, переданное
     * через ссылку на тип NUMBER.
     * \return Логическое выражение типа LOGICAL --- результат сравнения значений значения x
     * и числа y.
     */
    friend LOGICAL operator<=(real_type lhs, const NUMBER& rhs);
  };

  /**
   * \brief Проверка равенства значений '=' значения real_type с числом типа NUMBER, REAL
   * или INTEGER, переданного через ссылку на тип NUMBER
   * \param [in] lhs Значение типа real_type.
   * \param [in] rhs Число типа NUMBER, REAL или INTEGER, переданное
   * через ссылку на тип NUMBER.
   * \return Логическое выражение типа LOGICAL --- результат сравнения значений числа x
   * и числа y.
   */
  LOGICAL operator==(real_type lhs, const NUMBER& rhs);

}