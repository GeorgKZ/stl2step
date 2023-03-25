/**
 * \file
 * \brief Файл с описанием агрегированного типа данных \ref express::LIST_GENERIC "LIST (список)" языка EXPRESS (ГОСТ Р ИСО 10303-11-2009, 8.2.2)
 */

namespace express {

  /**
   * \brief Тип данных \ref express::LIST_GENERIC "LIST (список)" (ГОСТ Р ИСО 10303-11-2009, 8.2.2)
   *
   * \anchor p11_s8_2_2
   *
   * \ref express::LIST_GENERIC "8.2.2 Тип данных LIST"
   *
   * Областью определения типа данных \ref express::LIST_GENERIC "LIST" являются последовательности подобных элементов.
   * Необязательные нижняя и верхняя границы, задаваемые выражениями, имеющими целочисленные
   * значения, определяют минимальное и максимальное число элементов в совокупности, определённой
   * типом данных \ref express::LIST_GENERIC "LIST". В определении типа данных \ref express::LIST_GENERIC "LIST" может быть факультативно
   * установлено, что в списке не могут присутствовать одинаковые элементы.
   \verbatim
     Синтаксис:
      250 list_type = LIST [ bound_spec ] OF [ UNIQUE ] instantiable_type .
      185 bound_spec = '[' bound_1 ':' bound_2 ']' .
      183 bound_1 = numeric_expression .
      184 bound_2 = numeric_expression .
   \endverbatim
   * Правила и ограничения:
   *
   * a) Выражение <B>bound_1</B> должно иметь целочисленное значение, большее или равное нулю. Оно
   * задаёт нижнюю границу, определяющую минимальное число элементов, которое может содержаться в списке
   * этого типа данных. Выражение <B>bound_1</B> не должно иметь неопределённого (<B>?</B>) значения.
   *
   * b) Выражение <B>bound_2</B> должно иметь целочисленное значение, большее или равное значению
   * <B>bound_1</B>, либо неопределённое (<B>?</B>) значение. Оно задаёт верхнюю границу, определяющую максимальное
   * число элементов, которое может содержаться в списке этого типа данных. Если значение данного
   * выражения является неопределённым (<B>?</B>), то число элементов в списке этого типа данных не ограничено сверху.
   *
   * c) Если элемент <B>bound_spec</B> опущен, то границы списка определяются как [0:?].
   *
   * d) Если указано ключевое слово <B>UNIQUE</B>, то каждый элемент в списке этого типа данных должен
   * отличаться (то есть не являться эквивалентным экземпляром) от любого другого элемента того же
   * списка.
   *
   * <B><I>Пример --- В данном примере определён список массивов. Список может содержать от нуля до
   * десяти массивов. Каждый массив из десяти целых чисел должен отличаться от других массивов в
   * данном списке.</I>
   <PRE>
     complex_list : \ref express::LIST_GENERIC "LIST"[0:10] OF UNIQUE \ref express::ARRAY_GENERIC "ARRAY"[1:10] OF \ref express::INTEGER "INTEGER";
   </PRE>
   * </B>
   */
  class LIST_GENERIC : public AGGREGATE_GENERIC {

  private:

   /**
    * \brief Получить нижний индекс \ref express::LIST_GENERIC "списка LIST"
    * \return значение нижнего индекса \ref express::LIST_GENERIC "списка LIST".
    *
    * Если типом данных является \ref express::LIST_GENERIC "список LIST", нижний индекс всегда равен единице.
    */
    virtual integer_type get_loindex() const ;

   /**
    * \brief Получить верхний индекс \ref express::LIST_GENERIC "списка LIST"
    * \return значение верхнего индекса \ref express::LIST_GENERIC "списка LIST".
    *
    * Если типом данных является \ref express::LIST_GENERIC "список LIST", верхний индекс
    * равен числу элементов \ref express::LIST_GENERIC "списка LIST".
    */
    virtual integer_type get_hiindex() const ;

  protected:

    /**
     * \brief Получить тип данных списка
     * \return тип данных списка в виде элемента перечисления OBJTYPE.
     */
    virtual OBJTYPE objtype() const override;

    /**
     * \brief Проверка равенства значений или экземпляров списков
     * \param [in] rhs Список, с которым выполняется сравнение, в виде ссылки на тип LIST_GENERIC.
     * \return результат проверки равенства значений списков.
     */
    LOGICAL is_list_equal(const LIST_GENERIC& rhs, bool compare_value) const;

  public:

    /**
     * \brief Конструктор списка, имеющего неопределённое (<B>?</B>) значение
     * \param [in] Bound_1 минимальное число элементов, которое может содержаться в списке.
     * По умолчанию ноль.
     * \param [in] Bound_2 максимальное число элементов, которое может содержаться в списке.
     * По умолчанию имеет неопределённое значение.
     * \param [in] Options битовый флаг, принимающий значение \ref express::AGGREGATE_GENERIC.NONE
     * "NONE" (флаги не установлены) \ref express::AGGREGATE_GENERIC.UNIQUE "UNIQUE".
     *
     * Нижняя граница не должна иметь неопределённого (<B>?</B>) значения.
     *
     * Нижняя граница должна быть больше или равна нулю.
     *
     * Верхняя граница (если имеет определённое значение) должня быть больше или равна
     * верхней границе.
     */
    explicit LIST_GENERIC(const INTEGER& Bound_1 = INTEGER(0), const INTEGER& Bound_2 = INTEGER(), unsigned Options = NONE);

    /**
     * \brief Деструктор списка --- по умолчанию
     */
    virtual ~LIST_GENERIC() = default;

    friend class AGGREGATE_GENERIC;
    template<class T> friend class LIST;
  };

  /**
   * \brief Шаблон для типа данных \ref express::LIST_GENERIC "LIST (список)" (ГОСТ Р ИСО 10303-11-2009, 8.2.2),
   * специализированного для хранения произвольного типа данных
   */
  template<class T>
  class LIST : public LIST_GENERIC {

  protected:

    /**
     * \brief Элементы списка
     */
    std::vector<T> elements;

    /**
     * \brief Элемент, имеющий неопределённое значение
     */
    inline static const T undef = T();

    virtual const T& get_undef() const override {
      return undef;
    }

    /**
     * \brief Получить константную ссылку на элемент внутреннего представления списка
     * \param [in] index индекс требуемого элемента списка.
     * \return константная ссылка на элемент внутреннего представления списка.
     */
    virtual const T& get_constant_internal_element(integer_type index) const override {
      if (index < 0 || index >= static_cast<integer_type>(elements.size())) {
        throw exception{ __MYFUNCNAME__, "Index = %lli can not be out of borders (from %lli to %lli)", index, 0, elements.size() };
      }
      return elements[static_cast<size_t>(index)];
    }

    /**
     * \brief Получить ссылку на элемент внутреннего представления списка
     * \param [in] index индекс требуемого элемента списка.
     * \return ссылка на на элемент внутреннего представления списка.
     */
    virtual T& get_internal_element(integer_type index) override {
      if (index < 0 || index >= static_cast<integer_type>(elements.size())) {
        throw exception{ __MYFUNCNAME__, "Index = %lli can not be out of borders (from %lli to %lli)", index, 0, elements.size() };
      }
      return elements[static_cast<size_t>(index)];
    }
#if 0
    /**
     * \brief Проверить, является ли элемент rhs уникальным для списка
     * \param [in] rhs проверяемый элемент.
     * \return true, если элемент rhs уникален, и false, если нет.
     *
     * Проверка заключается в сравнении с элементами списка. Если хотя бы один
     * элемент списка равен проверяемому, то проверяемый элемент не является уникальным.
     *
     * Элемент, имеющий неопределённое (<B>?</B>) значение, всегда уникален, так как
     * возвращает значение \ref express::UNKNOWN "UNKNOWN" при сравнении с любым элементом,
     * что интерпретируется как отличие.
     */
    bool is_unique(const T& rhs) const {
      if (!determinated || !rhs.is_determinated()) return true;

      for (auto i = elements.cbegin(); i != elements.cend(); ++i) {
        if ((*i == rhs).is_true()) return false;
      }
      return true;
    }
#endif
    /**
     * \brief Получить количество элементов внутреннего представления списка
     * \return количество элементов внутреннего представления списка.
     */
    virtual integer_type get_elements_size() const override {
      return static_cast<integer_type>(elements.size());
    }

  public:

    /**
     * \brief Конструктор списка, имеющего неопределённое (<B>?</B>) значение
     * \param [in] Bound_1 минимальное число элементов, которое может содержаться в списке.
     * По умолчанию ноль.
     * \param [in] Bound_2 максимальное число элементов, которое может содержаться в списке.
     * По умолчанию имеет неопределённое значение.
     * \param [in] Options битовый флаг, принимающий значение \ref express::AGGREGATE_GENERIC.NONE
     * "NONE" (флаги не установлены) \ref express::AGGREGATE_GENERIC.UNIQUE "UNIQUE".
     */
    explicit LIST(const INTEGER& Bound_1 = INTEGER(0), const INTEGER& Bound_2 = INTEGER(),
          unsigned Options = NONE) : LIST_GENERIC(Bound_1, Bound_2, Options) {
      append_to_parent_type_list();

#ifdef TRACE
printf("Construct '%s' (", __MYFUNCNAME__);
if (bound_1.is_determinated()) printf("%lli ", bound_1.get_integer_value()); else printf("? ");
if (bound_2.is_determinated()) printf("%lli ", bound_2.get_integer_value()); else printf("? ");
printf(")\n");
#endif

    }

    /** \brief Деструктор списка по умолчанию */
    virtual ~LIST() = default;

    /**
     * \brief Оператор индексирования (\ref p11_s12_6_1 "ГОСТ Р ИСО 10303-11-2009, 12.6.1")
     * \param [in] index Значение индекса возвращаемого значения.
     * \return ссылка на элемент списка, находящийся по указанному индексу или на неопределённый тип данных,
     * если индекс или элемент имеют неопределённое значение. 
     * (можно использовать только в правой части присваивания)
     */
    virtual const T& operator[](const INTEGER& index) const override {
      return dynamic_cast<const T&>(AGGREGATE_GENERIC::operator[](index));
    }

    /**
     * \brief Уточнение элементом (\ref p11_s12_6_1 "ГОСТ Р ИСО 10303-11-2009, 13.3.2")
     * \param [in] index Значение индекса возвращаемого значения.
     * \return ссылка на элемент списка, находящийся по указанному индексу или на неопределённый тип данных,
     * если индекс или элемент имеют неопределённое значение. 
     * (можно использовать и в левой части присваивания)
     */
    virtual T& operator[](const INTEGER& index) override {
      return dynamic_cast<T&>(AGGREGATE_GENERIC::operator[](index));
    }

   /**
    * \brief Присвоение списку значений при помощи инициализатора (\ref p11_s12_9 "ГОСТ Р ИСО 10303-11-2009, 12.9")
    * \param [in] Elements перечень элементов, инициализирующих список.
    * \return ссылку на инициализированный список, как требует operator=()
    *
    * Количество элементов инициализатора не может превышать максимальный размер списка,
    * если он задан.
    *
    * Количество элементов инициализатора не может быть меньше минимального размера списка,
    * если он задан.
    *
    * Инициализатор не может содержать элементы, имеющие неопределённые значения.
    *
    * Если список определён с ключевым словом UNIQUE, элементы инициализатора должны быть уникальными.
    */
   LIST& operator=(std::initializer_list<T> Elements) {
      if (bound_2.is_determinated() && static_cast<integer_type>(Elements.size()) > bound_2.get_integer_value()) {
        throw exception{__MYFUNCNAME__, "initializer_list shall not be greater than maximal LIST size"};
      }

      if (static_cast<integer_type>(Elements.size()) < bound_1.get_integer_value()) {
        throw exception{__MYFUNCNAME__, "initializer_list shall not be less than minimal LIST size"};
      }
      determinated = true;
      elements.clear();
      size_t n = 1;
      for (auto& i : Elements) {
        if (!i.is_determinated()) {
          throw exception{__MYFUNCNAME__, "initializer_list element #%i shall not be indetrminated in LIST", n};
        }
        if (uniq && !is_unique(i)) {
          throw exception{__MYFUNCNAME__, "initializer_list element #%i shall be unique in LIST defined as Not UNIQUE", n};
        }
        elements.push_back(i);
        n++;
      }
      return *this;
    }

    /**
     * \brief Присвоение списку значений другого списка (\ref p11_s13_3 "ГОСТ Р ИСО 10303-11-2009, 13.3")
     * \param [in] rhs Список, элементы которого присваиваются текущему.
     * \return ссылку на список, как требует operator=()
     *
     * Тип элементов списка rhs должен быть совместим (быть одинаковым или быть подтипом
     * или быть конкретизацией) с типом элементов текущего списка или быть значением для
     * типа элементов текущего списка (см. \ref p11_s13_3_2 "п.13.3.2") --- эта проверка
     * выполняется на этапе компиляции.
     *
     * Если список rhs имеет неопределённое значение, текущему списку присваивается
     * неопределённое значение.
     *
     * Количество элементов списка rhs не должно быть больше максимально возможнго размера текущего списка.
     *
     * Количество элементов списка rhs не должно быть меньше минимально возможнго размера текущего списка.
     *
     * Если текущий список определён с ключевым словом UNIQUE, элементы списка rhs должны быть
     * уникальными.
     */
    LIST& operator=(const LIST_GENERIC& rhs) {

      /* Выполнить проверки */
      if (!rhs.determinated) {
        determinated = false;
        elements.clear();
        return *this;
      }
      if (bound_2.is_determinated() && rhs.get_elements_size() > bound_2.get_integer_value()) {
        throw exception{__MYFUNCNAME__, "rhs size shall not be greater than maximal LIST size"};
      }
      if (rhs.get_elements_size() < bound_1.get_integer_value()) {
        throw exception{__MYFUNCNAME__, "rhs size shall not be less than minimal LIST size"};
      }

      /* Скопировать элементы */
      determinated = true;
      elements.clear();
      for (auto n = rhs.get_loindex(); n <= rhs.get_hiindex(); ++n) {
        if (!rhs[n].is_determinated()) {
          throw exception{ __MYFUNCNAME__, "rhs element #%i shall not be indetrminated in LIST", n };
        }
        /* Попробовать привести элемент к типу T */
        const T* t = dynamic_cast<const T*>(&rhs[n]);
        if (t == nullptr) {
          throw exception{ __MYFUNCNAME__, "LIST rhs (%s) must be compatible to 'this' LIST (%s)", rhs.get_type_name().c_str(), get_type_name().c_str() };
        }
        if (uniq && !is_unique(*t)) {
          throw exception{ __MYFUNCNAME__, "rhs element #%i shall be unique in LIST defined as UNIQUE", n };
        }
        elements.push_back(*t);
      }

      return *this;
    }

    /**
     * \brief Объединение списка со списком (\ref p11_s12_6_3 "ГОСТ Р ИСО 10303-11-2009, 12.6.3")
     * \param [in] rhs список, добавляемый к текущему списку.
     * \return список, созданный из текущего добавлением списка rhs
     *
     * Если какой-либо из операндов имеет неопределенное (?) значение, то результат будет также иметь
     * неопределённое (?) значение.
     *
     * Добавлять можно только список с элементами совместимого типа.
     */
    LIST operator+(const LIST& rhs) const {
      LIST result;

      if (determinated && rhs.determinated) {
        result.determinated = true;
        for (auto i = elements.cbegin(); i != elements.cend(); ++i) {
          result.elements.push_back(*i);
        }
        for (auto i = rhs.elements.cbegin(); i != rhs.elements.cend(); ++i) {
          result.elements.push_back(*i);
        }
      }
      return result;
    }

    /**
     * \brief Объединение списка с элементом (\ref p11_s12_6_3 "ГОСТ Р ИСО 10303-11-2009, 12.6.3")
     * \param [in] rhs добавляемый к текущему списку элемент
     * \return список, созданный из текущего добавлением элемента rhs
     *
     * Если какой-либо из операндов имеет неопределенное (?) значение, то результат будет также иметь
     * неопределённое (?) значение.
     *
     * Добавлять можно только элемент совместимого типа.
     */
    LIST operator+(const T& rhs) const {
      LIST result;

      if (determinated && rhs.is_determinated()) {
        result.determinated = true;
        for (auto i = elements.cbegin(); i != elements.cend(); ++i) {
          result.elements.push_back(*i);
        }
        result.elements.push_back(rhs);
      }
      return result;
    }

    /**
     * \brief Объединение элемента со списком (\ref p11_s12_6_3 "ГОСТ Р ИСО 10303-11-2009, 12.6.3")
     * \param [in] Element слагаемое --- элемент.
     * \param [in] List слагаемое --- список.
     * \return список, созданный из элемента Element и списка List.
     *
     * Если какой-либо из операндов имеет неопределенное (?) значение, то результат будет также иметь
     * неопределённое (?) значение.
     *
     * Складывать можно только элемент со списком, имеющим элементы совместимого типа.
     */
    friend LIST<T> operator+(const T& Element, const LIST& List) {
      LIST<T> result;
      if (Element.is_determinated() && List.is_determinated()) {
        result.determinated = true;
        result.elements.push_back(Element);
        for (auto i = List.elements.cbegin(); i != List.elements.cend(); ++i) {
          result.elements.push_back(*i);
        }
      }
      return result;
    }
    
    friend class BAG<T>;
    friend class SET<T>;
  };
}