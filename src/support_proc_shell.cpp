/**
 * \file
 *
 * \brief Файл с определениями классов высокоуровневого интерфейса создания выходного файла..
 */

#ifndef TESTONLY

#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "precision.h"
#include "err.h"
#include "shell.h"
#include "support.h"

namespace express {

  err_enum_t STEP_API::process_shell(
    const std::string& product_name,
    const closed_shell* s_closed_shell,
    bool save_shell,
    const presentation_style_assignment* m_presentation_style_assignment,
          mechanical_design_geometric_presentation_representation* m_mechanical_design_geometric_presentation_representation,
    const axis2_placement_3d* m_axis2_placement_3d,
    const shape_representation* m_shape_representation,
    const product_definition_or_reference* m_product_definition_or_reference,
    const geometry::vector& pos)
  {

    // Изделие - фигура (замкнутая оболочка)
    const auto s_product = new product(product_name, "");
    S.push_back(s_product);
    s_product->frame_of_reference += g_product_context;
    g_related_product_category->products += s_product;

    // Определённая версия (вариант, разновидность) базового изделия - фигура
    const auto s_formation = new product_definition_formation("", "", s_product);
    S.push_back(s_formation);

    // Конктретный вид версии изделия - фигура
    const auto s_product_definition = new product_definition("", "", s_formation, g_product_definition_context);
    S.push_back(s_product_definition);
    product_definition_or_reference* s_product_definition_or_reference = new product_definition_or_reference(s_product_definition);
    noS.push_back(s_product_definition_or_reference);

    // Форма изделия
    const auto s_characterized_product_definition1 = new characterized_product_definition(s_product_definition);
    noS.push_back(s_characterized_product_definition1);
    const auto s_characterized_definition1 = new characterized_definition(s_characterized_product_definition1);
    noS.push_back(s_characterized_definition1);
    product_definition_shape* s_product_definition_shape1 = new product_definition_shape("", "", s_characterized_definition1);
    S.push_back(s_product_definition_shape1);

    // Представление информации о форме
    const auto s_shape_representation = new shape_representation("", g_representation_context_group);
    S.push_back(s_shape_representation);
    s_shape_representation->items += g_axis2_placement_3d;

    if (save_shell) {
      S.push_back(s_closed_shell);
    }

    // Односвязное тело
    const auto s_geometric_representation_item = new manifold_solid_brep("", s_closed_shell);
    S.push_back(s_geometric_representation_item);

    // Настройки стиля поверхности
    const auto s_styled_item_target = new styled_item_target(s_geometric_representation_item);
    noS.push_back(s_styled_item_target);
    const auto s_styled_item = new styled_item("", s_styled_item_target);
    S.push_back(s_styled_item);
    s_styled_item->styles += m_presentation_style_assignment;
    m_mechanical_design_geometric_presentation_representation->items += s_styled_item;

    // Представление формы
    const auto s_advanced_brep_shape_representation = new advanced_brep_shape_representation("", g_representation_context_group);
    S.push_back(s_advanced_brep_shape_representation);
    s_advanced_brep_shape_representation->items += s_geometric_representation_item;
    s_advanced_brep_shape_representation->items += g_axis2_placement_3d;

    // Взаимосвязь представлений формы
    const auto s_shape_representation_relationship1 = new shape_representation_relationship("", "", s_advanced_brep_shape_representation, s_shape_representation);
    S.push_back(s_shape_representation_relationship1);

    // Представление определённой формы
    const auto s_represented_definition = new represented_definition(s_product_definition_shape1);
    noS.push_back(s_represented_definition);

    const auto s_shape_definition_representation = new shape_definition_representation(s_represented_definition, s_advanced_brep_shape_representation);
    S.push_back(s_shape_definition_representation);

    // Система координат фигуры
    const auto s_location = new cartesian_point("", pos.getX(), pos.getY(), pos.getZ());
    S.push_back(s_location);
    const auto s_axis = new direction("", 0, 0, 1);
    S.push_back(s_axis);
    const auto s_ref_direction = new direction("", 1, 0, 0);
    S.push_back(s_ref_direction);
    const auto s_axis2_placement_3d = new axis2_placement_3d("", s_location, s_axis, s_ref_direction);
    S.push_back(s_axis2_placement_3d);
    s_shape_representation->items += s_axis2_placement_3d;

    // Взаимосвязь между материалом и фигурой
    const auto s_item_defined_transformation = new item_defined_transformation("", s_axis2_placement_3d, m_axis2_placement_3d, "");
    S.push_back(s_item_defined_transformation);
    const auto s_transformation = new transformation(s_item_defined_transformation);
    noS.push_back(s_transformation);

    // Отношения представления (формирование экземпляра сложного объекта)
    const auto s_representation_relationship_with_transformation = new representation_relationship_with_transformation("", "", m_shape_representation, s_advanced_brep_shape_representation, s_transformation);
    noS.push_back(s_representation_relationship_with_transformation);
    const auto s_shape_representation_relationship2 = new shape_representation_relationship("", "", m_shape_representation, s_advanced_brep_shape_representation);
    S.push_back(s_shape_representation_relationship2);
    s_shape_representation_relationship2->add_complex(s_representation_relationship_with_transformation);

    // Связь с объектом вышестоящей иерархии
    const auto s_next_assembly_usage_occurrence = new next_assembly_usage_occurrence("",
      std::string("material->shell (") + product_name + std::string(")"),
      "",
      m_product_definition_or_reference, s_product_definition_or_reference, "");
    S.push_back(s_next_assembly_usage_occurrence);

    // Форма изделия
    const auto s_characterized_product_definition2 = new characterized_product_definition(s_next_assembly_usage_occurrence);
    noS.push_back(s_characterized_product_definition2);
    const auto s_characterized_definition2 = new characterized_definition(s_characterized_product_definition2);
    noS.push_back(s_characterized_definition2);
    const auto s_product_definition_shape2 = new product_definition_shape("", "", s_characterized_definition2);
    S.push_back(s_product_definition_shape2);

    // Связь представления формы с определением изделия
    const auto s_context_dependent_shape_representation = new context_dependent_shape_representation(s_shape_representation_relationship2, s_product_definition_shape2);
    S.push_back(s_context_dependent_shape_representation);

    return err_enum_t::ERROR_OK;
  }
}

#endif