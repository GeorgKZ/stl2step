/**
 * \file
 *
 * \brief Файл с определениями функций классов, соответствующих ГОСТ Р ИСО 10303-43-2016.
 */

#include "stdafx.h"
#include "express.h"

namespace express {


  //STEP_TYPE_SELECT_CONSTRUCTOR(compound_item_definition, list_representation_item)
  //STEP_TYPE_SELECT_CONSTRUCTOR(compound_item_definition, set_representation_item)

  STEP_TYPE_SELECT_CONSTRUCTOR(founded_item_select, founded_item)
    STEP_TYPE_SELECT_CONSTRUCTOR(founded_item_select, representation_item)


    representation_relationship::representation_relationship(const std::string& Name, const std::string& Description, const representation* Rep1, const representation* Rep2) {
    name = new label(Name);
    description = new text(Description);
    rep_1 = Rep1;
    rep_2 = Rep2;
    add_attr_info(STEP_ATTR_LIST({
                                   {"name",         name},
                                   {"description",  description, true },
                                   {"rep_1",        rep_1},
                                   {"rep_2",        rep_2}
      }, this));
  }

  representation_relationship::~representation_relationship() {
    delete description;
    delete name;
  }

  representation::representation(const std::string& Name, const representation_context* Context_of_items) {
    name = new label(Name);
    items = new LIST<const representation_item>();
    context_of_items = Context_of_items;
    add_attr_info(STEP_ATTR_LIST({
                                   {"name", name},
                                   {"items", items},
                                   {"context_of_items", context_of_items},
      }, this));
  }

  representation::~representation() {
    delete items;
    delete name;
  }

  //  STEP_TYPE_SELECT_CONSTRUCTOR(transformation, functionally_defined_transformation)
  STEP_TYPE_SELECT_CONSTRUCTOR(transformation, item_defined_transformation)


    definitional_representation::definitional_representation(const std::string& Name, const representation_context* Context) :
    representation(Name, Context) {
  }

  // FUNCTION get_id_value
  identifier definitional_representation::get_id_value(void) {
    return "";
  }

  // FUNCTION get_description_value
  text definitional_representation::get_description_value(void) {
    return "";
  }


  // Конструктор
  global_uncertainty_assigned_context::global_uncertainty_assigned_context(const std::string& identifier, const std::string& type) :
    representation_context(identifier, type) {
    // Информация об аргументах этого класса
    add_attr_info(STEP_ATTR_LIST({ {"uncertainty", &uncertainty} }, this));
  }

  // Дополнить массив
  void global_uncertainty_assigned_context::add_uncert(const uncertainty_measure_with_unit* x) {
    uncertainty.push_back(x);
  }


  item_defined_transformation::item_defined_transformation(
    const std::string& Name,
    const representation_item* Transform_item_1,
    const representation_item* Transform_item_2,
    const std::string& Description)
    : transform_item_1(Transform_item_1), transform_item_2(Transform_item_2) {
    name = new label(Name);
    description = new text(Description);
    add_attr_info(STEP_ATTR_LIST({
                                   {"name",             name,             false},
                                   {"description",      description,      true},
                                   {"transform_item_1", transform_item_1, false},
                                   {"transform_item_2", transform_item_2, false}
      }, this));
  }

  item_defined_transformation::~item_defined_transformation() {
    delete description;
    delete name;
  }

  STEP_TYPE_SELECT_CONSTRUCTOR(representation_or_representation_reference, representation)
  STEP_TYPE_SELECT_CONSTRUCTOR(representation_or_representation_reference, representation_reference)


  representation_item::representation_item(const std::string& Name) {
    name = new label(Name);
    add_attr_info(STEP_ATTR_LIST({
                                   {"name", name}
      }, this));
  }

  representation_item::~representation_item() {
    delete name;
  }


  representation_context::representation_context(const std::string& Identifier, const std::string& Type) {
    context_identifier = new identifier(Identifier);
    context_type = new text(Type);
    add_attr_info(STEP_ATTR_LIST({ {"context_identifier", context_identifier},
                                   {"context_type",       context_type}
      }, this));
  }

  representation_context::~representation_context() {
    delete context_type;
    delete context_identifier;
  }


}
