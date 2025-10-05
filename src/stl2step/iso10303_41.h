/**
 * \file
 *
 * \brief Заголовочный файл с определениями классов, соответствующих ГОСТ Р ИСО 10303-41-1999.
 *
 * <B>Раздел 1. Общие положения</B><BR>
 * <B>1.1 Область применения</B><BR>
 * Настоящий стандарт определяет:<BR>
 * * обобщенные ресурсы описания изделия (раздел 2);<BR>
 * * обобщенные ресурсы управления (раздел 3);<BR>
 * * ресурсы поддержки (раздел 4).<BR>
 * Схемы, определяемые в настоящем стандарте, организованы в соответствии с данными разделами.
 *
 * <B>1.1.1 Обобщенные ресурсы описания изделия</B><BR>
 * В разделе 1 настоящего стандарта установлены структуры ресурсов для высшего уровня структуры
 * представления изделия и определены их свойства. В разделе также определены интегрированные
 * ресурсы стандартов серии ГОСТ Р ИСО 10303 для описания общих аспектов использования изделий,
 * классификации изделий и взаимосвязей между изделиями.<BR>
 * Область применения раздела 1 охватывает:<BR>
 * * обозначение изделия;<BR>
 * * классификацию изделий;<BR>
 * * спецификацию определений изделия, взаимосвязей между изделиями и допустимых замен изделия;<BR>
 * * спецификацию представления образца изделия;<BR>
 * * спецификацию представления свойств изделия;<BR>
 * * описание прикладного контекста, в котором определены данные об изделии.
 *
 * <B>1.1.2 Обобщенные ресурсы управления</B><BR>
 * В разделе 1 настоящего стандарта установлены структуры ресурсов для структур, используемых
 * при связывании административных данных с данными об изделии.<BR>
 * Область применения раздела 1 охватывает:<BR>
 * * структуру для соединения в прикладном контексте данных об изделии с соответствующими
 * административными данными.
 *
 * <B>1.1.3 Ресурсы поддержки</B><BR>
 * В разделе 1 настоящего стандарта определены структуры ресурсов для административных данных,
 * физических величин и единиц физических величин (далее — единиц), а также для основных типов
 * данных.<BR>
 * Область применения раздела 1 охватывает:<BR>
 * * описание ссылок на документы;<BR>
 * * описание действий, запросов на действие и статуса действий;<BR>
 * * описание сертификации, утверждений, классификаций защиты и применимости;<BR>
 * * обозначение контрактов;<BR>
 * * обозначение людей и организаций;<BR>
 * * спецификации дат и времени;<BR>
 * * обеспечение механизмов группирования элементов и ссылок на информацию, определяемую
 * вне протокола обмена;<BR>
 * * определение физических величин и единиц физических величин.
 *
 * <B>1.2 Нормативные ссылки</B><BR>
 * В настоящем стандарте использованы ссылки на следующие стандарты:<BR>
 * ГОСТ Р ИСО 10301-1—99 Системы автоматизации производства и их интеграция. Представление
 * данных об изделии и обмен этими данными. Часть 1. Общие представления и основополагающие
 * принципы<BR>
 * ИСО 31-0—92 Физические величины и единицы физических величин<BR>
 * ИСО 1000—810 Единицы физических величин в системе СИ и рекомендации по применению
 * кратных им и некоторых других единиц<BR>
 * ИСО 8601—88 Элементы данных и форматы обмена. Обмен информацией. Представление дат и
 * времени<BR>
 * ИСО/МЭК 8824-1—95 Информационная технология. Взаимосвязь открытых систем. Абстрактная
 * синтаксическая нотация версии один (АСН. 1). Часть 1. Требования к основной нотации
 * ИСО 10303-11—94 Системы автоматизации производства и их интеграция. Представление
 * данных об изделии и обмен этими данными. Часть 11. Справочное руководство по языку EXPRESS<BR>
 * ИСО 10303-41—94 Системы автоматизации производства и их интеграция. Представление
 * данных об изделии и обмен этими данными. Часть 41. Интегрированные обобщенные ресурсы. Основы
 * описания и поддержки изделий<BR>
 * ИСО 10303-43—94 Системы автоматизации производства и их интеграция. Представление
 * данных об изделии и обмен этими данными. Часть 43. Интегрированные ресурсы. Структуры представления<BR>
 * ИСО 10303-44—94 Системы автоматизации производства и их интеграция. Представление
 * данных об изделии и обмен этими данными. Часть 44. Интегрированные ресурсы. Конфигурация
 * структуры изделия
 *
 * <B>1.3 Определения и сокращения</B><BR>
 * <B>1.3.1 Термины, определенные в ГОСТ Р ИСО 10303-1</B><BR>
 * В настоящем стандарте использованы следующие термины, определенные в ГОСТ Р ИСО
 * 10303-1:<BR>
 * * приложение;
 * * прикладной контекст;
 * * прикладная интерпретированная модель;
 * * прикладной протокол;
 * * прикладная эталонная модель;
 * * интерпретация;
 * * изделие.
 *
 * <B>1.3.2 Термины, определенные в ИСО 8601</B><BR>
 * В настоящем стандарте использованы следующие термины, определенные в ИСО 8601:<BR>
 * * календарная дата;
 * * упорядоченная дата;
 * * секунда;
 * * минута;
 * * час;
 * * день;
 * * неделя;
 * * календарная неделя;
 * * месяц;
 * * год;
 * * календарный год;
 * * обычный год;
 * * високосный год;
 * * локальное время;
 * * скоординированное универсальное время;
 * * Григорианский календарь.
 *
 * <B>1.3.3 Сокращения, установленные в ИСО 1000</B><BR>
 * В настоящем стандарте использованы следующие сокращения, установленные в ИСО 1000:<BR>
 * * СИ (SI) — Международная система единиц
 *
 * <B>Раздел 2 ОБЩИЕ РЕСУРСЫ ОПИСАНИЯ ИЗДЕЛИЯ</B><BR>
 * <B>2.1 Введение</B><BR>
 * В разделе 2 определены интегрированные ресурсы стандартов серии ГОСТ Р ИСО 10303,
 * используемые для высшего уровня описания изделия. Раздел 2 охватывает следующие схемы:<BR>
 * * <B>application_context_schema;</B>
 * * <B>product_definition_schema;</B>
 * * <B>product_property_definition_schema;</B>
 * * <B>product_property_representation_schema.</B>
 *
 * Схема <B>application_context_schema</B> поддерживает описание соответствующего применения данных
 * об изделии.<BR>
 * Схема <B>product_definition_schema</B> поддерживает описание обозначений изделий, классификацию
 * изделий и отношения между определениями изделий.<BR>
 * Схема <B>productjroperty_definition_schema</B> поддерживает описание характеристик изделия.<BR>
 * Схема product_property_representation_schema описывает структуру для представления
 * характеристик формы изделия.<BR>
 * <SMALL>Примечания<BR>
 * 1 Настоящий стандарт не ограничен областью конкретного прикладного контекста. Читателя не
 * должны вводить в заблуждение умышленно ограниченные области применения примеров.<BR>
 * 2 Способ сочетания ресурсов поддержки с обобщенными ресурсами описания изделия - в
 * соответствии с приложением E.</SMALL>
 *
 * <B>2.2 application context schema</B><BR>
 *
 * Следующее описание на языке EXPRESS, являющееся началом <B>application_context_schema</B>,
 * определяет необходимые внешние ссылки.<BR>
 * <U>EXPRESS-спецификация:</U>
 * \verbatim
  *)
  SCHEMA application context schema;
  REFERENCE FROM supportresourceschem a
      (label,
       text);
  REFERENCE FROM date_time_schema
      (yearnumber);
  (*
 \endverbatim
 *
 * <SMALL>Примечания<BR>
 * 1 Схемы, на которые выше даны ссылки, можно найти в следующих пунктах настоящего стандарта:<BR>
 * <B>support_resource_schema</B> - 4.13;<BR>
 * <B>date_time_schema</B> - 4.9.<BR>
 * 2 Графическое представление настоящей схемы приведено на рисунке F.1 приложения F.<BR>
 * 3 Настоящая схема является одной их схем обобщенных ресурсов описания изделия. Связи между
 * схемами обобщенных ресурсов описания изделия приведены в приложении D.</SMALL>
 *
 * <B>2.2.1 Введение</B><BR>
 * В настоящем пункте установлены требования к <B>application_context_schema</B>. Данная схема
 * определяет механизм прикладных протоколов для определения системы ссылок или контекста,
 * которые применяются к конкретным наборам данных об изделии. Общий прикладной контекст имеет
 * несколько элементов контекста. Каждый элемент контекста может ссылаться на различный вид
 * данных об изделии.<BR>
 * Пользователям данных об изделии должны быть предоставлены средства для определения
 * прикладной интерпретированной модели в терминах, используемых при определении данных об изделии.
 *
 * <B>2.2.2 Фундаментальные понятия и допущения</B><BR>
 * Осмысленный обмен данными об изделии требует установления прикладного контекста, в
 * котором определяются данные об изделии. Одним из элементов прикладного контекста является
 * используемая прикладная интерпретированная модель. Каждая прикладная интерпретированная модель
 * принадлежит одному и только одному прикладному протоколу. Поскольку все прикладные
 * интерпретированные модели имеют уникальные имена в стандартах серии ГОСТ Р ИСО 10303, обозначение
 * имени схемы прикладной интерпретированной модели также уникально идентифицирует прикладной
 * протокол. Приложениям, использующим данные об изделии, требуется информация, которая обозначает
 * прикладную интерпретированную модель, определяющую содержимое и логическую структуру
 * данных об изделии.
 *
 * 2.2.3 Определения объекта <B>application_context_schema</B>
 */

namespace express {

   /**
    * \brief  ENTITY application_context (ГОСТ Р ИСО 10303-41-1999, 2.2.3.1)
    *
    * <B>2.2.3.1 application_context</B><BR>
    * Объект <B>\ref application_context</B> является контекстом, в котором определены данные об изделии. Объект
    * <B>\ref application_context</B> представляет разные типы информации, которые связаны с данными об изделии и
    * могут влиять на смысл и использование этих данных.<BR>
    * <U>EXPRESS-спецификация:</U>
    * \verbatim
     ENTITY application_context;
           application : label;
        DERIVE
           description : text := get_description_value(SELF);
           id : identifier := get_id_value(SELF);
        INVERSE
           context_elements : SET [1:?] OF application_context_element FOR frame_of_reference;
        WHERE
           WR1:
              SIZEOF(USEDIN(SELF, 'STEP_MERGED_AP_SCHEMA.DESCRIPTION_ATTRIBUTE.DESCRIBED_ITEM')) <= 1;
           wr2:
              SIZEOF(USEDIN(SELF, 'STEP_MERGED_AP_SCHEMA.ID_ATTRIBUTE.IDENTIFIED_ITEM')) <= 1;
     END_ENTITY;
    \endverbatim
    * <U>Определения атрибутов:</U><BR>
    * <B>\ref application</B> - описание использования данных об изделии;<BR>
    * <B>context_elements</B> - имеется хотя бы один appIication_context_eIement, связанный с
    * <B>\ref application_context</B>
    *
    * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_application_context.html">Ссылка.</A>
    */
  class application_context : public STEP_ENTITY {
  private:

    /** \brief Описание использования данных об изделии. */
    const label* application;

  public:

    /**
     * \brief Конструктор.
     *
     * \param [in] Application Описание использования данных об изделии.
     */
    application_context(const std::string& Application);

    /** \brief Деструктор. */
    virtual ~application_context();

    //FUNCTION get_description_value
    //      (obj : description_attribute_select ) : text;
    //   LOCAL
    //      description_bag : BAG OF description_attribute := USEDIN(obj, 'STEP_MERGED_AP_SCHEMA.DESCRIPTION_ATTRIBUTE.DESCRIBED_ITEM');
    //   END_LOCAL;
    //      IF SIZEOF(description_bag) = 1 THEN
    //         RETURN (description_bag[1].attribute_value);
    //      ELSE
    //         RETURN (?);
    //      END_IF;
    //END_FUNCTION;
    // STEP_text get_description_value() {
    //}

    //FUNCTION get_id_value
    //      (obj : id_attribute_select ) : identifier;
    //   LOCAL
    //      id_bag : BAG OF id_attribute := USEDIN(obj, 'STEP_MERGED_AP_SCHEMA.ID_ATTRIBUTE.IDENTIFIED_ITEM');
    //   END_LOCAL;
    //      IF SIZEOF(id_bag) = 1 THEN
    //         RETURN (id_bag[1].attribute_value);
    //      ELSE
    //         RETURN (?);
    //      END_IF;
    //END_FUNCTION;
    // STEP_identifier get_id_value() {
    //}
  };

  /**
   * \brief ENTITY application_protocol_definition (ГОСТ Р ИСО 10303-41-1999, 2.2.3.2)
   *
   * <B>2.2.3.2 application_protocol_definition</B><BR>
   * Объект <B>application_protocol_definition</B> является определением прикладного протокола.<BR>
   * <U>EXPRESS-спецификация:</U>
   * \verbatim
    ENTITY application_protocol_definition;
          status : label;
          application_interpreted_model_schema_name : label;
          application_protocol_year : year_number;
          application : application_context;
    END_ENTITY;
   \endverbatim
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_application_protocol_definition.html">Ссылка.</A>
   */
  class application_protocol_definition : public STEP_ENTITY {

  private:

    /**
     * \brief Классификация прикладного протокола с позиций его принятия некоторым утверждающим органом.
     *
     * <SMALL>Примечания<BR>
     * <OL><LI>Допустимые  значения  этого  атрибута установлены в прикладных интерпретированных моделях,
     * использующих данный объект.</LI>
     * <LI>Основное допущение (см. 2.2.2) о том, что имя схемы прикладной интерпретированной модели уникально
     * обозначает прикладной  протокол, справедливо только для прикладных протоколов стандартов серии ГОСТ Р ИСО 10303.</LI></OL></SMALL>
     */
    const label* status;
    /** \brief Имя EXPRESS-схемы прикладной интерпретированной модели. */
    const label* application_interpreted_model_schema_name;
    /** \brief Год, в котором прикладной протокол получил статус, заданный атрибутом <B>status</B>. */
    const year_number* application_protocol_year;
    /** \brief Прикладной контекст прикладного протокола. */
    const application_context* application;

  public:

    /**
     * \brief Конструктор.
     *
     * \param [in] Status Классификация прикладного протокола с позиций его принятия некоторым утверждающим органом.
     * \param [in] Name Имя EXPRESS-схемы прикладной интерпретированной модели.
     * \param [in] Year Год, в котором прикладной протокол получил статус, заданный атрибутом <B>status</B>.
     * \param [in] Application Прикладной контекст прикладного протокола.
     */
    application_protocol_definition(const std::string& Status, const std::string& Name, int Year, const application_context* Application);

    /** \brief Деструктор. */
    virtual ~application_protocol_definition();
  };

  /**
   * \brief ENTITY application_context_element (ГОСТ Р ИСО 10303-41-1999, 2.2.3.3)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
    ENTITY application_context_element
       SUPERTYPE OF (ONEOF(product_concept_context, product_context, product_definition_context));
          name : label;
          frame_of_reference : application_context;
    END_ENTITY;
   \endverbatim
   *
   * Объект <B>application_context_element</B> является видом прикладного контекста,
   * в котором определены данные об изделии. Ряд <B>application_context_element</B> может
   * представлять несколько различных видов прикладного контекста. Прикладной
   * протокол может устанавливать контекст данных, используя подтипы объекта
   * <B>application_context_element:
   * <BR><OL><LI>product_context;</LI>
   * <LI>product_definition_context</LI>
   * <LI>product_concept_context</LI>
   * <LI>library_context.</LI></OL></B>
   * <BR><SMALL>Примечание - При использовании данного объекта прикладной протокол
   * отвечает за соответствующее ограничение значений этих атрибутов на основе их
   * допустимого использования.</SMALL>
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_application_context_element.html">Ссылка.</A>
   */
  class application_context_element : public STEP_ENTITY {

  private:

    /** \brief Обозначение детализированного контекста, в котором существуют данные об изделии. */
    const label* name;
    /** \brief Общий контекст, частью которого является <B>application_context_element</B>. */
    const application_context* frame_of_reference;

  public:

    /**
     * \brief Конструктор.
     *
     * \param [in] Name Обозначение детализированного контекста, в котором существуют данные об изделии.
     * \param [in] Frame Общий контекст, частью которого является <B>application_context_element</B>.
     */
    application_context_element(const std::string& Name, const application_context* Frame);

    /** \brief Деструктор. */
    virtual ~application_context_element();
  };

  /**
   * \brief ENTITY product_context (ГОСТ Р ИСО 10303-41-1999, 2.2.3.4)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
     ENTITY product_context
       SUBTYPE OF (application_context_element);
          discipline_type : label;
    END_ENTITY;
   \endverbatim
   *
   * Подтип <B>product_context</B> является видом <B>application_context</B>, определяющим
   * контекст для <B>product</B>.
   * <BR><SMALL>Примечание 1 - Объект <B>product</B> определен в 2.3.4.1 настоящего стандарта.</SMALL><BR>
   * Подтип <B>product_context</B> представляет информацию о технических или производственных перспективах,
   * относящихся к данным об изделии, которые могут повлиять на смысл и использование этих данных.
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_product_context.html">Ссылка.</A>
   */
  class product_context : public application_context_element {

  private:

    /**
     * \brief Обозначение технической или производственной категории, к которой принадлежит <B>product</B>.
     *
     * <SMALL>Примечание 2 - Допустимые значения данного атрибута определены в прикладных интерпретированных
     * моделях, использующих данный объект.</SMALL>
     */
    const label* discipline_type;

  public:

    /**
     * \brief Конструктор.
     *
     * \param [in] Name Обозначение детализированного контекста, в котором существуют данные об изделии.
     * \param [in] Frame Общий контекст, частью которого является <B>application_context_element</B>.
     * \param [in] Type Обозначение технической или производственной категории, к которой принадлежит <B>product</B>.
     */
    product_context(const std::string& Name, const application_context* Frame, const std::string& Type);

    /** \brief Деструктор. */
    virtual ~product_context();
  };

  /**
   * \brief ENTITY product_definition_context (ГОСТ Р ИСО 10303-41-1999, 2.2.3.5)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
    ENTITY product_definition_context
       SUBTYPE OF (application_context_element);
          life_cycle_stage : label;
    END_ENTITY;
   \endverbatim
   *
   * Подтип <B>product_definition_context</B> является видом <B>application_context</B>,
   * определяющим контекст для <B>product_definition</B>.
   * <BR><SMALL>Примечание 1 - Объект <B>product_definition</B> определен в 2.3.4.8 настоящего стандарта.</SMALL><BR>
   * Данный контекст представляет информацию о стадии жизненного цикла изделия, к которой относятся данные
   * об изделии. Такая информация может влиять на смысл и использование данных об изделии.
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_product_definition_context.html">Ссылка.</A>
   */
  class product_definition_context : public application_context_element {

  private:

    /**
     * \brief Обозначение общей стадии жизненного цикла изделия, к которой относятся данные об изделии.
     *
     * <SMALL>Примечание 2 - Допустимые значения данного атрибута определены в прикладных интерпретированных моделях,
     * использующих данный объект.</SMALL>
     */
    const label* life_cycle_stage;

  public:

    /**
     * \brief Конструктор.
     *
     * \param [in] Name Обозначение детализированного контекста, в котором существуют данные об изделии.
     * \param [in] Frame Общий контекст, частью которого является <B>application_context_element</B>.
     * \param [in] Stage Обозначение общей стадии жизненного цикла изделия, к которой относятся данные об изделии.
     */
    product_definition_context(const std::string& Name, application_context* Frame, const std::string& Stage);

    /** \brief Деструктор. */
    virtual ~product_definition_context();
  };

  /**
   * \brief ENTITY product_concept_context (ГОСТ Р ИСО 10303-41-1999, 2.2.3.6)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
    ENTITY product_concept_context
       SUBTYPE OF (application_context_element);
          market_segment_type : label;
    END_ENTITY;
   \endverbatim
   *
   * Подтип <B>product_concept_context</B> является видом <B>application_context</B>, определяющим контекст для
   * <B>product_concept</B>.
   * <BR><SMALL>Примечание - Объект <B>product_concept</B> определен в ИСО 10303-44.</SMALL><BR>
   * Подтип <B>product_concept_context</B> представляет информацию, связанную с характеристикой потенциальных
   * покупателей изделия. Такая информация может влиять на смысл и использование данных об изделии.
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_product_concept_context.html">Ссылка.</A>
   */
  class product_concept_context : public application_context_element {

  private:

    /** \brief Обозначение категории, характеризующей потенциальных покупателей изделия. */
    const label* market_segment_type;

  public:

    /**
     * \brief Конструктор.
     *
     * \param [in] Name Обозначение детализированного контекста, в котором существуют данные об изделии.
     * \param [in] Frame Общий контекст, частью которого является <B>application_context_element</B>.
     * \param [in] Type Обозначение категории, характеризующей потенциальных покупателей изделия.
     */
    product_concept_context(const std::string& Name, application_context* Frame, const std::string& Type);

    /** \brief Деструктор. */
    virtual ~product_concept_context();
  };

  /**
   * \brief ENTITY library_context (ГОСТ Р ИСО 10303-41-1999, 2.2.3.7)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
    ENTITY library_context
       SUBTYPE OF (application_context_element);
          library_reference : label;
    END_ENTITY;
   \endverbatim
   *
   * Подтип <B>library_context</B> - это вид <B>application_context</B>, определяющий контекст для элементов
   * библиотеки. Подтип <B>library_context</B> представляет информацию, которая может влиять на смысл и
   * использование данных об изделии в библиотеке.
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_library_context.html">Ссылка.</A>
   */
  class library_context : public application_context_element {

  private:

    /** \brief Обозначение библиотеки, обеспечивающее контекст для элементов библиотеки. */
    const label* library_reference;

  public:

    /**
     * \brief Конструктор.
     *
     * \param [in] Name Обозначение детализированного контекста, в котором существуют данные об изделии.
     * \param [in] Frame Общий контекст, частью которого является <B>application_context_element</B>.
     * \param [in] Reference Обозначение библиотеки, обеспечивающее контекст для элементов библиотеки.
     */
    library_context(const std::string& Name, const application_context* Frame, const std::string& Reference);

    /** \brief Деструктор. */
    virtual ~library_context();
  };

  /*
   * product_definition_schema (ГОСТ Р ИСО 10303-41-1999, 2.3)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
    SCHEMA product_definition_schema;
    REFERENCE FROM application_context_schema
      (product_context,
       product_definition_context);
    REFERENCE FROM document_schema
      (document);
    REFERENCE FROM effectivity_schema
      (effectivity);
    REFERENCE FROM support_resource_schema
      (bag_to_set,
       identifier,
       label,
       text);
   \endverbatim
   */

   /*
   * Введение (ГОСТ Р ИСО 10303-41-1999, 2.3.1)
   *
   * Фундаментальные понятия и допущения (ГОСТ Р ИСО 10303-41-1999, 2.3.2)
   */

   /**
    * \brief TYPE source (ГОСТ Р ИСО 10303-41-1999, 2.3.3)
    *
    * <B>Определение объекта на языке EXPRESS:</B>
    * \verbatim
     TYPE source = ENUMERATION OF
       (made,
        bought,
        not_known);
     END_TYPE;
    \endverbatim
    *
    * Тип <B>source</B> представляет, является ли <B>product_definition_formation</B> изготовляемым в организации
    * или покупным. Возможные значения ограничены представлением этих двух возможностей либо фактом,
    * что данная информация неизвестна.
    *
    * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_source.html">Ссылка.</A>
    */
  class source : public ENUMERATION {

  public:

    enum class val {
      made = 0,
      bought,
      not_known
    };

  private:

    val x_;

  public:

    /**
     * \brief Конструктор.
     * \param [in] v Устанавливаемое значение.
     */
    source(val v) : x_(v) {
    }

    /** \brief Деструктор. */
    virtual ~source() {
    }

    /**
     * \brief Получить значение типа <B>source</B>.
     * \return значение типа <B>source</B>.
     */
    val getval() const {
      return x_;
    }

    /**
     * \brief Вывод значения типа <B>source</B>.
     * \return строку, содержащую значение типа <B>source</B>.
     */
    std::string print_value() const {
      std::stringstream s;
      switch (x_) {
      case val::made:      s << ".MADE.";      break;
      case val::bought:    s << ".BOUGHT.";    break;
      case val::not_known: s << ".NOT_KNOWN."; break;
      default:             s << "";            break;
      }
      return s.str();
    }
  };


  /*
   * Определение объектов product_definition_schema (ГОСТ Р ИСО 10303-41-1999, 2.3.4)
   */

   /**
    * \brief ENTITY product (ГОСТ Р ИСО 10303-41-1999, 2.3.4.1)
    *
    * <B>2.3.4.1 \ref product</B><BR>
    * Объект <B>\ref product</B> является обозначением и описанием в прикладном контексте
    * физически реализуемого объекта, создаваемого в процессе.
    *
    * <U>EXPRESS-спецификация:</U>
    * \verbatim
     ENTITY product;
           id                 : identifier;
           name               : label;
           description        : OPTIONAL text;
           frame_of_reference : SET [1:?] OF product_context;
     END_ENTITY;
    \endverbatim
    *
    * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_product.html">Ссылка.</A>
    */

  class product : public STEP_ENTITY {

  private:

    /** \brief Обозначение изделия. */
    const identifier* id;
    /** \brief Слово или группа слов для ссылок на <B>product</B> (изделие). */
    const label* name;
    /** \brief Текст, связанный с природой изделия. */
    const text* description;
    /** \brief Контексты, в которых определяется изделие. */
    LIST<const product_context>* frame_of_reference;

  public:

    //!!! "$"?

    /**
     * \brief Конструктор.
     * \param [in] Id Обозначение изделия.
     * \param [in] Name Текст, связанный с природой изделия.
     * \param [in] Description Текст, связанный с природой изделия.
     */
    product(const std::string& Id, const std::string& Name, const std::string& Description = "$");

    /** \brief Деструктор. */
    virtual ~product();

    /** \brief Добавить контекст определения издения. */
    void add_frame(const product_context* x);
  };

  /**
   * \brief ENTITY product_category (ГОСТ Р ИСО 10303-41-1999, 2.3.4.2)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
    -- IN AP203e2/AP214/AP232/AP238 STEP-NC/AP242
    ENTITY product_category;
          name : label;
          description : OPTIONAL text;
       DERIVE
          id : identifier := get_id_value(SELF);
       WHERE
          WR1:
             SIZEOF(USEDIN(SELF, 'STEP_MERGED_AP_SCHEMA.ID_ATTRIBUTE.IDENTIFIED_ITEM')) <= 1;
    END_ENTITY;
   \endverbatim
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_product_category.html">Ссылка.</A>
   */
  class product_category : public STEP_ENTITY {

  private:

    /** \brief Слово или группа слов для ссылок на <B>product_category</B>. */
    const label* name;
    /** \brief Текст, связанный с природой <B>product_category</B>. */
    const text* description;

  public:

    //!!! "$"?

    /**
     * \brief Конструктор.
     * \param [in] Name Слово или группа слов для ссылок на <B>product_category</B>.
     * \param [in] Description Текст, связанный с природой <B>product_category</B>.
     */
    product_category(const std::string& Name, const std::string& Description = "$");

    /** \brief Деструктор. */
    virtual ~product_category();
  };

  /**
   * \brief ENTITY product_related_product_category (ГОСТ Р ИСО 10303-41-1999, 2.3.4.3)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
    -- IN AP203e2/AP214/AP232/AP238 STEP-NC/AP242
    ENTITY product_related_product_category
       SUBTYPE OF (product_category);
          products : SET [1:?] OF product;
    END_ENTITY;
   \endverbatim
   *
   * Объект <B>product_reIated_product_category</B> является <B>product_category</B>, содержащей изделия.
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_product_related_product_category.html">Ссылка.</A>
   */
  class product_related_product_category : public product_category {

  private:

    /** \brief изделия, принадлежащие <B>product_related_product_category</B>. */
    LIST<const product>* products;

  public:

    /**
     * \brief Конструктор.
     * \param [in] Name Слово или группа слов для ссылок на <B>product_category</B>.
     * \param [in] Description Текст, связанный с природой <B>product_category</B>.
     */
    product_related_product_category(const std::string& Name, const std::string& Description = "");

    /** \brief Деструктор. */
    virtual ~product_related_product_category();

    /** \brief Добавить изделие, принадлежащее <B>product_related_product_category</B>. */
    void add_product(const product* x);
  };


  /**
   * \brief ENTITY product_category_relationship (ГОСТ Р ИСО 10303-41-1999, 2.3.4.4)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
    ENTITY product_category_relationshiр;
      name            :label;
      description     :text;
      vategory        :product_category;
      sub_category    :product_category;
    WHERE
      WR1 : acyclic_product_category_relationship (SELF, [SELF.sub_category]);
    END_ENTITY;
   \endverbatim
   * Объект <B>product_category_relationship</B> является отношением между двумя классами изделий. О&ьект
   * <B>product_category</B> может быть определен как подкласс по отношению к другим <B>product_category</B>.
   * <BR>Используя данный объект, можно определять сети product_category.
   * <BR>Если изделие принадлежит product_category, то оно также принадлежит всем родительским
   * <B>product_category</B> данной <B>product_category</B>.
   * <BR><SMALL>Примечание - Данный объект совместно с объектом <B>product_category</B> основан на шаблоне
   * отношений, описанном в приложении D.</SMALL>
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_product_category_relationship.html">Ссылка.</A>
   */
  class product_category_relationship : public STEP_ENTITY {

  private:

    /** \brief Слово или группа слов для ссылок на <B>product_category_relationship</B>. */
    const label* name;
    /** \brief Текст, связанный с природой <B>product_category_relationship</B>. */
    const text* description;
    /** \brief Родитель для <B>sub_category</B> */
    const product_category* category;
    /** \brief Порождение <B>category</B> */
    const product_category* sub_category;

  public:

    /**
     * \brief Конструктор.
     *
     * \param [in] Name Слово или группа слов для ссылок на <B>product_category</B>.
     * \param [in] Description Текст, связанный с природой <B>product_category</B>.
     * \param [in] Category Родитель для <B>sub_category</B>
     * \param [in] SubCategory Порождение <B>category</B>
     */
    product_category_relationship(const std::string& Name, const std::string& Description, const product_category* Category, const product_category* SubCategory);

    /** \brief Деструктор. */
    virtual ~product_category_relationship();
  };

  /**
   * \brief ENTITY product_definition_formation (ГОСТ Р ИСО 10303-41-1999, 2.3.4.5)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
    -- CASE DIFF IN AP214
    -- CASE DIFF IN AP224
    -- CASE DIFF IN AP232
    ENTITY product_definition_formation;
          id : identifier;
          description : OPTIONAL text;
          of_product : product;
       UNIQUE
          UR1 : id, of_product;
    END_ENTITY;
   \endverbatim
   *
   * Объект <B>product_deflnition_formation</B> обозначает группу <B>product_definition</B> для изделия. Каждое из
   * <B>product_definition</B> в группе имеет индивидуальный <B>frame_of_reference</B> (и поэтому <B>life_cycle_stage</B>) или
   * включает в себя некоторые варианты данных свойств.
   * <BR><SMALL>Примечание — Назначение <B>product_definition_formation</B> определено в прикладных
   * интерпретированных моделях, использующих данный объект.</SMALL>
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_product_definition_formation.html">Ссылка.</A>
   */
  class product_definition_formation : public STEP_ENTITY {

  private:

    /** \brief Уникальное обозначение <B>product_definition_formation</B> в контексте изделия, к которому оно относится. */
    identifier* id;
    /**
     * \brief Текст, связанный с характером <B>product_definition_formation</B>.
     *
     * <SMALL>Примечание 1 — Описания различных конструкций одного изделия должны устанавливать
     * отличия в назначении и функциях каждой конструкции.</SMALL>
     */
    text* description;
    /**
     * \brief Изделие, вариантом которого является product_definition_formation.
     *
     * <SMALL>Примечание 2 — Изделие связано с одним или несколькими <B>product_defmition_formation</B> посредством
     * наличия неявной обратной связи.</SMALL>
     */
    const product* of_product;

  public:

    /**
     * \brief Конструктор.
     * \param [in] Id Уникальное обозначение <B>product_definition_formation</B> в контексте изделия, к которому оно относится.
     * \param [in] Description Текст, связанный с характером <B>product_definition_formation</B>.
     * \param [in] Of_product Изделие, вариантом которого является product_definition_formation.
     */
    product_definition_formation(const std::string& Id, const std::string& Description, const product* Of_product);

    /** \brief Деструктор. */
    virtual ~product_definition_formation();
  };

  /*
   * \brief ENTITY product_definition_formation_relationship (ГОСТ Р ИСО 10303-41-1999, 2.3.4.6)
   */

   /*
    * \brief ENTITY product_definition_formation_with_specified_source (ГОСТ Р ИСО 10303-41-1999, 2.3.4.7)
    */

    /**
     * \brief ENTITY product_definition (ГОСТ Р ИСО 10303-41-1999, 2.3.4.8)
     *
     * <B>Определение объекта на языке EXPRESS:</B>
     * \verbatim
      -- DIFF IN AP214
      -- DIFF IN AP203e2
      -- DIFF IN AP238 STEP-NC
      -- DIFF IN AP224
      -- DIFF IN AP232
      ENTITY product_definition
         SUPERTYPE OF (ONEOF(composite_assembly_sequence_definition, laminate_table, ply_laminate_sequence_definition));
            id : identifier;
            description : OPTIONAL text;
            formation : product_definition_formation;
            frame_of_reference : product_definition_context;
         DERIVE
            name : label := get_name_value(SELF);
         WHERE
            WR1:
               SIZEOF(USEDIN(SELF, 'STEP_MERGED_AP_SCHEMA.NAME_ATTRIBUTE.NAMED_ITEM')) <= 1;
      END_ENTITY;
     \endverbatim
     *
     * Объект <B>product_definition</B> является обозначением характеристики изделия в конкретном прикладном контексте.
     * <BR><SMALL>Примечание — Объект <B>product_definition</B> характеризуется свойствами, которые ему приписывают.</SMALL>
     *
     * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_product_definition.html">Ссылка.</A>
     */
  class product_definition : public STEP_ENTITY {

  private:

    /** \brief обозначение <B>product_definition</B> */
    identifier* id;
    /** \brief текст, связанный с характером <B>product_definition</B> */
    text* description;
    /** \brief <B>product_definition_formation</B>, с которой связано product_definition */
    const product_definition_formation* formation;
    /** \brief <B>product_definition_context</B>, в котором используются <B>product_definition</B> или данные из <B>product_definition</B> */
    const product_definition_context* frame_of_reference;

  public:

    /** \brief Конструктор */
    product_definition(const std::string& Id, const std::string& Description,
      const product_definition_formation* Formation,
      const product_definition_context* Frame_of_reference);

    /** \brief Деструктор */
    virtual ~product_definition();
  };



  /**
   * \brief TYPE product_definition_or_reference (ISO 10303-41:2021(E), 21.3.1)
   *
   * <B>21.3.1 product_definition_or_reference</B><BR>
   * The <B>product_definition_or_reference</B> type is an extensible list of alternate data types.
   * It provides a mechanism to refer to instances of the data types included in the <B>product_definition_or_reference</B>
   * type or in its extensions.
   *
   * <SMALL><B>NOTE</B> The list of entity data types will be extended in application resources that
   * use the constructs of this resource.</SMALL>
   *
   * <U>EXPRESS specification:</U>
   * \verbatim
    -- IN AP238 STEP-NC/AP242
    TYPE product_definition_or_reference = SELECT
          (generic_product_definition_reference,
           product_definition,
           product_definition_occurrence);
    END_TYPE;
   \endverbatim
   *!!! EXTENSIBLE GENERIC_ENTITY SELECT?
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_product_definition_or_reference.html">Ссылка.</A>
   */
  class product_definition_or_reference : public SELECT {

  public:

    STEP_TYPE_SELECT_CONSTRUCTOR_DEF(product_definition_or_reference, generic_product_definition_reference);
    STEP_TYPE_SELECT_CONSTRUCTOR_DEF(product_definition_or_reference, product_definition);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(product_definition_or_reference, product_definition_occurrence);
  };



  /*
   * \brief ENTITY product_definition_with_associated_documents (ГОСТ Р ИСО 10303-41-1999, 2.3.4.9)
   */

   /**
    * \brief ENTITY product_definition_relationship (ГОСТ Р ИСО 10303-41-1999, 2.3.4.10)
    *
    * <B>Определение объекта на языке EXPRESS:</B>
    * \verbatim
     -- DIFF IN AP214
     -- DIFF IN AP203e2
     -- DIFF IN AP224
     -- DIFF IN AP232
     ENTITY product_definition_relationship;
           id : identifier;
           name : label;
           description : OPTIONAL text;
           relating_product_definition : product_definition_or_reference;
           related_product_definition : product_definition_or_reference;
     END_ENTITY;
    \endverbatim
    *
    */
  class product_definition_relationship : public STEP_ENTITY {
  private:
    // Explicit
    identifier* id;                            // Уникальный идентификатор взаимосвязи
    label* name;                          // Номенклатурное имя
    text* description;                   // Дополнительное описание взаимосвязи
    const product_definition_or_reference* relating_product_definition;   // Ссылка на родительский объект
    const product_definition_or_reference* related_product_definition;    // Ссылка на элемент

  public:

    /** \brief Конструктор */
    product_definition_relationship(identifier Id, label Name, text Description,
      const product_definition_or_reference* Relating_product_definition,
      const product_definition_or_reference* Related_product_definition);

    /** \brief Деструктор */
    virtual ~product_definition_relationship();
  };

  /*
   * \brief ENTITY product_defmition_substitute (ГОСТ Р ИСО 10303-41-1999, 2.3.4.11)
   */

   /*
    * \brief ENTITY product_definition_effectivity  (ГОСТ Р ИСО 10303-41-1999, 2.3.4.12)
    */

    /*
     * Определения функций product_definition_schema (ГОСТ Р ИСО 10303-41-1999, 2.3.5)
     */


     /*
      * \brief FUNCTION acyclic jroduct_definition_formation_relationship (ГОСТ Р ИСО 10303-41-1999, 2.3.5.1)
      */

      /*
       * \brief FUNCTION acyclic_product_defmition_relationship (ГОСТ Р ИСО 10303-41-1999, 2.3.5.2)
       */

       /*
        * \brief FUNCTION acyclic_product_category_relationship (ГОСТ Р ИСО 10303-41-1999, 2.3.5.3)
        */

        /*
         * product_property_definition_schema (ГОСТ Р ИСО 10303-41-1999, 2.4)
         *
         * Введение (ГОСТ Р ИСО 10303-41-1999, 2.4.1)
         *
         * Фундаментальные понятия и допущения (ГОСТ Р ИСО 10303-41-1999, 2.4.2)
         *
         * Определения типов product_property_definition_schema
         */

         /**
          * \brief TYPE characterized_definition (ГОСТ Р ИСО 10303-41-1999, 2.4.3.1)
          *
          * <B>Определение объекта на языке EXPRESS:</B>
          * \verbatim
           -- DIFF IN AP214
           -- DIFF IN AP203e2
           -- DIFF IN AP224
           -- DIFF IN AP232
           TYPE characterized_definition = SELECT
             (characterized_item,                                         -- AP238 STEP-NC/AP242
              characterized_object,                                       -- Common
              characterized_product_definition,                           -- Common
              shape_definition);                                          -- Common
           END_TYPE; \endverbatim
          *
          * Тип <B>characterized_definition</B> является средством агрегатирования различных свойств,
          * принадлежащих <B>characterized_object</B>, <B>product_definition</B> или <B>shape_definition</B>.
          * Данный тип обеспечивает связывание свойств с указанными объектами.
          *
          * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_characterized_definition.html">Ссылка.</A>
          */
  class characterized_definition : public SELECT {

  public:

    STEP_TYPE_SELECT_CONSTRUCTOR_DEF(characterized_definition, characterized_item);
    STEP_TYPE_SELECT_CONSTRUCTOR_DEF(characterized_definition, characterized_object);
    STEP_TYPE_SELECT_CONSTRUCTOR_DEF(characterized_definition, characterized_product_definition);
    STEP_TYPE_SELECT_CONSTRUCTOR_DEF(characterized_definition, shape_definition);
  };

  /**
   * \brief TYPE characterized_product_definition (ГОСТ Р ИСО 10303-41-1999, 2.4.3.2)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
    -- DIFF IN AP214
    -- DIFF IN AP203e2
    -- DIFF IN AP238 STEP-NC
    -- DIFF IN AP224
    -- DIFF IN AP232
    TYPE characterized_product_definition = SELECT
      (product_definition,                                         -- Common
       product_definition_occurrence,                              -- AP238 STEP-NC/AP242
       product_definition_relationship,                            -- Common
       product_definition_relationship_relationship);              -- AP242
    END_TYPE;
   \endverbatim
   *
   * Тип <B>characterized_product_definition</B> является средством агрегатирования различных свойств,
   * принадлежащих конкретному <B>product_definition</B>. Данный тип обеспечивает связь свойств с такими объектами.<BR>
   * В выборе <B>product_definition_relationship</B> содержится особый смысл: свойство, относящееся к
   * <B>product_definition_relationship</B>, применяется к атрибуту <B>related_product_definition</B> в контексте
   * его атрибута <B>relating_product_definition</B>.
   * <SMALL>Примечание 1 — Такой подход позволяет представлять свойства изделия, которые изменяются,
   * когда изделие становится частью связи.<BR>
   * Примечание 2 — Тип <B>characterized_product_definition</B> ссылается на <B>product_definition</B> либо
   * непосредственно, либо в контексте другого <B>product_definition</B> через <B>product_definition_relationship</B>.</SMALL>
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_characterized_product_definition.html">Ссылка.</A>
   */
  class characterized_product_definition : public SELECT {

  public:

    STEP_TYPE_SELECT_CONSTRUCTOR_DEF(characterized_product_definition, product_definition);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(characterized_product_definition, product_definition_occurrence);
    STEP_TYPE_SELECT_CONSTRUCTOR_DEF(characterized_product_definition, product_definition_relationship);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(characterized_product_definition, product_definition_relationship_relationship);
  };

  /**
   * \brief TYPE shape_definition (ГОСТ Р ИСО 10303-41-1999, 2.4.3.3)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
    TYPE shape_definition = SELECT
          (product_definition_shape,
           shape_aspect,
           shape_aspect_relationship);
    END_TYPE;
   \endverbatim
   *
   * Тип <B>shape_definition</B> обеспечивает механизм, посредством которого можно ссылаться либо на
   * общую форму изделия, либо на ограниченный фрагмент формы изделия, либо на отношение между
   * фрагментами форм изделий.
   * <BR><SMALL>Примечание — В отличие от типа <B>characterized_product_definition</B> ссылки на <B>shape_aspect_relationship</B>
   * являются ссылками на само отношение, а не на один из связанных <B>shape_aspect</B></SMALL>.
   */
  class shape_definition : public SELECT {

  public:

    STEP_TYPE_SELECT_CONSTRUCTOR_DEF(shape_definition, product_definition_shape);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(shape_definition, shape_aspect);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(shape_definition, shape_aspect_relationship);
  };

  /*
   * Определения объектов product_property_definition_schema (ГОСТ Р ИСО 10303-41-1999, 2.4.4)
   */

   /**
    * \brief ENTITY characterized_object (ГОСТ Р ИСО 10303-41-1999, 2.4.4.1)
    *
    * <B>Определение объекта на языке EXPRESS:</B>
    * \verbatim
     ENTITY characterized_object;
       name : label;
       description : OPTIONAL text;
     END_ENTITY;
    \endverbatim
    *
    * Объект <B>characterized_object</B> является обозначением элемента, который содержит информацию о
    * связанном свойстве.
    * <BR><SMALL>Примечания<OL>
    * <LI>Объект <B>characterized_object</B> характеризуется свойствами, которые ему приписывают.</LI>
    * <LI>Свойствами <B>characterized_object</B> могут быть условия окружающей среды, при которых оценивали свойства изделия.</LI></OL></SMALL>
    *
    * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_characterized_object.html">Ссылка.</A>
    */
  class characterized_object : public STEP_ENTITY {

  private:
    /** \brief Слово или группа слов для ссылок на <B>characterized_object</B> */
    label* name;
    /** \brief Текст, связанный с характером <B>characterized_object</B> */
    text* description;

  public:

    /** \brief Конструктор */
    characterized_object(const std::string& Name, const std::string& Description);

    /** \brief Деструктор */
    virtual ~characterized_object();
  };

  /**
   * \brief ENTITY property_definition (ГОСТ Р ИСО 10303-41-1999, 2.4.4.2)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
    -- DIFF IN AP214
    -- DIFF IN AP203e2
    -- DIFF IN AP224
    -- DIFF IN AP232
    ENTITY property_definition
       SUPERTYPE OF (ONEOF(product_definition_kinematics, product_definition_relationship_kinematics, product_definition_shape));
          name : label;
          description : OPTIONAL text;
          definition : characterized_definition;
       DERIVE
          id : identifier := get_id_value(SELF);
       WHERE
          WR1:
             SIZEOF(USEDIN(SELF, 'STEP_MERGED_AP_SCHEMA.ID_ATTRIBUTE.IDENTIFIED_ITEM')) <= 1;
    END_ENTITY;
   \endverbatim
   *
   * Объект <B>property_defiitition</B> является свойством, характеризующим изделие. Его применяют к
   * изделию, к изделию в контексте другого изделия, к форме изделия, к элементу формы изделия или к
   * элементу формы в контексте другого элемента формы изделия.
   * <BR><SMALL>Примечание — <B>property_definition</B> не может существовать, не будучи связанным
   * с <B>product_definition</B> или с <B>shape_definition</B>. Данный атрибут устанавливает такую связь.</SMALL>
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_property_definition.html">Ссылка.</A>
   */
  class property_definition : public STEP_ENTITY {

  private:

    /** \brief Слово или группа слов для ссылок на <B>property_definition</B> */
    label* name;
    /** \brief текст, связанный с характером <B>property_definition</B> */
    text* description;
    /** \brief <B>property_definition</B>, <B>shape_aspect</B> или <B>shape_aspect_relationsbip</B>, свойства которых определяют */
    const characterized_definition* definition;

  public:

    /** \brief Конструктор */
    property_definition(const std::string& Name, const std::string& Description, const characterized_definition* Definition);

    /** \brief Деструктор */
    virtual ~property_definition();
  };

  /**
   * \brief product_definition_shape (ГОСТ Р ИСО 10303-41-1999, 2.4.4.3)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
    -- CASE DIFF IN AP214
    -- DIFF IN AP224
    -- DIFF IN AP232
    ENTITY product_definition_shape
       SUBTYPE OF (property_definition);
       UNIQUE
          UR1 : SELF\property_definition.definition;
       WHERE
          WR1:
             SIZEOF([ 'STEP_MERGED_AP_SCHEMA.CHARACTERIZED_PRODUCT_DEFINITION', 'STEP_MERGED_AP_SCHEMA.CHARACTERIZED_OBJECT' ] * TYPEOF(SELF\property_definition.definition)) > 0;
    END_ENTITY;
   \endverbatim
   *
   * Объект <B>product_definition_shape</B> является типом <B>property_definition</B>. Он является формой изделия.
   * Данная форма может быть схематической формой, для которой не требуется конкретное геометрическое представление.
   * <BR><SMALL>Примечание — На ранних стадиях проектирования изделия может отсутствовать конкретное
   * представление о форме изделия, но могут быть определены некоторые характеристики, которыми
   * должна обладать форма. Такие характеристики формы изделия могут быть приписаны форме изделия с
   * помощью данного объекта.</SMALL>
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_product_definition_shape.html">Ссылка.</A>
   */
  class product_definition_shape : public property_definition {

  public:

    /** \brief Конструктор */
    product_definition_shape(const std::string& Name, const std::string& Description, const characterized_definition* Definition);

    virtual ~product_definition_shape();
  };

  // 2.4.4.4 shape_aspect

  // 2.4.4.5 shape_aspect_relationship

  // **************************************************************************
  // product_property_representation_schema (ГОСТ Р ИСО 10303-41-1999, 2.5)
  // **************************************************************************

  // ...

  /**
   * \brief ENTITY shape_representation (ГОСТ Р ИСО 10303-41, 2.5.3.1)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
    ENTITY shape_representation
       SUBTYPE OF (representation);
    END_ENTITY;
   \endverbatim
   *
   * Представление информации о форме
   */
  class shape_representation : public representation {

  public:

    /**  \brief Конструктор */
    shape_representation(const std::string& Name, const representation_context* Context_of_items);

    /**  \brief Деструктор */
    virtual ~shape_representation();

    // FUNCTION get_id_value
    identifier get_id_value(void);

    // FUNCTION get_description_value
    text get_description_value(void);
  };

  /**
   * \brief ENTITY property_definition_representation (ГОСТ Р ИСО 10303-41-1999, 2.5.3.2)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
    ENTITY property_definition_representation;
          definition : represented_definition;
          used_representation : representation;
       DERIVE
          description : text := get_description_value(SELF);
          name : label := get_name_value(SELF);
       WHERE
          WR1:
             SIZEOF(USEDIN(SELF, 'STEP_MERGED_AP_SCHEMA.DESCRIPTION_ATTRIBUTE.DESCRIBED_ITEM')) <= 1;
          wr2:
             SIZEOF(USEDIN(SELF, 'STEP_MERGED_AP_SCHEMA.NAME_ATTRIBUTE.NAMED_ITEM')) <= 1;
    END_ENTITY;
   \endverbatim
   *
   */
  class property_definition_representation : public STEP_ENTITY {

  private:

    const represented_definition* definition;
    const representation* used_representation;

  public:

    property_definition_representation(const represented_definition* Definition, const representation* Used_representation);

    virtual ~property_definition_representation();

    // FUNCTION get_description_value
    // const text *get_description_value(void) { return ???};
    // FUNCTION get_name_value
    // const label *get_name_value(void) { return ???};
  };

  /**
   * \brief ENTITY shape_representation_relationship (ГОСТ Р ИСО 10303-41-1999, 2.5.3.3)
   *
   * <B>2.5.3.3 \ref shape_representation_relationship</B>
   * Объект <B>\ref shape_representation_relationship</B> является отношением между двумя
   * представлениями, в котором хотя бы одно представление является <B>\ref shape_representation</B>.
   * <BR><SMALL>Пример 43 - Представление формы болта может быть связано с представлением позиции,
   * если болт является частью сборочного узла.</SMALL>
   *
   * <U>EXPRESS-спецификация:</U>
   * \verbatim
    -- IN AP224/AP238 STEP-NC/AP242
    *)
    ENTITY shape_representation_relationship
      SUBTYPE OF (representation_relationship);
    WHERE
      WR1: SIZEOF(['PRODUCT_PROPERTY_REPRESENTATION_SCHEMA.SHAPE_REPRESENTATION', 'PRODUCT_PROPERTY_REPRESENTATION_SCHEMA.SHAPE_REPRESENTATION_REFERENCE'] * (TYPEOF(SELF\representation_relationship.rep_1) + TYPEOF(SELF\representation_relationship.rep_2))) >= 1;
    END_ENTITY;
    (* 
   \endverbatim
   *
   * <U>Формальные утверждения:</U><BR>
   * <B>WR1</B>: - одно из двух представлений в <B>\ref shape_representation_relationship</B> должно быть
   * <B>\ref shape_representation</B>
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_shape_representation_relationship.html">Ссылка.</A>
   */
  class shape_representation_relationship : public representation_relationship {

  public:

    shape_representation_relationship(const std::string& Name, const std::string& Description, const representation* Rep1, const representation* Rep2);

    virtual ~shape_representation_relationship();
  };

  /**
   * \brief ENTITY context_dependent_shape_representation (ГОСТ Р ИСО 10303-41-1999, 2.5.3.4)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
    -- IN AP203e2/AP214/AP232/AP238 STEP-NC/AP242
    ENTITY context_dependent_shape_representation;
          representation_relation : shape_representation_relationship;
          represented_product_relation : product_definition_shape;
       DERIVE
          description : text := get_description_value(SELF);
          name : label := get_name_value(SELF);
       WHERE
          WR1:
             'STEP_MERGED_AP_SCHEMA.PRODUCT_DEFINITION_RELATIONSHIP' IN TYPEOF(SELF.represented_product_relation.definition);
          wr2:
             SIZEOF(USEDIN(SELF, 'STEP_MERGED_AP_SCHEMA.DESCRIPTION_ATTRIBUTE.DESCRIBED_ITEM')) <= 1;
          wr3:
             SIZEOF(USEDIN(SELF, 'STEP_MERGED_AP_SCHEMA.NAME_ATTRIBUTE.NAMED_ITEM')) <= 1;
    END_ENTITY;
   \endverbatim
   *
   * Связывает объект <B>shape_representation_relationship</B> с объектом <B>product_definition_shape</B>, то есть явно обозначает
   * форму сборки.
   */
  class context_dependent_shape_representation : public STEP_ENTITY {

  private:

    const shape_representation_relationship* representation_relation;       // Ссылка для определения сборки
    const product_definition_shape* represented_product_relation;  // Ссылка на объект, связанный с объектом assembly_usage_occurrence.

  public:

    context_dependent_shape_representation(const shape_representation_relationship* RepRelation,
      const product_definition_shape* ProdRelation);

    virtual ~context_dependent_shape_representation();
  };

  /**
   * \brief ENTITY shape_definition_representation (ГОСТ Р ИСО 10303-41, 2.5.3.5)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
    -- DIFF IN AP214
    -- DIFF IN AP203e2
    -- DIFF IN AP224
    -- DIFF IN AP232
    ENTITY shape_definition_representation
       SUBTYPE OF (property_definition_representation);
          SELF\property_definition_representation.definition : property_definition;
          SELF\property_definition_representation.used_representation : shape_representation;
       WHERE
          WR1:
             ('STEP_MERGED_AP_SCHEMA.PRODUCT_DEFINITION_SHAPE' IN TYPEOF(definition)) OR ('STEP_MERGED_AP_SCHEMA.SHAPE_DEFINITION' IN TYPEOF(definition\property_definition.definition));
    END_ENTITY;
   \endverbatim
   *
   * Представление информации о форме
   */
  class shape_definition_representation : public property_definition_representation {

  public:

    // !!!
    shape_definition_representation(const represented_definition* Definition, const representation* Used_representation)
      : property_definition_representation(Definition, Used_representation) {
    }
  };


  // **************************************************************************
  // Ресурсы управления (ГОСТ Р ИСО 10303-41-1999, 3)
  // **************************************************************************

  // **************************************************************************
  // management_resources_schema (ГОСТ Р ИСО 10303-41-1999, 3.2)
  // **************************************************************************

  // **************************************************************************
  // Ресурсы поддержки (ГОСТ Р ИСО 10303-41-1999, 4)
  // **************************************************************************

  // Введение (ГОСТ Р ИСО 10303-41-1999, 4.1)

  // **************************************************************************
  // document_schema (ГОСТ Р ИСО 10303-41-1999, 4.2)
  // **************************************************************************

  // **************************************************************************
  // action_schema (ГОСТ Р ИСО 10303-41-1999, 4.2)
  // **************************************************************************

  // ...

  // action_schema (ГОСТ Р ИСО 10303-41-1999, 4.3)

  // ...

  // **************************************************************************
  // certification_schema (ГОСТ Р ИСО 10303-41-1999, 4.4)
  // **************************************************************************



  // **************************************************************************
  // approval_schema (ГОСТ Р ИСО 10303-41-1999, 4.5)
  // **************************************************************************

  // **************************************************************************
  // contract_schema (ГОСТ Р ИСО 10303-41-1999, 4.6)
  // **************************************************************************

  // **************************************************************************
  // security_classification_schema (ГОСТ Р ИСО 10303-41-1999, 4.7)
  // **************************************************************************

  // **************************************************************************
  // person_organization_schema (ГОСТ Р ИСО 10303-41-1999, 4.8)
  // **************************************************************************

  // **************************************************************************
  // date_time_schema (ГОСТ Р ИСО 10303-41-1999, 4.9)
  // **************************************************************************

  // **************************************************************************
  // group_schema (ГОСТ Р ИСО 10303-41-1999, 4.10)
  // **************************************************************************

  // **************************************************************************
  // effectivity_schema (ГОСТ Р ИСО 10303-41-1999, 4.11)
  // **************************************************************************

  // **************************************************************************
  // external_reference_schema (ГОСТ Р ИСО 10303-41-1999, 4.12)
  // **************************************************************************

  /**
   * \brief ENTITY pre_defined_item (ГОСТ Р ИСО 10303-41-1999, 4.12.4.3)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
    ENTITY pre_defined_item;
          name : label;
    END_ENTITY;
   \endverbatim
   *
   */
  class pre_defined_item : public STEP_ENTITY {

  private:

    label* name;

  public:

    pre_defined_item(const std::string& Name);

    virtual ~pre_defined_item();
  };


  // **************************************************************************
  // support_resource_schema (ГОСТ Р ИСО 10303-41-1999, 4.13)
  // **************************************************************************

  /**
   * <B>4.14 measure_schema</B>
   *
   */

   // ...

   /**
    * \brief TYPE measure_value (ГОСТ Р ИСО 10303-41-1999, 4.14.3.1)
    *
    * <B>Определение объекта на языке EXPRESS:</B>
    * \verbatim
     TYPE measure_value = SELECT
       (absorbed_dose_measure,                                      -- AP203e2/AP238 STEP-NC/AP242
        acceleration_measure,                                       -- AP203e2/AP238 STEP-NC/AP242
        amount_of_substance_measure,                                -- AP203e2/AP214/AP232/AP238 STEP-NC/AP242
        area_measure,                                               -- AP203e2/AP214/AP232/AP238 STEP-NC/AP242
        capacitance_measure,                                        -- AP203e2/AP238 STEP-NC/AP242
        celsius_temperature_measure,                                -- AP203e2/AP214/AP232/AP238 STEP-NC/AP242
        conductance_measure,                                        -- AP203e2/AP238 STEP-NC/AP242
        context_dependent_measure,                                  -- Common
        count_measure,                                              -- Common
        descriptive_measure,                                        -- Common
        dose_equivalent_measure,                                    -- AP203e2/AP238 STEP-NC/AP242
        electric_charge_measure,                                    -- AP203e2/AP238 STEP-NC/AP242
        electric_current_measure,                                   -- AP203e2/AP214/AP232/AP238 STEP-NC/AP242
        electric_potential_measure,                                 -- AP203e2/AP238 STEP-NC/AP242
        energy_measure,                                             -- AP203e2/AP238 STEP-NC/AP242
        force_measure,                                              -- AP203e2/AP238 STEP-NC/AP242
        frequency_measure,                                          -- AP203e2/AP238 STEP-NC/AP242
        illuminance_measure,                                        -- AP203e2/AP238 STEP-NC/AP242
        inductance_measure,                                         -- AP203e2/AP238 STEP-NC/AP242
        length_measure,                                             -- Common
        luminous_flux_measure,                                      -- AP203e2/AP238 STEP-NC/AP242
        luminous_intensity_measure,                                 -- AP203e2/AP214/AP232/AP238 STEP-NC/AP242
        magnetic_flux_density_measure,                              -- AP203e2/AP238 STEP-NC/AP242
        magnetic_flux_measure,                                      -- AP203e2/AP238 STEP-NC/AP242
        mass_measure,                                               -- AP203e2/AP214/AP232/AP238 STEP-NC/AP242
        non_negative_length_measure,                                -- AP203e2/AP214/AP238 STEP-NC/AP242
        numeric_measure,                                            -- AP203e2/AP214/AP232/AP238 STEP-NC/AP242
        parameter_value,                                            -- Common
        plane_angle_measure,                                        -- Common
        positive_length_measure,                                    -- Common
        positive_plane_angle_measure,                               -- Common
        positive_ratio_measure,                                     -- AP203e2/AP214/AP232/AP238 STEP-NC/AP242
        power_measure,                                              -- AP203e2/AP238 STEP-NC/AP242
        pressure_measure,                                           -- AP203e2/AP238 STEP-NC/AP242
        radioactivity_measure,                                      -- AP203e2/AP238 STEP-NC/AP242
        ratio_measure,                                              -- Common
        resistance_measure,                                         -- AP203e2/AP238 STEP-NC/AP242
        solid_angle_measure,                                        -- AP203e2/AP214/AP232/AP238 STEP-NC/AP242
        thermodynamic_temperature_measure,                          -- AP203e2/AP214/AP232/AP238 STEP-NC/AP242
        time_measure,                                               -- AP203e2/AP214/AP232/AP238 STEP-NC/AP242
        velocity_measure,                                           -- AP203e2/AP238 STEP-NC/AP242
        volume_measure);                                            -- AP203e2/AP214/AP232/AP238 STEP-NC/AP242
     END_TYPE;
    \endverbatim
    */
  class measure_value : public SELECT {

  public:

    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, absorbed_dose_measure);
    // STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, acceleration_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, amount_of_substance_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, area_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, capacitance_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, celsius_temperature_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, conductance_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, context_dependent_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, count_measure);
    STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, descriptive_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, dose_equivalent_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, electric_charge_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, electric_current_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, electric_potential_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, energy_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, force_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, frequency_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, illuminance_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, inductance_measure);
    STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, length_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, luminous_flux_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, luminous_intensity_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, magnetic_flux_density_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, magnetic_flux_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, mass_measure);
    STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, non_negative_length_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, numeric_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, parameter_value);
    STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, plane_angle_measure);
    STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, positive_length_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, positive_plane_angle_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, positive_ratio_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, power_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, pressure_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, radioactivity_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, ratio_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, resistance_measure);
    STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, solid_angle_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, thermodynamic_temperature_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, time_measure);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(measure_value, volume_measure);
  };


  /**
   * \brief TYPE descriptive_measure (ГОСТ Р ИСО 10303-41-99, 4.14.3.20)
   *
   * <B>4.14.3.20 descriptive_measure</B><BR>
   * Тип <B>\ref descriptive_measure</B> является представляемым человеком
   * определением количественного значения.
   *
   * <U>EXPRESS-специФикания:</U>
   * \verbatim
    *)
    TYPE descriptive_measure = STRING;
    END_TYPE;
    (*
   \endverbatim
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_descriptive_measure.html">Ссылка.</A>
   */
  class descriptive_measure : public STRING {

  public:

    descriptive_measure() : STRING() {
    }
    descriptive_measure(const std::string &v) : STRING(v) {
    }
    descriptive_measure(const char* v) : STRING(v) {
    }

    virtual STEP_OBJTYPE objtype() const {
      return STEP_OBJTYPE::TYPE_DEFINED;
    }
  };


  /**
   * \brief TYPE count_measure (ГОСТ Р ИСО 10303-41-1999, 4.14.3.21)
   *
   * <B>4.14.3.21 count_measure</B><BR>
   * Тип <B>\ref count_measure</B> является значением количества.
   *
   * <U>EXPRESS-спецификация:</U>
   * \verbatim
    *)
    TYPE count_measure = NUMBER;
    ENDJTYPE;
    (*
   \endverbatim
   *
   */
  class count_measure : public NUMBER {

  public:

    count_measure() : NUMBER() {
    }

    virtual STEP_OBJTYPE objtype() const {
      return STEP_OBJTYPE::TYPE_DEFINED;
    }
  };


  /**
   * \brief TYPE unit (ГОСТ Р ИСО 10303-41-1999, 4.14.3.22)
   *
   * <B>4.14.3.22 unit</B><BR>
   * Тип  <B>\ref unit</B>  является  единицей  физической величины со стандартным единичным
   * значением, по отношению к которому выражаются другие величины.
   *
   * <U>EXPRESS-спецификация:</U>
   * \verbatim
    -- DIFF IN AP224
    -- DIFF IN AP232
    TYPE unit = SELECT
          (derived_unit,
           named_unit);
    END_TYPE;
   \endverbatim
   *
   */
  class unit : public SELECT {

  public:

    STEP_TYPE_SELECT_CONSTRUCTOR_DEF(unit, derived_unit);
    STEP_TYPE_SELECT_CONSTRUCTOR_DEF(unit, named_unit);
  };


  /**
   * \brief TYPE si_unit_name (ГОСТ Р ИСО 10303-41-1999, 4.14.3.23)
   *
   * <B>4.14.3.23 \ref si_unit_name</B>
   * Тип <B>\ref si_unit_name</B> является наименованием единицы системы СИ. Определения наименований
   * единиц в системе СИ установлены в разделе 2 ИСО 1000.
   *
   * <U>EXPRESS-спецификация:</U>
   * \verbatim
    TYPE si_unit_name = ENUMERATION OF
        (metre,
         gram,
         second,
         ampere,
         kelvin,
         mole,
         candela,
         radian,
         steradian,
         hertz,
         newton,
         pascal,
         joule,
         watt,
         coulomb,
         volt,
         farad,
         ohm,
         siemens,
         weber,
         tesla,
         henry,
         degree_celsius,
         lumen,
         lux,
         becquerel,
         gray,
         sievert);
  END_TYPE;
   \endverbatim
   *
   * <A http://www.steptools.com/stds/stp_aim/html/t_si_unit_nname.html">Ссылка.</A>
   */
  class si_unit_name : public ENUMERATION {
  public:
    enum
#if !defined(__DOXYGEN__)
      class
#endif 
      val {
      none = 0,
        metre,
        gram,
        second,
        ampere,
        kelvin,
        mole,
        candela,
        radian,
        steradian,
        hertz,
        newton,
        ppascal,
        joule,
        watt,
        coulomb,
        volt,
        farad,
        ohm,
        siemens,
        weber,
        tesla,
        henry,
        degree_celsius,
        lumen,
        lux,
        becquerel,
        gray,
        sievert
    };

  private:

    val x_;

  public:

    // Конструктор
    si_unit_name(val v) : x_(v) {
    }

    // Получение значения
    val getval() const {
      return x_;
    }

    // Вывод значения типа
    std::string print_value() const {
      std::stringstream s;
      switch (x_) {
      case val::none:            s << "$"; break;
      case val::metre:           s << ".METRE."; break;
      case val::gram:            s << ".GRAM."; break;
      case val::second:          s << ".SECOND."; break;
      case val::ampere:          s << ".AMPERE."; break;
      case val::kelvin:          s << ".KELVIN."; break;
      case val::mole:            s << ".MOLE."; break;
      case val::candela:         s << ".CANDELA."; break;
      case val::radian:          s << ".RADIAN."; break;
      case val::steradian:       s << ".STERADIAN."; break;
      case val::hertz:           s << ".HERTZ."; break;
      case val::newton:          s << ".NEWTON."; break;
      case val::ppascal:         s << ".PASCAL."; break;
      case val::joule:           s << ".JOULE."; break;
      case val::watt:            s << ".WATT."; break;
      case val::coulomb:         s << ".COULOMB."; break;
      case val::volt:            s << ".VOLT."; break;
      case val::farad:           s << ".FARAD."; break;
      case val::ohm:             s << ".OHM."; break;
      case val::siemens:         s << ".SIEMENS."; break;
      case val::weber:           s << ".WEBER."; break;
      case val::tesla:           s << ".TESLA."; break;
      case val::henry:           s << ".HENRY."; break;
      case val::degree_celsius:  s << ".DEGREE_CELSIUS."; break;
      case val::lumen:           s << ".LUMEN."; break;
      case val::lux:             s << ".LUX."; break;
      case val::becquerel:       s << ".BECQUEREL."; break;
      case val::gray:            s << ".GRAY."; break;
      case val::sievert:         s << ".SIEVERT."; break;
      }
      return s.str();
    }
  };

  /**
   * \brief TYPE si_prefix (ГОСТ Р ИСО 10303-41-1999, 4.14.3.24)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   *\verbatim
    -- DIFF IN AP224
    TYPE si_prefix = ENUMERATION OF
          (exa,
           peta,
           tera,
           giga,
           mega,
           kilo,
           hecto,
           deca,
           deci,
           centi,
           milli,
           micro,
           nano,
           pico,
           femto,
           atto);
    END_TYPE;
   \endverbatim
   *
   * <A http://www.steptools.com/stds/stp_aim/html/t_si_prefix.html">Ссылка.</A>
   */
  class si_prefix : public ENUMERATION {

  public:

    enum
#if !defined(__DOXYGEN__)
      class
#endif 
      val {
      none = 0,
        exa,
        peta,
        tera,
        giga,
        mega,
        kilo,
        hecto,
        deca,
        deci,
        centi,
        milli,
        micro,
        nano,
        pico,
        femto,
        atto
    };

  private:

    val x_;

  public:

    /* \brief Конструктор */
    si_prefix(val v) : x_(v) {
    }

    // Получение значения
    val getval() const {
      return x_;
    }

    // Вывод значения типа
    std::string print_value() const {
      std::stringstream s;
      switch (x_) {
      case val::none:   s << "$"; break;
      case val::exa:    s << ".EXA."; break;
      case val::peta:   s << ".PETA."; break;
      case val::tera:   s << ".TERA."; break;
      case val::giga:   s << ".GIGA."; break;
      case val::mega:   s << ".MEGA."; break;
      case val::kilo:   s << ".KILO."; break;
      case val::hecto:  s << ".HECTO."; break;
      case val::deca:   s << ".DECA."; break;
      case val::deci:   s << ".DECI."; break;
      case val::centi:  s << ".CENTI."; break;
      case val::milli:  s << ".MILLI."; break;
      case val::micro:  s << ".MICRO."; break;
      case val::nano:   s << ".NANO."; break;
      case val::pico:   s << ".PICO."; break;
      case val::femto:  s << ".FEMTO."; break;
      case val::atto:   s << ".ATTO."; break;
      }
      return s.str();
    }
  };


  /**
   * \brief ENTITY named_unit (ГОСТ Р ИСО 10303-41-1999, 4.14.4.1)
   *
   * <B>4.14.4.1 named_unit</B><BR>
   * Объект <B>\ref named_unit</B> является единицей физической величины, связанной со словом или группой
   * слов, которыми данная единица определяется.
   *
   * <U>EXPRESS-спецификация:</U>
   * \verbatim
    -- DIFF IN AP214
    -- DIFF IN AP224
    -- DIFF IN AP232
    ENTITY named_unit
       SUPERTYPE OF (ONEOF(si_unit, conversion_based_unit, context_dependent_unit) ANDOR ONEOF(length_unit, mass_unit, time_unit, electric_current_unit, thermodynamic_temperature_unit, amount_of_substance_unit, luminous_flux_unit, luminous_intensity_unit, plane_angle_unit, solid_angle_unit, ratio_unit));
          dimensions : dimensional_exponents;
    END_ENTITY;
   \endverbatim
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_named_unit.html">Ссылка.</A>
   */
  class named_unit : public STEP_ENTITY {

  private:
    /** \brief Показатели основных свойств, которыми определяется <B>named_unit</B>. */
    const dimensional_exponents* dimensions;

  public:

    /** \brief Конструктор */
    named_unit(const dimensional_exponents& Dimensions);

    /** \brief Деструктор */
    virtual ~named_unit();

    // Получить размерность
    const dimensional_exponents* get_dimensions() const {
      return dimensions;
    }
  };


  /**
   * \brief ENTITY si_unit (ГОСТ Р ИСО 10303-41-1999, 4.14.4.2)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
    ENTITY si_unit
       SUBTYPE OF (named_unit);
          prefix : OPTIONAL si_prefix;
          name : si_unit_name;
       DERIVE
          SELF\named_unit.dimensions : dimensional_exponents := dimensions_for_si_unit(name);
       WHERE
          WR1:
             NOT (('STEP_MERGED_AP_SCHEMA.MASS_UNIT' IN TYPEOF(SELF)) AND (SIZEOF(USEDIN(SELF, 'STEP_MERGED_AP_SCHEMA.DERIVED_UNIT_ELEMENT.UNIT')) > 0)) OR (prefix = si_prefix.kilo);
    END_ENTITY;
   \endverbatim
   *
   * Физическая величина, измеряемая согласно Международной системы единиц (СИ)
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_si_unit.html">Ссылка.</A>
   */
  class si_unit : public named_unit {

  private:

    si_prefix* prefix;     // приставка(множитель) Международной системы единиц (СИ)
    si_unit_name* name;       // единица Международной системы единиц (СИ)

  public:

    /**  \brief Конструктор */
    si_unit(const si_unit_name& Name, const si_prefix& Prefix = si_prefix(si_prefix::val::none));

    /**  \brief Деструктор */
    virtual ~si_unit();
  };

  /**
   * \brief ENTITY conversion_based_unit (ГОСТ Р ИСО 10303-41-1999, 4.14.4.3)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
    -- DIFF IN AP214
    ENTITY conversion_based_unit
       SUBTYPE OF (named_unit);
          name : label;
          conversion_factor : measure_with_unit;
       WHERE
          WR1:
             SELF\named_unit.dimensions = derive_dimensional_exponents(conversion_factor\measure_with_unit.unit_component);
    END_ENTITY;
   \endverbatim
   *
   */
  class conversion_based_unit : public named_unit {
  private:

    label* name;
    measure_with_unit* conversion_factor;

  public:

    conversion_based_unit(const label& Name, measure_with_unit* Conversion_factor);

    virtual ~conversion_based_unit();

  };

  /**
   * \brief ENTITY context_dependent_unit (ГОСТ Р ИСО 10303-41-1999, 4.14.4.4)
   *
   * <B>4.14.4.4 \ref context_dependent_unit</B><BR>
   * Объект <B>\ref context_dependent_unit</B> является единицей, не связанной с системой СИ.
   * <BR><SMALL>Пример 83 - Число деталей в сборочной единице является физической величиной, измеряемой в
   * единицах, которые могут быть названы «штуки», но которые не связаны с единицей СИ.</SMALL>
   * 
   * <U>EXPRESS-спецификаиия</U>
   * \verbatim
    ENTITY context_dependent_unit
       SUBTYPE OF (named_unit);
          name : label;
    END_ENTITY;
   \endverbatim
   * <U>Определения атрибутов:</U><BR>
   * <B>\ref name</B> - слово или группа слов для ссылок на <B>\ref context_dependent_unit</B>.
   * 
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_context_dependent_unit.html">Ссылка.</A>
   */
  class context_dependent_unit : public named_unit {

  private:

    /** \brief Слово или группа слов для ссылок на <B>\ref context_dependent_unit</B> */
    label* name;

  public:

    /** \brief Конструктор */
    context_dependent_unit(const label& Name, const dimensional_exponents* Dimensions = nullptr);

    /** \brief Деструктор */
    virtual ~context_dependent_unit();
  };

  /**
   * \brief ENTITY length_unit (ГОСТ Р ИСО 10303-41-1999, 4.14.4.5)
   *
   * <B>4.14.4.5 \ref length_unit</B><BR>
   * Объект <B>\ref length_unit</B> является единицей, в которой измеряют расстояния.
   *  
   * <U>EXPRESS-специФикаиия:</U>
   * \verbatim
    *)
    ENTITY length_unit
      SUBTYPE OF (named_unit);
    WHERE
      WR1: (SELF\named_unit.dimensions.length_exponent = 1.0) AND
           (SELF\named_unit.dimensions.mass_exponent = 0.0) AND
           (SELF\named_unit.dimensions.time_exponent = 0.0) AND
           (SELF\named_unit.dimensions.electric_current_exponent = 0.0) AND
           (SELF\named_unit.dimensions.thermodynamic_temperature_exponent = 0.0) AND
           (SELF\named_unit.dimensions.amount_of_substance_exponent = 0.0) AND
           (SELF\named_unit.dimensions.luminous_intensity_exponent = 0.0);
    END_ENTITY;
    (* 
   \endverbatim
   * <U>Формальные утверждения:</U><BR>
   * <B>WR1:</B> - показатель размерности длины должен быть равен единице, а остальные показатели
   * размерности должны быть равны нулю.
   */
  class length_unit : public named_unit {
  public:

    /** \brief Конструктор */
    length_unit();

    /** \brief Деструктор */
    virtual ~length_unit();
  };

  /**
   * \brief ENTITY mass_unit (ГОСТ Р ИСО 10303-41-1999, 4.14.4.6)
   *
   * <B>4.14.4.6 \ref mass_unit</B>
   * Объект <B>\ref mass_unit</B> является единицей, в которой измеряют количество
   * вещества, содержащегося в теле.
   *
   * <U>EXPRESS-спецификаиия:</U>
   * \verbatim
    *)
    ENTITY mass_unit
      SUBTYPE OF (named_unit);
    WHERE
      WR1: (SELF\named_unit.dimensions.length_exponent = 0.0) AND
           (SELF\named_unit.dimensions.mass_exponent = 1.0) AND
           (SELF\named_unit.dimensions.time_exponent = 0.0) AND
           (SELF\named_unit.dimensions.electric_current_exponent = 0.0) AND
           (SELF\named_unit.dimensions.thermodynamic_temperature_exponent = 0.0) AND
           (SELF\named_unit.dimensions.amount_of_substance_exponent = 0.0) AND
           (SELF\named_unit.dimensions.luminous_intensity_exponent = 0.0);
    END_ENTITY;
    (*
   \endverbatim
   * <U>Формальные утверждения:</U><BR>
   * <B>WR1:</B> - показатель размерности массы должен быть равен единице, а остальные показатели
   * размерности должны быть равны нулю.
   */
  class mass_unit : public named_unit {

    /** \brief Конструктор */
    mass_unit();

    /** \brief Деструктор */
    virtual ~mass_unit();
  };

  /**
   * \brief ENTITY time_unit (ГОСТ Р ИСО 10303-41-1999, 4.14.4.7)
   *
   * <B>4.14.4.7 \ref time_unit</B>
   * Объект <B>\ref time_unit</B> является единицей, в которой измеряют длительности промежутков времени.
   *
   * <U>EXPRESS-спецификаиия:</U>
   * \verbatim
    -- IN AP203e2/AP214/AP232/AP238 STEP-NC/AP242
    *)
    ENTITY time_unit
      SUBTYPE OF (named_unit);
    WHERE
      WR1: (SELF\named_unit.dimensions.length_exponent = 0.0) AND
           (SELF\named_unit.dimensions.mass_exponent = 0.0) AND
           (SELF\named_unit.dimensions.time_exponent = 1.0) AND
           (SELF\named_unit.dimensions.electric_current_exponent = 0.0) AND
           (SELF\named_unit.dimensions.thermodynamic_temperature_exponent = 0.0) AND
           (SELF\named_unit.dimensions.amount_of_substance_exponent = 0.0) AND
           (SELF\named_unit.dimensions.luminous_intensity_exponent = 0.0);
    END_ENTITY;
    (*
    \endverbatim
   *
   */
  class time_unit : public named_unit {

    time_unit();

    virtual ~time_unit();
  };

  /* ENTITY electric_current_unit (4.14.4.8) */

  /* ENTITY thermodynamic_temperature_unit (4.14.4.9) */

  /* ENTITY amount_of_substance_unit (4.14.4.10) */

  /* ENTITY luminous_intensity_unit (4.14.4.11) */

  /**
   * \brief ENTITY plane_angle_unit (ГОСТ Р ИСО 10303-41-1999, 4.14.4.12)
   *
   * <U>EXPRESS-спецификаиия:</U>
   * \verbatim
    ENTITY plane_angle_unit
       SUBTYPE OF (named_unit);
       WHERE
          WR1:
             ((((((SELF\named_unit.dimensions.length_exponent = 0.0) AND
                  (SELF\named_unit.dimensions.mass_exponent = 0.0)) AND
                  (SELF\named_unit.dimensions.time_exponent = 0.0)) AND
                  (SELF\named_unit.dimensions.electric_current_exponent = 0.0)) AND
                  (SELF\named_unit.dimensions.thermodynamic_temperature_exponent = 0.0)) AND
                  (SELF\named_unit.dimensions.amount_of_substance_exponent = 0.0)) AND
                  (SELF\named_unit.dimensions.luminous_intensity_exponent = 0.0);
    END_ENTITY;
   \endverbatim
   *
   */
  class plane_angle_unit : public named_unit {
  public:

    /** \brief Конструктор */
    plane_angle_unit();

    /** \brief Деструктор */
    virtual ~plane_angle_unit();
  };

  /**
   * \brief ENTITY solid_angle_unit (ГОСТ Р ИСО 10303-41-1999, 4.14.4.13)
   *
   * <U>EXPRESS-спецификаиия:</U>
   * \verbatim
    ENTITY solid_angle_unit
       SUBTYPE OF (named_unit);
       WHERE
          WR1:
             ((((((SELF\named_unit.dimensions.length_exponent = 0.0) AND
                  (SELF\named_unit.dimensions.mass_exponent = 0.0)) AND
                  (SELF\named_unit.dimensions.time_exponent = 0.0)) AND
                  (SELF\named_unit.dimensions.electric_current_exponent = 0.0)) AND
                  (SELF\named_unit.dimensions.thermodynamic_temperature_exponent = 0.0)) AND
                  (SELF\named_unit.dimensions.amount_of_substance_exponent = 0.0)) AND
                  (SELF\named_unit.dimensions.luminous_intensity_exponent = 0.0);
    END_ENTITY;
   \endverbatim
   *
   */
  class solid_angle_unit : public named_unit {
  public:

    // Конструктор
    solid_angle_unit();

    /** \brief Деструктор */
    virtual ~solid_angle_unit();
  };

  /* ENTITY area_unit (4.14.4.14) */

  /* ENTITY volume_unit (4.14.4.15) */

  /**
   * \brief ENTITY ratio_unit (ГОСТ Р ИСО 10303-41-1999, 4.14.4.16)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
    ENTITY ratio_unit
       SUBTYPE OF (named_unit);
       WHERE
          WR1:
             ((((((SELF\named_unit.dimensions.length_exponent = 0.0) AND
                  (SELF\named_unit.dimensions.mass_exponent = 0.0)) AND
                  (SELF\named_unit.dimensions.time_exponent = 0.0)) AND
                  (SELF\named_unit.dimensions.electric_current_exponent = 0.0)) AND
                  (SELF\named_unit.dimensions.thermodynamic_temperature_exponent = 0.0)) AND
                  (SELF\named_unit.dimensions.amount_of_substance_exponent = 0.0)) AND
                  (SELF\named_unit.dimensions.luminous_intensity_exponent = 0.0);
    END_ENTITY;
   \endverbatim
   *
   */
  class ratio_unit : public named_unit {

  public:

    ratio_unit();

    virtual ~ratio_unit();
  };

  /**
   * \brief ENTITY dimensional_exponents (ГОСТ Р ИСО 10303-41-1999, 4.14.4.17)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
    ENTITY dimensional_exponents;
          length_exponent : REAL;
          mass_exponent : REAL;
          time_exponent : REAL;
          electric_current_exponent : REAL;
          thermodynamic_temperature_exponent : REAL;
          amount_of_substance_exponent : REAL;
          luminous_intensity_exponent : REAL;
    END_ENTITY;
   \endverbatim
   *
   * Множители единиц Си, определяющие размерность величины
   */
  class dimensional_exponents : public STEP_ENTITY {

  private:

    REAL length_exponent;
    REAL mass_exponent;
    REAL time_exponent;
    REAL electric_current_exponent;
    REAL thermodynamic_temperature_exponent;
    REAL amount_of_substance_exponent;
    REAL luminous_intensity_exponent;

  public:

    /** \brief Конструктор */
    dimensional_exponents(double Length = 0.0, double Mass = 0.0, double Time = 0.0, double Current = 0.0, double Temp = 0.0, double Amount = 0.0, double Lum = 0.0);

    /** \brief Деструктор */
    virtual ~dimensional_exponents();

    REAL get_length_exponent() const;
    REAL get_mass_exponent() const;
    REAL get_time_exponent() const;
    REAL get_electric_current_exponent() const;
    REAL get_thermodynamic_temperature_exponent() const;
    REAL get_amount_of_substance_exponent() const;
    REAL get_luminous_intensity_exponent() const;

    void set_length_exponent(const REAL& x);
    void set_mass_exponent(const REAL& x);
    void set_time_exponent(const REAL& x);
    void set_electric_current_exponent(const REAL& x);
    void set_thermodynamic_temperature_exponent(const REAL& x);
    void set_amount_of_substance_exponent(const REAL& x);
    void set_luminous_intensity_exponent(const REAL& x);

    /** \brief Сравнение объектов (равно) */
    bool operator==(const dimensional_exponents& x) const;

    /** \brief Сравнение объектов (не равно) */
    bool operator!=(const dimensional_exponents& x) const;

  };

  /**
   * \brief ENTITY derived_unit_element (ГОСТ Р ИСО 10303-41-1999, 4.14.4.18)
   *
   * <B>4.14.4.18 \ref derived_unit_element</B><BR>
   * Объект <B>\ref derived_unit_element</B> является одной из единиц величин, образующих <B>\ref derived_unit</B>.
   *
   * <SMALL>Пример 86 - Ньютон на квадратный миллиметр является производной единицей. Эта единица имеет
   * два элемента: «ньютон», показатель размерности которого имеет значение 1, и «миллиметр»,
   * показатель размерности которого равен —2.</SMALL>
   *
   * <U>EXPRESS-спецификация:</U>
   * \verbatim
    ENTITY derived_unit_element;
          unit : named_unit;
          exponent : REAL;
    END_ENTITY;
   \endverbatim
   *
   * <U>Определения атрибутов:</U><BR>
   * <B>\ref unit</B> - фиксированная величина, используемая в качестве математического сомножителя;<BR>
   * <B>\ref exponent</B> - степень, в которую возводится атрибут <B>\ref unit</B>.
   */
  class derived_unit_element : public STEP_ENTITY {

  private:

    /** \brief Фиксированная величина, используемая в качестве математического сомножителя. */
    named_unit* unit;
    /** \brief Степень, в которую возводится атрибут <B>\ref unit</B> */
    REAL* exponent;

  public:

    /** \brief Конструктор */
    derived_unit_element(const named_unit& Unit, const REAL& Exponent);

    /** \brief Деструктор */
    virtual ~derived_unit_element();

    /** \brief Получить сомножитель */
    const named_unit* get_unit() const;


    /** \brief Получить степень */
    const REAL* get_exponent() const;

  };

  /**
   * \brief ENTITY derived_unit (ГОСТ Р ИСО 10303-41-1999, 4.14.4.19)
   *
   * <B>4.14.4.19 derived_unit</B><BR>
   * Объект <B>\ref derived_unit</B> является выражением, образованным из единиц.
   * <BR><SMALL>Пример 87 - Ньютон на квадратный миллиметр является <B>\ref derived_unit</B>.</SMALL><BR>
   * <U>EXPRESS-спецификация:</U>
   * \verbatim
    -- DIFF IN AP214
    -- DIFF IN AP224
    -- DIFF IN AP232
    ENTITY derived_unit
       SUPERTYPE OF (ONEOF(absorbed_dose_unit, acceleration_unit, radioactivity_unit, area_unit, capacitance_unit, dose_equivalent_unit, electric_charge_unit, conductance_unit, electric_potential_unit, energy_unit, magnetic_flux_density_unit, force_unit, frequency_unit, illuminance_unit, inductance_unit, magnetic_flux_unit, power_unit, pressure_unit, resistance_unit, velocity_unit, volume_unit));
          elements : SET [1:?] OF derived_unit_element;
       DERIVE
          name : label := get_name_value(SELF);
       WHERE
          WR1:
             (SIZEOF(elements) > 1) OR (SIZEOF(elements) = 1) AND (elements[1].exponent <> 1.0);
          WR2:
             SIZEOF(USEDIN(SELF, 'STEP_MERGED_AP_SCHEMA.NAME_ATTRIBUTE.NAMED_ITEM')) <= 1;
    END_ENTITY;
   \endverbatim
   *
   * <U>Определения атрибутов:</U><BR>
   * <B>\ref elements</B> - группа единиц и их показателей, определяющих <B>\ref derived_unit</B>.<BR>
   * <U>Формальные утверждения:</U><BR>
   * <B>WR1:</B> - должно быть более одного члена в множестве элементов, либо значение показателя
   * единственного элемента в множестве элементов не должно быть равным единице.
   */
  class derived_unit : public STEP_ENTITY {

  private:

    /** \brief группа единиц и их показателей, определяющих <B>\ref derived_unit</B> */
    SET<const derived_unit_element> elements;

  public:

    /** \brief Конструктор */
    derived_unit(const derived_unit_element* Element);

    /** \brief Деструктор */
    virtual ~derived_unit();

    /** \brief Добавление элемента в группу единиц */
    void add_element(const derived_unit_element* Element);

    /** \brief Получить указанную единицу */
    const derived_unit_element* get_element(size_t i) const;

    /** \brief Получить количество единиц */
    size_t get_elements_num() const;


  };

  /**
   * \brief ENTITY global_unit_assigned_context (ГОСТ Р ИСО 10303-41-1999, 4.14.4.20)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
    ENTITY global_unit_assigned_context
       SUBTYPE OF (representation_context);
          units : SET [1:?] OF unit;
    END_ENTITY;
   \endverbatim
   *
   * Объект global_unit_assigned_context является подтипом representation_context, в котором единицы применяются ко всем measure_value
   * указанного вида.
   */
  class global_unit_assigned_context : public representation_context {

  private:

    SET<const unit>  units; //  единицы, применимые в representation context

  public:

    // Конструктор
    global_unit_assigned_context() : representation_context("", "") {
      add_attr_info(STEP_ATTR_LIST({ {"units", &units} }, this));
      // !!!
    }

    // Добавть единицу к набору
    void add_unit(const unit* x) {
      units.push_back(x);
    }
  };

  /**
   * \brief ENTITY measure_with_unit (ГОСТ Р ИСО 10303-41-1999, 4.14.4.21)
   *
   * <B>4.14.4.21 \ref measure_with_unit</B><BR>
   * Объект <B>\ref measure_with_unit</B> является определением физической
   * величины в соответствии с определением по ИСО 31-0 (раздел 2).
   *
   * <U>EXPRESS-спепиФикация:</U>
   * \verbatim
    -- DIFF IN AP214
    -- DIFF IN AP224
    -- DIFF IN AP232
    ENTITY measure_with_unit
       SUPERTYPE OF (ONEOF(length_measure_with_unit, mass_measure_with_unit, time_measure_with_unit, electric_current_measure_with_unit, thermodynamic_temperature_measure_with_unit, celsius_temperature_measure_with_unit, amount_of_substance_measure_with_unit, luminous_intensity_measure_with_unit, plane_angle_measure_with_unit, solid_angle_measure_with_unit, area_measure_with_unit, volume_measure_with_unit, ratio_measure_with_unit, acceleration_measure_with_unit, capacitance_measure_with_unit, electric_charge_measure_with_unit, conductance_measure_with_unit, electric_potential_measure_with_unit, energy_measure_with_unit, magnetic_flux_density_measure_with_unit, force_measure_with_unit, frequency_measure_with_unit, illuminance_measure_with_unit, inductance_measure_with_unit, luminous_flux_measure_with_unit, magnetic_flux_measure_with_unit, power_measure_with_unit, pressure_measure_with_unit, resistance_measure_with_unit, velocity_measure_with_unit, absorbed_dose_measure_with_unit, radioactivity_measure_with_unit, dose_equivalent_measure_with_unit));
          value_component : measure_value;
          unit_component : unit;
       WHERE
          WR1:
             valid_units(SELF);
    END_ENTITY;
   \endverbatim
   *
   * <U>Определения атрибутов:</U><BR>
   * <B>\ref value_component</B> - значение физической величины, выраженное в конкретных единицах;<BR>
   * <B>\ref unit_component</B> - единица, в которой выражена физическая величина.
   *
   * <U>Формальные утверждения:</U><BR>
   * <B>WR1:</B> - единица должна быть правильной единицей для измерения данного вида.
   *
   * <A HREF="https://www.steptools.com/stds/stp_aim/html/t_measure_with_unit.html">Ссылка.</A>
   */
  class measure_with_unit : public STEP_ENTITY {

  private:

    /** \brief Значение физической величины, выраженное в конкретных единицах. */
    const measure_value* value_component;

    /** \brief Единица, в которой выражена физическая величина */
    const unit* unit_component;

  public:

    // !!!
    measure_with_unit(const measure_value* Value_component, const unit* Unit_component) :
      value_component(Value_component), unit_component(Unit_component) {
      // Информация об аргументах этого класса
      add_attr_info(STEP_ATTR_LIST({ {"value_component", value_component},
                                     {"unit_component",  unit_component}
                                   }, this));
    }

    virtual ~measure_with_unit() {
    }

    /**
     * \brief Получить единицу, в которой выражена физическая величина.
     * \return единицу, в которой выражена физическая величина.
     */
    const unit* get_unit_component() const {
      return unit_component;
    }
  };

  /* <B>4.14.5 Определения функций measure_schema</B> */

  /** 
   * \brief FUNCTION dimensions_for_si_unit (ГОСТ Р ИСО 10303-41, 4.14.5.1)
   * \param [in] n Наименование единицы, для которой выдается <B>dimensional_exponents</B> (исходные данные).
   * \return Показатели размерности в виде типа <B>\ref dimensional_exponents</B>.
   * 
   * <B>4.14.5.1 \ref dimensions_for_si_unit</B>
   * Функция <B>\ref dimensions_for_si_unit</B> возвращает <B>\ref dimensional_exponents</B> для заданной <B>si_unit</B>.
   *
   * <U>EXPRESS-спецификация:</U>
   * \verbatim
    *)
    FUNCTION dimensions_for_si_unit (n : si_unit_name) : dimensional_exponents;

    CASE n OF 
          metre:
            RETURN (dimensional_exponents(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0));
          gram:
            RETURN (dimensional_exponents(0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0));
          second:
            RETURN (dimensional_exponents(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0));
          ampere:
            RETURN (dimensional_exponents(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0));
          kelvin:
            RETURN (dimensional_exponents(0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0));
          mole:
            RETURN (dimensional_exponents(0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0));
          candela:
            RETURN (dimensional_exponents(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0));
          radian:
            RETURN (dimensional_exponents(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0));
          steradian:
            RETURN (dimensional_exponents(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0));
          hertz:
            RETURN (dimensional_exponents(0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0));
          newton:
            RETURN (dimensional_exponents(1.0, 1.0, -2.0, 0.0, 0.0, 0.0, 0.0));
          pascal:
            RETURN (dimensional_exponents(-1.0, 1.0, -2.0, 0.0, 0.0, 0.0, 0.0));
          joule:
            RETURN (dimensional_exponents(2.0, 1.0, -2.0, 0.0, 0.0, 0.0, 0.0));
          watt:
            RETURN (dimensional_exponents(2.0, 1.0, -3.0, 0.0, 0.0, 0.0, 0.0));
          coulomb:
            RETURN (dimensional_exponents(0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0));
          volt:
            RETURN (dimensional_exponents(2.0, 1.0, -3.0, -1.0, 0.0, 0.0, 0.0));
          farad:
            RETURN (dimensional_exponents(-2.0, -1.0, 4.0, 2.0, 0.0, 0.0, 0.0));
          ohm:
            RETURN (dimensional_exponents(2.0, 1.0, -3.0, -2.0, 0.0, 0.0, 0.0));
          siemens:
            RETURN (dimensional_exponents(-2.0, -1.0, 3.0, 2.0, 0.0, 0.0, 0.0));
          weber:
            RETURN (dimensional_exponents(2.0, 1.0, -2.0, -1.0, 0.0, 0.0, 0.0));
          tesla:
            RETURN (dimensional_exponents(0.0, 1.0, -2.0, -1.0, 0.0, 0.0, 0.0));
          henry:
            RETURN (dimensional_exponents(2.0, 1.0, -2.0, -2.0, 0.0, 0.0, 0.0));
          degree_Celsius:
            RETURN (dimensional_exponents(0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0));
          lumen:
            RETURN (dimensional_exponents(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0));
          lux:
            RETURN (dimensional_exponents(-2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0));
          becquerel:
            RETURN (dimensional_exponents(0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0));
          gray:
            RETURN (dimensional_exponents(2.0, 0.0, -2.0, 0.0, 0.0, 0.0, 0.0));
          sievert:
            RETURN (dimensional_exponents(2.0, 0.0, -2.0, 0.0, 0.0, 0.0, 0.0));
          OTHERWISE:
            RETURN (?);
        END_CASE;
    
    END_FUNCTION;
    (* 
    \endverbatim
   * <U>Определения аргументов:</U><BR>
   * <B>n</B> - наименование единицы, для которой выдается <B>dimensional_exponents</B> (исходные данные).
   */
  dimensional_exponents dimensions_for_si_unit(const si_unit_name& n);

  /** 
   * \brief FUNCTION derive_dimensional_exponents (ГОСТ Р ИСО 10303-41, 4.14.5.2)
   * \param [in] x Единица, для которой вычисляют <B>\ref dimensional_exponents</B> (исходные данные).
   * \return Показатели размерности в виде <B>\ref dimensional_exponents</B>.
   * 
   * <B>4.14.5.2 derive_dimensional_exponents</B><BR>
   * Данная функция определяет показатели размерности единицы. Для именованных единиц должен
   * быть выдан атрибут <B>dimensions</B>, а для производных единиц показатели размерности должны быть
   * вычислены поэлементно.
   * 
   * <U>EXPRESS-спецификация:</U>
   * \verbatim
    -- DIFF IN AP224
    -- DIFF IN AP232
    FUNCTION derive_dimensional_exponents (x : unit) : dimensional_exponents;
  
    LOCAL
          result : dimensional_exponents := dimensional_exponents(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
        END_LOCAL;
  
        IF 'MEASURE_SCHEMA.DERIVED_UNIT' IN TYPEOF(x) THEN
          REPEAT i := LOINDEX(x\derived_unit.elements) TO HIINDEX(x\derived_unit.elements);
            result.length_exponent := result.length_exponent +
            (x\derived_unit.elements[i]\derived_unit_element.exponent *
             x\derived_unit.elements[i]\derived_unit_element.unit\named_unit.dimensions.length_exponent);
            result.mass_exponent := result.mass_exponent +
            (x\derived_unit.elements[i]\derived_unit_element.exponent *
             x\derived_unit.elements[i]\derived_unit_element.unit\named_unit.dimensions.mass_exponent);
            result.time_exponent := result.time_exponent +
            (x\derived_unit.elements[i]\derived_unit_element.exponent *
             x\derived_unit.elements[i]\derived_unit_element.unit\named_unit.dimensions.time_exponent);
            result.electric_current_exponent := result.electric_current_exponent +
            (x\derived_unit.elements[i]\derived_unit_element.exponent *
             x\derived_unit.elements[i]\derived_unit_element.unit\named_unit.dimensions.electric_current_exponent);
            result.thermodynamic_temperature_exponent := result.thermodynamic_temperature_exponent +
            (x\derived_unit.elements[i]\derived_unit_element.exponent *
             x\derived_unit.elements[i]\derived_unit_element.unit\named_unit.dimensions.thermodynamic_temperature_exponent);
            result.amount_of_substance_exponent := result.amount_of_substance_exponent +
            (x\derived_unit.elements[i]\derived_unit_element.exponent *
             x\derived_unit.elements[i]\derived_unit_element.unit\named_unit.dimensions.amount_of_substance_exponent);
            result.luminous_intensity_exponent := result.luminous_intensity_exponent +
            (x\derived_unit.elements[i]\derived_unit_element.exponent *
             x\derived_unit.elements[i]\derived_unit_element.unit\named_unit.dimensions.luminous_intensity_exponent);
          END_REPEAT;
        ELSE
          result := x\named_unit.dimensions;
        END_IF;
        RETURN (result);
  
    END_FUNCTION;
    \endverbatim
   * <U>Определения аргументов:</U><BR>
   * <B>x</B> - единица, для которой вычисляют <B>\ref dimensional_exponents</B> (исходные данные).
   */
  dimensional_exponents derive_dimensional_exponents(const unit& x);

  /**
   * \brief FUNCTION valid_units (ГОСТ Р ИСО 10303-41, 4.14.5.3)
   * \param [in] m Проверяемый кандидат <B>\ref measure_with_unit</B> (исходные данные).
   * \return результат проверки правильности: true или false. 
   *
   * <B>4.14.5.3 valid_units</B>
   * Функция <B>\ref valid_units</B> проверяет правильность <B>\ref measure_with_unit</B>. Если единица в
   * <B>\ref measure_with_unit</B> верна, то функция возвращает значение TRUE, в противном случае функция
   * возвращает значение FALSE.
   *
   * <U>EXPRESS-спецификация:</U>
   * \verbatim
    FUNCTION valid_units (m : measure_with_unit) : BOOLEAN;

    IF 'MEASURE_SCHEMA.LENGTH_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
          dimensional_exponents(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.MASS_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
          dimensional_exponents(0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.TIME_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
          dimensional_exponents(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.ELECTRIC_CURRENT_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
          dimensional_exponents(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.THERMODYNAMIC_TEMPERATURE_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
          dimensional_exponents(0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.CELSIUS_TEMPERATURE_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
          dimensional_exponents(0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.AMOUNT_OF_SUBSTANCE_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
          dimensional_exponents(0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.LUMINOUS_INTENSITY_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
          dimensional_exponents(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.PLANE_ANGLE_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
          dimensional_exponents(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.SOLID_ANGLE_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
          dimensional_exponents(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.AREA_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
          dimensional_exponents(2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.VOLUME_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
          dimensional_exponents(3.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.RATIO_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
          dimensional_exponents(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.POSITIVE_LENGTH_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
          dimensional_exponents(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.POSITIVE_PLANE_ANGLE_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
          dimensional_exponents(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.ACCELERATION_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
            dimensional_exponents( 1.0, 0.0, -2.0, 0.0, 0.0, 0.0, 0.0 ) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
         IF 'MEASURE_SCHEMA.CAPACITANCE_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
            dimensional_exponents( -2.0, -1.0, 4.0, 2.0, 0.0, 0.0, 0.0 ) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.ELECTRIC_CHARGE_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
            dimensional_exponents( 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 ) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
            IF 'MEASURE_SCHEMA.CONDUCTANCE_MEASURE' IN TYPEOF(m.value_component) THEN
              IF derive_dimensional_exponents(m.unit_component) <> 
                dimensional_exponents( -2.0, -1.0, 3.0, 2.0, 0.0, 0.0, 0.0 ) THEN
                RETURN (FALSE);
              END_IF;
        END_IF;
            IF 'MEASURE_SCHEMA.ELECTRIC_POTENTIAL_MEASURE' IN TYPEOF(m.value_component) THEN
              IF derive_dimensional_exponents(m.unit_component) <> 
                dimensional_exponents( 2.0, 1.0, -3.0, -1.0, 0.0, 0.0, 0.0 ) THEN
                RETURN (FALSE);
              END_IF;
        END_IF;    
        IF 'MEASURE_SCHEMA.ENERGY_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
            dimensional_exponents( 2.0, 1.0, -2.0, 0.0, 0.0, 0.0, 0.0 ) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.FORCE_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
            dimensional_exponents( 1.0, 1.0, -2.0, 0.0, 0.0, 0.0, 0.0 ) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.FREQUENCY_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
            dimensional_exponents( 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0 ) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.ILLUMINANCE_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
            dimensional_exponents( -2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 ) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
         IF 'MEASURE_SCHEMA.INDUCTANCE_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
            dimensional_exponents( 2.0, 1.0, -2.0, -2.0, 0.0, 0.0, 0.0 ) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.LUMINOUS_FLUX_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
            dimensional_exponents( 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 ) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.MAGNETIC_FLUX_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
            dimensional_exponents( 2.0, 1.0, -2.0, -1.0, 0.0, 0.0, 0.0 ) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
         IF 'MEASURE_SCHEMA.MAGNETIC_FLUX_DENSITY_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
            dimensional_exponents( 0.0, 1.0, -2.0, -1.0, 0.0, 0.0, 0.0 ) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.POWER_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
            dimensional_exponents( 2.0, 1.0, -3.0, 0.0, 0.0, 0.0, 0.0 ) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.PRESSURE_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
            dimensional_exponents( -1.0, 1.0, -2.0, 0.0, 0.0, 0.0, 0.0 ) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.RESISTANCE_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
            dimensional_exponents( 2.0, 1.0, -3.0, -2.0, 0.0, 0.0, 0.0 ) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.VELOCITY_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
            dimensional_exponents( 1.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0 ) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.RADIOACTIVITY_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
            dimensional_exponents(0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.ABSORBED_DOSE_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
            dimensional_exponents(2.0, 0.0, -2.0, 0.0, 0.0, 0.0, 0.0) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        IF 'MEASURE_SCHEMA.DOSE_EQUIVALENT_MEASURE' IN TYPEOF(m.value_component) THEN
          IF derive_dimensional_exponents(m.unit_component) <> 
            dimensional_exponents(2.0, 0.0, -2.0, 0.0, 0.0, 0.0, 0.0) THEN
            RETURN (FALSE);
          END_IF;
        END_IF;
        RETURN (TRUE);
    
    END_FUNCTION;
    (*
    \endverbatim
   * <U>Определения аргументов:</U><BR>
   * <B>m</B> - проверяемый кандидат <B>\ref measure_with_unit</B> (исходные данные).
   */
  bool valid_units(const measure_with_unit& m);

  /**
   * \brief TYPE represented_definition (ISO 10303-41:2005(E), 7.3.1)
   *
   * <B>7.3.1 represented_definition</B>
   * The <B>represented_definition</B> type allows for the designation of a <B>general_property</B>, a
   * <B>property_definition</B>, a <B>property_definition_relationship</B>, a <B>shape_aspect</B>, or a
   * <B>shape_aspect_relationship</B>.
   *
   * <U>EXPRESS specification</U>
   * \verbatim
    *)
    TYPE represented_definition = SELECT
          (general_property,
           property_definition,
           property_definition_relationship,
           shape_aspect,
           shape_aspect_relationship);
    END_TYPE;
    (*
    \endverbatim
   *
   */
  class represented_definition : public SELECT {

  public:

    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(represented_definition, general_property);
    STEP_TYPE_SELECT_CONSTRUCTOR_DEF(represented_definition, property_definition);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(represented_definition, property_definition_relationship);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(represented_definition, shape_aspect);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(represented_definition, shape_aspect_relationship);
  };

  /**
   * \brief TYPE source_item (ISO 10303-41:2005(E), 19.3.2)
   *
   * <B>19.3.2 source_item</B><BR>
   * A <B>source_item</B> type allows for the designation of an <B>identifier</B> or a <B>message</B>.
   *
   * <U>EXPRESS specification:</U>
   * \verbatim
    *)
    TYPE source_item = SELECT
      (identifier,                                                 -- Common
       message);                                                   -- AP203e2/AP232/AP238 STEP-NC/AP242
    END_TYPE;
    (*
   \endverbatim
   *
   */
  class source_item : public SELECT {

  public:

    STEP_TYPE_SELECT_CONSTRUCTOR_DEF(source_item, identifier);
    STEP_TYPE_SELECT_CONSTRUCTOR_DEF(source_item, message);
  };

  /**
   * \brief ENTITY generic_product_definition_reference (ISO 10303-41:2021(E), 21.4.3)
   *
   * <B>21.4.3 generic_product_definition_reference</B>
   * A <B>generic_product_definition_reference</B> is a reference to an externally defined <B>product_definition</B>
   * that may or may not have a local representation. A <B>generic_product_definition_reference</B> is either a
   * <B>product_definition_reference</B> or a <B>product_definition_reference_with_local_representation</B>.
   *
   * <U>EXPRESS specification:</U>
   * \verbatim
    -- IN AP238 STEP-NC/AP242
    ENTITY generic_product_definition_reference
       ABSTRACT SUPERTYPE OF (ONEOF(product_definition_reference, product_definition_reference_with_local_representation));
          source : external_source;
    END_ENTITY;
   \endverbatim
   *
   * Конктретный вид версии изделия
   */
  class generic_product_definition_reference : public STEP_ENTITY {
  private:

    /** \brief Defines the location which contains the original definition of the <B>product_definition</B>. */
    const external_source* source;

  public:

    generic_product_definition_reference(const external_source* Source) {
      source = Source;
      //!!! attribs
    }

    virtual ~generic_product_definition_reference() {
    }
  };

  /**
   * \brief TYPE characterized_item (ISO 10303-41:2021(E), 22.3.2)
   *
   * <B>22.3.2 characterized_item</B>
   * The <B>characterized_item</B> type is a list of alternate data types. It provides a mechanism to refer to an
   * instance of one of these data types. The <B>characterized_item</B> type allows for the designation of an
   * <B>item_identified_representation_usage</B>, a <B>dimensional_size</B>, or a <B>geometric_tolerance</B> to
   * which properties may be assigned.
   *
   * <U>EXPRESS specification:</U>
   * \verbatim
    TYPE characterized_item = SELECT
       (dimensional_size,
        geometric_tolerance,
        item_identified_representation_usage);
    END_TYPE;
   \endverbatim
   *
   * <A HREF="https://www.steptools.com/stds/stp_aim/html/t_characterized_item.html">Ссылка.</A>
   */
  class characterized_item : public SELECT {

  public:

    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(characterized_item, dimensional_size);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(characterized_item, geometric_tolerance);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(characterized_item, item_identified_representation_usage);
  };

  /**
   * \brief TYPE id_attribute_select (ISO 10303-41:2005(E), 22.3.2)
   *
   * <B>22.3.2 id_attribute_select</B><BR>
   * An <B>id_attribute_select</B> specifies those objects that may be assigned an identifier.
   *
   * <U>EXPRESS specification</U>
   * \verbatim
    -- DIFF IN AP214
    -- DIFF IN AP203e2
    -- DIFF IN AP238 STEP-NC
    -- DIFF IN AP224
    -- DIFF IN AP232
    TYPE id_attribute_select = SELECT
      (action,                                                     -- Common
       address,                                                    -- Common
       application_context,                                        -- Common
       ascribable_state_relationship,                              -- AP242
       dimensional_size,                                           -- AP238 STEP-NC/AP242
       geometric_tolerance,                                        -- AP238 STEP-NC/AP242
       group,                                                      -- Common
       organizational_project,                                     -- AP203e2/AP214/AP232/AP238 STEP-NC/AP242
       product_category,                                           -- AP203e2/AP214/AP232/AP238 STEP-NC/AP242
       property_definition,                                        -- Common
       representation,                                             -- Common
       shape_aspect,                                               -- Common
       shape_aspect_relationship,                                  -- Common
       topological_representation_item);                           -- AP238 STEP-NC/AP242
    END_TYPE;
   \endverbatim
   *
   */
  class id_attribute_select : public SELECT {

  public:

    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(id_attribute_select, action);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(id_attribute_select, address);
    STEP_TYPE_SELECT_CONSTRUCTOR_DEF(id_attribute_select, application_context);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(id_attribute_select, dimensional_size);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(id_attribute_select, geometric_tolerance);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(id_attribute_select, group);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(id_attribute_select, organizational_project);
    STEP_TYPE_SELECT_CONSTRUCTOR_DEF(id_attribute_select, product_category);
    STEP_TYPE_SELECT_CONSTRUCTOR_DEF(id_attribute_select, property_definition);
    STEP_TYPE_SELECT_CONSTRUCTOR_DEF(id_attribute_select, representation);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(id_attribute_select, shape_aspect);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(id_attribute_select, shape_aspect_relationship);
    STEP_TYPE_SELECT_CONSTRUCTOR_DEF(id_attribute_select, topological_representation_item);
  };



/**
 * \brief TYPE year_number (ISO 10303-41, 4.9.3.2)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  TYPE year_number = INTEGER;
     WHERE
        WR1:
           SELF > 1581;
  END_TYPE;
 \endverbatim
 *
 * Тип year_number является годом, определяемым по Григорианскому календарю.<BR>
 * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_year_number.html">Ссылка.</A>
 */
class year_number : public INTEGER {

public:

  year_number() : INTEGER() {
  }
  year_number(const int v) : INTEGER(v) {
    assert(*this > 1581);
  }

  virtual STEP_OBJTYPE objtype() const {
    return STEP_OBJTYPE::TYPE_DEFINED;
  }
};

/**
 * \brief TYPE length_measure (ISO 10303-41, 4.14.3.2)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  TYPE length_measure = REAL;
  END_TYPE;
 \endverbatim
 *
 * Тип length_measure определяет значение расстояния.<BR>
 * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_length_measure.html">Ссылка.</A>
 */
class length_measure : public REAL {

public:

  length_measure() : REAL() {
  }
  length_measure(const double v) : REAL(v) {
  }

  double getval(void) const {
    return REAL::getval();
  }

  virtual STEP_OBJTYPE objtype() const {
    return STEP_OBJTYPE::TYPE_DEFINED;
  }
};

/**
 * \brief TYPE non_negative_length_measure (ISO 10303-41:2005/Cor.1:2008(E), 21.3.41)
 *
 * <B>21.3.41 non_negative_length_measure</B><BR>
 * <B>A non_negative_length_measure</B> type is a <B>length_measure</B> whose value is greater than or equal to zero.
 *
 * <U>Formal propositions</U>:
 * \verbatim
  TYPE non_negative_length_measure = length_measure;
     WHERE
        WR1:
           SELF >= 0.0;
  END_TYPE;
 \endverbatim
 *
 * <B>WR1:</B> A <B>non_negative_length_measure</B> shall be positive or zero.
 *
 * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_non_negative_length_measure.html">Ссылка.</A>
 */
class non_negative_length_measure : public length_measure {
  public:

    non_negative_length_measure() : length_measure() {
    }
    non_negative_length_measure(const double v) : length_measure(v) {
      assert(*this >= 0.0);
    }

    double getval(void) const {
      return length_measure::getval();
    }
};

/**
 * \brief TYPE positive_length_measure (ГОСТ Р ИСО 10303-41-1999, 4.14.3.16)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  TYPE positive_length_measure = non_negative_length_measure;
     WHERE
        WR1:
           SELF > 0.0;
  END_TYPE;
 \endverbatim
 *
 * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_positive_length_measure.html">Ссылка.</A>
 */
class positive_length_measure : public non_negative_length_measure {
public:

  positive_length_measure() : non_negative_length_measure() {
  }
  positive_length_measure(const double v) : non_negative_length_measure(v) {
    assert(*this > 0.0);
  }

  double getval(void) const {
    return length_measure::getval();
  }
};

/**
 * \brief TYPE plane_angle_measure (ГОСТ Р ИСО 10303-41-1999, 4.14.3.9)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  TYPE plane_angle_measure = REAL;
  END_TYPE;
 \endverbatim
 *
 * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_plane_angle_measure.html">Ссылка.</A>
 */
class plane_angle_measure : public REAL {
  public:

    plane_angle_measure() : REAL() {
    }
    plane_angle_measure(const double v) : REAL(v) {
    }

    double getval(void) const {
      return REAL::getval();
    }

    virtual STEP_OBJTYPE objtype() const {
      return STEP_OBJTYPE::TYPE_DEFINED;
    }
};

/**
 * \brief TYPE solid_angle_measure (ГОСТ Р ИСО 10303-41-1999, 4.14.3.10)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  TYPE solid_angle_measure = REAL;
  END_TYPE;
 \endverbatim
 *
 * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_solid_angle_measure.html">Ссылка.</A>
 */
class solid_angle_measure : public REAL {
  public:

    solid_angle_measure() : REAL() {
    }
    solid_angle_measure(const double v) : REAL(v) {
    }

    double getval(void) const {
      return REAL::getval();
    }

    virtual STEP_OBJTYPE objtype() const {
      return STEP_OBJTYPE::TYPE_DEFINED;
    }
};

/**
 * \brief TYPE label (ISO 10303-41, 20.3.2)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
   TYPE label = STRING;
   END_TYPE;
 \endverbatim
 *
 * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_label.html">Ссылка.</A>
 */
class label : public STRING {
  public:

    label() : STRING() {
    }
    label(const std::string &v) : STRING(v) {
    }
    label(const char* v) : STRING(v) {
    }

    virtual STEP_OBJTYPE objtype() const {
      return STEP_OBJTYPE::TYPE_DEFINED;
    }
};

/**
 * \brief TYPE identifier (ISO 10303-41, 20.3.1)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  TYPE identifier = STRING;
  END_TYPE;
 \endverbatim
 *
 * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_identifier.html">Ссылка.</A>
 */
class identifier : public STRING {
  public:
    identifier() : STRING() {
    }
    identifier(const std::string &v) : STRING(v) {
    }
    identifier(const char* v) : STRING(v) {
    }

    virtual STEP_OBJTYPE objtype() const {
      return STEP_OBJTYPE::TYPE_DEFINED;
    }
};

/**
 * \brief TYPE text (ISO 10303-41, 20.3.3)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  TYPE text = STRING;
  END_TYPE;
 \endverbatim
 *
 * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_text.html">Ссылка.</A>
 */
class text : public STRING {
  public:

    text() : STRING() {
    }
    text(const std::string &v) : STRING(v) {
    }
    text(const char* v) : STRING(v) {
    }

    virtual STEP_OBJTYPE objtype() const {
      return STEP_OBJTYPE::TYPE_DEFINED;
    }

};

/**
 * \brief TYPE message (ISO 10303-41, 19.3.1)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  -- IN AP203e2/AP232/AP238 STEP-NC/AP242
  TYPE message = STRING;
  END_TYPE;
 \endverbatim
 *
 * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_message.html">Ссылка.</A>
 */
class message : public STRING {
  public:

    message() : STRING() {
    }
    message(const std::string &v) : STRING(v) {
    }
    message(const char* v) : STRING(v) {
    }

    virtual STEP_OBJTYPE objtype() const {
      return STEP_OBJTYPE::TYPE_DEFINED;
    }
};



}
