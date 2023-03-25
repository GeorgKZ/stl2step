/**
 * \file
 * \brief Файл с описанием \ref express::AGGREGATE_GENERIC "агрегированного типа данных AGGREGATE_GENERIC" языка EXPRESS
 * (ГОСТ Р ИСО 10303-11-2009, \ref p11_s8_2 "п.8.2")
 *
 * \todo Рассмотреть возможность операций с аггрегатными типами разных базисных типов, наполнение
 * аггрегатного типа элементами разного типа, совместимого с базисным типом.
 */

namespace express {

  template<class T> class ARRAY;
  template<class T> class LIST;
  template<class T> class BAG;
  template<class T> class SET;

  /**
   * \brief Тип данных \ref express::AGGREGATE_GENERIC "AGGREGATE_GENERIC (совокупность)" (ГОСТ Р ИСО 10303-11-2009, 8.2)
   *
   * \ref express::AGGREGATE_GENERIC "8.2 Агрегированные типы данных"
   *
   * Областями определения агрегированных типов данных являются совокупности значений заданного
   * базисного типа данных (см. \ref p11_s8_6_1 "8.6.1"). Эти значения базисного типа данных называются элементами агрегированной
   * совокупности. В языке EXPRESS определены четыре вида агрегированных типов данных: \ref express::ARRAY_GENERIC "ARRAY"
   * (массив), \ref express::LIST "LIST" (список), \ref express::BAG "BAG" (пакет) и \ref express::SET "SET" (набор).
   * Значения каждого вида агрегированного типа данных
   * имеют разные свойства. Тип данных \ref express::AGGREGATE_GENERIC "AGGREGATE_GENERIC" является обобщением этих четырёх видов
   * агрегированных типов данных (см. \ref p11_s9_5_3_1 "9.5.3.1").
   *
   * Тип данных \ref express::ARRAY_GENERIC "ARRAY" представляет упорядоченное множество фиксированного размера, индексированное
   * последовательностью целых чисел.
   *
   * <B><I>Пример --- Матрица преобразования (в геометрии) может быть определена как массив массивов
   * (чисел).</I></B>
   *
   * Тип данных \ref express::LIST "LIST" представляет последовательность элементов, доступ к которым осуществляется по
   * их позициям. Число элементов в списке может изменяться и быть ограничено в определении типа данных.
   *
   * <B><I>Пример --- Операции технологического маршрута могут быть представлены списком. Операции
   * упорядочены и могут быть добавлены или удалены из технологического маршрута.</I></B>
   *
   * Тип данных \ref express::BAG "BAG" представляет неупорядоченное множество, в котором разрешены повторяющиеся
   * элементы. Число элементов в пакете может изменяться и быть ограничено в определении типа данных.
   *
   * <B><I>Пример --- Совокупность крепежных деталей, используемых при сборке, может быть
   * представлено пакетом. В состав его элементов может входить некоторое число одинаковых болтов,
   * но неважно, который из них используется в конкретном отверстии.</I></B>
   *
   * Тип данных \ref express::SET "SET" представляет неупорядоченное множество элементов, в котором нет двух
   * одинаковых элементов. Число элементов в наборе может изменяться и быть ограничено в определении
   * типа данных.
   *
   * <B><I>Пример --- Множество людей во всём мире является набором.</I></B>
   *
   * <SMALL>П&nbsp;р&nbsp;и&nbsp;м&nbsp;е&nbsp;ч&nbsp;а&nbsp;н&nbsp;и&nbsp;е ---
   * Агрегированные типы данных в языке EXPRESS являются одномерными. Объекты,
   * обычно рассматриваемые как многомерные (например, математические матрицы), могут быть представлены
   * агрегированным типом данных, базисным типом которого является другой агрегированный тип данных. Таким
   * образом, агрегированные типы данных могут быть вложенными на произвольную глубину, обеспечивая
   * представление структур данных любой размерности.</SMALL>
   *
   * <B><I>Пример --- Можно определить структуру \ref express::LIST "LIST" [1:3] OF \ref express::ARRAY_GENERIC "ARRAY" [5:10] OF
   * \ref express::INTEGER "INTEGER", которая в действительности является двумерной.</I></B>
   *
   */
  class AGGREGATE_GENERIC : public GENERIC {

  protected:

    /**
     * \brief Нижняя граница, определяющая наименьшее значение индекса (\ref express::ARRAY_GENERIC "ARRAY")
     * или минимальное число элементов,
     * которое может содержаться в совокупности (\ref express::SET "SET", \ref express::LIST "LIST", \ref express::BAG "BAG").
     */
    INTEGER bound_1;

    /**
     * \brief Верхняя граница, определяющая наименьшее значение индекса (\ref express::ARRAY_GENERIC "ARRAY")
     * или максимальное число элементов,
     * которое может содержаться в совокупности (\ref express::SET "SET", \ref express::LIST "LIST",
     * \ref express::BAG "BAG").
     */
    INTEGER bound_2;

    /**
     * \brief Общее количество элементов \ref express::AGGREGATE_GENERIC "совокупности"
     */
    integer_type size;

    /**
     * \brief Этот тип совокупности может содержать неопределённое (<B>?</B>) значение
     *
     * Может быть установлен для \ref express::ARRAY_GENERIC "ARRAY". Для 
     * \ref express::SET "SET", \ref express::LIST "LIST", \ref express::BAG "BAG" должен иметь значение false.
     */
    bool optional;

    /**
     * \brief Каждый элемент совокупности должен отличаться
     * (то есть не быть эквивалентным экземпляром) от любого другого элемента той же совокупности.
     *
     * Может быть установлен для \ref express::ARRAY_GENERIC "ARRAY" и \ref express::LIST "LIST".
     * Для \ref express::SET "SET" должен иметь значение true, для \ref express::BAG "BAG"
     * должен иметь значение false.
     */
    bool uniq;

    /**
     * \brief Этот тип совокупности должен быть упорядочен (порядок элементов в процессе хранения незменен).
     *
     * Для \ref express::ARRAY_GENERIC "ARRAY" и \ref express::LIST "LIST" должен иметь значение true,
     * для \ref express::SET "SET" и \ref express::BAG "BAG" должен иметь значение false.
     */
    bool ordered;

    /**
     * \brief Получить нижний индекс совокупности
     *
     * \return значение нижнего индекса совокупности.
     */
    virtual integer_type get_loindex() const = 0;

    /**
     * \brief Получить верхний индекс совокупности
     *
     * \return значение вернего индекса совокупности.
     */
    virtual integer_type get_hiindex() const = 0;

    /**
     * \brief Получить объявленный нижний индекс объекта типа \ref express::ARRAY_GENERIC "ARRAY" или
     * объявленную нижнюю границу объекта типа \ref express::BAG "BAG", \ref express::LIST "LIST"
     * или \ref express::SET "SET".
     * \return значение нижнего индекса или нижней границы.
     */
    integer_type get_lobound() const;


    /**
     * \brief Проверить, имеет ли значение объявленный верхний индекс объекта типа
     * \ref express::ARRAY_GENERIC "ARRAY" или объявленную верхнюю границу объекта типа
     * \ref express::BAG "BAG", \ref express::LIST "LIST" или \ref express::SET "SET".
     * \return true, если возвращается значение верхнего индекса или значение верхней
     * границы имеет значение, false в противном случае.
     */
    bool is_hibound() const;

    /**
     * \brief Получить объявленный верхний индекс объекта типа \ref express::ARRAY_GENERIC "ARRAY" или
     * объявленную верхнюю границу объекта типа \ref express::BAG "BAG", \ref express::LIST "LIST"
     * или \ref express::SET "SET".
     * \return значение верхнего индекса/верхней границы.
     *
     * Если объявленный верхний индекс/верхняя граница не имеет значения, будет вызвано исключение. 
     */
    integer_type get_hibound() const;

    /**
     * \brief Получить константную ссылку на элемент внутреннего представления
     * \ref express::AGGREGATE_GENERIC "совокупности" по индексу
     *
     * \return константная ссылка на элемент внутреннего представления совокупности,
     * приведённая к const GENERIC.
     */
    const GENERIC& get_constant_internal_element(integer_type index) const;

    /**
     * \brief Получить ссылку на элемент внутреннего представления
     * \ref express::AGGREGATE_GENERIC "совокупности" по индексу
     *
     * \return ссылка на на элемент внутреннего представления совокупности,
     * приведённая к GENERIC.
     */
    GENERIC& get_internal_element(integer_type index);

    /**
     * \brief Получить константную ссылку на уникальный элемент внутреннего представления
     * \ref express::AGGREGATE_GENERIC "совокупности" по "уникальному" индексу
     *
     * \param [in] uniq_index "уникальный" индекс элемента внутреннего представления совокупности.
     * \return константную ссылку на уникальный элемент \ref express::AGGREGATE_GENERIC "совокупности".
     *
     * Эта функция эквивалентна функции get_constant_internal_element для всех агрегатных типов, кроме BAG.
     */
    virtual const GENERIC& get_constant_uniq_element(integer_type uniq_index) const = 0;

    /**
     * \brief Получить ссылку на уникальный элемент внутреннего представления
     * \ref express::AGGREGATE_GENERIC "совокупности" по "уникальному" индексу
     *
     * \param [in] uniq_index "уникальный" индекс элемента внутреннего представления совокупности.
     * \return ссылку на уникальный элемент \ref express::AGGREGATE_GENERIC "совокупности".
     *
     * Эта функция эквивалентна функции get_internal_element для всех агрегатных типов, кроме BAG.
     */
    virtual GENERIC& get_uniq_element(integer_type uniq_index) = 0;

    /**
     * \brief Получить количество одинаковых уникальных элементов
     * внутреннего представления совокупности по "уникальному" индексу
     *
     * \param [in] uniq_index "уникальный" индекс элемента внутреннего представления совокупности.
     * \return количество одинаковых уникальных элементов совокупности.
     * 
     * Эта функция возвращает 1 для всех агрегатных типов, кроме BAG.
     */
    virtual integer_type get_uniq_count(integer_type uniq_index) const = 0;

    /**
     * \brief Получить количество уникальных элементов совокупности
     *
     * \return количество уникальных элементов совокупности.
     *
     * Эта функция эквивалентна функции get_elements_size для всех агрегатных типов,
     * кроме BAG.
     */
    virtual integer_type get_uniq_size() const = 0;

    /**
     * \brief Удалить все элементы из внутреннего представления \ref express::AGGREGATE совокупности
     */
    virtual void clear() = 0;

    /**
     * \brief Дополнить внутреннее представление \ref express::AGGREGATE совокупности элементом
     *
     * \param [in] element Добавляемый элемент, переданный в виде ссылки та тип GENERIC.
     * \param [in] count_of_elements Количество добавляемых одинаковых элементов (для BAG).
     *
     * \warning Эта функция не выполняет проверки правомерности добавления элемента
     * (исходя из допустимого размера совокупности, возможности присутствия неуникальных элементов,
     * возможности присутствия элементов с неопределённым хначением).
     */
    virtual void add_element(const GENERIC& element, integer_type count_of_elements = 1) = 0;

    /**
     * \brief Получить ссылку на элемент совокупности, имеющий неопределённое значение
     *
     * \return ссылку на элемент совокупности, имеющий неопределённое значение.
     */
    virtual const GENERIC& get_undef() const = 0;

    /**
     * \brief Получить "уникальный" индекс элемента совокупности, равного rhs
     * \param [in] rhs Искомый элемент, переданный в виде ссылки на тип GENERIC.
     * \param [in] compare_value true, если необходимо сравнивать значения и false,
     * если необходимо сравнивать экземпляры.
     * \return результат поиска: больше или равно нулю, если найден "уникальный" индекс элемента,
     * равного rhs, -1, если такой элемент не найден, и -2, если сравнение имело
     * неопределённый результат.
     */
    integer_type find_same_element(const GENERIC& rhs, bool compare_value = false) const;

    /**
     * \brief Проверить наличие в совокупности элемента, равного rhs
     * \param [in] rhs Искомый элемент, переданный в виде ссылки на тип GENERIC.
     * \param [in] compare_value true, если необходимо сравнивать значения и false,
     * если необходимо сравнивать экземпляры элементов.
     * \return результат поиска: положительное число --- количество одинаковых найденных элементов,
     * если таковые найдены (для множества, иначе 1), 0, если ни одного элемента не найдено и
     * отрицательное число, если элемент не найден, но были один или несколько результатов
     * непределённого сравнения.
     */
    integer_type check_same_element(const GENERIC& rhs, bool compare_value) const;

    /**
     * \brief Проверить, является ли элемент rhs уникальным в совокупности
     * \param [in] rhs проверяемый элемент, переданный в виде ссылки на тип GENERIC.
     * \return true, если элемент rhs уникален в совокупности, и false, если нет.
     *
     * Проверка заключается в сравнении с элементами совокупности. Если хотя бы один
     * элемент совокупности равен (является эквивалентным экземпляром) проверяемому,
     * то проверяемый элемент не является уникальным.
     *
     * Элемент, имеющий неопределённое (<B>?</B>) значение, всегда уникален, так как
     * возвращает значение \ref express::UNKNOWN "UNKNOWN" при сравнении с любым элементом,
     * что интерпретируется как отличие.
     */
    bool is_unique(const GENERIC& rhs) const;

    /**
     * \brief Проверка равенства значения или экземпляра с неизвестным типом
     * 
     * \param [in] rhs Объект, с которым выполняется сравнение.
     * \param [in] compare_value true, если необходимо сравнивать значения и false,
     * если необходимо сравнивать экземпляры.
     * \return результат проверки равенства значений или экземпляров.
     *
     * Неизвестный тип передан как ссылка на базовый тип GENERIC.
     */
    virtual LOGICAL is_equal(const GENERIC& rhs, bool compare_value) const override;

    /**
     * \brief Проверить совместимость (ГОСТ Р ИСО 10303-11-2009, \ref p11_s12_11 "п.12.11")
     * агрегатного типа с некоторым типом.
     *
     * \param [in] rhs Тип, с которым будет произведено сравнение, переданный в виде ссылки
     * на тип GENERIC.
     * \return результат сравнения типов в виде перечисления COMPAT.
     */
    virtual COMPAT check_compatibility(const GENERIC& rhs) const override;

  public:

    /**
     * \brief Конструктор по умолчанию совокупности, имеющей неопределённое (<B>?</B>) значение
     */
    AGGREGATE_GENERIC();

    /**
     * \brief Конструктор совокупности, имеющей неопределённое (<B>?</B>) значение
     * \param [in] Bound_1 нижнее значение индекса/границы совокупности
     * \param [in] Bound_2 верхнее значение индекса/границы совокупности
     */
    AGGREGATE_GENERIC(const INTEGER& Bound_1, const INTEGER& Bound_2);

    /**
     * \brief Не установлен ни один флаг.
     */
    static const unsigned NONE     = 0x00;

    /**
     * \brief Если этот флаг установлен, то совокупность не может содержать одинаковые
     * значения (отличаться (different from), а не иметь ), если не установлен, то может.
     */
    static const unsigned UNIQUE   = 0x01;

    /**
     * \brief Если этот флаг установлен, то совокупность может содержать неопределённые (?)
     * значения, если не установлен, то совокупность не должна содержать неопределённых (?) значений.
     */
    static const unsigned OPTIONAL = 0x02;

    /**
     * \brief Деструктор совокупности --- по умолчанию
     */
    virtual ~AGGREGATE_GENERIC() = default;

    /**
     * \brief Получить общее количество элементов \ref express::AGGREGATE_GENERIC "совокупности"
     *
     * \return общее количество элементов \ref express::AGGREGATE_GENERIC "совокупности".
     */
    integer_type get_elements_size() const;

    /**
     * \brief Оператор индексирования (\ref p11_s12_6_1 "ГОСТ Р ИСО 10303-11-2009, 12.6.1")
     * \param [in] index Значение индекса возвращаемого значения.
     * \return ссылка на элемент совокупности, находящийся по указанному индексу или на неопределённый тип данных,
     * если индекс или элемент (если это разрешено) имеют неопределённое значение. 
     *
     * Этот оператор используется только в правой части присваивания.
     */
    virtual const GENERIC& operator[](const INTEGER& index) const;

    /**
     * \brief Уточнение элементом (\ref p11_s13_3_2 "ГОСТ Р ИСО 10303-11-2009, 13.3.2")
     * \param [in] index Значение индекса возвращаемого значения.
     * \return ссылка на элемент совокупности, находящийся по указанному индексу или на неопределённый тип данных,
     * если индекс или элемент имеют неопределённое значение. 
     *
     * Этот оператор можно использовать и в правой, и в левой части присваивания.
     * \warning Внимание! При использовании этого оператора не проверются правила присвоения элемента
     * совокупности (уникальность, определённость и т.д.). Для присвоения с проверкой необходимо использовать
     * функцию \ref express::AGGREGATE_GENERIC::set_element(const express::INTEGER&, const express::GENERIC&) "set_element".
     */
    virtual GENERIC& operator[](const INTEGER& index);

    /**
     * \brief Уточнение элементом (\ref p11_s13_3_2 "ГОСТ Р ИСО 10303-11-2009, 13.3.2")
     *
     * \param [in] index Значение индекса изменяемого элемента.
     * \param [in] element Присваиваемый элемент.
     *
     * Этот оператор, в отличие от оператора  \ref express::AGGREGATE_GENERIC::operator[](const express::INTEGER&) "operator[]",
     * выполняет при выполнения присвоении элемента необходимые проверки (уникальность,
     * определённость и т.д.).
     */
    void set_element(const INTEGER& index, const GENERIC& element);

    /**
     * \brief Вывести в виде строки значение типа (как атрибут объектного типа)
     * 
     * \return строковое представление значения типа.
     *
     * Если тип данных совокупности имеет необязательные (OPTIONAL) элементы, любой элемент,
     * для которого отсутствует значение, должен быть закодирован знаком доллара “ $”.
     */
    virtual std::string print_value() const override;

    /**
     * \brief Получить имя базисного типа совокупности
     *
     * \return имя базисного типа совокупности.
     */
    const std::string get_value_type_name() const;

    friend INTEGER HIBOUND(const AGGREGATE_GENERIC& V);
    friend INTEGER LOBOUND(const AGGREGATE_GENERIC& V);
    friend INTEGER HIINDEX(const AGGREGATE_GENERIC& V);
    friend INTEGER LOINDEX(const AGGREGATE_GENERIC& V);
    friend INTEGER SIZEOF(const AGGREGATE_GENERIC& V);
    friend LOGICAL IN(const GENERIC& v, const AGGREGATE_GENERIC& agg);
    friend LOGICAL VALUE_IN(const AGGREGATE_GENERIC& C, const GENERIC& V);
  };

  template<class T>
  class AGGREGATE : virtual public AGGREGATE_GENERIC {

  protected:

    /**
     * \brief Внутреннее представление элементов \ref express::AGGREGATE совокупности
     */
    std::vector<std::pair<T, integer_type>> elements;

    /**
     * \brief Элемент \ref express::AGGREGATE совокупности, имеющий неопределённое значение
     */
    inline static const T undef = T();

    /**
     * \brief Получить ссылку на элемент \ref express::AGGREGATE совокупности,
     * имеющий неопределённое значение
     * 
     * \return ссылка на элемент\ref express::AGGREGATE совокупности,
     * имеющий неопределённое значение.
     */
    virtual const T& get_undef() const override {
      return undef;
    }

    /**
     * \brief Получить константную ссылку на уникальный элемент внутреннего представления
     * \ref express::AGGREGATE совокупности по "уникальному" индексу
     *
     * \param [in] uniq_index "уникальный" индекс элемента внутреннего представления совокупности.
     * \return константную ссылку на уникальный элемент  \ref express::AGGREGATE совокупности.
     * 
     * Эта функция эквивалентна функции get_constant_internal_element для агрегатных типов кроме BAG.
     */
    virtual const T& get_constant_uniq_element(integer_type uniq_index) const override {
      if (uniq_index >= size) {
        throw exception{ __MYFUNCNAME__, "uniq_index %lli is out of bound %lli", uniq_index, size };
      }
      return elements[static_cast<size_t>(uniq_index)].first;
    }

    /**
     * \brief Получить ссылку на уникальный элемент внутреннего представления
     * \ref express::AGGREGATE совокупности по "уникальному" индексу
     *
     * \param [in] uniq_index "уникальный" индекс элемента внутреннего представления совокупности.
     * \return ссылку на уникальный элемент \ref express::AGGREGATE совокупности.
     *
     * Эта функция эквивалентна функции get_internal_element для всех агрегатных типов кроме BAG.
     */
    virtual T& get_uniq_element(integer_type uniq_index) override {
      if (uniq_index >= size) {
        throw exception{ __MYFUNCNAME__, "uniq_index %lli is out of bound %lli", uniq_index, size };
      }
      return elements[static_cast<size_t>(uniq_index)].first;
    }

    /**
     * \brief Получить количество уникальных элементов внутреннего представления
     * \ref express::AGGREGATE совокупности по индексу
     *
     * \param [in] uniq_index "уникальный" индекс элемента внутреннего представления совокупности.
     * \return количество уникальных элементов внутреннего представления
     * \ref express::AGGREGATE совокупности.
     * 
     * Эта функция возвращает единицу для всех агрегатных типов кроме BAG.
     */
    virtual integer_type get_uniq_count(integer_type uniq_index) const override {
      if (uniq_index >= size) {
        throw exception{ __MYFUNCNAME__, "uniq_index %lli is out of bound %lli", uniq_index, size };
      }
      return elements[static_cast<size_t>(uniq_index)].second;
    }

   /**
    * \brief Получить количество уникальных элементов \ref express::AGGREGATE совокупности
    *
    * \return количество уникальных элементов \ref express::AGGREGATE совокупности.
    */
    virtual integer_type get_uniq_size() const override {
      return static_cast<integer_type>(elements.size());
    }

   /**
    * \brief Удалить все элементы из внутреннего представления \ref express::AGGREGATE совокупности
    */
    virtual void clear() override {
      elements.clear();
      size = 0;
    }

   /**
    * \brief Дополнить внутреннее представление \ref express::AGGREGATE совокупности элементом
    *
    * \param [in] element Добавляемый элемент, переданный в виде ссылки та тип GENERIC.
    * \param [in] count_of_elements Количество добавляемых одинаковых элементов (для BAG).
    *
    * \warning Эта функция не выполняет проверки правомерности добавления элемента
    * (исходя из допустимого размера совокупности, возможности присутствия неуникальных элементов,
    * возможности присутствия элементов с неопределённым хначением).
    */
    virtual void add_element(const GENERIC& element, integer_type count_of_elements = 1) override {
      const T* t = dynamic_cast<const T*>(&element);
      if (t == nullptr) {
        throw exception{ __MYFUNCNAME__, "element (%s) must be compatible with AGGREGATE elements (%s)",
        element.get_type_name().c_str(), undef.get_type_name().c_str() };
      }
      //!!! Проверить, если это не BAG, должно быть 1.
      elements.push_back({ *t, count_of_elements });
      size ++;
    }


  public:

    /**
     * \brief Конструктор по умолчанию совокупности, имеющей неопределённое (<B>?</B>) значение
     */
    AGGREGATE<T>() {
      GENERIC::determinated = false;
    }
 
    AGGREGATE<T>(const INTEGER& Bound_1, const INTEGER& Bound_2) : AGGREGATE_GENERIC(Bound_1, Bound_2) {
//      GENERIC::determinated = false;
//      bound_1 = Bound_1;
//      bound_2 = Bound_2;
      optional = false;
      uniq = false;
      ordered = false;

//#ifdef TRACE_AGGREGATE
      printf("%s: bound_1=%s, bound_2=%s, ordered=%s, optional=%s, uniq=%s\n",
       __MYFUNCNAME__, bound_1.print_value().c_str(), bound_2.print_value().c_str(),
       ordered ? "yes" : "no", optional ? "yes" : "no", uniq ? "yes" : "no");
//#endif

      append_to_parent_type_list();
    }


    virtual ~AGGREGATE() = default;

    /**
     * \brief Оператор индексирования (\ref p11_s12_6_1 "ГОСТ Р ИСО 10303-11-2009, 12.6.1")
     * \param [in] index Значение индекса возвращаемого значения.
     * \return ссылка на элемент массива, находящийся по указанному индексу или на неопределённый тип данных,
     * если индекс или элемент имеют неопределённое значение.
     *
     * Этот оператор используется только в правой части присваивания.
    */
    virtual const T& operator[](const INTEGER& index) const override {
      return dynamic_cast<const T&>(AGGREGATE_GENERIC::operator[](index));
    }

    /**
     * \brief Уточнение элементом (\ref p11_s13_3_2 "ГОСТ Р ИСО 10303-11-2009, 13.3.2")
     *
     * \param [in] index Значение индекса возвращаемого значения.
     * \return ссылка на элемент массива, находящийся по указанному индексу или на неопределённый тип данных,
     * если индекс или элемент имеют неопределённое значение.
     * (можно использовать и в левой части присваивания)
     *
     * Этот оператор можно использовать и в правой, и в левой части присваивания.
     * \warning Внимание! При использовании этого оператора не проверются правила присвоения элемента
     * совокупности (уникальность, определённость и т.д.). Для присвоения с проверкой необходимо использовать
     * функцию \ref express::AGGREGATE::set_element(const express::INTEGER&, const T&) "set_element".
    */
    virtual T& operator[](const INTEGER& index) override {
      return dynamic_cast<T&>(AGGREGATE_GENERIC::operator[](index));
    }
 
    /**
     * \brief Уточнение элементом (\ref p11_s13_3_2 "ГОСТ Р ИСО 10303-11-2009, 13.3.2")
     *
     * \param [in] index Значение индекса изменяемого элемента.
     * \param [in] element Присваиваемый элемент.
     *
     * Этот оператор, в отличие от оператора  \ref express::AGGREGATE::operator[](const express::INTEGER&) "operator[]",
     * выполняет при выполнения присвоении элемента необходимые проверки (уникальность,
     * определённость и т.д.).
     */
    void set_element(const INTEGER& index, const T& element) {
      return AGGREGATE_GENERIC::set_element(index, element);
    }
  };
}