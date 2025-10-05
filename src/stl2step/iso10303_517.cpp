/**
 * \file
 *
 * \brief Файл с определениями функций классов примитивов типов EXPRESS ГОСТ Р ИСО 10303-517-2009.
 */

#include "stdafx.h"
#include "express.h"

namespace express {


  STEP_TYPE_SELECT_CONSTRUCTOR(mechanical_design_geometric_presentation_representation_items, axis2_placement)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(mechanical_design_geometric_presentation_representation_items, camera_model_d3)
  //  STEP_TYPE_SELECT_CONSTRUCTOR(mechanical_design_geometric_presentation_representation_items, mapped_item)
  STEP_TYPE_SELECT_CONSTRUCTOR(mechanical_design_geometric_presentation_representation_items, styled_item)
}
