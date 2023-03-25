/**
 * \file
 * \brief Файл с описанием простого строкового типа данных STRING языка EXPRESS
 * (ГОСТ Р ИСО 10303-11-2009, 8.1.6; ГОСТ Р ИСО 10303-21, 6.3)
 */

namespace express {

  /** 
   * \brief Простой тип \ref express::STRING "STRING" --- Строка (ГОСТ Р ИСО 10303-11-2009, 8.1.6)
   *
   * \anchor p11_s8_1_6
   *
   * \ref express::STRING "8.1.6 Строковый тип данных"
   *
   * Областью определения типа данных \ref express::STRING "STRING" являются последовательности символов. Символами,
   * допусимыми в строковых значениях, являются символы ИСО/МЭК 10646-1 из позиций 09, 0A, 0D и
   * графические символы, расположенные в позициях от 20 до 7Е и от А0 до 10FFFE.
   \verbatim
     Синтаксис:
      311 string_type = STRING [ width_spec ] .
      341 width_spec = '(' width ')' [ FIXED ] .
      340 width = numeric_expression .
   \endverbatim
   * Тип данных \ref express::STRING "STRING" может иметь как фиксированную, так и переменную длину (число символов).
   * Если фиксированная длина строки конкретно не указана (посредством зарезервированного слова <B>FIXED</B>
   * в определении), то строка имеет переменную длину.
   *
   * Областью определения типа данных \ref express::STRING "STRING" фиксированной длины является множество всех
   * последовательностей символов длины, точно указанной в определении типа.
   *
   * Областью определения типа данных \ref express::STRING "STRING" переменной длины является множество всех
   * последовательностей символов длины, меньшее или равное максимальной длине, указанной в
   * определении типа.
   *
   * Если длина не указана, то областью определения является множество всех последовательностей
   * символов без ограничения на длину этих последовательностей.
   *
   * Адресация к подстрокам и отдельным символам может осуществляться посредством подстрочных
   * индексов, как описано в 12.5.
   *
   * В пределах строки имеет значение регистр ввода букв (верхний или нижний).
   *
   * Правило: значением выражения <B>width</B> должно быть положительное целое число.
   *
   * <B><I>Примеры
   *
   * 1 В данном примере определена строка переменной длины, значения которой не имеют
   * заданной максимальной длины:</I>
   *
   * string1 : STRING;
   *
   * <I>2 В данном примере определена строка с максимальной длиной равной десяти символам, значения
   * которой могут иметь длину от нуля до десяти символов:</I>
   *
   * string2 : STRING(10);
   * 
   * <I>3 В данном примере определена строка фиксированной длины равной десяти символам, значения
   * которой должны содержать ровно десять символов:</I>
   *
   * string3 : STRING(10) FIXED</B>
   */
  class STRING : public SIMPLE {

  private:

    /**
     * \brief Значение типа STRING --- строка
     */
    std::string _s;

    int max_length;

  protected:

    /**
     *\brief Получить принадлёжность типа данных к одной из групп
     * \return тип данных в виде элемента перечисления OBJTYPE.
     */
    virtual OBJTYPE objtype() const override;

  public:

    /**
     * \brief Конструктор типа, имеющего неопределённое (<B>?</B>) значение
     */
    STRING() : SIMPLE(false), max_length(-1) {
      append_to_parent_type_list();
    }

    /** \brief Конструктор из строки std::string */
    STRING(const std::string &v) : _s(v), max_length(-1) {
      append_to_parent_type_list();
    }

    /** \brief Конструктор из строки char* */
    STRING(const char *v) : _s(v), max_length(-1) {
      append_to_parent_type_list();
    }

    /**
     * \brief Деструктор строки --- по умолчанию
     */
    virtual ~STRING() = default;

    /** \brief Преобразование к std::string */
    const std::string& get_value() const {
      return _s;
    }

    /**
     * \brief Проверить совместимость строкового типа с некоторым типом.
     *
     * \param [in] rhs Тип, с которым будет произведено сравнение, переданный в виде ссылки
     * на тип GENERIC.
     * \return результат сравнения типов в виде перечисления COMPAT.
     */
    virtual COMPAT check_compatibility(const GENERIC& rhs) const override;

    /**
     * \brief Вывод значения типа (ГОСТ Р ИСО 10303-21, 6.3.3, 10.1.1.2)
     *
     * <B>6.3.3 Строка (String)</B>
     *
     * Строка должна быть закодирована как <I>апостроф</I> “'”, за которым следует нуль или несколько
     * 8-битных байтов, и заканчиваться “'”. Нулевая строка (строка нулевой длины) должна быть
     * закодирована последовательностью из двух <I>апострофов</I> “''”. Внутри строки единичный <I>апостроф</I>
     * должен быть закодирован как два последовательных <I>апострофа</I>. Внутри строки единичная <I>косая обратная
     * черта</I> “\” должна быть закодирована как две <I>косые обратные черты</I> “\\” 8-битные байты,
     * разрешенные внутри строки, являются десятичными эквивалентами чисел от 32 до 126 (включительно)
     * по ИСО/М ЭК 8859-1, которые определяют графические символы основного алфавита.
     *
     * <B>10.1.1.2 Тип данных \ref express::STRING "STRING" (строковый)</B>
     *
     * Значения данных в EXPRESS типа \ref express::STRING "STRING" отображаются в структуру обмена как строковый
     * тип данных. Состав строкового типа данных описан в 6.3.3.
     */
    virtual std::string print_value() const override {
      if (!determinated) {
#ifdef TRACE
        return std::string("INDETERMINATED");
#else
        throw exception{__MYFUNCNAME__, "value may not be indeterminate (?)"};
#endif
      }

      std::stringstream s;
      if (_s.empty()) {
        s << "''";
      } else {
        s << "'" << _s << "'";
      }
      return s.str();
    }


    /**
     * \brief Уточнение элементом (\ref p11_s13_3_2 "ГОСТ Р ИСО 10303-11-2009, 13.3.2")
     * \param [in] index Значение индекса возвращаемого значения.
     * \return ссылка на элемент строки, находящийся по указанному индексу. 
     * (можно использовать и в левой части присваивания)
     */
    char& operator[](const INTEGER& index) {
      /** 1. Проверка --- строка должна иметь значение */
      if (!determinated) {
        throw exception{__MYFUNCNAME__, "string may not be indeterminate (?)"};
      }

      /** 2. Проверка --- индекс должен иметь значение */
      if (!index.is_determinated()) {
        throw exception{__MYFUNCNAME__, "index may not be indeterminate (?)"};
      }

      /**
       * 3. Если индекс лежит вне пределов размера строки, вызвать исключение.
       */
      if (index.get_integer_value() < 1 || index.get_integer_value() > static_cast<integer_type>(_s.length())) {
        throw exception{__MYFUNCNAME__, "Index = %lli can not be out of borders (from 1 to %llu)", index.get_integer_value(), _s.length()};
      }

      return _s[static_cast<size_t>(index.get_integer_value() - 1)];
    }

    /**
     * \brief Уточнение диапазоном (\ref p11_s13_3_2 "ГОСТ Р ИСО 10303-11-2009, 13.3.2")
     * \param [in] index_pair Пара индексов, определяющих диапазон индексов в строке.
     * \return ссылка на элементы строки, находящиеся в указанном диапазоне. 
     * (можно использовать и в левой части присваивания)
     */
    char* operator[](std::pair<const INTEGER&, const INTEGER&>index_pair) {
      /** 1. Проверка --- строка должна иметь значение */
      if (!determinated) {
        throw exception{__MYFUNCNAME__, "string may not be indeterminate (?)"};
      }

      /** 2. Проверка --- индекс должен иметь значение */
      if (!index_pair.first.is_determinated() || !index_pair.second.is_determinated()) {
        throw exception{__MYFUNCNAME__, "index_1, index_2 may not be indeterminate (?)"};
      }

      /**
       * 3. Если индекс#1 лежит вне пределов [1, индекс#2], вызвать исключение.
       */
      if (index_pair.first.get_integer_value() < 1 || index_pair.first.get_integer_value() > index_pair.second.get_integer_value()) {
        throw exception{__MYFUNCNAME__, "Index_1 = %lli can not be out of borders (from 1 to Index_2 = %lli)",
          index_pair.first.get_integer_value(), index_pair.second.get_integer_value()};
      }

      /**
       * 4. Если индекс#2 больше размера строки, вызвать исключение.
       */
      if (index_pair.second.get_integer_value() > static_cast<integer_type>(_s.length())) {
        throw exception{__MYFUNCNAME__, "Index_2 = %lli can not be out of string size (%llu)",
          index_pair.second.get_integer_value(), _s.length()};
      }

      return _s.data() + index_pair.first.get_integer_value() - 1;//, index_pair.second.get_integer_value() + 1 - index_pair.first.get_integer_value());
    }

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

    friend INTEGER LENGTH(const STRING& V);
  };

  class STRING_FIXED : public STRING {

  public:

    /**
     * \brief Конструктор типа, имеющего неопределённое (<B>?</B>) значение
     */
    STRING_FIXED() : STRING() {
    }

    /** \brief Конструктор из строки std::string */
    STRING_FIXED(const std::string &src) : STRING(src) {
    }

    /** \brief Конструктор из строки char* */
    STRING_FIXED(const char *src) : STRING(src) {
    }
  };
}