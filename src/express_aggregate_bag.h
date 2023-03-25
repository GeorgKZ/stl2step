/**
 * \file
 * \brief Файл с описанием агрегированного типа данных \ref express::BAG "BAG (множество)" языка EXPRESS
 * (ГОСТ Р ИСО 10303-11-2009, 8.2.3)
 */

namespace express {

  class SET_GENERIC;

  /**
   * \brief Тип данных \ref express::BAG "BAG (множество)" (ГОСТ Р ИСО 10303-11-2009, 8.2.3)
   *
   * \anchor p11_s8_2_3
   *
   * \ref express::BAG "8.2.3 Тип данных  BAG"
   *
   * Областью определения типа данных \ref express::BAG "BAG" являются неупорядоченные совокупности
   * подобных элементов. Необязательные нижняя и верхняя границы, задаваемые выражениями,
   * имеющими целочисленные значения, определяют минимальное и максимальное число элементов
   * в совокупности, определённой типом данных \ref express::BAG "BAG".
   \verbatim
     Синтаксис:
      180 bag_type = BAG [ bound_spec ] OF instantiable_type.
      185 bound_spec = '[' bound_1 ':' bound_2 ']'.
      183 bound_1 = numeric_expression.
      184 bound_2 = numeric_expression.
   \endverbatim
   * Правила и ограничения:
   *
   * a) Выражение <B>bound_1</B> должно иметь целочисленное значение, большее или равное нулю.
   * Оно задаёт нижнюю границу, определяющую минимальное число элементов, которое может содержаться
   * в экземпляре пакета этого типа данных. Выражение <B>bound_1</B> не должно иметь неопределённого (<B>?</B>)
   * значения.
   *
   * b) Выражение <B>bound_2</B> должно иметь целочисленное значение, большее или равное значению
   * <B>bound_</B>1, либо неопределённое (<B>?</B>) значение. Оно задаёт верхнюю границу, определяющую
   * максимальное число элементов, которое может содержаться в экземпляре пакета этого типа данных.
   * Если значение данного выражения является неопределённым (<B>?</B>), то число элементов в экземпляре
   * пакета этого типа данных не ограничено сверху.
   *
   * c) Если элемент <B>bound_spec</B> опущен, то границы пакета определяются как <B>[0:?]</B>.
   *
   * <B><I>Пример --- В данном примере атрибут </I>a_bag_of_points<I> определён как пакет объектов
   * </I>point<I> (объекты </I>point<I> относятся к именованному типу данных, который объявлен
   * в другом месте).</I>
   <PRE>
     a_bag_of_points : \ref express::BAG "BAG" OF point;
   </PRE>
   * <I>Экземпляр атрибута </I>a_bag_of_points<I> может содержать ни одного или несколько объектов
   * </I>point<I>. Один и тот же экземпляр объекта </I>point<I> может появиться несколько раз
   * в экземпляре </I>a_bag_of_points<I>.
   *
   * Если требуется, чтобы экземпляр </I>a_bag_of_points<I> содержал, по крайней мере, один
   * элемент, то в спецификации нижняя граница должна быть определена следующим образом:</I>
   <PRE>
     a_bag_of_points : \ref express::BAG "BAG" [1:?] OF point;
   </PRE>
   * <I>Экземпляр атрибута </I>a_bag_of_points<I> теперь должен содержать, по крайней мере,
   * один объект </I>point.</B>
   */
  class BAG_GENERIC : public AGGREGATE_GENERIC {

  private:

   /**
    * \brief Получить нижний индекс \ref express::BAG_GENERIC "множества BAG"
    * \return значение нижнего индекса \ref express::BAG_GENERIC "множества BAG".
    *
    * Если типом данных является \ref express::BAG_GENERIC "множество BAG", нижний индекс всегда равен единице.
    */
    virtual integer_type get_loindex() const ;

   /**
    * \brief Получить верхний индекс \ref express::BAG_GENERIC "множества BAG"
    * \return значение верхнего индекса \ref express::BAG_GENERIC "множества BAG".
    *
    * Если типом данных является \ref express::BAG_GENERIC "множество BAG", верхний индекс
    * равен числу элементов \ref express::BAG_GENERIC "множества BAG".
    */
    virtual integer_type get_hiindex() const ;

  protected:

    /**
     * \brief Получить тип данных множества
     * \return тип данных множества в виде элемента перечисления OBJTYPE.
     */
    virtual GENERIC::OBJTYPE objtype() const override;

    /**
      * \brief Проверка равенства значений или экземпляров с множеством
      * \param [in] rhs Множество или набор, с которым выполняется сравнение, в виде ссылки на тип BAG_GENERIC.
      * \return логическое выражение типа LOGICAL --- результат проверки равенства значений
      * множества и множества rhs.
      */
    LOGICAL is_bag_equal(const BAG_GENERIC& rhs, bool compare_value) const;

    /**
      * \brief Проверка равенства значений или экземпляров с набором
      * \param [in] rhs Набор, с которым выполняется сравнение, в виде ссылки на тип SET_GENERIC.
      * \return логическое выражение типа LOGICAL --- результат проверки равенства значений
      * множества и набора rhs.
      */
    LOGICAL is_set_equal(const SET_GENERIC& rhs, bool compare_value) const;

  public:

    /**
     * \brief Конструктор \ref express::BAG_GENERIC "множества BAG", имеющего неопределённое (<B>?</B>) значение
     * \param [in] Bound_1 минимальное число элементов, которое может содержаться в \ref express::BAG_GENERIC "множестве BAG".
     * По умолчанию ноль.
     * \param [in] Bound_2 максимальное число элементов, которое может содержаться в \ref express::BAG_GENERIC "множестве BAG".
     * По умолчанию имеет неопределённое значение.
     */
    explicit BAG_GENERIC(const INTEGER& Bound_1 = INTEGER(0), const INTEGER& Bound_2 = INTEGER());

    /** \brief Деструктор \ref express::BAG_GENERIC "множества BAG" --- по умолчанию */
    virtual ~BAG_GENERIC() = default;

    friend class AGGREGATE_GENERIC;
    template<class T> friend class BAG;
    template<class T> friend class SET;
  };

  /**
   * \brief Шаблон для типа данных \ref express::BAG_GENERIC "BAG (множество)" (ГОСТ Р ИСО 10303-11-2009, 8.2.3),
   * специализированного для хранения произвольного типа данных
   */
  template<class T>
  class BAG : public BAG_GENERIC {

  protected:

    /**
     * \brief Внутреннее представление элементов \ref express::BAG_GENERIC "множества BAG"
     */
    std::vector<std::pair<T, integer_type>> elements;

    /**
     * \brief Общее количество элементов \ref express::BAG_GENERIC "множества BAG"
     */
    integer_type size;

    /**
     * \brief Элемент \ref express::BAG_GENERIC "множества BAG", имеющий неопределённое значение
     */
    inline static const T undef = T();

    /**
     * \brief Получить ссылку на элемент \ref express::BAG_GENERIC "множества BAG",
     * имеющий неопределённое значение
     * 
     * \return ссылка на элемент \ref express::BAG_GENERIC "множества BAG",
     * имеющий неопределённое значение.
     */
    virtual const T& get_undef() const override {
      return undef;
    }

    /**
     * \brief Получить количество элементов \ref express::BAG_GENERIC "множества BAG"
     *
     * \return количество элементов \ref express::BAG_GENERIC "множества BAG".
     */
    virtual integer_type get_elements_size() const override {
      return size;
    }

    /**
     * \brief Получить константную ссылку на уникальный элемент внутреннего представления
     * \ref express::BAG_GENERIC "множества BAG" по индексу
     *
     * \param [in] index индекс уникального элемента внутреннего представления множества.
     * \return константную ссылку на уникальный элемент \ref express::BAG_GENERIC "множества BAG".
     */
    virtual const T& get_uniq_element(integer_type index) const override {
      if (index >= static_cast<integer_type>(elements.size())) {
        throw exception{ __MYFUNCNAME__, "index %lli is out of bound %lli", index, elements.size() };
      }
      return elements[static_cast<size_t>(index)].first;
    }

    /**
     * \brief Получить количество уникальных элементов внутреннего представления
     * \ref express::BAG_GENERIC "множества BAG" по индексу
     *
     * \param [in] index индекс уникального элемента внутреннего представления множества.
     * \return количество уникальных элементов внутреннего представления
     * \ref express::BAG_GENERIC "множества BAG".
     */
    virtual integer_type get_uniq_count(integer_type index) const override {
      if (index >= static_cast<integer_type>(elements.size())) {
        throw exception{ __MYFUNCNAME__, "index %lli is out of bound %lli", index, elements.size() };
      }
      return elements[static_cast<size_t>(index)].second;
    }

   /**
    * \brief Получить количество уникальных элементов \ref express::BAG_GENERIC "множества BAG"
    *
    * \return количество уникальных элементов \ref express::BAG_GENERIC "множества BAG".
    */
    virtual integer_type get_uniq_size() const override {
      return static_cast<integer_type>(elements.size());
    }

    /**
     * \brief Получить константную ссылку на элемент внутреннего представления
     * \ref express::BAG_GENERIC "множества BAG"
     *
     * \param [in] index индекс элемента внутреннего представления множества.
     * \return константную ссылку на элемент множества.
     */
    virtual const T& get_constant_internal_element(integer_type index) const override {
      if (index >= size) {
        throw exception{ __MYFUNCNAME__, "index %lli is out of border %lli", index, size };
      }

      integer_type cnt_next, cnt = 0;
      for (auto i = elements.cbegin(); i != elements.cend(); ++i) {
        cnt_next = cnt + (*i).second;
        if (index >= cnt && index < cnt_next) {
          return (*i).first;
        }
        cnt = cnt_next;
      }
      throw exception{ __MYFUNCNAME__, "internal error - execution shall not reach this line" };
    }

    /**
     * \brief Получить ссылку на элемент внутреннего представления множества
     * \param [in] index индекс требуемого элемента множества.
     * \return ссылку на на элемент внутреннего представления множества.
     */
    virtual T& get_internal_element([[maybe_unused]] integer_type index) override {
      throw exception{ __MYFUNCNAME__, "BAG can not use left-side indexing" };
    }

    /**
     * \brief Получить итератор внутреннего представления множества с элементом, равным rhs
     * \param [in] rhs Искомый элемент, переданный в виде ссылки на тип GENERIC.
     * \param [in] compare_instance true, если необходимо сравнивать экземпляры и false,
     * если необходимо сравнивать значения.
     * \return результат поиска: TRUE, если элемент найден, FALSE если не найден и UNKNOWN, если
     * элемент не найден, но были один или несколько результатов сравнения UNKNOWN, а также
     * итератор, указывающий на найденный элемент.
     */
    auto find_same_element(const GENERIC& rhs, bool compare_instance = false);
#if 0
    /**
     * \brief Проверить, является ли элемент rhs уникальным для множества
     *
     * \param [in] rhs проверяемый элемент.
     * \return true, если элемент rhs уникален, и false, если нет.
     *
     * Проверка заключается в сравнении с уникальными элементами множества. Если хотя бы один
     * элемент множества равен проверяемому, то проверяемый элемент не является уникальным.
     *
     * Элемент, имеющий неопределённое (<B>?</B>) значение, всегда уникален, так как
     * возвращает значение \ref express::UNKNOWN "UNKNOWN" при сравнении с любым элементом,
     * что интерпретируется как отличие.
     */
    bool is_unique(const T& rhs) const {
      if (!determinated || !rhs.is_determinated()) return true;

      for (auto i = elements.cbegin(); i != elements.cend(); ++i) {
        if (((*i).first == rhs).is_true()) return false;
      }
      return true;
    }
#endif
  public:

    /**
     * \brief Конструктор множества, имеющего неопределённое (<B>?</B>) значение
     * \param [in] Bound_1 минимальное число элементов, которое может содержаться в множестве.
     * По умолчанию ноль.
     * \param [in] Bound_2 максимальное число элементов, которое может содержаться в множестве.
     * По умолчанию имеет неопределённое значение.
     */
    explicit BAG(const INTEGER& Bound_1 = INTEGER(0), const INTEGER& Bound_2 = INTEGER()) : BAG_GENERIC(Bound_1, Bound_2) {
      append_to_parent_type_list();

#ifdef TRACE_BAG
      printf("%s\n", __MYFUNCNAME__);
#endif


      size = 0;
    }

    /** \brief Деструктор множества по умолчанию */
    virtual ~BAG() = default;

    /**
     * \brief Оператор индексирования (\ref p11_s12_6_1 "ГОСТ Р ИСО 10303-11-2009, 12.6.1")
     * \param [in] index Значение индекса возвращаемого значения.
     * \return ссылка на элемент множества, находящийся по указанному индексу или на неопределённый тип данных,
     * если индекс или элемент имеют неопределённое значение. 
     * (можно использовать только в правой части присваивания)
     */
    virtual const T& operator[](const INTEGER& index) const override {
      return dynamic_cast<const T&>(AGGREGATE_GENERIC::operator[](index));

    }

    /**
     * \brief Уточнение элементом (\ref p11_s13_3_2 "ГОСТ Р ИСО 10303-11-2009, 13.3.2")
     * \return ссылка на элемент множества, находящийся по указанному индексу или на неопределённый тип данных,
     * если индекс или элемент имеют неопределённое значение. 
     * (можно использовать и в левой части присваивания)
     */
    virtual T& operator[](const INTEGER&) override {
      throw exception{__MYFUNCNAME__, "BAG can not be qualified by index (left-side indexing)" };
    }

    /**
     * \brief Присвоение множеству значений при помощи инициализатора (\ref p11_s12_6_1 "ГОСТ Р ИСО 10303-11-2009, 12.9")
     * \param [in] Elements перечень элементов, инициализирующих множество.
     * \return ссылку на инициализированное множество, как требует operator=()
     *
     * Количество элементов инициализатора не может превышать максимальный размер множества,
     * если он задан.
     *
     * Количество элементов инициализатора может быть меньше минимального размера множества,
     * если он задан.
     *
     * Инициализатор не может содержать элементы, имеющие неопределённые значения.
     */
    BAG& operator=(std::initializer_list<T> Elements) {

#ifdef TRACE_BAG
      printf("%s(", __MYFUNCNAME__);
      if (bound_1.is_determinated()) printf("%lli ", bound_1.get_integer_value()); else printf("? ");
      if (bound_2.is_determinated()) printf("%lli ", bound_2.get_integer_value()); else printf("? ");
      printf(") := { %s }\n", (*Elements.begin()).get_type_name().c_str());
#endif


      if (bound_2.is_determinated() && static_cast<integer_type>(Elements.size()) > bound_2.get_integer_value()) {
        throw exception{__MYFUNCNAME__, "initializer_list shall not be greater than maximal BAG size"};
      }

      if (static_cast<integer_type>(Elements.size()) < bound_1.get_integer_value()) {
        throw exception{__MYFUNCNAME__, "initializer_list shall not be less than minimal BAG size"};
      }

      determinated = true;
      elements.clear();
      size_t n = 0;
      for (auto& i : Elements) {
        if (!i.is_determinated()) {
          throw exception{__MYFUNCNAME__, "initializer_list element at pos. %i shall not be indetrminated in BAG", n};
        }
        auto [found, iter] = find_same_element(i);
        if (found == LOGICAL::TRUE) {
          iter->second++;
        } else {
          elements.push_back({ i, 1 });
        }
        n++;
      }
      size = static_cast<integer_type>(Elements.size());
      return *this;
    }

    /**
     * \brief Объединение множества с множеством (ГОСТ Р ИСО 10303-11-2009, 12.6.3)
     * \param [in] rhs множество, добавляемое к текущему множеству.
     * \return множество, созданное из текущего добавлением множества rhs
     *
     * Если какой-либо из операндов имеет неопределенное (?) значение, то результат будет также иметь
     * неопределённое (?) значение.
     *
     * Добавлять можно только множество с элементами совместимого типа.
     */
    BAG operator+(const BAG& rhs) const {

#ifdef TRACE_BAG
      printf("%s(", __MYFUNCNAME__);
      if (bound_1.is_determinated()) printf("%lli ", bound_1.get_integer_value()); else printf("? ");
      if (bound_2.is_determinated()) printf("%lli ", bound_2.get_integer_value()); else printf("? ");
      printf(") + %s\n", rhs.get_type_name().c_str());
#endif

      if (determinated && rhs.determinated) {
        BAG result(*this);

        for (auto i = rhs.elements.cbegin(); i != rhs.elements.cend(); ++i) {
          auto[found, iter] = result.find_same_element(i->first);
          if (found == LOGICAL::TRUE) {
            iter->second += i->second;
          } else {
            result.elements.push_back({ T(i->first), i->second });
          }
        }
        result.size += rhs.size;

        return result;
      } else {
        BAG result;
        return result;
      }
    }

    /**
     * \brief Объединение множества с элементом (ГОСТ Р ИСО 10303-11-2009, 12.6.3)
     * \param [in] rhs добавляемый к теущему множеству элемент совместимого с T типа
     * \return множество, созданное из текущего добавлением элемента rhs
     *
     * Если какой-либо из операндов имеет неопределенное (?) значение, то результат будет также иметь
     * неопределённое (?) значение.
     *
     * Добавлять можно только элемент совместимого типа.
     */
    BAG operator+(const T& rhs) const {

#ifdef TRACE_BAG
      printf("%s(", __MYFUNCNAME__);
      if (bound_1.is_determinated()) printf("%lli ", bound_1.get_integer_value()); else printf("? ");
      if (bound_2.is_determinated()) printf("%lli ", bound_2.get_integer_value()); else printf("? ");
      printf(") + %s\n", rhs.get_type_name().c_str());
#endif

      if (determinated && rhs.is_determinated()) {
        BAG result(*this);

        auto [found, iter] = result.find_same_element(rhs);
        if (found == LOGICAL::TRUE) {
          iter->second++;
        } else {
          result.elements.push_back({ rhs, 1 });
        }
        result.size ++;

        return result;
      } else {
        BAG result;
        return result;
      }
    }

    /**
     * \brief Объединение элемента с множеством (ГОСТ Р ИСО 10303-11-2009, 12.6.3)
     * \param [in] Element слагаемое --- добавляемый к множеству элемент совместимого с T типа.
     * \param [in] Bag слагаемое --- множество с элементами типа T.
     * \return множество, созданное из элемента Element и множества Bag.
     *
     * Если какой-либо из операндов имеет неопределенное (?) значение, то результат будет также иметь
     * неопределённое (?) значение.
     *
     * Складывать можно только элемент с множеством, имеющим элементы совместимого типа.
     */
    friend BAG<T> operator+(const T& Element, const BAG& Bag) {
      return Bag.operator+(Element);
    }

    /**
     * \brief Объединение множества с набором (ГОСТ Р ИСО 10303-11-2009, 12.6.3)
     * \param [in] rhs набор, добавляемый к текущему множеству.
     * \return множество, созданное из текущего добавлением набора rhs
     *
     * Если какой-либо из операндов имеет неопределенное (?) значение, то результат будет также иметь
     * неопределённое (?) значение.
     *
     * Добавлять можно только набор с элементами совместимого типа.
     */
    BAG operator+(const SET<T>& rhs) const {

#ifdef TRACE_BAG
      printf("%s(", __MYFUNCNAME__);
      if (bound_1.is_determinated()) printf("%lli ", bound_1.get_integer_value()); else printf("? ");
      if (bound_2.is_determinated()) printf("%lli ", bound_2.get_integer_value()); else printf("? ");
      printf(") + %s\n", rhs.get_type_name().c_str());
#endif


      if (determinated && rhs.determinated) {
        BAG result(*this);

        for (auto i = rhs.elements.cbegin(); i != rhs.elements.cend(); ++i) {
          auto [found, iter] = result.find_same_element(*i);
          if (found == LOGICAL::TRUE) {
            iter->second++;
          } else {
            result.elements.push_back({ *i, 1 });
          }
        }
        result.size += rhs.get_elements_size();

        return result;
      } else {
        BAG result;
        return result;
      }
    }

    /**
     * \brief Объединение множества со списком (ГОСТ Р ИСО 10303-11-2009, 12.6.3)
     * \param [in] rhs список, добавляемый к текущему множеству.
     * \return множество, созданное из текущего добавлением списка rhs
     *
     * Если какой-либо из операндов имеет неопределенное (?) значение, то результат будет также иметь
     * неопределённое (?) значение.
     *
     * Добавлять можно только список с элементами совместимого типа.
     */
    BAG operator+(const LIST<T>& rhs) const {

#ifdef TRACE_BAG
      printf("%s(", __MYFUNCNAME__);
      if (bound_1.is_determinated()) printf("%lli ", bound_1.get_integer_value()); else printf("? ");
      if (bound_2.is_determinated()) printf("%lli ", bound_2.get_integer_value()); else printf("? ");
      printf(") + %s\n", rhs.get_type_name().c_str());
#endif


      if (determinated && rhs.determinated) {
        BAG result(*this);

        for (auto i = rhs.elements.cbegin(); i != rhs.elements.cend(); ++i) {
          auto [found, iter] = result.find_same_element(*i);
          if (found == LOGICAL::TRUE) {
            iter->second++;
          } else {
            result.elements.push_back({ *i, 1 });
          }
        }
        result.size += rhs.get_elements_size();

        return result;
      } else {
        BAG result;
        return result;
      }
    }

    /**
     * \file
     * \todo Добавить операцию '*'
     */


    /**
     * \file
     * \todo Добавить операцию '-'
     */

    /**
     * \file
     * \todo Добавить операцию '<='
     */

    /**
     * \file
     * \todo Добавить операцию '=>'
     */


    /**
     * \brief Присвоение множеству значений другого множества или набора (\ref p11_s13_3 "ГОСТ Р ИСО 10303-11-2009, 13.3")
     * \param [in] rhs Множество или набор, элементы которого присваиваются текущему множеству.
     * \return ссылку на множество, как требует operator=()
     *
     * Тип элементов множества или набора rhs должен быть совместим (быть одинаковым или быть подтипом
     * или быть конкретизацией) с типом элементов текущего множества или быть значением для
     * типа элементов текущего множества (см. \ref p11_s13_3_2 "п.13.3.2") --- эта проверка
     * выполняется на этапе компиляции, присваивание обеспечивается конструктором элемента текущего
     * множества из элемента множества или набора rhs.
     *
     * Количество элементов множества или набора rhs не должно быть больше максимально возможнго
     * размера текущего множества.
     *
     * Количество элементов множества или набора rhs не должно быть меньше минимально возможнго
     * размера текущего множества.
     *
     * Если множество или набор rhs имеет неопределённое значение, текущему множеству присваивается
     * неопределённое значение.
     *
     */
    BAG& operator=(const BAG_GENERIC& rhs) {

#ifdef TRACE_BAG
      printf("%s(", __MYFUNCNAME__);
      if (bound_1.is_determinated()) printf("%lli ", bound_1.get_integer_value()); else printf("? ");
      if (bound_2.is_determinated()) printf("%lli ", bound_2.get_integer_value()); else printf("? ");
      printf(") := %s\n", rhs.get_type_name().c_str());
#endif

      /* Выполнить проверки */
      if (!rhs.determinated) {
        determinated = false;
        elements.clear();
        size = 0;
        return *this;
      }
      if (bound_2.is_determinated() && rhs.get_elements_size() > bound_2.get_integer_value()) {
        throw exception{__MYFUNCNAME__, "rhs size shall not be greater than maximal BAG size"};
      }
      if (rhs.get_elements_size() < bound_1.get_integer_value()) {
        throw exception{__MYFUNCNAME__, "rhs size shall not be less than minimal BAG size"};
      }

      /* Скопировать элементы */
      determinated = true;
      elements.clear();
      for (integer_type n = 0; n < rhs.get_uniq_size(); ++n) {
        const T& t = T(dynamic_cast<const T&>(rhs.get_uniq_element(n)));
        elements.emplace_back(std::pair(t, rhs.get_uniq_count(n)));
      }
      size = rhs.get_elements_size();
      return *this;
    }

    friend class LIST<T>;
    friend class SET<T>;
  };
}