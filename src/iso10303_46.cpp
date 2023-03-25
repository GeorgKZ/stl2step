/**
 * \file
 *
 * \brief Файл с определениями функций классов, соответствующих ISO 10303-46:2021(E)
 *
 * Здесь определены функции классов, относящихся к визуальному представлению.
 */

#ifndef TESTONLY

#include "stdafx.h"
#include "express.h"

namespace express {

  STEP_TYPE_SELECT_CONSTRUCTOR(rendering_properties_select, surface_style_reflectance_ambient)
    STEP_TYPE_SELECT_CONSTRUCTOR(rendering_properties_select, surface_style_transparent)


    surface_style_rendering::surface_style_rendering(const shading_surface_method& Rendering_method, colour* Surface_colour) {
    rendering_method = new shading_surface_method(Rendering_method);
    surface_colour = Surface_colour;
    add_attr_info(STEP_ATTR_LIST({
                                   {"rendering_method", rendering_method},
                                   {"surface_colour",   surface_colour},
      }, this));
  }

  surface_style_rendering::~surface_style_rendering() {
    delete rendering_method;
  }

  /*  6.4.62 */

  surface_style_rendering_with_properties::surface_style_rendering_with_properties(
    const shading_surface_method& Rendering_method,
    colour* Surface_colour) :
    surface_style_rendering(Rendering_method, Surface_colour),
    properties(1,2)  {
    add_attr_info(STEP_ATTR_LIST({
                                   {"properties", &properties}
      }, this));
  }


  /* 6.6.1 */

  curve_style::curve_style(
    const std::string& Name,
    const curve_font_or_scaled_curve_font_select* Font,
    const size_select* Width,
    const colour* Colour) {
    name = new label(Name);
    curve_font = Font;
    curve_width = Width;
    curve_colour = Colour;
    add_attr_info(STEP_ATTR_LIST({
                                   {"name",         name},
                                   {"curve_font",   curve_font, true},
                                   {"curve_width",  curve_width, true},
                                   {"curve_colour", curve_colour, true},
      }, this));
  }

  curve_style::~curve_style() {
    delete name;
  }

  fill_area_style_colour::fill_area_style_colour(const std::string& Name, const colour_rgb* Fill_colour) {
    name = new label(Name);
    fill_colour = Fill_colour;
    add_attr_info(STEP_ATTR_LIST({
                                   {"name", name},
                                   {"fill_colour", fill_colour},
      }, this));
  }

  fill_area_style_colour::~fill_area_style_colour() {
    delete name;
  }



  //  STEP_TYPE_SELECT_CONSTRUCTOR(fill_style_select, externally_defined_hatch_style)
  //STEP_TYPE_SELECT_CONSTRUCTOR(fill_style_select, externally_defined_tile_style)
  STEP_TYPE_SELECT_CONSTRUCTOR(fill_style_select, fill_area_style_colour)
    //  STEP_TYPE_SELECT_CONSTRUCTOR(fill_style_select, fill_area_style_hatching)
    //  STEP_TYPE_SELECT_CONSTRUCTOR(fill_style_select, fill_area_style_tiles)
    //  STEP_TYPE_SELECT_CONSTRUCTOR(fill_style_select, texture_style_specification)

    //  STEP_TYPE_SELECT_CONSTRUCTOR(presentation_style_select, approximation_tolerance)
    STEP_TYPE_SELECT_CONSTRUCTOR(presentation_style_select, curve_style)
    //  STEP_TYPE_SELECT_CONSTRUCTOR(presentation_style_select, externally_defined_style)
    STEP_TYPE_SELECT_CONSTRUCTOR(presentation_style_select, fill_area_style)
    STEP_TYPE_SELECT_CONSTRUCTOR(presentation_style_select, null_style)
    //  STEP_TYPE_SELECT_CONSTRUCTOR(presentation_style_select, point_style)
    //  STEP_TYPE_SELECT_CONSTRUCTOR(presentation_style_select, pre_defined_presentation_style)
    STEP_TYPE_SELECT_CONSTRUCTOR(presentation_style_select, surface_style_usage)
    //  STEP_TYPE_SELECT_CONSTRUCTOR(presentation_style_select, symbol_style)
    //  STEP_TYPE_SELECT_CONSTRUCTOR(presentation_style_select, text_style)
    //  STEP_TYPE_SELECT_CONSTRUCTOR(presentation_style_select, texture_style_tessellation_specification)

    //  STEP_TYPE_SELECT_CONSTRUCTOR(curve_font_or_scaled_curve_font_select, curve_style_font_and_scaling)
    STEP_TYPE_SELECT_CONSTRUCTOR(curve_font_or_scaled_curve_font_select, curve_style_font_select)
    //  STEP_TYPE_SELECT_CONSTRUCTOR(curve_style_font_select, curve_style_font)
    //  STEP_TYPE_SELECT_CONSTRUCTOR(curve_style_font_select, externally_defined_curve_font)
    STEP_TYPE_SELECT_CONSTRUCTOR(curve_style_font_select, pre_defined_curve_font)

    //  STEP_TYPE_SELECT_CONSTRUCTOR(surface_style_element_select, surface_style_boundary)
    //  STEP_TYPE_SELECT_CONSTRUCTOR(surface_style_element_select, surface_style_control_grid)
    STEP_TYPE_SELECT_CONSTRUCTOR(surface_style_element_select, surface_style_fill_area)
    //  STEP_TYPE_SELECT_CONSTRUCTOR(surface_style_element_select, surface_style_parameter_line)
    STEP_TYPE_SELECT_CONSTRUCTOR(surface_style_element_select, surface_style_rendering)
    //  STEP_TYPE_SELECT_CONSTRUCTOR(surface_style_element_select, surface_style_segmentation_curve)
    //  STEP_TYPE_SELECT_CONSTRUCTOR(surface_style_element_select, surface_style_silhouette)

    STEP_TYPE_SELECT_CONSTRUCTOR(styled_item_target, geometric_representation_item)
    //  STEP_TYPE_SELECT_CONSTRUCTOR(styled_item_target, mapped_item)
    STEP_TYPE_SELECT_CONSTRUCTOR(styled_item_target, representation_or_representation_reference)
    STEP_TYPE_SELECT_CONSTRUCTOR(styled_item_target, topological_representation_item)

    //  STEP_TYPE_SELECT_CONSTRUCTOR(surface_side_style_select, pre_defined_surface_side_style)
    STEP_TYPE_SELECT_CONSTRUCTOR(surface_side_style_select, surface_side_style)

    STEP_TYPE_SELECT_CONSTRUCTOR(size_select, descriptive_measure)
    STEP_TYPE_SELECT_CONSTRUCTOR(size_select, measure_with_unit)
    STEP_TYPE_SELECT_CONSTRUCTOR(size_select, positive_length_measure)

}

#endif