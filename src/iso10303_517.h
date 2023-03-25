/**
 * \file
 *
 * \brief Файл с определениями классов, соответствующих ГОСТ Р ИСО 10303-517-2009.
 */

#include "express_typelist.h"

namespace express {

  /**
   * \brief ENTITY mechanical_design_geometric_presentation_representation (ГОСТ Р ИСО 10303-517—2009, 4.2.2)
   *
   * <B>4.2.2 Объект mechanical_design_geometric_presentation_representation</B><BR>
   * Объект <B>mechanical_design_geometric_presentation_representation</B> определяет форму и,
   * факультативно, относящиеся к ней стили представления, которые должны воспроизводиться в объекте
   * <B>mechanical_design_geometric_presentation_area</B>. Данный объект является подтипом объекта
   * <B>representation</B>. Все элементы <B>item</B> объекта <B>mechanical_design_geometric_presentation_representation</B> должны
   * быть объектами <B>representation_item</B>, описывающими форму, или <B>shape_representation</B>. Данные
   * элементы могут быть стилизованными или нестилизованными. Элемент может быть объектом <B>mapped_item</B>.
   * Использование стилей и атрибутов стилей ограничено для точек, кривых и поверхностей.
   *
   * <U>EXPRESS-спецификация:</U>
   * \verbatim
   -- DIFF IN AP214
   -- DIFF IN AP232
   -- IN AP203e2/AP214/AP232/AP238 STEP-NC/AP242
   ENTITY mechanical_design_geometric_presentation_representation
       SUBTYPE OF (representation);
          SELF\representation.items : SET [1:?] OF mechanical_design_geometric_presentation_representation_items;
       WHERE
          WR1:
             SIZEOF(QUERY (mi <* QUERY (it <* SELF.items| ('STEP_MERGED_AP_SCHEMA.MAPPED_ITEM' IN TYPEOF(it)))| NOT (SIZEOF([ 'STEP_MERGED_AP_SCHEMA.SHAPE_REPRESENTATION', 'STEP_MERGED_AP_SCHEMA.MECHANICAL_DESIGN_GEOMETRIC_PRESENTATION_REPRESENTATION' ] * TYPEOF(mi\mapped_item.mapping_source.mapped_representation)) = 1))) = 0;
          wr2:
             SIZEOF(QUERY (smi <* QUERY (si <* QUERY (it <* SELF.items| ('STEP_MERGED_AP_SCHEMA.STYLED_ITEM' IN TYPEOF(it)))| ('STEP_MERGED_AP_SCHEMA.MAPPED_ITEM' IN TYPEOF(si\styled_item.item)))| NOT ('STEP_MERGED_AP_SCHEMA.SHAPE_REPRESENTATION' IN TYPEOF(smi\styled_item.item\mapped_item.mapping_source.mapped_representation)))) = 0;
          wr3:
             SIZEOF(QUERY (si <* QUERY (it <* SELF.items| ('STEP_MERGED_AP_SCHEMA.STYLED_ITEM' IN TYPEOF(it)))| NOT (SIZEOF(QUERY (psa <* si\styled_item.styles| NOT (SIZEOF(QUERY (pss <* psa.styles| NOT (SIZEOF([ 'STEP_MERGED_AP_SCHEMA.POINT_STYLE', 'STEP_MERGED_AP_SCHEMA.CURVE_STYLE', 'STEP_MERGED_AP_SCHEMA.SURFACE_STYLE_USAGE' ] * TYPEOF(pss)) = 1))) = 0))) = 0))) = 0;
          wr4:
             SIZEOF(QUERY (si <* QUERY (it <* SELF.items| ('STEP_MERGED_AP_SCHEMA.STYLED_ITEM' IN TYPEOF(it)))| NOT (SIZEOF(QUERY (psbc <* QUERY (psa <* si\styled_item.styles| ('STEP_MERGED_AP_SCHEMA.PRESENTATION_STYLE_BY_CONTEXT' IN TYPEOF(psa)))| NOT (SIZEOF([ 'STEP_MERGED_AP_SCHEMA.REPRESENTATION_ITEM', 'STEP_MERGED_AP_SCHEMA.REPRESENTATION' ] * TYPEOF(psbc\presentation_style_by_context.style_context)) = 1))) = 0))) = 0;
          wr5:
             SIZEOF(QUERY (si <* QUERY (it <* SELF.items| ('STEP_MERGED_AP_SCHEMA.STYLED_ITEM' IN TYPEOF(it)))| NOT (SIZEOF(QUERY (psa <* si\styled_item.styles| NOT (SIZEOF(QUERY (ps <* QUERY (pss <* psa.styles| ('STEP_MERGED_AP_SCHEMA.POINT_STYLE' IN TYPEOF(pss)))| NOT (('STEP_MERGED_AP_SCHEMA.POSITIVE_LENGTH_MEASURE' IN TYPEOF(ps\point_style.marker_size)) AND (SIZEOF([ 'STEP_MERGED_AP_SCHEMA.COLOUR_RGB', 'STEP_MERGED_AP_SCHEMA.DRAUGHTING_PRE_DEFINED_COLOUR' ] * TYPEOF(ps\point_style.marker_colour)) = 1)))) = 0))) = 0))) = 0;
          wr6:
             SIZEOF(QUERY (si <* QUERY (it <* SELF.items| ('STEP_MERGED_AP_SCHEMA.STYLED_ITEM' IN TYPEOF(it)))| NOT (SIZEOF(QUERY (psa <* si\styled_item.styles| NOT (SIZEOF(QUERY (cs <* QUERY (pss <* psa.styles| ('STEP_MERGED_AP_SCHEMA.CURVE_STYLE' IN TYPEOF(pss)))| NOT (((SIZEOF([ 'STEP_MERGED_AP_SCHEMA.COLOUR_RGB', 'STEP_MERGED_AP_SCHEMA.DRAUGHTING_PRE_DEFINED_COLOUR' ] * TYPEOF(cs\curve_style.curve_colour)) = 1) AND ('STEP_MERGED_AP_SCHEMA.POSITIVE_LENGTH_MEASURE' IN TYPEOF(cs\curve_style.curve_width))) AND (SIZEOF([ 'STEP_MERGED_AP_SCHEMA.CURVE_STYLE_FONT', 'STEP_MERGED_AP_SCHEMA.DRAUGHTING_PRE_DEFINED_CURVE_FONT' ] * TYPEOF(cs\curve_style.curve_font)) = 1)))) = 0))) = 0))) = 0;
          wr7:
             SIZEOF(QUERY (si <* QUERY (it <* SELF.items| ('STEP_MERGED_AP_SCHEMA.STYLED_ITEM' IN TYPEOF(it)))| NOT (SIZEOF(QUERY (psa <* si\styled_item.styles| NOT (SIZEOF(QUERY (ssu <* QUERY (pss <* psa.styles| ('STEP_MERGED_AP_SCHEMA.SURFACE_STYLE_USAGE' IN TYPEOF(pss)))| NOT ('STEP_MERGED_AP_SCHEMA.SURFACE_SIDE_STYLE' IN TYPEOF(ssu\surface_style_usage.style)))) = 0))) = 0))) = 0;
          wr8:
             SIZEOF(QUERY (si <* QUERY (it <* SELF.items| ('STEP_MERGED_AP_SCHEMA.STYLED_ITEM' IN TYPEOF(it)))| NOT (SIZEOF(QUERY (psa <* si\styled_item.styles| NOT (SIZEOF(QUERY (ssu <* QUERY (pss <* psa.styles| ('STEP_MERGED_AP_SCHEMA.SURFACE_STYLE_USAGE' IN TYPEOF(pss)))| NOT (SIZEOF(QUERY (sses <* ssu\surface_style_usage.style\surface_side_style.styles| NOT (SIZEOF([ 'STEP_MERGED_AP_SCHEMA.SURFACE_STYLE_PARAMETER_LINE', 'STEP_MERGED_AP_SCHEMA.SURFACE_STYLE_CONTROL_GRID', 'STEP_MERGED_AP_SCHEMA.SURFACE_STYLE_SILHOUETTE', 'STEP_MERGED_AP_SCHEMA.SURFACE_STYLE_SEGMENTATION_CURVE', 'STEP_MERGED_AP_SCHEMA.SURFACE_STYLE_FILL_AREA', 'STEP_MERGED_AP_SCHEMA.SURFACE_STYLE_BOUNDARY' ] * TYPEOF(sses)) = 1))) = 0))) = 0))) = 0))) = 0;
          wr9:
             SIZEOF(QUERY (si <* QUERY (it <* SELF.items| ('STEP_MERGED_AP_SCHEMA.STYLED_ITEM' IN TYPEOF(it)))| NOT (SIZEOF(QUERY (psa <* si\styled_item.styles| NOT (SIZEOF(QUERY (ssu <* QUERY (pss <* psa.styles| ('STEP_MERGED_AP_SCHEMA.SURFACE_STYLE_USAGE' IN TYPEOF(pss)))| NOT (SIZEOF(QUERY (sspl <* QUERY (sses <* ssu\surface_style_usage.style\surface_side_style.styles| ('STEP_MERGED_AP_SCHEMA.SURFACE_STYLE_PARAMETER_LINE' IN TYPEOF(sses)))| NOT (((('STEP_MERGED_AP_SCHEMA.CURVE_STYLE' IN TYPEOF(sspl\surface_style_parameter_line.style_of_parameter_lines)) AND (SIZEOF([ 'STEP_MERGED_AP_SCHEMA.COLOUR_RGB', 'STEP_MERGED_AP_SCHEMA.DRAUGHTING_PRE_DEFINED_COLOUR' ] * TYPEOF(sspl\surface_style_parameter_line.style_of_parameter_lines\curve_style.curve_colour)) = 1)) AND ('STEP_MERGED_AP_SCHEMA.POSITIVE_LENGTH_MEASURE' IN TYPEOF(sspl\surface_style_parameter_line.style_of_parameter_lines\curve_style.curve_width))) AND (SIZEOF([ 'STEP_MERGED_AP_SCHEMA.CURVE_STYLE_FONT', 'STEP_MERGED_AP_SCHEMA.DRAUGHTING_PRE_DEFINED_CURVE_FONT' ] * TYPEOF(sspl\surface_style_parameter_line.style_of_parameter_lines\curve_style.curve_font)) = 1)))) = 0))) = 0))) = 0))) = 0;
          wr10:
             SIZEOF(QUERY (si <* QUERY (it <* SELF.items| ('STEP_MERGED_AP_SCHEMA.STYLED_ITEM' IN TYPEOF(it)))| NOT (SIZEOF(QUERY (psa <* si\styled_item.styles| NOT (SIZEOF(QUERY (ssu <* QUERY (pss <* psa.styles| ('STEP_MERGED_AP_SCHEMA.SURFACE_STYLE_USAGE' IN TYPEOF(pss)))| NOT (SIZEOF(QUERY (sscg <* QUERY (sses <* ssu\surface_style_usage.style\surface_side_style.styles| ('STEP_MERGED_AP_SCHEMA.SURFACE_STYLE_CONTROL_GRID' IN TYPEOF(sses)))| NOT (((('STEP_MERGED_AP_SCHEMA.CURVE_STYLE' IN TYPEOF(sscg\surface_style_control_grid.style_of_control_grid)) AND (SIZEOF([ 'STEP_MERGED_AP_SCHEMA.COLOUR_RGB', 'STEP_MERGED_AP_SCHEMA.DRAUGHTING_PRE_DEFINED_COLOUR' ] * TYPEOF(sscg\surface_style_control_grid.style_of_control_grid\curve_style.curve_colour)) = 1)) AND ('STEP_MERGED_AP_SCHEMA.POSITIVE_LENGTH_MEASURE' IN TYPEOF(sscg\surface_style_control_grid.style_of_control_grid\curve_style.curve_width))) AND (SIZEOF([ 'STEP_MERGED_AP_SCHEMA.CURVE_STYLE_FONT', 'STEP_MERGED_AP_SCHEMA.DRAUGHTING_PRE_DEFINED_CURVE_FONT' ] * TYPEOF(sscg\surface_style_control_grid.style_of_control_grid\curve_style.curve_font)) = 1)))) = 0))) = 0))) = 0))) = 0;
          wr11:
             SIZEOF(QUERY (si <* QUERY (it <* SELF.items| ('STEP_MERGED_AP_SCHEMA.STYLED_ITEM' IN TYPEOF(it)))| NOT (SIZEOF(QUERY (psa <* si\styled_item.styles| NOT (SIZEOF(QUERY (ssu <* QUERY (pss <* psa.styles| ('STEP_MERGED_AP_SCHEMA.SURFACE_STYLE_USAGE' IN TYPEOF(pss)))| NOT (SIZEOF(QUERY (sssh <* QUERY (sses <* ssu\surface_style_usage.style\surface_side_style.styles| ('STEP_MERGED_AP_SCHEMA.SURFACE_STYLE_SILHOUETTE' IN TYPEOF(sses)))| NOT (((('STEP_MERGED_AP_SCHEMA.CURVE_STYLE' IN TYPEOF(sssh\surface_style_silhouette.style_of_silhouette)) AND (SIZEOF([ 'STEP_MERGED_AP_SCHEMA.COLOUR_RGB', 'STEP_MERGED_AP_SCHEMA.DRAUGHTING_PRE_DEFINED_COLOUR' ] * TYPEOF(sssh\surface_style_silhouette.style_of_silhouette\curve_style.curve_colour)) = 1)) AND ('STEP_MERGED_AP_SCHEMA.POSITIVE_LENGTH_MEASURE' IN TYPEOF(sssh\surface_style_silhouette.style_of_silhouette\curve_style.curve_width))) AND (SIZEOF([ 'STEP_MERGED_AP_SCHEMA.CURVE_STYLE_FONT', 'STEP_MERGED_AP_SCHEMA.DRAUGHTING_PRE_DEFINED_CURVE_FONT' ] * TYPEOF(sssh\surface_style_silhouette.style_of_silhouette\curve_style.curve_font)) = 1)))) = 0))) = 0))) = 0))) = 0;
          wr12:
             SIZEOF(QUERY (si <* QUERY (it <* SELF.items| ('STEP_MERGED_AP_SCHEMA.STYLED_ITEM' IN TYPEOF(it)))| NOT (SIZEOF(QUERY (psa <* si\styled_item.styles| NOT (SIZEOF(QUERY (ssu <* QUERY (pss <* psa.styles| ('STEP_MERGED_AP_SCHEMA.SURFACE_STYLE_USAGE' IN TYPEOF(pss)))| NOT (SIZEOF(QUERY (sssc <* QUERY (sses <* ssu\surface_style_usage.style\surface_side_style.styles| ('STEP_MERGED_AP_SCHEMA.SURFACE_STYLE_SEGMENTATION_CURVE' IN TYPEOF(sses)))| NOT (((('STEP_MERGED_AP_SCHEMA.CURVE_STYLE' IN TYPEOF(sssc\surface_style_segmentation_curve.style_of_segmentation_curve)) AND (SIZEOF([ 'STEP_MERGED_AP_SCHEMA.COLOUR_RGB', 'STEP_MERGED_AP_SCHEMA.DRAUGHTING_PRE_DEFINED_COLOUR' ] * TYPEOF(sssc\surface_style_segmentation_curve.style_of_segmentation_curve\curve_style.curve_colour)) = 1)) AND ('STEP_MERGED_AP_SCHEMA.POSITIVE_LENGTH_MEASURE' IN TYPEOF(sssc\surface_style_segmentation_curve.style_of_segmentation_curve\curve_style.curve_width))) AND (SIZEOF([ 'STEP_MERGED_AP_SCHEMA.CURVE_STYLE_FONT', 'STEP_MERGED_AP_SCHEMA.DRAUGHTING_PRE_DEFINED_CURVE_FONT' ] * TYPEOF(sssc\surface_style_segmentation_curve.style_of_segmentation_curve\curve_style.curve_font)) = 1)))) = 0))) = 0))) = 0))) = 0;
          wr13:
             SIZEOF(QUERY (si <* QUERY (it <* SELF.items| ('STEP_MERGED_AP_SCHEMA.STYLED_ITEM' IN TYPEOF(it)))| NOT (SIZEOF(QUERY (psa <* si\styled_item.styles| NOT (SIZEOF(QUERY (ssu <* QUERY (pss <* psa.styles| ('STEP_MERGED_AP_SCHEMA.SURFACE_STYLE_USAGE' IN TYPEOF(pss)))| NOT (SIZEOF(QUERY (ssbd <* QUERY (sses <* ssu\surface_style_usage.style\surface_side_style.styles| ('STEP_MERGED_AP_SCHEMA.SURFACE_STYLE_BOUNDARY' IN TYPEOF(sses)))| NOT (((('STEP_MERGED_AP_SCHEMA.CURVE_STYLE' IN TYPEOF(ssbd\surface_style_boundary.style_of_boundary)) AND (SIZEOF([ 'STEP_MERGED_AP_SCHEMA.COLOUR_RGB', 'STEP_MERGED_AP_SCHEMA.DRAUGHTING_PRE_DEFINED_COLOUR' ] * TYPEOF(ssbd\surface_style_boundary.style_of_boundary\curve_style.curve_colour)) = 1)) AND ('STEP_MERGED_AP_SCHEMA.POSITIVE_LENGTH_MEASURE' IN TYPEOF(ssbd\surface_style_boundary.style_of_boundary\curve_style.curve_width))) AND (SIZEOF([ 'STEP_MERGED_AP_SCHEMA.CURVE_STYLE_FONT', 'STEP_MERGED_AP_SCHEMA.DRAUGHTING_PRE_DEFINED_CURVE_FONT' ] * TYPEOF(ssbd\surface_style_boundary.style_of_boundary\curve_style.curve_font)) = 1)))) = 0))) = 0))) = 0))) = 0;
    END_ENTITY;
   \endverbatim
   *
   * <U>Формальные утверждения</U><BR>
   * <B>WR1</B> - каждый объект из множества items должен быть объектом styled_item, mapped item,
   * axis2_placement или camera_model_d3.
   * <B>WR2</B> - объект mapped_representation из representation_map, то есть объект mapping source из
   * mapped_item, в mechanical design geometric presentation representation должен быть представлен
   * объектом shape_representation или другим объектом mechanical_design_geometric_presentation_representation.
   * <B>WR3</B> - элемент styled_item может быть только объектом mapped_item, если у объекта mapped_item
   * атрибут mapped_representation является объектом shape_representation.
   * <B>WR4</B> - каждый элемент множества styles из presentation_style_assignment должен быть объектом
   * point_style, curve_style или surface_style_usage.
   * <B>WR5</B> - атрибут style_context объекта presentation_style_by_context должен быть объектом
   * representation или representationitem.
   * <B>WR6</B> - для каждого объекта point_style из множества styles объекта presentation_style_assignment
   * атрибут markercolour должен быть объектом colourrgb или draughting_pre_defined_colour; атрибут
   * marker_size должен быть объектом positive_length_measure.
   * <B>WR7</B> - для каждого объекта curve_style из множества styles объекта presentation_style_assignment
   * атрибут curve_colour должен быть объектом colour rgb или draughting_pre_defined_colour; атрибут
   * curve_width должен быть объектом positivejengthmeasure; атрибут curve_font должен быть объектом
   * curve_style_font или draughting_pre_defined_curve_font.
   * <B>WR8</B> - атрибут style каждого объекта surface_style_usage из множества styles объекта
   * presentation_style_assignment должен быть объектом surface_side_style.
   * <B>WR9</B> - каждый элемент множества styles объекта surface_side_style должен быть объектом
   * surface_style_parameter_line, surface_style_control_grid, surface_style_silhouette, surface_style_segmentationcurve,
   * surface_style_fill_area или surface_style_boundary.
   * <B>WR10</B> - атрибут style_of_parameter_lines объекта surface_style_parameter_line должен быть объектом curve_style, и для
   * данного объекта curve_style атрибут curve_colourдолжен быть объектом colour rgb или draughting pre defined colour;
   * атрибут curve_width должен быть объектом positive_length_measure;
   * атрибут curve_font должен быть объектом curve_style_font или draughting_pre_defined_curve_font.
   * <B>WR11</B> - атрибут style_of_control_grid объекта surface_style_control_grid должен быть объектом
   * curve_style, и для данного объекта curve_style атрибут curve_colour должен быть объектом colour rgb
   * или draughting_pre_defined_colour; атрибут curve_width должен быть объектом positive_length_measure;
   * атрибут curve_font должен быть объектом curve_style_font или draughting_pre_defined_curve_font.
   * <B>WR12</B> - атрибут style_of_silhouette объекта surface_style_silhouette должен быть объектом
   * curve_style, и для данного объекта curve_style атрибут curve_colour должен быть объектом colour rgb
   * или draughting_pre_defined_colour; атрибут curve_width должен быть объектом positive_length_measure;
   * атрибут curve_font должен быть объектом curve_style_font или draughting_pre_defined_curve_font.
   * <B>WR13</B> - атрибут style_of_segmentation_curve объекта surface_style_ segmentation curve должен
   * быть объектом curve_style, и для данного объекта curve_style атрибут curve_colour должен быть объектом colour_rgb или draughting_pre_defined_colour; атрибут curve_width должен быть объектом
   * positive length measure;
   * атрибут curve_font должен быть объектом curve_style_font или draughting_pre_defined_curve_font.
   * <B>WR14</B> - атрибут style_of_boundary объекта surface_style_boundary должен быть объектом
   * curve_style, и для данного объекта curve_style атрибут curve_colour должен быть объектом colour_rgb
   * или draughting pre defined colour;<BR>
   * атрибут curve_width должен быть объектом positive length measure;<BR>
   * атрибут curve_font должен быть объектом curve_style_font или draughting_pre_defined_curve_font.
   */
  class mechanical_design_geometric_presentation_representation : public representation {
  public:

    /** \brief Конструктор */
    mechanical_design_geometric_presentation_representation(const std::string& Name, const representation_context* Context_of_items) :
      representation(Name, Context_of_items) {
    }

    /** \brief Деструктор по умолчанию */
    virtual ~mechanical_design_geometric_presentation_representation() = default;

    // FUNCTION get_id_value
//    identifier get_id_value() {
//      return "";
//    }

    // FUNCTION get_description_value
//    text get_description_value() {
//      return "";
//    }
  };


  /**
   * \brief TYPE mechanical_design_geometric_presentation_representation_items (ISO 10303-517:2021(E), 4.3.2)
   *
   * <B>4.3.2 mechanical_design_geometric_presentation_representation_items</B><BR>
   * The <B>mechanical_design_geometric_presentation_representation_items</B> type is a list of alternate data types.
   * It provides a mechanism to refer to an instance of one of these data types.
   *
   * <U>EXPRESS specification:</U>
   * \verbatim
    -- IN AP203e2/AP238 STEP-NC/AP242
    TYPE mechanical_design_geometric_presentation_representation_items = SELECT
          (axis2_placement,
           camera_model_d3,
           mapped_item,
           styled_item);
    END_TYPE;
   \endverbatim
   *
   */
  class mechanical_design_geometric_presentation_representation_items : public SELECT {

  public:

    /** \brief Конструктор из типа axis2_placement */
    mechanical_design_geometric_presentation_representation_items(const axis2_placement* t);
//  /** \brief Конструктор из типа camera_model_d3 */
//  mechanical_design_geometric_presentation_representation_items(const camera_model_d3* t);
//  /** \brief Конструктор из типа mapped_item */
//  mechanical_design_geometric_presentation_representation_items(const mapped_item* t);
    /** \brief Конструктор из типа styled_item */
    mechanical_design_geometric_presentation_representation_items(const styled_item* t);
  };
}