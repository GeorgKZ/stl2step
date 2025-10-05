/**
 * \file
 *
 * \brief Файл с определениями функций классов, соответствующих ISO 10303-42:2021(E)
 *
 * Здесь определены функции классов, относящихся к геометрическому и топологическому представлению.
 */

#include "stdafx.h"
#include "express.h"

namespace express {


  /* CONSTANT dummy_tri (5.3.1) */

  //const topological_representation_item dummy_tri("");


  geometric_representation_item::geometric_representation_item(const std::string &Name) : representation_item(Name) {
  }

  geometric_representation_item::~geometric_representation_item() {
  }


  // Конструктор
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



void face_surface::check_face_geometry(void) {
  if (typeid(*face_geometry) == typeid(oriented_surface)) {
    throw "Face_geometry is not oriented_surface*";
  }
}

  //  STEP_TYPE_SELECT_CONSTRUCTOR(axis2_placement, axis2_placement_2d)
  STEP_TYPE_SELECT_CONSTRUCTOR(axis2_placement, axis2_placement_3d)

  STEP_TYPE_SELECT_CONSTRUCTOR(vector_or_direction, vector)
  STEP_TYPE_SELECT_CONSTRUCTOR(vector_or_direction, direction)

  vector::vector(const std::string &Name, const direction* Orientation, const length_measure &Magnitude) :
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

  // FUNCTION dimension_of
  dimension_count vector::dimension_of(void) const {
    return orientation->dimension_of();
  }


  line::line(const std::string &Name, const cartesian_point *Pnt, const vector *Dir) :
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


  edge_curve::edge_curve(const std::string &Name, const vertex *Edge_start, const vertex *Edge_end, const curve *Edge_geometry, const BOOLEAN &Same_sense) :
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

  int edge_curve::compare(const edge_curve &ec) const {
    int sign = edge::compare(ec);
    if (sign == 0) return 0;

//      const curve *edge_geometry1 = get_edge_geometry();
//      const curve *edge_geometry2 = ec.get_edge_geometry();
// !!!   Проверить edge_geometry


    BOOLEAN same_sense1 = *same_sense;
    BOOLEAN same_sense2 = *ec.same_sense;

    if (same_sense1 == same_sense2) return sign; else return -sign;
  }


  /* FUNCTION edge_reversed (5.6.5) */

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

  oriented_edge edge_reversed(const edge& an_edge) {
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

    if (an_edge.is_type_name("oriented_edge")) {
      return oriented_edge("", new edge("", an_edge.edge_end, an_edge.edge_start), !*static_cast<const oriented_edge*>(&an_edge)->orientation);
    } else {
      return oriented_edge("", new edge("", an_edge.edge_end, an_edge.edge_start), BOOLEAN::value::FALSE);
    }
  }

  dimension_count dimension_of(const geometric_representation_item& item) {
    //!!!
    return 0;
  }

}
