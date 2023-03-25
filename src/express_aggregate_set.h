/**
 * \file
 * \brief Файл с описанием агрегированного типа данных \ref express::SET_GENERIC "SET (набор)" языка EXPRESS
 * (ГОСТ Р ИСО 10303-11-2009, 8.2.4)
 */

namespace express {

  /**
   * \brief Тип данных \ref express::SET_GENERIC "SET (набор)" (ГОСТ Р ИСО 10303-11-2009, 8.2.4)
   *
   * \anchor p11_s8_2_4
   *
   * \ref express::SET_GENERIC "8.2.4 Тип данных SET"
   *
   * Областью определения типа данных \ref express::SET_GENERIC "SET" являются неупорядоченные совокупности подобных
   * элементов. Тип данных \ref express::SET_GENERIC "SET" является конкретизацией типа данных \ref express::BAG "BAG". Необязательные нижняя и верхняя
   * границы, задаваемые выражениями, имеющими целочисленные значения, определяют минимальное и
   * максимальное число элементов в совокупности, определённой типом данных \ref express::SET_GENERIC "SET". Определённая типом
   * данных \ref express::SET_GENERIC "SET" совокупность не должна содержать двух или более одинаковых элементов.
   \verbatim
     Синтаксис:
      303 set_type = SET [ bound_spec ] OF instantiable_type.
      185 bound_spec = '[' bound_1 ':' bound_2 ']'.
      183 bound_1 = numeric_expression.
      184 bound_2 = numeric_expression.
   \endverbatim
   *
   * Правила и ограничения:
   *
   * a) Выражение <B>bound_1</B> должно иметь целочисленное значение, большее или равное нулю. Оно
   * задаёт нижнюю границу, определяющую минимальное число элементов, которое может содержаться в
   * экземпляре набора этого типа данных. Выражение <B>bound_1</B> не должно иметь неопределённого (<B>?</B>) значения.
   *
   * b) Выражение <B>bound_2</B> должно иметь целочисленное значение, большее или равное значению
   * <B>bound_1</B>, либо неопределённое (<B>?</B>) значение. Оно задаёт верхнюю границу, определяющую
   * максимальное число элементов, которое может содержаться в экземпляре набора этого типа данных. Если
   * значение данного выражения является неопределённым (<B>?</B>), то число элементов в экземпляре набора
   * этого типа данных не ограничено сверху.
   *
   * c) Если элемент <B>bound_spec</B> опущен, то границы набора определяются как <B>[0:?]</B>.
   *
   * d) Каждый элемент в экземпляре типа данных \ref express::SET_GENERIC "SET" должен отличаться (то есть не являться
   * эквивалентным экземпляром) от любого другого элемента того же экземпляра набора.
   *
   * <B><I>Пример --- В данном примере атрибут </I>a_set_of_points<I> определён как набор объектов </I>point<I>
   * (объекты point относятся к именованному типу данных, который объявлен в другом месте).</I>
   <PRE>
     a_set_of_points : \ref express::SET_GENERIC "SET" OF point;
   </PRE>
   * <I>Атрибут </I>a_set_of_points<I> может содержать ни одного или несколько объектов </I>point<I>. Каждый
   * экземпляр объекта </I>point<I> (в экземпляре набора) должен отличаться от любого другого объекта
   * </I>point<I> в наборе.
   *
   * Если требуется, чтобы набор содержал не более 15 объектов </I>point<I>, то в спецификации верхняя
   * граница должна быть определена следующим образом:</I>
   <PRE>
     a_set_of_points : \ref express::SET_GENERIC "SET" [0:15] OF point;
   </PRE>
   * <I>Теперь экземпляр атрибута </I>a_set_of_points<I> может содержать не более 15 точек.</I></B>
   *
   */
  class SET_GENERIC : public BAG_GENERIC {

  protected:

    /**
     * \brief Получить тип данных набора
     * \return тип данных набора в виде элемента перечисления OBJTYPE.
     */
    virtual OBJTYPE objtype() const override;

  public:

    /**
     * \brief Конструктор набора, имеющего неопределённое (<B>?</B>) значение
     * \param [in] Bound_1 минимальное число элементов, которое может содержаться в наборе.
     * По умолчанию ноль.
     * \param [in] Bound_2 максимальное число элементов, которое может содержаться в наборе.
     * По умолчанию имеет неопределённое значение.
     */
    explicit SET_GENERIC(const INTEGER& Bound_1 = INTEGER(0), const INTEGER& Bound_2 = INTEGER());

    /**
     * \brief Деструктор \ref express::SET_GENERIC "набора SET" --- по умолчанию
     */
    virtual ~SET_GENERIC() = default;

    friend class AGGREGATE_GENERIC;
  };

  /**
   * \brief Шаблон для типа данных \ref express::SET_GENERIC "SET (набор)" (ГОСТ Р ИСО 10303-11-2009, 8.2.4),
   * специализированного для хранения дочернего для типа GENERIC типа данных
   */
  template<class T>
  class SET : public SET_GENERIC {

  protected:

    /**
     * \brief Внутреннее представление элементов набора
     */
    std::vector<T> elements;

    /**
     * \brief Элемент, имеющий неопределённое значение
     */
    inline static const T undef = T();

    virtual const T& get_undef() const override final {
      return undef;
    }

    /**
     * \brief Получить константную ссылку на элемент внутреннего представления набора
     * \param [in] index индекс требуемого элемента набора.
     * \return константную ссылку на элемент внутреннего представления набора.
     */
    virtual const T& get_constant_internal_element(integer_type index) const override final {
      if (index >= static_cast<integer_type>(elements.size())) {
        throw exception{__MYFUNCNAME__, "index %lli is out of bound %lli", index, elements.size()};
      }
      return elements[static_cast<size_t>(index)];
    }

    /**
     * \brief Получить ссылку на элемент внутреннего представления набора
     * \param [in] index индекс требуемого элемента набора.
     * \return ссылку на на элемент внутреннего представления набора.
     */
    virtual T& get_internal_element(integer_type index) override final {
      throw exception{ __MYFUNCNAME__, "SET can not use left-side indexing [%lli]", index };
    }
#if 0
    /**
     * \brief Проверить, является ли элемент rhs уникальным для набора
     * \param [in] rhs проверяемый элемент.
     * \return true, если элемент rhs уникален, и false, если нет.
     *
     * Проверка заключается в сравнении с элементами набора. Если хотя бы один
     * элемент набора равен проверяемому, то проверяемый элемент не является уникальным.
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
     * \brief Получить количество элементов внутреннего представления набора
     * \return количество элементов внутреннего представления набора.
     */
    virtual integer_type get_elements_size() const override final {
      return static_cast<integer_type>(elements.size());
    }

  public:

    /**
     * \brief Конструктор набора, имеющего неопределённое (<B>?</B>) значение
     * \param [in] Bound_1 минимальное число элементов, которое может содержаться в наборе.
     * По умолчанию ноль.
     * \param [in] Bound_2 максимальное число элементов, которое может содержаться в наборе.
     * По умолчанию имеет неопределённое значение.
     */
    explicit SET(const INTEGER & Bound_1 = INTEGER(0), const INTEGER & Bound_2 = INTEGER()) : SET_GENERIC(Bound_1, Bound_2) {
      GENERIC::append_to_parent_type_list();
    }

    /**
     * \brief Деструктор набора --- по умолчанию
     */
    virtual ~SET() = default;

    /**
     * \brief Оператор индексирования (\ref p11_s12_6_1 "ГОСТ Р ИСО 10303-11-2009, 12.6.1")
     * \param [in] index Значение индекса возвращаемого значения.
     * \return ссылка на элемент набора, находящийся по указанному индексу или на неопределённый тип данных,
     * если индекс или элемент имеют неопределённое значение. 
     * (можно использовать только в правой части присваивания)
     */
    virtual const T& operator[](const INTEGER& index) const override final {
      return dynamic_cast<const T&>(AGGREGATE_GENERIC::operator[](index));
    }

    /**
     * \brief Уточнение элементом (\ref p11_s13_3_2 "ГОСТ Р ИСО 10303-11-2009, 13.3.2")
     * \return ссылка на элемент набора, находящийся по указанному индексу или на неопределённый тип данных,
     * если индекс или элемент имеют неопределённое значение. 
     * (можно использовать и в левой части присваивания)
     */
    virtual T& operator[](const INTEGER&) override final {
      throw exception{__MYFUNCNAME__, "SET can not be qualified by index (left-side indexing)"};
    }

   /**
    * \brief Присвоение набору значений при помощи инициализатора (\ref p11_s12_6_1 "ГОСТ Р ИСО 10303-11-2009, 12.9")
    * \param [in] Elements перечень элементов, инициализирующих набор.
    * \return ссылку на инициализированный набор, как требует operator=()
    *
    * Количество элементов инициализатора не может превышать максимальный размер набора,
    * если он задан.
    *
    * Количество элементов инициализатора может быть меньше минимального размера набора,
    * если он задан.
    *
    * Инициализатор не может содержать элементы, имеющие неопределённые значения.
    *
    * Элементы инициализатора должны быть уникальными.
    */
   SET& operator=(std::initializer_list<T> Elements) {
      if (static_cast<integer_type>(Elements.size()) > AGGREGATE_GENERIC::bound_2.get_integer_value()) {
        throw exception{__MYFUNCNAME__, "SET::operator=(std::initializer_list): initializer_list shall not be greater than maximal SET size"};
      }
      if (static_cast<integer_type>(Elements.size()) < AGGREGATE_GENERIC::bound_1.get_integer_value()) {
        throw exception{__MYFUNCNAME__, "SET::operator=(std::initializer_list): initializer_list shall not be less than minimal SET size"};
      }
      AGGREGATE_GENERIC::determinated = true;
      elements.clear();
      size_t n = 0;
      for (auto& i : Elements) {
        if (!AGGREGATE_GENERIC::optional && !i.is_determinated()) {
          throw exception{__MYFUNCNAME__, "initializer_list element at pos. %i shall not be indetrminated in SET defined as Not OPTIONAL", n};
        }
        if (AGGREGATE_GENERIC::uniq && !is_unique(i)) {
          throw exception{__MYFUNCNAME__, "initializer_list element at pos. %i shall be unique in SET defined as Not UNIQUE", n};
        }
        elements.push_back(i);
        n++;
      }
      return *this;
    }

//!!! Объединение: если правый операнд является пакетом, списком или набором,
//!!! элементы которого совместимы с базисным типом данных левого операнда, то результат формируется
//!!! следующим образом: сначала результату присваивается значение левого операнда, затем по очереди
//!!! рассматриваются элементы правого операнда и, если очередного элемента нет в результирующем наборе, то
//!!! данный элемент добавляется в результирующий набор.


    /**
     * \brief Объединение набора с набором (ГОСТ Р ИСО 10303-11-2009, 12.6.3)
     * \param [in] rhs набор, добавляемое к текущему набору.
     * \return набор, созданный из текущего добавлением набора rhs
     *
     * Если какой-либо из операндов имеет неопределенное (?) значение, то результат будет также иметь
     * неопределённое (?) значение.
     *
     * Добавлять можно только набор с элементами совместимого типа.
     */
    SET operator+(const SET& rhs) const {
      if (is_determinated() && rhs.is_determinated()) {
        SET result(*this);
        result.determinated = true;


        for (auto i = rhs.elements.cbegin(); i != rhs.elements.cend(); ++i) {
          if (result.is_unique(*i)) {
            result.elements.push_back(*i);
          }
        }
        return result;
      } else {
        SET result;
        return result;
      }
    }

    /**
     * \brief Объединение набора с элементом (ГОСТ Р ИСО 10303-11-2009, 12.6.3)
     * \param [in] rhs добавляемый к теущему набору элемент
     * \return набор, созданный из текущего добавлением элемента rhs
     *
     * Если какой-либо из операндов имеет неопределенное (?) значение, то результат будет также иметь
     * неопределённое (?) значение.
     *
     * Добавлять можно только элемент совместимого типа.
     */
    SET operator+(const T& rhs) const {
      if (is_determinated() && rhs.is_determinated()) {
        SET result(*this);
        result.determinated = true;

        if (result.is_unique(rhs)) {
          result.elements.push_back(rhs);
        }
        return result;
      } else {
        SET result;
        return result;
      }
    }

    /**
     * \brief Объединение элемента с набором (ГОСТ Р ИСО 10303-11-2009, 12.6.3)
     * \param [in] Element слагаемое --- элемент.
     * \param [in] Set слагаемое --- набор.
     * \return набор, созданный из элемента Element и набора Set.
     *
     * Если какой-либо из операндов имеет неопределенное (?) значение, то результат будет также иметь
     * неопределённое (?) значение.
     *
     * Складывать можно только элемент с набором, имеющим элементы совместимого типа.
     */
    friend SET<T> operator+(const T& Element, const SET& Set) {
      return Set.operator+(Element);
    }

    /**
     * \brief Объединение набора с множеством (ГОСТ Р ИСО 10303-11-2009, 12.6.3)
     * \param [in] rhs множество, добавляемое к текущему набору.
     * \return набор, созданный из текущего добавлением множества rhs
     *
     * Если какой-либо из операндов имеет неопределенное (?) значение, то результат будет также иметь
     * неопределённое (?) значение.
     *
     * Добавлять можно только множество с элементами совместимого типа.
     */
    SET operator+(const BAG<T>& rhs) const {
      if (is_determinated() && rhs.is_determinated()) {
        SET result(*this);

        /* Перебираются только уникальные элементы BAG, однако необходимо проверить, являются ли они
           уникальными для SET
         */
       for (auto i = rhs.elements.cbegin(); i != rhs.elements.cend(); ++i) {
          if (result.is_unique((*i).first)) {
            result.elements.push_back((*i).first);
          }
        }
        return result;
      }
      else {
        SET result;
       return result;
      }
    }

    /**
     * \brief Объединение набора со списком (ГОСТ Р ИСО 10303-11-2009, 12.6.3)
     * \param [in] rhs список, добавляемый к текущему набору.
     * \return набор, созданный из текущего добавлением списка rhs
     *
     * Если какой-либо из операндов имеет неопределенное (?) значение, то результат будет также иметь
     * неопределённое (?) значение.
     *
     * Добавлять можно только список с элементами совместимого типа.
     */
    SET operator+(const LIST<T>& rhs) const {
      if (is_determinated() && rhs.is_determinated()) {
        SET result(*this);
        result.determinated = true;
        for (auto i = rhs.elements.cbegin(); i != rhs.elements.cend(); ++i) {
          if (result.is_unique(*i)) {
            result.elements.push_back(*i);
          }
        }
        return result;
      }
      else {
        SET result;
    
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
     * \brief Присвоение набору значений другого набора (\ref p11_s13_3 "ГОСТ Р ИСО 10303-11-2009, 13.3")
     * \param [in] rhs Набор, элементы которого присваиваются текущему.
     * \return ссылку на набор, как требует operator=()
     *
     * Тип элементов набора rhs должен быть совместим (быть одинаковым или быть подтипом
     * или быть конкретизацией) с типом элементов текущего набора или быть значением для
     * типа элементов текущего набора (см. \ref p11_s13_3_2 "п.13.3.2") --- эта проверка
     * выполняется на этапе компиляции.
     *
     * Количество элементов набора rhs не должно быть больше максимально возможнго размера текущего набора.
     *
     * Количество элементов набора rhs не должно быть меньше минимально возможнго размера текущего набора.
     *
     * Если набор rhs имеет неопределённое значение, текущему набору присваивается
     * неопределённое значение.
     *
     */
    SET& operator=(const SET_GENERIC& rhs) {

      /* Выполнить проверки */
      if (!rhs.is_determinated()) {
        determinated = false;
        elements.clear();
        return *this;
      }
      if (bound_2.is_determinated() && rhs.get_elements_size() > bound_2.get_integer_value()) {
        throw exception{__MYFUNCNAME__, "SET::operator=(const SET_GENERIC&): rhs size shall not be greater than maximal SET size"};
      }
      if (rhs.get_elements_size() < bound_1.get_integer_value()) {
        throw exception{__MYFUNCNAME__, "SET::operator=(const SET_GENERIC&): rhs size shall not be less than minimal SET size"};
      }

      /* Скопировать элементы */
      determinated = true;
      elements.clear();
      for (auto n = rhs.get_loindex(); n <= rhs.get_hiindex(); ++n) {
        const T& t = T(dynamic_cast<const T&>(rhs[n]));
        elements.push_back(t);
      }

      return *this;
    }

    /**
     * \file
     * \todo Добавить операцию сравнения значеня с SET
     */

    /**
     * \file
     * \todo Добавить операцию сравнения значеня с BAG
     */

//!!! два набора а и b равны тогда и только тогда, когда каждый элемент VALUE_IN а
//!!! встречается в VALUE_IN b равное число раз, а каждый элемент VALUE_IN b также встречается в VALUE_IN а
//!!! равное число раз.


    /**
     * \file
     * \todo Добавить операцию сравнения экземпляра с GENERIC
     */

    /**
     * \file
     * \todo Добавить операцию сравнения экземпляра с SET
     */

    /**
     * \file
     * \todo Добавить операцию сравнения экземпляра с BAG
     */


    friend class BAG<T>;
    friend class LIST<T>;
  };
}