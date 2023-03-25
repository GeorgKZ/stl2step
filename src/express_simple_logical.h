/**
 * \file
 * \brief Файл с описанием простого типа данных LOGICAL языка EXPRESS
 * (ГОСТ Р ИСО 10303-11-2009, 8.1.4; ГОСТ Р ИСО 10303-21, 6.3)
 */

namespace express {

  /** 
   * \brief Простой тип \ref express::LOGICAL "LOGICAL --- логическое значение" (ГОСТ Р ИСО 10303-11-2009, 8.1.4)
   *
   * \anchor p11_s8_1_4
   *
   * \ref express::LOGICAL "8.1.4 Логический тип данных"
   *
   * Областью определения типа данных \ref express::LOGICAL "LOGICAL" являются три литерала:
   * \ref express::LOGICAL.TRUE "TRUE",
   * \ref express::LOGICAL.FALSE "FALSE", и
   * \ref express::LOGICAL.UNKNOWN "UNKNOWN".
   \verbatim
     Синтаксис:
      256 logical_type = LOGICAL .
   \endverbatim
   * Значения логического типа данных упорядочены следующим образом:
   * \ref express::LOGICAL.FALSE "FALSE" \<
   * \ref express::LOGICAL.UNKNOWN "UNKNOWN" \<
   * \ref express::LOGICAL.TRUE "TRUE".
   * Тип данных \ref express::LOGICAL "LOGICAL" совместим с типом данных
   * \ref express::BOOLEAN "BOOLEAN", за исключением того, что
   * булевой переменной не может быть присвоено значение \ref express::LOGICAL.UNKNOWN "UNKNOWN".
   */
  class LOGICAL : public SIMPLE {

    MAKE_ENUM(F, U, T);

  protected:

  /* Пояснение для Доксигена */
#if defined (__DOXYGEN__)
    enum class value { };
#endif

    value _l;

    /** 
     *\brief Получить принадлёжность типа данных к одной из групп
     * \return тип данных в виде элемента перечисления OBJTYPE.
     */
    virtual constexpr OBJTYPE objtype() const override;

  public:

    static const value FALSE   = value::F;
    static const value UNKNOWN = value::U;
    static const value TRUE    = value::T;

    /**
     * \file
     * Для типа LOGICAL определены следующие члены-методы (функции):<BR><BR>
     */

   /**
     * Конструкторы (неопределённого значения, копирующий (из базового и дочерних
     * типов) и конструктор из значения), деструктор и оператор присваивания
     * своего и дочерних типов.
     */

    /**
     * \brief Конструктор логического типа LOGICAL по умолчанию, имеющего неопределённое
     * (<B>?</B>) значение
     */
    LOGICAL();

    /**
     * \brief Конструктор логического типа LOGICAL из логического типа LOGICAL или булевого типа
     * BOOLEAN, переданного через ссылку на тип LOGICAL
     * \param [in] src Объект-источник --- логический тип LOGICAL или булев тип BOOLEAN, переданный
     * через ссылку на тип LOGICAL.
     */
    LOGICAL(const LOGICAL& src);

    /**
     * \brief Конструктор логического типа LOGICAL из логических значений TRUE или FALSE
     * \param [in] src Источник --- логическое значение TRUE или FALSE, которое будет присвоено.
     */
    LOGICAL(value src);

    /**
     * \brief Деструктор логического типа --- по умолчанию
     */
    virtual ~LOGICAL() = default;

    /**
     * \brief Оператор присваивания логического типа LOGICAL или булева типа BOOLEAN, переданного
     * через ссылку на тип LOGICAL
     * \param [in] rhs Объект-источник --- логический тип LOGICAL или булев тип BOOLEAN,
     * переданный через ссылку на тип LOGICAL.
     *
     * При выполнении присваивания проводится проверка на самоприсваивание.
     */
    LOGICAL& operator=(const LOGICAL& rhs);

    /**
     * \file
     * Получение значения типа, вывод значения типа в виде строки.
     */

    /**
     * \brief Проверка, имеет ли логический тип LOGICAL значение TRUE
     * \return true, если логический тип LOGICAL имеет значение TRUE, и false в других случаях.
     */
    virtual bool is_true() const;

    /**
     * \brief Проверка, имеет ли логический тип LOGICAL значение FALSE
     * \return true, если логический тип LOGICAL имеет значение FALSE, и false в других случаях.
     */
    virtual bool is_false() const;

    /**
     * \brief Проверка, имеет ли логический тип LOGICAL значение UNKNOWN
     * \return true, если логический тип LOGICAL имеет значение UNKNOWN, и false в других случаях.
     */
    virtual bool is_unknown() const;

    /**
     * \brief Получение логического значения логического типа LOGICAL
     * \return логическое значение логического типа LOGICAL.
     */
    value get_value() const;

    /**
     * \brief Проверить совместимость логического типа с некоторым типом.
     *
     * \param [in] rhs Тип, с которым будет произведено сравнение, переданный в виде ссылки
     * на тип GENERIC.
     * \return результат сравнения типов в виде перечисления COMPAT.
     */
    virtual COMPAT check_compatibility(const GENERIC& rhs) const override;

    /**
     * \brief Вывод значения логического и булевого типа
     * (ГОСТ Р ИСО 10303-21, п.10.1.1.3, п.10.1.1.4)
     *
     * <B>10.1.1.3 Тип данных boolean (булевский)</B>
     *
     * Значения данных в EXPRESS типа \ref express::BOOLEAN "BOOLEAN" отображаются в структуру
     * обмена как данные перечисляемого типа. Состав данных перечисляемого типа описан в 6.3.5.
     * EXPRESS-данные типа \ref express::BOOLEAN "BOOLEAN" должны быть обработаны как
     * предопределенный перечисляемый тип данных со значением, кодированным графическим символом
     * <B>“Т”</B> или <B>“F”</B>. Эти значения соответствуют true (истина) и false (ложь).
     *
     * \ref express::LOGICAL "10.1.1.4 Тип данных LOGICAL (логический)"
     *
     * Значения данных в EXPRESS типа \ref LOGICAL отображаются в структуру обмена как данные
     * перечисляемого типа. В 6.3.5 описан состав перечисляемого типа данных. EXPRESS-данные типа
     * \ref LOGICAL должны быть обработаны как предопределенный перечисляемый тип данных со
     * значением, кодированным графическими символами “Т”, “F” или “U ”. Эти значения соответствуют
     * true (истина), false (ложь) и unknown (неизвестно).
     */
    virtual std::string print_value() const override;

    /**
     * \file
     * Логические операции (отрицание, пересечение, объединение...).
     */

    /**
     * \brief Оператор логического отрицания NOT (ГОСТ Р ИСО 10303-11-2009, \ref p11_s12_4_1 "12.4.1")
     * \result логическое выражение типа LOGICAL --- результат логического отрицания логического типа LOGICAL.
     *
     * Данный оператор выполняет функцию логического отрицания NOT (ГОСТ Р ИСО 10303-11-2009,
     * \ref p11_s12_4_1 "12.4.1").
     */
    LOGICAL operator!() const;

    /**
     * \brief Оператор логического пересечения AND (ГОСТ Р ИСО 10303-11-2009, 12.4.2)
     *
     * \ref express::LOGICAL::operator&&() "12.4.2 Оператор AND"
     *
     * Оператору \ref express::LOGICAL::operator&&() "AND" требуются два логических операнда, а результатом является логическое
     * значение, формируемое в соответствии с \ref p11_table13 "таблицей 13".
     * Оператор \ref express::LOGICAL::operator&&() "AND" является коммутативным.
     *
     * <BR>
     *
     * \anchor p11_table13
     * Т&nbsp;а&nbsp;б&nbsp;л&nbsp;и&nbsp;ц&nbsp;а 13 --- Оператор \ref express::LOGICAL::operator&&() "AND"
     *
     * <TABLE border="1" cellspacing="0">
     * <tr><td><CENTER>Операнд 1</CENTER>     </td><td><CENTER>Операнд 2</CENTER>     </td><td><CENTER>Результат</CENTER>     </td></tr>
     * <tr><td></td><td></td><td></td></tr>
     * <tr><td><CENTER><B>TRUE</B></CENTER>   </td><td><CENTER><B>TRUE</B></CENTER>   </td><td><CENTER><B>TRUE</B></CENTER>   </td></tr>
     * <tr><td><CENTER><B>TRUE</B></CENTER>   </td><td><CENTER><B>UNKNOWN</B></CENTER></td><td><CENTER><B>UNKNOWN</B></CENTER></td></tr>
     * <tr><td><CENTER><B>TRUE</B></CENTER>   </td><td><CENTER><B>FALSE</B></CENTER>  </td><td><CENTER><B>FALSE</B></CENTER>  </td></tr>
     * <tr><td><CENTER><B>UNKNOWN</B></CENTER></td><td><CENTER><B>TRUE</B></CENTER>   </td><td><CENTER><B>UNKNOWN</B></CENTER></td></tr>
     * <tr><td><CENTER><B>UNKNOWN</B></CENTER></td><td><CENTER><B>UNKNOWN</B></CENTER></td><td><CENTER><B>UNKNOWN</B></CENTER></td></tr>
     * <tr><td><CENTER><B>UNKNOWN</B></CENTER></td><td><CENTER><B>FALSE</B></CENTER>  </td><td><CENTER><B>FALSE</B></CENTER>  </td></tr>
     * <tr><td><CENTER><B>FALSE</B></CENTER>  </td><td><CENTER><B>TRUE</B></CENTER>   </td><td><CENTER><B>FALSE</B></CENTER>  </td></tr>
     * <tr><td><CENTER><B>FALSE</B></CENTER>  </td><td><CENTER><B>UNKNOWN</B></CENTER></td><td><CENTER><B>FALSE</B></CENTER>  </td></tr>
     * <tr><td><CENTER><B>FALSE</B></CENTER>  </td><td><CENTER><B>FALSE</B></CENTER>  </td><td><CENTER><B>FALSE</B></CENTER>  </td></tr>
     * </TABLE>
     */
    LOGICAL operator&&(const LOGICAL& rhs) const;

    /**
     * \brief Оператор логического объединения OR (ГОСТ Р ИСО 10303-11-2009, 12.4.3)
     *
     * \ref express::LOGICAL::operator||() "12.4.3 Оператор OR"
     *
     * Оператору \ref express::LOGICAL::operator||() "OR" требуются два логических операнда, а результатом является логическое значение,
     * формируемое в соответствии с \ref p11_table14 "таблицей 14". Оператор \ref express::LOGICAL::operator||() "OR" является коммутативным.
     *
     * <BR>
     *
     * \anchor p11_table14
     * Т&nbsp;а&nbsp;б&nbsp;л&nbsp;и&nbsp;ц&nbsp;а 14 --- Оператор \ref express::LOGICAL::operator||() "OR"
     *
     * <TABLE border="1" cellspacing="0">
     * <tr><td><CENTER>Операнд 1</CENTER>     </td><td><CENTER>Операнд 2</CENTER>     </td><td><CENTER>Результат</CENTER>    </td></tr>
     * <tr><td></td><td></td><td></td></tr>
     * <tr><td><CENTER><B>TRUE</B></CENTER>   </td><td><CENTER><B>TRUE</B></CENTER>   </td><td><CENTER><B>TRUE</B></CENTER>  </td></tr>
     * <tr><td><CENTER><B>TRUE</B></CENTER>   </td><td><CENTER><B>UNKNOWN</B></CENTER></td><td><CENTER><B>TRUE</B></CENTER>  </td></tr>
     * <tr><td><CENTER><B>TRUE</B></CENTER>   </td><td><CENTER><B>FALSE</B></CENTER>  </td><td><CENTER><B>TRUE</B></CENTER>  </td></tr>
     * <tr><td><CENTER><B>UNKNOWN</B></CENTER></td><td><CENTER><B>TRUE</B></CENTER>   </td><td><CENTER><B>TRUE</B></CENTER>  </td></tr>
     * <tr><td><CENTER><B>UNKNOWN</B></CENTER></td><td><CENTER><B>UNKNOWN</B></CENTER></td><td><CENTER><B>UNKNOWN</B></CENTER></td></tr>
     * <tr><td><CENTER><B>UNKNOWN</B></CENTER></td><td><CENTER><B>FALSE</B></CENTER>  </td><td><CENTER><B>UNKNOWN</B></CENTER></td></tr>
     * <tr><td><CENTER><B>FALSE</B></CENTER>  </td><td><CENTER><B>TRUE</B></CENTER>   </td><td><CENTER><B>TRUE</B></CENTER>   </td></tr>
     * <tr><td><CENTER><B>FALSE</B></CENTER>  </td><td><CENTER><B>UNKNOWN</B></CENTER></td><td><CENTER><B>UNKNOWN</B></CENTER></td></tr>
     * <tr><td><CENTER><B>FALSE</B></CENTER>  </td><td><CENTER><B>FALSE</B></CENTER>  </td><td><CENTER><B>FALSE</B></CENTER>  </td></tr>
     * </TABLE>
     */
    LOGICAL operator||(const LOGICAL& rhs) const;

    /**
     * \brief Оператор исключающего логического объединения XOR (ГОСТ Р ИСО 10303-11-2009, 12.4.4)
     *
     * \ref express::LOGICAL::operator^() "12.4.4 Оператор XOR"
     *
     * Оператору \ref express::LOGICAL::operator^() "XOR" требуются два логических операнда, а результатом является логическое значение,
     * формируемое в соответствии с \ref p11_table15 "таблицей 15". Оператор \ref express::LOGICAL::operator^() "XOR" является коммутативным.
     *
     * <BR>
     *
     * \anchor p11_table15
     * Т&nbsp;а&nbsp;б&nbsp;л&nbsp;и&nbsp;ц&nbsp;а 15 --- Оператор \ref express::LOGICAL::operator^() "XOR"
     *
     * <TABLE border="1" cellspacing="0">
     * <tr><td><CENTER>Операнд 1</CENTER>     </td><td><CENTER>Операнд 2</CENTER>     </td><td><CENTER>Результат</CENTER>     </td></tr>
     * <tr><td></td><td></td><td></td></tr>
     * <tr><td><CENTER><B>TRUE</B></CENTER>   </td><td><CENTER><B>TRUE</B></CENTER>   </td><td><CENTER><B>FALSE</B></CENTER>  </td></tr>
     * <tr><td><CENTER><B>TRUE</B></CENTER>   </td><td><CENTER><B>UNKNOWN</B></CENTER></td><td><CENTER><B>UNKNOWN</B></CENTER></td></tr>
     * <tr><td><CENTER><B>TRUE</B></CENTER>   </td><td><CENTER><B>FALSE</B></CENTER>  </td><td><CENTER><B>TRUE</B></CENTER>   </td></tr>
     * <tr><td><CENTER><B>UNKNOWN</B></CENTER></td><td><CENTER><B>TRUE</B></CENTER>   </td><td><CENTER><B>UNKNOWN</B></CENTER></td></tr>
     * <tr><td><CENTER><B>UNKNOWN</B></CENTER></td><td><CENTER><B>UNKNOWN</B></CENTER></td><td><CENTER><B>UNKNOWN</B></CENTER></td></tr>
     * <tr><td><CENTER><B>UNKNOWN</B></CENTER></td><td><CENTER><B>FALSE</B></CENTER>  </td><td><CENTER><B>UNKNOWN</B></CENTER></td></tr>
     * <tr><td><CENTER><B>FALSE</B></CENTER>  </td><td><CENTER><B>TRUE</B></CENTER>   </td><td><CENTER><B>TRUE</B></CENTER>   </td></tr>
     * <tr><td><CENTER><B>FALSE</B></CENTER>  </td><td><CENTER><B>UNKNOWN</B></CENTER></td><td><CENTER><B>UNKNOWN</B></CENTER></td></tr>
     * <tr><td><CENTER><B>FALSE</B></CENTER>  </td><td><CENTER><B>FALSE</B></CENTER>  </td><td><CENTER><B>FALSE</B></CENTER>  </td></tr>
     * </TABLE>
     */
    LOGICAL operator^(const LOGICAL& rhs) const;

    /**
     * \file
     * Проверки равенства экземпляров ':=:' и отношений значений.
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
     * \brief Проверка равенства значения значений логического типа LOGICAL
     * (или дочерних типов) с логическим типом LOGICAL (или дочерним типом)
     * \param rhs [in] Сравниваемый логический тип LOGICAL или BOOLEAN, переданный
     * через ссылку на тип LOGICAL.
     * \return Логическое выражение типа LOGICAL --- результат сравнения значений типа и rhs.
     */
    LOGICAL is_logical_value_equal(const LOGICAL& rhs) const;

    /**
     * \brief Проверка отношения значений логического типа LOGICAL '>'
     * (\ref p11_s12_2_1_3 "ГОСТ Р ИСО 10303-11-2009, п.12.2.1.3")
     * с логическим типом LOGICAL или булевым типом BOOLEAN, переданным через ссылку на тип LOGICAL.
     * \param [in] rhs Сравниваемый логический тип LOGICAL или BOOLEAN, переданный через ссылку на
     * родительский тип LOGICAL.
     * \return Результат сравнения значений данной величины и rhs. 
     */
    LOGICAL operator>(const LOGICAL& rhs) const;

    /**
     * \brief Проверка отношения значений логического типа LOGICAL '>='
     * (\ref p11_s12_2_1_3 "ГОСТ Р ИСО 10303-11-2009, п.12.2.1.3")
     * с логическим типом LOGICAL или булевым типом BOOLEAN, переданным через ссылку на тип LOGICAL.
     * \param [in] rhs Сравниваемый логический тип LOGICAL или BOOLEAN, переданный через ссылку на
     * родительский тип LOGICAL.
     * \return Результат сравнения значений данной величины и rhs. 
     */
    LOGICAL operator>=(const LOGICAL& rhs) const;

    /**
     * \brief Проверка отношения значений логического типа LOGICAL '<'
     * (\ref p11_s12_2_1_3 "ГОСТ Р ИСО 10303-11-2009, п.12.2.1.3")
     * с логическим типом LOGICAL или булевым типом BOOLEAN, переданным через ссылку на тип LOGICAL.
     * \param [in] rhs Сравниваемый логический тип LOGICAL или BOOLEAN, переданный через ссылку на
     * родительский тип LOGICAL.
     * \return Результат сравнения значений данной величины и rhs. 
     */
    LOGICAL operator<(const LOGICAL& rhs) const;

    /**
     * \brief Проверка отношения значений логического типа LOGICAL '<='
     * (\ref p11_s12_2_1_3 "ГОСТ Р ИСО 10303-11-2009, п.12.2.1.3")
     * с логическим типом LOGICAL или булевым типом BOOLEAN, переданным через ссылку на тип LOGICAL.
     * \param rhs [in] Сравниваемый логический тип LOGICAL или BOOLEAN, переданный через ссылку на
     * родительский тип LOGICAL.
     * \return Результат сравнения значений данной величины и rhs. 
     */
    LOGICAL operator<=(const LOGICAL& rhs) const;
  };
}