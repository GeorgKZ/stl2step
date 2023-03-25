/**
 * \file
 *
 * \brief Файл с определениями классов, соответствующих ГОСТ Р ИСО 10303-511-2005.
 */

#include "express_typelist.h"

  /**
   * \file
   *
   * <HR>
   * \anchor p511
   * <CENTER>
   * \image html GOST.png
   * \image latex GOST.png width=1.5cm
   * </CENTER>
   * <CENTER><B>ГОСТ Р ИСО 10303-511-2006</B></CENTER>
   * <HR>
   * <H2>
   * <BR>Системы автоматизации производства и их интеграция ---<BR>
   * ПРЕДСТАВЛЕНИЕ ДАННЫХ ОБ ИЗДЕЛИИ И ОБМЕН ЭТИМИ ДАННЫМИ ---<BR>
   * Часть 511:<BR>
   * Прикладные интерпретированные конструкции:<BR>
   * Топологически ограниченная поверхность
   * </H2>
   *
   * \section p511_s1 1 Область применения
   *
   * Настоящий стандарт определяет интерпретацию интегрированных ресурсов, обеспечивающую
   * соответствие требованиям к определению грани с явными топологическими границами и полностью
   * определенной геометрией.
   *
   * Область применения настоящего стандарта распространяется на:
   * - трехмерную геометрию;
   * - би-сплайновые кривые и поверхности;
   * - кривые второго порядка;
   * - элементарные кривые;
   * - элементарные поверхности;
   * - полилинии;
   * - параметрические кривые;
   * - рельефные поверхности;
   * - поверхностные кривые, ссылающиеся на параметрические кривые;
   * - изогнутые поверхности;
   * - пространственные кривые;
   * - геометрию свободных форм;
   * - геометрические преобразования;
   * - использование топологии для ограничения геометрических объектов.
   *
   * Область применения настоящего стандарта не распространяется на:
   * - двумерную геометрию, кроме определения параметрических кривых в пространстве параметров
   * поверхности;
   * - ограниченные линии, кроме полилиний и би-сплайновых кривых;
   * - ограниченные поверхности, кроме би-сплайновых поверхностей;
   * - вынесенные линии и поверхности.
   *
   * \section p511_s2 2 Нормативные ссылки
   *
   * В настоящем стандарте использованы ссылки на следующие международные стандарты:
   *
   * ИСО/МЭК 8824-1:1995 Информационные технологии. Открытая взаимосвязь систем.
   * Абстрактная синтаксическая нотация Один (ASN.1). Часть 1. Спецификация базовой нотации
   *
   * ИСО 10303-1:1994 Системы автоматизации производства и их интеграция. Представление
   * данных об изделии и обмен этими данными. Часть 1. Общие представления и основополагающие принципы
   *
   * ИСО 10303-11:1994 Системы автоматизации производства и их интеграция. Представление
   * данных об изделии и обмен этими данными. Часть 11. Методы описания. Справочное руководство по языку EXPRESS
   *
   * ИСО 10303-41:1994 Системы автоматизации производства и их интеграция. Представление
   * данных об изделии и обмен этими данными. Часть41. Интегрированные обобщенные ресурсы. Основы
   * описания и поддержки изделий
   *
   * ИСО 10303-42:1994 Системы автоматизации производства и их интеграция. Представление
   * данных об изделии и обмен этими данными. Часть 42. Интегрированные обобщенные ресурсы.
   * Геометрическое и топологическое представление
   *
   * ИСО 10303-43:1994 Системы автоматизации производства и их интеграция. Представление
   * данных об изделии и обмен этими данными. Часть 43. Интегрированные обобщенные ресурсы. Структуры представлений
   *
   * ИСО 10303-202:1996 Системы автоматизации производства и их интеграция. Представление
   * данных об изделии и обмен этими данными. Часть 202. Прикладные протоколы. Ассоциативные чертежи
   *
   * \section p511_s3 3 Термины и определения
   *
   * \subsection p511_s3_1 3.1 Термины, определенные в ИС0 10303-1
   *
   * В настоящем стандарте применены следующие термины:
   * - <B>приложение</B> (application);
   * - <B>прикладной контекст</B> (application context);
   * - <B>прикладной протокол</B>; ПП (application protocol; АР);
   * - <B>метод реализации</B> (implementation method);
   * - <B>интегрированный ресурс</B> (integrated resource);
   * - <B>интерпретация</B> (interpretation);
   * - <B>модель</B> (model);
   * - <B>изделие</B> (product);
   * - <B>данные об изделии</B> (product data).
   *
   * \subsection p511_s3_2 3.2 Термины, определенные в ИС0 10303-42
   *
   * В настоящем стандарте применены следующие термины:
   * - <B>осесимметричный</B> (axi-symmetric);
   * - <B>граница</B> (boundary);
   * - <B>ограничения</B> (bounds);
   * - <B>координатное пространство</B> (coordinate space);
   * - <B>кривая</B> (curve);
   * - <B>незамкнутая кривая</B> (open curve);
   * - <B>ориентируемый</B> (orientable);
   * - <B>поверхность</B> (surface);
   * - <B>топологическое значение</B> (topological sense).
   *
   * \subsection p511_s3_3 3.3 Термин, определенный в ИС0 10303-202
   *
   * В настоящем стандарте применен следующий термин:
   * - <B>прикладная интерпретированная конструкция</B>; ПИК (application interpreted construct; AIC):
   * Логическая группировка интерпретируемых конструкций, которая поддерживает определенную
   * функцию для использования данных об изделии в контекстах различных приложений.
   *
   * \subsection p511_s3_4 3.4 Другие определения
   *
   * В настоящем стандарте также применены следующие термины с соответствующими определениями:
   *
   * \anchor p511_s3_4_1
   * 3.4.1 <B>расширенная грань</B> (advanced face): Грань, определенная на поверхности. Такая грань
   * является конечной частью поверхности, которая имеет свои границы, полностью определенные
   * посредством топологических объектов, соответствующих геометрическим кривым. Требуется, чтобы
   * геометрия поверхности соответствовала либо элементарной поверхности, либо изогнутой поверхности, либо
   * би-сплайновой поверхности.
   *
   * \anchor p511_s3_4_2
   * 3.4.2 <B>рельефная поверхность</B> (sculptured surface): Би-параметрическая поверхность
   * произвольной формы. В настоящем стандарте рельефная поверхность представляется би-сплайновой поверхностью.
   *
   * \anchor p511_s3_4_3
   * 3.4.3 <B>изогнутая поверхность</B> (swept surface): Поверхность, полученная путем перемещения или
   * вращения кривой.
   *
   * \anchor p511_s3_4_4
   * 3.4.4 <B>пространственная кривая</B> (twisted curve): Параметрическая кривая в трехмерном
   * пространстве. В настоящем стандарте пространственная кривая представляется би-сплайновой кривой.
   *
   * \section p511_s4 4 Сокращенный листинг на языке EXPRESS
   *
   * В настоящем разделе определена EXPRESS-схема, в которой используются элементы
   * интегрированных ресурсов и содержатся типы, конкретизации объектов и функции, относящиеся к настоящему стандарту.
   *
   * <SMALL>Примечание --- В интегрированных ресурсах допускается существование подтипов и элементов
   * списков выбора, не импортированных в данную ПИК. Такие конструкции исключают из дерева подтипов или из списка
   * выбора посредством правил неявного интерфейса, определенных в ИСО 10303-11. Ссылки на исключенные
   * конструкции находятся вне области применения данной ПИК. В некоторых случаях исключаются все элементы списка
   * выбора. Поскольку ПИК предназначены для реализации в контексте прикладного протокола, элементы списка
   * выбора будут определяться областью применения прикладного протокола.</SMALL>
   *
   * Данная интерпретируемая приложением конструкция предоставляет непротиворечивое
   * множество геометрических и топологических объектов для определения грани с полностью определенной
   * геометрией и явной топологией, определяющей ее границы. Допустимые типы геометрии грани включают в
   * себя элементарные и би-сплайновые поверхности. Требуется, чтобы геометрия ребер была определена
   * кривыми, в том числе параметрическими.
   *
   * Объектом самого верхнего уровня в данной ПИК является \ref express::advanced_face "advanced_face", который является
   * специализированным типом объекта \ref express::face_surface "face_surface" (см. \ref p42 "ИСО 10303-42"). Правила, относящиеся к этому
   * объекту, обеспечивают полное определение топологии и геометрии.
   *
   * <U>EXPRESS-спецификация</U>
   * \anchor aic_topologically_bounded_surface_schema
   <PRE>
   *)
   SCHEMA aic_topologically_bounded_surface;
    USE FROM \ref geometry_schema
     (\ref express::axis2_placement_2d "axis2_placement_2d",
      \ref express::axis2_placement_3d "axis2_placement_3d",
      bezier_curve,
      bezier_surface,
      b_spline_curve_with_knots,
      b_spline_surface_with_knots,
      \ref express::cartesian_point "cartesian_point",
      \ref express::circle "circle",
      composite_curve_on_surface,
      \ref express::conical_surface "conical_surface",
      cylindrical_surface,
      degenerate_toroidal_surface,
      \ref express::direction "direction",
      ellipse,
      \ref express::geometric_representation_context "geometric_representation_context",
      hyperbola,
      line,
      parabola,
      pcurve,
      plane,
      polyline,
      quasi_uniform_curve,
      quasi_uniform_surface,
      rational_b_spline_curve,
      rational_b_spline_surface,
      spherical_surface,
      surface_curve,
      surface_of_linear_extrusion,
      surface_of_revolution,
      swept_surface,
      toroidal_surface,
      uniform_curve,
      uniform_surface,
      \ref express::vector "vector");
    USE FROM topology_schema
     (\ref express::edge "edge",
      \ref express::edge_curve "edge_curve",
      \ref express::edge_loop "edge_loop",
      \ref express::face_bound "face_bound",
      \ref express::face_outer_bound "face_outer_bound",
      \ref express::face_surface "face_surface",
      \ref express::oriented_edge "oriented_edge",
      \ref express::path "path",
      \ref express::vertex_loop "vertex_loop",
      \ref express::vertex_point "vertex_point");
    USE FROM representation_schema
     (\ref express::definitional_representation "definitional_representation",
      parametric_representation_context);
    USE FROM measure_schema (parameter_value);
   (*
   </PRE>
   * <SMALL>Примечания
   *
   * 1 Для объектов \ref express::edge "edge", \ref express::path "path" и \ref express::swept_surface "swept_surface"
   * установлены явные интерфейсы, т.е. они включены в списки операторов USE FORM для того, чтобы позволить правилам,
   * действующим в рамках объекта \ref express::advanced_face "advanced_face", получить
   * доступ к атрибутам этих объектов. Для использования данной ПИК требуется только, чтобы эти объекты
   * реализовывались в виде одного из своих подтипов.
   *
   * 2 Схемы, на которые выше даны ссылки, можно найти в следующих стандартах комплекса ИС0 10303:
   *
   * geometry_schema --- ИС0 10303-42;
   *
   * topology_schema --- ИС0 10303-42;
   *
   * representation_schema --- ИСО 10303-43;
   *
   * measure schema --- ИСО 10303-41.</SMALL>
   *
   * \subsection p511_s4_1 4.1 Основные понятия и допущения
   *
   * Подразумевается, что независимой реализации в схемах прикладных протоколов, в которых
   * используется данная ПИК, подлежат следующие объекты:
   <PRE>
       \ref express::advanced_face "advanced_face";
       \ref express::axis2_placement_2d "axis2_placement_2d";
       \ref express::axis2_placement_3d "axis2_placement_3d";
       bezier_curve;
       bezier_surface;
       b_spline_curve_with_knots;
       b_spline_surface_with_knots;
       \ref express::cartesian_point "cartesian_point";
       \ref express::circle "circle";
       \ref express::conical_surface "conical_surface";
       \ref express::definitional_representation "definitional_representation";
       degenerate_toroidal_surface;
       cylindrical_surface;
       \ref express::direction "direction";
       \ref express::edge_curve "edge_curve";
       \ref express::edge_loop "edge_loop";
       ellipse;
       \ref express::face_bound "face_bound";
       \ref express::face_outer_bound "face_outer_bound";
       \ref express::face_surface "face_surface";
       \ref express::geometric_representation_context "geometric_representation_context";
       hyperbola;
       \ref express::line "line";
       parabola;
       parametric_representation_context;
       pcurve;
       plane;
       polyline;
       quasi_uniform_curve;
       quasi_uniform_surface;
       rational_b_spline_curve;
       rational_b_spline_surface;
       spherical_surface;
       surface_of_linear_extrusion;
       surface_of_revolution;
       toroidal_surface;
       uniform_curve;
       uniform_surface;
       \ref express::vector "vector";
       \ref express::vertex_loop "vertex_loop";
       \ref express::vertex_point "vertex_point".
   </PRE>
   * Прикладной протокол, использующий данную ПИК, должен требовать, чтобы поддерживались все
   * вышеперечисленные объекты.
   *
   * Прикладной протокол, использующий данную ПИК, должен требовать, чтобы объект \ref express::face "face"
   * реализовывался как объект \ref express::advanced_face "advanced_face".
   *
   * <BR>
   *
   * \copydetails express::advanced_face
   *
   * <BR>
   *
   * <U>EXPRESS-спецификаиия</U>
   *
   <PRE>
   *)
     END_SCHEMA; - конец схемы AIC_TOPOLOGICALLY_BOUNDED_SURFACE
   (*
   </PRE>
   *
   */


namespace express {

  /**
   * \brief ENTITY advanced_face (ГОСТ Р ИСО 10303-511-2006, 4.2)
   *
   * \ref express::advanced_face "4.2 Определение объекта advanced_face схемы aic_topologically_bounded_surface"
   *
   * Объект \ref express::advanced_face "advanced_face" является специальным типом объекта \ref express::face_surface "face_surface", который имеет
   * дополнительные ограничения с тем, чтобы гарантировать то, что геометрия прямо и полностью определена.
   * Объект \ref express::advanced_face "advanced_face" является объектом верхнего уровня, который используется для формулировки
   * точного смысла топологически ограниченной поверхности, соответствующей области применения данной ПИК.
   *
   * Требуется, чтобы объект \ref express::advanced_face "advanced_face" был полностью ограничен посредством объектов
   * \ref express::edge_loop "edge_loop" или express::vertex_loop "vertex_loop".
   *
   * Тип \ref express::face_outer_bound "face_outer_bound" может иметь не более одной границы (объект \ref express::face_bound.bound "bound") грани.
   *
   * <SMALL>Примечание --- Для некоторых типов замкнутых или частично замкнутых поверхностей может оказаться
   * невозможным установить единственную внешнюю границу.</SMALL>
   *
   * <B><I>Примеры
   *
   * 1 Любой объект</I> \ref express::edge_loop "edge_loop" <I>на плоской поверхности может использоваться для определения
   * объекта</I> \ref express::face_outer_bound "face_outer_bound" <I>при условии, что он не заключен в какой-либо другой замкнутой цепи на грани.
   *
   * 2 Окружная замкнутая петля вокруг цилиндрической поверхности (объект</I> cylindrical_surface<I>) не
   * может определять объект</I> \ref express::face_outer_bound "face_outer_bound"<I>, так как она не окружает замкнутую область поверхности.</I></B>
   *
   * <U>EXPRESS-спецификация</U>
   <PRE>
   *)
   ENTITY \ref express::advanced_face "advanced_face"
      SUBTYPE OF (\ref express::face_surface "face_surface");
      WHERE
         WR1:
            SIZEOF([ 'STEP_MERGED_AP_SCHEMA.ELEMENTARY_SURFACE', 'STEP_MERGED_AP_SCHEMA.B_SPLINE_SURFACE',
                     'STEP_MERGED_AP_SCHEMA.SWEPT_SURFACE' ] * TYPEOF(face_geometry)) = 1;
         wr2:
            SIZEOF(QUERY (elp_fbnds <* QUERY (bnds <* bounds |
                  ('STEP_MERGED_AP_SCHEMA.EDGE_LOOP' IN TYPEOF(bnds.bound))) |
                  NOT (SIZEOF(QUERY (oe <* elp_fbnds.bound\\path.edge_list |
                  NOT ('STEP_MERGED_AP_SCHEMA.EDGE_CURVE'
                  IN TYPEOF(oe\\oriented_edge.edge_element)))) = 0))) = 0;
         wr3:
            SIZEOF(QUERY (elp_fbnds <* QUERY (bnds <* bounds |
                  ('STEP_MERGED_AP_SCHEMA.EDGE_LOOP' IN TYPEOF(bnds.bound))) |
                  NOT (SIZEOF(QUERY (oe <* elp_fbnds.bound\\path.edge_list |
                  NOT (SIZEOF([ 'STEP_MERGED_AP_SCHEMA.LINE', 'STEP_MERGED_AP_SCHEMA.CONIC',
                  'STEP_MERGED_AP_SCHEMA.POLYLINE', 'STEP_MERGED_AP_SCHEMA.SURFACE_CURVE',
                  'STEP_MERGED_AP_SCHEMA.B_SPLINE_CURVE' ] *
                  TYPEOF(oe.edge_element\\edge_curve.edge_geometry)) = 1))) = 0))) = 0;
         wr4:
            SIZEOF(QUERY (elp_fbnds <* QUERY (bnds <* bounds |
                  ('STEP_MERGED_AP_SCHEMA.EDGE_LOOP' IN TYPEOF(bnds.bound))) |
                  NOT (SIZEOF(QUERY (oe <* elp_fbnds.bound\\path.edge_list |
                  NOT ((('STEP_MERGED_AP_SCHEMA.VERTEX_POINT' IN TYPEOF(oe\\edge.edge_start))
                 AND ('STEP_MERGED_AP_SCHEMA.CARTESIAN_POINT'
                 IN TYPEOF(oe\\edge.edge_start\\vertex_point.vertex_geometry)))
                 AND (('STEP_MERGED_AP_SCHEMA.VERTEX_POINT' IN TYPEOF(oe\\edge.edge_end))
                 AND ('STEP_MERGED_AP_SCHEMA.CARTESIAN_POINT'
                 IN TYPEOF(oe\\edge.edge_end\\vertex_point.vertex_geometry)))))) = 0))) = 0;
         wr5:
            SIZEOF(QUERY (elp_fbnds <* QUERY (bnds <* bounds| ('STEP_MERGED_AP_SCHEMA.EDGE_LOOP'
            IN TYPEOF(bnds.bound)))| ('STEP_MERGED_AP_SCHEMA.ORIENTED_PATH' IN TYPEOF(elp_fbnds.bound)))) = 0;
         wr6:
            NOT ('STEP_MERGED_AP_SCHEMA.SWEPT_SURFACE' IN TYPEOF(face_geometry)) OR
            (SIZEOF([ 'STEP_MERGED_AP_SCHEMA.LINE', 'STEP_MERGED_AP_SCHEMA.CONIC',
             'STEP_MERGED_AP_SCHEMA.POLYLINE', 'STEP_MERGED_AP_SCHEMA.B_SPLINE_CURVE' ] *
             TYPEOF(face_geometry\\swept_surface.swept_curve)) = 1);
         wr7:
            SIZEOF(QUERY (vlp_fbnds <* QUERY (bnds <* bounds| ('STEP_MERGED_AP_SCHEMA.VERTEX_LOOP'
            IN TYPEOF(bnds.bound)))| NOT (('STEP_MERGED_AP_SCHEMA.VERTEX_POINT'
            IN TYPEOF(vlp_fbnds\\face_bound.bound\\vertex_loop.loop_vertex)) AND
            ('STEP_MERGED_AP_SCHEMA.CARTESIAN_POINT'
            IN TYPEOF(vlp_fbnds\\face_bound.bound\\vertex_loop.loop_vertex\\vertex_point.vertex_geometry))))) = 0;
         wr8:
            SIZEOF(QUERY (bnd <* bounds| NOT (SIZEOF([ 'STEP_MERGED_AP_SCHEMA.EDGE_LOOP',
            'STEP_MERGED_AP_SCHEMA.VERTEX_LOOP' ] * TYPEOF(bnd.bound)) = 1))) = 0;
         wr9:
            SIZEOF(QUERY (elp_fbnds <* QUERY (bnds <* bounds| ('STEP_MERGED_AP_SCHEMA.EDGE_LOOP'
            IN TYPEOF(bnds.bound))) | NOT (SIZEOF(QUERY (oe <* elp_fbnds.bound\\path.edge_list |
            ('STEP_MERGED_AP_SCHEMA.SURFACE_CURVE'
            IN TYPEOF(oe\\oriented_edge.edge_element\\edge_curve.edge_geometry)) AND NOT
            (SIZEOF(QUERY (sc_ag <* oe.edge_element\\edge_curve.edge_geometry\\surface_curve.associated_geometry|
            NOT ('STEP_MERGED_AP_SCHEMA.PCURVE' IN TYPEOF(sc_ag)))) = 0))) = 0))) = 0;
         wr10:
            (NOT ('STEP_MERGED_AP_SCHEMA.SWEPT_SURFACE' IN TYPEOF(face_geometry)) OR
            (NOT ('STEP_MERGED_AP_SCHEMA.POLYLINE' IN TYPEOF(face_geometry\\swept_surface.swept_curve)) OR
            (SIZEOF(face_geometry\\swept_surface.swept_curve\\polyline.points) >= 3))) AND
            (SIZEOF(QUERY (elp_fbnds <* QUERY (bnds <* bounds| ('STEP_MERGED_AP_SCHEMA.EDGE_LOOP'
            IN TYPEOF(bnds.bound)))| NOT (SIZEOF(QUERY (oe <* elp_fbnds.bound\\path.edge_list |
            ('STEP_MERGED_AP_SCHEMA.POLYLINE' IN TYPEOF(oe\\oriented_edge.edge_element\\edge_curve.edge_geometry))
            AND NOT (SIZEOF(oe\\oriented_edge.edge_element\\edge_curve.edge_geometry\\polyline.points)
            >= 3))) = 0))) = 0);
   END_ENTITY;
   (*
   </PRE>
   *
   * <U>Формальные утверждения</U>
   *
   * <B>WR1</B> --- геометрия, используемая при определении грани, должна быть ограниченной. Тип геометрии грани должен быть
   * \ref express::elementary_surface "elementary_surface", \ref express::swept_surface "swept_surface" или \ref express::b_spline_surface "b_spline_surface".
   *
   * <B>WR2</B> --- геометрия всех граничных ребер грани должна быть полностью определена через объекты \ref express::edge_curve "edge_curve".
   *
   * <B>WR3</B> --- типы линий, используемых для определения геометрии ребер, должны быть ограничены типами
   * \ref express::line "line", \ref express::conic "conic", \ref express::polyline "polyline", \ref express::surface_curve "surface_curve" или \ref express::b_spline_curve "b_spline_curve".
   *
   * <B>WR4</B> --- вершины, используемые при определении грани, должны иметь тип \ref express::vertex_point "vertex_point"
   * с геометрией, определенной объектом \ref express::cartesian_point "cartesian_point".
   *
   * <B>WR5</B> --- запрещено использование ориентированных путей при определении объектов \ref express::edge_loop "edge_loop"
   * объекта \ref express::advanced_face "advanced_face".
   *
   * <B>WR6</B> --- если геометрия грани имеет тип \ref express::swept_surface "swept_surface", то используемый в её
   * определении объект \ref express::swept_surface "swept_surface" должен быть типа
   * \ref express::line "line", \ref express::conic "conic", \ref express::polyline "polyline" или \ref express::b_spline_curve "b_spline_curve".
   *
   * <B>WR7</B> --- для любого объекта \ref express::vertex_loop "vertex_loop", используемого для ограничения грани, объект
   * \ref express::vertex_loop.loop_vertex "loop_vertex" должен иметь тип \ref express::vertex_point "vertex_point", а геометрия должна
   * быть определена посредством объекта \ref express::cartesian_point "cartesian_point".
   *
   * <B>WR8</B> --- границы грани должны быть определены посредством объектов либо
   * \ref express::edge_loop "edge_loop", либо \ref express::vertex_loop "vertex_loop".
   *
   * <B>WR9</B> --- если объект \ref express::surface_curve "surface_curve" используется как часть границы грани,
   * то атрибут объекта \ref express::surface_curve.associated_geometry "associated_geometry" должен ссылаться на объекты
   * \ref express::pcurve "pcurve", но не на объекты \ref express::surface "surface".
   *
   * <B>WR10</B> --- если объект \ref express::polyline "polyline" используется либо для определения объекта
   * \ref express::swept_surface "swept_surface", либо как часть границы грани, то он должен содержать,
   * по крайней мере, три точки.
   *
   * <U>Неформальное утверждение</U>
   *
   * <B>IP1</B> --- любой экземпляр объекта \ref express::advanced_face "advanced_face", который имеет геометрию полной сферической
   * поверхности (объект \ref express::spherical_surface "spherical_surface"), должен быть ограничен посредством объекта \ref express::vertex_loop "vertex_loop",
   * расположенного в точке, где ось Z системы координат выходитза пределы поверхности сферы (то есть в точке «Северный Полюс» сферы).
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_advanced_face.html">Ссылка 1,</A>
   * <A HREF="http://www.steptools.com/stds/smrl/data/modules/topologically_bounded_surface/sys/4_info_reqs.htm#topologically_bounded_surface_arm.advanced_face">Ссылка 2.</A>
   */
  class advanced_face : public face_surface {

  public:

    /**
     * \brief Конструктор неопределённого объекта.
     */ 
    advanced_face() : representation_item(), face_surface() {
      add_attr_info(STEP_ATTR_LIST({ { } }, this));
    }

    /**
     * \brief Конструктор.
     *
     * \param [in] Name
     * \param [in] Face_geometry
     * \param [in] Same_sense
     */
    advanced_face(const std::string& Name, const plane* Face_geometry, const BOOLEAN& Same_sense) :
      representation_item(Name),
      face_surface(Name, Face_geometry, Same_sense) {
      add_attr_info(STEP_ATTR_LIST({ { } }, this));
    }

    /** \brief Деструктор. */
    virtual ~advanced_face() = default;
  };
}