/**
 * \file
 * \brief Файл с описанием агрегированного типа данных \ref express::ARRAY_GENERIC "ARRAY (массив)" языка EXPRESS
 * (ГОСТ Р ИСО 10303-11-2009, 8.2.1)
 */

#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4250)
#endif

namespace express {

  /**
   * \brief Тип данных \ref express::ARRAY_GENERIC "ARRAY (массив)" (ГОСТ Р ИСО 10303-11-2009, 8.2.1)
   *
   * \anchor p11_s8_2_1
   *
   * \ref express::ARRAY_GENERIC "8.2.1 Тип данных ARRAY"
   *
   * Областью определения типа данных \ref express::ARRAY_GENERIC "ARRAY" являются индексированные совокупности подобных
   * элементов фиксированного размера. Нижняя и верхняя границы, задаваемые выражениями, имеющими
   * целочисленные значения, определяют диапазон значений индекса и, следовательно, размер массива. В
   * определении типа данных \ref express::ARRAY_GENERIC "ARRAY" может факультативно устанавливаться, что в массиве не могут
   * присутствовать одинаковые элементы. Кроме того, может быть установлено, что элементы массива могут не
   * присутствовать на всех индексированных позициях.
   \verbatim
     Синтаксис:
      175 array_type = ARRAY bound_spec OF [ OPTIONAL ] [ UNIQUE ] instantiable_type .
      185 bound_spec = '[' bound_1 ':' bound_2 ']' .
      183 bound_1 = numeric_expression .
      184 bound_2 = numeric_expression .
   \endverbatim
   * Пусть <I>m</I> является нижней границей, а <I>n</I> --- верхней, тогда в массиве имеется ровно <I>n - m + 1</I>
   * элементов. Эти элементы проиндексированы подстрочными индексами от <I>m</I> до <I>n</I> включительно (см. \ref p11_s12_6_1 "12.6.1").
   *
   * <SMALL>П&nbsp;р&nbsp;и&nbsp;м&nbsp;е&nbsp;ч&nbsp;а&nbsp;н&nbsp;и&nbsp;е ---
   * Границы массива могут быть положительными, отрицательными или равными нулю, но
   * не могут быть неопределёнными (<B>?</B>) (см. \ref p11_s14_2 "14.2").</SMALL>
   *
   * Правила и ограничения:
   *
   * a) Оба выражения в спецификации границ (\ref express::AGGREGATE.bound_1 "bound_1" и \ref express::AGGREGATE.bound_2 "bound_2") должны иметь целочисленные
   * значения. Ни одно из них не должно иметь неопределённого (<B>?</B>) значения.
   *
   * b) Выражение \ref express::AGGREGATE.bound_1 "bound_1" задаёт нижнюю границу массива. Оно задаёт наименьшее значение индекса,
   * допустимое для элементов массива этого типа данных.
   *
   * c) Выражение \ref express::AGGREGATE.bound_2 "bound_2" задаёт верхнюю границу массива. Оно задаёт наибольшее значение
   * индекса, допустимое для элементов массива этого типа данных.
   *
   * d) Значение выражения \ref express::AGGREGATE.bound_1 "bound_1" должно быть меньше или равно значению выражения \ref express::AGGREGATE.bound_2 "bound_2".
   *
   * e) Если указано ключевое слово <B>OPTIONAL</B>, то массив этого типа данных может иметь неопределённое (<B>?</B>)
   * значение в одной или нескольких индексированных позициях.
   *
   * f) Если ключевое слово <B>OPTIONAL</B> не указано, то массив этого типа данных не должен содержать
   * неопределённых (<B>?</B>) значений ни в одной индексированной позиции.
   *
   * g) Если указано ключевое слово <B>UNIQUE</B>, то каждый элемент массива этого типа данных должен
   * отличаться (то есть не быть эквивалентным экземпляром) от любого другого элемента того же массива.
   *
   * <SMALL>П&nbsp;р&nbsp;и&nbsp;м&nbsp;е&nbsp;ч&nbsp;а&nbsp;н&nbsp;и&nbsp;е ---
   * Оба ключевых слова <B>OPTIONAL</B> и <B>UNIQUE</B> могут использоваться в одном и том же
   * определении типа данных \ref express::ARRAY_GENERIC "ARRAY". Это не исключает многократного появления неопределённых (<B>?</B>) значений
   * элементов массива, поскольку сравнение неопределённых (<B>?</B>) значений дает результат <B>UNKNOWN</B> и,
   * следовательно, условие уникальности не нарушается.</SMALL>
   *
   * <B><I>Пример --- Данный пример показывает, как объявляется многомерный массив.</I>
   <PRE>
     sectors : ARRAY [ 1 : 10 ] OF  –– первое измерение
     \ref express::ARRAY_GENERIC "ARRAY" [ 11 : 14 ] OF –– второе измерение
     UNIQUE something;
   </PRE>
   *
   * <I>Первый массив содержит 10 элементов типа данных </I>\ref express::ARRAY_GENERIC "ARRAY" [11:14] OF UNIQUE something<I>.
   * Атрибут с именем </I>sectors<I> содержит всего 40 элементов типа данных </I>something<I>. В каждом из
   * массивов </I>\ref express::ARRAY_GENERIC "ARRAY" [11:14]<I> не может быть повторяющихся элементов. Однако один и тот же
   * экземпляр объекта </I>something<I> может присутствовать в двух разных массивах</I> \ref express::ARRAY_GENERIC "ARRAY" [11:14] <I>одного
   * экземпляра атрибута </I>sectors</B>.
   */
  class ARRAY_GENERIC : virtual public AGGREGATE_GENERIC {

  protected:

   /**
    * \brief Получить нижний индекс \ref express::ARRAY_GENERIC "массива ARRAY"
    * \return значение нижнего индекса \ref express::ARRAY_GENERIC "массива ARRAY".
    *
    * Если типом данных является \ref express::ARRAY_GENERIC "массив ARRAY", нижний индекс
    * равен значению \ref express::AGGREGATE.bound_1 "объявленного нижнего индекса".
    */
    virtual integer_type get_loindex() const;

   /**
    * \brief Получить верхний индекс \ref express::ARRAY_GENERIC "массива ARRAY"
    * \return значение верхнего индекса \ref express::ARRAY_GENERIC "массива ARRAY".
    *
    * Если типом данных является \ref express::ARRAY_GENERIC "массив ARRAY", верхний индекс
    * равен значению \ref express::AGGREGATE.bound_2 "объявленного верхнего индекса".
    */
    virtual integer_type get_hiindex() const;

    /**
     * \brief Проверка равенства значений или экземпляров массивов
     * \param [in] rhs Массив, с которым выполняется сравнение, в виде ссылки на тип ARRAY_GENERIC.
     * \param [in] compare_value true, если сравниваются значения и false, если экземпляры.
     * \return результат проверки равенства значений массивов.
     */
    LOGICAL is_array_equal(const ARRAY_GENERIC& rhs, bool compare_value) const;

    /**
     * \brief Получить тип данных массива
     * \return тип данных массива в виде элемента перечисления OBJTYPE.
     */
    virtual GENERIC::OBJTYPE objtype() const override;

  public:

    /**
     * \brief Конструктор по умолчанию массива, имеющего неопределённое (<B>?</B>) значение
     */
    ARRAY_GENERIC();

    /**
     * \brief Конструктор массива, имеющего неопределённое (<B>?</B>) значение
     * \param [in] Bound_1 наименьшее значение индекса, допустимое для элементов массива.
     * \param [in] Bound_2 наибольшее значение индекса, допустимое для элементов массива.
     * \param [in] Options битовый флаг, принимающий значение \ref express::AGGREGATE.NONE
     * "NONE" (флаги не установлены) или комбинаций \ref express::AGGREGATE.UNIQUE "UNIQUE"
     * и \ref express::AGGREGATE.OPTIONAL "OPTIONAL".
     *
     * Оба выражения в спецификации границ (Bound_1 и Bound_2) не должны иметь неопределённого
     * (<B>?</B>) значения.
     *
     * Значение выражения Bound_1 должно быть меньше или равно значению выражения Bound_2.
     */
    explicit ARRAY_GENERIC(const INTEGER& Bound_1, const INTEGER& Bound_2, unsigned Options = NONE);

    /**
     * \brief Деструктор массива --- по умолчанию
     */
    virtual ~ARRAY_GENERIC() = default;

    /**
     * \brief Присвоение массиву значений при помощи инициализатора (\ref p11_s12_9 "ГОСТ Р ИСО 10303-11-2009, 12.9")
     * \param [in] Elements перечень элементов, инициализирующих массив.
     * \return ссылку на инициализированный массив, как требует operator=()
     *
     * Количество элементов инициализатора не может превышать размер массива.
     *
     * Количество элементов инициализатора может быть меньше размера массива только
     * если массив определён с ключевым словом OPTIONAL.
     *
     * Инициализатор может содержать элементы, имеющие неопределённые значения, только если
     * массив определён с ключевым словом OPTIONAL.
     *
     * Если массив определён с ключевым словом UNIQUE, элементы инициализатора должны быть
     * уникальными.
     */
    ARRAY_GENERIC& operator=(std::initializer_list<const GENERIC> Elements);

    /**
     * \brief Присвоение массиву значений другого массива (\ref p11_s13_3 "ГОСТ Р ИСО 10303-11-2009, 13.3")
     * \param [in] rhs Массив, элементы которого присваиваются текущему.
     * \return ссылку на массив, как требует operator=()
     *
     * Тип элементов массива rhs должен быть совместим (быть одинаковым или быть подтипом
     * или быть конкретизацией) с типом элементов текущего массива или быть значением для
     * типа элементов текущего массива (см. \ref p11_s13_3_2 "п.13.3.2") --- эта проверка
     * выполняется на этапе компиляции.
     *
     * Если массив rhs имеет неопределённое значение, текущему массиву присваивается
     * неопределённое значение.
     *
     * Количество элементов массива rhs не может превышать размер текущего массива.
     *
     * Количество элементов массива rhs может быть меньше размера текущего массива только
     * если массив определён с ключевым словом OPTIONAL.
     *
     * Массив rhs может содержать элементы, имеющие неопределённые значения, только если
     * текущий массив определён с ключевым словом OPTIONAL.
     *
     * Если текущий массив определён с ключевым словом UNIQUE, элементы массива rhs должны быть
     * уникальными.
     */
    virtual ARRAY_GENERIC& operator=(const ARRAY_GENERIC& rhs);

    friend class AGGREGATE_GENERIC;
    template<class T> friend class ARRAY;
  };

  /**
   * \brief Шаблон для типа данных \ref express::ARRAY_GENERIC "ARRAY (массив)" (ГОСТ Р ИСО 10303-11-2009, 8.2.1),
   * специализированного для хранения произвольного типа данных
   */
  template<class T>
  class ARRAY : public AGGREGATE<T>, public ARRAY_GENERIC {

  public:

    /**
     * \brief Конструктор по умолчанию массива, имеющего неопределённое (<B>?</B>) значение
     */
    ARRAY() : ARRAY_GENERIC() {
      append_to_parent_type_list();

#ifdef TRACE_ARRAY
      printf("%s: determinated=%s, bound_1=%s, bound_2=%s, ordered=%s, optional=%s, uniq=%s\n",
       __MYFUNCNAME__, determinated ? "yes" : "no", bound_1.print_value().c_str(), bound_2.print_value().c_str(),
       ordered ? "yes" : "no", optional ? "yes" : "no", uniq ? "yes" : "no");
#endif
    };

    /**
     * \brief Конструктор массива, имеющего неопределённое (<B>?</B>) значение
     * \param [in] Bound_1 наименьшее значение индекса, допустимое для элементов массива.
     * \param [in] Bound_2 наибольшее значение индекса, допустимое для элементов массива.
     * \param [in] Options битовый флаг, принимающий значение \ref express::AGGREGATE.NONE
     * "NONE" (флаги не установлены) или комбинаций \ref express::AGGREGATE.UNIQUE "UNIQUE"
     * и \ref express::AGGREGATE.OPTIONAL "OPTIONAL".
     *
     * Оба выражения в спецификации границ (Bound_1 и Bound_2) не должны иметь неопределённого
     * (<B>?</B>) значения.
     *
     * Значение выражения Bound_1 должно быть меньше или равно значению выражения Bound_2.
     */
    explicit ARRAY(const INTEGER& Bound_1, const INTEGER& Bound_2, unsigned Options = NONE) : 
      ARRAY_GENERIC(Bound_1, Bound_2, Options) {
      append_to_parent_type_list();

#ifdef TRACE_ARRAY
      printf("%s: determinated=%s, bound_1=%s, bound_2=%s, ordered=%s, optional=%s, uniq=%s\n",
       __MYFUNCNAME__, bound_1.print_value().c_str(), bound_2.print_value().c_str(),
       determinated? "yes" : "no", ordered ? "yes" : "no", optional ? "yes" : "no", uniq ? "yes" : "no");
#endif
    }

    /**
     * \brief Деструктор массива --- по умолчанию
     */
    virtual ~ARRAY() = default;

    /**
     * \brief Присвоение массиву значений при помощи инициализатора (\ref p11_s12_9 "ГОСТ Р ИСО 10303-11-2009, 12.9")
     * \param [in] Elements перечень элементов, инициализирующих массив.
     * \return ссылку на инициализированный массив, как требует operator=()
     *
     * Количество элементов инициализатора не может превышать размер массива.
     *
     * Количество элементов инициализатора может быть меньше размера массива только
     * если массив определён с ключевым словом OPTIONAL.
     *
     * Инициализатор может содержать элементы, имеющие неопределённые значения, только если
     * массив определён с ключевым словом OPTIONAL.
     *
     * Если массив определён с ключевым словом UNIQUE, элементы инициализатора должны быть
     * уникальными.
     */
    ARRAY& operator=(std::initializer_list<const T> Elements) {
      ARRAY_GENERIC::operator=((std::initializer_list<const GENERIC>)Elements);
      return *this;
    }
#if 0

#ifdef TRACE_ARRAY
      printf("Assign list '%s'(%lli, %lli)\n", __MYFUNCNAME__, bound_1.get_integer_value(), bound_2.get_integer_value());
#endif

      if (static_cast<integer_type>(Elements.size()) > bound_2.get_integer_value() - bound_1.get_integer_value() + 1) {
        throw exception{__MYFUNCNAME__, "initializer_list size %u shall not be greater than ARRAY size %lli", Elements.size(), bound_2.get_integer_value() - bound_1.get_integer_value() + 1};
      }

      if (!optional && static_cast<integer_type>(Elements.size()) < bound_2.get_integer_value() - bound_1.get_integer_value() + 1) {
        throw exception{__MYFUNCNAME__, "initializer_list shall have same size (%u) as ARRAY (size %lli) defined as Not OPTIONAL", Elements.size(), bound_2.get_integer_value() - bound_1.get_integer_value() + 1};
      }

      determinated = true;
      AGGREGATE<T>::elements.clear();
      AGGREGATE<T>::size = 0;
      /* Скопировать список инициализации в массив */

      for (auto& i : Elements) {

#ifdef TRACE_ARRAY
          printf("Assigning element %lli '%s'\n", AGGREGATE<T>::size, i.print_value().c_str());
#endif

        if (!optional && !i.is_determinated()) {
          throw exception{__MYFUNCNAME__, "initializer_list element #%lli shall not be indetrminated in ARRAY defined as Not OPTIONAL", AGGREGATE<T>::size};
        }
        if (uniq && !is_unique(i)) {
          throw exception{__MYFUNCNAME__, "initializer_list element #%lli shall be unique in ARRAY defined as Not UNIQUE", AGGREGATE<T>::size};
        }
        AGGREGATE<T>::elements.push_back({ i, 1 });
        AGGREGATE<T>::size ++;
      }
      if (optional) {
        /* При необходимости дополнить массив неопределёнными элементами */
        for (auto i = AGGREGATE<T>::elements.size(); i < static_cast<size_t>(bound_2.get_integer_value() - bound_1.get_integer_value() + 1); ++i) {

#ifdef TRACE_ARRAY
          printf("Assigning undefined element %lli\n", AGGREGATE<T>::size);
#endif
          AGGREGATE<T>::elements.push_back({ AGGREGATE<T>::undef, 1});
          AGGREGATE<T>::size ++;
        }
      }
      return *this;
    }
#endif
    /**
     * \brief Присвоение массиву значений другого массива (\ref p11_s13_3 "ГОСТ Р ИСО 10303-11-2009, 13.3")
     * \param [in] rhs Массив, элементы которого присваиваются текущему.
     * \return ссылку на массив, как требует operator=()
     *
     * Тип элементов массива rhs должен быть совместим (быть одинаковым или быть подтипом
     * или быть конкретизацией) с типом элементов текущего массива или быть значением для
     * типа элементов текущего массива (см. \ref p11_s13_3_2 "п.13.3.2") --- эта проверка
     * выполняется на этапе компиляции.
     *
     * Если массив rhs имеет неопределённое значение, текущему массиву присваивается
     * неопределённое значение.
     *
     * Количество элементов массива rhs не может превышать размер текущего массива.
     *
     * Количество элементов массива rhs может быть меньше размера текущего массива только
     * если массив определён с ключевым словом OPTIONAL.
     *
     * Массив rhs может содержать элементы, имеющие неопределённые значения, только если
     * текущий массив определён с ключевым словом OPTIONAL.
     *
     * Если текущий массив определён с ключевым словом UNIQUE, элементы массива rhs должны быть
     * уникальными.
     */
    virtual ARRAY& operator=(const ARRAY_GENERIC& rhs) override {
      ARRAY_GENERIC::operator=(rhs);
      return *this;
    }
  };
}

#if defined(_MSC_VER)
#pragma warning( pop ) 
#endif
