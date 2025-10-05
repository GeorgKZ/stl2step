/**
 * \file
 *
 * \brief Заголовочный файл с определениями классов, соответствующих ISO 10303-44:2021(E).
 *
 */

namespace express {

/**
 * \brief ENTITY product_definition_usage (ISO 10303-44:2021(E), 4.4.14)
 *
 * <B>4.4.14 product_definition_usage</B>
 * A <B>product_definition_usage</B> is a type of <B>product_definition_relationship</B> that specifies
 * a directed association between two <B>product_definitions</B> in which the <B>related_product_definition</B>
 * is used in the context of the <B>relating_product_definition</B>. The <B>product_definition_usage</B>
 * establishes a relationship stating that the related product is used in the context of the relating product.
 * This usage is established for the life cycle stages and application contexts in which the two products
 * are described. 
 *
 * <SMALL>EXAMPLE 1 The assembly trees established for production sometimes contain more intermediate
 * levels than the trees established during the design phase. In such a case, the design phase relationship
 * between a component and the assembly in which it is contained may be replaced by several intermediate
 * relationships during production.
 *
 * EXAMPLE 2 A given product may be used in a support role with respect to another product. A screwdriver
 * may be identified as a resource to be used for the maintenance life cycle stage of a given product.
 * In such a case, the support resource relationship between the screwdriver and the product for which
 * it is identified to be used for maintenance activities may be specified.
 *
 * EXAMPLE 3 If four identical bolts are used to attach two plates, there may be a need to identify
 * one specific bolt for some purpose. It needs to be torqued to a greater degree than the rest.
 * The inherited id attribute then is used to identify this specific bolt's requirement, even though
 * the product_definition_usages of all four bolts will have the same attribute pair of product_definitions.</SMALL>
 *
 * A <B>product_definition_usage</B> may be either a <B>make_from_usage_option</B> or an <B>assembly_component_usage</B>.
 *
 * <U>EXPRESS specification:</U>
 * \verbatim
  -- CASE DIFF IN AP214
  -- DIFF IN AP224
  -- DIFF IN AP232
  ENTITY product_definition_usage
     SUPERTYPE OF (ONEOF(make_from_usage_option,
                         assembly_component_usage))
     SUBTYPE OF (product_definition_relationship);
     UNIQUE
        UR1 : SELF\product_definition_relationship.id, SELF\product_definition_relationship.relating_product_definition, SELF\product_definition_relationship.related_product_definition;
     WHERE
        WR1:
           acyclic_product_definition_relationship(SELF, [ SELF\product_definition_relationship.related_product_definition ], 'STEP_MERGED_AP_SCHEMA.PRODUCT_DEFINITION_USAGE');
  END_ENTITY;
 \endverbatim
 *
 * <U>Formal propositions:</U><BR>
 * <B>UR1:</B> The combination of the inherited <B>id</B>, <B>relating_product_definition</B>, and
 * <B>related_product_definition</B> attributes shall be unique within a scope of <B>product_definition_usage</B>.
 *
 * <B>WR1:</B> Each <B>product_definition_usage</B> shall not relate the same <B>relating_product_definition</B>
 * instance of <B>product_definition</B> to the <B>related_product_definition</B> or any of its descendants
 * formed by their reference as the <B>relating_product_definition</B> in a graph of <B>product_definition_usages.</B>
 *
 * <SMALL>NOTE This rule uses the function <B>acyclic_product_definition_relationship</B> defined in the
 * <B>product_definition_schema</B> in ISO 10303-41.</SMALL> 
 */
class product_definition_usage : public product_definition_relationship {

public:

  product_definition_usage(identifier Id, label Name, text Description,
    const product_definition_or_reference* Relating_product_definition,
    const product_definition_or_reference* Related_product_definition)
    : product_definition_relationship(Id, Name, Description, Relating_product_definition, Related_product_definition) {
    add_attr_info(STEP_ATTR_LIST({
                                   { }
                                 }, this));
  }

  virtual ~product_definition_usage() {
  }
};

/**
 * \brief ENTITY assembly_component_usage (ГОСТ Р ИСО 10303-44-2002, 4.3.2)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
 \endverbatim
 *
 * Связь между идентификатором  - определением компонента и идентификатором - родительской сборкой
 */
class assembly_component_usage : public product_definition_usage {
private:

  identifier       reference_designator;  // OPTIONAL

public:

  assembly_component_usage(const identifier &Id,
    const label &Name,
    const text &Description,
    const product_definition_or_reference* Relating_product_definition,
    const product_definition_or_reference* Related_product_definition,
    const identifier &Reference_designator = "") :
    product_definition_usage(Id, Name, Description, Relating_product_definition, Related_product_definition),
    reference_designator(Reference_designator) {
    add_attr_info(STEP_ATTR_LIST({ {"reference_designator", &reference_designator, true} }, this));
    }
};

/**
 * \brief ENTITY next_assembly_usage_occurrence (ISO 10303-44:2021(E), 4.4.8)
 *
 * <B>4.4.8 next_assembly_usage_occurrence</B><BR>
 * A <B>next_assembly_usage_occurrence</B> is a type of <B>assembly_component_usage</B> that specifies the
 * relationship between a child constituent and its immediate parent assembly in a product structure.
 *
 * Одиночное индивидуальное включение определения компонента после родительской сборки.
 *
 * <SMALL><B>NOTE 1</B> An instance of <B>next_assembly_usage_occurrence</B> represents an individual occurrence
 * of a constituent in an assembly. Each specific use of the same constituent may be represented by another distinct
 * <B>next_assembly_usage_occurrence</B> instance for the purpose of assigning property information such as a position
 * and orientation for the constituent. Property information is not provided by any of the entities of this part of
 * ISO 10303 but by using the appropriate capabilities defined in ISO 10303-42 [1], ISO 10303-43 [2], and ISO 10303-41.
 * The representation of a constituent occurrence in an assembly may be linked to mechanisms in ISO 10303-42 [1] and
 * ISO 10303-43 [2] by means of a product_definition entity defined in the product_definition_schema in ISO 10303-41.</SMALL>
 *
 * <SMALL><B>EXAMPLE</B> The position and orientation of a constituent with respect to its assembly would be
 * computed using a transformation defined in the <B>representation_schema</B> in ISO 10303-43 [2].</SMALL>
 *
 * <SMALL><B>NOTE 2</B> An application algorithm can produce an indented parts list for a product by sequentially
 * tracing through a structure of next_assembly_usage_occurrence instances. A similar algorithm can be used to
 * calculate the position and orientation of each occurrence of every constituent relative to its higher-level
 * assemblies within a BOM when used in conjunction with the property information constructs defined ISO 10303-41,
 * ISO 10303-42 [1], and ISO 10303-43 [2].</SMALL>
 *
 * <SMALL><B>NOTE 3</B> The number of constituents used in the assembly may be specified by composing a complex
 * instance of <B>next_assembly_usage_occurrence</B> and <B>quantified_assembly_component_usage</B>.</SMALL>
 *
 * <U>EXPRESS specification:</U>
 * \verbatim
  -- DIFF IN AP214
  -- DIFF IN AP203e2
  -- DIFF IN AP224
  -- DIFF IN AP232
  ENTITY next_assembly_usage_occurrence
     SUBTYPE OF (assembly_component_usage);
     DERIVE
        product_definition_occurrence_id : identifier := SELF\product_definition_relationship.related_product_definition\product_definition_occurrence.id;
     UNIQUE
        UR1 : SELF\assembly_component_usage.reference_designator, SELF\product_definition_relationship.relating_product_definition;
        UR2 : product_definition_occurrence_id, SELF\product_definition_relationship.relating_product_definition;
  END_ENTITY;
 \endverbatim
 *
 * <B>Attribute definitions:</B><BR>
 * <B>product_definition_occurrence_id</B>: a derived attribute that represents the id of the <B>product_definition_occurrence</B>
 * when it is referenced by the <B>related_product_definition</B> attribute.
 *
 * <B>Formal propositions:</B><BR>
 * <B>UR1:</B> The combination of <B>reference_designator</B> and <B>relating_product_definition</B> shall be unique
 * within a population of next_assembly_usage_occurrences.<BR>
 * <B>UR2:</B> The combination of <B>product_definition_occurrence_id</B> and <B>relating_product_definition</B> shall
 * be unique within a population of <B>next_assembly_usage_occurrences.</B>
 *
 * <A HREF="https://www.steptools.com/stds/stp_aim/html/t_next_assembly_usage_occurrence.html">Ссылка.</A>
 */
class next_assembly_usage_occurrence : public assembly_component_usage {
  public:
    /** \brief Конструктор */
    next_assembly_usage_occurrence(const identifier &Id, const label &Name, const text &Description,
      const product_definition_or_reference* Relating_product_definition,
      const product_definition_or_reference* Related_product_definition,
      const identifier &Reference_designator = "")
      : assembly_component_usage(Id, Name, Description, Relating_product_definition, Related_product_definition, Reference_designator) {
     //!!! derive
    }
};

}
