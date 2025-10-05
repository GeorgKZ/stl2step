/**
 * \file
 *
 * \brief Заголовочный файл с определениями классов, соответствующих ISO 10303-46:2021(E)
 */

namespace express {

/**
 * \brief TYPE presentation_style_select (ГОСТ Р ИСО 10303-46-2002, 6.3.2)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  -- DIFF IN AP214
  -- DIFF IN AP203e2
  -- DIFF IN AP238 STEP-NC
  -- DIFF IN AP232
  -- IN AP203e2/AP214/AP232/AP238 STEP-NC/AP242
  TYPE presentation_style_select = SELECT
    (approximation_tolerance,                                    -- AP214
     curve_style,                                                -- Common
     externally_defined_style,                                   -- AP214/AP232/AP238 STEP-NC/AP242
     fill_area_style,                                            -- Common
     null_style,                                                 -- AP203e2/AP214/AP238 STEP-NC/AP242
     point_style,                                                -- Common
     pre_defined_presentation_style,                             -- AP214
     surface_style_usage,                                        -- Common
     symbol_style,                                               -- AP203e2/AP214/AP238 STEP-NC/AP242
     text_style,                                                 -- Common
     texture_style_tessellation_specification);                  -- AP242
  END_TYPE;
 \endverbatim
 *
 */
class presentation_style_select : public SELECT {

public:

//  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(presentation_style_select, approximation_tolerance);
  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(presentation_style_select, curve_style);
//  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(presentation_style_select, externally_defined_style);
  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(presentation_style_select, fill_area_style);
  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(presentation_style_select, null_style);
//  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(presentation_style_select, point_style);
//  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(presentation_style_select, pre_defined_presentation_style);
  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(presentation_style_select, surface_style_usage);
//  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(presentation_style_select, symbol_style);
//  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(presentation_style_select, text_style);
//  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(presentation_style_select, texture_style_tessellation_specification);
};

/**
 * \brief TYPE curve_font_or_scaled_curve_font_select (ГОСТ Р ИСО 10303-46-2002, 6.3.7)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  -- DIFF IN AP214
  -- DIFF IN AP203e2
  -- DIFF IN AP238 STEP-NC
  -- DIFF IN AP232
  -- IN AP203e2/AP214/AP232/AP238 STEP-NC/AP242
  TYPE curve_font_or_scaled_curve_font_select = SELECT
    (curve_style_font_and_scaling,                               -- AP203e2/AP238 STEP-NC/AP242
     curve_style_font_select);                                   -- Common
  END_TYPE;
 \endverbatim
 *
 */
class curve_font_or_scaled_curve_font_select : public SELECT {

public:

//  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(curve_font_or_scaled_curve_font_select, curve_style_font_and_scaling);
  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(curve_font_or_scaled_curve_font_select, curve_style_font_select);
};

/**
 * \brief TYPE curve_style_font_select (ГОСТ Р ИСО 10303-46-2002, 6.3.8)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  TYPE curve_style_font_select = SELECT
    (curve_style_font,                                           -- Common
     externally_defined_curve_font,                              -- AP203e2/AP214/AP238 STEP-NC/AP242
     pre_defined_curve_font);                                    -- Common
  END_TYPE;
 \endverbatim
 *
 */
class curve_style_font_select : public SELECT {

public:

//  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(curve_style_font_select, curve_style_font);
//  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(curve_style_font_select, externally_defined_curve_font);
  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(curve_style_font_select, pre_defined_curve_font);
};


/**
 * \brief TYPE fill_style_select (ГОСТ Р ИСО 10303-46-2002, 6.3.10)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  -- DIFF IN AP214
  -- DIFF IN AP203e2
  -- DIFF IN AP238 STEP-NC
  -- DIFF IN AP232
  -- IN AP203e2/AP214/AP232/AP238 STEP-NC/AP242
  TYPE fill_style_select = SELECT
    (externally_defined_hatch_style,                             -- AP203e2/AP214/AP238 STEP-NC/AP242
     externally_defined_tile_style,                              -- AP203e2/AP214/AP238 STEP-NC/AP242
     fill_area_style_colour,                                     -- Common
     fill_area_style_hatching,                                   -- AP203e2/AP214/AP238 STEP-NC/AP242
     fill_area_style_tiles,                                      -- AP203e2/AP214/AP238 STEP-NC/AP242
     texture_style_specification);                               -- AP242
  END_TYPE;
 \endverbatim
 *
 */
class fill_style_select : public SELECT {

public:

//  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(fill_style_select, externally_defined_hatch_style);
//  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(fill_style_select, externally_defined_tile_style);
  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(fill_style_select, fill_area_style_colour);
//  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(fill_style_select, fill_area_style_hatching);
//  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(fill_style_select, fill_area_style_tiles);
//  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(fill_style_select, texture_style_specification);
};

/**
 * \brief TYPE surface_side_style_select (ГОСТ Р ИСО 10303-46-2002, 6.3.14)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  -- DIFF IN AP214
  -- DIFF IN AP203e2
  -- DIFF IN AP238 STEP-NC
  -- DIFF IN AP232
  -- IN AP203e2/AP214/AP232/AP238 STEP-NC/AP242
  TYPE surface_side_style_select = SELECT
    (pre_defined_surface_side_style,                             -- AP203e2/AP238 STEP-NC/AP242
     surface_side_style);                                        -- Common
  END_TYPE;
 \endverbatim
 *
 */
class surface_side_style_select : public SELECT {

public:

//  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(surface_side_style_select, pre_defined_surface_side_style);
  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(surface_side_style_select, surface_side_style);
};



/**
 * \brief TYPE surface_style_element_select (ГОСТ Р ИСО 10303-46-2002, 6.3.15)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  -- DIFF IN AP214
  -- DIFF IN AP203e2
  -- DIFF IN AP238 STEP-NC
  -- DIFF IN AP232
  -- IN AP203e2/AP214/AP232/AP238 STEP-NC/AP242
  TYPE surface_style_element_select = SELECT
        (surface_style_boundary,
         surface_style_control_grid,
         surface_style_fill_area,
         surface_style_parameter_line,
         surface_style_rendering,
         surface_style_segmentation_curve,
         surface_style_silhouette);
  END_TYPE;
 \endverbatim
 *
 */
class surface_style_element_select : public SELECT {

public:

//  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(surface_style_element_select, surface_style_boundary);
//  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(surface_style_element_select, surface_style_control_grid);
  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(surface_style_element_select, surface_style_fill_area);
//  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(surface_style_element_select, surface_style_parameter_line);
  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(surface_style_element_select, surface_style_rendering);
//  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(surface_style_element_select, surface_style_segmentation_curve);
//  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(surface_style_element_select, surface_style_silhouette);
};

/**
 * \brief TYPE null_style (ISO 10303-46:2021(E), 6.3.25)
 *
 *<B>6.3.25 null_style</B>
 * The <B>\ref null_style</B> specifies that no specific style is assigned directly to an item
 * that is to be presented. The style or styles to be used in presenting the item are specified
 * within the definition of the item. If no styles are specified within the definition, then it
 * is up to the receiving system on how to present the item.
 *
 * <SMALL>EXAMPLE A symbol is defined using two <B>\ref annotation_curve_occurrences</B>, which are
 * styled such that one is red and the other is blue. If an instance of the symbol is assigned
 * <B>\ref null_style</B>, it will be presented using the colours specified in the definition.</SMALL>
 *
 * <U>EXPRESS specification:</U>
 *\verbatim
  *)
  -- IN AP203e2/AP214/AP238 STEP-NC/AP242
  TYPE null_style = ENUMERATION OF
     (null);
  END_TYPE;
  (* 
 \endverbatim
 *
 * <U>Enumerated item definitions:</U><BR>
 * null: the <B>\ref representation_item</B> to which the style is applied shall be presented using
 * the style or styles contained in its definition, if any. 
 *
 * <A http://www.steptools.com/stds/stp_aim/html/t_null_style.html">Ссылка.</A>
 */
class null_style : public ENUMERATION {
public:

  enum
#if !defined(__DOXYGEN__)
  class
#endif 
  val {
    /**
     * the <B>\ref representation_item</B> to which the style is applied shall be presented using
     * the style or styles contained in its definition, if any. 
     */
    none = 0,
    };

private:

  val x_;

public:

  // Конструктор
  null_style(val v) : x_(v) {
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
    }
    return s.str();
  }
};



/**
 * \brief rendering_properties_select (ISO 10303-46:2021(E), 6.3.28)
 *
 * <B>6.3.28 rendering_properties_select</B><BR>
 * The <B>rendering_properties_select</B> type is a list of alternate data types. It provides a mechanism
 * to refer to an instance of one of these data types. The <B>rendering_properties_select</B> is a selection
 * between two kinds of properties for a surface: reflectance and transparency.
 *
 *
 * <U>EXPRESS specification:</U>
 * \verbatim
  *)
  TYPE rendering_properties_select = SELECT
     (surface_style_reflectance_ambient,
      surface_style_transparent);
  END_TYPE;
  (* 
  (* 
 \endverbatim
 * 
 * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_rendering_properties_select.html">Ссылка.</A>
 */
class rendering_properties_select : public SELECT {

public:

  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(rendering_properties_select, surface_style_reflectance_ambient);
  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(rendering_properties_select, surface_style_transparent);
};

/**
 * \brief TYPE styled_item_target (ISO 10303-46:2021(E), 6.3.34)
 *
 * <B>6.3.34 styled_item_target</B><BR>
 * The <B>styled_item_target</B> type is a list of alternate data types. It provides a mechanism to refer to an
 * instance of one of these data types.
 *
 * <U>EXPRESS specification:</U>
 * \verbatim
  -- IN AP238 STEP-NC/AP242
  TYPE styled_item_target = SELECT
        (geometric_representation_item,
         mapped_item,
         representation_or_representation_reference,
         topological_representation_item);
  END_TYPE;
 \endverbatim
 *
 * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_styled_item_target.html">Ссылка.</A>
 */
class styled_item_target : public SELECT {

public:

  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(styled_item_target, geometric_representation_item);
//  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(styled_item_target, mapped_item);
  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(styled_item_target, representation_or_representation_reference);
  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(styled_item_target, topological_representation_item);
};

/**
 * \brief TYPE surface_side (ISO 10303-46:2021(E), 6.3.35)
 *
 * <B>6.3.35 surface_side</B><BR>
 * The <B>\ref surface_side</B> is used by <B>\ref surface_style_usage</B> to specify the sides of a
 * surface to which a surface style is applied. 
 *
 * <U>EXPRESS specification:</U>
 * \verbatim
  *)
  TYPE surface_side = ENUMERATION OF
        (positive,
         negative,
         both);
  END_TYPE;
  (*
 \endverbatim
 */
class surface_side : public ENUMERATION {
  public:

    enum
#if !defined(__DOXYGEN__)
    class
#endif 
    val {
      none = 0,
      /** The side of a surface which is in the same direction as the surface normal. */
      positive,
      /** The side of a surface which is in the opposite direction than the surface normal. */
      negative,
      /** Both sides. */
      both
    };

  private:

    val x_;

  public:

    // Конструктор
    surface_side(val v) : x_(v) {
    }

    // Получение значения
    val getval() const {
      return x_;
    }

   // Вывод значения типа
    std::string print_value() const {
      std::stringstream s;
      switch(x_) {
        case val::none:     s << "$";           break;
        case val::positive: s << ".POSITIVE."; break;
        case val::negative: s << ".NEGATIVE."; break;
        case val::both:     s << ".BOTH.";     break;
        default:            s << "";           break;
      }
      return s.str();
    }
};


/**
 * \brief TYPE size_select (ISO 10303-46:2021(E), 6.3.31)
 *
 * <B>6.3.31 size_select</B>
 * The <B>size_select</B> type is a list of alternate data types. It provides a mechanism to refer to an instance
 * of one of these data types. The <B>size_select</B> is used to specify the size of marker symbols or the width of curves.
 *
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  *)
  TYPE size_select = SELECT
     (positive_length_measure,
      measure_with_unit,
      descriptive_measure,
      pre_defined_size);
  END_TYPE;
  (* 
 \endverbatim
 *
 */
class size_select : public SELECT {

public:

  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(size_select, positive_length_measure);
  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(size_select, measure_with_unit);
  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(size_select, descriptive_measure);
//  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(size_select, pre_defined_size);
};



/**
 * \brief ENTITY pre_defined_curve_font (ГОСТ Р ИСО 10303-46-2002, 6.6.4)
 *
 * 6.6.4 Объект pre_defined_curve_font<BR>
 * Объект <B>pre_defined_curve_font</B> может быть использован для определения прикладных шрифтов кривой.
 *
 * <SMALL>Примечание - Порядок применения данного объекта задают в прикладных ресурсах или протоколах.</SMALL>
 *
 * <U>EXPRESS-спецификация</U>
 * \verbatim
  -- IN AP203e2/AP214/AP232/AP238 STEP-NC/AP242
  ENTITY pre_defined_curve_font
     SUBTYPE OF (pre_defined_item);
  END_ENTITY;
 \endverbatim
 *
 */
class pre_defined_curve_font : public pre_defined_item {

public:

  pre_defined_curve_font(const std::string &Name) : pre_defined_item(Name) {
  }

  virtual ~pre_defined_curve_font() {
  }
};


/**
 * \brief TYPE shading_surface_method (ISO 10303-46:2021(E), 6.3.30)
 *
 * <B>6.3.30 shading_surface_method</B><BR>
 * The <B>shading_surface_method</B> specifies the method which shall be used for the shading of surfaces.
 *
 * <SMALL><B>NOTE 1 </B>The descriptions of the different types of surface shading show that in some
 * cases the method involves interpolating results from the lighting, and in other case it involves
 * performing the reflectance calculation after interpolation. For this reason, the shading method
 * may be thought of as selecting a location in a display system's graphics pipeline where
 * interpolation takes place.<BR>
 * <B>NOTE 2 </B>The results of the shading methods should produce the effects according to the
 * enumerated item definitions. One particular case where the effects are difficult to define is
 * when the silhouette of a surface intersects itself or another silhouette of the same surface.
 * In this case, the effect is implementation-dependent.<BR>
 * <B>NOTE 3 </B>The shading methods correspond to those provided by PHIGS PLUS [10].</SMALL>
 *
 * <U>EXPRESS specification:</U>
 * \verbatim
  *)
  TYPE shading_surface_method = ENUMERATION OF
     (constant_shading,
      colour_shading,
      dot_shading,
      normal_shading);
  END_TYPE;
  (* 
 \endverbatim
 *
 * If the <B>surface_colour</B> is specified through a colour_specification, the interpolation of colours
 * shall be performed in the colour model of that specification. Otherwise the interpolation may be
 * performed in an arbitrary model.
 *
 * <SMALL><B>NOTE 4 </B>The result of colour interpolation depends on the colour model in which interpolation is performed.<BR>
 * <B>NOTE 5 </B>Examples of colour models are RGB, HSV, HLS.<BR>
 * <B>NOTE 6 </B> More information about colour models and colour interpolation can be found in [13], pp. 611-620.</SMALL>
 * 
 * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_shading_surface_method.html">Ссылка.</A>
 */
class shading_surface_method : public  ENUMERATION {

public:

  /** \brief Значение перечисляемого типа */
  enum class val {
    none = 0, //!!! ?
    /** \brief a reflectance calculation is performed for each facet of the approximated surface to produce one reflected colour per facet. The point on the facet used in the calculation is implementation-dependent. The colour used in the reflectance calculation is the surface_colour specified in the relevant surface_style_rendering entity. */
    constant_shading,
    /** \brief a reflectance calculation is performed at each vertex of each facet of the approximated product shape, using the surface_colour and the surface normals in the vertices. The resulting reflected colours are interpolated linearly across each facet. */
    colour_shading,
    /** \brief any dot products needed by the reflectance equation are calculated from surface normals at a set of positions on the surface. These dot products are interpolated linearly across the surface. The reflectance calculation is performed at each interpolated position of the surface to produce a reflected colour based on the interpolated dot products and the surface_colour of the relevant surface_style_rendering entity. */
    dot_shading,
    /** \brief the surface normals are interpolated linearly across the surface. The reflectance calculation is performed at each interpolated position of the surface to produce a reflected colour based on the interpolated surface normal and the surface_colour of the relevant surface_style_rendering entity. */
    normal_shading,
  };

private:

  val x_;

public:

  /** \brief Конструктор */
  shading_surface_method(val v) : x_(v) {
  }

  /** \brief Получение значения */
  val getval() const {
    return x_;
  }

  /** \brief Вывод значения типа */
  std::string print_value() const {
    std::stringstream s;
    switch (x_) {
      case val::none:             s << "$"; break;
      case val::constant_shading: s << ".CONSTANT_SHADING."; break;
      case val::colour_shading:   s << ".COLOUR_SHADING."; break;
      case val::dot_shading:      s << ".DOT_SHADING."; break;
      case val::normal_shading:   s << ".NORMAL_SHADING."; break;
    }
    return s.str();
  }
};

/**
 * \brief ENTITY styled_item (ГОСТ Р ИСО 10303-46-2002, 6.4.1)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  -- DIFF IN AP214
  -- DIFF IN AP203e2
  -- DIFF IN AP232
  -- IN AP203e2/AP214/AP232/AP238 STEP-NC/AP242
  ENTITY styled_item
     SUBTYPE OF (representation_item);
        styles : SET [0:?] OF presentation_style_assignment;
        item : styled_item_target;
     WHERE
        WR1:
           ((SIZEOF(styles) = 0) AND ('STEP_MERGED_AP_SCHEMA.STYLED_TESSELLATED_ITEM_WITH_COLOURS' IN TYPEOF(SELF)) OR (SIZEOF(styles) = 1)) OR (SIZEOF(styles) > 1) AND (SIZEOF(QUERY (pres_style <* styles| NOT ('STEP_MERGED_AP_SCHEMA.PRESENTATION_STYLE_BY_CONTEXT' IN TYPEOF(pres_style)))) = 0);
        wr2:
           NOT ('STEP_MERGED_AP_SCHEMA.STYLED_ITEM' IN TYPEOF(item));
        wr3:
           (('STEP_MERGED_AP_SCHEMA.MAPPED_ITEM' IN TYPEOF(item)) OR ('STEP_MERGED_AP_SCHEMA.GEOMETRIC_REPRESENTATION_ITEM' IN TYPEOF(item))) OR ('STEP_MERGED_AP_SCHEMA.CONTEXT_DEPENDENT_OVER_RIDING_STYLED_ITEM' IN TYPEOF(SELF));
  END_ENTITY;
 \endverbatim
 *
 */
class styled_item : public representation_item {

private:

  LIST<const presentation_style_assignment>* styles;
  const styled_item_target* item;

public:

  styled_item(const std::string &Name, const styled_item_target *Item) : representation_item(Name) {
    styles = new LIST<const presentation_style_assignment>();
    item = Item;
    add_attr_info(STEP_ATTR_LIST({
                                   {"styles", styles},
                                   {"item", item},
                                 }, this));
  }

  virtual ~styled_item() {
    delete styles;
  }

  void add_style(const presentation_style_assignment *presentation_style_assignment) {
    styles->push_back(presentation_style_assignment);
  }
};



/**
 * \brief ENTITY presentation_style_assignment  (ГОСТ Р ИСО 10303-46-2002, 6.4.4)
 *
 * <B>6.4.4 Объект presentation_style_assignment</B><BR>
 * Объект <B>presentation_style_assignment</B> представляет собой набор стилей, заданных в объекте
 * <B>герresentation_item</B> с целью представления конкретного элемента. Определения этих стилей влияют
 * только на вид элемента конкретного типа. Стиль поверхности связан только с поверхностями. Стили
 * области заполнения и кривой связаны только с кривыми и поверхностями. Стиль точки относится к
 * точкам, кривым и поверхностям. Стиль текста связан только с аннотируемым текстом. Стиль знаков
 * связан только со знаками.
 *
 * <SMALL><B>Пример 12 </B>- В случае задания для линии стиля кривой, его следует использовать. В случае задания для
 * линии стилей кривой и точки следует использовать оба стиля.</SMALL>
 *
 * <U>EXPRESS-спецификация:</U>
 * \verbatim
  -- DIFF IN AP232
  -- IN AP203e2/AP214/AP232/AP238 STEP-NC/AP242
  ENTITY presentation_style_assignment
     SUBTYPE OF (founded_item);
        styles : SET [1:?] OF presentation_style_select;
     WHERE
        WR1:
           SIZEOF(QUERY (style1 <* styles| NOT (SIZEOF(QUERY (style2 <* styles - style1| NOT ((TYPEOF(style1) <> TYPEOF(style2)) OR (SIZEOF([ 'STEP_MERGED_AP_SCHEMA.SURFACE_STYLE_USAGE', 'STEP_MERGED_AP_SCHEMA.EXTERNALLY_DEFINED_STYLE' ] * TYPEOF(style1)) = 1)))) = 0))) = 0;
        WR2:
           SIZEOF(QUERY (style1 <* styles| ('STEP_MERGED_AP_SCHEMA.SURFACE_STYLE_USAGE' IN TYPEOF(style1)))) <= 2;
        WR3:
           SIZEOF(QUERY (style1 <* styles| ('STEP_MERGED_AP_SCHEMA.SURFACE_STYLE_USAGE' IN TYPEOF(style1)) AND (SIZEOF(QUERY (style2 <* styles - style1| ('STEP_MERGED_AP_SCHEMA.SURFACE_STYLE_USAGE' IN TYPEOF(style2)) AND (((style1\surface_style_usage.side = both) OR (style2\surface_style_usage.side = both)) OR (style1\surface_style_usage.side = style2\surface_style_usage.side)))) > 0))) = 0;
  END_ENTITY;
\endverbatim
 *
 * <U>Формальные утверждения</U><BR>
 * <B>WR1</B> - один и тот же стиль не должен использоваться дважды, за исключением объектов
 * <B>extemally_defmed_style</B> и <B>surface_style_usage</B>;<BR>
 * <B>WR2</B> - в наборе стилей объект <B>surface_style_usage</B> не должен использоваться более двух раз.<BR>
 * <U>Неформальные утверждения</U><BR>
 * <B>IP1</B> - внешне определённый стиль не должен противоречить другим стилям того же объекта
 * <B>presentation_style_assignment</B>, включая другие внешне определённые стили.
 *
 * <SMALL>Ппримечание - При конфликте одного стиля с другим это связано с различными стилями описания
 * одинаковой характеристики (такой, как цвет или ширина). Например, для одного объекта могут быть заданы
 * два стиля цвета: синий или зелёный;</SMALL>
 *
 * <B>IP2</B> - тип каждого стиля должен быть уникальным;<BR>
 * <B>IP3</B> - если в наборе стилей имеются два экземпляра объекта <B>surface_style_usage</B>, каждый из
 * них должен определять стилизацию противоположных сторон поверхности.
 */
class presentation_style_assignment : public founded_item {

private:

  /** \brief Набор стилей представления, заданных в объекте <B>representation_item</B>. */
  SET<const presentation_style_select>* styles;

public:

  presentation_style_assignment() {
    styles = new SET<const presentation_style_select>();
    add_attr_info(STEP_ATTR_LIST({
                                   {"styles", styles},
                                 }, this));
  }

  virtual ~presentation_style_assignment() {
    delete styles;
  }

    void add_style(presentation_style_select *x) {
      styles->push_back(x);
    }
};


/**
 * \brief ENTITY draughting_pre_defined_curve_font (ISO 10303-46:2021(E), 6.4.19)
 *
 * <B>6.4.19 draughting_pre_defined_curve_font</B><BR>
 * A <B>draughting_pre_defined_curve_font</B> is a type of <B>pre_defined_curve_font</B>
 * that is identified by name.
 *
 * <U>EXPRESS specification:</U>
 * \verbatim
  -- IN AP203e2/AP214/AP232/AP238 STEP-NC/AP242
  ENTITY draughting_pre_defined_curve_font
     SUBTYPE OF (pre_defined_curve_font);
     WHERE
        WR1:
           SELF\pre_defined_item.name IN [ 'continuous', 'chain', 'chain double dash', 'dashed', 'dotted' ];
  END_ENTITY;
 \endverbatim
 *
 * <U>Formal propositions:</U><BR>
 * <B>WR1:</B> The name of the <B>draughting_pre_defined_curve_font</B> shall be ’continuous’, ’chain’,
 * ’chain double dash’, ’dashed’, or ’dotted’. 
 *
 */
class draughting_pre_defined_curve_font : public pre_defined_curve_font {

public:

  draughting_pre_defined_curve_font(const std::string& Name) : pre_defined_curve_font(Name) {
  }

  virtual ~draughting_pre_defined_curve_font() {
  }
};

/**
 * \brief ENTITY surface_style_reflectance_ambient (ISO 10303-46:2021(E), 6.4.58)
 *
 * <B>6.4.58 surface_style_reflectance_ambient</B><BR>
 * A <B>surface_style_reflectance_ambient</B> is a specification of the ambient part of the reflectance behaviour of a surface. 
 *
 * <U>EXPRESS specification:</U>
 * \verbatim
  *)
  ENTITY surface_style_reflectance_ambient;
    ambient_reflectance : REAL;
  END_ENTITY;  (*
 \endverbatim
 *
 * <SMALL><B>NOTE 1 </B> The reflectance calculation is conceptually applied at one or more points on a surface
 * being lit and shaded and produces a colour at such points. Input to the reflectance calculation includes the
 * position at which the reflectance equation is to be applied, the surface normal, the surface colour at that
 * position, the light sources, and the three-dimensional camera model.<BR>
 * <B>NOTE 2 </B>Suggested reflectance equations can be found in Annex E.</SMALL>
 *
 * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_surface_style_reflectance_ambient.html">Ссылка.</A>
 */
class surface_style_reflectance_ambient : public STEP_ENTITY {

private:

  /** \brief The reflectance coefficient for the ambient part of the reflectance equation. */
  REAL *ambient_reflectance;

public:

  surface_style_reflectance_ambient(const REAL& Ambient_reflectance) {
    ambient_reflectance = new REAL(Ambient_reflectance);
    add_attr_info(STEP_ATTR_LIST({
                                   {"ambient_reflectance", ambient_reflectance}
                                 }, this));
  }

  /** \brief Деструктор. */
  virtual ~surface_style_reflectance_ambient() {
    delete ambient_reflectance;
  }
};

/**
 * \brief ENTITY surface_style_rendering (ISO 10303-46:2021(E), 6.4.61)
 *
 * <B>6.4.61 surface_style_rendering</B><BR>
 * A <B>surface_style_rendering</B> is the realistic visualization of surfaces by use of rendering techniques.
 * The effect of the reflectance calculation shall be as if the calculation is performed in the coordinate-system
 * in which the camera_model is founded.
 *
 * <U>EXPRESS specification:</U>
 * \verbatim
  *)
  ENTITY surface_style_rendering;
    rendering_method : shading_surface_method;
    surface_colour : colour;
  END_ENTITY;
  (*
 \endverbatim
 *
 * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_surface_style_rendering.html">Ссылка.</A>
 */
class surface_style_rendering : public STEP_ENTITY {

private:

  /** \brief The method for interpolating colours across surfaces. */
  const shading_surface_method* rendering_method; 

  /** \brief The colour used to render the surface. */
  const colour* surface_colour;

public:

  surface_style_rendering(const shading_surface_method& Rendering_method, colour* Surface_colour);

  virtual ~surface_style_rendering();
};

/**
 * \brief ENTITY surface_style_rendering_with_properties (ISO 10303-46:2021(E), 6.4.62)
 *
 * <B>6.4.62 surface_style_rendering_with_properties</B><BR>
 * A <B>surface_style_rendering_with_properties</B> is a type of <B>surface_style_rendering</B>.
 * A <B>surface_style_rendering_with_properties</B> allows the realistic visualization of surfaces
 * with properties which determine transparency and reflection characteristics.
 *
 * <U>EXPRESS specification:</U>
 * \verbatim
  *)
  ENTITY surface_style_rendering_with_properties
    SUBTYPE OF (surface_style_rendering);
    properties : SET[1:2] OF rendering_properties_select;
  WHERE
    WR1: (HIINDEX(properties) = 1) XOR (TYPEOF(properties[1]) <> TYPEOF(properties[2]));
  END_ENTITY;
  (*
 \endverbatim
 *
 * <U>Formal propositions:</U><BR>
 * <B>WR1: </B>All of the properties shall be of different types. 
 *
 * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_surface_style_rendering_with_properties.html">Ссылка.</A>
 */
class surface_style_rendering_with_properties : public surface_style_rendering {

private:

  /** \brief The collection of rendering properties for a surface. */
  SET<rendering_properties_select>* properties;

public:
 
  /**
   * \brief Конструктор.
   *
   */
  surface_style_rendering_with_properties(const shading_surface_method& Rendering_method, colour* Surface_colour);

  /** \brief Деструктор. */
  virtual ~surface_style_rendering_with_properties();

  void add_properties(rendering_properties_select* t) {
    properties->push_back(t);
  }
};

/**
 * \brief ENTITY surface_style_transparent (ISO 10303-46:2021(E), 6.4.65)
 *
 * <B>6.4.65 surface_style_transparent</B><BR>
 * A <B>surface_style_transparent</B> is the surface rendering property that specifies the degree
 * of transparency of a surface.
 *
 * <U>EXPRESS specification:</U>
 * \verbatim
  *)
  ENTITY surface_style_transparent;
    transparency : REAL;
  WHERE
    WR1: {0.0 <= transparency <= 1.0};
  END_ENTITY;
  (*
 \endverbatim
 *
 * <U>Formal propositions:</U><BR>
 * <B>WR1: </B>The transparency shall be between 0.0 and 1.0. 
 *
 * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_surface_style_transparent.html">Ссылка.</A>
 */
class surface_style_transparent : public STEP_ENTITY {

private:

  /** \brief The degree of transparency indicated by the percentage of light traversing the surface. */
  REAL *transparency;

public:

  surface_style_transparent(const REAL& Transparency) {
    transparency = new REAL(Transparency);
    add_attr_info(STEP_ATTR_LIST({
                                   {"transparency", transparency}
                                 }, this));
  }

  /** \brief Деструктор. */
  virtual ~surface_style_transparent() {
    delete transparency;
  }
};

/**
 * \brief ENTITY curve_style (ГОСТ Р ИСО 10303-46-2002, 6.6.1)
 *
 * 6.6.1 Объект curve_style<BR>
 * Объект <B>curve_style</B> определяет визуальный вид кривой.
 *
 * <U>EXPRESS-спецификация</U>
 * \verbatim
  -- DIFF IN AP214
  -- DIFF IN AP203e2
  -- DIFF IN AP232
  -- IN AP203e2/AP214/AP232/AP238 STEP-NC/AP242
  ENTITY curve_style
     SUBTYPE OF (founded_item);
        name : label;
        curve_font : OPTIONAL curve_font_or_scaled_curve_font_select;
        curve_width : OPTIONAL size_select;
        curve_colour : OPTIONAL colour;
     WHERE
        WR1:
           (EXISTS(curve_font) OR EXISTS(curve_width)) OR EXISTS(curve_colour);
  END_ENTITY;
 \endverbatim
 *
 */
class curve_style  : public founded_item {

private:

  /** \brief Слово или группа слов, посредством которых ссылаются на <B>curve_style</B> */
  label *name;
  /**
   * \brief Объект <B>curve_style_font</B>, масштабированный объект <B>curve_style_font</B>,
   * объект <B>рге_defined_curve_font</B>, масштабированный объект <B>pre_defined_curve_font</B>,
   * объект <B>externally_defined_curve_font</B> или масштабированный <B>extemally_defined_curve_font</B>,
   * используемые для представления кривой.
   */
  const curve_font_or_scaled_curve_font_select* curve_font;
  /** \brief Ширина (толщина) видимой части представленной кривой, выраженная в единицах объекта <B>presentation_area</B>. */
  const size_select* curve_width;
  /** \brief Цвет видимой части кривой. */
  const colour* curve_colour;

public:

  curve_style(
    const std::string &Name,
    const curve_font_or_scaled_curve_font_select *Font = nullptr,
    const size_select *Width = nullptr,
    const colour *Colour = nullptr);

  virtual ~curve_style();};

/**
 * \brief ENTITY fill_area_style (ГОСТ Р ИСО 10303-46-2002, 6.7.1)
 *
 * 6.7.1 Объект  fill_area_style<BR>
 * Объект <B>fill_area_style</B> задает стиль для заполнения видимых сегментов кривой, аннотируемых
 * заполняемых областей или поверхностей в виде ячеек или штриховки.<BR>
 * <U>EXPRESS-спецификация</U>
 * \verbatim
  -- DIFF IN AP232
  -- IN AP203e2/AP214/AP232/AP238 STEP-NC/AP242
  ENTITY fill_area_style
     SUBTYPE OF (founded_item);
        name : label;
        fill_styles : SET [1:?] OF fill_style_select;
     WHERE
        WR1:
           SIZEOF(QUERY (fill_style <* fill_styles| ('STEP_MERGED_AP_SCHEMA.FILL_AREA_STYLE_COLOUR' IN TYPEOF(fill_style)))) <= 1;
  END_ENTITY;
 \endverbatim
 *
 * <U>Формальное утверждение</U><BR>
 * <B>WR1</B> - в наборе объектов <B>fill_styles</B> не должно быть более одного объекта <B>fill_area_style_colour</B>.
 */
class fill_area_style : public founded_item {

private:

  /** \brief Слово или группа слов, посредством которых сслаются на <B>fill_area_style</B>. */
  label* name;
  /**
   * \brief Набор стилей заполнения областей для представления видимых сегментов кривой,
   * аннотируемых заполняемых областей или поверхностей.
   */
  LIST<const fill_style_select>* fill_styles;

public:

  // Конструктор
  fill_area_style(const std::string &Name) {
    name = new label(Name);
    fill_styles = new LIST<const fill_style_select>();
    add_attr_info(STEP_ATTR_LIST({
                                   {"name", name},
                                   {"fill_styles", fill_styles},
                                 }, this));
    }

  virtual ~fill_area_style() {
    delete fill_styles;
    delete name;
  }

  void add_style(const fill_style_select *x) {
    fill_styles->push_back(x);
  }
};

/**
 * \brief ENTITY fill_area_style_colour (ГОСТ Р ИСО 10303-46-2002, 6.7.2)
 *
 * 6.7.2 Объект fill_area_style_colour<BR>
 * Объект <B>fill_area_style_colour</B> определяет цвет, используемый для сплошного заполнения
 * видимых сегментов кривой, аннотируемых заполняемых областей или поверхностей.<BR>
 * <U>EXPRESS-спецификация</U>
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  -- IN AP203e2/AP214/AP232/AP238 STEP-NC/AP242
  ENTITY fill_area_style_colour;
     name: label;
     fill_colour: colour;
  END_ENTITY;
 \endverbatim
 *
 */
class fill_area_style_colour : public STEP_ENTITY {

private:

  /** \brief Слово или группа слов, посредством которых ссылаются на <B>fill_area_style_colour</B> */
  label* name;
  /** \brief Цвет, используемый для заливки конкретной области */
  const colour* fill_colour;

public:

  fill_area_style_colour(const std::string &Name, const colour_rgb *Fill_colour);

  virtual ~fill_area_style_colour();};


/**
 * \brief ENTITY \ref colour (ГОСТ Р ИСО 10303-46-2002, 7.3.10)
 *
 * 7.3.10 Объект \ref colour <BR>
 * Объект <B>\ref colour</B> определяет основное свойство конкретного элемента, связанное с его
 * способностью отражать световой поток.<BR>
 * <U>EXPRESS-спецификация</U>
 * \verbatim
  -- IN AP203e2/AP214/AP232/AP238 STEP-NC/AP242
  ENTITY colour;
  END_ENTITY; 
 \endverbatim
 *
 */
class colour : public STEP_ENTITY {

public:

  colour() {
    add_attr_info(STEP_ATTR_LIST({
                                   { }
                                 }, this));
  }

  virtual ~colour() {
  }

};

/**
 * \brief ENTITY \ref colour_specification (ГОСТ Р ИСО 10303-46-2002, 7.3.11)
 *
 * 7.3.11 Объект \ref colour_specification <BR>
 * Объект <B>\ref colour_specification</B> определяет цвет, прямо связанный с заданным цветовым
 * интервалом (пространством).
 * <BR><SMALL>Пример 18 —  Цветовыми пространствами являются RGB, HLS, HSV и CIE.  Более подробно эти
 * вопросы рассмотрены в [7].<BR>
 * Примечание - В настоящем стандарте использованы только цвета модели RGB. Данная модель
 * может быть расширена.</SMALL><BR>
 * <U>EXPRESS-спецификация</U>
 * \verbatim
  -- IN AP203e2/AP214/AP232/AP238 STEP-NC/AP242
  ENTITY colour_specification
     SUBTYPE OF (colour);
        name : label;
  END_ENTITY; 
 \endverbatim
 *
 */
class colour_specification : public colour {

private:

  /** \brief Слово или группа слов, посредством которых ссылаются на <B>colour_specification</B> */
  label *name;

public:

  colour_specification(const std::string &Name) {
    name = new label(Name);
    add_attr_info(STEP_ATTR_LIST({
                                   {"name", name}
                                 }, this));
  }

  virtual ~colour_specification() {
    delete name;
  }
};

/**
 * \brief ENTITY \ref colour_rgb (ГОСТ Р ИСО 10303-46-2002, 7.3.12)
 *
 * 7.3.12 Объект \ref colour_rgb <BR>
 * Объект <B>\ref colour_rgb</B> определяет цвет посредством задания яркости красного, зеленого
 * и синего цветов.<BR>
 * <U>EXPRESS-спецификация</U>
 * \verbatim
  -- IN AP203e2/AP214/AP232/AP238 STEP-NC/AP242
  ENTITY colour_rgb
     SUBTYPE OF (colour_specification);
        red : REAL;
        green : REAL;
        blue : REAL;
     WHERE
        WR1:
           (0.0 <= red) AND (red <= 1.0);
        WR2:
           (0.0 <= green) AND (green <= 1.0);
        WR3:
           (0.0 <= blue) AND (blue <= 1.0);
  END_ENTITY;
 \endverbatim
 *
 */
class colour_rgb : public colour_specification {

private:
  /** \brief <B>red</B> — яркость красного компонента цвета */
  REAL *red;
  /** \brief <B>green</B> — яркость зелёного компонента цвета */
  REAL *green;
  /** \brief <B>blue</B> — яркость синего компонента цвета */
  REAL *blue;

public:

  colour_rgb(const std::string& Name, double Red, double Green, double Blue) :
    colour_specification(Name) {
    red = new REAL(Red);
    green = new REAL(Green);
    blue = new REAL(Blue);
    add_attr_info(STEP_ATTR_LIST({
                                    {"red", red},
                                    {"green", green},
                                    {"blue", blue},
                                 }, this));
  }

  virtual ~colour_rgb() {
    delete blue;
    delete green;
    delete red;
  }
};


/**
 * \brief ENTITY surface_style_usage (ГОСТ Р ИСО 10303-46-2002, 6.8.1)
 *
 * 6.8.1 Тип surface_style_usage<BR>
 * Объект <B>surface_style_usage</B> определяет использование объекта <B>surface_side_style_select</B> для
 * лицевой, оборотной или обеим сторонам поверхности.<BR>
 * <U>EXPRESS-спецификация</U>
 * \verbatim
  -- DIFF IN AP232
  -- IN AP203e2/AP214/AP232/AP238 STEP-NC/AP242
  ENTITY surface_style_usage
     SUBTYPE OF (founded_item);
        side : surface_side;
        style : surface_side_style_select;
  END_ENTITY;
 \endverbatim
 *
 */
class surface_style_usage : public founded_item {

private:

  /** \brief Определяет сторону поверхности, для которой используют заданный стиль. */
  surface_side* side;
  /** \brief Стиль, который следует использовать при описании поверхности. */
  const surface_side_style_select* style;

public:
 
  surface_style_usage(surface_side::val Side, const surface_side_style_select *Style) {
    side = new surface_side(Side);
    style = Style;
    add_attr_info(STEP_ATTR_LIST({
                                   {"side", side},
                                   {"style", style},
                                 }, this));
  }

  virtual ~surface_style_usage() {
    delete side;
  }
};

/**
 * \brief ENTITY surface_side_style (ГОСТ Р ИСО 10303-46-2002, 6.8.3)
 *
 * 6.8.3 Объект surface_side_style<BR>
 * Объект <B>surface_side_style</B> представляет собой набор (коллекцию) стилей, используемых при
 * представлении конкретной стороны поверхности.<BR>
 * <U>EXPRESS-спецификация</U>
 * \verbatim
  -- DIFF IN AP232
  -- IN AP203e2/AP214/AP232/AP238 STEP-NC/AP242
  ENTITY surface_side_style
     SUBTYPE OF (founded_item);
        name : label;
        styles : SET [1:7] OF surface_style_element_select;
     WHERE
        WR1:
           SIZEOF(QUERY (style1 <* styles| (SIZEOF(QUERY (style2 <* styles - style1| (TYPEOF(style1) = TYPEOF(style2)))) > 0))) = 0;
  END_ENTITY;
 \endverbatim
 *
 * <U>Формальное утверждение</U><BR>
 * <B>WR1</B> - все стили должны быть различных типов.
 */
class surface_side_style  : public founded_item {

private:

  /** \brief Слово или группа слов, посредством которых ссылаются на <B>surface_side_style</B>. */
  label* name;
  /** \brief Набор (коллекция) различных стилей поверхности. */
  SET<const surface_style_element_select>* styles;

public:

  surface_side_style(const std::string &Name) {
    name = new label(Name);
    styles = new SET<const surface_style_element_select>();
    add_attr_info(STEP_ATTR_LIST({
                                   {"name", name},
                                   {"styles", styles},
                                 }, this));
  }

  virtual ~surface_side_style() {
    delete styles;
    delete name;
  }

  void add_style(surface_style_element_select *x) {
    styles->push_back(x);
  }
};

/**
 * \brief ENTITY surface_style_fill_area (ГОСТ Р ИСО 10303-46-2002, 6.8.4)
 *
 * 6.8.4 Объект surface_style_fill_area<BR>
 * Объект <B>surface_style_fill_area</B> определяет стиль поверхности при отображении на неё
 * заполня­емой области.<BR>
 * <U>EXPRESS-спецификация</U>
 * \verbatim
  -- DIFF IN AP232
  -- IN AP203e2/AP214/AP232/AP238 STEP-NC/AP242
  ENTITY surface_style_fill_area
     SUBTYPE OF (founded_item);
        fill_area : fill_area_style;
  END_ENTITY;
 \endverbatim
 *
 */
class surface_style_fill_area : public founded_item {

private:

  /**
   * \brief Объект <B>flll_area_style</B>, связанный с двумерным параметризованным пространством
   * поверхности и отображаемый на эту поверхность.
   */
  fill_area_style *fill_area;

public:

  surface_style_fill_area(fill_area_style *Fill_area) {
    fill_area = Fill_area;
    add_attr_info(STEP_ATTR_LIST({
                                   {"fill_area", fill_area},
                                 }, this));
  }

  virtual ~surface_style_fill_area() {
  }
};


/**
 * \brief ENTITY presentation_representation (ISO 10303-46:2021(E), 4.4.26)
 *
 * <B>4.4.26 presentation_representation</B>
 * A <B>presentation_representation</B> is a type of representation. A <B>presentation_representation</B> represents
 * the definition of the picture to be generated by a system which displays the presentation information. The picture
 * refers to an object which may consist of two-dimensional geometry, three-dimensional geometry, and annotation.
 * The reference to geometry and annotation is made indirectly by building a hierarchy of <B>presentation_representations.</B>
 * Lower levels of this hierarchy are constrained to contain only geometry or annotation. A <B>presentation_representation</B>
 * may be either a <B>area_dependent_annotation_representation</B> or a <B>presentation_area</B> or a <B>presentation_view</B>
 * or a <B>product_data_representation_view</B> or a <B>view_dependent_annotation_representation</B>.
 *
 * <U>EXPRESS specification:</U>
 * \verbatim
  --DIFF IN AP232
  -- IN AP203e2 / AP214 / AP232 / AP238 STEP - NC / AP242
  ENTITY presentation_representation
    SUPERTYPE OF (ONEOF (area_dependent_annotation_representation,
                         presentation_area,
                         presentation_view,
                         product_data_representation_view,
                         view_dependent_annotation_representation))
    SUBTYPE OF (representation);
    SELF\representation.context_of_items : geometric_representation_context;
  WHERE
    WR1: SELF\representation. context_of_items\geometric_representation_context. coordinate_space_dimension = 2;
    WR2: ('PRESENTATION_ORGANIZATION_SCHEMA.PRESENTATION_AREA' IN TYPEOF (SELF)) OR (SIZEOF (QUERY (prr <* USEDIN (SELF, 'REPRESENTATION_SCHEMA.' + 'REPRESENTATION_RELATIONSHIP.REP_2') | 'PRESENTATION_ORGANIZATION_SCHEMA.PRESENTATION_REPRESENTATION' IN TYPEOF (prr\representation_relationship.rep_1))) > 0) OR (SIZEOF(QUERY( rm <* USEDIN(SELF, 'REPRESENTATION_SCHEMA.'+ 'REPRESENTATION_MAP.'+ 'MAPPED_REPRESENTATION') | SIZEOF(QUERY( mi <* USEDIN(rm, 'REPRESENTATION_SCHEMA.'+ 'MAPPED_ITEM.'+ 'MAPPING_SOURCE') | SIZEOF(QUERY( rep <* using_representations (mi) | 'PRESENTATION_ORGANIZATION_SCHEMA.'+ 'PRESENTATION_REPRESENTATION' IN TYPEOF (rep))) > 0 )) > 0)) > 0);
  END_ENTITY;
 \endverbatim
 *
 * <U>Formal propositions:</U><BR>
 * <B>WR1:</B> The picture shall have a dimensionality of 2.<BR>
 * <B>WR2:</B> A <B>presentation_representation</B> shall either be included in another <B>presentation_representation</B>
 * or it shall be a <B>presentation_area</B>.
 *
 * <A HREF="https://www.steptools.com/stds/stp_aim/html/t_presentation_representation.html">Ссылка.</A>
 */
class presentation_representation : public representation {
public:

  /**
   * \brief Конструктор.
   * 
   * \param [in] Name
   * \param [in] Context_of_items A geometric_representation_context in which the items of this
   * <B>presentation_representation</B> are related to form a representation of some concept.
   */
  presentation_representation(const std::string& Name, const representation_context* Context_of_items) :
    representation(Name, Context_of_items) {
    add_attr_info(STEP_ATTR_LIST({
                                   {}
      }, this));
  }

  /** \brief Деструктор. */
  virtual ~presentation_representation() {
  }
};


/**
 * \brief TYPE layered_item (ГОСТ Р ИСО 10303-46-2002, 4.3.4)
 *
 * 4.3.4 Тип layered_item<BR>
 * Тип <B>layered_item</B> определяет элементы, сгруппированные в уровнях посредством объекта
 * <B>presentation_layer_assigment</B>
 *
 * <U>EXPRESS-спецификация</U>
 * \verbatim
  --IN AP203e2 / AP214 / AP232 / AP238 STEP - NC / AP242
  TYPE layered_item = SELECT
  (presentation_representation,
    representation_item);
  END_TYPE;
   \endverbatim
 *
 */
class layered_item : public SELECT {

public:

//  STEP_TYPE_SELECT_CONSTRUCTOR(layered_item, presentation_representation)
//  STEP_TYPE_SELECT_CONSTRUCTOR(layered_item, representation_item)

  // Автоматическое преобразование к выбираемому типу
  layered_item(const presentation_representation* t) : SELECT(t) {
  }

  layered_item(const representation_item* t) : SELECT(t) {
  }

  // Преобразование выбираемого типа к одному из состоавляющих типов
  operator const presentation_representation* () const {
    return dynamic_cast<const presentation_representation*>(get_value());
  }

  operator const representation_item* () const {
    return dynamic_cast<const representation_item*>(get_value());
  }

//!!! Операторы присвоения????
  layered_item& operator=(const presentation_representation& t) {
    set_value(&t);
    return *this;
  }
  layered_item& operator=(const representation_item& t) {
    set_value(&t);
    return *this;
  }

  // Проверка принадлежности к выбранному типу
  bool is_presentation_representation() const {
    return get_step_name().compare("PRESENTATION_REPRESENTATION") == 0 ? true : false;
  }
  bool is_representation_item() const {
    return get_step_name().compare("REPRESENTATION_ITEM") == 0 ? true : false;
  }

  // Получение имени типа наследуется

  // Конструктор по умолчанию - наследовать?
  layered_item() : SELECT(nullptr) {
  }
};

/**
 * \brief ENTITY presentation_layer_assignment (ISO 10303-46:2021(E), 4.4.24)
 *
 * <B>4.4.24 presentation_layer_assignment</B><BR>
 * A <B>presentation_layer_assignment</B> is assignment of an identifier to a set of <B>presentation_representations</B>
 * or <B>representation_items</B>. This set contains the pictures, or elements of pictures, that are assigned to a layer.
 * A <B>representation_item</B> that is assigned to a layer shall be a <B>styled_item</B>, or shall be defined by one or
 * more styled_items. In the case of a <B>presentation_representation</B>, the assignment also associates the layer
 * identifier with each styled <B>representation_item</B> that is contained in or referenced by that
 * <B>presentation_representation</B>, unless this assignment is over-ridden by a <B>representation_item_dependent_layer_assignment</B>.
 * In the case of a <B>representation_item</B>, the assignment also associates the layer
 * identifier with each styled <B>representation_item</B> that is referenced directly
 * or indirectly by that item, unless this assignment is over-ridden by a <B>representation_item_dependent_layer_assignment</B>.
 *
 * <SMALL><B>NOTE</B> This assignment is for the purpose of determining visibility and style in a picture
 * represented by a <B>presentation_representation</B> through the use of the <B>presentation_layer_usage</B> entity.</SMALL>
 *
 * <U>EXPRESS specification:</U>
 * \verbatim
  -- IN AP203e2/AP214/AP238 STEP-NC/AP242
  ENTITY presentation_layer_assignment;
        name : label;
        description : text;
        assigned_items : SET [1:?] OF layered_item;
  END_ENTITY;
 \endverbatim
 *
 */
class presentation_layer_assignment : public STEP_ENTITY {

private:

  /** \brief The word, or group of words, by which the layer defined by the <B>presentation_layer_assignment</B> is referred to. */
  label* name;
  /** \brief Text that relates the nature of the presentation_layer_assignment. */
  text* description;
  /** \brief The set of items assigned to the layer defined by the <B>presentation_layer_assignment</B>.  */
  SET<const layered_item>* assigned_items;

public:

  /**
   * \brief Конструктор.
   * \param [in] Name The word, or group of words, by which the layer defined by the <B>presentation_layer_assignment</B> is referred to.
   * \param [in] Description Text that relates the nature of the presentation_layer_assignment.
   */
  presentation_layer_assignment(const std::string& Name, const std::string& Description) {
    name = new label(Name);
    description = new text(Description);
    assigned_items = new SET<const layered_item>();
    add_attr_info(STEP_ATTR_LIST({
                                   {"name",           name},
                                   {"description",    description},
                                   {"assigned_items", assigned_items},
                                 }, this));
  }

  /** \brief Деструктор. */
  virtual ~presentation_layer_assignment() {
    delete assigned_items;
    delete description;
    delete name;
  }

};


}
