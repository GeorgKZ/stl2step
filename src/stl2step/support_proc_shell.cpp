/**
 * \file
 *
 * \brief Файл с определением метода process_shell класса STP_API высокоуровневого интерфейса создания выходного файла
 */

#include "stdafx.h"
#include "precision.h"
#include "err.h"
#include "shell.h"
#include "support.h"

namespace express {

  err_enum_t STEP_API::process_shell(
    const std::string& product_name,
    const prim3d::shell& shell,
    const closed_shell* s_closed_shell,
    bool save_shell,
    const presentation_style_assignment* m_presentation_style_assignment,
    mechanical_design_geometric_presentation_representation* m_mechanical_design_geometric_presentation_representation,
    const axis2_placement_3d* m_axis2_placement_3d,
    const shape_representation* m_shape_representation,
    const product_definition_or_reference* m_product_definition_or_reference,
    const geometry::vector* shift)
  {

    // Изделие - фигура (замкнутая оболочка)
    product* s_product = new product(product_name, product_name);
    S.push_back(s_product);
    s_product->add_frame(g_product_context);
    g_related_product_category->add_product(s_product);
    // Определённая версия (вариант, разновидность) базового изделия - фигура
    product_definition_formation* s_formation = new product_definition_formation("", "", s_product);
    S.push_back(s_formation);
    // Конктретный вид версии изделия - фигура
    //!!!
    auto tmp1_product_definition = new product_definition("", "", s_formation, g_product_definition_context);
    S.push_back(tmp1_product_definition);
    product_definition_or_reference* s_product_definition_or_reference = new product_definition_or_reference(tmp1_product_definition);
    noS.push_back(s_product_definition_or_reference);
    // **************************************************************************
    // Форма изделия
  //      s_characterized_definition.characterized_product_definition.product_definition = tmp1_product_definition;
    characterized_product_definition* s_characterized_product_definition = new characterized_product_definition(tmp1_product_definition);
    noS.push_back(s_characterized_product_definition);
    characterized_definition* s_characterized_definition = new characterized_definition(s_characterized_product_definition);
    noS.push_back(s_characterized_definition);
    product_definition_shape* s_product_definition_shape = new product_definition_shape("", "", s_characterized_definition);
    S.push_back(s_product_definition_shape);
    // Представление информации о форме
    shape_representation* s_shape_representation = new shape_representation("", g_representation_context_group);
    S.push_back(s_shape_representation);
    s_shape_representation->add_item(g_axis2_placement_3d);

    if (save_shell) {
      S.push_back(s_closed_shell);
    }

    // Односвязное тело
    auto tmp2_geometric_representation_item = new manifold_solid_brep("", s_closed_shell);
    S.push_back(tmp2_geometric_representation_item);

    // Настройки стиля поверхности
    styled_item_target* s_styled_item_target = new styled_item_target(tmp2_geometric_representation_item);
    noS.push_back(s_styled_item_target);
    styled_item* s_styled_item = new styled_item("", s_styled_item_target);
    S.push_back(s_styled_item);
    s_styled_item->add_style(m_presentation_style_assignment);
    m_mechanical_design_geometric_presentation_representation->add_item(s_styled_item);
    // Представление формы
    advanced_brep_shape_representation* s_advanced_brep_shape_representation = new advanced_brep_shape_representation("", g_representation_context_group);
    S.push_back(s_advanced_brep_shape_representation);
    s_advanced_brep_shape_representation->add_item(tmp2_geometric_representation_item);
    s_advanced_brep_shape_representation->add_item(g_axis2_placement_3d);
    // Взаимосвязь представлений формы
    shape_representation_relationship* s_shape_representation_relationship = new shape_representation_relationship("", "", s_advanced_brep_shape_representation, s_shape_representation);
    S.push_back(s_shape_representation_relationship);
    // Представление определённой формы

    //!!!
    const represented_definition* gt_definition = new represented_definition(s_product_definition_shape);
    noS.push_back(gt_definition);

    shape_definition_representation* s_shape_definition_representation = new shape_definition_representation(gt_definition, s_advanced_brep_shape_representation);
    S.push_back(s_shape_definition_representation);

    // Взаимосвязь между материалом и фигурой
    // Система координат фигуры

    const auto& svv = shell.get_pos();
    double X = 0.0, Y = 0.0, Z = 0.0;
    if (shift != nullptr) {
      X = shift->getX();
      Y = shift->getY();
      Z = shift->getZ();
    }
    cartesian_point* s_location = new cartesian_point("", svv.getX() + X, svv.getY() + Y, svv.getZ() + Z);
    S.push_back(s_location);
    direction* s_axis = new direction("", 3, 0, 0, 1);
    S.push_back(s_axis);
    direction* s_ref_direction = new direction("", 3, 1, 0, 0);
    S.push_back(s_ref_direction);
    axis2_placement_3d* s_axis2_placement_3d = new axis2_placement_3d("", s_location, s_axis, s_ref_direction);
    S.push_back(s_axis2_placement_3d);
    s_shape_representation->add_item(s_axis2_placement_3d);

    //!!!
    item_defined_transformation* sm_item_defined_transformation = new item_defined_transformation("", s_axis2_placement_3d, m_axis2_placement_3d);
    S.push_back(sm_item_defined_transformation);
    transformation* sm_transf = new transformation(sm_item_defined_transformation);
    noS.push_back(sm_transf);

    // Отношения представления (формирование экземпляра сложного объекта (complex entity instance))
    // !!! new representation_relationship("", "", m_shape_representation, s_advanced_brep_shape_representation);
    representation_relationship* sm_representation_rel_group = new representation_relationship_with_transformation("", "", m_shape_representation, s_advanced_brep_shape_representation, sm_transf);
    S.push_back(sm_representation_rel_group);
    // !!! sm_representation_rel_group->add_complex(new representation_relationship_with_transformation("", "", m_shape_representation, s_advanced_brep_shape_representation, sm_transf));

    auto* t_shape_representation_relationship = new shape_representation_relationship("", "", m_shape_representation, s_advanced_brep_shape_representation);
    noS.push_back(t_shape_representation_relationship);
    sm_representation_rel_group->add_complex(t_shape_representation_relationship);

    // Связь с объектом вышестоящей иерархии
    next_assembly_usage_occurrence* sm_next_assembl = new next_assembly_usage_occurrence("", std::string("material->shell (") + product_name + std::string(")"), std::string("material->shell (") + product_name + std::string(")"), m_product_definition_or_reference, s_product_definition_or_reference);
    S.push_back(sm_next_assembl);
    // Форма изделия
    //!!!
  //      product_definition_relationship* sm_product_definition_relationship = new product_definition_relationship(sm_next_assembl);
    characterized_product_definition* t_characterized_product_definition = new characterized_product_definition(sm_next_assembl);
    noS.push_back(t_characterized_product_definition);
    characterized_definition* sm_characterized_definition = new characterized_definition(t_characterized_product_definition);
    noS.push_back(sm_characterized_definition);
    //      sm_characterized_definition.characterized_product_definition.product_definition_relationship = sm_next_assembl;
    product_definition_shape* sm_product_definition_shape = new product_definition_shape("", "", sm_characterized_definition);
    S.push_back(sm_product_definition_shape);
    // Связь представления формы с определением изделия
    context_dependent_shape_representation* sm_context_dependent_shape_representation = new context_dependent_shape_representation(static_cast<const shape_representation_relationship*>(sm_representation_rel_group), sm_product_definition_shape);
    S.push_back(sm_context_dependent_shape_representation);

    return err_enum_t::ERROR_OK;
  }
}
