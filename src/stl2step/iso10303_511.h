/**
 * \file
 *
 * \brief Заголовочный файл с определениями классов, соответствующих ГОСТ Р ИСО 10303-511-2005.
 */

namespace express {

/**
 * \brief ENTITY advanced_face (ГОСТ Р ИСО 10303-511-2005, 4.2)
 *
 * <B>Определение объекта на языке EXPRESS:</B>
 * \verbatim
  ENTITY advanced_face
     SUBTYPE OF (face_surface);
     WHERE
        WR1:
           SIZEOF([ 'STEP_MERGED_AP_SCHEMA.ELEMENTARY_SURFACE', 'STEP_MERGED_AP_SCHEMA.B_SPLINE_SURFACE', 'STEP_MERGED_AP_SCHEMA.SWEPT_SURFACE' ] * TYPEOF(face_geometry)) = 1;
        wr2:
           SIZEOF(QUERY (elp_fbnds <* QUERY (bnds <* bounds| ('STEP_MERGED_AP_SCHEMA.EDGE_LOOP' IN TYPEOF(bnds.bound)))| NOT (SIZEOF(QUERY (oe <* elp_fbnds.bound\path.edge_list| NOT ('STEP_MERGED_AP_SCHEMA.EDGE_CURVE' IN TYPEOF(oe\oriented_edge.edge_element)))) = 0))) = 0;
        wr3:
           SIZEOF(QUERY (elp_fbnds <* QUERY (bnds <* bounds| ('STEP_MERGED_AP_SCHEMA.EDGE_LOOP' IN TYPEOF(bnds.bound)))| NOT (SIZEOF(QUERY (oe <* elp_fbnds.bound\path.edge_list| NOT (SIZEOF([ 'STEP_MERGED_AP_SCHEMA.LINE', 'STEP_MERGED_AP_SCHEMA.CONIC', 'STEP_MERGED_AP_SCHEMA.POLYLINE', 'STEP_MERGED_AP_SCHEMA.SURFACE_CURVE', 'STEP_MERGED_AP_SCHEMA.B_SPLINE_CURVE' ] * TYPEOF(oe.edge_element\edge_curve.edge_geometry)) = 1))) = 0))) = 0;
        wr4:
           SIZEOF(QUERY (elp_fbnds <* QUERY (bnds <* bounds| ('STEP_MERGED_AP_SCHEMA.EDGE_LOOP' IN TYPEOF(bnds.bound)))| NOT (SIZEOF(QUERY (oe <* elp_fbnds.bound\path.edge_list| NOT ((('STEP_MERGED_AP_SCHEMA.VERTEX_POINT' IN TYPEOF(oe\edge.edge_start)) AND ('STEP_MERGED_AP_SCHEMA.CARTESIAN_POINT' IN TYPEOF(oe\edge.edge_start\vertex_point.vertex_geometry))) AND (('STEP_MERGED_AP_SCHEMA.VERTEX_POINT' IN TYPEOF(oe\edge.edge_end)) AND ('STEP_MERGED_AP_SCHEMA.CARTESIAN_POINT' IN TYPEOF(oe\edge.edge_end\vertex_point.vertex_geometry)))))) = 0))) = 0;
        wr5:
           SIZEOF(QUERY (elp_fbnds <* QUERY (bnds <* bounds| ('STEP_MERGED_AP_SCHEMA.EDGE_LOOP' IN TYPEOF(bnds.bound)))| ('STEP_MERGED_AP_SCHEMA.ORIENTED_PATH' IN TYPEOF(elp_fbnds.bound)))) = 0;
        wr6:
           NOT ('STEP_MERGED_AP_SCHEMA.SWEPT_SURFACE' IN TYPEOF(face_geometry)) OR (SIZEOF([ 'STEP_MERGED_AP_SCHEMA.LINE', 'STEP_MERGED_AP_SCHEMA.CONIC', 'STEP_MERGED_AP_SCHEMA.POLYLINE', 'STEP_MERGED_AP_SCHEMA.B_SPLINE_CURVE' ] * TYPEOF(face_geometry\swept_surface.swept_curve)) = 1);
        wr7:
           SIZEOF(QUERY (vlp_fbnds <* QUERY (bnds <* bounds| ('STEP_MERGED_AP_SCHEMA.VERTEX_LOOP' IN TYPEOF(bnds.bound)))| NOT (('STEP_MERGED_AP_SCHEMA.VERTEX_POINT' IN TYPEOF(vlp_fbnds\face_bound.bound\vertex_loop.loop_vertex)) AND ('STEP_MERGED_AP_SCHEMA.CARTESIAN_POINT' IN TYPEOF(vlp_fbnds\face_bound.bound\vertex_loop.loop_vertex\vertex_point.vertex_geometry))))) = 0;
        wr8:
           SIZEOF(QUERY (bnd <* bounds| NOT (SIZEOF([ 'STEP_MERGED_AP_SCHEMA.EDGE_LOOP', 'STEP_MERGED_AP_SCHEMA.VERTEX_LOOP' ] * TYPEOF(bnd.bound)) = 1))) = 0;
        wr9:
           SIZEOF(QUERY (elp_fbnds <* QUERY (bnds <* bounds| ('STEP_MERGED_AP_SCHEMA.EDGE_LOOP' IN TYPEOF(bnds.bound)))| NOT (SIZEOF(QUERY (oe <* elp_fbnds.bound\path.edge_list| ('STEP_MERGED_AP_SCHEMA.SURFACE_CURVE' IN TYPEOF(oe\oriented_edge.edge_element\edge_curve.edge_geometry)) AND NOT (SIZEOF(QUERY (sc_ag <* oe.edge_element\edge_curve.edge_geometry\surface_curve.associated_geometry| NOT ('STEP_MERGED_AP_SCHEMA.PCURVE' IN TYPEOF(sc_ag)))) = 0))) = 0))) = 0;
        wr10:
           (NOT ('STEP_MERGED_AP_SCHEMA.SWEPT_SURFACE' IN TYPEOF(face_geometry)) OR (NOT ('STEP_MERGED_AP_SCHEMA.POLYLINE' IN TYPEOF(face_geometry\swept_surface.swept_curve)) OR (SIZEOF(face_geometry\swept_surface.swept_curve\polyline.points) >= 3))) AND (SIZEOF(QUERY (elp_fbnds <* QUERY (bnds <* bounds| ('STEP_MERGED_AP_SCHEMA.EDGE_LOOP' IN TYPEOF(bnds.bound)))| NOT (SIZEOF(QUERY (oe <* elp_fbnds.bound\path.edge_list| ('STEP_MERGED_AP_SCHEMA.POLYLINE' IN TYPEOF(oe\oriented_edge.edge_element\edge_curve.edge_geometry)) AND NOT (SIZEOF(oe\oriented_edge.edge_element\edge_curve.edge_geometry\polyline.points) >= 3))) = 0))) = 0);
  END_ENTITY;
 \endverbatim
 *
 * Объект <B>advanced_face</B> является специальным типом объекта <B>face_surface</B>, который имеет
 *  допол­нительные ограничения с тем, чтобы гарантировать то, что геометрия прямо и полностью определена.
 * Объект <B>advanced_face</B> является объектом верхнего уровня, который используется для формулировки
 * точного смысла топологически ограниченной поверхности, соответствующей области применения данной ПИК.<BR>
 * Требуется, чтобы объект <B>advanced_face</B> был полностью ограничен посредством объектов
 * <B>edge_loop</B> или <B>vertex_loop</B>.<BR>
 * Тип <B>face_outer_bound</B> может иметь не более одной границы (объект <B>bound</B>) грани.
 * <BR><SMALL>Примечание - Для некоторых типов замкнутых или частично замкнутых поверхностей может оказаться
 * невозможным установить единственную внешнюю границу.</SMALL><BR>
 * <U>Формальные утверждения</U><BR><UL>
 * <LI>WR1 - геометрия, используемая при определении грани, должна быть ограниченной. Тип геометрии грани должен быть elementary_surface, swept_surface или b_spline_surface.</LI>
 * <LI>WR2 - геометрия всех граничных ребер грани должна быть полностью определена через объекты <B>edge_curve</B>.</LI>
 * <LI>WR3 - типы линий, используемых для определения геометрии ребер, должны быть ограничены типами <B>line</B>, <B>conic</B>, <B>polyline</B>, <B>surface_curve</B> или <B>b_splines_curve</B>.</LI>
 * <LI>WR4 - вершины, используемые при определении грани, должны иметь тип <B>vertex_point</B> с геометрией, определенной объектом <B>cartesian_point</B>.</LI>
 * <LI>WR5 - запрещено использование ориентированных путей при определении объектов <B>edge_loop</B> объекта <B>advanced_face</B>.</LI>
 * <LI>WR6 - если геометрия грани имеет тип <B>swept_surface</B>, то используемый в ее определении объект <B>swept_curve</B> должен быть типа <B>line</B>, <B>conic</B>, <B>polyline</B> или <B>b_splines_curve</B>.</LI>
 * <LI>WR7 - для любого объекта <B>vertex_loop</B>, используемого для ограничения грани, объект <B>loop_vertex</B> должен иметь тип <B>vertex_point</B>, а геометрия должна быть определена посредством объекта
 * <B>cartesian_point</B>.</LI>
 * <LI>WR8 — границы грани должны быть определены посредством объектов либо <B>edge_loop</B>, либо <B>vertex_loop</B>.</LI>
 * <LI>WR9 — если объект <B>surface_curve</B> используется как часть границы грани, то атрибут объекта
 * <B>associated_geometry</B> должен ссылаться на объекты <B>pcurve</B>, но не на объекты <B>surface</B>.</LI>
 * <LI>WR10 — если объект <B>polyline</B> используется либо для определения объекта <B>swept_surface</B>, либо
 * как часть границы грани, то он должен содержать, по крайней мере, три точки.</LI>
 * </UL>
 * 
 * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_advanced_face.html">Ссылка.</A>
 */
class advanced_face : public face_surface {

public:

  /**
   * \brief Конструктор.
   * 
   * \param [in] Name
   * \param [in] Face_geometry
   * \param [in] Same_sense
   */
  advanced_face(const std::string &Name, const plane *Face_geometry, BOOLEAN::value Same_sense) :
    representation_item(Name),
    face_surface(Name, Face_geometry, Same_sense) {
    add_attr_info(STEP_ATTR_LIST({ { } }, this));
  }

  /** \brief Деструктор. */
  virtual ~advanced_face() {
  }
};


}
