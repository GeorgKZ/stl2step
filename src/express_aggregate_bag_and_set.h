#pragma once
/**
 * \file
 * \brief Файл с определениями функций агрегированных типов данных \ref express::BAG "BAG (множество)" \ref express::SET_GENERIC "SET (набор)"
 *  языка EXPRESS (ГОСТ Р ИСО 10303-11-2009, 8.2.3, 8.2.4)
 */

namespace express {


  template<class T>
  auto BAG<T>::find_same_element(const GENERIC& rhs, bool compare_instance) {
    bool was_unknown = false;
    for (auto i = elements.begin(); i != elements.end(); ++i) {
      LOGICAL cmp;
      if (compare_instance) {
        cmp = (*i).first.is_instance_equal(rhs);
      }
      else {
        cmp = (*i).first.is_value_equal(rhs);
      }
      if (cmp.is_true()) {
        return std::make_pair(LOGICAL::TRUE, i);
      }
      if (cmp.is_unknown()) was_unknown = true;
    }
    return std::make_pair(was_unknown ? LOGICAL::UNKNOWN : LOGICAL::FALSE, elements.end());
  }
}