/**
 * \file
 *
 * \brief Файл с определениями функций классов, соответствующих ГОСТ Р ИСО 10303-43-2016.
 */

#ifndef TESTONLY

#include "stdafx.h"
#include "express.h"

namespace express {

  /* */

  //STEP_TYPE_SELECT_CONSTRUCTOR(compound_item_definition, list_representation_item)
  //STEP_TYPE_SELECT_CONSTRUCTOR(compound_item_definition, set_representation_item)

  /* 4.4.5 */

  STEP_TYPE_SELECT_CONSTRUCTOR(founded_item_select, founded_item)
  STEP_TYPE_SELECT_CONSTRUCTOR(founded_item_select, representation_item)


  representation_relationship::representation_relationship(const std::string& Name, const std::string& Description, const representation* Rep1, const representation* Rep2) :
    name(Name), description(Description) {
    rep_1 = Rep1;
    rep_2 = Rep2;
    add_attr_info(STEP_ATTR_LIST({
                                   {"name",         &name},
                                   {"description",  &description, true },
                                   {"rep_1",        rep_1},
                                   {"rep_2",        rep_2}
      }, this));
  }


  /* 4.4.13 */

  representation::representation() : GENERIC_ENTITY(false),
    name(), items(1,INTEGER()) {
    context_of_items = nullptr;
    add_attr_info(STEP_ATTR_LIST({
                                   {"name",            &name},
                                   {"items",           &items},
                                   {"context_of_items", context_of_items},
      }, this));
  }

  representation::representation(const std::string& Name, const representation_context* Context_of_items) :
    name(Name), items(1,INTEGER()) {
    context_of_items = Context_of_items;
    add_attr_info(STEP_ATTR_LIST({
                                   {"name",            &name},
                                   {"items",           &items},
                                   {"context_of_items", context_of_items},
      }, this));
  }


  /* */

  //  STEP_TYPE_SELECT_CONSTRUCTOR(transformation, functionally_defined_transformation)
  STEP_TYPE_SELECT_CONSTRUCTOR(transformation, item_defined_transformation)


    definitional_representation::definitional_representation(const std::string& Name, const representation_context* Context) :
    representation(Name, Context) {
  }

  /* 4.4.9 */

  global_uncertainty_assigned_context::global_uncertainty_assigned_context(const std::string& identifier, const std::string& type) :
    representation_context(identifier, type) {
    // Информация об аргументах этого класса
    add_attr_info(STEP_ATTR_LIST({ {"uncertainty", &uncertainty} }, this));
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
                                   {"name",             name},
                                   {"description",      description, true},
                                   {"transform_item_1", transform_item_1},
                                   {"transform_item_2", transform_item_2}
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

  /* 4.4.14 */

  representation_context::representation_context() : GENERIC_ENTITY(false) {
  }

  representation_context::representation_context(const std::string& Identifier, const std::string& Type) :
    context_identifier(Identifier),
    context_type(Type) {
    add_attr_info(STEP_ATTR_LIST({ {"context_identifier", &context_identifier},
                                   {"context_type",       &context_type}
      }, this));
  }

  /* 4.5.4 using_items */

  SET<founded_item_select> using_items(const founded_item_select& item, const SET<founded_item_select>& checked_items) {
//    SET<founded_item_select> new_check_items;
    SET<founded_item_select> result_items;
//    SET<founded_item_select> next_items;

#if 0
    //    result_items.clear();
    if (checked_items != nullptr) {
      new_check_items = *checked_items + &item;
    }
    else {
      new_check_items = &item;
    }
    /*
     * Find the set of representation_items or founded_items
     * in which item is used directly.
     */
    next_items = QUERY(z, bag_to_set(USEDIN(&item, "")),
      ("representation_item" IN TYPEOF(z)) OR("founded_item" IN TYPEOF(z)));
    /* If the set of next_items is not empty; */
    if (SIZEOF(next_items) > INTEGER(0)) {
      /* For each element in the set, find the using_items recursively */
      for (INTEGER i = INTEGER(0); i <= HIINDEX(next_items); ++i) {
        /*
         * Check for loop in data model, i.e. one of the next_items
         * occurred earlier in the set of check_items;
         */
        if (NOT(next_items[i] IN new_check_items)) {
          result_items = result_items + next_items[i] + using_items(next_items[i], new_check_items);
        }
      }
    }
    /*
     * return the set of representation_items or founded_items
     * in which the input item is used directly and indirectly.
     */
#endif
    RETURN (result_items);
  }

  /* 4.5.5 using_representations */

  SET<representation> using_representations(const founded_item_select& item) {
    SET<representation> results;

    /*
       FUNCTION using_representations (item : founded_item_select) : SET[0:?] OF representation;
    */

    /* Find the representations in which the item is used and add to the
     * results set.
     */
     //    results.clear();
    BAG< representation> result_bag(0);//!!! = USEDIN(&item, "REPRESENTATION_SCHEMA.REPRESENTATION.ITEMS");
    if (SIZEOF(result_bag).get_value() > 0) {
      for (INTEGER i = 0; i.get_value() <= HIINDEX(result_bag).get_value(); i = i + 1) {
        results += result_bag[i];
      }
    }

    /* Find all representation_items or founded_items
     * by which item is referenced directly or indirectly.
     */
    SET<founded_item_select> intermediate_items = using_items(item, SET<founded_item_select>({}, 0,INTEGER()));

    /* If the set of intermediate items is not empty; */
    if (SIZEOF(intermediate_items).get_value() > 0) {
      /* For each element in the set, add the
       * representations of that element.
       */
      for (INTEGER i = 0; i.get_value() <= HIINDEX(intermediate_items).get_value(); i = i + 1) {
//!!!        result_bag = USEDIN(intermediate_items[i], "REPRESENTATION_SCHEMA.REPRESENTATION.ITEMS");
        if (SIZEOF(result_bag).get_value() > 0) {
          for (INTEGER j = 0; j.get_value() <= HIINDEX(result_bag).get_value(); j = j + 1) {
            results += result_bag[j];
          }
        }
      }
    }

    /* Return the set of representation in which the input item is
     * used directly and indirectly (through intervening
     * representation_items or founded items).
     */

    return results;
  }


}

#endif