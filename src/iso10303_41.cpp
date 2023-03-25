/**
 * \file
 *
 * \brief Файл с определениями функций классов, соответствующих ГОСТ Р ИСО 10303-41-1999.
 */

#ifndef TESTONLY

#include "stdafx.h"
#include "express.h"

namespace express {

  /* ENTITY application_context (2.2.3.1) */

  application_context::application_context(const std::string& Application) {
    application = new label(Application);
    add_attr_info(STEP_ATTR_LIST({
                                   {"application", application}
      }, this));
  }

  application_context::~application_context() {
    delete application;
  }

  /* ENTITY shape_representation_relationship */

  shape_representation_relationship::shape_representation_relationship(
    const std::string& Name,
    const std::string& Description,
    const representation* Rep1,
    const representation* Rep2)
    : representation_relationship(Name, Description, Rep1, Rep2) {
    /* Сохранить информацию об аргументах */
    add_attr_info(STEP_ATTR_LIST({ {} }, this));
  }

  shape_representation_relationship:: ~shape_representation_relationship() {
  }

  /* ENTITY context_dependent_shape_representation */

  context_dependent_shape_representation::context_dependent_shape_representation(
    const shape_representation_relationship* RepRelation,
    const product_definition_shape* ProdRelation) {
    representation_relation = RepRelation;
    represented_product_relation = ProdRelation;
    /* Сохранить информацию об аргументах */
    add_attr_info(STEP_ATTR_LIST({
                                   {"representation_relation", representation_relation},
                                   {"represented_product_relation", represented_product_relation},
      }, this));
  }

  context_dependent_shape_representation::~context_dependent_shape_representation() {
  }








  /* */

  edge::edge(const std::string& Name, const vertex* Edge_start, const vertex* Edge_end) :
    representation_item(Name),
    topological_representation_item(Name) {
    edge_start = Edge_start;
    edge_end = Edge_end;
    add_attr_info(STEP_ATTR_LIST({
      {"edge_start", edge_start},
      {"edge_end", edge_end},
      }, this));

  }

  edge::~edge() {
  }
#if 0
  int edge::compare(const edge& e2) const {
    const vertex* vs1 = edge_start;
    const vertex* ve1 = edge_end;
    const vertex* vs2 = e2.edge_start;
    const vertex* ve2 = e2.edge_end;
    if (vs1 != nullptr && ve1 != nullptr && vs2 != nullptr && ve2 != nullptr) {
      if (*vs1 == *vs2 && *ve1 == *ve2) {
        return 1;
      }
      else if (*vs1 == *ve2 && *ve1 == *vs2) {
        return -1;
      }
    }
    return 0;
  }
#endif

  named_unit::named_unit(const dimensional_exponents& Dimensions) : dimensions(&Dimensions) {
    // Информация об аргументах
    add_attr_info(STEP_ATTR_LIST({ {"dimensions", dimensions} }, this));
  }

  /** \brief Деструктор */
  named_unit::~named_unit() {
  }


  STEP_TYPE_SELECT_CONSTRUCTOR(source_item, identifier)
  STEP_TYPE_SELECT_CONSTRUCTOR(source_item, message)

  //  STEP_TYPE_SELECT_CONSTRUCTOR(represented_definition, general_property)
  STEP_TYPE_SELECT_CONSTRUCTOR(represented_definition, property_definition)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(represented_definition, property_definition_relationship)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(represented_definition, shape_aspect)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(represented_definition, shape_aspect_relationship)

  //  STEP_TYPE_SELECT_CONSTRUCTOR(characterized_item, dimensional_size)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(characterized_item, geometric_tolerance)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(characterized_item, item_identified_representation_usage)

  STEP_TYPE_SELECT_CONSTRUCTOR(characterized_definition, characterized_item)
  STEP_TYPE_SELECT_CONSTRUCTOR(characterized_definition, characterized_object)
  STEP_TYPE_SELECT_CONSTRUCTOR(characterized_definition, characterized_product_definition)
  STEP_TYPE_SELECT_CONSTRUCTOR(characterized_definition, shape_definition)

  STEP_TYPE_SELECT_CONSTRUCTOR(characterized_product_definition, product_definition)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(characterized_product_definition, product_definition_occurrence)
  STEP_TYPE_SELECT_CONSTRUCTOR(characterized_product_definition, product_definition_relationship)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(characterized_product_definition, product_definition_relationship_relationship)

  STEP_TYPE_SELECT_CONSTRUCTOR(shape_definition, product_definition_shape)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(shape_definition, shape_aspect)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(shape_definition, shape_aspect_relationship)

  //  STEP_TYPE_SELECT_CONSTRUCTOR(id_attribute_select, action)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(id_attribute_select, address)

  id_attribute_select::id_attribute_select(const application_context* t) : SELECT(t) {}

  //  STEP_TYPE_SELECT_CONSTRUCTOR(id_attribute_select, dimensional_size)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(id_attribute_select, geometric_tolerance)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(id_attribute_select, group)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(id_attribute_select, organizational_project)

  STEP_TYPE_SELECT_CONSTRUCTOR(id_attribute_select, product_category)
  STEP_TYPE_SELECT_CONSTRUCTOR(id_attribute_select, property_definition)
  STEP_TYPE_SELECT_CONSTRUCTOR(id_attribute_select, representation)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(id_attribute_select, shape_aspect)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(id_attribute_select, shape_aspect_relationship)
  STEP_TYPE_SELECT_CONSTRUCTOR(id_attribute_select, topological_representation_item)

  STEP_TYPE_SELECT_CONSTRUCTOR(product_definition_or_reference, generic_product_definition_reference)
  STEP_TYPE_SELECT_CONSTRUCTOR(product_definition_or_reference, product_definition)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(product_definition_or_reference,sproduct_definition_occurrence)

  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, absorbed_dose_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, acceleration_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, amount_of_substance_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, area_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, capacitance_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, celsius_temperature_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, conductance_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, context_dependent_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, count_measure)
  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, descriptive_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, dose_equivalent_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, electric_charge_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, electric_current_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, electric_potential_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, energy_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, force_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, frequency_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, illuminance_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, inductance_measure)
  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, length_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, luminous_flux_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, luminous_intensity_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, magnetic_flux_density_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, magnetic_flux_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, mass_measure)
  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, non_negative_length_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, numeric_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, parameter_value)
  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, plane_angle_measure)
  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, positive_length_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, positive_plane_angle_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, positive_ratio_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, power_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, pressure_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, radioactivity_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, ratio_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, resistance_measure)
  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, solid_angle_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, thermodynamic_temperature_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, time_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, velocity_measure)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(measure_value, volume_measure)

 /* 4.14.3.22 */

  unit::unit(const derived_unit* t) : SELECT(t) {
  }

  unit::unit(const named_unit* t) : SELECT(t) {
  }

  unit::operator const derived_unit& () const {
    return *dynamic_cast<const derived_unit*>(get_value());
  }

  unit::operator const named_unit& () const {
    return *dynamic_cast<const named_unit*>(get_value());
  }


  /*  */

  application_protocol_definition::application_protocol_definition(const std::string& Status, const std::string& Name, integer_type Year, const application_context* Application) {
  status = new label(Status);
  application_interpreted_model_schema_name = new label(Name);
  application_protocol_year = new year_number(Year);
  application = Application;
  add_attr_info(STEP_ATTR_LIST({
                                 {"status",                                     status},
                                 {"application_interpreted_model_schema_name",  application_interpreted_model_schema_name},
                                 {"application_protocol_year",                  application_protocol_year},
                                 {"application",                                application}
    }, this));
  }

  application_protocol_definition::~application_protocol_definition() {
    delete status;
    delete application_interpreted_model_schema_name;
    delete application_protocol_year;
  }

  application_context_element::application_context_element(const std::string& Name, const application_context* Frame) {
    name = new label(Name);
    frame_of_reference = Frame;
    add_attr_info(STEP_ATTR_LIST({
                                   {"name",               name},
                                   {"frame_of_reference", frame_of_reference}
      }, this));
  }

  /** \brief Деструктор. */
  application_context_element::~application_context_element() {
    delete name;
  }

  product_context::product_context(const std::string& Name, const application_context* Frame, const std::string& Type) :
    application_context_element(Name, Frame) {
    discipline_type = new label(Type);
    add_attr_info(STEP_ATTR_LIST({
                                   {"discipline_type", discipline_type}
      }, this));
  }

  product_context::~product_context() {
    delete discipline_type;
  }

  product_definition_context::product_definition_context(const std::string& Name, application_context* Frame, const std::string& Stage) :
    application_context_element(Name, Frame) {
    life_cycle_stage = new label(Stage);
    add_attr_info(STEP_ATTR_LIST({
                                   {"life_cycle_stage", life_cycle_stage}
      }, this));
  }

  product_definition_context::~product_definition_context() {
    delete life_cycle_stage;
  }

  product_concept_context::product_concept_context(const std::string& Name, application_context* Frame, const std::string& Type) :
    application_context_element(Name, Frame) {
    market_segment_type = new label(Type);
    add_attr_info(STEP_ATTR_LIST({
                                   {"market_segment_type", market_segment_type}
      }, this));
  }

  product_concept_context::~product_concept_context() {
    delete market_segment_type;
  }

  library_context::library_context(const std::string& Name, const application_context* Frame, const std::string& Reference) :
    application_context_element(Name, Frame) {
    library_reference = new label(Reference);
    add_attr_info(STEP_ATTR_LIST({
                                   {"library_reference", library_reference}
      }, this));
  }

  library_context::~library_context() {
    delete library_reference;
  }

  /* 2.3.4.1 */

  product::product(const std::string& Id, const std::string& Name, const std::string& Description) :
    id(Id),
    name(Name),
    description(Description),
    frame_of_reference(1,INTEGER()) {
    add_attr_info(STEP_ATTR_LIST({
                                   {"id",                 &id},
                                   {"name",               &name},
                                   {"description",        &description, true},
                                   {"frame_of_reference", &frame_of_reference},
                                 }, this));
  }

//  void product::add_frame(const product_context* x) {
//    *frame_of_reference += x;
//  }

  /* 2.3.4.2 */

  product_category::product_category(const std::string& Name, const std::string& Description) {
    name = new label(Name);
    description = new text(Description);
    add_attr_info(STEP_ATTR_LIST({
                                   {"name", name},
                                   {"description", description, true},
      }, this));
  }

  product_category::~product_category() {
    delete description;
    delete name;
  }

  /* 2.3.4.3 */

  product_related_product_category::product_related_product_category(const std::string& Name, const std::string& Description) :
    product_category(Name, Description),
    products(1,INTEGER()) {
    add_attr_info(STEP_ATTR_LIST({
                                   {"products", &products}
      }, this));
  }

//  void product_related_product_category::add_product(const product* x) {
//    *products += x;
//  }


  /* 2.3.4.4 */

  product_category_relationship::product_category_relationship(const std::string& Name, const std::string& Description, const product_category* Category, const product_category* SubCategory) {
    name = new label(Name);
    description = new text(Description);
    category = Category;
    sub_category = SubCategory;
    add_attr_info(STEP_ATTR_LIST({
                                   {"name",         name},
                                   {"description",  description},
                                   {"category",     category},
                                   {"sub_category", sub_category},
      }, this));
  }

  product_category_relationship::~product_category_relationship() {
    delete description;
    delete name;
  }

  product_definition_formation::product_definition_formation(const std::string& Id, const std::string& Description, const product* Of_product) {
    id = new identifier(Id);
    description = new text(Description);
    of_product = Of_product;
    /* Сохранить информацию об аргументах */
    add_attr_info(STEP_ATTR_LIST({
                                   {"id",            id},
                                   {"description",   description,       true},
                                   {"of_product",    of_product}
      }, this));
  }

  product_definition_formation::~product_definition_formation() {
    delete description;
    delete id;
  }

  product_definition::product_definition(const std::string& Id, const std::string& Description,
    const product_definition_formation* Formation,
    const product_definition_context* Frame_of_reference) {
    id = new identifier(Id);
    description = new text(Description);
    formation = Formation,
      frame_of_reference = Frame_of_reference;
    /* Сохранить информацию об аргументах */
    add_attr_info(STEP_ATTR_LIST({ {"id",            id},
                                   {"description",   description,       true },
                                   {"formation",     formation},
                                   {"description",   frame_of_reference}
      }, this));
    /* Атрибут name вычисляется при помощи функции get_name_value() */
    // set_attr_derived("name");

  }

  product_definition::~product_definition() {
    delete description;
    delete id;
  }


  product_definition_relationship::product_definition_relationship(identifier Id, label Name, text Description,
    const product_definition_or_reference* Relating_product_definition,
    const product_definition_or_reference* Related_product_definition) {
    id = new identifier(Id);
    name = new label(Name);
    description = new text(Description);
    relating_product_definition = Relating_product_definition;
    related_product_definition = Related_product_definition;
    // Информация об аргументах
    add_attr_info(STEP_ATTR_LIST({ {"id",                            id},
                                   {"name",                          name},
                                   {"description",                   description},
                                   {"relating_product_definition",   relating_product_definition},
                                   {"related_product_definition",    related_product_definition}
      }, this));
  }

  product_definition_relationship::~product_definition_relationship() {
    delete description;
    delete name;
    delete id;

  }


  characterized_object::characterized_object(const std::string& Name, const std::string& Description) {
    name = new label(Name);
    description = new text(Description);
    /* Сохранить информацию об аргументах */
    add_attr_info(STEP_ATTR_LIST({ {"name",          name},
                                   {"description",   description, true }
      }, this));
  }

  characterized_object::~characterized_object() {
    delete description;
    delete name;
  }


  property_definition::property_definition(const std::string& Name, const std::string& Description, const characterized_definition* Definition) {
    name = new label(Name);
    description = new text(Description);
    definition = Definition;
    /* Сохранить информацию об аргументах */
    add_attr_info(STEP_ATTR_LIST({
                                   {"name",          name},
                                   {"description",   description, true },
                                   {"definition",    definition},
      }, this));
  }

  property_definition::~property_definition() {
    delete description;
    delete name;
  }

  /* 2.4.4.3 */

  product_definition_shape::product_definition_shape(const std::string& Name, const std::string& Description, const characterized_definition* Definition)
    : property_definition(Name, Description, Definition) {
    add_attr_info(STEP_ATTR_LIST({ {} }, this));

  }

  shape_representation::shape_representation(const std::string& Name, const representation_context* Context_of_items) : representation(Name, Context_of_items) {
    add_attr_info(STEP_ATTR_LIST({ {} }, this));
  }

  property_definition_representation::property_definition_representation(const represented_definition* Definition, const representation* Used_representation)
    : definition(Definition), used_representation(Used_representation) {
    // Информация об аргументах
    add_attr_info(STEP_ATTR_LIST({ {"definition",          definition},
                                    {"used_representation", used_representation}
      }, this));
  }

  property_definition_representation::~property_definition_representation() {
  }


  pre_defined_item::pre_defined_item(const std::string& Name) {
    name = new label(Name);
    add_attr_info(STEP_ATTR_LIST({ {"name", name}
      }, this));
  }

  pre_defined_item::~pre_defined_item() {
    delete name;
  }


  si_unit::si_unit(const si_unit_name& Name, const si_prefix& Prefix) : named_unit(dimensions_for_si_unit(Name)) {
    prefix = new si_prefix(Prefix);
    name = new si_unit_name(Name);

    //!!!   NOT (  ('MASS_UNIT' IN TYPEOF(SELF)) AND (SIZEOF(USEDIN(SELF, 'DERIVED_UNIT_ELEMENT.UNIT')) > 0)  )    OR (prefix = si_prefix.kilo);

    /** Атрибут <B>\ref dimensions</B> вычисляется при помощи функции <B>\ref dimensions_for_si_unit()</B> */
    set_attr_derived("dimensions");
    /** Сохраненить информацию об аргументах этого класса */
    add_attr_info(STEP_ATTR_LIST({ {"prefix", prefix, true},
                                   {"name",    name}
      }, this));
  }

  si_unit::~si_unit() {
    delete name;
    delete prefix;
  }

  /* ENTITY conversion_based_unit (4.14.4.3) */

  conversion_based_unit::conversion_based_unit(const label& Name, measure_with_unit* Conversion_factor) :
    named_unit(derive_dimensional_exponents(*Conversion_factor->get_unit_component())) {
    name = new label(Name);
    conversion_factor = Conversion_factor;
    add_attr_info(STEP_ATTR_LIST({ {"name", name}
      }, this));
  }

  conversion_based_unit::~conversion_based_unit() {
    delete name;
  }

  /* ENTITY context_dependent_unit (4.14.4.4) */

  context_dependent_unit::context_dependent_unit(const label& Name, const dimensional_exponents* Dimensions) : named_unit(*Dimensions) {
    name = new label(Name);
    add_attr_info(STEP_ATTR_LIST({ {"name", name}
      }, this));
  }

  context_dependent_unit::~context_dependent_unit() {
    delete name;
  }

  /* ENTITY length_unit (4.14.4.5) */

  length_unit::length_unit() :
    named_unit(dimensional_exponents(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)) {
    // Информация об аргументах этого класса
    add_attr_info(STEP_ATTR_LIST({ { } }, this));
  }


  length_unit::~length_unit() {
  }

  /* ENTITY mass_unit (4.14.4.6) */

  mass_unit::mass_unit() :
    named_unit(dimensional_exponents(0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0)) {
    // Информация об аргументах этого класса
    add_attr_info(STEP_ATTR_LIST({ { } }, this));
  }


  mass_unit::~mass_unit() {
  }

  /* ENTITY mass_unit (4.14.4.7) */

  time_unit::time_unit() :
    named_unit(dimensional_exponents(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0)) {
    // Информация об аргументах этого класса
    add_attr_info(STEP_ATTR_LIST({ { } }, this));
  }

  time_unit::~time_unit() {
  }


  /* ENTITY electric_current_unit (4.14.4.8) */

  /* ENTITY thermodynamic_temperature_unit (4.14.4.9) */

  /* ENTITY amount_of_substance_unit (4.14.4.10) */

  /* ENTITY luminous_intensity_unit (4.14.4.11) */

  /* ENTITY plane_angle_unit (4.14.4.12) */

  plane_angle_unit::plane_angle_unit() : named_unit(dimensional_exponents(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)) {
    // Информация об аргументах этого класса
    add_attr_info(STEP_ATTR_LIST({ { } }, this));
  }

  plane_angle_unit::~plane_angle_unit() {
  }


  /* ENTITY solid_angle_unit (4.14.4.13) */

  solid_angle_unit::solid_angle_unit() : named_unit(dimensional_exponents(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)) {
    // Информация об аргументах этого класса
    add_attr_info(STEP_ATTR_LIST({ { } }, this));
  }

  solid_angle_unit::~solid_angle_unit() {
  }


  /* ENTITY area_unit (4.14.4.14) */

  /* ENTITY volume_unit (4.14.4.15) */

  /* ENTITY ratio_unit (4.14.4.16) */

  ratio_unit::ratio_unit() : named_unit(dimensional_exponents(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)) {
    // Информация об аргументах этого класса
    add_attr_info(STEP_ATTR_LIST({ { } }, this));
  }

  ratio_unit::~ratio_unit() {
  }

  /* ENTITY dimensional_exponents 4.14.4.17) */

  dimensional_exponents::dimensional_exponents(double Length, double Mass, double Time, double Current, double Temp, double Amount, double Lum) :
    length_exponent(Length),
    mass_exponent(Mass),
    time_exponent(Time),
    electric_current_exponent(Current),
    thermodynamic_temperature_exponent(Temp),
    amount_of_substance_exponent(Amount),
    luminous_intensity_exponent(Lum) {
  }

  dimensional_exponents::~dimensional_exponents() {
  }

  REAL dimensional_exponents::get_length_exponent() const {
    return length_exponent;
  }
  REAL dimensional_exponents::get_mass_exponent() const {
    return mass_exponent;
  }
  REAL dimensional_exponents::get_time_exponent() const {
    return time_exponent;
  }
  REAL dimensional_exponents::get_electric_current_exponent() const {
    return electric_current_exponent;
  }
  REAL dimensional_exponents::get_thermodynamic_temperature_exponent() const {
    return thermodynamic_temperature_exponent;
  }
  REAL dimensional_exponents::get_amount_of_substance_exponent() const {
    return amount_of_substance_exponent;
  }
  REAL dimensional_exponents::get_luminous_intensity_exponent() const {
    return luminous_intensity_exponent;
  }

  void dimensional_exponents::set_length_exponent(const REAL& x) {
    length_exponent = x;
  }
  void dimensional_exponents::set_mass_exponent(const REAL& x) {
    mass_exponent = x;
  }
  void dimensional_exponents::set_time_exponent(const REAL& x) {
    time_exponent = x;
  }
  void dimensional_exponents::set_electric_current_exponent(const REAL& x) {
    electric_current_exponent = x;
  }
  void dimensional_exponents::set_thermodynamic_temperature_exponent(const REAL& x) {
    thermodynamic_temperature_exponent = x;
  }
  void dimensional_exponents::set_amount_of_substance_exponent(const REAL& x) {
    amount_of_substance_exponent = x;
  }
  void dimensional_exponents::set_luminous_intensity_exponent(const REAL& x) {
    luminous_intensity_exponent = x;
  }

  bool dimensional_exponents::operator==(const dimensional_exponents& x) const {
    if (length_exponent != x.length_exponent) return false;
    if (mass_exponent != x.mass_exponent) return false;
    if (time_exponent != x.time_exponent) return false;
    if (electric_current_exponent != x.electric_current_exponent) return false;
    if (thermodynamic_temperature_exponent != x.thermodynamic_temperature_exponent) return false;
    if (amount_of_substance_exponent != x.amount_of_substance_exponent) return false;
    if (luminous_intensity_exponent != x.luminous_intensity_exponent) return false;
    return true;
  }

  bool dimensional_exponents::operator!=(const dimensional_exponents& x) const {
    return !(*this == x);
  }


  /* ENTITY derived_unit_element (4.14.4.18) */

  derived_unit_element::derived_unit_element() : GENERIC_ENTITY(false) {
    unit = nullptr;
    exponent = nullptr;
    add_attr_info(STEP_ATTR_LIST({
                                   {"unit", unit},
                                   {"exponent", exponent},
      }, this));
  }

  derived_unit_element::derived_unit_element(const named_unit& Unit, const REAL& Exponent) {
    unit = new named_unit(Unit);
    exponent = new REAL(Exponent);
    add_attr_info(STEP_ATTR_LIST({
                                   {"unit", unit},
                                   {"exponent", exponent},
      }, this));
  }

  derived_unit_element::~derived_unit_element() {
    delete exponent;
    delete unit;
  }

  const named_unit* derived_unit_element::get_unit() const {
    return unit;
  }


  const REAL* derived_unit_element::get_exponent() const {
    return exponent;
  }


  /* 4.14.4.19 */

  derived_unit::derived_unit(const derived_unit_element* Element) :
    elements(1,INTEGER()) {
    elements += Element;
    add_attr_info(STEP_ATTR_LIST({
                                   {"elements", &elements}
                                 }, this));
  }

//  void derived_unit::add_element(const derived_unit_element* Element) {
//    *elements += Element;
//  }

//  const derived_unit_element* derived_unit::get_element(const INTEGER& i) const {
//    return (*elements)[i];
//  }

//  /** \brief Вернуть количество единиц */
//  INTEGER derived_unit::get_elements_size() const {
//    return SIZEOF<const derived_unit_element>(*elements);
//  }





  /* FUNCTION dimensions_for_si_unit (4.14.5.1) */

  dimensional_exponents dimensions_for_si_unit(const si_unit_name& n) {
    dimensional_exponents de;
    switch (n) {
    case si_unit_name::metre:          de = dimensional_exponents( 1.0,  0.0,  0.0,  0.0, 0.0, 0.0, 0.0); break;
    case si_unit_name::gram:           de = dimensional_exponents( 0.0,  1.0,  0.0,  0.0, 0.0, 0.0, 0.0); break;
    case si_unit_name::second:         de = dimensional_exponents( 0.0,  0.0,  1.0,  0.0, 0.0, 0.0, 0.0); break;
    case si_unit_name::ampere:         de = dimensional_exponents( 0.0,  0.0,  0.0,  1.0, 0.0, 0.0, 0.0); break;
    case si_unit_name::mole:           de = dimensional_exponents( 0.0,  0.0,  0.0,  0.0, 0.0, 1.0, 0.0); break;
    case si_unit_name::radian:
    case si_unit_name::steradian:      de = dimensional_exponents( 0.0,  0.0,  0.0,  0.0, 0.0, 0.0, 0.0); break;
    case si_unit_name::newton:         de = dimensional_exponents( 1.0,  1.0, -2.0,  0.0, 0.0, 0.0, 0.0); break;
    case si_unit_name::ppascal:        de = dimensional_exponents(-1.0,  1.0, -2.0,  0.0, 0.0, 0.0, 0.0); break;
    case si_unit_name::joule:          de = dimensional_exponents( 2.0,  1.0, -2.0,  0.0, 0.0, 0.0, 0.0); break;
    case si_unit_name::watt:           de = dimensional_exponents( 2.0,  1.0, -3.0,  0.0, 0.0, 0.0, 0.0); break;
    case si_unit_name::coulomb:        de = dimensional_exponents( 0.0,  0.0,  1.0,  1.0, 0.0, 0.0, 0.0); break;
    case si_unit_name::volt:           de = dimensional_exponents( 2.0,  1.0, -3.0, -1.0, 0.0, 0.0, 0.0); break;
    case si_unit_name::farad:          de = dimensional_exponents(-2.0, -1.0,  4.0,  2.0, 0.0, 0.0, 0.0); break;
    case si_unit_name::ohm:            de = dimensional_exponents( 2.0,  1.0, -3.0, -2.0, 0.0, 0.0, 0.0); break;
    case si_unit_name::siemens:        de = dimensional_exponents(-2.0, -1.0,  3.0,  2.0, 0.0, 0.0, 0.0); break;
    case si_unit_name::weber:          de = dimensional_exponents( 2.0,  1.0, -2.0, -1.0, 0.0, 0.0, 0.0); break;
    case si_unit_name::tesla:          de = dimensional_exponents( 0.0,  1.0, -2.0, -1.0, 0.0, 0.0, 0.0); break;
    case si_unit_name::henry:          de = dimensional_exponents( 2.0,  1.0, -2.0, -2.0, 0.0, 0.0, 0.0); break;
    case si_unit_name::kelvin:
    case si_unit_name::degree_celsius: de = dimensional_exponents( 0.0,  0.0,  0.0,  0.0, 1.0, 0.0, 0.0); break;
    case si_unit_name::candela:
    case si_unit_name::lumen:          de = dimensional_exponents( 0.0,  0.0,  0.0,  0.0, 0.0, 0.0, 1.0); break;
    case si_unit_name::lux:            de = dimensional_exponents(-2.0,  0.0,  0.0,  0.0, 0.0, 0.0, 1.0); break;
    case si_unit_name::becquerel:
    case si_unit_name::hertz:          de = dimensional_exponents( 0.0,  0.0, -1.0,  0.0, 0.0, 0.0, 0.0); break;
    case si_unit_name::gray:
    case si_unit_name::sievert:        de = dimensional_exponents( 2.0,  0.0, -2.0,  0.0, 0.0, 0.0, 0.0); break;
    }
    return de;
  }

  /* 4.14.5.2 */

  dimensional_exponents derive_dimensional_exponents(const unit& x) {
    if (x.is_type_name("derived_unit")) {
      const derived_unit& du = x;
      dimensional_exponents result(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
      for (INTEGER i = LOINDEX(du.elements); i.get_value() <= HIINDEX(du.elements).get_value(); i = i + 1) {
        const auto& exponent = *du.elements[i]->exponent;
        const auto& dimensions = *du.elements[i]->get_unit()->get_dimensions();
        result.set_length_exponent(result.get_length_exponent() + exponent * dimensions.get_length_exponent());
        result.set_mass_exponent(result.get_mass_exponent() + exponent * dimensions.get_mass_exponent());
        result.set_time_exponent(result.get_time_exponent() + exponent * dimensions.get_time_exponent());
        result.set_electric_current_exponent(result.get_electric_current_exponent() + exponent * dimensions.get_electric_current_exponent());
        result.set_thermodynamic_temperature_exponent(result.get_thermodynamic_temperature_exponent() + exponent * dimensions.get_thermodynamic_temperature_exponent());
        result.set_amount_of_substance_exponent(result.get_amount_of_substance_exponent() + exponent * dimensions.get_amount_of_substance_exponent());
        result.set_luminous_intensity_exponent(result.get_luminous_intensity_exponent() + exponent * dimensions.get_luminous_intensity_exponent());
      }
      return result;
    }
    else {
      const named_unit& nu = x;
      return dimensional_exponents(*nu.dimensions);

    }
  }

  /* FUNCTION valid_units (4.14.5.3) */

  bool valid_units(const measure_with_unit& m) {
    dimensional_exponents de(derive_dimensional_exponents(*m.get_unit_component()));
    if (m.is_type_name("length_measure") &&                    de != dimensional_exponents( 1.0,  0.0,  0.0,  0.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("mass_measure") &&                      de != dimensional_exponents( 0.0,  1.0,  0.0,  0.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("time_measure") &&                      de != dimensional_exponents( 0.0,  0.0,  1.0,  0.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("electric_current_measure") &&          de != dimensional_exponents( 0.0,  0.0,  0.0,  1.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("thermodynamic_temperature_measure") && de != dimensional_exponents( 0.0,  0.0,  0.0,  0.0, 1.0, 0.0, 0.0)) return false;
    if (m.is_type_name("celsius_temperature_measure") &&       de != dimensional_exponents( 0.0,  0.0,  0.0,  0.0, 1.0, 0.0, 0.0)) return false;
    if (m.is_type_name("amount_of_substance_measure") &&       de != dimensional_exponents( 0.0,  0.0,  0.0,  0.0, 0.0, 1.0, 0.0)) return false;
    if (m.is_type_name("luminous_intensity_measure") &&        de != dimensional_exponents( 0.0,  0.0,  0.0,  0.0, 0.0, 0.0, 1.0)) return false;
    if (m.is_type_name("plane_angle_measure") &&               de != dimensional_exponents( 0.0,  0.0,  0.0,  0.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("solid_angle_measure") &&               de != dimensional_exponents( 0.0,  0.0,  0.0,  0.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("area_measure") &&                      de != dimensional_exponents( 2.0,  0.0,  0.0,  0.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("volume_measure") &&                    de != dimensional_exponents( 3.0,  0.0,  0.0,  0.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("ratio_measure") &&                     de != dimensional_exponents( 0.0,  0.0,  0.0,  0.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("positive_length_measure") &&           de != dimensional_exponents( 1.0,  0.0,  0.0,  0.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("positive_plane_angle_measure") &&      de != dimensional_exponents( 0.0,  0.0,  0.0,  0.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("acceleration_measure") &&              de != dimensional_exponents( 1.0,  0.0, -2.0,  0.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("capacitance_measure") &&               de != dimensional_exponents(-2.0, -1.0,  4.0,  2.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("electric_charge_measure") &&           de != dimensional_exponents( 0.0,  0.0,  1.0,  1.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("conductance_measure") &&               de != dimensional_exponents(-2.0, -1.0,  3.0,  2.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("electric_potential_measure") &&        de != dimensional_exponents( 2.0,  1.0, -3.0, -1.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("energy_measure") &&                    de != dimensional_exponents( 2.0,  1.0, -2.0,  0.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("force_measure") &&                     de != dimensional_exponents( 1.0,  1.0, -2.0,  0.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("frequency_measure") &&                 de != dimensional_exponents( 0.0,  0.0, -1.0,  0.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("illuminance_measure") &&               de != dimensional_exponents(-2.0,  0.0,  0.0,  0.0, 0.0, 0.0, 1.0)) return false;
    if (m.is_type_name("inductance_measure") &&                de != dimensional_exponents( 2.0,  1.0, -2.0, -2.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("luminous_flux_measure") &&             de != dimensional_exponents( 0.0,  0.0,  0.0,  0.0, 0.0, 0.0, 1.0)) return false;
    if (m.is_type_name("magnetic_flux_measure") &&             de != dimensional_exponents( 2.0,  1.0, -2.0, -1.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("magnetic_flux_density_measure") &&     de != dimensional_exponents( 0.0,  1.0, -2.0, -1.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("power_measure") &&                     de != dimensional_exponents( 2.0,  1.0, -3.0,  0.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("pressure_measure") &&                  de != dimensional_exponents(-1.0,  1.0, -2.0,  0.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("resistance_measure") &&                de != dimensional_exponents( 2.0,  1.0, -3.0, -2.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("velocity_measure") &&                  de != dimensional_exponents( 1.0,  0.0, -1.0,  0.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("radioactivity_measure") &&             de != dimensional_exponents( 0.0,  0.0, -1.0,  0.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("absorbed_dose_measure") &&             de != dimensional_exponents( 2.0,  0.0, -2.0,  0.0, 0.0, 0.0, 0.0)) return false;
    if (m.is_type_name("dose_equivalent_measure") &&           de != dimensional_exponents( 2.0,  0.0, -2.0,  0.0, 0.0, 0.0, 0.0)) return false;
    return true;
  }
}

#endif