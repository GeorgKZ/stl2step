/**
 * \file
 *
 * \brief Заголовочный файл с определениями классов, соответствующих ГОСТ Р ИСО 10303-43-2016.
 *
 * В это файл включены определения классов элементов языка EXPRESS стандарта 10303-43,
 * родительских по отношению к некотороым описаниям классов стандарта 10303-41, и поэтому
 * помещённых в первую очередь описания вне "своего" заголовочного файла.
 */

namespace express {




/**
 * \brief ENTITY representation_relationship (ГОСТ Р ИСО 10303-43, 4.4.5)
 *
 * <P><U>EXPRESS-спецификация:</U></P>
 * \verbatim
  -- DIFF IN AP214
  -- DIFF IN AP203e2
  -- DIFF IN AP224
  -- DIFF IN AP232
  ENTITY representation_relationship;
        name : label;
        description : OPTIONAL text;
        rep_1 : representation_or_representation_reference;
        rep_2 : representation_or_representation_reference;
  END_ENTITY;
 \endverbatim
 *
 */
class representation_relationship : public STEP_ENTITY {

private:

  label* name;        // Название взаимосвязи
  text* description; // OPTIONAL дополнительное описание взаимосвязи
  const representation* rep_1;       // Первый объект взаимосвязи 
  const representation* rep_2;       // Второй объект взаимосвязи

public:

  /**
   * \brief Конструктор.
   * 
   * \param [in] Name
   * \param [in] Description
   * \param [in] Rep1
   * \param [in] Rep2
   */
  representation_relationship(const std::string& Name, const std::string& Description, const representation* Rep1, const representation* Rep2);

  virtual ~representation_relationship();
};

/* используется в 10303-41 */

/**
 * \brief ENTITY representation (ГОСТ Р ИСО 10303-43-2016, 4.4.13)
 *
 *<P><U>EXPRESS-спецификация:</U></P>
 * \verbatim
  -- DIFF IN AP214
  -- DIFF IN AP203e2
  -- DIFF IN AP238 STEP-NC
  -- DIFF IN AP224
  -- DIFF IN AP232
  ENTITY representation
     SUPERTYPE OF (((ONEOF(reinforcement_orientation_basis, ply_angle_representation) ANDOR ONEOF(interpolated_configuration_representation, link_motion_representation_along_path)) ANDOR ONEOF(kinematic_link_representation, kinematic_topology_structure, kinematic_topology_directed_structure, kinematic_topology_network_structure, mechanism_representation, shape_representation)) ANDOR ONEOF(kinematic_topology_structure, kinematic_topology_directed_structure, kinematic_topology_network_structure));
        name : label;
        items : SET [1:?] OF representation_item;
        context_of_items : representation_context;
     DERIVE
        id : identifier := get_id_value(SELF);
        description : text := get_description_value(SELF);
     WHERE
        WR1:
           SIZEOF(USEDIN(SELF, 'STEP_MERGED_AP_SCHEMA.ID_ATTRIBUTE.IDENTIFIED_ITEM')) <= 1;
        WR2:
           SIZEOF(USEDIN(SELF, 'STEP_MERGED_AP_SCHEMA.DESCRIPTION_ATTRIBUTE.DESCRIBED_ITEM')) <= 1;
  END_ENTITY;
 \endverbatim
 *
 * Представление
 */
class representation : public STEP_ENTITY {

private:

  label* name;                // Имя, однозначно идентифицирующее модель
  LIST<const representation_item>* items;               // Массив ссылок на элементы представления, связанные с контекстом представления
  const representation_context* context_of_items;    // Контекст представления или комплесный объект

public:

  /** \brief Конструктор */
  representation(const std::string& Name, const representation_context* Context_of_items);

  /** \brief Деструктор */
  virtual ~representation();

  void add_item(const representation_item* x) {
    items->push_back(x);
  }

  // FUNCTION get_id_value
  virtual identifier get_id_value(void) = 0; // { // id_attribute_select
//      return "";
//    }

  // FUNCTION get_description_value
  virtual text get_description_value(void) = 0; // { // DESCRIPTION_ATTRIBUTE_SELECT
//      return "";
//    }
};


/* используется в 10303-41 */

/**
 * \brief ENTITY representation_context (ГОСТ Р ИСО 10303-43-2016, 4.4.14)
 *
 * <P><U>EXPRESS-спецификация:</U></P>
 * \verbatim
  ENTITY representation_context;
        context_identifier : identifier;
        context_type : text;
     INVERSE
        representations_in_context : SET [1:?] OF representation FOR context_of_items;
  END_ENTITY;
 \endverbatim
 *
 * Контекст, связывающий экземпляры объектов representation_item.
 */
class representation_context : public STEP_ENTITY {

private:

  const identifier* context_identifier;           // Идентификация контекста представления
  const text* context_type;	           // Описание типа контекста представления

public:

  /** \brief Конструктор */
  representation_context(const std::string& Identifier, const std::string& Type);

  /** \brief Деструктор */
  virtual ~representation_context();
};


}
