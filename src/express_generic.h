/**
 * \file
 * \brief Файл с описанием обобщённого типа данных GENERIC языка EXPRESS
 * (\ref p11_s9_5_3_2 "ГОСТ Р ИСО 10303-11-2009, п.9.5.3.2")
 */

namespace express {

  /** \brief Тип, который используется для хранения значения типа \ref express::REAL "REAL" */
  typedef double real_type;

  /** \brief Тип, который используется для хранения значения типа \ref express::INTEGER "INTEGER" */
  typedef long long integer_type;

  /** \brief Тип, который используется для хранения значения типа \ref express::NUMBER "NUMBER" */
  typedef real_type number_type;

  /**
   * \brief Обобщённый тип данных (\ref p11_s9_5_3_2 "ГОСТ Р ИСО 10303-11-2009, п.9.5.3.2").
   *
   * Это базовый тип для всех типов данных EXPRESS.
   */
  class GENERIC {

  protected:

    /**
     * \brief Вывод в виде строки значения типа ENUMERATION
     * \param [in] str Массив строк с текстовыми представлениями значений типа ENUMERATION
     * \param [in] index значение типа ENUMERATION, приведённое к size_t (должно начинаться с нуля).
     * \param [in] maxstr количество строк в массиве строк str.
     *
     * \return строковое представдение значения типа ENUMERATION.
     */
    std::string print_enum_value(const char* const str[], size_t maxstr, size_t index) const;

//  public:

    /**
     * \brief Типы данных (ГОСТ Р ИСО 10303-11-2009, \ref p11_s8_1 "п.8.1" --- \ref p11_s8_4 "п.8.4")
     *
     * Перечисление, определяющее простой, агрегированный, именованные (объектный и определённый), 
     * конструкционные (перечисляемый и выбираемый) типы данных.
     */
    enum
#if !defined(__DOXYGEN__)
      class
#endif 
      OBJTYPE
#if !defined(__DOXYGEN__)
      : uint32_t
#endif 
    {
      /** \brief Тип данных не определён */
      OBJ_NONE =                                                                                             0,
      /** \brief Обобщённый тип данных (ГОСТ Р ИСО 10303-11-2009, \ref p11_s9_5_3_2 "9.5.3.2") */
      OBJ_GENERIC =                                                                                          (1 << 0),
      /** \brief Простой тип данных (ГОСТ Р ИСО 10303-11-2009, \ref p11_s8_1 "8.1") */
      OBJ_SIMPLE =                                                                                           (1 << 1),

      /** \brief Простой числовой тип данных (ГОСТ Р ИСО 10303-11-2009, \ref p11_s8_1_1 "8.1.1") */
      OBJ_NUMBER =                                                                                           (1 << 2),
      /** \brief Простой действительный тип данных (ГОСТ Р ИСО 10303-11-2009, \ref p11_s8_1_2 "8.1.2") */
      OBJ_REAL =                                                                                             (1 << 3),
      /** \brief Простой целочисленный тип данных (ГОСТ Р ИСО 10303-11-2009, \ref p11_s8_1_3 "8.1.3") */
      OBJ_INTEGER =                                                                                          (1 << 4),

      /** \brief Простой логический тип данных (ГОСТ Р ИСО 10303-11-2009, \ref p11_s8_1_4 "8.1.4") */
      OBJ_LOGICAL =                                                                                          (1 << 5),
      /** \brief Простой булев тип данных (ГОСТ Р ИСО 10303-11-2009, \ref p11_s8_1_5 "8.1.5") */
      OBJ_BOOLEAN =                                                                                          (1 << 6),

      /** \brief Простой строковый тип данных (ГОСТ Р ИСО 10303-11-2009, \ref p11_s8_1_6 "8.1.6") */
      OBJ_STRING =                                                                                           (1 << 7),
      /** \brief Простой двоичный тип данных (ГОСТ Р ИСО 10303-11-2009, \ref p11_s8_1_7 "8.1.7") */
      OBJ_BINARY =                                                                                           (1 << 8),

      /** \brief Агрегированный тип данных (ГОСТ Р ИСО 10303-11-2009, \ref p11_s8_2 "8.2") */
      OBJ_AGGREGATE =                                                                                        (1 << 9),

      /** \brief Агрегированный тип данных 'массив' (ГОСТ Р ИСО 10303-11-2009, \ref p11_s8_2_1 "8.2.1") */
      OBJ_ARRAY =                                                                                            (1 << 10),
      /** \brief Агрегированный тип данных 'список' (ГОСТ Р ИСО 10303-11-2009, \ref p11_s8_2_2 "8.2.2") */
      OBJ_LIST =                                                                                             (1 << 11),
      /** \brief Агрегированный тип данных 'множество' (ГОСТ Р ИСО 10303-11-2009, \ref p11_s8_2_3 "8.2.3") */
      OBJ_BAG =                                                                                              (1 << 12),
      /** \brief Агрегированный тип данных 'набор' (ГОСТ Р ИСО 10303-11-2009, \ref p11_s8_2_4 "8.2.4") */
      OBJ_SET =                                                                                              (1 << 13),

      /** \brief Объектный тип данных, простой объект (ГОСТ Р ИСО 10303-11-2009, \ref p11_s8_3_1 "8.3.1") */
      OBJ_ENTITY =                                                                                           (1 << 14),
      /** \brief Сложный объектный тип данных (ГОСТ Р ИСО 10303-11-2009, \ref p11_s8_3_1 "8.3.1") */
      OBJ_ENTITY_COMPLEX =                                                                                   (1 << 15),
      /** \brief Определённый тип данных (ГОСТ Р ИСО 10303-11-2009, \ref p11_s8_3_2 "8.3.2") */
      OBJ_DEFINED =                                                                                          (1 << 16),
      /** \brief Перечисляемый тип данных (ГОСТ Р ИСО 10303-11-2009, \ref p11_s8_4_1 "8.4.1") */
      OBJ_ENUMERATION =                                                                                      (1 << 17),
      /** \brief Выбираемый тип данных (ГОСТ Р ИСО 10303-11-2009, \ref p11_s8_4_2 "8.4.2") */
      OBJ_SELECT =                                                                                           (1 << 18),
    };

    /**
     * \brief Объединить два типа данных в виде элемента перечисления OBJTYPE
     * \param [in] lhs Тип данных в виде элемента перечисления OBJTYPE.
     * \param [in] rhs Тип данных в виде элемента перечисления OBJTYPE.
     * \return объединение двух типов данных в виде элемента перечисления OBJTYPE.
     */
    friend constexpr OBJTYPE operator|(OBJTYPE lhs, OBJTYPE rhs) {
      using type = std::underlying_type<OBJTYPE>::type;

      if (lhs == rhs) {
        return lhs;
      }
      /** 2. Проверка допустимых комбинаций типов --- GENERIC не может комбинироваться ни с чем */
      if (lhs == OBJTYPE::OBJ_GENERIC || rhs == OBJTYPE::OBJ_GENERIC) {
        throw exception{ __MYFUNCNAME__, "GENERIC type can not be combined" };
      }
      /** 3. Проверка допустимых комбинаций типов --- простые типы данных */
      if ((lhs == OBJTYPE::OBJ_SIMPLE && (rhs == OBJTYPE::OBJ_LOGICAL ||
        rhs == OBJTYPE::OBJ_BOOLEAN ||
        rhs == OBJTYPE::OBJ_NUMBER ||
        rhs == OBJTYPE::OBJ_REAL ||
        rhs == OBJTYPE::OBJ_INTEGER ||
        rhs == OBJTYPE::OBJ_BINARY ||
        rhs == OBJTYPE::OBJ_STRING)) ||
        (rhs == OBJTYPE::OBJ_SIMPLE && (lhs == OBJTYPE::OBJ_LOGICAL ||
          lhs == OBJTYPE::OBJ_BOOLEAN ||
          lhs == OBJTYPE::OBJ_NUMBER ||
          lhs == OBJTYPE::OBJ_REAL ||
          lhs == OBJTYPE::OBJ_INTEGER ||
          lhs == OBJTYPE::OBJ_BINARY ||
          lhs == OBJTYPE::OBJ_STRING))) {
        return OBJTYPE(static_cast<type>(lhs) | static_cast<type>(rhs));
      }
      /** 3. Проверка допустимых комбинаций типов --- аггрегированные типы данных */
      if ((lhs == OBJTYPE::OBJ_AGGREGATE && (rhs == OBJTYPE::OBJ_ARRAY ||
        rhs == OBJTYPE::OBJ_LIST ||
        rhs == OBJTYPE::OBJ_BAG ||
        rhs == OBJTYPE::OBJ_SET)) ||
        (rhs == OBJTYPE::OBJ_AGGREGATE && (lhs == OBJTYPE::OBJ_ARRAY ||
          lhs == OBJTYPE::OBJ_LIST ||
          lhs == OBJTYPE::OBJ_BAG ||
          lhs == OBJTYPE::OBJ_SET))) {
        return OBJTYPE(static_cast<type>(lhs) | static_cast<type>(rhs));
      }
      throw std::invalid_argument("mutually exclusive values");
    }

    /**
     * \brief Получить пересечение двух типов данных в виде элементов перечисления OBJTYPE
     * \param [in] lhs Тип данных в виде элемента перечисления OBJTYPE.
     * \param [in] rhs Тип данных в виде элемента перечисления OBJTYPE.
     * \return пересечение двух типов данных в виде элементов перечисления OBJTYPE.
     */
    friend OBJTYPE operator&(OBJTYPE lhs, OBJTYPE rhs) {
      using type = std::underlying_type<OBJTYPE>::type;
      return OBJTYPE(static_cast<type>(lhs) & static_cast<type>(rhs));
    }

    /**
     * \brief Проверить существование пересечения двух типов данных в виде элементов перечисления OBJTYPE
     * \param [in] lhs Тип данных в виде элемента перечисления OBJTYPE.
     * \param [in] rhs Тип данных в виде элемента перечисления OBJTYPE.
     * \return true, если существует пересечение двух типов данных в виде элементов перечисления OBJTYPE
     * и false в противном случае.
     */
    friend bool operator&&(OBJTYPE lhs, OBJTYPE rhs) {
      using type = std::underlying_type<OBJTYPE>::type;
      return (static_cast<type>(lhs) & static_cast<type>(rhs)) == 0 ? false : true;
    }

    /**
     * \brief Получить принадлёжность типа данных к одной из групп
     * 
     * \return тип данных в виде элемента перечисления OBJTYPE.
     */
    virtual constexpr OBJTYPE objtype() const = 0;

  protected:

    /**
     * \brief Преобразовать тип данных в строку
     * \param [in] t Тип данных в виде элемента перечисления OBJTYPE.
     * \return строку, содержащую текстовое представление названия типа данных.
     *
     * <B>ГОСТ Р ИСО 10303-21, 10.1.6 Простые определённые типы</B>
     *
     * Простой определённый тип является типом, определяемым объявлением EXPRESS-типа, в
     * котором опорным типом не является перечисляемый тип (ENUMERATION) или выбираемый тип
     * (SELECT). Простой определённый тип должен быть отображен в структуру обмена как тот тип
     * данных, который использовался в его определении.
     *
     */
    static std::string objtype_to_string(OBJTYPE t);

    /**
     * \brief Список родительских типов, накапливается при наследовании
     *
     * При каждом наследовании имя дочернего типа добавляется к этому списку.
     */
    std::vector<std::string> parent_type_list;

    /**
     * \brief Имеет ли объект определённое значение
     *
     * true, если объект определён и false, если объект имеет неопределённое значение.
     */
    bool determinated;

    //!!! Для каждого типа должна быть предусмотрена ссылка на объект, в котором он является атрибутом (или NULL)
    //! Это нужно для работы функции USEDIN, возвращающей набор типов, использующих данный тип в указанной роли (например, "схема.класс.атрибут")
    //! и для функции ROLESOF, набор возвращающей ролей указанного типа.
    //! Объект при уничтожении должен убирать эти ссылки со своих атрибутов

    /**
      * \brief Вывести в виде строки значение типа (как атрибут объектного типа)
      * 
      * \return строковое представление значения типа.
      *
      * Для объектных типов строковое представление экземпляра --- это имя-индекс,
      * для прочих типов --- значение.
      */
    virtual std::string print_value() const = 0;

    /**
     *\brief Добавить имя типа в список родительских типов
     * \param [in] override Строка с имененм типа вместо автоматически определяемого
     */
    void append_to_parent_type_list(const char* override = nullptr);

  public:

    /**
     * \brief Конструктор обобщённого типа, имеющего определённое или неопределённое (<B>?</B>) значение
     */
    explicit GENERIC(bool Determinated = true);

    /**
     * \brief Копирующий конструктор обобщённого типа --- по умолчанию 
     */
    explicit GENERIC(const GENERIC& rhs) = default;

    /**
     * \brief Деструктор обобщённого типа --- по умолчанию
     */
    virtual ~GENERIC() = default;

    /**
     * \brief Проверить, является ли объект определённым
     * \return true, если объект определён и false, если объект имеет неопределённое значение.
     */
    bool is_determinated() const;

    /**
     * \brief Получить отладочный вывод списка родительских типов
     * 
     * \return строку со списком родительских типов.
     */
    std::string debug_print_type_list() const;

    /**
     * \brief Проверить, является ли тип числом (NUMBER)
     * \return true, если тип --- число и false, если нет.
     */
    bool is_number() const;

    /**
     * \brief Проверить, является ли тип действительным (REAL) числом
     * \return true, если тип --- действительное число и false, если нет.
     */
    bool is_real() const;

    /**
     * \brief Проверить, является ли тип целым (INTEGER) числом
     * \return true, если тип --- целое число и false, если нет.
     */
    bool is_integer() const;

    /**
     * \brief Проверить, является ли тип логическим (LOGICAL) числом
     * \return true, если тип --- логический и false, если нет.
     */
    bool is_logical() const;

    /**
     * \brief Проверить, является ли тип булевым (BOOLEAN) числом
     * \return true, если тип --- логический и false, если нет.
     */
    bool is_boolean() const;

    /**
     * \brief Проверить, является ли тип строковым (STRING) числом
     * \return true, если тип --- логический и false, если нет.
     */
    bool is_string() const;

    /**
     * \brief Проверить, является ли тип двоичным (BINARY) числом
     * \return true, если тип --- двоичный и false, если нет.
     */
    bool is_binary() const;


    /**
     * \brief Получить имя типа данных в виде строки
     * 
     * \return тип данных в виде строки.
     */
    std::string get_type_name() const;

    /**
     * \brief Проверить, имеет ли тип данных указанное имя
     * \param [in] Typename Указатель на строку с проверяемым именем типа данных
     * \return true, если тип данных имеет имя, переданное в Typename, и false в противном случае.
     */
    bool is_type_name(const char* Typename) const;

    /**
     * \brief Проверить, имеет ли тип данных указанное имя у себя или у предков
     * 
     * \return true, если типа данных имеет указанное имя у себя или у предков, и false, если нет.
     */
    bool is_parent_name(const char* Typename) const;

    /**
     *\brief Получить имя типа данных вложенного/базисного типа (для SELECT и агрегированных типов)
     * 
     * \return строковое представление типа данных вложенного/базисного типа.
     */
    virtual const std::string get_value_type_name() const;

    /**
     * \brief Получить тип данных вложенного типа (для SELECT и агрегированных типов).
     * 
     * \return тип данных вложенного/базисного типа в виде элемента перечисления OBJTYPE.
     */
    virtual OBJTYPE get_value_objtype() const;


    /**
     * \brief Возможность совместимости типов
     */
    enum
#if !defined(__DOXYGEN__)
      class
#endif 
      COMPAT
    {
      /** \brief Типы данных не совместимы, сравнивать и присваивать нельзя */
      COMPAT_NONE,

      /** \brief Типы данных одинаковы, можно сравнивать и присваивать */
      COMPAT_SAME,

      /** \brief Можно сравнивать, присваивать своему типу указанный тип */
      COMPAT_BACKWARD,

      /** \brief Можно сравнивать, присвоить свой тип указанному типу */
      COMPAT_FORWARD,
    };

    /**
     * \brief Проверить совместимость с типом.
     * 
     * \param [in] rhs Тип, с которым будет произведено сравнение, переданный в виде ссылки
     * на тип GENERIC. 
     * \return результат сравнения типов в виде перечисления COMPAT.
     */
    virtual COMPAT check_compatibility(const GENERIC& rhs) const = 0;
    
    /**
     * \brief Проверка равенства значения с неизвестным типом
     * 
     * \param [in] rhs Объект, с которым выполняется сравнение, в виде ссылки на тип GENERIC.
     * \return результат проверки равенства значений.
     * 
     * Неизвестный тип передан как ссылка на базовый тип GENERIC.
     */
    virtual LOGICAL operator==(const GENERIC& rhs) const;

    /**
     * \brief Проверка неравенства значения с неизвестным типом
     * 
     * \param [in] rhs Объект, с которым выполняется сравнение, в виде ссылки на тип GENERIC.
     * \return результат проверки неравенства значений.
     * 
     * Неизвестный тип передан как ссылка на базовый тип GENERIC.
     */
    virtual LOGICAL operator!=(const GENERIC& rhs) const;

    /**
     * \brief Проверка равенства значения или экземпляра с неизвестным типом
     * 
     * \param [in] rhs Объект, с которым выполняется сравнение.
     * \param [in] compare_value true, если сравниваются значения и false, если экземпляры.
     * \return результат проверки равенства значений или экземпляров.
     *
     * Неизвестный тип передан как ссылка на базовый тип GENERIC.
     */
    virtual LOGICAL is_equal(const GENERIC& rhs, bool compare_value) const = 0;

    /**
     * \brief Проверка равенства экземпляров с неизвестным типом
     * 
     * \param [in] rhs Объект, с которым выполняется сравнение, в виде ссылки на тип GENERIC.
     * \return результат проверки равенства экземпляров.
     *
     * Неизвестный тип передан как ссылка на базовый тип GENERIC.
     * Эта функция должна быть переопределена для объектных типов, аггрегатных
     * и выбранных типов ((они могут содержать объектные типы)).
     */
    virtual LOGICAL is_instance_equal(const GENERIC& rhs) const;


/**
 * Набор макросов для задания перечислений.
 */
#if (_MSVC_LANG >= 202002L) || (__STDC_VERSION__ > 201710L)

  #define PARENS ()

  #define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
  #define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
  #define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
  #define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
  #define EXPAND1(...) __VA_ARGS__

  #define FOR_EACH(macro, ...) __VA_OPT__(EXPAND(FOR_EACH_HELPER(macro, __VA_ARGS__)))
  #define FOR_EACH_HELPER(macro, a1, ...) macro(a1) __VA_OPT__(FOR_EACH_AGAIN PARENS (macro, __VA_ARGS__))
  #define FOR_EACH_AGAIN() FOR_EACH_HELPER

#else

  #define EXPAND(x) x

  #define FOR_EACH_1(what, x, ...)  what(x)
  #define FOR_EACH_2(what, x, ...)  what(x) EXPAND(FOR_EACH_1 (what, __VA_ARGS__))
  #define FOR_EACH_3(what, x, ...)  what(x) EXPAND(FOR_EACH_2 (what, __VA_ARGS__))
  #define FOR_EACH_4(what, x, ...)  what(x) EXPAND(FOR_EACH_3 (what, __VA_ARGS__))
  #define FOR_EACH_5(what, x, ...)  what(x) EXPAND(FOR_EACH_4 (what, __VA_ARGS__))
  #define FOR_EACH_6(what, x, ...)  what(x) EXPAND(FOR_EACH_5 (what, __VA_ARGS__))
  #define FOR_EACH_7(what, x, ...)  what(x) EXPAND(FOR_EACH_6 (what, __VA_ARGS__))
  #define FOR_EACH_8(what, x, ...)  what(x) EXPAND(FOR_EACH_7 (what, __VA_ARGS__))
  #define FOR_EACH_9(what, x, ...)  what(x) EXPAND(FOR_EACH_8 (what, __VA_ARGS__))
  #define FOR_EACH_10(what, x, ...) what(x) EXPAND(FOR_EACH_9 (what, __VA_ARGS__))
  #define FOR_EACH_11(what, x, ...) what(x) EXPAND(FOR_EACH_10(what, __VA_ARGS__))
  #define FOR_EACH_12(what, x, ...) what(x) EXPAND(FOR_EACH_11(what, __VA_ARGS__))
  #define FOR_EACH_13(what, x, ...) what(x) EXPAND(FOR_EACH_12(what, __VA_ARGS__))
  #define FOR_EACH_14(what, x, ...) what(x) EXPAND(FOR_EACH_13(what, __VA_ARGS__))
  #define FOR_EACH_15(what, x, ...) what(x) EXPAND(FOR_EACH_14(what, __VA_ARGS__))
  #define FOR_EACH_16(what, x, ...) what(x) EXPAND(FOR_EACH_15(what, __VA_ARGS__))
  #define FOR_EACH_17(what, x, ...) what(x) EXPAND(FOR_EACH_16(what, __VA_ARGS__))
  #define FOR_EACH_18(what, x, ...) what(x) EXPAND(FOR_EACH_17(what, __VA_ARGS__))
  #define FOR_EACH_19(what, x, ...) what(x) EXPAND(FOR_EACH_18(what, __VA_ARGS__))
  #define FOR_EACH_20(what, x, ...) what(x) EXPAND(FOR_EACH_19(what, __VA_ARGS__))
  #define FOR_EACH_21(what, x, ...) what(x) EXPAND(FOR_EACH_20(what, __VA_ARGS__))
  #define FOR_EACH_22(what, x, ...) what(x) EXPAND(FOR_EACH_21(what, __VA_ARGS__))
  #define FOR_EACH_23(what, x, ...) what(x) EXPAND(FOR_EACH_22(what, __VA_ARGS__))
  #define FOR_EACH_24(what, x, ...) what(x) EXPAND(FOR_EACH_23(what, __VA_ARGS__))
  #define FOR_EACH_25(what, x, ...) what(x) EXPAND(FOR_EACH_24(what, __VA_ARGS__))
  #define FOR_EACH_26(what, x, ...) what(x) EXPAND(FOR_EACH_25(what, __VA_ARGS__))
  #define FOR_EACH_27(what, x, ...) what(x) EXPAND(FOR_EACH_26(what, __VA_ARGS__))
  #define FOR_EACH_28(what, x, ...) what(x) EXPAND(FOR_EACH_27(what, __VA_ARGS__))
  #define FOR_EACH_29(what, x, ...) what(x) EXPAND(FOR_EACH_28(what, __VA_ARGS__))
  #define FOR_EACH_30(what, x, ...) what(x) EXPAND(FOR_EACH_29(what, __VA_ARGS__))
  #define FOR_EACH_31(what, x, ...) what(x) EXPAND(FOR_EACH_30(what, __VA_ARGS__))
  #define FOR_EACH_32(what, x, ...) what(x) EXPAND(FOR_EACH_31(what, __VA_ARGS__))
  #define FOR_EACH_33(what, x, ...) what(x) EXPAND(FOR_EACH_32(what, __VA_ARGS__))
  #define FOR_EACH_34(what, x, ...) what(x) EXPAND(FOR_EACH_33(what, __VA_ARGS__))
  #define FOR_EACH_35(what, x, ...) what(x) EXPAND(FOR_EACH_34(what, __VA_ARGS__))

  #define FOR_EACH_NARG(...) FOR_EACH_NARG_(__VA_ARGS__, FOR_EACH_RSEQ_N())
  #define FOR_EACH_NARG_(...) EXPAND(FOR_EACH_ARG_N(__VA_ARGS__))
  #define FOR_EACH_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16,\
  _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35,\
  N, ...) N
  #define FOR_EACH_RSEQ_N() 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19,\
  18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1
  #define CONCATENATE(x,y) x##y
  #define FOR_EACH_(N, what, ...) EXPAND(CONCATENATE(FOR_EACH_, N)(what, __VA_ARGS__))

  #define FOR_EACH(what, ...) FOR_EACH_(FOR_EACH_NARG(__VA_ARGS__), what, __VA_ARGS__)

#endif

#define MAKE_ENUM(...) protected: enum class value { __VA_ARGS__ };               \
constexpr static const char* value_str[] = { FOR_EACH(ENUM_VAL, __VA_ARGS__) }

#define MAKE_ENUM_WITH_PUBLIC(...) protected: enum class value { __VA_ARGS__ };   \
constexpr static const char* value_str[] = { FOR_EACH(ENUM_VAL, __VA_ARGS__) };   \
public: FOR_EACH(ENUM_PUBLIC, __VA_ARGS__)

#define ENUM_VAL(v) #v,

#define ENUM_PUBLIC(v) static const value v = value::##v


    friend class STEP_ATTRIBUTE;
    friend class AGGREGATE_GENERIC;
    friend class SELECT;
    template<class T> friend class AGGREGATE;
    template<class T> friend class ARRAY;
    template<class T> friend class LIST;
    template<class T> friend class BAG;
    template<class T> friend class SET;
  };
}
