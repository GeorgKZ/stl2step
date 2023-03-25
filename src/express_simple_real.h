/**
 * \file
 * \brief Файл с описанием простого действительного типа данных REAL языка EXPRESS
 * (ГОСТ Р ИСО 10303-11-2009, \ref p11_s8_1_2 "8.1.2"; ГОСТ Р ИСО 10303-21, 6.3)
 */

namespace express {

  /** \brief Вспомогательный класс для указания точночти */
  class PREC {

  private:

    unsigned precision_spec;

  public:

    explicit PREC(unsigned precision) : precision_spec(precision) {
    }

    operator unsigned () const {
      return precision_spec;
    }
  };

  /** 
   * \brief Простой тип \ref express::REAL "REAL" --- Действительное число (ГОСТ Р ИСО 10303-11-2009, 8.1.2)
   *
   * \anchor p11_s8_1_2
   *
   * \ref express::REAL "8.1.2 Действительный тип данных"
   *
   * Областью определения типа данных \ref express::REAL "REAL" являются все рациональные, иррациональные и
   * экспоненциально представленные числа. Данный тип данных является конкретизацией
   * типа данных \ref express::NUMBER "NUMBER".
   \verbatim
     Синтаксис:
      278 real_type = REAL [ '(' precision_spec ')' ] .
      268 precision_spec = numeric_expression .
   \endverbatim
   * Рациональные и иррациональные числа имеют неограниченное разрешение и являются точными.
   * Числа в экспоненциальной форме представляют величины, известные лишь с определенной точностью.
   * Объект <B>precision_spec</B> выражается в терминах значащих цифр.
   *
   * Действительное число представляется мантиссой и необязательным показателем степени. Число
   * цифр, составляющих мантиссу после удаления всех стоящих впереди нулей, является числом
   * значащих цифр. Известная точность значения определяется числом первых цифр, необходимых для
   * конкретного приложения.
   *
   * Правила и ограничения:
   *
   * a) Объект <B>precision_spec</B> задает необходимое минимальное число цифр разрешения. Значением
   * соответствующего этому объекту выражения должно быть положительное целое число.
   *
   * b) Если спецификация разрешения не задана, то точность действительного числа не ограничена.
   */
  class REAL : public NUMBER {

  private:

    /**
     * \brief Значение типа REAL --- число с плавающей запятой
     */
    real_type _r;

    /**
     * \brief Точность: число значащих цифр мантиссы
     *
     * Точность используется при выполнении операций присвоения значения переменной типа
     * REAL --- цифры, лежащие за пределами значащих цифр мантиссы, игнорируются. При
     * выполнении операций сравнения сравниваются только значащие цифры мантиссы (блоее
     * коротная мантисса дополняется нулями).
     */
    unsigned precision_spec = precision_max;

  protected:

    /** 
     *\brief Получить принадлёжность типа данных к одной из групп
     * \return тип данных в виде элемента перечисления OBJTYPE.
     */
    virtual GENERIC::OBJTYPE objtype() const override;

  public:

    /**
     * \file
     * Для типа REAL определены следующие члены-методы (функции):<BR><BR>
     */

    /**
     * \file
     * Функции округления и сравнения действительных чисел.
     */

    /**
     * \brief Алгоритм округления числа, заданного мантиссой m согласно точности precision (ГОСТ Р ИСО 10303-11-2009, 12.1)
     * \param [in,out] mantissa Мантисса числа (в виде массива цифр). После округления имеет длину precision.
     * \param [in] precision Точность, с которой будет выполнено округление (количество цифр мантиссы).
     * Специальное нулевое значение приводит к округлению до нуля или единицы разряда, стоящего слева от
     * старшего разраяда мантиссы.
     * \param [in] sign Знак числа (1,-1,0).
     * \return true при ненулевом округлении в результате нулевого значения точности, false в других случаях.
     */
    static bool round_m(std::vector<unsigned>& mantissa, unsigned precision, int sign);

    /**
     * \brief Округление числа rhs согласно точности precision (ГОСТ Р ИСО 10303-11-2009, 12.1)
     *
     * Кроме выполнения собственно округления, эта функция может использоваться для получения
     * значения округлённой мантиссы, показателя степени и знака действительного числа.
     *
     * \param [in] src Округляемое действительное число.
     * \param [in] precision Точность, с которой будет выполнено округление (количество цифр
     * мантиссы). Специальное значение точности, равное нулю, приводит к округлению
     * разряда, стоящего слева от старшего разряда мантиссы, до нуля или единицы, и именно этот
     * единственный разряд возвращается в качестве значения мантиссы.
     * \param [out] r_mant Указатель на вектор, который будет заполнен цифрами мантиссы
     * округлённого числа (precision цифр) или nullptr.
     * \param [out] r_exp Указатель на int, которому будет присвоено значение показателя степени
     * округлённого числа или nullptr.
     * \param [out] r_sign Указатель на int, которому будет присвоено значение знака округлённого
     * числа (в форме 1, -1 ил 0) или nullptr.
     * \return действительное число --- результат округления.
     */
    static real_type round(real_type src, unsigned precision, std::vector<unsigned>* r_mant = nullptr, int* r_exp = nullptr, int* r_sign = nullptr);

    /**
     * \brief Сравнение двух значений типа real_type с учётом точности представления
     * \param x [in] Первое значение типа real_type.
     * \param precision_x [in] Количество значащих цифр мантиссы первого значения.
     * \param y [in] Второе значение типа real_type.
     * \param precision_y [in] Количество значащих цифр мантиссы второго значения.
     * \return 1, если первое значение больше второго, -1, если первое значение меньше второго,
     * и 0, если первое и второе значения равны (с учётом точности представления).
     *
     * Выполняется сравнение знака, показателя десятичной степени и значащих цифр мантиссы
     * (их количество определяется точностью).
     */
    static int compare(real_type x, unsigned precision_x, real_type y, unsigned precision_y);

    /**
     * \brief Число значащих цифр мантиссы, обеспеченные выбором типа, используемого в качестве real_type
     *
     * Для типа double, например, гарантируется точность, соответствующая 15 цифрам мантиссы.
     * Один десятичный разряд зарезервирован для возможности округления при использовании
     * неограниченной, то есть максимально возможной точности.
     */
    constexpr static unsigned precision_max = std::numeric_limits<real_type>::digits10 - 1;

    /**
     * \file
     * Конструкторы (неопределённого значения, копирующий (из базового и дочерних
     * типов) и конструктор из значения), деструктор и оператор присваивания.
     */

    /**
     * \brief Конструктор числа типа REAL по умолчанию, имеющего неопределённое
     * (<B>?</B>) значение
     */
    explicit REAL() {
      append_to_parent_type_list("REAL");
      precision_spec = precision_max;
      _r = 0.0;
#ifdef TRACE_REAL
      printf("%s\n", __MYFUNCNAME__);
#endif
    }

    explicit REAL(const PREC& precision) {
      append_to_parent_type_list("REAL");
      _r = 0.0;
      precision_spec = precision == 0 ? precision_max : precision;
#ifdef TRACE_REAL
      printf("%s\n", __MYFUNCNAME__);
#endif
    }

     /* \param [in] precision Число значащих цифр мантиссы. */


    /**
     * \brief Конструктор числового типа REAL из числового типа REAL или INTEGER,
     * переданного через ссылку на тип REAL
     * \param [in] src Объект-источник --- число типа REAL или INTEGER, переданное
     * через ссылку на тип REAL.
     */
    REAL(const REAL& src) : NUMBER() {
      append_to_parent_type_list("REAL");
      precision_spec = src.precision_spec;

      if (!src.is_determinated()) {
        determinated = false;
        _r = 0.0;
      } else {
        determinated = true;
        _r = src.get_number_value();
      }

#ifdef TRACE_REAL
    printf("%s: %s <- %s\n", __MYFUNCNAME__, print_value().c_str(), src.print_value().c_str());
#endif

    }

    /**
     * \brief Конструктор числового типа REAL из значения real_type
     * \param [in] src Источник --- числовое значение, которое будет присвоено.
     */
    REAL(real_type src) {
      determinated = true;
      append_to_parent_type_list("REAL");
      precision_spec = precision_max;
      _r = round(src, precision_spec);

#ifdef TRACE_REAL
      printf("%s: %s <- %.20e\n", __MYFUNCNAME__, print_value().c_str(), src);
#endif

    }

    /**
     * \brief Конструктор числового типа REAL из значения real_type
     * \param [in] src Источник --- числовое значение, которое будет присвоено.
     * \param [in] precision Число значащих цифр мантиссы.
     */
    explicit REAL(real_type src, const PREC& precision) {
      determinated = true;
      append_to_parent_type_list("REAL");
      precision_spec = precision == 0 ? precision_max : precision;
      _r = round(src, precision_spec);

#ifdef TRACE_REAL
    printf("%s: %s <- %.20e\n", __MYFUNCNAME__, print_value().c_str(), src);
#endif

    }

    /**
     * \brief Деструктор числового типа REAL --- по умолчанию
     */
    virtual ~REAL() = default;

    /**
     * \brief Оператор присваивания числового типа REAL, переданного через ссылку на тип REAL
     * \param [in] rhs Источник --- число типа REAL или INTEGER, переданное
     * через ссылку на тип REAL.
     *
     * При выполнении присваивания проводится проверка на самоприсваивание и копирование значения
     * с округлением согласно максимальной точности.
     */
    REAL& operator=(const REAL& rhs);

    /**
     * \file
     * Получение значения и свойств типа.
     */

    /**
     * \brief Преобразование числа типа REAL к значению типа number_type
     * \return значение числа типа REAL в виде типа number_type.
     */
    virtual number_type get_number_value() const override;

    /**
     * \brief Получить количество значащих цифр мантиссы значения числа типа REAL
     * \return количество значащих цифр мантиссы значения числа типа REAL.
     */
    virtual unsigned get_number_precision() const override;

    /**
     * \file
     * Арифметические операторы:
     *
     * * Унарный знак.
     */

    /**
     * \brief Унарный плюс числа типа REAL
     * \return число типа REAL, равное результату сложения числа типа REAL с нулём.
     */
    REAL operator+() const;

    /**
     * \brief Унарный минус числа типа REAL
     * \return число типа REAL, равное результату вычитания числа типа REAL из нуля.
     */
    REAL operator-() const;

    /**
     * \file
     * * Сложение чисел типа REAL и INTEGER со значением.
     */

    /**
     * \brief Сложение числа типа REAL со значением типа real_type
     * \param [in] rhs Значение типа real_type, с которым складывается число типа REAL.
     * \return число типа REAL --- результат сложения числа типа REAL с аргументом.
     */
    REAL operator+(real_type rhs) const;

    /**
     * \brief Сложение числа типа INTEGER со значением типа real_type
     * \param [in] lhs Число типа INTEGER, первое слагаемое.
     * \param [in] rhs Значение типа real_type, второе слагаемое.
     * \return число типа REAL --- результат сложения слагаемых.
     */
    friend REAL operator+(const INTEGER& lhs, real_type rhs);

    /**
     * \file
     * * Вычитание из чисел типа REAL и INTEGER значения.
     */

    /**
     * \brief Вычитание из числа типа REAL значения типа real_type
     * \param [in] rhs Значение типа real_type, которое вычитается из числа типа REAL.
     * \return число типа REAL --- результат вычитания аргумента из числа типа REAL.
     */
    REAL operator-(real_type rhs) const;

    /**
     * \brief Вычитание из числа типа INTEGER значения типа real_type
     * \param [in] lhs Число типа INTEGER, уменьшаемое.
     * \param [in] rhs Значение типа real_type, вычитаемое.
     * \return число типа REAL --- результат вычитания вычитаемого из уменьшаемого.
     */
    friend REAL operator-(const INTEGER& lhs, real_type rhs);

    /**
     * \file
     * * Умножение чисел типа REAL и INTEGER на значение.
     */

    /**
     * \brief Умножение числа типа REAL на значение типа real_type
     * \param [in] rhs Значение типа real_type, на которое умножается число типа REAL.
     * \return число типа REAL --- результат умножения числа типа REAL на аргумент.
     */
    REAL operator*(real_type rhs) const;

    /**
     * \brief Умножение числа типа INTEGER на значение типа real_type
     * \param [in] lhs Число типа INTEGER, первый множитель.
     * \param [in] rhs Значение типа real_type, второй множитель.
     * \return число типа REAL --- результат умножения множителей.
     */
    friend REAL operator*(const INTEGER& lhs, real_type rhs);

    /**
     * \file
     * * Деление чисел типа REAL и INTEGER на значение.
     */

    /**
     * \brief Деление числа типа REAL на значение типа real_type
     * \param [in] rhs Значение типа real_type, на которое делится число типа REAL.
     * \return число типа REAL --- результат деления числа типа REAL на аргумент.
     */
    REAL operator/(real_type rhs) const;

    /**
     * \brief Деление числа типа INTEGER на значение типа real_type
     * \param [in] lhs Число типа INTEGER, делимое.
     * \param [in] rhs Значение типа real_type, делитель.
     * \return число типа REAL --- результат деления делимого на делитель.
     */
    friend REAL operator/(const INTEGER& lhs, real_type rhs);

    /**
     * \file
     * * Целочисленное деление (DIV) числа типа REAL на значение
     * (используется оператор '>>', соответствующий оператору 'DIV' в языке EXPRESS).
     */

    /**
     * \brief Целочисленное деление DIV числа типа NUMBER на значение типа real_type
     * \param [in] rhs Значение типа number_type, на котрое делится число типа NUMBER.
     * \return число типа INTEGER --- результат целочисленного деления числа типа NUMBER на аргумент.
     */
    INTEGER operator>>(real_type rhs);

    /**
     * \file
     * * Остаток от деления по модулю (MOD) числа типа REAL на значение real_type.
     * (используется оператор '%', соответствующий оператору 'MOD' в языке EXPRESS).
     */

    /**
     * \brief Остаток от деления по модулю MOD числа типа NUMBER на значение типа real_type
     * \param [in] rhs Значение типа number_type, на котрое делится число типа NUMBER.
     * \return число типа INTEGER --- остаток от деления числа типа NUMBER на аргумент.
     */
    INTEGER operator%(real_type rhs);
  };

#if 0
  /** 
   * \brief Шаблон, дополняющий класс \ref express::REAL "REAL" указанием точности
   * в качестве параметра
   */
  template<int precision = 0>
  class REAL: public REAL {

  public:

    /**
     * \brief Конструктор типа, имеющего неопределённое (<B>?</B>) значение
     */
    REAL() : REAL(0.0, precision == 0 ? precision_max : precision) {
      determinated = false;
    }

    /**
     * \brief Конструктор из числа типа REAL
     * \param [in] src Источник --- действительное число типа REAL.
     */
    REAL(const REAL& src) : REAL(src, precision == 0 ? precision_max : precision) {
#ifdef TRACE_REAL
    printf("%s: %s <- %s\n", __MYFUNCNAME__, print_value().c_str(), src.print_value().c_str());
#endif
    }

    /**
     * \brief Конструктор из типа real_type
     * \param [in] src Источник - значение типа real_type.
     */
    REAL(real_type src) : REAL(src, precision == 0 ? precision_max : precision) {
#ifdef TRACE_REAL
    printf("%s: %s <- %.20e\n", __MYFUNCNAME__, print_value().c_str(), src);
#endif
    }

    /**
     * \brief Деструктор типа REAL --- по умолчанию
     */
    virtual ~REAL() = default;
  };
#endif
}
