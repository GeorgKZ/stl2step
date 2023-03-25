/**
 * \file
 * \brief Файл с описанием простого типа данных BOOLEAN языка EXPRESS
 * (ГОСТ Р ИСО 10303-11-2009, 8.1.5; ГОСТ Р ИСО 10303-21, 6.3)
 */

namespace express {

  /** 
   * \brief Простой тип \ref express::BOOLEAN "BOOLEAN" --- булево значение (ГОСТ Р ИСО 10303-11-2009, 8.1.5)
   *
   * \anchor p11_s8_1_5
   *
   * \ref express::BOOLEAN "8.1.5 Булев тип данных"
   *
   * Областью определения типа данных \ref express::BOOLEAN "BOOLEAN" являются два литерала: \ref express::BOOLEAN.TRUE "TRUE" и
   * \ref express::BOOLEAN.FALSE "FALSE".
   * Тип данных \ref express::BOOLEAN "BOOLEAN" является конкретизацией типа данных \ref express::LOGICAL "LOGICAL".
   \verbatim
     Синтаксис:
      182 boolean_type = BOOLEAN .
   \endverbatim
   * Для значений типа данных \ref express::BOOLEAN "BOOLEAN" установлен тот же порядок, что и для значений типа данных
   * \ref express::LOGICAL "LOGICAL": \ref express::BOOLEAN.FALSE "FALSE" \< \ref express::BOOLEAN.TRUE "TRUE".
   *
   * <B><I>Пример --- В данном примере атрибут с именем</I> planar<I>, представлен типом данных</I> \ref express::BOOLEAN "BOOLEAN".
   * <I>Значением для</I> planar<I>, связанным с экземпляром</I> surface<I>, может быть либо</I>
   * \ref express::BOOLEAN.TRUE "TRUE"<I>, либо</I>
   * \ref express::BOOLEAN.FALSE "FALSE".
   <PRE>
       ENTITY surface;
         planar : BOOLEAN;
         ...
       END_ENTITY;
   </PRE> </B>
   */
  class BOOLEAN : public LOGICAL {

  protected:

    /** 
     *\brief Получить принадлёжность типа данных к одной из групп
     * \return тип данных в виде элемента перечисления OBJTYPE.
     */
    virtual constexpr OBJTYPE objtype() const override;

  public:

    static const value FALSE = value::F;
    static const value TRUE = value::T;

    /**
     * \file
     * Для типа BOOLEAN определены следующие члены-методы (функции):<BR><BR>
     */

    /**
     * Конструкторы (неопределённого значения, копирующий и конструктор из начения), деструктор и
     * оператор присваивания.
     */

    /**
     * \brief Конструктор булевого типа BOOLEAN по умолчанию, имеющего неопределённое
     * (<B>?</B>) значение
     */
    BOOLEAN();

    /**
     * \brief Копирующий конструктор булевого типа
     * \param [in] src Булев тип BOOLEAN
     */
    BOOLEAN(const BOOLEAN& src);

    /**
     * \brief Конструктор булевого типа BOOLEAN из булевых значений TRUE или FALSE
     * \param [in] src Источник --- булево значение TRUE или FALSE, которое будет присвоено.
     */
    BOOLEAN(value src);

    /**
     * \brief Деструктор булева типа --- по умолчанию.
     */
    virtual ~BOOLEAN() = default;

    /**
     * \brief Оператор присваивания булева типа BOOLEAN
     * \param [in] rhs Булев тип BOOLEAN.
     *
     * При выполнении присваивания проводится проверка на самоприсваивание.
     */
    BOOLEAN& operator=(const BOOLEAN& rhs);

    /**
     * \file
     * Получение значения типа, вывод значения типа в виде строки.
     */

    /**
     * \brief Проверка, имеет ли булев тип BOOLEAN значение UNKNOWN (всегда нет)
     * \return всегда false.
     */
    virtual bool is_unknown() const override;
  };
}