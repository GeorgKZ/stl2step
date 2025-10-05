/**
 * \file
 *
 * \brief Заголовочный файл с определениями классов, соответствующих ISO 10303-42:2021(E).
 */

namespace express {

/**
 * \brief ENTITY geometric_representation_item (ISO 10303-42:2003, 4.4.2)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  -- DIFF IN AP214
  -- DIFF IN AP203e2
  -- DIFF IN AP238 STEP-NC
  -- DIFF IN AP224
  -- DIFF IN AP232 
  ENTITY geometric_representation_item
     SUPERTYPE OF ((((((ONEOF(point, direction, vector, placement, cartesian_transformation_operator, curve, surface, edge_curve, face_surface, poly_loop, vertex_point, solid_model, boolean_result, sphere, right_circular_cone, right_circular_cylinder, torus, block, primitive_2d, right_angular_wedge, ellipsoid, faceted_primitive, rectangular_pyramid, cyclide_segment_solid, volume, half_space_solid, shell_based_surface_model, face_based_surface_model, shell_based_wireframe_model, edge_based_wireframe_model, geometric_set, tessellated_item, volume_with_faces, scanned_data_item) ANDOR ONEOF(annotation_fill_area, curve, point, text_literal)) ANDOR ONEOF(camera_model, curve, direction)) ANDOR ONEOF(curve, externally_defined_hatch_style, externally_defined_tile_style, fill_area_style_hatching, fill_area_style_tile_symbol_with_style, fill_area_style_tiles, one_direction_repeat_factor, point, vector)) ANDOR ONEOF(curve, planar_extent)) ANDOR ONEOF(kinematic_path, placement)) ANDOR ONEOF(rotation_about_direction, su_parameters))
     SUBTYPE OF (representation_item);
     DERIVE
        dim : dimension_count := dimension_of(SELF);
     WHERE
        WR1:
           SIZEOF(QUERY (using_rep <* using_representations(SELF)| NOT ('STEP_MERGED_AP_SCHEMA.GEOMETRIC_REPRESENTATION_CONTEXT' IN TYPEOF(using_rep.context_of_items)))) = 0;
  END_ENTITY;
 \endverbatim
 */
class geometric_representation_item : virtual public representation_item {
public:

  geometric_representation_item(const std::string &Name);

  virtual ~geometric_representation_item();
};


/**
* \brief TYPE dimension_count (ISO 10303-42, 4.3.2)
*
* <B>Определение объекта на языке EXPRESS:</B>
*\verbatim
  TYPE dimension_count = INTEGER;
     WHERE
        WR1:
           SELF > 0;
  END_TYPE;
 \endverbatim
 *
 * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_dimension_count.html">Ссылка.</A>
 */
class dimension_count : public INTEGER {
  public:

    // Конструктор
    dimension_count() : INTEGER() {
    }

    // Конструктор
    dimension_count(const int v) : INTEGER(v) {
      assert(*this > 0);
    }

    // Конструктор
    dimension_count(const size_t v) : INTEGER(v) {
      assert(*this > 0);
    }

    virtual STEP_OBJTYPE objtype() const {
      return STEP_OBJTYPE::TYPE_DEFINED;
    }
};


/**
 * \brief TYPE axis2_placement (ISO 10303-42:2003(E), 4.3.10)
 *
 * <B>4.3.10 axis2_placement</B><BR>
 * This select type represents the placing of mutually perpendicular axes in two-dimensional or
 * in threedimensional Cartesian space.
 *
 * <SMALL><B>NOTE</B> This select type enables entities requiring axis placement information
 * to reference the axes without specifying the space dimensionality.</SMALL>
 *
 * <U>EXPRESS specification:</U>
 * \verbatim
  *)
  TYPE axis2_placement = SELECT
        (axis2_placement_2d,
         axis2_placement_3d);
  END_TYPE;
  (*
 \endverbatim
 *
 */
class axis2_placement : public SELECT {

public:

//  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(axis2_placement, axis2_placement_2d);
  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(axis2_placement, axis2_placement_3d);
};

/**
 * \brief TYPE pcurve_or_surface (ISO 10303-42:2003(E), 4.3.12)
 *
 * <B>4.3.12 pcurve_or_surface</B>
 * This select type enables a surface curve to identify as an attribute the associated surface or pcurve.
 *
 * <U>EXPRESS specification:</U>
 * \verbatim
  *)
  TYPE pcurve_or_surface = SELECT
        (pcurve,
         surface);
  END_TYPE;
  (*
 \endverbatim
 *
 * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_pcurve_or_surface.html">Ссылка.</A>
 */
class pcurve_or_surface : public SELECT {

public:

//  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(pcurve_or_surface, pcurve);
//  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(pcurve_or_surface, surface);
};


/**
 * \brief TYPE vector_or_direction (ISO 10303-42-2003, 4.3.15)
 *
 * <B>4.3.15 vector_or_direction</B><BR>
 * This type is used to identify the types of entity which can participate in vector computations.
 *
 * <U>EXPRESS specification:</U>
 * \verbatim
  -- DIFF IN AP214
  -- DIFF IN AP203e2
  -- DIFF IN AP224
  -- DIFF IN AP232
  TYPE vector_or_direction = SELECT
        (direction,
         vector);
  END_TYPE;
 \endverbatim
 *
 * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_vector_or_direction.html">Ссылка.</A>
 */
class vector_or_direction : public SELECT {

public:

  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(vector_or_direction, vector);
  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(vector_or_direction, direction);
};


/**
 * \brief ENTITY geometric_representation_context (ISO 10303-42:2003, 4.4.1)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  -- DIFF IN AP214
  -- DIFF IN AP203e2
  -- DIFF IN AP224
  -- DIFF IN AP232
  ENTITY geometric_representation_context
     SUPERTYPE OF (ONEOF(geometric_representation_context_with_parameter, path_parameter_representation_context))
     SUBTYPE OF (representation_context);
        coordinate_space_dimension : dimension_count;
  END_ENTITY;
 \endverbatim
 *
 */
class geometric_representation_context : public representation_context {

private:

  const dimension_count* coordinate_space_dimension;

public:

  /** \brief Конструктор */
  geometric_representation_context(const std::string& Identifier, const std::string& Type, const dimension_count& Dimension);

  /** \brief Деструктор */
  virtual ~geometric_representation_context();
};

/**
 * \brief ENTITY vector (ISO 10303-42:2003, 4.4.15)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  ENTITY vector
     SUBTYPE OF (geometric_representation_item);
        orientation : direction;
        magnitude : length_measure;
     WHERE
        WR1:
           magnitude >= 0.0;
  END_ENTITY;
 \endverbatim
 *
 */
class vector : public geometric_representation_item {

private:

  /** \brief Направление <B>vector</B> */
  const direction* orientation;
  /**
   * \brief Длина <B>vector</B>
   *
   * Все векторы с нулевым значением <B>magnitude</B> считаются равными независимо от значения атрибута <B>orientation</B>.
   */
  length_measure* magnitude;

public:

  /**
   * \brief Конструктор
   */
  vector(const std::string &Name, const direction* Orientation, const length_measure &Magnitude);

  /** \brief Деструктор */
  virtual ~vector();

  /** \brief FUNCTION dimension_of */
  dimension_count dimension_of(void) const;
};

/**
 * \brief ENTITY curve (ISO 10303-42:2003, 4.4.23)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  -- DIFF IN AP214
  -- DIFF IN AP203e2
  -- DIFF IN AP224
  -- DIFF IN AP232
  ENTITY curve
     SUPERTYPE OF (ONEOF(line, conic, clothoid, circular_involute, pcurve, surface_curve, offset_curve_2d, offset_curve_3d, curve_replica))
     SUBTYPE OF (geometric_representation_item);
  END_ENTITY;
 \endverbatim
 *
 */
class curve : public geometric_representation_item {

public:

  // Конструктор
  curve(const std::string &Name) :
      representation_item(Name),
      geometric_representation_item(Name) {
  }

  virtual ~curve() {
  }
};


/**
 * \brief ENTITY line (ISO 10303-42:2003, 4.4.24)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  ENTITY line
     SUBTYPE OF (curve);
        pnt : cartesian_point;
        dir : vector;
     WHERE
        WR1:
           dir.dim = pnt.dim;
  END_ENTITY;
 \endverbatim
 *
 */
class line : public curve {

private:
    
  const cartesian_point *pnt; // Начальная точка
  const vector          *dir; // Вектор от начальной точки до конечной

public:

  /** \brief Констуктор */
  line(const std::string &Name, const cartesian_point *Pnt, const vector *Dir);

  /** \brief Деструктор */
  virtual ~line();
};



/**
 * \brief ENTITY point (ISO 10303-42:2003, 4.4.3)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  -- DIFF IN AP214
  -- DIFF IN AP203e2
  -- DIFF IN AP224
  -- DIFF IN AP232
  ENTITY point
     SUPERTYPE OF (ONEOF(cartesian_point, point_on_curve, point_on_surface, point_in_volume, point_replica, degenerate_pcurve))
     SUBTYPE OF (geometric_representation_item);
  END_ENTITY;
 \endverbatim
 */
class point : public geometric_representation_item {

public:

  // Конструктор
  point(const std::string &Name) : 
    representation_item(Name),
    geometric_representation_item(Name) {
  }

  // Сравнение "меньше"
  bool operator<(const point& p) const;

  // Сравнение "равно"
  bool operator==(const point& vp) const;
};

/**
 * \brief ENTITY cartesian_point (ISO 10303-42:2003, 4.4.4)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  ENTITY cartesian_point
    SUPERTYPE OF(ONEOF(cylindrical_point, polar_point, spherical_point))
    SUBTYPE OF(point);
    coordinates: LIST[1:3] OF length_measure;
  END_ENTITY;
 \endverbatim
 * Декартова точка (до трех декартовых координат)
 */
class cartesian_point : public point {

private:

  /**
   * Список, содержащий до трех значений мер длины (экземпляры данных типа
   * length_measure), задающих декартовы координаты точки.
   */
  LIST<length_measure> *coordinates;

public:

  /**
   * \brief Конструктор
   */
  cartesian_point(const std::string &Name, const double X, const double Y, const double Z) :
    representation_item(Name),
    point(Name) {
    coordinates = new LIST<length_measure>;
    coordinates->push_back(new length_measure(X));
    coordinates->push_back(new length_measure(Y));
    coordinates->push_back(new length_measure(Z));
    add_attr_info(STEP_ATTR_LIST({ {"coordinates", coordinates} }, this));
  }

  // Деструктор
  virtual ~cartesian_point() {
    for (auto it = coordinates->begin(); it != coordinates->end(); ++it) {
      delete *it;
    }
    delete coordinates;
  }

  // FUNCTION dimension_of
  dimension_count dimension_of(void) const {
    return dimension_count(coordinates->size());
  }

  // Сравнение "меньше"
  bool operator<(const cartesian_point& cp) const {
    // Если размерность разная - не сравниваем
    if (coordinates->size() != cp.coordinates->size()) {
      throw "Comparing (<) cartesian_point with different dimensions";
    }

    // Сравнить координаты вершин
    for (auto i = coordinates->cbegin(),
         j = cp.coordinates->cbegin(); i != coordinates->cend(); ++i, ++j) {
      if (*i < *j) return true;
      if (*i > *j) return false;
    }
    // Если все координаты равны
    return false;
  }

  // Сравнение "равенство"
  bool operator==(const cartesian_point& cp) const {
    // Если размерность разная - не сравниваем
    if (coordinates->size() != cp.coordinates->size()) {
      throw "Comparing (==) cartesian_point with different dimensions";
    }

    // Сравнить координаты вершин
    for (auto i = coordinates->cbegin(),
      j = cp.coordinates->cbegin(); i != coordinates->cend(); ++i, ++j) {
      if (**i != **j) return false;
    }
    // Если все координаты равны
    return true;
  }
};

// **************************************************************************
// Сравнение различных типов точек point, приведённых к базовому типу
// **************************************************************************

// Сравнение "меньше"
bool inline point::operator<(const point& p) const {
  if (typeid(*this) != typeid(p)) {
    throw "Comparing (<) point with different type";
  }
  if (typeid(*this) == typeid(point)) {
    throw "Comparing (<) abstract point";
  }
  if (typeid(*this) == typeid(cartesian_point)) {
    return *static_cast<const cartesian_point*>(this) < *static_cast<const cartesian_point*>(&p);
  }
  throw "Comparing (<) non-implemented point type";
}

// Сравнение "равенство"
bool inline point::operator==(const point& p) const {
  if (typeid(*this) != typeid(p)) {
    throw "Comparing (==) point with different type";
  }
  if (typeid(*this) == typeid(point)) {
    throw "Comparing (==) abstract point";
  }
  if (typeid(*this) == typeid(cartesian_point)) {
    return *static_cast<const cartesian_point*>(this) == *static_cast<const cartesian_point*>(&p);
  }
  throw "Comparing (==) non-implemented point type";
}

/**
 * \brief TYPE preferred_surface_curve_representation (ISO 10303-42:2021(E), 4.4.11)
 *
 * The <B>\ref preferred_surface_curve_representation</B> type is used to indicate the
 * preferred form of representation for a surface curve, which is either a curve in
 * geometric space or in the parametric space of the underlying surfaces.
 *
 * <U>EXPRESS specification:</U>
 * \verbatim
  *)
  TYPE preferred_surface_curve_representation = ENUMERATION OF
        (curve_3d,
         pcurve_s1,
         pcurve_s2);
  END_TYPE;
  (*
 \endverbatim
 */
class preferred_surface_curve_representation : public ENUMERATION {

public:

  enum
#if !defined(__DOXYGEN__)
  class
#endif 
  val {
      none = 0,
      /** the curve in three-dimensional space is preferred; */
      curve_3d,
      /** the first pcurve is preferred; */ 
      pcurve_s1,
      /**  the second pcurve is preferred. */
      pcurve_s2
  };

private:

  val x_;

public:

  // Конструктор
  preferred_surface_curve_representation(val v) : x_(v) {
  }

  // Получение значения
  val getval() const {
    return x_;
  }

  // Вывод значения типа
  std::string print_value() const {
    std::stringstream s;
    switch(x_) {
      case val::none:      s << "$";           break;
      case val::curve_3d:  s << ".CURVE_3D.";  break;
      case val::pcurve_s1: s << ".PCURVE_S1."; break;
      case val::pcurve_s2: s << ".PURVE_S2.";  break;
      default:               s << "";
        break;
    }
    return s.str();
  }
};


/**
 * \brief ENTITY pcurve (ISO 10303-42:2003, 4.4.44)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  ENTITY pcurve
     SUBTYPE OF (curve);
        basis_surface : surface;
        reference_to_curve : definitional_representation;
     WHERE
        WR1:
           SIZEOF(reference_to_curve\representation.items) = 1;
        wr2:
           'STEP_MERGED_AP_SCHEMA.CURVE' IN TYPEOF(reference_to_curve\representation.items[1]);
        wr3:
           reference_to_curve\representation.items[1]\geometric_representation_item.dim = 2;
  END_ENTITY;
 \endverbatim
 *
 */
class pcurve : public curve {
  private:

  // Explicit LABEL 			name;     // Defined by	representation_item
  // Explicit
  surface* basis_surface;
  // Explicit
  definitional_representation* reference_to_curve;
  // Derived
  // dimension_count dim; // Defined by geometric_representation_item

  public:

    // FUNCTION get_id_value
    identifier get_id_value(void) {
      return "";
    }

    // FUNCTION get_description_value
    text get_description_value(void) {
      return "";
    }

  virtual ~pcurve() {
  }
};



/**
 * \brief ENTITY surface_curve (ISO 10303-42:2003, 4.4.46)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  -- DIFF IN AP224 
  ENTITY surface_curve
     SUPERTYPE OF (ONEOF(intersection_curve, seam_curve) ANDOR bounded_surface_curve)
     SUBTYPE OF (curve);
        curve_3d : curve;
        associated_geometry : LIST [1:2] OF pcurve_or_surface;
        master_representation : preferred_surface_curve_representation;
     DERIVE
        basis_surface : SET [1:2] OF surface := get_basis_surface(SELF);
     WHERE
        WR1:
           curve_3d.dim = 3;
        wr2:
           ('STEP_MERGED_AP_SCHEMA.PCURVE' IN TYPEOF(associated_geometry[1])) OR (master_representation <> pcurve_s1);
        wr3:
           ('STEP_MERGED_AP_SCHEMA.PCURVE' IN TYPEOF(associated_geometry[2])) OR (master_representation <> pcurve_s2);
        wr4:
           NOT ('STEP_MERGED_AP_SCHEMA.PCURVE' IN TYPEOF(curve_3d));
  END_ENTITY;
 \endverbatim
 *
 */
class surface_curve : public curve {

private:

    curve* curve_3d;
    //!!! LIST OF pcurve_or_surface (SELECT)		associated_geometry;
    preferred_surface_curve_representation* master_representation;
  // Derived
  // dimension_count dim;                          // Defined by geometric_representation_item
  // LIST<SUFACE> basis_surface;             // Defined by surface_curve
};


  /**
   * \brief ENTITY topological_representation_item (ISO 10303-42:2021(E), 5.5.1)
   *
   * <B>5.5.1 \ref topological_representation_item</B><BR>
   * A <B>\ref topological_representation_item</B> is a type of <B>\ref representation_item</B> that represents
   * the topology, or connectivity, of entities which make up the representation of an object.
   * The <B>\ref topological_representation_item</B> is the supertype for all the representation items in the topology schema.
   *
   * <SMALL>NOTE 1 As subtypes of representation_item there is an implicit and/or relationship
   * between <B>\ref geometric_representation_item</B> and <B>\ref topological_representation_item</B>.
   * The only complex instances intended to be created are <B>\ref edge_curve</B>, <B>\ref face_surface</B>,
   * and <B>\ref vertex_point</B>.</SMALL>
   *
   * <SMALL>NOTE 2 The definition of <B>\ref topological_representation_item</B> defines an and/or relationship between
   * <B>\ref loop</B> and <B>\ref path</B>. The only valid complex instance is the <B>\ref edge_loop</B> entity.</SMALL>
   *
   * <U>EXPRESS-спецификация:</U>
   * \verbatim
    -- DIFF IN AP214
    -- DIFF IN AP203e2
    -- DIFF IN AP224
    -- DIFF IN AP232
    ENTITY topological_representation_item
       SUPERTYPE OF (ONEOF(vertex, edge, face_bound, face, vertex_shell, wire_shell, connected_edge_set, connected_face_set, connected_volume_set, volume_with_faces, loop ANDOR path))
       SUBTYPE OF (representation_item);
       DERIVE
          permanent_id : identifier := get_id_value(SELF);
          permanent_aggregate_id : identifier := get_aggregate_id_value(SELF);
       WHERE
          WR1:
             SIZEOF(USEDIN(SELF, 'STEP_MERGED_AP_SCHEMA.ID_ATTRIBUTE.IDENTIFIED_ITEM')) <= 1;
          wr2:
             SIZEOF(USEDIN(SELF, 'STEP_MERGED_AP_SCHEMA.AGGREGATE_ID_ATTRIBUTE.IDENTIFIED_ITEM')) <= 1;
    END_ENTITY;
    \endverbatim
   *
   * <U>Attribute definitions:</U>
   *
   * <B>permanent_id</B>: an identifier that distinguishes the <B>\ref topological_representation_item</B>.
   *
   * <SMALL>NOTE 3 This attribute is an enhancement to the definition of <B>\ref topological_representation_item</B>
   * using a method that is upwardly compatible with ISO 10303-42.</SMALL>
   *
   * <SMALL>NOTE 4 The meaning of this attribute can be defined in the annotated EXPRESS schemas that use or
   * specialize this entity, or in an agreement of common understanding between the partners sharing this information.</SMALL>
   *
   * <SMALL>NOTE 5 The context in which <B>permanent_id</B> is used as a discriminating characteristic can be identified
   * in an annotated Express schema that uses or specializes this entity, or by default, in an agreement of common
   * understanding between partners sharing this information.</SMALL>
   *
   * <B>permanent_aggregate_id</B>: an identifier that distinguishes the <B>\ref topological_representation_item</B>.
   * A <B>permanent_aggregate_id</B> supports the assignment of more than one instance of <B>topological_representation_item</B>
   * to the same identifier.
   *
   * <SMALL>NOTE 6 This attribute is an enhancement to the definition of <B>\ref topological_representation_item</B> using
   * a method that is upwardly compatible with ISO 10303-42.</SMALL>
   *
   * <SMALL>NOTE 7 The meaning of this attribute can be defined in the annotated EXPRESS schemas that use
   * or specialize this entity, or in an agreement of common understanding between the partners sharing
   * this information.</SMALL>
   *
   * <SMALL>NOTE 8 The context in which <B>\ref permanent_aggregate_id</B> is used as a discriminating characteristic
   * can be identified in an annotated Express schema that uses or specializes this entity, or by default, in an
   * agreement of common understanding between partners sharing this information.</SMALL>
   *
   * <U>Formal propositions:</U>
   *
   * <B>WR1:</B> Each <B>\ref topological_representation_item</B> shall be the identified_item in at most
   * one id_attribute.
   *
   * <SMALL>NOTE 9 The <B>\ref id_attribute</B> data type is defined in <B>basic_attribute_schema</B> of ISO 10303-42.</SMALL>
   *
   * <SMALL>NOTE 10 A template for constraining the population of the entity data types defined in the
   * <B>basic_attribute_schema</B> is described in annex E of ISO 10303-41.</SMALL>
   *
   * <B>WR2:</B> Each <B>\ref topological_representation_item</B> shall be the identified_item in at most
   * one <B>\ref aggregate_id_attribute</B>.
   *
   * <SMALL>NOTE 11 The <B>\ref aggregate_id_attribute</B> data type is defined in
   * <B>\ref basic_attribute_schema</B> of ISO 10303-42.</SMALL>
   *
   * <U>Informal propositions:</U><BR>
   * <B>IP1:</B> For each <B>\ref topological_representation_item</B>, consider the set of <B>\ref edge</B>s,
   * <B>\ref edge_curve</B>, and <B>\ref face_surface</B>s that are referenced, either directly or recursively,
   * from that <B>\ref topological_representation_item</B>. (Do not include in this set oriented edges or faces,
   * but do include the non-oriented edges and faces on which they are based.) Then no two distinct elements in
   * this set shall have domains that intersect. 
   */
  class topological_representation_item : virtual public representation_item {

  public:

    /** \brief Конструктор */
    topological_representation_item(const std::string &Name) : representation_item(Name) {
    }

    /** \brief Деструктор */
    virtual ~topological_representation_item() {
    }
};


/**
 * \brief ENTITY vertex (ISO 10303-42:2003, 5.4.2)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  ENTITY vertex
     SUBTYPE OF (topological_representation_item);
  END_ENTITY;
 \endverbatim
 * Вершина
 */
class vertex : public topological_representation_item {
  public:

    // Конструктор
    vertex(const std::string& Name) :
      representation_item(Name),
      topological_representation_item(Name) {
    }

    // Сравнение "меньше"
    bool operator<(const vertex& v) const;

    // Сравнение "равно"
    bool operator==(const vertex& v) const;
};

/**
 * \brief ENTITY vertex_point (ISO 10303-42:2003, 5.4.3)
 * \verbatim
  ENTITY vertex_point
     SUBTYPE OF (vertex, geometric_representation_item);
        vertex_geometry : point;
  END_ENTITY;
 \endverbatim
 * Вершина
 */
class vertex_point : public vertex, public geometric_representation_item {

private:

  const point* vertex_geometry;

public:

    // Конструктор
  vertex_point(const std::string &Name, const point* Vertex_geometry) :
    representation_item(Name),
    vertex(Name),
    geometric_representation_item(Name) {
    vertex_geometry = Vertex_geometry;
    add_attr_info(STEP_ATTR_LIST({
      {"vertex_geometry", vertex_geometry},
     }, this));
  }

  virtual ~vertex_point() {
  }

    // Возврат координат точки
//    const point* get_point(void) const {
//      return vertex_geometry;
//    }

    // Сравнение "меньше"
    bool operator<(const vertex_point& vp) const {
      if (vertex_geometry == nullptr) {
        throw "Comparing (<) this vertex_point when vertex_geometry == nullptr";
      }
      if (vp.vertex_geometry == nullptr) {
        throw "Comparing (<) with vertex_point when vertex_geometry == nullptr";
      }
      return *vertex_geometry < *vp.vertex_geometry;
    }

    // Сравнение "равенство"
    bool operator==(const vertex_point& vp) const {
      if (vertex_geometry == nullptr) {
        throw "Comparing (==) this vertex_point when vertex_geometry == nullptr";
      }
      if (vp.vertex_geometry == nullptr) {
        throw "Comparing (==) with vertex_point when vertex_geometry == nullptr";
      }
      return *vertex_geometry == *vp.vertex_geometry;
    }
};

// **************************************************************************
// Сравнение различных типов точек vertex, приведённых к базовому типу
// **************************************************************************

// Сравнение "меньше"
bool inline vertex::operator<(const vertex& v) const {
  if (typeid(*this) != typeid(v)) {
    throw "Comparing (<) vertex with different type";
  }
  if (typeid(*this) == typeid(vertex)) {
    throw "Comparing (<) abstract vertex";
  }
  if (typeid(*this) == typeid(vertex_point)) {
    return *static_cast<const vertex_point*>(this) < *static_cast<const vertex_point*>(&v);
  }
  throw "Comparing (<) non-implemented vertex type";
}

// Сравнение "равенство"
bool inline vertex::operator==(const vertex& v) const {
  if (typeid(*this) != typeid(v)) {
    throw "Comparing (==) vertex with different type";
  }
  if (typeid(*this) == typeid(vertex)) {
    throw "Comparing (==) abstract vertex";
  }
  if (typeid(*this) == typeid(vertex_point)) {
    return *static_cast<const vertex_point*>(this) == *static_cast<const vertex_point*>(&v);
  }
  throw "Comparing (==) non-implemented vertex type";
}


/**
 * \brief ENTITY edge (ISO 10303-42:2003, 5.4.4)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  -- DIFF IN AP214
  -- DIFF IN AP203e2
  -- DIFF IN AP238 STEP-NC
  -- DIFF IN AP224
  -- DIFF IN AP232 
  ENTITY edge
     SUPERTYPE OF(ONEOF(edge_curve, edge_with_length, oriented_edge, subedge))
     SUBTYPE OF(topological_representation_item);
        edge_start: vertex;
        edge_end: vertex;
  END_ENTITY;
 \endverbatim
 *
 * A  vertex  is  the  topological  construct corresponding to a point. It has
 * dimensionality  0  and  extent  0. The domain of a vertex, if present, is a
 * point  in  m  dimensional  real  space  Rm;  this  is  represented  by  the
 * vertex_point subtype.
 */
class edge : public topological_representation_item {

private:

  const vertex *edge_start; // Start point (vertex) of the edge.
  const vertex *edge_end;   // End point (vertex) of the edge. The same vertex can be used for both edge_start and edge_end.

public:

  /** \brief Конструктор */
  edge(const std::string &Name, const vertex *Edge_start, const vertex *Edge_end);

  /** \brief Деструктор */
  virtual ~edge();

  /**
   * Сравнение двух объектов edge
   * return: 0 - разные, 1 - одинаковые, -1 - противоположные
   */
  int compare(const edge &e2) const;

  friend oriented_edge edge_reversed(const edge &an_edge);
};



  /**
   * \brief ENTITY edge_curve (ISO 10303-42:2012(E), 5.5.5)
   *
   * <B>5.5.5 \ref edge_curve</B>
   *
   * <U>EXPRESS-спецификация:</U>
   * \verbatim
    ENTITY edge_curve
       SUBTYPE OF(edge,geometric_representation_item);
       edge_geometry : curve;
       same_sense : BOOLEAN;
    END_ENTITY;
   \endverbatim
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_edge_curve.html">Ссылка.</A>
   */
  class edge_curve : public geometric_representation_item, public edge {

  private:

    const curve* edge_geometry;  // The curve which defines the shape and spatial location of the edge. This curve may be
                                        // unbounded and is implicitly trimmed by the vertices of the edge; this defines the edge domain.
    BOOLEAN* same_sense;     // Признак того, что направление объекта-ребра edge (от первой вершине к последней) совпадает с
                                        // направлением объекта-кривой (направление возрастания параметра)

  public:

    /** \brief Конструктор */
    edge_curve(const std::string& Name, const vertex* Edge_start, const vertex* Edge_end, const curve* Edge_geometry, const BOOLEAN& Same_sense);

    /** \brief Деструктор */
    virtual ~edge_curve();

    // const curve *get_edge_geometry(void) const { return edge_geometry; }
    // BOOLEAN get_sense(void) const { return same_sense; }

      /**
       * Сравнение двух объектов edge_curve
       * return: 0 - разные, 1 - одинаковые, -1 - противоположные
       */
    int compare(const edge_curve& ec) const;
  };

  /**
   * \brief ENTITY oriented_edge (ISO 10303-42:2012(E), 5.5.6)
   *
   * <B>5.5.6 \ref oriented_edge</B><BR>
   * An <B>\ref oriented_edge</B> is a type of edge, constructed from another edge and contains
   * a BOOLEAN orientation flag to indicate whether or not the orientation of the constructed
   * <B>\ref edge</B> agrees with the orientation of the original <B>edge</B>. Except for possible
   * re-orientation, the <B>\ref oriented_edge</B> is equivalent to the original <B>\ref edge</B>.
   *
   * <SMALL>NOTE A common practice in solid modelling systems is to have an entity that represents
   * the "use" or "traversal" of an edge. This "use" entity explicitly represents the requirement
   * in a manifold solid that each edge must be traversed exactly twice, once in each direction.
   * The "use" functionality is provided by the <B>\ref edge</B> subtype <B>\ref oriented_edge</B>.</SMALL>
   *
   * <U>EXPRESS-спецификация:</U>
   * \verbatim
    -- DIFF IN AP203e2
    ENTITY oriented_edge
       SUBTYPE OF (edge);
       edge_element : edge;
       orientation : BOOLEAN;
    DERIVE
       SELF\edge.edge_start : vertex := boolean_choose (SELF.orientation,
                                                        SELF.edge_element.edge_start,
                                                        SELF.edge_element.edge_end);
       SELF\edge.edge_end : vertex := boolean_choose (SELF.orientation,
                                                      SELF.edge_element.edge_end,
                                                      SELF.edge_element.edge_start);
    WHERE
       WR1: NOT (’TOPOLOGY_SCHEMA.ORIENTED_EDGE’ IN TYPEOF (SELF.edge_element));
    END_ENTITY;
   \endverbatim
   *
   * <U>Attribute definitions:</U><BR>
   * <B>\ref edge_element</B>: an <B>\ref edge</B> entity used to construct this <B>\ref oriented_edge</B>;<BR>
   * <B>\ref orientation</B>: a BOOLEAN, if TRUE, the topological orientation as used
   * coincides with the orientation, from start vertex to end vertex, of the <B>\ref edge_element</B>.<BR>
   * <B>\ref edge_start</B>: the start vertex of the oriented edge, this is derived from the vertices of the
   * <B>\ref edge_element</B> after taking account of the <B>\ref orientation</B>.
   * <B>\ref edge_end</B>: the end vertex of the oriented edge, this is derived from the vertices of the
   * <B>\ref edge_element</B> after taking account of the <B>\ref orientation</B>.
   *
   * <U>Formal propositions:</U><BR>
   * <B>WR1:</B> The <B>\ref edge_element</B> shall not be an <B>\ref oriented_edge</B>.
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_oriented_edge.html">Ссылка.</A>
   */
  class oriented_edge : public edge {

  private:

    /** \brief An <B>\ref edge</B> entity used to construct this <B>\ref oriented_edge</B> */
    const edge* edge_element;

    /**
     * \brief A BOOLEAN, if TRUE, the topological orientation as used
     * coincides with the orientation, from start vertex to end vertex, of the <B>\ref edge_element</B>.
     */
    BOOLEAN* orientation;

  public:

    /** \brief Конструктор */
    oriented_edge(const std::string &Name, const edge *Edge_element, const BOOLEAN &Orientation) :
      representation_item(Name),
      //!!! edge_start = Orientation ? edge_element.edge_start : edge_element.edge_end;
      //!!! edge_end   = Orientation ? edge_element.edge_end   : edge_element.edge_start;
      edge(Name, nullptr, nullptr) {
      edge_element = Edge_element;
      orientation = new BOOLEAN(Orientation);
      set_attr_derived("edge_start");
      set_attr_derived("edge_end");
      add_attr_info(STEP_ATTR_LIST({
                                     {"edge_element",  edge_element},
                                     {"orientation", orientation},
                                   }, this));
    }

    /** \brief Деструктор */
    virtual ~oriented_edge() {
      delete orientation;
    }

    friend oriented_edge edge_reversed(const edge &an_edge);
  };


/**
 * \brief ENTITY loop (ISO 10303-42:2003, 5.4.12)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  -- DIFF IN AP224
  ENTITY loop
     SUPERTYPE OF (ONEOF(vertex_loop, edge_loop, poly_loop))
     SUBTYPE OF (topological_representation_item);
  END_ENTITY;
 \endverbatim
 */
class loop : virtual public topological_representation_item {
public:

  loop(const std::string& Name) :
    representation_item(Name),
    topological_representation_item(Name) {
  }
};

  /**
   * \brief FUNCTION edge_reversed (ISO 10303-42:2021(E), 5.6.5)
   * \param [in] an_edge The <B>\ref edge</B> which is to have its orientation reversed.
   * \return an <B>\ref oriented_edge</B> equivalent
   * to the input <B>\ref edge</B> except that the orientation is reversed. 
   *
   * <B>5.6.5 \ref edge_reversed</B>
   * The <B>\ref edge_reversed</B> function returns an <B>\ref oriented_edge</B> equivalent
   * to the input <B>\ref edge</B> except that the orientation is reversed.
   *
   * <U>EXPRESS-спецификация:</U>
   * \verbatim
    *)
    FUNCTION edge_reversed (an_edge : edge) : oriented_edge;
    LOCAL
         the_reverse : oriented_edge;
    END_LOCAL;

    IF ('TOPOLOGY_SCHEMA.ORIENTED_EDGE' IN TYPEOF (an_edge) ) THEN
         the_reverse  := dummy_tri ||
                 edge(an_edge.edge_end, an_edge.edge_start) ||
                 oriented_edge(an_edge\oriented_edge.edge_element,
                            NOT (an_edge\oriented_edge.orientation)) ;
      ELSE
         the_reverse := dummy_tri ||
                 edge(an_edge.edge_end, an_edge.edge_start) ||
                 oriented_edge(an_edge, FALSE);
       END_IF;
       RETURN (the_reverse);

    END_FUNCTION;
    (*  
    \endverbatim
   *
   * <U>Argument definitions:</U> <BR>
   * <B>an_edge</B>: (input) the <B>\ref edge</B> which is to have its orientation reversed.
   */
  oriented_edge edge_reversed(const edge& an_edge);


/**
 * \brief ENTITY path (ISO 10303-42:2003, 5.4.9) 
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
-- DIFF IN AP214
-- DIFF IN AP203e2
-- DIFF IN AP224
-- DIFF IN AP232
  ENTITY path
     SUPERTYPE OF (ONEOF(open_path, edge_loop, oriented_path))
     SUBTYPE OF (topological_representation_item);
        edge_list : LIST [1:?] OF UNIQUE oriented_edge;
     WHERE
        WR1:
           path_head_to_tail(SELF);
  END_ENTITY;
 \endverbatim
 */
class path : virtual public topological_representation_item {

private:

  /** Список ориентированных рёбер */
  LIST<const oriented_edge>* edge_list;

public:

  path(const std::string &Name) :
    representation_item(Name),
    topological_representation_item(Name) {
    edge_list = new LIST<const oriented_edge>();
    add_attr_info(STEP_ATTR_LIST({
                                   {"edge_list", edge_list},
                                 }, this));
  }

  virtual ~path() {
    delete edge_list;
  }

  void add_edge(const oriented_edge *x) {
    edge_list->push_back(x);
  }

//   const LIST<const oriented_edge> *get_edge_list(void) const {
//     return &edge_list;
//   }
};

/**
 * \brief ENTITY edge_loop (ISO 10303-42:2003, 5.4.14)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  ENTITY edge_loop
     SUBTYPE OF (loop, path);
     DERIVE
        ne : INTEGER := SIZEOF(SELF\path.edge_list);
     WHERE
        WR1:
           SELF\path.edge_list[1].edge_start :=: SELF\path.edge_list[ne].edge_end;
  END_ENTITY;
 \endverbatim
 */
class edge_loop : public loop, virtual public path {
public:

  edge_loop(const std::string &Name) :
    representation_item(Name),
    topological_representation_item(Name),
    path(Name),
    loop(Name) {
  }

  virtual ~edge_loop() {
  }
};


/**
 * \brief ENTITY vertex_loop (ISO 10303-42:2003, 5.4.13)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  ENTITY vertex_loop
     SUBTYPE OF (loop);
        loop_vertex : vertex;
  END_ENTITY;
 \endverbatim
 *
 */
class vertex_loop : public loop {

private:

  const vertex* loop_vertex;

public:

  vertex_loop(const std::string& Name, const vertex* Loop_vertex) :
    representation_item(Name),
    topological_representation_item(Name),
    loop(Name) {
    loop_vertex = Loop_vertex;
    add_attr_info(STEP_ATTR_LIST({
                                   {"loop_vertex", loop_vertex},
                                 }, this));
  }

  virtual ~vertex_loop() {
  }
};

/**
 * \brief ENTITY face_bound (ISO 10303-42:2003, 5.4.16)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  ENTITY face_bound
     SUBTYPE OF (topological_representation_item);
        bound : loop;
        orientation : BOOLEAN;
  END_ENTITY;
 \endverbatim
 *
 */
class face_bound : public topological_representation_item {

private:

  const loop* bound;      // Граница грани
  BOOLEAN* orientation; // Признак того, что направление номали грани совпадает с направлением нормали границы

public:

  face_bound(const std::string &Name, const loop *Bound, BOOLEAN::value Orientation) :
    representation_item(Name),
    topological_representation_item(Name) {
    bound = Bound;
    orientation = new BOOLEAN(Orientation);
    add_attr_info(STEP_ATTR_LIST({
                                   {"bound", bound},
                                   {"orientation", orientation},
                                 }, this));
  }

  virtual ~face_bound() {
    delete orientation;
  }

//    const loop *get_bound(void) const {
//      return bound;
//    }
};

/**
 * \brief ENTITY face_outer_bound (ISO 10303-42:2003, 5.4.17)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  ENTITY face_outer_bound
     SUBTYPE OF (face_bound);
  END_ENTITY;
 \endverbatim
 *
 */
class face_outer_bound : public face_bound {

public:

  // Конструктор
  face_outer_bound(const std::string &Name, const loop *Bound, BOOLEAN::value Orientation) :
    representation_item(Name),
    face_bound(Name, Bound, Orientation) {
  }

  virtual ~face_outer_bound() {
  }
};

/**
 * \brief ENTITY face (ISO 10303-42:2003, 5.4.18)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  -- DIFF IN AP224
  -- DIFF IN AP232
  ENTITY face
     SUPERTYPE OF (ONEOF(face_surface, subface, oriented_face))
     SUBTYPE OF (topological_representation_item);
        bounds : SET [1:?] OF face_bound;
     WHERE
        WR1:
           NOT mixed_loop_type_set(list_to_set(list_face_loops(SELF)));
        WR2:
           SIZEOF(QUERY (temp <* bounds| ('STEP_MERGED_AP_SCHEMA.FACE_OUTER_BOUND' IN TYPEOF(temp)))) <= 1;
  END_ENTITY;
 \endverbatim
 *
 */
class face : public topological_representation_item {
private:

  LIST<const face_bound>* bounds;

public:

  // Конструктор
  face(const std::string &Name) :
    representation_item(Name),
    topological_representation_item(Name) {
    bounds = new LIST<const face_bound>();
    add_attr_info(STEP_ATTR_LIST({
      {"bounds", bounds},
     }, this));
  }

  virtual ~face() {
    delete bounds;
  }

   // Добавление границы
  void add_bound(const face_bound* x) {
    bounds->push_back(x);
  }

//   const LIST<const face_bound>* get_bounds(void) const {
//     return &bounds;
//   }
};

/**
 * \brief ENTITY surface (ISO 10303-42:2003, 4.4.54)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  -- DIFF IN AP224
  ENTITY surface
     SUPERTYPE OF (ONEOF(elementary_surface, swept_surface, bounded_surface, offset_surface, surface_replica))
     SUBTYPE OF (geometric_representation_item);
  END_ENTITY;
 \endverbatim
 *
 */
class surface : public geometric_representation_item {

  public:

  // Конструктор
  surface(const std::string &Name) :
    representation_item(Name),
    geometric_representation_item(Name) {
  }

  dimension_count dimension_of(void) {
    return dimension_count();
  }
};


/**
 * \brief ENTITY direction (ISO 10303-42:2003, 4.4.14)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  ENTITY direction
     SUBTYPE OF (geometric_representation_item);
        direction_ratios : LIST [2:3] OF REAL;
     WHERE
        WR1:
           SIZEOF(QUERY (tmp <* direction_ratios | (tmp <> 0.0))) > 0;
  END_ENTITY;
 \endverbatim
 *
 * Направление - двух- или трёхмерный вектор нормированной длины
 * WR1 - длина вектора направления должна быть больше нуля.
 */
class direction : public geometric_representation_item {

private:
  /**
   * Список из 2 или 3 значений мер длины (экземпляры данных типа length_measure),
   * задающих проекции направления, представленного настоящим объектом вектора на
   * оси координат.
   */
  LIST<REAL>* direction_ratios; 

public:

  /** Конструктор */
  direction(const std::string &Name, unsigned Num_ratios, double X, double Y, double Z = 0) :
    representation_item(Name),
    geometric_representation_item(Name) {
    direction_ratios = new LIST<REAL>();
    assert(Num_ratios == 2 || Num_ratios == 3);
    direction_ratios->emplace_back(new REAL(X));
    direction_ratios->emplace_back(new REAL(Y));
    if (Num_ratios == 3) {
      direction_ratios->emplace_back(new REAL(Z));
    }
    add_attr_info(STEP_ATTR_LIST({ {"direction_ratios", direction_ratios} }, this));
  }

  /** Деструктор */
  ~direction() {
    for (auto it = direction_ratios->begin(); it != direction_ratios->end(); ++it)
      delete *it;
    delete direction_ratios;
  }
  
  // FUNCTION dimension_of
  dimension_count dimension_of(void) const {
    return dimension_count(direction_ratios->size());
  }

  LIST<REAL> *get_direction_ratios(void) {
    return direction_ratios;
  }
};

/**
 * \brief ENTITY placement (ISO 10303-42:2003, 4.4.16)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  ENTITY placement
     SUPERTYPE OF (ONEOF(axis1_placement, axis2_placement_2d, axis2_placement_3d))
     SUBTYPE OF (geometric_representation_item);
        location : cartesian_point;
  END_ENTITY;
 \endverbatim
 *
 * Этот тип располагает геометрический объект согласно его контексту.
 */
class placement : public geometric_representation_item {
private:

  /** Геометрические координаты опорной точки (например, центр круга) определяемого объекта */
  cartesian_point *location;

public:
  
  placement(const std::string &Name, cartesian_point *Location) :
    representation_item(Name),
    geometric_representation_item(Name) {
    location = Location;
    add_attr_info(STEP_ATTR_LIST({ {"location", location} }, this));
  }

  virtual ~placement() {
  }

  // FUNCTION dimension_of
  dimension_count dimension_of(void) const {
    return location->dimension_of();
  }
};

/**
 * \brief ENTITY axis2_placement_3d (ISO 10303-42:2003, 4.4.19)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  ENTITY axis2_placement_3d
     SUBTYPE OF (placement);
        axis : OPTIONAL direction;
        ref_direction : OPTIONAL direction;
     DERIVE
        p : LIST [3:3] OF direction := build_axes(axis, ref_direction);
     WHERE
        WR1:
           SELF\placement.location.dim = 3;
        wr2:
           NOT EXISTS(axis) OR (axis.dim = 3);
        wr3:
           NOT EXISTS(ref_direction) OR (ref_direction.dim = 3);
        wr4:
           (NOT EXISTS(axis) OR NOT EXISTS(ref_direction)) OR (cross_product(axis, ref_direction).magnitude > 0.0);
  END_ENTITY;
 \endverbatim
 *
 * Это разновидность положения, определяющего расположение и ориентацию
 * в трёхмерном пространстве двумя желательно взаимно перпендикулярными осями.
 */
class axis2_placement_3d : public placement {
private:

  direction *axis;                                            // Точное направление локальной оси Z
  direction *ref_direction;                                   // Направление, используемое для получения направления локальной оси X

public:
  axis2_placement_3d(const std::string &Name, cartesian_point *Location, direction *Axis, direction *Ref_direction) :
    representation_item(Name),
    placement(Name, Location) {
    axis = Axis;
    ref_direction = Ref_direction;
    // WR1: пространственная размерность Location должна быть равно 3.
    assert(Location->dimension_of() == dimension_count(3));
    // WR2: пространственная размерность Axis должна быть равнв 3.
    assert(Axis == nullptr || Axis->dimension_of() == dimension_count(3));
    // WR3: пространственная размерность Ref_direction должна быть равно 3.
    assert(Ref_direction == nullptr || Ref_direction->dimension_of() == dimension_count(3));
    // WR4: Axis и Ref_direction не должны быть параллельны или антипараллельны.
    // !!!
    assert((Axis == nullptr || Ref_direction == nullptr) || 1 /* cross_product(Axis, Ref_direction).magnitude > 0.0 */);

    add_attr_info(STEP_ATTR_LIST({
                                   {"axis", axis, true},
                                   {"ref_direction", ref_direction, true},
      }, this));


  }

  virtual ~axis2_placement_3d() {
  }

  const direction *get_axis(void) const {
    return axis;
  }

  const direction *get_ref_direction(void) const {
    return ref_direction;
  }
};


/**
 * \brief ENTITY oriented_surface (ISO 10303-42:2003, 4.4.82)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  -- IN AP203e2/AP214/AP232/AP238 STEP-NC/AP242
  ENTITY oriented_surface
     SUBTYPE OF (surface);
        orientation : BOOLEAN;
  END_ENTITY;
 \endverbatim
 *
 */
class oriented_surface : public surface {
  private:

    BOOLEAN orientation;

  public:

    oriented_surface(const std::string &Name, BOOLEAN Orientation) :
      representation_item(Name),
      surface(Name),
      orientation(Orientation) {
    }
};


/**
 * \brief ENTITY elementary_surface (ISO 10303-42:2003, 4.4.55)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  ENTITY elementary_surface
     SUPERTYPE OF (ONEOF(plane, cylindrical_surface, conical_surface, spherical_surface, toroidal_surface))
     SUBTYPE OF (surface);
        position : axis2_placement_3d;
  END_ENTITY;
 \endverbatim
 *
 * Элементарная поверхность это параметрически определяемая разновидность поверхности.
 */
class elementary_surface : public surface {

private:

  const axis2_placement_3d *position;            // Положение и ориентация поверхности

public:

  elementary_surface(const std::string &Name, const axis2_placement_3d *Position) :
    representation_item(Name),
    surface(Name) {
    position = Position;
    add_attr_info(STEP_ATTR_LIST({
      {"position", position},
      }, this));
  }

  virtual ~elementary_surface() {
  }
};

/**
 * \brief ENTITY plane (ISO 10303-42:2003, 4.4.56)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  ENTITY plane
     SUBTYPE OF (elementary_surface);
  END_ENTITY;
 \endverbatim
 *
 * Плоскость это разновидность элементарной поверхности - есть неограниченной и с постоянной нормалью. 
 */
class plane : public elementary_surface {
public:
    
  plane(const std::string &Name, const axis2_placement_3d *Position) :
    representation_item(Name),
    elementary_surface(Name, Position) {
  }

  virtual ~plane() {
  }
};

  /*
   * 5.3 topology_schema constant definition
   *
   * <U>EXPRESS-спецификация:</U>
   * \verbatim
    *)
    CONSTANT
    (*
    \endverbatim
   *
   */

  /**
   * \brief dummy_tri (ISO 10303-42:2021(E), 5.3.1)
   *
   * <B>5.3.1 \ref dummy_tri</B>
   * A <B>\ref dummy_tri</B> is a constant that is a partial entity definition to be used when types of
   * <B>\ref topological_representation_item</B> are constructed. It provides the correct supertypes and
   * the <B>name</B> attribute as an empty string.
   * <U>EXPRESS-спецификация:</U>
   * \verbatim
    *)
      dummy_tri : topological_representation_item := representation_item('') || topological_representation_item();
    (* 
    \endverbatim
   *
   */
  extern const topological_representation_item dummy_tri;


  /**
   * \brief FUNCTION dimension_of (ISO 10303-42:2021(E), 4.6.21)
   * \param [in] item A <B>\ref geometric_representation_item</B> for which the <B>dimension_count</B> is determined. 
   * \return количество измерений геометрического объекта.
   *
   * <B>4.6.21 dimension_of</B><BR>
   * The <B>\ref dimension_of</B> function returns the dimensionality of the input <B>\ref geometric_representation_item</B>.
   * If the item is a <B>\ref cartesian_point</B>, <B>\ref direction</B>, or <B>\ref vector</B>, the dimensionality is
   * obtained directly by counting components. For all other other subtypes the dimensionality is the integer <B>\ref dimension_count</B>
   * of a <B>\ref geometric_representation_context</B> in which the input <B>geometric_representation_item</B> is geometrically founded.
   * By virtue of the constraints in global rule <B>\ref compatible_dimension</B>, this value is the <B>\ref dim</B> of the input
   * <B>\ref geometric_representation_item</B>.
   *
   * <U>EXPRESS-спецификация:</U>
   * \verbatim
  *)
  FUNCTION dimension_of (item : geometric_representation_item) : dimension_count;

  LOCAL
      x   : SET OF representation;
      y   : representation_context;
      dim : dimension_count;
    END_LOCAL;
    -- For cartesian_point, direction, or vector dimension is determined by
    -- counting components.
      IF 'GEOMETRY_SCHEMA.CARTESIAN_POINT' IN TYPEOF(item) THEN
         dim := SIZEOF(item\cartesian_point.coordinates);
         RETURN(dim);
      END_IF;
      IF 'GEOMETRY_SCHEMA.DIRECTION' IN TYPEOF(item) THEN
         dim := SIZEOF(item\direction.direction_ratios);
         RETURN(dim);
      END_IF;
      IF 'GEOMETRY_SCHEMA.VECTOR' IN TYPEOF(item) THEN
         dim := SIZEOF(item\vector.orientation\direction.direction_ratios);
         RETURN(dim);
      END_IF;
    -- For all other types of geometric_representation_item dim is obtained
    -- via context.
    -- Find the set of representation in which the item is used. 

    x := using_representations(item);

    -- Determines the dimension_count of the 
    -- geometric_representation_context.
    -- The SET x is non-empty for legal instances since this is required by WR1 of
    -- representation_item.
      IF (SIZEOF(x) > 0) THEN
         y := x[1].context_of_items;
        dim := y\geometric_representation_context.coordinate_space_dimension;
      RETURN (dim);
      ELSE
        RETURN(?);
      -- mark error by returning indeterminate result
     END_IF;

  END_FUNCTION;
  (*
   \endverbatim
   *
   * <U>Argument definitions:</U><BR>
   * <B>item</B>: (input) a <B>\ref geometric_representation_item</B> for which the <B>dimension_count</B> is determined. 
   */

  dimension_count dimension_of(const geometric_representation_item& item);


/**
 * \brief ENTITY face_surface (ISO 10303-42:2003, 5.4.19)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  ENTITY face_surface
     SUBTYPE OF(face, geometric_representation_item);
        face_geometry: surface;
        same_sense: BOOLEAN;
     WHERE
        WR1 :
           NOT('STEP_MERGED_AP_SCHEMA.ORIENTED_SURFACE' IN TYPEOF(face_geometry));
  END_ENTITY;
 \endverbatim
 *
 */
class face_surface : public face, public geometric_representation_item {

private:

  const surface* face_geometry;   // Поверхность, определяющая внутреннюю поверхность грани
  BOOLEAN* same_sense;            // Признак того, что нормаль грани совпадает с нормалью поверхности, то есть
                                       // на какой стороне поверхности находится грань
  void check_face_geometry(void);

public:
  // Конструктор
  face_surface(const std::string& Name, const surface* Face_geometry, BOOLEAN::value Same_sense) :
    representation_item(Name),
    face(Name),
    geometric_representation_item(Name) {
    face_geometry = Face_geometry;
    same_sense = new BOOLEAN(Same_sense);
    //WR1
    check_face_geometry();

    add_attr_info(STEP_ATTR_LIST({
      {"face_geometry", face_geometry},
      {"same_sense", same_sense},
     }, this));
  }

  ~face_surface() {
    delete same_sense;
  }

   // Добавление границы
  void add_bound(const face_bound* x) {
    face::add_bound(x);
  }
};

/**
 * \brief ENTITY connected_face_set (ISO 10303-42:2003, 5.4.22)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  ENTITY connected_face_set
     SUPERTYPE OF (ONEOF(closed_shell, open_shell))
     SUBTYPE OF (topological_representation_item);
        cfs_faces : SET [1:?] OF face;
  END_ENTITY;
 \endverbatim
 *
 */
class connected_face_set : public topological_representation_item {

private:

  LIST<const face>* cfs_faces;

public:

  connected_face_set(const std::string& Name) :
    representation_item(Name),
    topological_representation_item(Name) {
    cfs_faces = new LIST<const face>();
    add_attr_info(STEP_ATTR_LIST({
                                   {"cfs_faces", cfs_faces},
                                 }, this));
  }

  virtual ~connected_face_set() {
    delete cfs_faces;
  }

  void add_face(const face* x) {
    cfs_faces->push_back(x);
  }
};

/**
 * \brief ENTITY closed_shell (ISO 10303-42:2003, 5.4.27)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  ENTITY closed_shell
     SUBTYPE OF (connected_face_set);
  END_ENTITY;
 \endverbatim
 *
 */
class closed_shell : public connected_face_set {

public:

  // Констуктор
  closed_shell(const std::string& Name) :
    representation_item(Name),
    connected_face_set(Name) {
  }

  virtual ~closed_shell() {
  }
};


/**
 * \brief ENTITY solid_model (ISO 10303-42:2003, 6.4.1)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  -- DIFF IN AP224
  -- DIFF IN AP232
  ENTITY solid_model
     SUPERTYPE OF (ONEOF(csg_solid, manifold_solid_brep, swept_face_solid, swept_area_solid, swept_disk_solid, solid_replica))
     SUBTYPE OF (geometric_representation_item);
  END_ENTITY;
 \endverbatim
 *
 */
class solid_model : public geometric_representation_item {

public:

  solid_model(const std::string& Name) :
    representation_item(Name),
    geometric_representation_item(Name) {
  }
};

/**
 * \brief ENTITY manifold_solid_brep (ISO 10303-42:2003, 6.4.2)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  ENTITY manifold_solid_brep
     SUBTYPE OF (solid_model);
        outer : closed_shell;
  END_ENTITY;
 \endverbatim
 *
 */
class manifold_solid_brep : public solid_model {

private:

  const closed_shell* outer;

public:

  manifold_solid_brep(const std::string& Name, const closed_shell* Outer) :
    representation_item(Name),
    solid_model(Name) {
    outer = Outer;
    add_attr_info(STEP_ATTR_LIST({
                                   {"outer", outer},
                                 }, this));
    
  }

  virtual ~manifold_solid_brep() {
  }

  // FUNCTION dimension_of
  dimension_count dimension_of(void) const {
    if (outer == nullptr) {
      throw "outer is nullptr";
    }

    return 3; // !!! return outer->?????
  }
};


}
