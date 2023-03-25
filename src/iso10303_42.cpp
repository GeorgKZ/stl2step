/**
 * \file
 *
 * \brief Файл с определениями функций классов, соответствующих ISO 10303-42:2021(E)
 *
 * Здесь определены функции классов, относящихся к геометрическому и топологическому представлению.
 */

#ifndef TESTONLY

#include "stdafx.h"
#include "express.h"

namespace express {

  /* 4.4.17 TYPE vector_or_direction */

//  STEP_TYPE_SELECT_CONSTRUCTOR(vector_or_direction, vector)
//  STEP_TYPE_SELECT_CONSTRUCTOR(vector_or_direction, direction)

  vector_or_direction::vector_or_direction(const vector& t) : SELECT(&t) {
  }

  vector_or_direction::vector_or_direction(const direction& t) : SELECT(&t) {
  }

  vector_or_direction::operator const vector& () const {
    return *dynamic_cast<const vector*>(get_value());
  }

  const vector& vector_or_direction::_vector() const {
    return *dynamic_cast<const vector*>(get_value());
  }

  vector_or_direction::operator const direction& () const {
    return *dynamic_cast<const direction*>(get_value());
  }

  const direction& vector_or_direction::_direction() const {
    return *dynamic_cast<const direction*>(get_value());
  }


  /** \brief Получить значение размености (количества координат) объекта */
  dimension_count vector_or_direction::get_dim() const {
    if (is_type_name("vector")) {
      const vector& v = *this;
      return v._dim();
    } else {
      const direction& d = *this;
      return d._dim();
    }
  }


  /* 5.3.1 CONSTANT dummy_tri */

  //const topological_representation_item dummy_tri("");

  /* 4.5.1 TYPE geometric_representation_context */

  geometric_representation_context::geometric_representation_context(const std::string& Identifier, const std::string& Type, const dimension_count& Dimension) :
    representation_context(Identifier, Type) {

    coordinate_space_dimension = new dimension_count(Dimension);
    add_attr_info(STEP_ATTR_LIST({
                                   {"coordinate_space_dimension", coordinate_space_dimension}
                                 }, this));
  }

  geometric_representation_context::~geometric_representation_context() {
    delete coordinate_space_dimension;
  }


  /* 4.5.2 TYPE geometric_representation_item */

  geometric_representation_item::geometric_representation_item(const std::string& Name) : representation_item(Name) {
    add_attr_info(STEP_ATTR_LIST({
                                   {}
                                 }, this));
  }

  geometric_representation_item::~geometric_representation_item() {
  }


  bool point::operator==(const point& p) const {
    if (typeid(*this) != typeid(p)) {
      throw exception {"Comparing (==) point with different type"};
    }
    if (typeid(*this) == typeid(point)) {
      throw exception {"Comparing (==) abstract point"};
    }
    if (typeid(*this) == typeid(cartesian_point)) {
      return *static_cast<const cartesian_point*>(this) == *static_cast<const cartesian_point*>(&p);
    }
    throw exception {"Comparing (==) non-implemented point type"};
  }


  void face_surface::check_face_geometry() {
    if (typeid(*face_geometry) == typeid(oriented_surface)) {
      throw exception {"Face_geometry is not oriented_surface*"};
    }
  }

  //  STEP_TYPE_SELECT_CONSTRUCTOR(axis2_placement, axis2_placement_2d)
  STEP_TYPE_SELECT_CONSTRUCTOR(axis2_placement, axis2_placement_3d)

  /* 4.5.15 ENTITY vector*/

  vector::vector() :
    representation_item(),
    geometric_representation_item(),
    orientation(nullptr),
    magnitude(nullptr) {
    add_attr_info(STEP_ATTR_LIST({
                                   {"orientation", orientation},
                                   {"magnitude", magnitude},
      }, this));
  }

  vector::vector(const std::string& Name, const direction* Orientation, const length_measure& Magnitude) :
    representation_item(Name),
    geometric_representation_item(Name) {

    // WR1
    assert(Magnitude >= length_measure(0.0));

    orientation = Orientation;
    magnitude = new length_measure(Magnitude);
    add_attr_info(STEP_ATTR_LIST({
                                   {"orientation", orientation},
                                   {"magnitude", magnitude},
      }, this));
  }

  vector::~vector() {
    delete magnitude;
  }

  /* */

  line::line(const std::string& Name, const cartesian_point* Pnt, const vector* Dir) :
    representation_item(Name),
    curve(Name) {
    pnt = Pnt;
    dir = Dir;
    add_attr_info(STEP_ATTR_LIST({
                                   {"pnt", pnt},
                                   {"dir", dir},
      }, this));
  }

  line::~line() {
  }


  edge_curve::edge_curve(const std::string& Name, const vertex* Edge_start, const vertex* Edge_end, const curve* Edge_geometry, const BOOLEAN& Same_sense) :
    representation_item(Name),
    geometric_representation_item(Name),
    edge(Name, Edge_start, Edge_end) {
    edge_geometry = Edge_geometry;
    same_sense = new BOOLEAN(Same_sense);
    add_attr_info(STEP_ATTR_LIST({
                                   {"edge_geometry", edge_geometry},
                                   {"same_sense", same_sense},
                                 }, this));
  }

  edge_curve::~edge_curve() {
    delete same_sense;
  }

#if 0
  int edge_curve::compare(const edge_curve& ec) const {
    int sign = edge::compare(ec);
    if (sign == 0) return 0;

    //      const curve *edge_geometry1 = get_edge_geometry();
    //      const curve *edge_geometry2 = ec.get_edge_geometry();
    // !!!   Проверить edge_geometry


    BOOLEAN same_sense1 = *same_sense;
    BOOLEAN same_sense2 = *ec.same_sense;

    if (same_sense1 == same_sense2) return sign; else return -sign;
  }
#endif

  /* 5.6.5 FUNCTION edge_reversed */

/*
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
*/

  oriented_edge* edge_reversed(const edge* an_edge) {
    //    oriented_edge the_reverse();
    //    if (an_edge.is_type_name("oriented_edge")) {
    //    {
    //                                   // topological_representation_item  <- edge <- oriented_edge
    //      the_reverse = ENTITY_COMPLEX(dummy_tri, edge(an_edge.edge_end, an_edge.edge_start), oriented_edge(an_edge\oriented_edge.edge_element, NOT (an_edge\oriented_edge.orientation))
    //    } else {
    //                                   // topological_representation_item  <- edge <- oriented_edge
    //      the_reverse = ENTITY_COMPLEX(dummy_tri, edge(an_edge.edge_end, an_edge.edge_start), oriented_edge(an_edge, FALSE);
    //    }
    //    return the_reverse;

    if (an_edge->is_type_name("oriented_edge")) {
      return new oriented_edge("", new edge("", an_edge->get_edge_end(), an_edge->get_edge_start()), NOT (reinterpret_cast<const oriented_edge*>(an_edge))->get_orientation() );
    }
    else {
      return new oriented_edge("", new edge("", an_edge->get_edge_end(), an_edge->get_edge_start()), FALSE);
    }
  }


  /* 4.6.8 FUNCTION build_axes */

  LIST<direction> build_axes(const direction& axis, const direction& ref_direction) {

    direction d1 = NVL<direction>(normalise(axis), direction("", 0.0, 0.0, 1.0));
    direction d2 = first_proj_axis(d1, ref_direction);

    return LIST<direction>( {d2, *normalise(cross_product(d1, d2))._vector().orientation, d1}, 3, 3);
  }


  /* 4.6.15 FUNCTION cross_product */

  vector cross_product(const direction& arg1, const direction& arg2) {
    REAL mag;
    direction res;

    IF ((NOT EXISTS(arg1) OR arg1._dim() == dimension_count(2)) OR (NOT EXISTS(arg2) OR arg2._dim() == dimension_count(2))) {
      return vector();
    }

    const LIST<REAL>& v1 = normalise(arg1)._direction().direction_ratios;
    const LIST<REAL>& v2 = normalise(arg2)._direction().direction_ratios;
    res = direction("", v1[2] * v2[3] - v1[3] * v2[2], v1[3] * v2[1] - v1[1] * v2[3], v1[1] * v2[2] - v1[2] * v2[1]);
    mag = REAL(0.0);
    for (INTEGER i = 1; i.get_value() <= 3; i = i + 1) {
      mag = mag + res.direction_ratios[i] * res.direction_ratios[i];
    }

    if (mag > REAL(0.0)) {
      return vector("", new direction(res), SQRT(mag));
    } else {
      return vector("", new direction(arg1), REAL(0.0));
    }
  }

  /* 4.6.21 dimension_of */

  dimension_count dimension_of(const geometric_representation_item* item) {
    /* For cartesian_point, direction, or vector dimension is determined by
     * counting components.
     */

    if (item->is_type_name("cartesian_point")) return SIZEOF(reinterpret_cast<const cartesian_point*>(item)->get_coordinates());
//    if (item->is_type_name("direction"))       return SIZEOF(reinterpret_cast<const direction*>(item)->direction_ratios);
//    if (item->is_type_name("vector"))          return SIZEOF(reinterpret_cast<const vector*>(item)->orientation->direction_ratios);
    if (item->is_type_name("direction"))       return SIZEOF(reinterpret_cast<const direction*>(item)->direction_ratios);
    if (item->is_type_name("vector"))          return SIZEOF(reinterpret_cast<const vector*>(item)->orientation->direction_ratios);

    /* For all other types of geometric_representation_item dim is obtained
     * via context.
     */

    /* Find the set of representation in which the item is used. */
    SET<representation> x = using_representations(item);

    /* Determines the dimension_count of the
     * geometric_representation_context.
     * The SET x is non-empty for legal instances since this is required by WR1 of
     * representation_item.
     */
    if (SIZEOF(x).get_value() > 0) {
      const representation_context* y = x[1].context_of_items;
      return reinterpret_cast<const geometric_representation_context*>(y)->get_coordinate_space_dimension();
    }
    else {

      /* mark error by returning indeterminate result */
      return dimension_count();
    }
  }

  /* 4.6.22 dot_product */

  REAL dot_product(const direction& arg1, const direction& arg2) {
    IF (EXISTS(arg1) OR NOT EXISTS(arg2)) {
      /* When function is called with invalid data an indeterminate result is returned */
      return REAL();
    }

    IF (arg1._dim() != arg2._dim()) {
      /* When function is called with invalid data an indeterminate result is returned */
      return REAL();
    }
    const direction& vec1 = normalise(arg1);
    const direction& vec2 = normalise(arg2);
    INTEGER ndim(arg1._dim());
    REAL scalar = 0.0;
    for (INTEGER i = 1; i.get_value() <= ndim.get_value(); i = i + 1) {
      scalar = scalar + vec1.direction_ratios[i] * vec2.direction_ratios[i];
    }
    return scalar;
  }

  /* 4.6.23 first_proj_axis */

  direction first_proj_axis(const direction& z_axis, const direction& arg) {
    if (EXISTS(z_axis).is_false()) {
      return direction();
    }

    direction v;
    const direction& z = normalise(z_axis);
    vector x_vec;

    if  (EXISTS(arg).is_false()) {
      if ((z.direction_ratios != LIST<REAL>({1.0, 0.0, 0.0})) && (z.direction_ratios != LIST<REAL>({-1.0, 0.0, 0.0}))) {
        v = direction("", LIST<REAL>({ 1.0, 0.0, 0.0 }));
      } else {
        v = direction("", LIST<REAL>({ 0.0, 1.0, 0.0 }));
      }
    } else {
      IF (arg._dim() != dimension_count(3)) {
        return direction();
      }
      if (*cross_product(arg, z).magnitude == REAL(0.0)) {
        return direction();
      } else {
        v = normalise(arg);
      }
    }
    x_vec = scalar_times_vector(dot_product(v, z), z);
    const direction& x_axis = *vector_difference(v, x_vec).orientation;
    return normalise(x_axis);
  }

  /* 4.6.30 normalise */

  vector_or_direction normalise(const vector_or_direction& arg) {
    INTEGER ndim;
    direction v("", 1.0, 0.0, 0.0);
    vector_or_direction result;
    vector vec("", &v, REAL(1.0));
    REAL mag;

    if (EXISTS(arg).is_false()) {
      /* When function is called with invalid data a NULL result is returned */
      return vector_or_direction();
    }

    ndim = arg.get_dim();
    if (arg.is_type_name("vector")) {
      v = direction("", arg._vector().orientation->direction_ratios);
      if (*arg._vector().magnitude == REAL(0.0)) {
        return vector_or_direction();
      } else {
        vec = vector("", &v, REAL(1.0));
      }
    } else {
      v = direction ("", arg._direction().direction_ratios);
    }

    mag = REAL(0.0);
    for (INTEGER i = 1; i.get_value() <= ndim.get_value(); i = i + 1) {
      mag = mag + v.direction_ratios[i] * v.direction_ratios[i];
    }
    if (mag > REAL(0.0)) {
      mag = SQRT(mag);
      for (INTEGER i = 1; i.get_value() <= ndim.get_value(); i = i + 1) {
        v.direction_ratios[i] = v.direction_ratios[i] / mag;
      }
      if (arg.is_type_name("vector")) {
        return vector("", new direction(v), *vec.magnitude);
      } else {
        return v;
      }
    } else {
      return vector_or_direction();
    }
  }

  /* 4.6.31 orthogonal_complement */

  direction orthogonal_complement (const direction& vec) {
   IF (NOT EXISTS(vec) OR vec._dim() != dimension_count(2)) THEN
     return direction();
   ELSE
     return direction("", -vec.direction_ratios[2], vec.direction_ratios[1]);
   END_IF
  }

  /* 4.6.33 scalar_times_vector */

  vector scalar_times_vector(const REAL& scalar, const vector_or_direction& vec) {

    direction v;
    REAL mag;

    if (EXISTS(scalar).is_false() || EXISTS(vec).is_false()) {
      return vector();
    }

    if (vec.is_type_name("vector")) {
      v = direction("", vec._vector().orientation->direction_ratios);
      mag = scalar * *vec._vector().magnitude;
    } else {
      v = direction("", vec._direction().direction_ratios);
      mag = scalar;
    }
    if (mag < REAL(0.0)) {
      for (INTEGER i = 1; i.get_value() <= SIZEOF(v.direction_ratios).get_value(); i = i + 1) {
        v.direction_ratios[i] = -v.direction_ratios[i];
      }
      mag = -mag;
    }
    return vector("", new direction(normalise(v)), mag);
  }


  /* 4.6.36 vector_difference */

  vector vector_difference(const vector_or_direction& arg1, const vector_or_direction& arg2) {

    LOCAL
      direction res, vec1, vec2;
      REAL mag, mag1, mag2;
      INTEGER ndim;
    END_LOCAL

//    if (EXISTS(arg1).is_false() || EXISTS(arg2).is_false() || (arg1.get_dim() != arg2.get_dim())) {
//      return vector();
//    }

    IF (((NOT EXISTS(arg1)) OR (NOT EXISTS(arg2))) OR (arg1.get_dim() != arg2.get_dim()))
       THEN
      return vector();
       ELSE

    if (arg1.is_type_name("vector")) {
      mag1 = *arg1._vector().magnitude;
      vec1 = *arg1._vector().orientation;
    } else {
      mag1 = REAL(1.0);
      vec1 = arg1;
    }

    if (arg2.is_type_name("vector")) {
      mag2 = *arg2._vector().magnitude;
      vec2 = *arg2._vector().orientation;
    } else {
      mag2 = REAL(1.0);
      vec2 = arg2;
    }

    vec1 = normalise(vec1);
    vec2 = normalise(vec2);

    ndim = SIZEOF(vec1.direction_ratios);
    mag = REAL(0.0);
    res = direction("", vec1.direction_ratios);
    for (INTEGER i = 1; i.get_value() <= ndim.get_value(); i = i + INTEGER(1)) {
      res.direction_ratios[i] = mag1 * vec1.direction_ratios[i] - mag2 * vec2.direction_ratios[i];
      mag = mag + res.direction_ratios[i] * res.direction_ratios[i];
    }
    if (mag > REAL(0.0)) {
      return vector("", new direction(res), SQRT(mag));
    } else {
      return vector("", new direction(vec1), REAL(0.0));
    }

    END_IF
  END_FUNCTION
}

#endif