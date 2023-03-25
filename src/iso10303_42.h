/**
 * \file
 * \brief Файл с определениями классов, соответствующих ISO 10303-42:2021(E).
 */

namespace express {

  /**
   * \file
   *
   * <HR>
   * \anchor p42
   * <CENTER>
   * \image html ISO.png
   * \image latex ISO.png width=1.5cm
   * </CENTER>
   * <CENTER><B>ISO 10303-42:2021(E)</B></CENTER>
   * <HR>
   * <H2>
   * Industrial automation systems and integration —<BR>
   * Product data representation and exchange —<BR>
   * Part 42:<BR>
   * Integrated generic resource:<BR>
   * Geometric and topological representation
   * </H2>
   *
   * \section p42_s1 1 Scope
   *
   * This document specifies the integrated generic resource constructs for geometric and topological
   * representation. The following are within the scope of this document:
   *
   * \subsection p42_s1_1 1.1 Geometry
   *
   * The following are in the scope of the geometry schema:<BR>
   * * definition of points, vectors, parametric curves and parametric surfaces;
   * * definition of finite volumes with internal parametrisation;
   * * definition of transformation operators;
   * * points defined directly by their coordinate values or in terms of the parameters of an existing curve or surface;
   * * definition of conic curves and elementary surfaces;
   * * definition of curves defined on a parametric surface;
   * * definition of general parametric spline curves, surfaces and volumes;
   * * definition of locally refined spline curves, surfaces and volumes;
   * * definition of point, curve and surface replicas;
   * * definition of offset curves and surfaces;
   * * definition of intersection curves.
   *
   * \subsection p42_s1_2 1.2 Topology
   *
   * The following are in the scope of the topology schema:<BR>
   * * definition of the fundamental topological entities vertex, edge, and face, each with
   * a specialised subtype to enable it to be associated with the geometry of a point, curve,
   * or surface, respectively;
   * * collections of the basic entities to form topological structures of path, loop and shell
   * and constraints to ensure the integrity of these structures;
   * * the association of faces with geometric volumes;
   * * orientation of topological entities.
   *
   * \subsection p42_s1_3 1.3 Geometric Shape Models
   * The following are in the scope of the geometric model schema:<BR>
   * * data describing the precise geometric form of three-dimensional solid
   * objects;
   * * constructive solid geometry (CSG) models;
   * * CSG models in two-dimensional space;
   * * definition of CSG primitives and half-spaces;
   * * creation of solid models by sweeping operations;
   * * manifold boundary representation (B-rep) models;
   * * constraints to ensure the integrity of B-rep models;
   * * surface models;
   * * wireframe models;
   * * geometric sets;
   * * creation of a replica of a solid model in a new location;
   * * tessellated geometry;
   * * the association of tessellated geometry with exact geometry.
   *
   *  The following are in the scope of the scan data 3d shape model schema:
   * * representation of a shape as a cloud of points produced by a scanning process.
   *
   * The following are outside the scope of this document:
   *
   * * all other forms of procedurally defined curves and surfaces;
   * * curves and surfaces which do not have a parametric form of representation;
   * * any form of explicit representation of a ruled surface.
   *
   * <SMALL>NOTE For a ruled surface the geometry is critically dependent upon the parametrisation
   * of the boundary curves and the method of associating pairs of points on the two curves. A ruled
   * surface with B-spline boundary curves can however be exactly represented by the B-spline surface entity.</SMALL>
   *
   * * spatial occupancy forms of solid models (such as octree models);
   * * geometric tolerances;
   * * implicit forms of representation in terms of features;
   * * assemblies and mechanisms.
   *
   * \section p42_s2 2 Normative references
   *
   * The following documents are referred to in the text in such a way that some or all of their content
   * constitutes requirements of this document. For dated references, only the edition cited applies.
   * For undated references, the latest edition of the referenced document (including any amendments) applies.
   *
   * ISO 10303-1, <I>Industrial automation systems and integration — Product data representation and exchange — Part 1:
   * Overview and fundamental principles</I>
   *
   * ISO 10303-11, <I>Industrial automation systems and integration — Product data representation and exchange — Part 11:
   * Description methods: The EXPRESS language reference manual</I>
   *
   * ISO 10303-41, <I>Industrial automation systems and integration — Product data representation and exchange — Part 41:
   * Integrated generic resource: Fundamentals of product description and support</I>
   *
   * ISO 10303-43, <I>Industrial automation systems and integration — Product data representation and exchange — Part 43:
   * Integrated generic resource: Representation structures</I>
   *
   * \section p42_s3 3 Terms, definitions and abbreviated terms
   *
   * \subsection p42_s3_1 3.1 Terms and definitions
   *
   * \subsubsection p42_s3_1_1 3.1.1 Terms defined in ISO 10303-1
   *
   * For the purposes of this document, the following terms defined in ISO 10303-1 apply:
   *
   * * integrated resource.
   *
   * \subsubsection p42_s3_1_2 3.1.2 Other terms and definitions
   *
   * For the purposes of this document, the following terms and definitions apply:
   *
   * \paragraph p42_s3_1_2_1 3.1.2.1
   * <I>d</I><B>-manifold with boundary</B><BR>
   * a domain which is the union of its <I>d</I>-dimensional interior and its boundary. 
   *
   * \paragraph p42_s3_1_2_2 3.1.2.2
   * <B>arcwise connected</B><BR>
   * such that any pair of distinct points in the relevant domain may be connected by
   * a continuous arc entirely contained within that domain.
   *
   * \paragraph p42_s3_1_2_3 3.1.2.3
   * <B>axi-symmetric</B><BR>
   * invariant under all rotations about a central axis.
   *
   * \paragraph p42_s3_1_2_4 3.1.2.4
   * <B>boundary</B><BR>
   * subset of the points \f$ x \f$ in a domain \f$ X \f$ having the property that any
   * open ball \f$ U \f$ centred on \f$ x \f$ satisfies \f$ U \cap X \neq U \f$.
   *
   * <SMALL>NOTE Any open ball centred on the boundary of the domain will contain both points inside
   * the domain and points outside the domain.</SMALL>
   *
   * \paragraph p42_s3_1_2_5 3.1.2.5
   * <B>boundary representation solid model (B-rep)</B><BR>
   * type of geometric model in which the size and shape of a solid is defined in terms of the faces,
   * edges and vertices which make up its boundary.
   *
   * \paragraph p42_s3_1_2_6 3.1.2.6
   * <B>bounds</B><BR>
   * limits of a topological entity.
   *
   * <SMALL>NOTE Bounds are the topological entities of lower dimensionality which mark the limits
   * of a topological entity. The bounds of a face are loops, and the bounds of an edge are vertices.</SMALL>
   *
   * \paragraph p42_s3_1_2_7 3.1.2.7
   * <B>closed curve</B><BR>
   * curve such that both end points are the same.
   *
   * \paragraph p42_s3_1_2_8 3.1.2.8
   * <B>closed surface</B><BR>
   * connected 2-manifold that divides space into exactly two connected components, one of which is finite.
   *
   * \paragraph p42_s3_1_2_9 3.1.2.9
   * <B>completion of a topological entity</B><BR>
   * set consisting of the entity in question together with all the faces, edges and vertices referenced,
   * directly or indirectly, in the definition of the bounds of that entity.
   *
   * \paragraph p42_s3_1_2_10 3.1.2.10
   * <B>connected</B><BR>
   * synonym for arcwise connected.
   *
   * \paragraph p42_s3_1_2_11 3.1.2.11
   * <B>connected component</B><BR>
   * maximal connected subset of a domain
   *
   * \paragraph p42_s3_1_2_12 3.1.2.12
   * <B>constructive solid geometry (CSG)</B><BR>
   * type of geometric modelling in which a solid is defined as the result of a sequence of regularised
   * Boolean operations operating on solid models.
   *
   * \paragraph p42_s3_1_2_13 3.1.2.13
   * <B>coordinate space</B><BR>
   * reference system that associates a unique set of \f$ n \f$ parameters with each point in an \f$ n \f$-dimensional space.
   *
   * \paragraph p42_s3_1_2_14 3.1.2.14
   * <B>curve</B><BR>
   * set of mathematical points which is the image, in two- or three-dimensional space, of a continuous
   * function defined over a connected subset of the real line \f$ (R^1) \f$, and which is not a single point.
   *
   * \paragraph p42_s3_1_2_15 3.1.2.15
   * <B>cycle</B><BR>
   * chain of alternating vertices and edges in a graph such that the first and last vertices are the same.
   *
   * \paragraph p42_s3_1_2_16 3.1.2.16
   * <B>dimensionality</B><BR>
   * number of independent coordinates in the parameter space of a geometric entity.
   *
   * <SMALL>NOTE A curve has dimensionality 1, a surface has dimensionality 2. The dimensionality of topological
   * entities which need not have domains is specified in the entity definitions. The dimensionality of a list
   * or set is the maximum of the dimensionalities of the elements of that list or set.</SMALL>
   *
   * \paragraph p42_s3_1_2_17 3.1.2.17
   * <B>domain</B><BR>
   * mathematical point set in model space corresponding to an entity.
   *
   * \paragraph p42_s3_1_2_18 3.1.2.18
   * <B>euler equations</B><BR>
   * equations used to verify the topological consistency of objects.
   *
   * <SMALL>NOTE Various equalities relating topological properties of entities are derived from the invariance
   * of a number known as the Euler characteristic. Typically, these are used as quick checks on the integrity
   * of the topological structure. A violation of an Euler condition signals an "impossible" object. Two special
   * cases are important in this document. The Euler equation for graphs is discussed in 5.2.3. Euler conditions
   * for surfaces are discussed in 5.4.25 and 5.2.27.</SMALL>
   *
   * \paragraph p42_s3_1_2_19 3.1.2.19
   * <B>extent</B><BR>
   * measure of the domain of a geometric entity in units appropriate to the dimensionality of the entity.
   *
   * <SMALL>NOTE Length, area and volume are used for dimensionalities 1, 2, and 3, respectively. Where necessary,
   *  the symbol \f$ \Xi \f$ will be used to denote extent.</SMALL>
   *
   * \paragraph p42_s3_1_2_20 3.1.2.20
   * <B>facet</B><BR>
   * a planar triangle.
   *
   * \paragraph p42_s3_1_2_21 3.1.2.21
   * <B>finite</B><BR>
   * capable of being completely counted or measured.
   *
   * <SMALL>NOTE An entity is finite (or alternatively bounded) if there is a finite upper bound on the distance
   * between any two points in its domain.</SMALL>
   *
   * \paragraph p42_s3_1_2_22 3.1.2.22
   * <B>genus of a graph</B><BR>
   * integer-valued invariant defined algorithmically by the graph traversal algorithm.
   *
   * <SMALL>NOTE The graph traversal algorithm is described in the note in 5.2.3.</SMALL>
   *
   * \paragraph p42_s3_1_2_23 3.1.2.23
   * <B>genus of a surface</B><BR>
   * number of handles that are added to a sphere to produce a surface homeomorphic to the surface in question.
   *
   * <SMALL>NOTE Handle is defined below.</SMALL>
   *
   * \paragraph p42_s3_1_2_24 3.1.2.24
   * <B>geometric coordinate system</B><BR>
   * underlying global rectangular Cartesian coordinate system to which all geometry refers.
   *
   * \paragraph p42_s3_1_2_25 3.1.2.25
   * <B>geometrically founded</B><BR>
   * having an associated coordinate space.
   *
   * <SMALL>NOTE Geometric founding is a property of geometric_representation_item s (see 4.4.2) asserting
   * their relationship to a coordinate space in which the coordinate values of points and directions on
   * which they depend for position and orientation are measured.</SMALL>
   *
   * \paragraph p42_s3_1_2_26 3.1.2.26
   * <B>geometrically related</B><BR>
   * related by being in the same geometric context.
   *
   * <SMALL>NOTE If two geometric_representation_item s (see 4.4.2) are geometricaslly related then the concepts
   * of distance and direction between them are defined.</SMALL>
   *
   * \paragraph p42_s3_1_2_27 3.1.2.27
   * <B>graph</B><BR>
   * set of vertices and edges.
   *
   * <SMALL>NOTE The graphs discussed in this document are generally called pseudographs in the technical literature
   * because they allow self-loops and also multiple edges connecting the same two vertices.</SMALL>
   *
   * \paragraph p42_s3_1_2_28 3.1.2.28
   * <B>handle</B><BR>
   * structure distinguishing a torus from a sphere, which can be viewed as a tubular surface connecting
   * two holes in a surface.
   *
   * \paragraph p42_s3_1_2_29 3.1.2.29
   * <B>homeomorphic</B><BR>
   * in one to one correspondence.
   *
   * <SMALL>NOTE Domains \f$ X \f$ and \f$ Y \f$ are homeomorphic if there is a continuous
   * function \f$ f \f$ from \f$ X \f$ to \f$ Y \f$ which is a one-to-one correspondence, so that the inverse
   * function \f$ f^{-1} \f$ exists, and \f$ f^{-1} \f$ is also continuous.</SMALL>
   *
   * \paragraph p42_s3_1_2_30 3.1.2.30
   * <B>inside</B><BR>
   * completely included within.
   *
   * <SMALL>NOTE A domain \f$ X \f$ is inside domain \f$ Y \f$ if both domains are contained in the same Euclidean
   * space, \f$ R^m \f$, and \f$ Y \f$ separates \f$ R^m \f$ into exactly two connected components, one of which is
   * finite, and \f$ X \f$ is contained in the finite component.</SMALL>
   *
   * \paragraph p42_s3_1_2_31 3.1.2.31
   * <B>interior</B><BR>
   * point set resulting from exclusion of all boundary points from a bounded point set.
   *
   * <SMALL>NOTE The \f$ d \f$-dimensional interior of a \f$ d \f$-dimensional domain \f$ X \f$ contained in
   * \f$ R^m \f$ is the set of mathematical points \f$ x \f$ in \f$ X \f$ for which there is an open ball \f$ U \f$
   * in \f$ R^m \f$ containing \f$ x \f$ such that the intersection \f$ U \cap X \f$ is homeomorphic
   * to an open ball in \f$ R^d \f$.</SMALL>
   *
   * \paragraph p42_s3_1_2_32 3.1.2.32
   * <B>list</B><BR>
   * ordered homogeneous collection with possibly duplicate members.
   *
   * \paragraph p42_s3_1_2_33 3.1.2.33
   * <B>model space</B><BR>
   * space with dimensionality 2 or 3 in which the geometry of a representation of a physical object,
   * or any of its elements, is defined.
   *
   * \paragraph p42_s3_1_2_34 3.1.2.34
   * <B>open curve</B><BR>
   * curve which has two distinct end points.
   *
   * \paragraph p42_s3_1_2_35 3.1.2.35
   * <B>open surface</B><BR>
   * surface which is a manifold with boundary, but is not closed.
   *
   * <SMALL>NOTE Either it is not finite, or it does not divide space into exactly two connected components.</SMALL>
   *
   * \paragraph p42_s3_1_2_36 3.1.2.36
   * <B>orientable</B><BR>
   * capable of being oriented in space.
   *
   * <SMALL>NOTE A surface is orientable if a consistent, continuously varying choice can be made of the sense
   * of the normal vectors to the surface. This does not require a continuously varying choice of the values
   * of the normal vectors; the surface may have tangent plane discontinuities.</SMALL>
   *
   * \paragraph p42_s3_1_2_37 3.1.2.37
   * <B>overlap</B><BR>
   * area or range shared in common by two or more geometric elements.
   *
   * <SMALL>NOTE Two topological entities overlap when they have shells, faces, edges, or vertices in common.</SMALL>
   *
   * \paragraph p42_s3_1_2_38 3.1.2.38
   * <B>parameter range</B><BR>
   * range of valid parameter values for a curve, surface, or volume.
   *
   * \paragraph p42_s3_1_2_39 3.1.2.39
   * <B>parameter space</B><BR>
   * one-dimensional space associated with a curve via its uniquely defined parameterisation, or the two-dimensional
   * space associated with a surface.
   *
   * \paragraph p42_s3_1_2_40 3.1.2.40
   * <B>parametric volume</B><BR>
   * bounded region of three dimensional model space with an associated parametric coordinate system such that every
   * interior point is associated with a list \f$ (u,v,w) \f$ of parameter values.
   *
   * \paragraph p42_s3_1_2_41 3.1.2.41
   * <B>placement coordinate system</B><BR>
   * rectangular Cartesian coordinate system associated with the placement of a geometric entity in space.
   *
   * <SMALL>NOTE This is used to describe the interpretation of the attributes and to associate a unique parameterisation
   * with curve and surface entities.</SMALL>
   *
   * \paragraph p42_s3_1_2_42 3.1.2.42
   * <B>self-intersect</B><BR>
   * intersection of a geometric element with itself.
   *
   * <SMALL> NOTE A curve or surface self-intersects if there is a mathematical point in its domain which is
   * the image of at least two points in the object's parameter range, and one of those two points lies
   * in the interior of the parameter range. A vertex, edge or face self-intersects if its domain does.</SMALL>
   *
   * <SMALL>NOTE A curve or surface is not considered to be self-intersecting just because it is closed.</SMALL>
   *
   * \paragraph p42_s3_1_2_43 3.1.2.43
   * <B>self-loop</B><BR>
   * edge that has the same vertex at both ends.
   *
   * \paragraph p42_s3_1_2_44 3.1.2.44
   * <B>set</B><BR>
   * unordered collection in which no two members are equal.
   *
   * \paragraph p42_s3_1_2_45 3.1.2.45
   * <B>space dimensionality</B><BR>
   * number of parameters required to define the location of a point in the coordinate space.
   *
   * \paragraph p42_s3_1_2_46 3.1.2.46
   * <B>surface</B><BR>
   * set of mathematical points which is the image of a continuous function defined over
   * a connected subset of the plane \f$ (R^2) \f$.
   *
   * \paragraph p42_s3_1_2_47 3.1.2.47
   * <B>tessellated geometry</B><BR>
   * geometry composed of a large number of planar tiles, usually of triangular shape.
   *
   * <SMALL>NOTE Tessellated geometry is frequently used as an approximation to the exact shape of an object.</SMALL>
   *
   * \paragraph p42_s3_1_2_48 3.1.2.48
   * <B>topological sense</B><BR>
   * sense of a topological entity as derived from the order of its attributes.
   *
   * <SMALL>EXAMPLE 1 The topological sense of an edge is from the edge start vertex to the edge end vertex.</SMALL>
   *
   * <SMALL>EXAMPLE 2 The topological sense of a path follows the edges in their listed order.</SMALL>
   *
   * \subsection p42_s3_2 3.2 Abbreviated terms
   *
   * For the purposes of this document, the following abbreviated terms apply:
   *
   * <B>URL:</B> uniform resource locator<BR>
   * <B>B-rep:</B> boundary representation solid model<BR>
   * <B>CSG:</B> constructive solid geometry<BR>
   *
   * \section p42_s4 4 Geometry schema
   *
   * \subsection p42_s4_1 4.1 General
   *
   * The subject of the \ref p42_s4 "geometry_schema" is the geometry of parametric curves and surfaces. The
   * \ref p43_s4 "representation_schema" (see \ref p43 "ISO 10303-43") and the
   * \ref express::geometric_representation_context "geometric_representation_context" defined in this
   * Part of ISO 10303, provide the context in which the geometry is defined. The
   * \ref express::geometric_representation_context "geometric_representation_context"
   * enables a distinction to be made between those items which are in the same context, and thus geometrically related,
   * and those existing in independent coordinate spaces. In particular, each
   * \ref express::geometric_representation_item "geometric_representation_item" has a
   * \ref express::geometric_representation_context "geometric_representation_context"
   * which includes as an attribute the Euclidean dimension of its coordinate
   * space. The coordinate system for this space is referred to as the geometric coordinate system in this clause.
   * Units associated with \ref express::length_measure "length_measure"s and
   * \ref express::plane_angle_measure "plane_angle_measure"s are assumed to be assigned globally
   * within this context. A global rule (\ref p42_s4_7_1 "compatible_dimension") ensures that all
   * \ref express::geometric_representation_item "geometric_representation_item"s
   * in the same
   * \ref express::geometric_representation_context "geometric_representation_context"
   * have the same space dimensionality. The space dimensionality
   * \ref express::geometric_representation_item._dim() "dim"
   * is a derived attribute of all subtypes of
   * \ref express::geometric_representation_item "geometric_representation_item".
   *
   * This clause defines the information requirements to which implementations shall conform using the EXPRESS language
   * as defined in ISO 10303-11. The following EXPRESS declaration begins the \ref p42_s4 "geometry_schema" and identifies the
   * necessary external references.
   *
   * Each implementation of an AP that uses this schema and that encodes entity names shall use the encoding specified in
   * Annex A. Each reference to this schema in an open system shall use the identifier encoding specified in Annex B.
   * This schema is illustrated in Annex D using the EXPRESS-G notation.
   *
   * <U>EXPRESS specification:</U>
   * \anchor geometry_schema
   <PRE>
    *)
    SCHEMA geometry_schema;

    REFERENCE FROM geometric_model_schema    --  ISO 10303-42
      (block,
       boolean_result,
       cyclide_segment_solid,
       eccentric_cone,
       edge_based_wireframe_model,
       ellipsoid,
       face_based_surface_model,
       faceted_primitive,
       geometric_set,
       half_space_solid,
       primitive_2d,
       rectangular_pyramid,
       right_angular_wedge,
       right_circular_cone,
       right_circular_cylinder,
       shell_based_surface_model,
       shell_based_wireframe_model,
       solid_model,
       sphere,
       tessellated_item,
       torus);

    REFERENCE FROM measure_schema    --  ISO 10303-41
      (global_unit_assigned_context,
       length_measure,
       parameter_value,
       plane_angle_measure,
       plane_angle_unit,
       positive_length_measure,
       positive_plane_angle_measure);

    REFERENCE FROM representation_schema    --  ISO 10303-43
      (definitional_representation,
       founded_item,
       functionally_defined_transformation,
       item_in_context,
       representation,
       \ref express::representation_context "representation_context",
       \ref express::representation_item "representation_item",
       using_representations);

    REFERENCE FROM scan_data_3d_shape_model_schema    --  ISO 10303-42
      (scanned_data_item);

    REFERENCE FROM topology_schema    --  ISO 10303-42
      (\ref express::edge_curve "edge_curve",
       face_surface,
       poly_loop,
       vertex_point,
       volume_with_faces);
    (*
    </PRE>
   *
   * <SMALL>NOTE 1 The schemas referenced above are specified in the following parts:
   * * <B>geometric_model_schema</B> ISO 10303-42
   * * <B>measure_schema</B> ISO 10303-41
   * * <B>representation_schema</B> ISO 10303-43
   * * <B>scan_data_3d_shape_model_schema</B> ISO 10303-42
   * * <B>topology_schema</B> ISO 10303-42
   * 
   * NOTE 2 See Annex D for a graphical representation of this schema.</SMALL>
   *
   * \subsection p42_s4_2 4.2 Fundamental concepts and assumptions
   *
   * \subsubsection p42_s4_2_1 4.2.1 Space Dimensionality
   * All geometry shall be defined in a right-handed rectangular Cartesian coordinate system with the same
   * units on each axis. A common scheme has been used for the definition of both two-dimensional and
   * three-dimensional geometry. Points and directions exist in both a two-dimensional and a three-dimensional
   * form; these forms are distinguished solely by the presence, or absence, of a third coordinate value.
   * Complex geometric entities are all defined using points and directions from which their space dimensionality
   * can be deduced. 
   *
   * \subsubsection p42_s4_2_2 Geometric relationships
   * All \ref express::geometric_representation_item "geometric_representation_item"s which are included as
   * \ref express::representation.items "items" in a \ref express::representation "representation" having a
   * \ref express::geometric_representation_context "geometric_representation_context"
   * are geometrically related. Any such
   * \ref express::geometric_representation_item "geometric_representation_item"
   * is said to be geometrically founded in the context of that
   * \ref express::representation "representation". No geometric relationship,
   * such as distance between points, is assumed to exist for
   * \ref express::geometric_representation_item "geometric_representation_item"s
   * occurring as \ref express::representation.items "items" in different
   * \ref express::representation "representation"s. 
   *
   * \subsubsection p42_s4_2_3 4.2.3 Parametrisation of analytic curves and surfaces
   * Each curve or surface specified here has a defined parametrisation. In some instances the definitions
   * are in parametric terms. In others, the conic curves and elementary surfaces, the definitions are in
   * geometric terms. In this latter case a placement coordinate system is used to define the parametrisation.
   * The geometric definitions contain some, but not all, of the data required for this. The relevant data to define
   * this placement coordinate system is contained in the \ref express::axis2_placement "axis2_placement" associated with the individual curve and
   * surface entities. Where the curve or surface parameterisation uses trigonometric functions, the parameter for
   * the function behaves like an angle and can be considered to be an angular parameter. Numerical values for such
   * angular parameters shall use the current units for <B>plane_angle_measure</B>.
   *
   * \subsubsection p42_s4_2_4 4.2.4 Curves
   * The curve entities defined in this schema include lines, elementary conics, a general parametric polynominal curve,
   * and some referentially or procedurally defined curves. All the curves have a well defined parametrisation which makes
   * it possible to trim a curve or identify points on the curve by parameter value. The geometric direction of a curve is
   * the direction of increasing parameter value. For the conic curves, a method of representation is used which separates
   * their geometric form from their orientation and position in space. In each case, the position and orientation information
   * is conveyed by an \ref express::axis2_placement "axis2_placement". The general purpose parametric curve is represented by the <B>b_spline_curve</B> entity.
   * This was selected as the most stable form of representation for the communication of all types of polynomial and
   * rational parametric curves. With appropriate attribute values and subtypes, a <B>b_spline_curve</B> entity is capable of
   * representing single span or spline curves of explicit polynomial, rational, Bézier or B-spline type.
   * A <B>composite_curve</B> entity, which includes the facility to communicate continuity information at the curve-to-curve
   * transition points, is provided for the construction of more complex curves.
   *
   * The <B>offset_curve</B> and <B>curve_on_surface</B> types are curves defined with reference to other geometry.
   * Separate offset_curve entities exist for 2D and 3D applications. The curve on surface entities include an
   * <B>intersection_curve</B> which represents the intersection of two surfaces. Such a curve may be represented
   * in 3D space or in the 2D parameter space of either of the surfaces.
   *
   * \subsubsection p42_s4_2_5 4.2.5 Surfaces
   * The surface entities support the requirements of simple boundary representation (B-rep) solid modelling system
   * and enable the communication of general polynomial and rational parametric surfaces. The simple surfaces are
   * the planar, spherical, cylindrical, conical and toroidal surfaces, a <B>surface_of_revolution</B> and a
   * <B>surface_of_linear_extrusion</B>. As with curves, all surfaces have an associated standard parametrisation.
   * In many cases the surfaces, as defined, are unbounded; it is assumed that they will be bounded either explicitly
   * or implicitly. Explicit bounding is achieved with the <B>rectangular_trimmed_surface</B> or <B>curve_bounded_surface</B>
   * entities; implicit bounding requires the association of additional topological information to define a <B>face</B>.
   *
   * The <B>b_spline_surface</B> entity and its subtypes provide the most general capability for the communication of
   * all types of polynomial and rational biparametric surfaces. This entity uses control points as the most stable
   * form of representation for the surface geometry. The <B>offset_surface</B> entity is intended for the communication of
   * a surface obtained as a simple normal offset from a given surface. The <B>rectangular_composite_surface</B> entity
   * provides the basic capability to connect together a rectangular mesh of distinct surface patches, specifying
   * the degree of continuity from patch to patch.
   *
   * \subsubsection p42_s4_2_6 4.2.6 Preferred form
   * Some of the geometric entities provide the potential capability of defining an item of geometry in more than one way.
   * Such multiple representations are accommodated by requiring the nomination of a `preferred form' or `master
   * representation'. This is the form which is used to determine the parametrisation.
   *
   * <SMALL>NOTE The <B>master_representation</B> attribute acknowledges the impracticality of ensuring that multiple forms
   * are indeed identical and allows the indication of a preferred form. This would probably be determined by the
   *  creator of the data. All characteristics, such as parametrisation, domain, and results of evaluation, for
   * an entity having multiple representations, are derived from the master representation. Any use of the other
   * representations is a compromise for practical considerations.</SMALL>
   *
   * <CENTER><B>Table 1 — Geometry mathematical symbology</B>
   * <TABLE border="1" cellpadding="2" cellspacing="0">
   * <tr><th><b>Symbol</b></th><th><b>Definition</b></th></tr>
   * <tr><td>\f$ a \f$</td><td>Scalar quantity</td></tr>
   * <tr><td><B>A</B></td><td>Vector quantity</td></tr>
   * <tr><td>\f$ \langle \rangle \f$</td><td>Vector normalisation</td></tr>
   * <tr><td><B>a</B></td><td>Normalised vector \f$ \langle \f$ <b>A</b> \f$ \rangle = \f$ <b>A</b> \f$ / | \f$ <b>A</b> \f$ | \f$</td></tr>
   * <tr><td>\f$  \times \f$</td><td>Vector (cross) product</td></tr>
   * <tr><td>\f$  \cdot \f$</td><td>Scalar product</td></tr>
   * <tr><td><B>A</B>\f$ \to \f$<B>B</B></td><td><B>A</B> is transformed to <B>B</B></td></tr>
   * <tr><td>\f$ \lambda (u) \f$</td><td>Parametric curve</td></tr>
   * <tr><td>\f$ \sigma (u,v) \f$</td><td>Parametric surface</td></tr>
   * <tr><td>\f$ S(x,y,z) \f$</td><td>Analytic surface</td></tr>
   * <tr><td>\f$ C_x \f$</td><td>Partial differential of \f$ C \f$ with respect to \f$ x \f$</td></tr>
   * <tr><td>\f$ \sigma _u \f$</td><td>Partial differential of \f$ \sigma (u,v) \f$ with respect to \f$ u \f$</td></tr>
   * <tr><td>\f$ S_x \f$</td><td>Partial derivative of \f$ S \f$ with respect to \f$ x \f$ </td></tr>
   * <tr><td>\f$ | \f$ \f$ | \f$</td><td>Absolute value, or magnitude or determinant</td></tr>
   * <tr><td>\f$ R^m \f$</td><td> m-dimensional real space</td></tr>
   * </TABLE></CENTER>
   *
   * \subsection p42_s4_3 4.3 Geometry constant definition
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
    *)
    CONSTANT
    (*
   </PRE>
   *
   * \copydetails express::dummy_gri
   * 
   <PRE>
    *)
    END_CONSTANT;
    (* 
   </PRE>
   *
   * \subsection p42_s4_4 4.4 geometry_schema type definitions
   *
   * \copydetails express::axis2_placement
   *
   * \subsubsection p42_s4_4_4 4.4.4 curve_on_surface
   *
   * \copydetails express::dimension_count
   *
   * <B>4.4.6 extent_enumeration</B>
   *
   * <B>4.4.7 knot_type</B>
   *
   * <B>4.4.8 linearly_independent_enum</B>
   *
   * <B>4.4.9 locally_refined_spline_type_enum</B>
   *
   * \subsubsection p42_s4_4_9 4.4.9 pcurve_or_surface
   *
   * \copydetails express::pcurve_or_surface
   *
   * \subsubsection p42_s4_4_11 4.4.11 preferred_surface_curve_representation
   *
   * \copydetails express::preferred_surface_curve_representation
   */

  /**
   * \brief dummy_gri (ISO 10303-42:2021(E), 4.3.1)
   *
   * \ref express::dummy_gri "4.3.1 dummy_gri"
   *
   * A \ref express::dummy_gri "dummy_gri" is a partial entity definition to be used when
   * types of \ref express::geometric_representation_item "geometric_representation_item" are constructed.
   * It provides the correct supertypes and the <B>name</B> attribute
   * as an empty string.
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
    *)
      \ref express::dummy_gri "dummy_gri": \ref express::geometric_representation_item "geometric_representation_item" :=
      \ref express::representation_item "representation_item"('') || \ref express::geometric_representation_item "geometric_representation_item"();
    (*
   </PRE>
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_constant.html">Ссылка 1, </A>
   * <A HREF="http://www.steptools.com/stds/smrl/data/resource_docs/geometric_and_topological_representation/sys/4_schema.htm#geometry_schema.dummy_gri">Ссылка 2.</A>
   */
  extern const geometric_representation_item dummy_gri;

  /**
   * \brief TYPE axis2_placement (ISO 10303-42:2021(E), 4.4.1)
   *
   * \ref express::axis2_placement "4.4.1 axis2_placement"
   *
   * The \ref express::axis2_placement "axis2_placement" type is a list of alternate data types. It provides
   * a mechanism to refer to an instance of one of these data types. The \ref express::axis2_placement "axis2_placement"
   * type represents the placing of mutually perpendicular axes in two-dimensional or
   * in three-dimensional Cartesian space.
   *
   * <SMALL>NOTE This select type enables entities requiring axis placement information
   * to reference the axes without specifying the space dimensionality.</SMALL>
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
    *)
    TYPE \ref express::axis2_placement "axis2_placement" = SELECT
          (axis2_placement_2d,
           \ref express::axis2_placement_3d "axis2_placement_3d");
    END_TYPE;
    (*
   </PRE>
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_axis2_placement.html">Ссылка 1, </A>
   * <A HREF="http://www.steptools.com/stds/smrl/data/resource_docs/geometric_and_topological_representation/sys/4_schema.htm#geometry_schema.axis2_placement">Ссылка 2.</A>
   */
  class axis2_placement : public SELECT {

  public:

//  /** \brief Конструктор из типа axis2_placement_2d */
//  axis2_placement(const axis2_placement_2d* t);

    /** \brief Конструктор из типа axis2_placement_3d */
    axis2_placement(const axis2_placement_3d* t);
  };

  /**
   * \brief 4.4.2 b_spline_curve_form
   */
  class b_spline_curve_form : public ENUMERATION {
  private:

    enum
#if !defined(__DOXYGEN__)
      class
#endif 
      value {
        polyline_form,
        circular_arc,
        elliptic_arc,
        parabolic_arc,
        hyperbolic_arc,
        unspecified
      };

    value _x;

  public:

    static const value polyline_form = value::polyline_form;
    static const value circular_arc = value::circular_arc;
    static const value elliptic_arc = value::elliptic_arc;
    static const value parabolic_arc = value::parabolic_arc;
    static const value hyperbolic_arc = value::hyperbolic_arc;
    static const value unspecified = value::unspecified;

    /** \brief Конструктор неопределённого типа */
    b_spline_curve_form() : ENUMERATION(false), _x(unspecified) {
    }

    /** \brief Конструктор из типа LOGICAL::value */
    b_spline_curve_form(value v) : _x(v) {
    }

    /** \brief Деструктор */
    virtual ~b_spline_curve_form() = default;

    /** \brief Получение значения */
    operator value () const {
      return _x;
    }

    /**
     * \brief Вывод значения типа
     */
    virtual std::string print_value() const {
      if (!determinated) {
        return "$";
      }

      std::stringstream s;
      switch(_x) {
      case polyline_form:
        s << ".POLYLINE_FORM.";
        break;
      case circular_arc:
        s << ".CIRCULAR_ARC.";
        break;
      case elliptic_arc:
        s << ".ELLIPTIC_ARC.";
        break;
      case parabolic_arc:
        s << ".PARABOLIC_ARC.";
        break;
      case hyperbolic_arc:
        s << ".HYPERBOLIC_ARC.";
        break;
      case unspecified:
        s << ".UNSPECIFIED.";
        break;
      default:
        throw exception {"b_spline_curve_form::print_value(): Wrong b_spline_curve_form::value"};
        break;
      }
      return s.str();
    }
  };

   /**
    * \brief TYPE b_spline_surface_form (ISO 10303-42:2021(E), 4.4.3)
    */
  class b_spline_surface_form : public ENUMERATION {

  private:

    enum
#if !defined(__DOXYGEN__)
      class
#endif 
      value {
        plane_surf,
        cylindrical_surf,
        conical_surf,
        spherical_surf,
        toroidal_surf,
        surf_of_revolution,
        ruled_surf,
        generalised_cone,
        quadric_surf,
        surf_of_linear_extrusion,
        unspecified
    };

    value _x;

  public:

    static const value plane_surf = value::plane_surf;
    static const value cylindrical_surf = value::cylindrical_surf;
    static const value conical_surf = value::conical_surf;
    static const value spherical_surf = value::spherical_surf;
    static const value toroidal_surf = value::toroidal_surf;
    static const value surf_of_revolution = value::surf_of_revolution;
    static const value ruled_surf = value::ruled_surf;
    static const value generalised_cone = value::generalised_cone;
    static const value quadric_surf = value::quadric_surf;
    static const value surf_of_linear_extrusion = value::surf_of_linear_extrusion;
    static const value unspecified = value::unspecified;


    /** \brief Конструктор неопределённого типа */
    b_spline_surface_form() : ENUMERATION(false), _x(unspecified) {
    }

    /** \brief Конструктор из типа LOGICAL::value */
    b_spline_surface_form(value v) : _x(v) {
    }

    /** \brief Деструктор */
    virtual ~b_spline_surface_form() = default;

    /** \brief Получение значения */
    operator value () const {
      return _x;
    }

    /**
     * \brief Вывод значения типа
     */
    virtual std::string print_value() const {
      if (!determinated) {
        return "$";
      }

      std::stringstream s;
      switch(_x) {
      case plane_surf:
        s << ".PLANE_SURF.";
        break;
      case cylindrical_surf:
        s << ".CYLINDRICAL_SURF.";
        break;
      case conical_surf:
        s << ".CONICAL_SURF.";
        break;
      case spherical_surf:
        s << ".SPHERICAL_SURF.";
        break;
      case toroidal_surf:
        s << ".TOROIDAL_SURF.";
        break;
      case surf_of_revolution:
        s << ".SURF_OF_REVOLUTION.";
        break;
      case ruled_surf:
        s << ".RULED_SURF.";
        break;
      case generalised_cone:
        s << ".GENERALISED_CONE.";
        break;
      case quadric_surf:
        s << ".QUADRIC_SURF.";
        break;
      case surf_of_linear_extrusion:
        s << ".SURF_OF_LINEAR_EXTRUSION.";
        break;
      case unspecified:
        s << ".UNSPECIFIED.";
        break;
      default:
        throw exception {"b_spline_surface_form::print_value(): Wrong b_spline_surface_form::value"};
        break;
      }
      return s.str();
    }
  };

  /**
   * \brief TYPE dimension_count (ISO 10303-42:2021(E), 4.4.5)
   *
   * \ref express::dimension_count "4.4.5 dimension_count"
   *
   * A \ref express::dimension_count "dimension_count" is a positive integer used to define the coordinate space
   * dimensionality of a \ref express::geometric_representation_context "geometric_representation_context".
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
    TYPE \ref express::dimension_count "dimension_count" = INTEGER;
       WHERE
          WR1:
             SELF > 0;
    END_TYPE;
   </PRE>
   * <U>Formal propositions:</U>
   *
   * <B>WR1:</B> A \ref express::dimension_count "dimension_count" shall be positive.
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_dimension_count.html">Ссылка 1, </A>
   * <A HREF="http://www.steptools.com/stds/smrl/data/resource_docs/geometric_and_topological_representation/sys/4_schema.htm#geometry_schema.dimension_count">Ссылка 2.</A>
   */
  class dimension_count : public INTEGER {

  public:

    /** \brief Конструктор неопределённого типа */
    dimension_count() : INTEGER() {
    }

    /** \brief Конструктор из INTEGER */
    dimension_count(const INTEGER& v) : INTEGER(v) {
      assert(this->get_value() > 0);
    }

    /** \brief Получить тип объекта - определённый тип */
    virtual OBJTYPE objtype() const {
      return OBJTYPE::OBJ_DEFINED;
    }
  };

   /**
    * \brief TYPE pcurve_or_surface (ISO 10303-42:2021(E), 4.4.10)
    *
    * \ref express::pcurve_or_surface "4.4.10 pcurve_or_surface"
    *
    * This select type enables a surface curve to identify as an
    * attribute the associated surface or pcurve.
    *
    * <U>EXPRESS specification:</U>
    <PRE>
     *)
     TYPE pcurve_or_surface = SELECT
           (pcurve,
            surface);
     END_TYPE;
     (*
    </PRE>
    *
    * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_pcurve_or_surface.html">Ссылка 1, </A>
    * <A HREF="http://www.steptools.com/stds/smrl/data/resource_docs/geometric_and_topological_representation/sys/4_schema.htm#geometry_schema.curve_on_surface">Ссылка 2.</A>
    */
  class pcurve_or_surface : public SELECT {

  public:

    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(pcurve_or_surface, pcurve);
    //  STEP_TYPE_SELECT_CONSTRUCTOR_DEF(pcurve_or_surface, surface);
  };

  /**
   * \brief TYPE preferred_surface_curve_representation (ISO 10303-42:2021(E), 4.4.11)
   *
   * \ref express::preferred_surface_curve_representation "4.4.11 preferred_surface_curve_representation"
   *
   * The \ref express::preferred_surface_curve_representation "preferred_surface_curve_representation"
   * type is used to indicate the preferred form of representation for a surface curve, which is either a curve in
   * geometric space or in the parametric space of the underlying surfaces.
   *
   * <U>EXPRESS specification:</U>
   <PRE>
    *)
    TYPE preferred_surface_curve_representation = ENUMERATION OF
          (curve_3d,
           pcurve_s1,
           pcurve_s2);
    END_TYPE;
    (*
   </PRE>
   * <U>Enumerated item definitions:</U><BR>
   * <B>curve_3d:</B> the curve in three-dimensional space is preferred;<BR>
   * <B>pcurve_s1:</B> the first pcurve is preferred;<BR>
   * <B>pcurve_s2:</B> the second pcurve is preferred;
   *
    * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_preferred_surface_curve_representation.html">Ссылка 1, </A>
    * <A HREF="http://www.steptools.com/stds/smrl/data/resource_docs/geometric_and_topological_representation/sys/4_schema.htm#geometry_schema.preferred_surface_curve_representation">Ссылка 2.</A>
    */
  class preferred_surface_curve_representation : public ENUMERATION {

  private:

    enum
#if !defined(__DOXYGEN__)
      class
#endif 
      value {
        /** \brief the curve in three-dimensional space is preferred; */
        curve_3d,
        /** \brief the first pcurve is preferred; */
        pcurve_s1,
        /** \brief the second pcurve is preferred. */
        pcurve_s2
    };

    value _x;

  public:

    static const value curve_3d  = value::curve_3d;
    static const value pcurve_s1 = value::pcurve_s1;
    static const value pcurve_s2 = value::pcurve_s2;

    /** \brief Конструктор неопределённого типа */
    preferred_surface_curve_representation() : ENUMERATION(false), _x(curve_3d) {
    }

    /** \brief Конструктор из типа preferred_surface_curve_representation::value */
    preferred_surface_curve_representation(value v) : _x(v) {
    }

    /** \brief Деструктор */
    virtual ~preferred_surface_curve_representation() = default;

    /** \brief Получение значения */
    operator value () const {
      return _x;
    }

    /** \brief Вывод значения типа */
    std::string print_value() const {
      if (!determinated) {
        return "$";
      }

      std::stringstream s;
      switch (_x) {
      case curve_3d:  s << ".CURVE_3D.";  break;
      case pcurve_s1: s << ".PCURVE_S1."; break;
      case pcurve_s2: s << ".PURVE_S2.";  break;
      default:
        throw exception {"preferred_surface_curve_representation::print_value(): Wrong value"};
        break;
      }
      return s.str();
    }
  };

  /**
   * \file
   * <B>4.4.12 spline_knot_values</B>
   *
   * <B>4.4.13 surface_boundary</B>
   *
   * <B>4.4.14 transition_code</B>
   *
   * <B>4.4.15 trimming_preference</B>
   *
   * <B>4.4.16 trimming_select</B>
   */


  /**
   * \file
   * \copydetails express::vector_or_direction
   */

  /**
   * \brief TYPE vector_or_direction (ISO 10303-42:2021(E), 4.4.17)
   *
   * \ref express::vector_or_direction "4.4.17 vector_or_direction"
   *
   * The \ref express::vector_or_direction "vector_or_direction" type is a list of alternate data types. It provides
   * a mechanism to refer to an instance of one of these data types. This type is used to
   * identify the types of entity which can participate in vector computations.
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
    -- DIFF IN AP214
    -- DIFF IN AP203e2
    -- DIFF IN AP224
    -- DIFF IN AP232
    TYPE vector_or_direction = SELECT
          (direction,
           vector);
    END_TYPE;
   </PRE>
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_vector_or_direction.html">Ссылка 1, </A>
   * <A HREF="http://www.steptools.com/stds/smrl/data/resource_docs/geometric_and_topological_representation/sys/4_schema.htm#geometry_schema.vector_or_direction">Ссылка 2.</A>
   */
  class vector_or_direction : public SELECT {

  public:

    /** \brief Конструктор неопределённого типа */
    vector_or_direction() : SELECT(){
    }

    /** \brief Конструктор из типа vector */
    vector_or_direction(const vector& t);

    /** \brief Конструктор из типа direction */
    vector_or_direction(const direction& t);

    /** \brief Проверка принадлежности к типу vector */
    bool is_vector() const {
      return get_type_name().compare("vector");
    }

    /** \brief Проверка принадлежности к типу direction */
    bool is_direction() const {
      return get_type_name().compare("direction");
    }

    /** \brief Преобразование к vector неявное */
    operator const vector& () const;

    /** \brief Преобразование к vector явное */
    const vector& _vector() const;

    /** \brief Преобразование к direction неявное */
    operator const direction& () const;

    /** \brief Преобразование к direction явное */
    const direction& _direction() const;

    /** \brief Получить значение размености (количества координат) объекта */
    dimension_count get_dim() const;
  };

  /**
   * \file
   * \subsection p42_s4_5 4.5 geometry_schema entity definitions
   *
   * \copydetails express::geometric_representation_context
   */

  /**
   * \brief ENTITY geometric_representation_context (ISO 10303-42:2021, 4.5.1)
   *
   * \ref express::geometric_representation_context "4.5.1 geometric_representation_context"
   *
   * A \ref express::geometric_representation_context "geometric_representation_context" is a type of
   * \ref express::representation_context "representation_context" in which
   * \ref express::geometric_representation_item "geometric_representation_item"s are geometrically founded.
   *
   * A \ref express::geometric_representation_context "geometric_representation_context" is a distinct
   * coordinate space, spatially unrelated to other coordinate spaces except as those coordinate spaces
   * are specifically related by an appropriate transformation. (See \ref p42_s3_2 "3.2" for definitions of geometrically
   * founded and coordinate space.).
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
    -- DIFF IN AP214
    -- DIFF IN AP203e2
    -- DIFF IN AP224
    -- DIFF IN AP232
    *)
    ENTITY geometric_representation_context
       SUPERTYPE OF (ONEOF(geometric_representation_context_with_parameter, path_parameter_representation_context))
       SUBTYPE OF (representation_context);
          coordinate_space_dimension : dimension_count;
    END_ENTITY;
    (*
   </PRE>
   *
   * <U>Определения атрибутов:</U>
   *
   * \ref express::geometric_representation_context.coordinate_space_dimension "coordinate_space_dimension": the number of dimensions of the coordinate
   * space which is the \ref express::geometric_representation_context "geometric_representation_context".
   *
   * <SMALL>NOTE Any constraints on the allowed range of \ref express::geometric_representation_context.coordinate_space_dimension "coordinate_space_dimension"
   * are outside the scope of this part of ISO 10303.</SMALL>
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_geometric_representation_context.html">Ссылка 1, </A>
   * <A HREF="http://www.steptools.com/stds/smrl/data/resource_docs/geometric_and_topological_representation/sys/4_schema.htm#geometry_schema.geometric_representation_context">Ссылка 2.</A>
   */
  class geometric_representation_context : public representation_context {

  private:

    /**
     * \brief The number of dimensions of the coordinate
     * space which is the \ref express::geometric_representation_context "geometric_representation_context".
     */
    const dimension_count* coordinate_space_dimension;

  public:

    /** \brief Конструктор */
    geometric_representation_context(const std::string& Identifier, const std::string& Type, const dimension_count& Dimension);

    /** \brief Деструктор */
    virtual ~geometric_representation_context();

    /** \brief Получить количество измерений контекста */
    const dimension_count& get_coordinate_space_dimension() const {
      return *coordinate_space_dimension;
    }
  };

  /**
   * \file
   * \copydetails express::geometric_representation_item
   */

  /**
   * \brief ENTITY geometric_representation_item (ISO 10303-42:2021(E), 4.5.2)
   *
   * \ref express::geometric_representation_item "4.5.2 geometric_representation_item"
   *
   * A \ref express::geometric_representation_item "geometric_representation_item" is a type of
   * \ref express::representation_item "representation_item" that has the additional meaning of
   * having geometric position or orientation or both.
   *
   * This meaning is present by virtue of:
   * * being a \ref express::cartesian_point "cartesian_point" or a \ref express::direction "direction";
   * * referencing directly a \ref express::cartesian_point "cartesian_point" or a \ref express::direction "direction";
   * * referencing indirectly a \ref express::cartesian_point "cartesian_point" or a \ref express::direction "direction".
   *
   * <SMALL>NOTE 1 An indirect reference to a \ref express::cartesian_point "cartesian_point" or a \ref express::direction "direction"
   * means that a given \ref express::geometric_representation_item "geometric_representation_item" references the
   * \ref express::cartesian_point "cartesian_point" or \ref express::direction "direction" through one or more
   * intervening attributes. In many cases this information is given in the form of an
   * \ref express::axis2_placement "axis2_placement".
   * </SMALL>
   *
   * <SMALL>EXAMPLE 1 Consider a circle. It gains its geometric position and orientation by virtue of a reference to an
   * \ref express::axis2_placement "axis2_placement" that in turn references a \ref express::cartesian_point "cartesian_point"
   * and several \ref express::direction "direction"s.
   * </SMALL>
   *
   * <SMALL>EXAMPLE 2 A \ref express::manifold_solid_brep "manifold_solid_brep" is a
   * \ref express::geometric_representation_item "geometric_representation_item" that through several layers
   * of \ref express::topological_representation_item "topological_representation_item"s,
   * references, \ref express::curve "curve"s, \ref express::surface "surface"s
   * and \ref express::point "point"s. Through additional intervening entities curves and surfaces reference
   * \ref express::cartesian_point "cartesian_point" and \ref express::direction "direction".
   * </SMALL>
   *
   * <SMALL>NOTE 2 The intervening entities, which are all of type \ref express::representation_item, "representation_item"
   * need not be of subtype \ref express::geometric_representation_item "geometric_representation_item".
   * Consider the \ref express::manifold_solid_brep "manifold_solid_brep" from the above example. One of the
   * intervening levels of \ref express::representation_item "representation_item" is a
   * \ref express::closed_shell "closed_shell". This is a \ref express::topological_representation_item "topological_representation_item"
   * and does not require a \ref express::geometric_representation_context "geometric_representation_context"
   * in its own right. When used as part of the definition of a
   * \ref express::manifold_solid_brep "manifold_solid_brep" that itself is a
   * \ref express::geometric_representation_item "geometric_representation_item", it is founded in a
   * \ref express::geometric_representation_context "geometric_representation_context".
   * </SMALL>
   *
   * <SMALL>NOTE 3 A \ref express::geometric_representation_item "geometric_representation_item"
   * inherits the need to be related to a \ref express::representation_context "representation_context"
   * in a representation.
   * </SMALL>
   *
   * <SMALL>NOTE 4 As subtypes of \ref express::representation_item "representation_item" there is an implicit
   * and/or relationship between \ref express::geometric_representation_item "geometric_representation_item"
   * and \ref express::topological_representation_item "topological_representation_item". The only complex instances
   * intended to be created are \ref express::edge_curve "edge_curve",
   * \ref express::face_surface "face_surface", and \ref express::vertex_point "vertex_point".
   * </SMALL>
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
    -- DIFF IN AP214
    -- DIFF IN AP203e2
    -- DIFF IN AP238 STEP-NC
    -- DIFF IN AP224
    -- DIFF IN AP232
    ENTITY geometric_representation_item
       SUPERTYPE OF (ONEOF (point,
                            direction,
                            vector,
                            placement,
                            cartesian_transformation_operator,
                            curve,
                            surface,
                            edge_curve,
                            face_surface,
                            poly_loop,
                            vertex_point,
                            solid_model,
                            boolean_result,
                            sphere,
                            right_circular_cone,
                            right_circular_cylinder,
                            torus,
                            block,
                            primitive_2d,
                            right_angular_wedge,
                            ellipsoid,
                            faceted_primitive,
                            rectangular_pyramid,
                            cyclide_segment_solid,
                            volume,
                            half_space_solid,
                            shell_based_surface_model,
                            face_based_surface_model,
                            shell_based_wireframe_model,
                            edge_based_wireframe_model,
                            geometric_set,
                            tessellated_item,
                            volume_with_faces,
                            scanned_data_item))
      SUBTYPE OF (representation_item);
    DERIVE
      dim : dimension_count := dimension_of(SELF);
    WHERE
      WR1:
           SIZEOF(QUERY (using_rep <* using_representations(SELF)| NOT ('STEP_MERGED_AP_SCHEMA.GEOMETRIC_REPRESENTATION_CONTEXT' IN TYPEOF(using_rep.context_of_items)))) = 0;
    END_ENTITY;
   </PRE>
   * <U>Определения атрибутов:</U>
   *
   * \ref express::geometric_representation_item._dim() "dim":
   * the coordinate \ref express::dimension_count "dimension_count" of
   * the \ref express::geometric_representation_item "geometric_representation_item".
   *
   * <U>Formal propositions:</U>
   *
   * <B>WR1:</B> The context of any representation referencing a
   * \ref express::geometric_representation_item "geometric_representation_item" shall be a
   * \ref express::geometric_representation_context "geometric_representation_context".
   *
   * <SMALL>NOTE 5 The \ref express::geometric_representation_item._dim() "dim" attribute is derived from the
   * \ref express::geometric_representation_context "coordinate_space_dimension" of a
   * \ref express::geometric_representation_context "geometric_representation_context" in which the
   * \ref express::geometric_representation_item "geometric_representation_item" is geometrically founded.
   * </SMALL>
   *
   * <SMALL>NOTE 6 A \ref express::geometric_representation_item "geometric_representation_item" 
   * is geometrically founded in one or more
   * \ref express::geometric_representation_context "geometric_representation_context"s, all of which have the same
   * \ref express::geometric_representation_context "coordinate_space_dimension".
   * See the rule \ref p42_s4_7_1 "compatible_dimension". 
   * </SMALL>
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_geometric_representation_item.html">Ссылка 1, </A>
   * <A HREF="http://www.steptools.com/stds/smrl/data/resource_docs/geometric_and_topological_representation/sys/4_schema.htm#geometry_schema.geometric_representation_item">Ссылка 2.</A>
   */
  class geometric_representation_item : virtual public representation_item {

  public:

    /** Количество координат объекта */
    dimension_count _dim() const {
      return dimension_of(this);
    }

    /** \brief Конструктор неопределённого типа */
    geometric_representation_item() : representation_item() {
    }

    /** \brief Конструктор */
    geometric_representation_item(const std::string& Name);

    /** \brief Деструктор */
    virtual ~geometric_representation_item();
  };

  /**
   * \file
   * \copydetails express::point
   */

  /**
   * \brief ENTITY point (ISO 10303-42:2021(E), 4.5.3)
   *
   * \ref express::point "4.5.3 point"
   *
   * A \ref express::point "point" is a type of \ref express::geometric_representation_item "geometric_representation_item"
   * and is a location in some real Cartesian coordinate space \f$ R^m \f$, for \f$ m = 1, \f$ \f$ 2 \f$ or \f$ 3 \f$. 
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
    -- DIFF IN AP214
    -- DIFF IN AP203e2
    -- DIFF IN AP224
    -- DIFF IN AP232
    ENTITY point
       SUPERTYPE OF (ONEOF(cartesian_point,
                           point_on_curve,
                           point_on_surface,
                           point_in_volume,
                           point_replica,
                           degenerate_pcurve))
       SUBTYPE OF (geometric_representation_item);
    END_ENTITY;
   </PRE>
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_point.html">Ссылка 1, </A>
   * <A HREF="http://www.steptools.com/stds/smrl/data/resource_docs/geometric_and_topological_representation/sys/4_schema.htm#geometry_schema.point">Ссылка 2.</A>
   */
  class point : public geometric_representation_item {

  public:

    /** \brief Конструктор */
    point(const std::string& Name) :
      representation_item(Name),
      geometric_representation_item(Name) {
    }

    /** \brief Деструктор */
    virtual ~point() {
    }

    /** \brief Сравнение "равно" */
    bool operator==(const point& p) const;
  };

  /**
   * \file
   * \copydetails express::cartesian_point
   */

  /**
   * \brief ENTITY cartesian_point (ISO 10303-42:2021(E), 4.5.4)
   *
   * \ref express::cartesian_point "4.5.4 cartesian_point"
   *
   * A \ref express::cartesian_point "cartesian_point" is a type of \ref express::point "point" defined by its
   * coordinates in a rectangular Cartesian coordinate system, or in a parameter
   * space. The entity is defined in a one, two or three-dimensional space as
   * determined by the number of coordinates in the list.
   *
   * <SMALL>NOTE 1 For the purposes of defining geometry in this part of ISO 10303
   * only two or three-dimensional points are used.</SMALL>
   *
   * <SMALL>NOTE 2 Depending upon the \ref express::geometric_representation_context "geometric_representation_context"
   * in which the point is used the names of the coordinates may be \f$ (x,y,z) \f$,
   * or \f$ (u,v) \f$, or any other chosen values.</SMALL>
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
    ENTITY cartesian_point
      SUPERTYPE OF(ONEOF(cylindrical_point, polar_point, spherical_point))
      SUBTYPE OF(point);
      coordinates: LIST[1:3] OF length_measure;
    END_ENTITY;
    </PRE>
   *
   * <U>Определения атрибутов:</U>
   *
   * \ref express::cartesian_point.coordinates "coordinates": the ordered list of 1, 2 or 3 coordinate values,
   * according to the dimensionality of the space in which the point is defined;
   *
   * \ref express::cartesian_point.coordinates "coordinates[1]" The component in the direction of the first axis,
   * X or, in parameter space u;
   *
   * \ref express::cartesian_point.coordinates "coordinates[2]" The component in the direction of the second axis
   * Y, or in a parameter space v;
   *
   * \ref express::cartesian_point.coordinates "coordinates[3]" The component in the direction of the Z axis;
   * this will not be present in the case of a cartesian_point in a two-dimensional coordinate space. 
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_cartesian_point.html">Ссылка 1, </A>
   * <A HREF="http://www.steptools.com/stds/smrl/data/resource_docs/geometric_and_topological_representation/sys/4_schema.htm#geometry_schema.cartesian_point">Ссылка 2.</A>
   */
  class cartesian_point : public point {

  private:

    /**
     * \brief Упорядоченный список, содержащий 1, 2 или 3 значений координат, соответствующих размерности
     * пространства, в которм определеа точка.
     */
    LIST<length_measure> coordinates;

  public:

    /**
     * \brief Конструктор одномерный
     */
    cartesian_point(const std::string& Name, const double& X) :
      representation_item(Name),
      point(Name),
      coordinates(1,3) {
      coordinates += length_measure(X);
      add_attr_info(STEP_ATTR_LIST({
                                     {"coordinates", &coordinates}
                                   }, this));
    }

    /**
     * \brief Конструктор двумерный
     */
    cartesian_point(const std::string& Name, const double& X, const double& Y) :
      representation_item(Name),
      point(Name),
      coordinates(1, 3) {
      coordinates += length_measure(X);
      coordinates += length_measure(Y);
      add_attr_info(STEP_ATTR_LIST({
                                     {"coordinates", &coordinates}
                                   }, this));
    }

    /**
     * \brief Конструктор трёхмерный
     */
    cartesian_point(const std::string& Name, const double& X, const double& Y, const double& Z) :
      representation_item(Name),
      point(Name),
      coordinates(1, 3) {
      coordinates += length_measure(X);
      coordinates += length_measure(Y);
      coordinates += length_measure(Z);
      add_attr_info(STEP_ATTR_LIST({
                                     {"coordinates", &coordinates}
                                   }, this));
    }

    /** \brief Деструктор */
    virtual ~cartesian_point() = default;

    /** \brief Получить список координат */
    const LIST<length_measure>& get_coordinates() const {
      return coordinates;
    }

    /** \brief Сравнение координат точек */
    bool operator==(const cartesian_point& cp) const {
      /** 1. Если размерность разная - не сравниваем */
      IF (SIZEOF(coordinates) != SIZEOF(cp.coordinates)) {
        throw exception {"Comparing (==) cartesian_point with different dimensions"};
      }

      /** 2. Сравнить координаты точки, если найдено различие, вернуть false */
      for (INTEGER i = LOINDEX(coordinates); (i <= HIINDEX(coordinates)).is_true(); i = i + 1) {
        if (coordinates[i] != cp.coordinates[i]) return false;
      }
      /** 3. Если все координаты равны, вернуть true */
      return true;
    }
  };

  /**
   * \file
   * 4.5.5 cylindrical_point
   *
   * 4.5.6 spherical_point
   *
   * 4.5.7 polar_point
   *
   * 4.5.8 point_on_curve
   *
   * 4.5.9 point_on_surface
   *
   * 4.5.10 point_in_volume
   *
   * 4.5.11 point_replica
   *
   * 4.5.12 degenerate_pcurve
   *
   * 4.5.13 evaluated_degenerate_pcurve
   *
   * \copydetails express::direction
   */

  /**
   * \brief ENTITY direction (ISO 10303-42:2021(E), 4.5.14)
   *
   * \ref express::direction "4.5.14 direction"
   *
   * A \ref express::direction "direction" is a type of
   * \ref express::geometric_representation_item "geometric_representation_item"
   * that defines a general direction vector in two or three dimensional space. The actual magnitudes
   * of the components have no effect upon the direction being defined, only the ratios x:y:z or x:y,
   * or, in parameter space u:v, are significant.
   *
   * <SMALL>NOTE 1 The components of this entity are not normalised. If a unit vector is required
   * it should be normalised before use.</SMALL>
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
    ENTITY direction
       SUBTYPE OF (geometric_representation_item);
          direction_ratios : LIST [2:3] OF REAL;
       WHERE
          WR1:
             SIZEOF(QUERY (tmp <* direction_ratios | (tmp <> 0.0))) > 0;
    END_ENTITY;
   </PRE>
   *
   * <U>Определения атрибутов:</U>
   *
   * \ref express::direction.direction_ratios "direction_ratios": list of \ref express::REAL "REAL";
   *
   * <SMALL>NOTE 2 The \ref express::direction.direction_ratios "direction_ratios"
   * attribute is a list, the individual elements of this list are defined below.</SMALL>
   *
   * \ref express::direction.direction_ratios "direction_ratios"[1] The component in the direction
   * of the first axis, X or, in parameter space u;
   *
   * \ref express::direction.direction_ratios "direction_ratios"[2] The component in the direction
   * of the second axis Y, or in a parameter space v;
   *
   * \ref express::direction.direction_ratios "direction_ratios"[3] The component in the direction
   * of the Z axis; this will not be present in the case of a direction in a two-dimensional coordinate space.
   *
   * <U>Formal propositions:</U>
   *
   * <B>WR1:</B> The magnitude of the direction vector shall be greater than zero. 
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_direction.html">Ссылка 1, </A>
   * <A HREF="http://www.steptools.com/stds/smrl/data/resource_docs/geometric_and_topological_representation/sys/4_schema.htm#geometry_schema.direction">Ссылка 2.</A>
   */
  class direction : public geometric_representation_item {

  public:

    /**
     * \brief Список из 2 или 3 значений мер длины, задающих проекции направления,
     * представленного настоящим объектом вектора, на оси координат.
     */
    LIST<REAL> direction_ratios;

    /** \brief Конструктор неопределённого типа */
    direction() :
      representation_item(),
      geometric_representation_item(),
      direction_ratios(2, 3) {
        add_attr_info(STEP_ATTR_LIST({
                                       {"direction_ratios", &direction_ratios}
                                     }, this));
    }

    /** \brief Конструктор из списка мер длин */
    direction(const std::string& Name, const LIST<REAL>& Direction_ratios) :
      representation_item(Name),
      geometric_representation_item(Name),
      direction_ratios(2,3)  {
      for (INTEGER i = 0; (i <= SIZEOF(Direction_ratios)).is_true(); i = i + 1) {
        direction_ratios += REAL(Direction_ratios[i]);
      }
      add_attr_info(STEP_ATTR_LIST({
                                     {"direction_ratios", &direction_ratios}
                                   }, this));
    }

    /** \brief Конструктор двумерный из REAL */
    direction(const std::string& Name, const REAL& X, const REAL& Y) :
      representation_item(Name),
      geometric_representation_item(Name),
      direction_ratios(2, 3) {
      direction_ratios += REAL(X);
      direction_ratios += REAL(Y);
      add_attr_info(STEP_ATTR_LIST({
                                     {"direction_ratios", &direction_ratios}
                                   }, this));
    }

    /** \brief Конструктор трёхмерный */
    direction(const std::string& Name, const REAL& X, const REAL& Y, const REAL& Z) :
      representation_item(Name),
      geometric_representation_item(Name),
      direction_ratios(2, 3) {
      direction_ratios += REAL(X);
      direction_ratios += REAL(Y);
      direction_ratios += REAL(Z);
      add_attr_info(STEP_ATTR_LIST({
                                     {"direction_ratios", &direction_ratios}
                                   }, this));
    }


    /** \brief Деструктор */
    virtual ~direction() = default;
  };

  /**
   * \file
   * \copydetails express::vector
   */

  /**
   * \brief ENTITY vector (ISO 10303-42:2021(E), 4.5.15)
   *
   * \ref express::vector "4.5.15 vector"
   *
   * A \ref express::vector "vector" is a type of
   * \ref express::geometric_representation_item "geometric_representation_item" that defines a vector in terms
   * of the direction and the magnitude of the vector.
   *
   * <SMALL>NOTE The magnitude of the vector must not be calculated from the components of the
   * \ref express::vector.orientation "orientation" attribute. This form of representation was selected
   * to reduce problems with numerical instability. For example a vector of magnitude 2.0mm and equally
   * inclined to the coordinate axes could be represented with orientation attribute of (1.0,1.0,1.0)
   * and magnitude attribute 2.0.</SMALL>
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
    *)
    ENTITY vector
       SUBTYPE OF (geometric_representation_item);
          orientation : direction;
          magnitude : length_measure;
       WHERE
          WR1:
             magnitude >= 0.0;
    END_ENTITY;
    (*
    </PRE>
   *
   * <U>Определения атрибутов:</U>
   *
   * \ref express::vector.orientation "orientation": the direction of the \ref express::vector "vector".
   *
   * \ref express::vector.magnitude "magnitude": the magnntude of the \ref express::vector "vector". All \ref express::vector "vector"s of
   * \ref express::vector.magnitude "magnitude" 0.0 are regarded as equal in value regardless of the orientation attribute.
   *
   * <U>Formal propositions:</U>
   *
   * <B>WR1:</B> The magnitude shall be positive or zero. 
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_vector.html">Ссылка 1, </A>
   * <A HREF="http://www.steptools.com/stds/smrl/data/resource_docs/geometric_and_topological_representation/sys/4_schema.htm#geometry_schema.vector">Ссылка 2.</A>
   */
  class vector : public geometric_representation_item {

  public:

    /** \brief Направление \ref express::vector "вектор"а */
    const direction* orientation;

    /**
     * \brief Длина \ref express::vector "вектор"а.
     * Все \ref express::vector "вектор"ы с нулевым значением express::vector.magnitude "magnitude (длина)" считаются равными
     * независимо от значения атрибута \ref express::vector.orientation "orientation (направление)".
     */
    const length_measure* magnitude;

    /**
     * \brief Конструктор неопределённого вектора
     */
    vector();

    /**
     * \brief Конструктор
     */
    vector(const std::string& Name, const direction* Orientation, const length_measure& Magnitude);

    /** \brief Деструктор */
    virtual ~vector();
  };

  /**
   * \file
   * \copydetails express::placement
   */

  /**
   * \brief ENTITY placement (ISO 10303-42:2021(E), 4.5.16)
   *
   * \ref express::placement "4.5.16 placement"
   *
   * A \ref express::placement "placement" is a type of
   * \ref express::geometric_representation_item "geometric_representation_item" that locates a geometric item
   * with respect to the coordinate system of its geometric context. It locates the item to be defined and,
   * in the case of the axis placement subtypes, gives its orientation. 
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
    ENTITY \ref express::placement "placement"
       SUPERTYPE OF (ONEOF(axis1_placement,
                           axis2_placement_2d,
                           \ref express::axis2_placement_3d "axis2_placement_3d"))
       SUBTYPE OF (express::geometric_representation_item "geometric_representation_item");
          location : cartesian_point;
    END_ENTITY;
    </PRE>
   *
   * <U>Определения атрибутов:</U>
   *
   * \ref express::placement.location "location": the geometric position of a reference point,
   * such as the centre of a circle, of the item to be located.
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_placement.html">Ссылка 1, </A>
   * <A HREF="http://www.steptools.com/stds/smrl/data/resource_docs/geometric_and_topological_representation/sys/4_schema.htm#geometry_schema.placement">Ссылка 2.</A>
   */
  class placement : public geometric_representation_item {

  private:

    /** \brief Геометрические координаты опорной точки (например, центр окружности) определяемого объекта */
    const cartesian_point* location;

  public:

    /**
     * \brief Конструктор
     */
    placement(const std::string& Name, const cartesian_point* Location) :
      representation_item(Name),
      geometric_representation_item(Name) {
      location = Location;
      add_attr_info(STEP_ATTR_LIST({
                                     {"location", location}
                                   }, this));
    }

    /** \brief Деструктор */
    virtual ~placement() {
    }
  };

  /**
   * \file
   * \copydetails express::axis1_placement
   */

  /**
   * \brief ENTITY axis1_placement (ISO 10303-42:2021(E), 4.5.17)
   *
   * \ref express::axis1_placement "4.5.17 axis1_placement"
   *
   * A \ref express::axis1_placement "axis1_placement" is a type of
   * \ref express::placement "placement", that represents the direction and location
   * in three-dimensional space of a single axis.
   * An \ref express::axis1_placement "axis1_placement" is defined in terms of a locating point
   * (inherited from the placement supertype) and an axis direction; this is either the direction of
   * \ref express::axis1_placement.axis "axis" or defaults to (0.0,0.0,1.0). The actual direction for
   * the \ref express::axis1_placement "axis1_placement" is given by the derived attribute express::axis1_placement.z "z".
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
    *)
    ENTITY \ref express::axis1_placement "axis1_placement"
      SUBTYPE OF (\ref express::placement "placement");
      \ref express::axis1_placement.axis "axis" : OPTIONAL \ref express::direction "direction";
    DERIVE
      \ref express::axis1_placement.z "z" : \ref express::direction "direction" := NVL(normalise(axis), \ref express::dummy_gri "dummy_gri" || \ref express::direction "direction"([0.0,0.0,1.0]));
    WHERE
      WR1: \ref express::geometric_representation_item._dim() "SELF\\geometric_representation_item.dim" = 3;
    END_ENTITY;
    (* 
   </PRE>
   *
   * <U>Attribute definitions:</U>
   *
   * \ref express::axis1_placement.axis "axis": the direction of the local Z axis;
   *
   * \ref express::axis1_placement.z "z": the normalised direction of the local Z axis;
   *
   * <U>Formal propositions:</U>
   *
   * <B>WR1:</B> The coordinate space dimensionality shall be 3. 
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_axis1_placement.html">Ссылка 1, </A>
   * <A HREF="http://www.steptools.com/stds/smrl/data/resource_docs/geometric_and_topological_representation/sys/4_schema.htm#geometry_schema.axis1_placement">Ссылка 2.</A>
   */
  class axis1_placement : public placement {

  private:

    /** \brief Направление локальной оси Z */
    const direction* axis;

    /** \brief Нормализованное направление локальной оси Z */
    direction* z;

  public:

    /**
     * \brief Конструктор
     */
    axis1_placement(const std::string& Name, const cartesian_point* Location, const direction* Axis = nullptr) :
      representation_item(Name),
      placement(Name, Location) {
      axis = Axis;
      add_attr_info(STEP_ATTR_LIST({
                                     {"axis", axis}

                                   }, this));
      if (axis != nullptr) {
        //!!!
        z = new direction(*axis);
      } else {
        z = new direction(0,0,1.0);
      }
    }

    /** \brief Деструктор */
    virtual ~axis1_placement() {
      delete z;
    }
  };

  /**
   * \file
   * \copydetails express::axis2_placement_2d
   */

  /**
   * \brief ENTITY axis2_placement_2d (ISO 10303-42:2021(E), 4.5.18)
   *
   * \ref express::axis2_placement_2d "4.5.18 axis2_placement_2d"
   *
   * A \ref express::axis2_placement_2d "axis2_placement_2d" is a type of
   * \ref express::placement " placement" that represents the location
   * and orientation in two-dimensional space of two mutually perpendicular axes. An
   * \ref express::axis2_placement_2d "axis2_placement_2d" is defined in terms of a point,
   * (inherited from the \ref express::placement "placement" supertype), and an axis. It can be used to
   * locate and orientate an object in two-dimensional space and to define a placement coordinate system.
   * The entity includes a point which forms the origin of the placement coordinate system. A direction
   * vector is required to complete the definition of the placement coordinate system. The
   * \ref express::axis2_placement_2d::ref_direction "ref_direction" defines the placement X axis direction;
   * the placement Y axis direction is derived from this.
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
    ENTITY \ref express::axis2_placement_2d "axis2_placement_2d"
       SUBTYPE OF (\ref express::placement "placement");
          ref_direction : OPTIONAL \ref express::direction "direction";
       DERIVE
          p : LIST[2:2] OF \ref express::direction "direction" := build_2axes(axis, ref_direction);
       WHERE
          WR1:
             SELF\\geometric_representation_item.dim = 2;
    END_ENTITY;
   </PRE>
   *
   * <U>Attribute definitions:</U>
   *
   * \ref express::axis2_placement_2d.ref_direction "ref_direction": the direction used to determine the direction of the local X axis.
   * If \ref express::axis2_placement_2d.ref_direction "ref_direction" is omitted, this direction is taken from the geometric coordinate system;
   *
   * \ref express::axis2_placement_2d.p "p": the axis set for the placement coordinate system.
   *
   * \ref express::axis2_placement_2d.p "p"[1] The normalised direction of the placement X axis. This is (1.0,0.0) if
   * \ref express::axis2_placement_2d.ref_direction "ref_direction" is omitted.
   *
   * \ref express::axis2_placement_2d.p "p"[2] The normalised direction of the placement
   * Y axis. This is a derived attribute and is orthogonal to \ref express::axis2_placement_2d.p "p"[1].
   *
   * <U>Formal propositions:</U>
   *
   * WR1: The space dimensionality of the axis2_placement_2d shall be 2. 
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_axis2_placement_2d.html">Ссылка 1, </A>
   * <A HREF="http://www.steptools.com/stds/smrl/data/resource_docs/geometric_and_topological_representation/sys/4_schema.htm#geometry_schema.axis2_placement_2d">Ссылка 2.</A>
   */
  class axis2_placement_2d : public placement {

  public:

    direction* axis;                                            // Точное направление локальной оси Z
    direction* ref_direction;                                   // Направление, используемое для получения направления локальной оси X
    LIST<direction> p;

    axis2_placement_2d(const std::string& Name, cartesian_point* Location, direction* Axis, direction* Ref_direction) :
      representation_item(Name),
      placement(Name, Location),
      p(2,2) {
      axis = Axis;
      ref_direction = Ref_direction;
      // WR1: пространственная размерность Location должна быть равно 3.
      assert((Location->_dim() == dimension_count(3)).is_true());
      // WR2: пространственная размерность Axis должна быть равнв 3.
      assert(Axis == nullptr || (Axis->_dim() == dimension_count(3)).is_true());
      // WR3: пространственная размерность Ref_direction должна быть равно 3.
      assert(Ref_direction == nullptr || (Ref_direction->_dim() == dimension_count(3)).is_true());
      // WR4: Axis и Ref_direction не должны быть параллельны или антипараллельны.
      // !!!
      assert((Axis == nullptr || Ref_direction == nullptr) || 1 /* cross_product(Axis, Ref_direction).magnitude > 0.0 */);

      add_attr_info(STEP_ATTR_LIST({
                                     {"axis", axis, true},
                                     {"ref_direction", ref_direction, true},
                                   }, this));
    }

    virtual ~axis2_placement_2d() = default;

//    const direction* get_axis() const {
//      return axis;
//    }

//    const direction* get_ref_direction() const {
//      return ref_direction;
//    }
  };

  /**
   * \file
   * \copydetails express::axis2_placement_3d
   */

  /**
   * \brief ENTITY axis2_placement_3d (ISO 10303-42:2021(E), 4.5.19)
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
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
             (NOT EXISTS(axis) OR NOT EXISTS(ref_direction)) OR
             (cross_product(axis, ref_direction).magnitude > 0.0);
    END_ENTITY;
   </PRE>
   *
   * Это разновидность положения, определяющего расположение и ориентацию
   * в трёхмерном пространстве двумя желательно взаимно перпендикулярными осями.
   */
  class axis2_placement_3d : public placement {

  public:

    direction* axis;                                            // Точное направление локальной оси Z
    direction* ref_direction;                                   // Направление, используемое для получения направления локальной оси X
    LIST<direction> p;

    axis2_placement_3d(const std::string& Name, cartesian_point* Location, direction* Axis, direction* Ref_direction) :
      representation_item(Name),
      placement(Name, Location),
      p(3,3) {
      axis = Axis;
      ref_direction = Ref_direction;
      // WR1: пространственная размерность Location должна быть равно 3.
      assert((Location->_dim() == dimension_count(3)).is_true());
      // WR2: пространственная размерность Axis должна быть равнв 3.
      assert(Axis == nullptr || (Axis->_dim() == dimension_count(3)).is_true());
      // WR3: пространственная размерность Ref_direction должна быть равно 3.
      assert(Ref_direction == nullptr || (Ref_direction->_dim() == dimension_count(3)).is_true());
      // WR4: Axis и Ref_direction не должны быть параллельны или антипараллельны.
      // !!!
      assert((Axis == nullptr || Ref_direction == nullptr) || 1 /* cross_product(Axis, Ref_direction).magnitude > 0.0 */);

      add_attr_info(STEP_ATTR_LIST({
                                     {"axis", axis, true},
                                     {"ref_direction", ref_direction, true},
                                   }, this));
    }

    virtual ~axis2_placement_3d() = default;

//    const direction* get_axis() const {
//      return axis;
//    }

//    const direction* get_ref_direction() const {
//      return ref_direction;
//    }
  };

  /**
   * \file
   * 4.5.20 cartesian_transformation_operator
   *
   * 4.5.21 cartesian_transformation_operator_3d
   *
   * 4.5.22 cartesian_transformation_operator_2d
   *
   * \copydetails express::curve
   */

   /**
    * \brief ENTITY curve (ISO 10303-42:2021(E), 4.5.23)
    *
    * <B>Определение объекта на языке EXPRESS:</B>
    <PRE>
     -- DIFF IN AP214
     -- DIFF IN AP203e2
     -- DIFF IN AP224
     -- DIFF IN AP232
     ENTITY curve
        SUPERTYPE OF (ONEOF(line, conic, clothoid, circular_involute, pcurve, surface_curve, offset_curve_2d, offset_curve_3d, curve_replica))
        SUBTYPE OF (geometric_representation_item);
     END_ENTITY;
    </PRE>
    *
    */
  class curve : public geometric_representation_item {

  public:

    // Конструктор
    curve(const std::string& Name) :
      representation_item(Name),
      geometric_representation_item(Name) {
    }

    virtual ~curve() {
    }
  };

  /**
   * \file
   * \copydetails express::line
   */

  /**
   * \brief ENTITY line (ISO 10303-42:2021(E), 4.5.24)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   <PRE>
    ENTITY line
       SUBTYPE OF (curve);
          pnt : cartesian_point;
          dir : vector;
       WHERE
          WR1:
             dir.dim = pnt.dim;
    END_ENTITY;
   </PRE>
   *
   */
  class line : public curve {

  private:

    const cartesian_point* pnt; // Начальная точка
    const vector* dir; // Вектор от начальной точки до конечной

  public:

    /** \brief Констуктор */
    line(const std::string& Name, const cartesian_point* Pnt, const vector* Dir);

    /** \brief Деструктор */
    virtual ~line();
  };

  /**
   * \brief ENTITY conic (4.5.25)
   */
  class conic : public curve {

  public:

    axis2_placement position;

    virtual ~conic() = default;
  };


  /**
   * \brief ENTITY circle (4.5.26)
   */
  class circle : public conic {

  public:

    positive_length_measure radius;

    virtual ~circle() = default;
  };

  /**
   * \file
   * 4.5.27 ellipse
   *
   * 4.5.28 hyperbola
   *
   * 4.5.29 parabola
   *
   * 4.5.30 clothoid
   *
   * 4.5.31 circular_involute
   */

   /** \brief 4.5.32 bounded_curve */
   class bounded_curve : public curve {
   public:

     virtual ~bounded_curve() = default;
   };

   /** \brief 4.5.33 polyline */
   class polyline : public bounded_curve {
   public:

     LIST<cartesian_point> points;

     virtual ~polyline() = default;
   };


   /** \brief 4.5.34 b_spline_curve */
   class b_spline_curve : public bounded_curve {
   public:

     INTEGER degree;
     LIST<cartesian_point> control_points_list;
     b_spline_curve_form curve_form;
     LOGICAL closed_curve;
     LOGICAL self_intersect;

     virtual ~b_spline_curve() = default;
   };


  /**
   * \file
   * 4.5.35 b_spline_curve_with_knots
   *
   * 4.5.36 uniform_curve
   *
   * 4.5.37 quasi_uniform_curve
   *
   * 4.5.38 bezier_curve
   *
   * 4.5.39 rational_b_spline_curve
   *
   * 4.5.40 local_b_spline
   *
   * 4.5.41 locally_refined_spline_curve
   *
   * 4.5.42 rational_locally_refined_spline_curve
   *
   * 4.5.43 trimmed_curve
   *
   * 4.5.44 composite_curve
   *
   * 4.5.45 composite_curve_segment
   *
   * 4.5.46 reparametrised_composite_curve_segment
   *
   * \copydetails express::pcurve
   */

   /**
    * \brief ENTITY pcurve (ISO 10303-42:2021(E), 4.5.47)
    *
    * <B>Определение объекта на языке EXPRESS:</B>
    <PRE>
     ENTITY pcurve
        SUBTYPE OF (curve);
           basis_surface : surface;
           reference_to_curve : definitional_representation;
        WHERE
           WR1:
              SIZEOF(reference_to_curve\\representation.items) = 1;
           wr2:
              'STEP_MERGED_AP_SCHEMA.CURVE' IN TYPEOF(reference_to_curve\\representation.items[1]);
           wr3:
              reference_to_curve\\representation.items[1]\\geometric_representation_item.dim = 2;
     END_ENTITY;
    </PRE>
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
//    identifier get_id_value() {
//      return "";
//    }

    // FUNCTION get_description_value
//    text get_description_value() {
//      return "";
//    }

    virtual ~pcurve() {
    }
  };

  /**
   * \file
   * 4.5.48 bounded_pcurve
   *
   * \copydetails express::surface_curve
   */

   /**
    * \brief ENTITY surface_curve (ISO 10303-42:2021(E), 4.5.49)
    *
    * <B>Определение объекта на языке EXPRESS:</B>
    <PRE>
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
    </PRE>
    *
    */
  class surface_curve : public curve {

  public:

    curve* curve_3d;

    LIST<pcurve_or_surface> associated_geometry;

    preferred_surface_curve_representation* master_representation;

    // Derived
    // dimension_count dim;                          // Defined by geometric_representation_item
    // LIST<SUFACE> basis_surface;             // Defined by surface_curve
  };

  /**
   * \file
   * 4.5.51 seam_curve
   *
   * 4.5.52 bounded_surface_curve
   *
   * 4.5.53 composite_curve_on_surface
   *
   * 4.5.54 offset_curve_2d
   *
   * 4.5.55 offset_curve_3d
   *
   * 4.5.56 curve_replica
   *
   * \copydetails express::surface
   */

   /**
    * \brief ENTITY surface (ISO 10303-42:2021(E), 4.5.57)
    *
    * <B>Определение объекта на языке EXPRESS:</B>
    <PRE>
     -- DIFF IN AP224
     ENTITY surface
        SUPERTYPE OF (ONEOF(elementary_surface, swept_surface, bounded_surface, offset_surface, surface_replica))
        SUBTYPE OF (geometric_representation_item);
     END_ENTITY;
    </PRE>
    *
    */
  class surface : public geometric_representation_item {

  public:

    // Конструктор
    surface(const std::string& Name) :
      representation_item(Name),
      geometric_representation_item(Name) {
    }

    dimension_count dimension_of() {
      return dimension_count();
    }
  };

  /**
   * \file
   * \copydetails express::elementary_surface
   */

  /**
   * \brief ENTITY elementary_surface (ISO 10303-42:2021(E), 4.5.58)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   <PRE>
    ENTITY elementary_surface
       SUPERTYPE OF (ONEOF(plane, cylindrical_surface, conical_surface, spherical_surface, toroidal_surface))
       SUBTYPE OF (surface);
          position : axis2_placement_3d;
    END_ENTITY;
   </PRE>
   *
   * Элементарная поверхность это параметрически определяемая разновидность поверхности.
   */
  class elementary_surface : public surface {

  private:

    const axis2_placement_3d* position;            // Положение и ориентация поверхности

  public:

    elementary_surface(const std::string& Name, const axis2_placement_3d* Position) :
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
   * \file
   * \copydetails express::plane
   */

  /**
   * \brief ENTITY plane (ISO 10303-42:2021(E), 4.5.59)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   <PRE>
    ENTITY plane
       SUBTYPE OF (elementary_surface);
    END_ENTITY;
   </PRE>
   *
   * Плоскость это разновидность элементарной поверхности - есть неограниченной и с постоянной нормалью.
   */
  class plane : public elementary_surface {

  public:

    plane(const std::string& Name, const axis2_placement_3d* Position) :
      representation_item(Name),
      elementary_surface(Name, Position) {
    }

    virtual ~plane() {
    }
  };

  /**
   * \brief 4.5.60 cylindrical_surface
   */
  class cylindrical_surface : public elementary_surface {

  public:

     positive_length_measure radius;

     virtual ~cylindrical_surface() = default;
   };

   /**
    * \brief 4.5.61 conical_surface
    */
  class conical_surface : public elementary_surface {

  public:

     length_measure radius;
     plane_angle_measure semi_angle;

     virtual ~conical_surface() = default;
   };

   /**
    * \brief 4.5.62 spherical_surface
    */
   class spherical_surface : public elementary_surface {

   public:

     positive_length_measure radius;

     virtual ~spherical_surface() = default;
   };

  /**
   * \file
   * 4.5.63 toroidal_surface
   *
   * 4.5.64 degenerate_toroidal_surface
   *
   * 4.5.65 dupin_cyclide_surface
   */




  /**
   * \file
   * \copydetails express::swept_surface
   */

  /**
   * \brief ENTITY plane (ISO 10303-42:2021(E), 4.5.66)
   *
   * \ref express::swept_surface "4.5.66 swept_surface"
   *
   * A \ref express::swept_surface "swept_surface" is a type of \ref express::surface "surface",
   * that is constructed by sweeping a curve along another curve. 
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
   *)
   ENTITY swept_surface
     SUPERTYPE OF (ONEOF (surface_of_linear_extrusion,
                          surface_of_revolution,
                          surface_curve_swept_surface,
                          fixed_reference_swept_surface))
     SUBTYPE OF (surface);
     swept_curve : curve;
   END_ENTITY;
   (* 
   </PRE>
   */
  class swept_surface : public surface {

  public:
    /**
     * \brief the curve to be swept in defining the surface; if the swept curve is a pcurve,
     * it is the image of this curve in 3D geometric space which is swept, not the parameter space curve.
     */
    curve swept_curve;

    virtual ~swept_surface() =  default;
  };

  /**
   * 4.5.67 surface_of_linear_extrusion
   *
   * 4.5.68 surface_of_revolution
   *
   * 4.5.69 surface_curve_swept_surface
   *
   * 4.5.70 fixed_reference_swept_surface
   */



  /**
   * \brief ENTITY bounded_surface (ISO 10303-42:2021(E), 4.5.71)
   */
  class bounded_surface : public surface {

  public:

    virtual ~bounded_surface() = default;
  };

  /**
   * \brief ENTITY b_spline_surface (ISO 10303-42:2021(E), 4.5.72)
   */
  class b_spline_surface : public bounded_surface {

  public:

    INTEGER u_degree;
    INTEGER v_degree;
    LIST<LIST<cartesian_point>> control_points_list;
    b_spline_surface_form surface_form;
    LOGICAL u_closed;
    LOGICAL v_closed;
    LOGICAL self_intersect;

    virtual ~b_spline_surface() = default;
  };

  /**
   * \file
   * 4.5.73 b_spline_surface_with_knots
   *
   * 4.5.74 uniform_surface
   *
   * 4.5.75 quasi_uniform_surface
   *
   * 4.5.76 bezier_surface
   *
   * 4.5.77 rational_b_spline_surface
   *
   * 4.5.78 locally_refined_spline_surface
   *
   * 4.5.79 rational_locally_refined_spline_surface
   *
   * 4.5.80 rectangular_trimmed_surface
   *
   * 4.5.81 curve_bounded_surface
   *
   * 4.5.82 boundary_curve
   *
   * 4.5.83 outer_boundary_curve
   *
   * 4.5.84 rectangular_composite_surface
   *
   * 4.5.85 surface_patch
   *
   * 4.5.86 offset_surface
   *
   * \copydetails express::oriented_surface
   */

   /**
    * \brief ENTITY oriented_surface (ISO 10303-42:2021(E), 4.5.87)
    *
    * <B>Определение объекта на языке EXPRESS:</B>
    <PRE>
     -- IN AP203e2/AP214/AP232/AP238 STEP-NC/AP242
     ENTITY oriented_surface
        SUBTYPE OF (surface);
           orientation : BOOLEAN;
     END_ENTITY;
    </PRE>
    *
    */
  class oriented_surface : public surface {

  public:

    BOOLEAN orientation;

    oriented_surface(const std::string& Name, const BOOLEAN& Orientation) :
      representation_item(Name),
      surface(Name),
      orientation(Orientation) {
    }

    virtual ~oriented_surface() = default;
  };

  /**
   * \file
   * 4.5.88 surface_replica
   *
   * 4.5.89 volume
   *
   * 4.5.90 block_volume
   *
   * 4.5.91 wedge_volume
   *
   * 4.5.92 pyramid_volume
   *
   * 4.5.93 tetrahedron_volume
   *
   * 4.5.94 hexahedron_volume
   *
   * 4.5.95 spherical_volume
   *
   * 4.5.96 cylindrical_volume
   *
   * 4.5.97 eccentric_conical_volume
   *
   * 4.5.98 toroidal_volume
   *
   * 4.5.99 ellipsoid_volume
   *
   * 4.5.100 b_spline_volume
   *
   * 4.5.101 b_spline_volume_with_knots
   *
   * 4.5.102 bezier_volume
   *
   * 4.5.103 uniform_volume
   *
   * 4.5.104 quasi_uniform_volume
   *
   * 4.5.105 rational_b_spline_volume
   *
   * 4.5.106 locally_refined_spline_volume
   *
   * 4.5.107 rational_locally_refined_spline_volume
   *
   * \subsection p42_s4_6 4.6 Geometry function definitions
   *
   * 4.6.1 above_plane
   *
   * 4.6.2 acyclic_curve_replica
   *
   * 4.6.3 acyclic_point_replica
   *
   * 4.6.4 acyclic_surface_replica
   *
   * 4.6.5 associated_surface
   *
   * 4.6.6 base_axis
   */

  /**
   * \file
   * \copydetails express::build_2axes()
   */ 

  /**
   * \brief FUNCTION build_2axes (ISO 10303-42:2021(E), 4.6.7)
   *
   * \ref express::build_2axes() "4.6.7 build_2axes"
   *
   * The \ref express::build_2axes() "build_2axes" function returns two normalised orthogonal directions.<BR>
   * <B>u[1]</B> is in the direction of \ref express::build_2axes() "ref_direction"
   * and <B>u[2]</B> is perpendicular to u[1].<BR>
   * A default value of (1.0, 0.0) is supplied for
   * \ref express::build_2axes() "ref_direction" if the input data is incomplete.
   *
   * <SMALL> NOTE This function does not provide geometric founding for the directions returned,
   * the caller of the the function is responsible for ensuring that they are used in a
   * \ref express::representation "representation" with a
   * \ref express::geometric_representation_context "geometric_representation_context".</SMALL>
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
    *)
    FUNCTION build_2axes (ref_direction : direction) : LIST[2:2] OF direction;

     LOCAL
         d : direction := NVL(normalise(ref_direction),
                              dummy_gri || direction([1.0,0.0]));
       END_LOCAL;

       RETURN([d, orthogonal_complement(d)]);

    END_FUNCTION;
    (*
    </PRE>
   *
   * \param ref_direction [in] A reference \ref express::direction "direction" in 2 dimensional space,
   * this may be defaulted to (1.0, 0.0).
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_build_2axes.html">Ссылка 1, </A>
   * <A HREF="http://www.steptools.com/stds/smrl/data/resource_docs/geometric_and_topological_representation/sys/4_schema.htm#geometry_schema.build_2axes">Ссылка 2.</A>
   */
  LIST<const direction> build_2axes(const direction& ref_direction);

  /**
   * \file
   * \copydetails express::build_axes()
   */ 

  /**
   * \brief FUNCTION build_axes (ISO 10303-42:2021(E), 4.6.8)
   *
   * \ref express::build_axes() "4.6.8 build_axes"
   *
   * The \ref express::build_axes() "build_axes" function returns three normalised orthogonal
   * \ref express::direction "direction"s. <B>u[3]</B> is in the direction of
   * \ref express::build_axes() "axis", <B>u[1]</B>
   * is in the direction of the projection of \ref express::build_axes() "ref_direction" onto the plane normal to
   * <B>u[3]</B>, and <B>u[2]</B> is the cross product of <B>u[3]</B> and <B>u[1]</B>. Default values are supplied
   * if input data is incomplete.
   *
   * <SMALL> NOTE This function does not provide geometric founding for the
   * \ref express::build_axes() "directions" returned,
   * the caller of the the function is responsible for ensuring that they are used in a
   * \ref express::representation "representation" with a
   * \ref express::geometric_representation_context "geometric_representation_context".</SMALL>
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
    *)
    FUNCTION build_axes (axis : direction; ref_direction : direction) : LIST[3:3] OF direction;

        LOCAL
           d1, d2 : direction;
        END_LOCAL;
        d1 := NVL(normalise(axis), dummy_gri || direction([0.0,0.0,1.0]));
        d2 := first_proj_axis(d1, ref_direction);
        RETURN([d2, normalise(cross_product(d1,d2))\\vector.orientation, d1]);

    END_FUNCTION;
     (*
    </PRE>
   *
   * \param axis [in] The intended \ref express::direction "direction" of <B>u[3]</B>,
   * this may be defaulted to (0.0, 0.0, 1.0).
   *
   * \param ref_direction [in] A \ref express::direction "direction" in a direction used to compute <B>u[1]</B>.
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_build_axes.html">Ссылка 1, </A>
   * <A HREF="http://www.steptools.com/stds/smrl/data/resource_docs/geometric_and_topological_representation/sys/4_schema.htm#geometry_schema.build_axes">Ссылка 2.</A>
   */
  LIST<direction> build_axes(const direction& axis, const direction& ref_direction);

  /**
   * \file
   * \copydetails express::check_geometric_dimension()
   */ 

  /**
   * \brief FUNCTION check_geometric_dimension (ISO 10303-42:2021(E), 4.6.9)
   *
   * \ref express::check_geometric_dimension() "4.6.9 check_geometric_dimension"
   */
  bool check_geometric_dimension(const SET<cartesian_point>& capt, const SET<direction>& dir, const SET<geometric_representation_context>& grc); 

  /**
   * \file
   * 4.6.10 constraints_composite_curve_on_surface
   *
   * 4.6.11 constraints_param_b_spline
   *
   * 4.6.12 constraints_param_local_b_spline
   *
   * 4.6.13 constraints_rectangular_composite_surface
   *
   * 4.6.14 constraints_scaling
   */

  /**
   * \file
   * \copydetails express::cross_product()
   */ 

  /**
   * \brief FUNCTION cross_product (ISO 10303-42:2021(E), 4.6.15)
   *
   * \ref express::cross_product() "4.6.15 cross_product"
   *
   * The \ref express::cross_product() "cross_product" function returns the vector, or cross, product of two input
   * \ref express::direction "direction"s. The input directions must be three-dimensional and are normalised at the
   * start of the computation. The result is always a \ref express::vector "vector" which is unitless. If the input
   * \ref express::direction "direction"s are either parallel or anti-parallel, a
   * \ref express::vector "vector" of zero magnitude is returned with
   * \ref express::vector.orientation "orientation" as \ref express::cross_product() "arg1".
   *
   * <SMALL>NOTE This function does not provide geometric founding for the
   * \ref express::vector "vector" returned, the caller of the the function is responsible for ensuring that it is used in a
   * \ref express::representation "representation" with a
   * \ref express::geometric_representation_context "geometric_representation_context".</SMALL>
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
    *)
    FUNCTION cross_product (arg1 : \ref express::direction "direction"; arg2 : \ref express::direction "direction") : \ref express::vector "vector";

      LOCAL
        mag    : \ref express::REAL "REAL";
        res    : \ref express::direction "direction";
        v1,v2  : LIST[3:3] OF REAL;
        result : \ref express::vector "vector";
      END_LOCAL;
  
      IF ( NOT EXISTS (arg1) OR (arg1.dim = 2)) OR
         ( NOT EXISTS (arg2) OR (arg2.dim = 2)) THEN
        RETURN(?);
      ELSE
        BEGIN
          v1  := \ref express::normalise() "normalise"(arg1).direction_ratios;
          v2  := \ref express::normalise() "normalise"(arg2).direction_ratios;
          res := \ref express::dummy_gri "dummy_gri" || \ref express::direction "direction"([(v1[2]*v2[3] - v1[3]*v2[2]),
                (v1[3]*v2[1] - v1[1]*v2[3]), (v1[1]*v2[2] - v1[2]*v2[1])]);
          mag := 0.0;
          REPEAT i := 1 TO 3;
            mag := mag + res.direction_ratios[i]*res.direction_ratios[i];
          END_REPEAT;
          IF (mag > 0.0) THEN
            result := \ref express::dummy_gri "dummy_gri" || \ref express::vector "vector"(res, \ref express::SQRT() "SQRT"(mag));
          ELSE
            result := \ref express::dummy_gri "dummy_gri" || \ref express::vector "vector"(arg1, 0.0);
          END_IF;
          RETURN(result);
        END;
      END_IF;

    END_FUNCTION;
    (* 
   </PRE>
   *
   * \param arg1 [in] a \ref express::direction "direction" defining the first operand in cross product operation.
   * \param arg2 [in] a \ref express::direction "direction" defining the second operand for cross product.
   * \return vector, or cross, product of two input \ref express::direction "direction"s.
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_cross_product.html">Ссылка 1, </A>
   * <A HREF="http://www.steptools.com/stds/smrl/data/resource_docs/geometric_and_topological_representation/sys/4_schema.htm#geometry_schema.dimension_of">Ссылка 2.</A>
   */
  vector cross_product(const direction& arg1, const direction& arg2);

  /**
   *\file
   * 4.6.16 curve_weights_positive
   *
   * 4.6.17 default_b_spline_curve_weights
   *
   * 4.6.18 default_b_spline_knot_mult
   *
   * 4.6.19 default_b_spline_knots
   *
   * 4.6.20 default_b_spline_surface_weights
   *
   * \copydetails express::dimension_of()
   */

  
  /**
   * \brief FUNCTION dimension_of (ISO 10303-42:2021(E), 4.6.21)
   *
   * \ref express::dimension_of() "4.6.21 dimension_of"
   *
   * The \ref express::dimension_of() "dimension_of" function returns the dimensionality of the input
   * \ref express::geometric_representation_item "geometric_representation_item".
   * If the item is a \ref express::cartesian_point "cartesian_point", \ref express::direction "direction",
   * or \ref express::vector "vector", the dimensionality is obtained directly by counting components.
   * For all other other subtypes the dimensionality is the integer
   * \ref express::dimension_count "dimension_count" of a
   * \ref express::geometric_representation_context "geometric_representation_context"
   * in which the input
   * \ref express::geometric_representation_item "geometric_representation_item" is geometrically founded.
   * By virtue of the constraints in global rule <B>compatible_dimension</B>, this value is the
   * \ref express::geometric_representation_item._dim() "dim" of the input
   * \ref express::geometric_representation_item "geometric_representation_item".
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
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
         dim := SIZEOF(item\\cartesian_point.coordinates);
         RETURN(dim);
      END_IF;
      IF 'GEOMETRY_SCHEMA.DIRECTION' IN TYPEOF(item) THEN
         dim := SIZEOF(item\\direction.direction_ratios);
         RETURN(dim);
      END_IF;
      IF 'GEOMETRY_SCHEMA.VECTOR' IN TYPEOF(item) THEN
         dim := SIZEOF(item\\vector.orientation\\direction.direction_ratios);
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
        dim := y\\geometric_representation_context.coordinate_space_dimension;
      RETURN (dim);
      ELSE
        RETURN(?);
      -- mark error by returning indeterminate result
     END_IF;

  END_FUNCTION;
  (*
   </PRE>
   *
   * \param [in] item a \ref express::geometric_representation_item "geometric_representation_item"
   * for which the <B>dimension_count</B> is determined.
   *
   * \return количество измерений геометрического объекта.
   */
  dimension_count dimension_of(const geometric_representation_item* item);


  /**
   * \file
   * \copydetails express::dot_product()
   */

  /** \brief FUNCTION dot_product (ISO 10303-42:2021(E), 4.6.22)
   *
   * \ref express::dot_product() "4.6.22 dot_product"
   *
   * The \ref express::dot_product "dot_product" function returns the scalar, or dot (\f$ \bullet \f$), product of two
   * \ref express::direction "direction"s. The input arguments can be
   * \ref express::direction "direction"s in either two- or three-dimensional space and are normalised
   * at the start of the computation. The returned scalar is undefined if the input
   * \ref express::direction "direction"s have different dimensionality, or if either is undefined. 
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
    *)
    FUNCTION dot_product (arg1 : direction; arg2 : direction) : REAL;

      LOCAL
        scalar : REAL;
        vec1, vec2: direction;
        ndim : INTEGER;
      END_LOCAL;

      IF NOT EXISTS (arg1) OR NOT EXISTS (arg2) THEN
        scalar := ?;
        (* When function is called with invalid data an indeterminate result
        is returned *)
      ELSE
        IF (arg1.dim <> arg2.dim) THEN
          scalar := ?;
        (* When function is called with invalid data an indeterminate result
        is returned *)
        ELSE
          BEGIN
            vec1   := normalise(arg1);
            vec2   := normalise(arg2);
            ndim   := arg1.dim;
            scalar := 0.0;
            REPEAT  i := 1 TO ndim;
              scalar := scalar +
                          vec1.direction_ratios[i]*vec2.direction_ratios[i];
            END_REPEAT;
          END;
        END_IF;
      END_IF;
      RETURN (scalar);

    END_FUNCTION;
    (* 
   </PRE>
   *
   * \param [in] arg1 a \ref express::direction "direction" defining first vector in dot product, or scalar product, operation.
   * \param [in] arg2 a \ref express::direction "direction" defining second operand for dot product operation. 
   * \return scalar, or dot (\f$ \bullet \f$), product of two \ref express::direction "direction"s.
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_dot_product.html">Ссылка 1, </A>
   * <A HREF="http://www.steptools.com/stds/smrl/data/resource_docs/geometric_and_topological_representation/sys/4_schema.htm#geometry_schema.dot_product">Ссылка 2.</A>
   */
  REAL dot_product(const direction& arg1, const direction& arg2);



  /**
   * \file
   * \copydetails express::first_proj_axis()
   */

  /**
   * \brief FUNCTION first_proj_axis (ISO 10303-42:2021(E), 4.6.23)
   *
   * \ref express::first_proj_axis() "4.6.23 first_proj_axis"
   *
   * The \ref express::first_proj_axis "first_proj_axis" function produces a 3-dimensional
   * \ref express::direction "direction" which is, with fully defined input, the projection of <B>arg</B> onto the
   * plane normal to the <B>z_axis</B>. With <B>arg</B> defaulted the result is the projection of [1,0,0] onto this
   * plane; except that, if <B>z_axis</B> = [1,0,0], or, <B>z_axis</B> = [-1,0,0], [0,1,0] is the default for <B>arg</B>.
   * A violation occurs if <B>arg</B> is in the same direction as the input <B>z_axis</B>.
   *
   * <SMALL> NOTE This function does not provide geometric founding for the \ref express::direction "direction"
   * returned, the caller of the the function is responsible for ensuring that it is used in a
   * \ref express::representation "representation" with a
   * \ref express::geometric_representation_context "geometric_representation_context".</SMALL>
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
    *)
    FUNCTION first_proj_axis (z_axis : direction; arg : direction) : direction;

      LOCAL
          x_axis : direction;
          v      : direction;
          z      : direction;
          x_vec  : vector;
      END_LOCAL;
  
      IF (NOT EXISTS(z_axis)) THEN
        RETURN (?) ;
      ELSE
        z := normalise(z_axis);
        IF NOT EXISTS(arg) THEN
          IF ((z.direction_ratios <> [1.0,0.0,0.0]) AND
              (z.direction_ratios <> [-1.0,0.0,0.0]))  THEN
            v :=  dummy_gri || direction([1.0,0.0,0.0]);
          ELSE
            v := dummy_gri || direction([0.0,1.0,0.0]);
          END_IF;
        ELSE
          IF  (arg.dim <> 3) THEN
            RETURN (?) ;
          END_IF;
          IF ((cross_product(arg,z).magnitude) = 0.0) THEN
            RETURN (?);
          ELSE
            v := normalise(arg);
          END_IF;
        END_IF;
        x_vec := scalar_times_vector(dot_product(v, z), z);
        x_axis := vector_difference(v, x_vec).orientation;
        x_axis := normalise(x_axis);
      END_IF;
      RETURN(x_axis);

    END_FUNCTION;
    (*
   </PRE>
   *
   * \param [in] z_axis A direction defining a local Z coordinate axis.
   * \param [in] arg A direction not parallel to <B>z_axis</B>.
   * \return a \ref express::direction "direction" which is in the direction of the projection of <B>arg</B> onto the plane with normal <B>z_axis</B>.
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_first_proj_axis.html">Ссылка 1, </A>
   * <A HREF="http://www.steptools.com/stds/stds/smrl/data/resource_docs/geometric_and_topological_representation/sys/4_schema.htm#geometry_schema.first_proj_axis">Ссылка 2.</A>
   */
  direction first_proj_axis(const direction& z_axis, const direction& arg);

  /**
   * \file
   * 4.6.24 geometric_dimensionalities_in_contexts
   *
   * 4.6.25 get_basis_surface
   *
   * 4.6.26 increasing_values_in_list
   *
   * 4.6.27 list_to_array
   *
   * 4.6.28 make_array_of_array
   *
   * 4.6.29 make_array_of_array_of_array
   */

  /**
   * \file
   * \copydetails express::normalise()
   */

  /**
   * \brief FUNCTION normalise (ISO 10303-42:2021(E), 4.6.30)
   *
   * \ref express::normalise() "4.6.30 normalise"
   *
   * The \ref express::normalise "normalise" function returns a \ref express::vector "vector" or
   * \ref express::direction "direction" whose components are normalised to have a sum of squares of 1.0.
   * The output is of the same type (\ref express::direction "direction" or \ref express::vector "vector",
   * with the same units) as the input argument. If the input argument is not defined or is of zero length,
   * the output vector is undefined.
   *
   * <SMALL>NOTE This function does not provide geometric founding for the \ref express::direction "direction"
   * returned, the caller of the the function is responsible for ensuring that it is used in a
   * \ref express::representation "representation" with a
   * \ref express::geometric_representation_context "geometric_representation_context".</SMALL>
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
    *)
    FUNCTION normalise (arg : vector_or_direction) : vector_or_direction;

    LOCAL
          ndim   : INTEGER;
          v      : direction := dummy_gri || direction ([1.0,0.0,0.0]);
          result : vector_or_direction;
          vec    : vector := dummy_gri || vector (v, 1.0);
          mag    : REAL;
    END_LOCAL;
    
    IF NOT EXISTS (arg) THEN
      result := ?;
    (* When function is called with invalid data a NULL result is returned *)
    ELSE
      ndim := arg.dim;
      IF 'GEOMETRY_SCHEMA.VECTOR' IN TYPEOF(arg) THEN
        BEGIN
              v := dummy_gri || direction(arg\vector.orientation.direction_ratios);
          IF arg\vector.magnitude = 0.0 THEN
            RETURN(?);
          ELSE
           vec := dummy_gri || vector (v, 1.0);
          END_IF;
        END;
      ELSE
        v := dummy_gri || direction (arg.direction_ratios);
      END_IF;
      mag := 0.0;
      REPEAT  i := 1 TO ndim;
        mag := mag + v.direction_ratios[i]*v.direction_ratios[i];
      END_REPEAT;
      IF mag > 0.0 THEN
        mag := SQRT(mag);
        REPEAT  i := 1 TO ndim;
          v.direction_ratios[i] := v.direction_ratios[i]/mag;
        END_REPEAT;
        IF 'GEOMETRY_SCHEMA.VECTOR' IN TYPEOF(arg) THEN
          vec.orientation := v;
          result := vec;
        ELSE
          result := v;
        END_IF;
      ELSE
        RETURN(?);
      END_IF;
    END_IF;
    RETURN (result);

    END_FUNCTION;
    (* 
   </PRE>
   *
   * \param [in] arg \ref express::vector "vector" or \ref express::direction "direction" to be normalised. 
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_normalise.html">Ссылка 1, </A>
   * <A HREF="http://www.steptools.com/stds/smrl/data/resource_docs/geometric_and_topological_representation/sys/4_schema.htm#geometry_schema.normalise">Ссылка 2.</A>
   */
  vector_or_direction normalise(const vector_or_direction& arg);

  /**
   * \file
   * 4.6.31 orthogonal_complement
   */

  direction orthogonal_complement(const direction& vec);

  /**
   * \file
   * 4.6.32 same_side
   */

  /**
   * \file
   * \copydetails express::scalar_times_vector()
   */

  /**
   * \brief FUNCTION scalar_times_vector (ISO 10303-42:2021(E), 4.6.33)
   *
   * \ref express::scalar_times_vector "4.6.33 scalar_times_vector"
   *
   * The \ref express::scalar_times_vector() "scalar_times_vector" function returns the
   * \ref express::vector "vector" that is the scalar multiple of the input vector. It accepts
   * as input a scalar and a `vector' which may be either a \ref express::vector "vector" or a
   * \ref express::direction "direction". The output is a
   * \ref express::vector "vector" of the same units as the input
   * \ref express::vector "vector", or unitless if a
   * \ref express::direction "direction" is input. If either input argument is undefined, the returned
   * \ref express::vector "vector" is also undefined. The \ref express::vector "orientation" of the
   * \ref express::vector "vector" is reversed if the scalar is negative.
   *
   * <SMALL>NOTE This function does not provide geometric founding for the
   * \ref express::vector "vector" returned, the caller of the the function is responsible for ensuring that
   * it is used in a \ref express::representation "representation" with a
   * \ref express::geometric_representation_context "geometric_representation_context".</SMALL>
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
    *)
    FUNCTION scalar_times_vector (scalar : REAL; vec : vector_or_direction) : vector;

      LOCAL
        v      : direction;
        mag    : REAL;
        result : vector;
      END_LOCAL;

      IF NOT EXISTS (scalar) OR NOT EXISTS (vec) THEN
        RETURN (?) ;
       ELSE
        IF 'GEOMETRY_SCHEMA.VECTOR' IN TYPEOF (vec) THEN
          v   := dummy_gri || direction(vec\vector.orientation.direction_ratios);
          mag := scalar * vec\vector.magnitude;
        ELSE
          v   := dummy_gri || direction(vec.direction_ratios);
          mag := scalar;
        END_IF;
        IF (mag < 0.0 ) THEN
          REPEAT i := 1 TO SIZEOF(v.direction_ratios);
            v.direction_ratios[i] := -v.direction_ratios[i];
          END_REPEAT;
          mag := -mag;
        END_IF;
        result := dummy_gri || vector(normalise(v), mag);
      END_IF;
      RETURN (result);

    END_FUNCTION;
    (*
   </PRE>
   *
   * \param [in] scalar a real number to participate in the product.
   * \param [in] vec a \ref express::vector "vector" or \ref express::direction "direction" which is to be multiplied. 
   * \return \ref express::vector "vector" that is the scalar multiple of the input vector.
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_scalar_times_vector.html">Ссылка 1, </A>
   * <A HREF="http://www.steptools.com/stds/smrl/data/resource_docs/geometric_and_topological_representation/sys/4_schema.htm#geometry_schema.scalar_times_vector">Ссылка 2.</A>
   */
   vector scalar_times_vector(const REAL& scalar, const vector_or_direction& vec);


  /**
   * \file
   * 4.6.34 second_proj_axis
   *
   * 4.6.35 surface_weights_positive
   */

  /**
   * \file
   * \copydetails express::vector_difference()
   */

  /**
   * \brief FUNCTION vector_difference (ISO 10303-42:2021(E), 4.6.36)
   *
   * \ref express::vector_difference "4.6.36 vector_difference"
   *
   * The \ref express::vector_difference "vector_difference" function returns the difference of the input arguments as
   * (<B>arg1</B> - <B>arg2</B>). The function returns as a \ref express::vector "vector" the vector difference of the
   * two input `vectors'. For this purpose \ref express::direction "direction"s are treated as unit vectors. The input
   * arguments shall both be of the same dimensionality but may be either
   * \ref express::direction "direction"s or \ref express::vector "vector"s. If both input arguments are
   * \ref express::vector "vector"s, they must be expressed in the same units; if both are
   * \ref express::direction "direction"s, a unitless result is produced. A zero difference vector produces a
   * \ref express::vector "vector" of zero magnitude in the direction of <B>arg1</B>.
   *
   * <SMALL>NOTE This function does not provide geometric founding for the
   * \ref express::vector "vector" returned, the caller of the the function is responsible for ensuring that it is used in a
   * \ref express::representation "representation" with a
   * \ref express::geometric_representation_context "geometric_representation_context".</SMALL>
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
    *)
    FUNCTION vector_difference (arg1 : vector_or_direction; arg2 : vector_or_direction) : vector;

      LOCAL
        result          : vector;
        res, vec1, vec2 : direction;
        mag, mag1, mag2 : REAL;
        ndim            : INTEGER;
      END_LOCAL;

      IF ((NOT EXISTS (arg1)) OR (NOT EXISTS (arg2))) OR (arg1.dim <> arg2.dim)
          THEN
        RETURN (?) ;
       ELSE
        BEGIN
          IF 'GEOMETRY_SCHEMA.VECTOR' IN TYPEOF(arg1) THEN
            mag1 := arg1\vector.magnitude;
            vec1 := arg1\vector.orientation;
          ELSE
            mag1 := 1.0;
            vec1 := arg1;
          END_IF;
          IF 'GEOMETRY_SCHEMA.VECTOR' IN TYPEOF(arg2) THEN
            mag2 := arg2\vector.magnitude;
            vec2 := arg2\vector.orientation;
          ELSE
            mag2 := 1.0;
            vec2 := arg2;
          END_IF;
          vec1 := normalise (vec1);
          vec2 := normalise (vec2);
          ndim := SIZEOF(vec1.direction_ratios);
          mag := 0.0;
          res := dummy_gri || direction(vec1.direction_ratios);
          REPEAT i := 1 TO ndim;
            res.direction_ratios[i] := mag1*vec1.direction_ratios[i] -
                                        mag2*vec2.direction_ratios[i];
            mag := mag + (res.direction_ratios[i]*res.direction_ratios[i]);
          END_REPEAT;
          IF (mag > 0.0 ) THEN
          result := dummy_gri || vector( res, SQRT(mag));
          ELSE
            result := dummy_gri || vector( vec1,  0.0);
          END_IF;
        END;
      END_IF;
      RETURN (result);

    END_FUNCTION;
    (* 
   </PRE>
   *
   * \param [in] arg1 a \ref express::direction "direction"s or \ref express::vector "vector" defining first operand in the vector difference operation;
   * \param [in] arg2 a \ref express::direction "direction"s or \ref express::vector "vector" defining the second operand for vector difference; 
   * \return difference of the input arguments as (<B>arg1</B> - <B>arg2</B>).
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_vector_difference.html">Ссылка 1, </A>
   * <A HREF="http://www.steptools.com/stds/smrl/data/resource_docs/geometric_and_topological_representation/sys/4_schema.htm#geometry_schema.vector_difference">Ссылка 2.</A>
   */
  vector vector_difference (const vector_or_direction& arg1, const vector_or_direction& arg2);

  /**
   * \file
   * 4.6.37 vector_sum
   *
   * 4.6.38 volume_weights_positive
   *
   * 4.6.39 weights_positive
   *
   * \subsection p42_s4_7 4.7 Geometry rule definition
   *
   * \subsubsection p42_s4_7_1 4.7.1 compatible_dimension
   *
   * All \ref express::geometric_representation_item "geometric_representation_item"s are geometrically founded in one or
   * more \ref express::geometric_representation_context "geometric_representation_context" coordinate spaces.
   *
   * The rule \ref p42_s4_7_1 "compatible_dimension" ensures that when
   * \ref express::geometric_representation_item "geometric_representation_item"s are geometrically founded together
   * in a coordinate space, they have the same coordinate space \ref express::dimension_count "dimension_count"
   * by ensuring that each matches the \ref express::dimension_count "dimension_count" of the coordinate space in which
   * it is geometrically founded. The rule returns TRUE when there are no \ref express::cartesian_point "cartesian_point",
   * no \ref express::direction "direction", and no \ref express::geometric_representation_context "geometric_representation_context".
   *
   * <SMALL>NOTE 1 Two-dimensional \ref express::geometric_representation_item "geometric_representation_item"s
   * that are geometrically founded in a \ref express::geometric_representation_context "geometric_representation_context"
   * are only geometrically founded in context with a 
   * \ref express::geometric_representation_context.coordinate_space_dimension "coordinate_space_dimension" of 2.
   * All \ref express::geometric_representation_item "geometric_representation_items"s founded in such a context are
   * two-dimensional. All other values of \ref express::dimension_count "dimension_count" behave similarly.</SMALL>
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
    *)
    RULE compatible_dimension FOR
    (cartesian_point,direction,geometric_representation_context);
    WHERE
      WR1: ((SIZEOF(cartesian_point) = 0) AND (SIZEOF(direction) = 0) AND (SIZEOF(geometric_representation_context) = 0)) OR check_geometric_dimension(cartesian_point, direction, geometric_representation_context);
    END_RULE;
    (*
   </PRE>
   *
   * <U>Argument definitions:</U>
   *
   * <B>cartesian_point</B>: the set of all instances of \ref express::cartesian_point "cartesian_point".
   *
   * <B>direction</B>: the set of all instances of \ref express::direction "direction".
   *
   * <B>geometric_representation_context</B>: the set of all instances of \ref express::geometric_representation_context "geometric_representation_context".
   *
   * <U>Formal propositions:</U>
   *
   * <B>WR1:</B> There shall be no \ref express::cartesian_point "cartesian_point" that has a number of coordinates
   * that differs from the \ref express::geometric_representation_context.coordinate_space_dimension "coordinate_space_dimension"
   * of the \ref express::geometric_representation_context "geometric_representation_context"s in which it is geometrically
   * founded; there shall be no \ref express::direction "direction" that has a number of
   * \ref express::direction.direction_ratios "direction_ratios" that differs from the
   * \ref express::geometric_representation_context.coordinate_space_dimension "coordinate_space_dimension" of the
   * \ref express::geometric_representation_context "geometric_representation_contexts" in which it is geometrically founded.
   * These properties are verifieded by the function \ref express::check_geometric_dimension "check_geometric_dimension".
   *
   * <SMALL>NOTE 2 A check of only \ref express::cartesian_point "cartesian_points"s and
   * \ref express::direction "direction"s is sufficient for all
   * \ref express::geometric_representation_item "geometric_representation_item"s because:<BR>
   * All \ref express::geometric_representation_item "geometric_representation_item"s appear in trees of
   * \ref express::representation_item "representation_item"s descending from the \ref express::representation.items "items" attribute of entity
   * \ref express::representation "representation". See WR1 of entity
   * \ref express::representation_item "representation_item" in ISO 10303-43.<BR>
   * Each \ref express::geometric_representation_item "geometric_representation_item" gains its position and orientation
   * information only by being, or referring to, a \ref express::cartesian_point "cartesian_point" or
   * \ref express::direction "direction" entity in such a tree. In many cases this reference is made via an
   * \ref express::placement "placement".<BR>
   * No other use of any \ref express::geometric_representation_item "geometric_representation_item"
   * is allowed that would associate it with a coordinate space or otherwise assign a
   * \ref express::dimension_count "dimension_count".</SMALL>
   *
   <PRE>
    *)
    END_SCHEMA;  -- geometry_schema
    (*
   </PRE>
   *
   * \section p42_s5 5 Topology schema
   *
   * \subsection p42_s5_1 5.1 General
   *
   * \subsection p42_s5_2 5.2 Fundamental concepts and assumptions
   *
   * \subsection p42_s5_3 5.3 topology_schema constant definition
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
    *)
    CONSTANT
    (*
    </PRE>
   *
   * \copydetails express::dummy_tri
   */

  /**
   * \brief dummy_tri (ISO 10303-42:2021(E), 5.3.1)
   *
   * \ref express::dummy_tri "5.3.1 dummy_tri"
   *
   * A \ref express::dummy_tri "dummy_tri" is a constant that is a partial entity definition to be used when types of
   * \ref express::topological_representation_item "topological_representation_item" are constructed. It provides
   * the correct supertypes and the \ref express::representation_item.name "name" attribute as an empty string.
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
    *)
      dummy_tri : topological_representation_item := representation_item('') || topological_representation_item();
    (*
    </PRE>
   *
   */
  extern const topological_representation_item dummy_tri;

  /**
   * \file
   * \subsection p42_s5_4 5.4 Topology type definitions
   *
   * 5.4.1 list_of_reversible_topology_item
   *
   * 5.4.2 reversible_topology
   *
   * 5.4.3 reversible_topology_item
   *
   * 5.4.4 set_of_reversible_topology_item
   *
   * 5.4.5 shell
   *
   * 5.4.6 tri_id_attribute_select
   *
   * \subsection p42_s5_5 5.5 Topology entity definitions
   *
   * \copydetails express::topological_representation_item
   */

  /**
   * \brief ENTITY topological_representation_item (ISO 10303-42:2021(E), 5.5.1)
   *
   * \ref express::topological_representation_item "5.5.1 topological_representation_item"
   *
   * A \ref express::topological_representation_item "topological_representation_item" is a type of
   * \ref express::representation_item "representation_item" that represents
   * the topology, or connectivity, of entities which make up the representation of an object.
   * The \ref express::topological_representation_item "topological_representation_item"
   * is the supertype for all the representation items in the topology schema.
   *
   * <SMALL>NOTE 1 As subtypes of representation_item there is an implicit and/or relationship
   * between \ref express::geometric_representation_item "geometric_representation_item" and
   * \ref express::topological_representation_item "topological_representation_item".
   * The only complex instances intended to be created are \ref express::edge_curve "edge_curve",
   * \ref express::face_surface "face_surface", and \ref express::vertex_point "vertex_point".</SMALL>
   *
   * <SMALL>NOTE 2 The definition of \ref express::topological_representation_item "topological_representation_item" defines an and/or relationship between
   * \ref express::loop "loop" and \ref express::path "path". The only valid complex instance is the \ref express::edge_loop "edge_loop" entity.</SMALL>
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
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
    </PRE>
   *
   * <U>Определения атрибутов:</U>
   *
   * <B>permanent_id</B>: an identifier that distinguishes the \ref express::topological_representation_item "topological_representation_item".
   *
   * <SMALL>NOTE 3 This attribute is an enhancement to the definition of \ref express::topological_representation_item "topological_representation_item"
   * using a method that is upwardly compatible with ISO 10303-42.</SMALL>
   *
   * <SMALL>NOTE 4 The meaning of this attribute can be defined in the annotated EXPRESS schemas that use or
   * specialize this entity, or in an agreement of common understanding between the partners sharing this information.</SMALL>
   *
   * <SMALL>NOTE 5 The context in which <B>permanent_id</B> is used as a discriminating characteristic can be identified
   * in an annotated Express schema that uses or specializes this entity, or by default, in an agreement of common
   * understanding between partners sharing this information.</SMALL>
   *
   * <B>permanent_aggregate_id</B>: an identifier that distinguishes the \ref express::topological_representation_item "topological_representation_item".
   * A <B>permanent_aggregate_id</B> supports the assignment of more than one instance of <B>topological_representation_item</B>
   * to the same identifier.
   *
   * <SMALL>NOTE 6 This attribute is an enhancement to the definition of \ref express::topological_representation_item "topological_representation_item" using
   * a method that is upwardly compatible with ISO 10303-42.</SMALL>
   *
   * <SMALL>NOTE 7 The meaning of this attribute can be defined in the annotated EXPRESS schemas that use
   * or specialize this entity, or in an agreement of common understanding between the partners sharing
   * this information.</SMALL>
   *
   * <SMALL>NOTE 8 The context in which <B>permanent_aggregate_id</B> is used as a discriminating characteristic
   * can be identified in an annotated Express schema that uses or specializes this entity, or by default, in an
   * agreement of common understanding between partners sharing this information.</SMALL>
   *
   * <U>Formal propositions:</U>
   *
   * <B>WR1:</B> Each \ref express::topological_representation_item "topological_representation_item" shall be the identified_item in at most
   * one <B>id_attribute</B>.
   *
   * <SMALL>NOTE 9 The <B>id_attribute</B> data type is defined in <B>basic_attribute_schema</B> of ISO 10303-42.</SMALL>
   *
   * <SMALL>NOTE 10 A template for constraining the population of the entity data types defined in the
   * <B>basic_attribute_schema</B> is described in annex E of ISO 10303-41.</SMALL>
   *
   * <B>WR2:</B> Each \ref express::topological_representation_item "topological_representation_item" shall be the identified_item in at most
   * one <B>aggregate_id_attribute</B>.
   *
   * <SMALL>NOTE 11 The <B>aggregate_id_attribute</B> data type is defined in
   * <B>basic_attribute_schema</B> of ISO 10303-42.</SMALL>
   *
   * <U>Informal propositions:</U><BR>
   * <B>IP1:</B> For each \ref express::topological_representation_item "topological_representation_item", consider the set of \ref express::edge "edge"s,
   * \ref express::edge_curve "edge_curve", and \ref express::face_surface "face_surface"s that are referenced, either directly or recursively,
   * from that \ref express::topological_representation_item "topological_representation_item". (Do not include in this set oriented edges or faces,
   * but do include the non-oriented edges and faces on which they are based.) Then no two distinct elements in
   * this set shall have domains that intersect.
   */
  class topological_representation_item : virtual public representation_item {

  public:

    /** \brief Конструктор неопределённого объекта */
    topological_representation_item() : representation_item() {
      add_attr_info(STEP_ATTR_LIST({ {} }, this));
    }

    /** \brief Конструктор */
    topological_representation_item(const std::string& Name) : representation_item(Name) {
      add_attr_info(STEP_ATTR_LIST({ {} }, this));
    }

    /** \brief Деструктор */
    virtual ~topological_representation_item() = default;
  };

  /**
   * \file
   * \copydetails express::vertex
   */

  /**
   * \brief ENTITY vertex (ISO 10303-42:2021(E), 5.5.2)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   <PRE>
    ENTITY vertex
       SUBTYPE OF (topological_representation_item);
    END_ENTITY;
   </PRE>
   * Вершина
   */
  class vertex : public topological_representation_item {
  public:

    /** \brief Конструктор */
    vertex(const std::string& Name) :
      representation_item(Name),
      topological_representation_item(Name) {
    }

    // Сравнение "равно"
//  bool operator==(const vertex& v);
  };

  /**
   * \file
   * \copydetails express::vertex_point
   */

  /**
   * \brief ENTITY vertex_point (ISO 10303-42:2021(E), 5.5.3)
   <PRE>
    ENTITY vertex_point
       SUBTYPE OF (vertex, geometric_representation_item);
          vertex_geometry : point;
    END_ENTITY;
   </PRE>
   * Вершина
   */
  class vertex_point : public vertex, public geometric_representation_item {

  private:

    const point* vertex_geometry;

  public:

    /** \brief Конструктор */
    vertex_point(const std::string& Name, const point* Vertex_geometry) :
      representation_item(Name),
      vertex(Name),
      geometric_representation_item(Name) {
      vertex_geometry = Vertex_geometry;
      add_attr_info(STEP_ATTR_LIST({
                                     {"vertex_geometry", vertex_geometry},
        }, this));
    }

    /** \brief Деструктор */
    virtual ~vertex_point() {
    }

    // Возврат координат точки
//    const point* get_point() const {
//      return vertex_geometry;
//    }

    // Сравнение "равенство"
    bool operator==(const vertex_point& vp) const {
      if (vertex_geometry == nullptr) {
        throw exception {"Comparing (==) this vertex_point when vertex_geometry == nullptr"};
      }
      if (vp.vertex_geometry == nullptr) {
        throw exception {"Comparing (==) with vertex_point when vertex_geometry == nullptr"};
      }
      return *vertex_geometry == *vp.vertex_geometry;
    }
  };

  /**
   * \file
   * \copydetails express::edge
   */

  /**
   * \brief ENTITY edge (ISO 10303-42:2021(E), 5.5.4)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   <PRE>
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
   </PRE>
   *
   * A  vertex  is  the  topological  construct corresponding to a point. It has
   * dimensionality  0  and  extent  0. The domain of a vertex, if present, is a
   * point  in  m  dimensional  real  space  Rm;  this  is  represented  by  the
   * vertex_point subtype.
   */
  class edge : public topological_representation_item {

  private:

    const vertex* edge_start; // Start point (vertex) of the edge.
    const vertex* edge_end;   // End point (vertex) of the edge. The same vertex can be used for both edge_start and edge_end.

  public:

    /** \brief Конструктор */
    edge(const std::string& Name, const vertex* Edge_start, const vertex* Edge_end);

    /** \brief Деструктор */
    virtual ~edge();

    const vertex* get_edge_start() const {
      return edge_start;
    }

    const vertex* get_edge_end() const {
      return edge_end;
    }

    /**
     * Сравнение двух объектов edge
     * return: 0 - разные, 1 - одинаковые, -1 - противоположные
     */
     // int compare(const edge &e2) const;
  };

  /**
   * \file
   * \copydetails express::edge_curve
   */

  /**
   * \brief ENTITY edge_curve (ISO 10303-42:2021(E), 5.5.5)
   *
   * \ref express::edge_curve "5.5.5 edge_curve"
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
    ENTITY edge_curve
       SUBTYPE OF(edge,geometric_representation_item);
       edge_geometry : curve;
       same_sense : BOOLEAN;
    END_ENTITY;
   </PRE>
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

    // const curve *get_edge_geometry() const { return edge_geometry; }
    // BOOLEAN get_sense() const { return same_sense; }

    /**
     * Сравнение двух объектов edge_curve
     * return: 0 - разные, 1 - одинаковые, -1 - противоположные
     */
    int compare(const edge_curve& ec) const;
  };

  /**
   * \file
   * \copydetails express::oriented_edge
   */

  /**
   * \brief ENTITY oriented_edge (ISO 10303-42:2021(E), 5.5.6)
   *
   * \ref express::oriented_edge "5.5.6 oriented_edge"
   *
   * An \ref express::oriented_edge "oriented_edge" is a type of edge, constructed from another edge and contains
   * a BOOLEAN orientation flag to indicate whether or not the orientation of the constructed
   * \ref express::edge "edge" agrees with the orientation of the original <B>edge</B>. Except for possible
   * re-orientation, the \ref express::oriented_edge "oriented_edge" is equivalent to the original \ref express::edge "edge".
   *
   * <SMALL>NOTE A common practice in solid modelling systems is to have an entity that represents
   * the "use" or "traversal" of an edge. This "use" entity explicitly represents the requirement
   * in a manifold solid that each edge must be traversed exactly twice, once in each direction.
   * The "use" functionality is provided by the \ref express::edge "edge" subtype \ref express::oriented_edge "oriented_edge".</SMALL>
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
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
   </PRE>
   *
   * <U>Определения атрибутов:</U><BR>
   * \ref express::oriented_edge.edge_element "edge_element": an
   * \ref express::edge "edge" entity used to construct this
   * \ref express::oriented_edge "oriented_edge";<BR>
   * \ref express::oriented_edge.orientation "orientation": a BOOLEAN, if TRUE, the topological orientation as used
   * coincides with the orientation, from start vertex to end vertex, of the
   * \ref express::oriented_edge.edge_element "edge_element".<BR>
   * \ref express::edge.edge_start "edge_start": the start vertex of the oriented edge, this is derived from the vertices of the
   * \ref express::oriented_edge.edge_element "edge_element" after taking account of the
   * \ref express::oriented_edge.orientation "orientation".
   * \ref express::edge.edge_end "edge_end": the end vertex of the oriented edge, this is derived from the vertices of the
   * \ref express::oriented_edge.edge_element "edge_element" after taking account of the
   * \ref express::oriented_edge.orientation "orientation".
   *
   * <U>Formal propositions:</U><BR>
   * <B>WR1:</B> The \ref express::oriented_edge.edge_element "edge_element" shall not be an \ref express::oriented_edge "oriented_edge".
   *
   * <A HREF="http://www.steptools.com/stds/stp_aim/html/t_oriented_edge.html">Ссылка.</A>
   */
  class oriented_edge : public edge {

  private:

    /** \brief An \ref express::edge "edge" entity used to construct this \ref express::oriented_edge "oriented_edge" */
    const edge* edge_element;

    /**
     * \brief A BOOLEAN, if TRUE, the topological orientation as used
     * coincides with the orientation, from start vertex to end vertex, of the \ref express::oriented_edge.edge_element "edge_element".
     */
    BOOLEAN* orientation;

  public:

    /** \brief Конструктор */
    oriented_edge(const std::string& Name, const edge* Edge_element, const BOOLEAN& Orientation) :
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

    const BOOLEAN& get_orientation() const {
      return *orientation;
    }

    friend oriented_edge edge_reversed(const edge& an_edge);
  };

  /**
   * \file
   * 5.5.7 seam_edge
   *
   * 5.5.8 subedge
   *
   * \copydetails express::path
   */

  /**
   * \brief ENTITY path (ISO 10303-42:2003, 5.5.9)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   <PRE>
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
    </PRE>
   */
  class path : virtual public topological_representation_item {

  public:

    /** Список ориентированных рёбер */
    LIST<oriented_edge*> edge_list;


    path(const std::string& Name) :
      representation_item(Name),
      topological_representation_item(Name),
      edge_list(1) {
      add_attr_info(STEP_ATTR_LIST({
                                     {"edge_list", &edge_list},
                                   }, this));
    }

    virtual ~path()  = default;

//    void add_edge(const oriented_edge& x) {
//      *edge_list += x;
//    }
  };

  /**
   * \file
   * 5.5.10 subpath
   *
   * 5.5.11 oriented_path
   *
   * 5.5.12 open_path
   *
   * \copydetails express::loop
   */

  /**
   * \brief ENTITY loop (ISO 10303-42:2003, 5.5.13)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   <PRE>
    -- DIFF IN AP224
    ENTITY loop
       SUPERTYPE OF (ONEOF(vertex_loop, edge_loop, poly_loop))
       SUBTYPE OF (topological_representation_item);
    END_ENTITY;
    </PRE>
   */
  class loop : virtual public topological_representation_item {

  public:

    loop(const std::string& Name) :
      representation_item(Name),
      topological_representation_item(Name) {
    }
  };

  /**
   * \file
   * \copydetails express::vertex_loop
   */

  /**
   * \brief ENTITY vertex_loop (ISO 10303-42:2021(E), 5.5.14)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   <PRE>
    ENTITY vertex_loop
       SUBTYPE OF (loop);
          loop_vertex : vertex;
    END_ENTITY;
   </PRE>
   *
   */
  class vertex_loop : public loop {

  public:

    const vertex* loop_vertex;

    vertex_loop(const std::string& Name, const vertex* Loop_vertex) :
      representation_item(Name),
      topological_representation_item(Name),
      loop(Name) {
      loop_vertex = Loop_vertex;
      add_attr_info(STEP_ATTR_LIST({
                                     {"loop_vertex", loop_vertex},
                                   }, this));
    }

    virtual ~vertex_loop() = default;
  };

  /**
   * \file
   * \copydetails express::edge_loop
   */

  /**
   * \brief ENTITY edge_loop (ISO 10303-42:2021(E), 5.5.15)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   <PRE>
    ENTITY edge_loop
       SUBTYPE OF (loop, path);
       DERIVE
          ne : INTEGER := SIZEOF(SELF\path.edge_list);
       WHERE
          WR1:
             SELF\path.edge_list[1].edge_start :=: SELF\path.edge_list[ne].edge_end;
    END_ENTITY;
   </PRE>
   */
  class edge_loop : public loop, virtual public path {

  public:

    edge_loop(const std::string& Name) :
      representation_item(Name),
      topological_representation_item(Name),
      path(Name),
      loop(Name) {
    }

    virtual ~edge_loop() {
    }
  };

  /**
   * \file
   * 5.5.16 poly_loop
   *
   * \copydetails express::face_bound
   */

   /**
    * \brief ENTITY face_bound (ISO 10303-42:2021(E), 5.5.17)
    *
    * <B>Определение объекта на языке EXPRESS:</B>
    <PRE>
     ENTITY face_bound
        SUBTYPE OF (topological_representation_item);
           bound : loop;
           orientation : BOOLEAN;
     END_ENTITY;
    </PRE>
    *
    */
  class face_bound : public topological_representation_item {

  public:

    const loop* bound;      // Граница грани
    BOOLEAN orientation; // Признак того, что направление номали грани совпадает с направлением нормали границы


    face_bound(const std::string& Name, const loop* Bound, const BOOLEAN& Orientation) :
      representation_item(Name),
      topological_representation_item(Name),
       orientation(Orientation) {
      bound = Bound;
      add_attr_info(STEP_ATTR_LIST({
                                     {"bound",        bound},
                                     {"orientation", &orientation},
        }, this));
    }

    virtual ~face_bound() = default;
  };

  /**
   * \file
   * \copydetails express::face_outer_bound
   */

  /**
   * \brief ENTITY face_outer_bound (ISO 10303-42:2021(E), 5.5.18)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   <PRE>
    ENTITY face_outer_bound
       SUBTYPE OF (face_bound);
    END_ENTITY;
   </PRE>
   *
   */
  class face_outer_bound : public face_bound {

  public:

    // Конструктор
    face_outer_bound(const std::string& Name, const loop* Bound, const BOOLEAN& Orientation) :
      representation_item(Name),
      face_bound(Name, Bound, Orientation) {
    }

    virtual ~face_outer_bound() {
    }
  };

  /**
   * \file
   * \copydetails express::face
   */

  /**
   * \brief ENTITY face (ISO 10303-42:2021(E), 5.5.19)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   <PRE>
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
   </PRE>
   *
   */
  class face : public topological_representation_item {

  public:

    SET<face_bound*> bounds;

    /** \brief Конструктор неопределённого объекта */
    face() : representation_item(), topological_representation_item() {
      add_attr_info(STEP_ATTR_LIST({
                                     {"bounds", &bounds},
                                   }, this));
    }

    /** \brief Конструктор */
    // Конструктор
    face(const std::string& Name) :
      representation_item(Name),
      topological_representation_item(Name),
      bounds(1,INTEGER())  {
      add_attr_info(STEP_ATTR_LIST({
                                     {"bounds", &bounds},
                                   }, this));
    }

    virtual ~face() = default;

    // Добавление границы
//    void add_bound(const face_bound* x) {
//      *bounds += x;
//    }

  };

  /**
   * \file
   * \copydetails express::face_surface
   */

  /**
   * \brief ENTITY face_surface (ISO 10303-42:2021(E), 5.5.20)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   <PRE>
    ENTITY face_surface
       SUBTYPE OF(face, geometric_representation_item);
          face_geometry: surface;
          same_sense: BOOLEAN;
       WHERE
          WR1 :
             NOT('STEP_MERGED_AP_SCHEMA.ORIENTED_SURFACE' IN TYPEOF(face_geometry));
    END_ENTITY;
   </PRE>
   *
   */
  class face_surface : public face, public geometric_representation_item {

  public:

    const surface* face_geometry;   // Поверхность, определяющая внутреннюю поверхность грани

    BOOLEAN same_sense;            // Признак того, что нормаль грани совпадает с нормалью поверхности, то есть
                                         // на какой стороне поверхности находится грань
    void check_face_geometry();

    /** \brief Конструктор неопределённого объекта */
    face_surface() : representation_item(), face(), geometric_representation_item() {
      face_geometry = nullptr;
      add_attr_info(STEP_ATTR_LIST({
                                     {"face_geometry",  face_geometry},
                                     {"same_sense",    &same_sense},
                                   }, this));
    }

    /** \brief Конструктор */
    face_surface(const std::string& Name, const surface* Face_geometry, const BOOLEAN& Same_sense) :
      representation_item(Name),
      face(Name),
      geometric_representation_item(Name),
      same_sense(Same_sense) {
      face_geometry = Face_geometry;
      //WR1
      check_face_geometry();

      add_attr_info(STEP_ATTR_LIST({
                                     {"face_geometry",  face_geometry},
                                     {"same_sense",    &same_sense},
                                   }, this));
    }

    virtual ~face_surface() = default;

    // Добавление границы
//    void add_bound(const face_bound* x) {
//      face::add_bound(x);
//    }
  };

  /**
   * \file
   * 5.5.21 oriented_face
   *
   * 5.5.22 subface
   *
   * \copydetails express::connected_face_set
   */

  /**
   * \brief ENTITY connected_face_set (ISO 10303-42:2021(E), 5.5.23)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   <PRE>
    ENTITY connected_face_set
       SUPERTYPE OF (ONEOF(closed_shell, open_shell))
       SUBTYPE OF (topological_representation_item);
          cfs_faces : SET [1:?] OF face;
    END_ENTITY;
    </PRE>
   *
   */
  class connected_face_set : public topological_representation_item {

  public:

    SET<face*> cfs_faces;


    connected_face_set(const std::string& Name) :
      representation_item(Name),
      topological_representation_item(Name),
      cfs_faces(1,INTEGER()) {
      add_attr_info(STEP_ATTR_LIST({
                                     {"cfs_faces", &cfs_faces},
                                   }, this));
    }

    virtual ~connected_face_set() = default;

//    void add_face(const face& x) {
//      cfs_faces += &x;
//    }
  };

  /**
   * \file
   * 5.5.24 vertex_shell
   *
   * 5.5.25 wire_shell
   *
   * 5.5.26 open_shell
   *
   * 5.5.27 oriented_open_shell
   *
   * \copydetails express::closed_shell
   */

   /**
    * \brief ENTITY closed_shell (ISO 10303-42:2021(E), 5.5.28)
    *
    * <B>Определение объекта на языке EXPRESS:</B>
    <PRE>
     ENTITY closed_shell
        SUBTYPE OF (connected_face_set);
     END_ENTITY;
    </PRE>
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
   * \file
   * 5.5.29 oriented_closed_shell
   *
   * 5.5.30 connected_face_sub_set
   *
   * 5.5.31 connected_edge_set
   *
   * 5.5.32 connected_edge_sub_set
   *
   * 5.5.33 volume_with_faces
   *
   * 5.5.34 volume_with_parametric_boundary
   *
   * 5.5.35 volume_with_shell
   *
   * 5.5.36 connected_volume_set
   *
   * 5.5.37 connected_volume_sub_set
   *
   * \subsection p42_s5_6 5.6 Topology function definitions
   *
   * 5.6.1 boolean_choose
   *
   * 5.6.2 closed_shell_reversed
   *
   * 5.6.3 conditional_reverse
   *
   * 5.6.4 edge_curve_pcurves
   *
   * \copydetails express::edge_reversed
   */

  /**
   * \brief FUNCTION edge_reversed (ISO 10303-42:2021(E), 5.6.5)
   *
   * \ref express::edge_reversed "5.6.5 edge_reversed"
   *
   * The \ref express::edge_reversed "edge_reversed" function returns an \ref express::oriented_edge "oriented_edge"
   * equivalent to the input \ref express::edge "edge" except that the orientation is reversed.
   *
   * <U>EXPRESS-спецификация:</U>
   <PRE>
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
    </PRE>
   *
   * \param [in] an_edge the \ref express::edge "edge" which is to have its orientation reversed.
   *
   * \return an \ref express::oriented_edge "oriented_edge" equivalent
   * to the input \ref express::edge "edge" except that the orientation is reversed.
   *
   */
  oriented_edge* edge_reversed(const edge* an_edge);

  /**
   * \file
   * 5.6.6 face_bound_reversed
   *
   * 5.6.7 face_reversed
   *
   * 5.6.8 get_tri_in_representations
   *
   * 5.6.9 list_face_loops
   *
   * 5.6.10 list_loop_edges
   *
   * 5.6.11 list_of_topology_reversed
   *
   * 5.6.12 list_shell_edges
   *
   * 5.6.13 list_shell_faces
   *
   * 5.6.14 list_shell_loops
   *
   * 5.6.15 list_to_set
   *
   * 5.6.16 mixed_loop_type_set
   *
   * 5.6.17 open_shell_reversed
   *
   * 5.6.18 path_head_to_tail
   *
   * 5.6.19 path_reversed
   *
   * 5.6.20 set_of_topology_reversed
   *
   * 5.6.21 shell_reversed
   *
   * 5.6.22 topology_reversed
   *
   * 5.6.23 valid_tri_ids
   *
   * 5.6.24 vertex_point_pcurves
   *
   * \section p42_s6 6 Geometric model schema
   *
   * \subsection p42_s6_1 6.1 General
   *
   * \subsection p42_s6_2 6.2 Fundamental concepts and assumptions
   *
   * \subsection p42_s6_3 6.3 Geometric model type definitions
   *
   * 6.3.1 angular_deviation
   *
   * 6.3.2 boolean_operand
   *
   * 6.3.3 boolean_operator
   *
   * 6.3.4 bounded_primitive_2d
   *
   * 6.3.5 chordal_deviation
   *
   * 6.3.6 csg_primitive
   *
   * 6.3.7 csg_select
   *
   * 6.3.8 edge_or_curve
   *
   * 6.3.9 face_or_surface
   *
   * 6.3.10 geometric_set_select
   *
   * 6.3.11 length_to_height_ratio
   *
   * 6.3.12 maximum_edge_length
   *
   * 6.3.13 path_or_composite_curve
   *
   * 6.3.14 surface_model
   *
   * 6.3.15 tessellated_facet_long_short_edge_ratio
   *
   * 6.3.16 tessellated_edge_or_vertex
   *
   * 6.3.17 tessellation_accuracy_parameter_item
   *
   * 6.3.18 wireframe_model
   *
   * \subsection p42_s6_4 6.4 Geometric model entity definitions
   *
   * \copydetails express::solid_model
   */

  /**
   * \brief ENTITY solid_model (ISO 10303-42:2021(E), 6.4.1)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   <PRE>
    -- DIFF IN AP224
    -- DIFF IN AP232
    ENTITY solid_model
       SUPERTYPE OF (ONEOF(csg_solid, manifold_solid_brep, swept_face_solid, swept_area_solid, swept_disk_solid, solid_replica))
       SUBTYPE OF (geometric_representation_item);
    END_ENTITY;
   </PRE>
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
   * \file
   * \copydetails express::manifold_solid_brep
   */

  /**
   * \brief ENTITY manifold_solid_brep (ISO 10303-42:2021(E), 6.4.2)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   <PRE>
    ENTITY manifold_solid_brep
       SUBTYPE OF (solid_model);
          outer : closed_shell;
    END_ENTITY;
   </PRE>
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
  };

  /**
   * \file
   * 6.4.3 brep_with_voids
   *
   * 6.4.4 faceted_brep
   *
   * 6.4.5 brep_2d
   *
   * 6.4.6 csg_solid
   *
   * 6.4.7 boolean_result
   *
   * 6.4.8 block
   *
   * 6.4.9 right_angular_wedge
   *
   * 6.4.10 rectangular_pyramid
   *
   * 6.4.11 faceted_primitive
   *
   * 6.4.12 tetrahedron
   *
   * 6.4.13 convex_hexahedron
   *
   * 6.4.14 sphere
   *
   * 6.4.15 right_circular_cone
   *
   * 6.4.16 right_circular_cylinder
   *
   * 6.4.17 eccentric_cone
   *
   * 6.4.18 torus
   *
   * 6.4.19 ellipsoid
   *
   * 6.4.20 cyclide_segment_solid
   *
   * 6.4.21 half_space_solid
   *
   * 6.4.22 boxed_half_space
   *
   * 6.4.23 box_domain
   *
   * 6.4.24 primitive_2d
   *
   * 6.4.25 circular_area
   *
   * 6.4.26 elliptic_area
   *
   * 6.4.27 rectangular_area
   *
   * 6.4.28 polygonal_area
   *
   * 6.4.29 area_with_outer_boundary
   *
   * 6.4.30 half_space_2d
   *
   * 6.4.31 rectangled_half_space
   *
   * 6.4.32 rectangle_domain
   *
   * 6.4.33 swept_face_solid
   *
   * 6.4.34 extruded_face_solid
   *
   * 6.4.35 revolved_face_solid
   *
   * 6.4.36 surface_curve_swept_face_solid
   *
   * 6.4.37 swept_area_solid
   *
   * 6.4.38 extruded_area_solid
   *
   * 6.4.39 revolved_area_solid
   *
   * 6.4.40 surface_curve_swept_area_solid
   *
   * 6.4.41 swept_disk_solid
   *
   * 6.4.42 trimmed_volume
   *
   * 6.4.43 solid_replica
   *
   * 6.4.44 shell_based_surface_model
   *
   * 6.4.45 face_based_surface_model
   *
   * 6.4.46 shell_based_wireframe_model
   *
   * 6.4.47 edge_based_wireframe_model
   *
   * 6.4.48 geometric_set
   *
   * 6.4.49 geometric_curve_set
   *
   * 6.4.50 sectioned_spine
   *
   * 6.4.51 geometric_set_replica
   *
   * 6.4.52 tessellated_shape_representation
   *
   * 6.4.53 tessellated_item
   *
   * 6.4.54 repositioned_tessellated_item
   *
   * 6.4.55 tessellated_structured_item
   *
   * 6.4.56 coordinates_list
   *
   * 6.4.57 tessellated_vertex
   *
   * 6.4.58 tessellated_edge
   *
   * 6.4.59 tessellated_connecting_edge
   *
   * 6.4.60 tessellated_face
   *
   * 6.4.61 triangulated_face
   *
   * 6.4.62 cubic_bezier_tessellated_edge
   *
   * 6.4.63 cubic_tessellated_connecting_edge
   *
   * 6.4.64 complex_triangulated_face
   *
   * 6.4.65 cubic_bezier_triangulated_face
   *
   * 6.4.66 tessellated_solid
   *
   * 6.4.67 tessellated_shell
   *
   * 6.4.68 tessellated_wire
   *
   * 6.4.69 tessellated_surface_set
   *
   * 6.4.70 triangulated_surface_set
   *
   * 6.4.71 complex_triangulated_surface_set
   *
   * 6.4.72 tessellated_curve_set
   *
   * 6.4.73 tessellated_geometric_set
   *
   * 6.4.74 tessellated_point_set
   *
   * 6.4.75 tessellated_shape_representation_with_accuracy_parameters
   *
   * \subsection p42_s6_5 6.5 Geometric model function definitions
   *
   * 6.5.1 acyclic_set_replica
   *
   * 6.5.2 acyclic_solid_replica
   *
   * 6.5.3 build_transformed_set
   *
   * 6.5.4 constraints_geometry_shell_based_surface_model
   *
   * 6.5.5 constraints_geometry_shell_based_wireframe_model
   *
   * 6.5.6 msb_shells
   *
   * \section p42_s7 7 Scan data 3d shape model schema
   *
   * \subsection p42_s7_1 7.1 General
   *
   * \subsection p42_s7_2 7.2 Fundamental concepts and assumptions
   *
   * \subsection p42_s7_3 7.3 Scan data 3d shape model type definition
   *
   * 7.3.1 point_cloud_set_or_superset
   *
   * \subsection p42_s7_4 7.4 Scan data 3d shape model entity definitions
   *
   * 7.4.1 scan_data_shape_representation
   *
   * 7.4.2 scanned_data_item
   *
   * 7.4.3 point_cloud_dataset
   *
   * 7.4.4 point_cloud_dataset_with_normals
   *
   * 7.4.5 point_cloud_dataset_with_colours
   *
   * 7.4.6 point_cloud_dataset_with_intensities
   *
   * 7.4.7 point_cloud_superdataset
   *
   * 7.4.8 triangulated_point_cloud_dataset
   *
   * 7.4.9 scan_3d_model
   *
   * 7.4.10 scanner_property
   *
   * 7.4.11 scanner_basic_properties
   *
   * \subsection p42_s7_5 7.5 Scan data 3d shape model function definition
   *
   * 7.5.1 consistent_sizes
   *
   * Annex A Short names of entities
   *
   * Annex B Information object registration
   *
   *  B.1 Document identification
   *
   *  B.2 Schema identification
   *
   * Annex C Computer interpretable listings
   *
   * Annex D EXPRESS-G diagrams
   */
}
