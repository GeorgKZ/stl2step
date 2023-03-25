/**
 * \file
 *
 * \brief Файл с перечислением типов данных EXPRESS.
 */

#ifndef _EXPRESS_LIST_H
#define _EXPRESS_LIST_H

namespace express {

  /* SIMPLE TYPE */

  class NUMBER;
  class REAL;
  class INTEGER;
  class STRING;
  class BOOLEAN;
  class LOGICAL;
  class BINARY;


  namespace step_merged_ap_schema {

    /**
     *
     * \verbatim
  
      (* Constructed by merging:
       *  - AP242 (ap242e2_is_mim_lf.exp)
       *  - AP214 (wg3n2628_ap214e3.exp)
       *  - AP203e2 (wg3n2635_ap203e2.exp)
       *  - AP238 STEP-NC (ap238e2_aim_lf.exp)
       *  - AP224 (wg3n1941_ap224e3.exp)
       *  - AP240 (ap240_extras.exp)
       *  - Deprecated AP203e1 (ap203e1_types.exp)
       *  - AP238 DIS (ap238_dis_extras.exp)
       *  - AP232 (wg3n1063_ap232.exp)
       *)
     \endverbatim
     *
     */

#if !defined(__DOXYGEN__)
    /* TYPE */
//    #include "list_type.h"
    /* ENTITY */
//    #include "list_entity.h"
#endif

#if 0
  FUNCTION a3ma_get_accuracy_types;
  FUNCTION a3ma_get_detected_difference_type;
  FUNCTION a3ma_get_element_type;
  FUNCTION a3ma_get_measured_type;
  FUNCTION a3ma_get_value_limit_type;
  FUNCTION a3ma_validate_accuracy_types;
  FUNCTION a3ma_validate_detected_difference_types;
  FUNCTION a3ma_validate_element_types;
  FUNCTION a3ma_validate_measured_type;
  FUNCTION a3ms_get_accuracy_types;
  FUNCTION a3ms_get_detected_difference_type;
  FUNCTION a3ms_get_element_type;
  FUNCTION a3ms_get_measured_type;
  FUNCTION a3ms_get_value_limit_type;
  FUNCTION a3ms_validate_accuracy_types;
  FUNCTION a3ms_validate_detected_difference_types;
  FUNCTION a3ms_validate_element_types;
  FUNCTION a3ms_validate_measured_type;
  FUNCTION above_plane;
  FUNCTION acyclic;
  FUNCTION acyclic_action_directive_relationship;
  FUNCTION acyclic_alternative_solution_relationship;
  FUNCTION acyclic_assignment_object_relationship;
  FUNCTION acyclic_classification_assignment_relationship;
  FUNCTION acyclic_composite_text;
  FUNCTION acyclic_curve_replica;
  FUNCTION acyclic_description_text_assignment_relationship;
  FUNCTION acyclic_external_identification_assignment_relationship;
  FUNCTION acyclic_generic_property_relationship;
  FUNCTION acyclic_geometric_tolerance_relationship;
  FUNCTION acyclic_mapped_item_usage;
  FUNCTION acyclic_mapped_representation;
  FUNCTION acyclic_point_replica;
  FUNCTION acyclic_product_category_relationship;
  FUNCTION acyclic_product_definition_relationship;
  FUNCTION acyclic_product_definition_specified_occurrence;
  FUNCTION acyclic_representation_relationship;
  FUNCTION acyclic_shape_aspect_occurrence;
  FUNCTION acyclic_shape_aspect_relationship;
  FUNCTION acyclic_solid_replica;
  FUNCTION acyclic_state_definition_to_state_assignment_relationship;
  FUNCTION acyclic_surface_replica;
  FUNCTION advanced_face_properties;
  FUNCTION all_members_of_es;
  FUNCTION any_space_satisfies;
  FUNCTION aspect_ratio;
  FUNCTION assembly_leaf;
  FUNCTION assembly_root;
  FUNCTION assembly_shape_is_defined;
  FUNCTION assoc_product_space;
  FUNCTION associated_surface;
  FUNCTION atan2;
  FUNCTION bag_to_set;
  FUNCTION base_axis;
  FUNCTION bool;
  FUNCTION boolean_choose;
  FUNCTION build_2axes;
  FUNCTION build_axes;
  FUNCTION categories_of_product;
  FUNCTION check_associative_shape_aspects;
  FUNCTION check_continuous_edges;
  FUNCTION check_curve_planarity;
  FUNCTION check_geometric_dimension;
  FUNCTION check_sparse_index_domain;
  FUNCTION check_sparse_index_to_loc;
  FUNCTION check_sparse_loc_range;
  FUNCTION check_text_alignment;
  FUNCTION check_text_font;
  FUNCTION class_assignment_is_valid;
  FUNCTION closed_shell_reversed;
  FUNCTION collect_joints;
  FUNCTION compare_basis_and_coef;
  FUNCTION compatible_complex_number_regions;
  FUNCTION compatible_es_values;
  FUNCTION compatible_intervals;
  FUNCTION compatible_spaces;
  FUNCTION composable_sequence;
  FUNCTION compute_total_depth;
  FUNCTION conditional_reverse;
  FUNCTION consistent_sizes;
  FUNCTION constraints_composite_curve_on_surface;
  FUNCTION constraints_geometry_shell_based_surface_model;
  FUNCTION constraints_geometry_shell_based_wireframe_model;
  FUNCTION constraints_param_b_spline;
  FUNCTION constraints_param_local_b_spline;
  FUNCTION constraints_rectangular_composite_surface;
  FUNCTION constraints_scaling;
  FUNCTION control_characters_free;
  FUNCTION convert_plane_angle_for_pair_from_radian;
  FUNCTION convert_spatial_to_ypr_rotation;
  FUNCTION convert_to_literal;
  FUNCTION convert_to_maths_function;
  FUNCTION convert_to_maths_value;
  FUNCTION convert_to_operand;
  FUNCTION convert_to_operands;
  FUNCTION convert_to_operands_prcmfn;
  FUNCTION coordinated_pair_link_representation;
  FUNCTION cross_product;
  FUNCTION curve_weights_positive;
  FUNCTION default_tolerance_table_cell_wr2;
  FUNCTION default_tolerance_table_cell_wr3;
  FUNCTION default_tolerance_table_cell_wr4;
  FUNCTION default_tolerance_table_cell_wr5;
  FUNCTION definite_integral_check;
  FUNCTION definite_integral_expr_check;
  FUNCTION dependently_instantiated;
  FUNCTION derive_angle;
  FUNCTION derive_definite_integral_domain;
  FUNCTION derive_dimensional_exponents;
  FUNCTION derive_elementary_function_domain;
  FUNCTION derive_elementary_function_range;
  FUNCTION derive_finite_function_domain;
  FUNCTION derive_finite_function_range;
  FUNCTION derive_function_domain;
  FUNCTION derive_function_range;
#endif

//  dimension_count dimension_of(const geometric_representation_item* item);

#if 0
  FUNCTION dimensions_for_si_unit;
  FUNCTION domain_from;
  FUNCTION dot_count;
  FUNCTION dot_product;
  FUNCTION dotted_identifiers_syntax;
  FUNCTION drop_numeric_constraints;
  FUNCTION duration_is_negative;
  FUNCTION duration_is_positive;
  FUNCTION edge_reversed;
  FUNCTION enclose_cregion_in_pregion;
  FUNCTION enclose_pregion_in_cregion;
  FUNCTION enclose_pregion_in_pregion;
  FUNCTION equal_cregion_pregion;
  FUNCTION equal_maths_functions;
  FUNCTION equal_maths_spaces;
  FUNCTION equal_maths_values;
  FUNCTION es_subspace_of_es;
  FUNCTION expression_is_constant;
  FUNCTION external_version_assignment_is_valid;
  FUNCTION extract_factors;
  FUNCTION extremal_position_check;
  FUNCTION face_bound_reversed;
  FUNCTION face_reversed;
  FUNCTION factor1;
  FUNCTION factor_space;
  FUNCTION find_assembly_root;
  FUNCTION find_representative_shape_representation_of_product_definition;
  FUNCTION find_representative_shape_representation_of_shape_aspect;
  FUNCTION find_shape_representation_of_product_definition;
  FUNCTION find_shape_representation_of_shape_aspect;
  FUNCTION first_proj_axis;
  FUNCTION frame_associated_to_background;
  FUNCTION free_variables_of;
  FUNCTION function_applicability;
  FUNCTION function_is_1d_array;
  FUNCTION function_is_1d_table;
  FUNCTION function_is_2d_table;
  FUNCTION function_is_array;
  FUNCTION function_is_table;
  FUNCTION gbsf_check_curve;
  FUNCTION gbsf_check_point;
  FUNCTION gbsf_check_surface;
  FUNCTION geometric_dimensionalities_in_contexts;
  FUNCTION get_action_property;
  FUNCTION get_aggregate_id_value;
  FUNCTION get_associated_mandatory_document_ids;
  FUNCTION get_basis_surface;
  FUNCTION get_coordinate_values;
  FUNCTION get_count_of_relating_amr;
  FUNCTION get_count_of_relating_amr_with_name;
  FUNCTION get_descendant_occurrences;
  FUNCTION get_description_value;
  FUNCTION get_diameter_for_round_hole;
  FUNCTION get_directed_link;
  FUNCTION get_id_value;
  FUNCTION get_kinematic_joints_from_kinematic_loops;
  FUNCTION get_kinematic_joints_from_oriented_joints;
  FUNCTION get_multi_language;
  FUNCTION get_name_value;
  FUNCTION get_plane_of_implicit_geometry;
  FUNCTION get_property_definition_representations;
  FUNCTION get_relating_amr;
  FUNCTION get_relative_direction_2points;
  FUNCTION get_representations_for_items;
  FUNCTION get_resource_property;
  FUNCTION get_role;
  FUNCTION get_root_shape_aspect;
  FUNCTION get_round_holes_for_composite_hole;
  FUNCTION get_shape_aspect_property_definition_representations;
  FUNCTION get_shape_aspects;
  FUNCTION get_tool_body_item;
  FUNCTION has_values_space;
  FUNCTION increasing_values_in_list;
  FUNCTION inspected_product_definition;
  FUNCTION invalidate_vrep_item;
  FUNCTION is_acyclic;
  FUNCTION is_int_expr;
  FUNCTION is_sql_mappable;
  FUNCTION item_correlation;
  FUNCTION item_in_context;
  FUNCTION leap_year;
  FUNCTION list_face_loops;
  FUNCTION list_of_topology_reversed;
  FUNCTION list_selected_components;
  FUNCTION list_to_array;
  FUNCTION list_to_set;
  FUNCTION make_array_of_array;
  FUNCTION make_array_of_array_of_array;
  FUNCTION make_atom_based_literal;
  FUNCTION make_binary_literal;
  FUNCTION make_boolean_literal;
  FUNCTION make_cartesian_complex_number_region;
  FUNCTION make_complex_number_literal;
  FUNCTION make_elementary_function;
  FUNCTION make_elementary_space;
  FUNCTION make_extended_tuple_space;
  FUNCTION make_finite_integer_interval;
  FUNCTION make_finite_real_interval;
  FUNCTION make_finite_space;
  FUNCTION make_function_application;
  FUNCTION make_function_space;
  FUNCTION make_int_literal;
  FUNCTION make_listed_product_space;
  FUNCTION make_logical_literal;
  FUNCTION make_maths_enum_literal;
  FUNCTION make_maths_tuple_literal;
  FUNCTION make_numeric_set;
  FUNCTION make_parallel_composed_function;
  FUNCTION make_polar_complex_number_region;
  FUNCTION make_real_interval_from_min;
  FUNCTION make_real_interval_to_max;
  FUNCTION make_real_literal;
  FUNCTION make_string_literal;
  FUNCTION make_uniform_product_space;
  FUNCTION max_exists;
  FUNCTION max_included;
  FUNCTION md_pmi_name_and_type_correlation;
  FUNCTION md_valid_content_in_geometric_set_for_placeholder;
  FUNCTION member_of;
  FUNCTION min_exists;
  FUNCTION min_included;
  FUNCTION mixed_loop_type_set;
  FUNCTION msb_shells;
  FUNCTION msf_curve_check;
  FUNCTION msf_surface_check;
  FUNCTION nmsf_curve_check;
  FUNCTION nmsf_surface_check;
  FUNCTION no_cyclic_domain_reference;
  FUNCTION no_cyclic_space_reference;
  FUNCTION nondecreasing;
  FUNCTION normalise;
  FUNCTION number_superspace_of;
  FUNCTION number_tuple_subspace_check;
  FUNCTION one_tuples_of;
  FUNCTION open_path_based_inner_boundary;
  FUNCTION open_shell_reversed;
  FUNCTION orthogonal_complement;
  FUNCTION parallel_composed_function_composability_check;
  FUNCTION parallel_composed_function_domain_check;
  FUNCTION parse_express_identifier;
  FUNCTION partial_derivative_check;
  FUNCTION path_head_to_tail;
  FUNCTION path_reversed;
  FUNCTION plane_angle_for_pair_in_radian;
  FUNCTION product_category_graph_members;
  FUNCTION real_max;
  FUNCTION real_min;
  FUNCTION regular_indexing;
  FUNCTION relating_shape_representations_of_extreme_values;
  FUNCTION remove_first;
  FUNCTION repackage;
  FUNCTION representation_of_link;
  FUNCTION representations_mapped_into;
  FUNCTION same_side;
  FUNCTION scalar_times_vector;
  FUNCTION second_proj_axis;
  FUNCTION set_of_topology_reversed;
  FUNCTION shape_of_array;
  FUNCTION shell_reversed;
  FUNCTION simplify_function_application;
  FUNCTION simplify_generic_expression;
  FUNCTION simplify_maths_space;
  FUNCTION simplify_maths_value;
  FUNCTION singleton_member_of;
  FUNCTION sort_link_associations;
  FUNCTION space_dimension;
  FUNCTION space_is_continuum;
  FUNCTION space_is_singleton;
  FUNCTION stripped_typeof;
  FUNCTION sts_get_general_datum_reference;
  FUNCTION sts_get_product_definition_shape;
  FUNCTION subspace_of;
  FUNCTION subspace_of_es;
  FUNCTION substitute;
  FUNCTION suitably_based_mechanism;
  FUNCTION surface_condition_correlation;
  FUNCTION surface_weights_positive;
  FUNCTION topology_reversed;
  FUNCTION type_check_function;
  FUNCTION unambiguously_specified_multi_level_reference_designator;
  FUNCTION unique_in_product_definition;
  FUNCTION unique_in_shape_aspect;
  FUNCTION unique_link_usage;
  FUNCTION used_variables;
  FUNCTION using_items;
  FUNCTION using_product_definition_of_shape_aspect;
  FUNCTION using_product_definition_of_shape_representation;
  FUNCTION using_representation_with_mapping;
  FUNCTION using_representations;
  FUNCTION using_shape_aspect_of_shape_representation;
  FUNCTION valid_basis_curve_in_2d_wireframe;
  FUNCTION valid_calendar_date;
  FUNCTION valid_csg_2d_primitives;
  FUNCTION valid_datum_target_parameters;
  FUNCTION valid_geometrically_bounded_wf_curve;
  FUNCTION valid_geometrically_bounded_wf_point;
  FUNCTION valid_measure_value;
  FUNCTION valid_selected_instance_representation;
  FUNCTION valid_time;
  FUNCTION valid_units;
  FUNCTION valid_wireframe_edge_curve;
  FUNCTION valid_wireframe_vertex_point;
  FUNCTION validate_accuracy_types;
  FUNCTION validate_attribute_id;
  FUNCTION validate_countersink_radii;
  FUNCTION validate_ecdq_inspected_elements_type;
  FUNCTION validate_inspected_elements_type;
  FUNCTION validate_locations_of_extreme_value_type;
  FUNCTION validate_measured_data_type;
  FUNCTION value_limit_type;
  FUNCTION value_range_aggregate_rep_item;
  FUNCTION value_range_wr1;
  FUNCTION value_range_wr2;
  FUNCTION value_range_wr3;
  FUNCTION values_space_of;
  FUNCTION vector_difference;
  FUNCTION verify_angle_measure_action_property;
  FUNCTION verify_angle_measure_rep_item;
  FUNCTION verify_angle_measure_resource_property;
  FUNCTION verify_angle_measure_tool_body_item;
  FUNCTION verify_ballnose_endmill_dimensions;
  FUNCTION verify_bullnose_endmill_dimensions;
  FUNCTION verify_count_measure_action_property;
  FUNCTION verify_count_measure_rep_item;
  FUNCTION verify_count_measure_resource_property;
  FUNCTION verify_count_measure_tool_body_item;
  FUNCTION verify_descriptive_action_property;
  FUNCTION verify_enumeration_action_property;
  FUNCTION verify_enumeration_resource_property;
  FUNCTION verify_enumeration_tool_body_item;
  FUNCTION verify_length_measure_action_property;
  FUNCTION verify_length_measure_rep_item;
  FUNCTION verify_length_measure_resource_property;
  FUNCTION verify_length_measure_tool_body_item;
  FUNCTION verify_linear_speed_measure_rep_item;
  FUNCTION verify_numeric_measure_action_property;
  FUNCTION verify_optional_action_property;
  FUNCTION verify_optional_in_process_geometry;
  FUNCTION verify_optional_relating_amr;
  FUNCTION verify_optional_relating_amr_with_name;
  FUNCTION verify_optional_rep_item;
  FUNCTION verify_optional_resource_property;
  FUNCTION verify_optional_tool_body_item;
  FUNCTION verify_pressure_measure_action_property;
  FUNCTION verify_ratio_measure_action_property;
  FUNCTION verify_ratio_measure_rep_item;
  FUNCTION verify_related_type_for_amr;
  FUNCTION verify_related_type_for_amr_with_name;
  FUNCTION verify_rep_item_for_action_property;
  FUNCTION verify_rep_item_for_resource_property;
  FUNCTION verify_rep_item_for_tool_body;
  FUNCTION verify_rep_name_for_action_property;
  FUNCTION verify_rep_type_for_action_property;
  FUNCTION verify_rep_type_for_resource_property;
  FUNCTION verify_required_action_property;
  FUNCTION verify_required_relating_amr;
  FUNCTION verify_required_relating_amr_with_name;
  FUNCTION verify_required_rep_item;
  FUNCTION verify_required_resource_property;
  FUNCTION verify_required_tool_body_item;
  FUNCTION verify_rotary_speed_measure_rep_item;
  FUNCTION verify_time_measure_action_property;
  FUNCTION verify_time_measure_rep_item;
  FUNCTION verify_time_measure_resource_property;
  FUNCTION volume_weights_positive;
  FUNCTION weights_positive;
  FUNCTION ypr_index;
#endif

  }
}

#endif /* _EXPRESS_LIST_H */