/**
 * \file
 *
 * \brief Файл с определениями функций класса AGGREGATE_GENERIC, соответствующего ГОСТ Р ИСО 10303-11-2009, п.8.2,
 * и некоторых использующих класс AGGREGATE_GENERIC в качестве аргумента
 */

#include "stdafx.h"
#include "express.h"

namespace express {

  /**
   * \file
   * Функции класса AGGREGATE_GENERIC:
   */

  /**
   * \file
   * * \copybrief express::AGGREGATE_GENERIC::get_lobound() const
   */
  integer_type AGGREGATE_GENERIC::get_lobound() const {
    return bound_1.is_determinated() ? bound_1.get_integer_value() : 0;
  }

  /**
   * \file
   * * \copybrief express::AGGREGATE_GENERIC::is_hibound() const
   */
  bool AGGREGATE_GENERIC::is_hibound() const {
    return bound_2.is_determinated();
  }

  /**
   * \file
   * * \copybrief express::AGGREGATE_GENERIC::get_hibound() const
   */
  integer_type AGGREGATE_GENERIC::get_hibound() const {
    if (!bound_2.is_determinated()) {
      throw exception{ __MYFUNCNAME__, "bound_2 is indeterminated. Check it with is_hibound()." };
    }
    return bound_2.get_integer_value();
  }

  /**
   * \file
   * * \copybrief express::AGGREGATE_GENERIC::get_constant_internal_element(express::integer_type) const
   */
  const GENERIC& AGGREGATE_GENERIC::get_constant_internal_element(integer_type index) const {
    if (!determinated) {
      throw exception{ __MYFUNCNAME__, "AGGREGATE_GENERIC (internal indexed) can not be indeterminated" };
    }


//!!!! set not unique, not optional...

    if (index >= get_uniq_size()) {
      throw exception{ __MYFUNCNAME__, "Index = %lli can not be out of borders (from 0 to %lli)", index, get_uniq_size()-1 };
    }

#ifdef TRACE_AGGREGATE
      printf("%s: (index = %lli from %lli)\n", __MYFUNCNAME__, index, get_uniq_size());
#endif

    integer_type cnt_next, cnt = 0;
    for (integer_type i = 0; i < get_uniq_size(); ++i) {
      cnt_next = cnt + get_uniq_count(i);
      if (index >= cnt && index < cnt_next) {
        return get_constant_uniq_element(i);
      }
      cnt = cnt_next;
    }
    throw exception{ __MYFUNCNAME__, "internal error - execution shall not reach this line" };
  }

  /**
   * \file
   * * \copybrief express::AGGREGATE_GENERIC::get_internal_element(express::integer_type)
   */
  GENERIC& AGGREGATE_GENERIC::get_internal_element(integer_type index) {
    if (!determinated) {
      throw exception{ __MYFUNCNAME__, "AGGREGATE may not be undeterminated" };
    }

    if (index >= get_uniq_size()) {
      throw exception{ __MYFUNCNAME__, "Index = %lli can not be out of borders (from 0 to %lli)", index, get_uniq_size()-1 };
    }

#ifdef TRACE_AGGREGATE
      printf("%s: (index = %lli from %lli)\n", __MYFUNCNAME__, index, get_uniq_size());
#endif

    integer_type cnt_next, cnt = 0;
    for (integer_type i = 0; i < get_uniq_size(); ++i) {
      cnt_next = cnt + get_uniq_count(i);
      if (index >= cnt && index < cnt_next) {
        return get_uniq_element(i);
      }
      cnt = cnt_next;
    }
    throw exception{ __MYFUNCNAME__, "internal error - execution shall not reach this line" };
  }

  /**
   * \file
   * * \copybrief express::AGGREGATE_GENERIC::get_elements_size() const
   */
  integer_type AGGREGATE_GENERIC::get_elements_size() const {
    return size;
  }

  /**
   * \file
   * * \copybrief express::AGGREGATE_GENERIC::find_same_element(const express::GENERIC&s, bool) const
   */
  integer_type AGGREGATE_GENERIC::find_same_element(const GENERIC& rhs, bool compare_value) const {
    if (!determinated || !rhs.is_determinated()) {
      return -2;
    }

    integer_type was_unknown = -1;
    for (auto i = 0; i < get_uniq_size(); ++i) {
      LOGICAL cmp = get_constant_uniq_element(i).is_equal(rhs, compare_value);
      if (cmp.is_true()) {
        return i;
      }
      else if (cmp.is_unknown()) {
        was_unknown = -2;
      }
    }
    return was_unknown;
  }

  /**
   * \file
   * * \copybrief express::AGGREGATE_GENERIC::check_same_element(const express::GENERIC&s, bool) const
   */
  integer_type AGGREGATE_GENERIC::check_same_element(const GENERIC& rhs, bool compare_value) const {
    if (!determinated || !rhs.is_determinated()) {
      return -1;
    }

    integer_type found = 0;
    integer_type was_unknown = 0;
    for (auto i = 0; i < get_uniq_size(); ++i) {
      LOGICAL cmp = get_constant_uniq_element(i).is_equal(rhs, compare_value);
      if (cmp.is_true()) {
        found = get_uniq_count(i);
        break;
      }
      else if (cmp.is_unknown()) {
        was_unknown = -1;
      }
    }
    return found ? found : was_unknown;
  }

  /**
   * \file
   * * \copybrief express::AGGREGATE_GENERIC::is_unique(const express::GENERIC&) const
   */
  bool AGGREGATE_GENERIC::is_unique(const GENERIC& rhs) const {
    if (!determinated || !rhs.is_determinated()) {
      return true;
    }

    return check_same_element(rhs, false) <= 0;
  }

  /**
   * \file
   * * \copybrief express::AGGREGATE_GENERIC::is_equal(const express::GENERIC&, bool) const
   */
  LOGICAL AGGREGATE_GENERIC::is_equal(const GENERIC& rhs, bool compare_value) const {

#ifdef TRACE_AGGREGATE
    printf("%s: %s compare with %s\n", __MYFUNCNAME__, print_value().c_str(), rhs.print_value().c_str());
#endif

    /**
     * Алгоритм:
     * 
     * 1. Если this и rhs --- это массивы, то использовать функцию сравнения массива с массивом.
     */
    if ((objtype() && OBJTYPE::OBJ_ARRAY) && (rhs.objtype() && OBJTYPE::OBJ_ARRAY)) {
      return dynamic_cast<const ARRAY_GENERIC&>(*this).is_array_equal(dynamic_cast<const ARRAY_GENERIC&>(rhs), compare_value);
    }
#if 0
    /**
     * 2. Если this и rhs --- это списки, то использовать функцию сравнения списка со списком.
     */
    if ((objtype() && OBJTYPE::OBJ_LIST) && (rhs.objtype() && OBJTYPE::OBJ_LIST)) {
      return dynamic_cast<const LIST_GENERIC&>(*this).is_list_equal(dynamic_cast<const LIST_GENERIC&>(rhs), compare_value);
    }
    /**
     * 3. Если this и rhs --- это множества, то использовать функцию сравнения множества с множеством.
     */
    if ((objtype() && OBJTYPE::OBJ_BAG) && (rhs.objtype() && OBJTYPE::OBJ_BAG)) {
      return dynamic_cast<const BAG_GENERIC&>(*this).is_bag_equal(dynamic_cast<const BAG_GENERIC&>(rhs), compare_value);
    }
    /**
     * 4. Если this и rhs --- это наборы, то использовать функцию сравнения набора с набором.
     */
    if ((objtype() && OBJTYPE::OBJ_SET) && (rhs.objtype() && OBJTYPE::OBJ_SET)) {
      return dynamic_cast<const SET_GENERIC&>(*this).is_set_equal(dynamic_cast<const SET_GENERIC&>(rhs), compare_value);
    }
    /**
     * 5. Если this --- это множество, а rhs --- это набор, то использовать функцию сравнения множества с набором.
     */
    if ((objtype() && OBJTYPE::OBJ_BAG) && (rhs.objtype() && OBJTYPE::OBJ_SET)) {
      return dynamic_cast<const BAG_GENERIC&>(*this).is_set_equal(dynamic_cast<const SET_GENERIC&>(rhs), compare_value);
    }
    /**
     * 5. Если this --- это набор, а rhs --- это множество, то использовать функцию сравнения множества с набором.
     */
    if ((objtype() && OBJTYPE::OBJ_SET) && (rhs.objtype() && OBJTYPE::OBJ_BAG)) {
      return dynamic_cast<const BAG_GENERIC&>(rhs).is_set_equal(dynamic_cast<const SET_GENERIC&>(*this), compare_value);
    }
#endif
    /**
     * 6. Если это ещё какая-то комбинация агрегатных типов, то вызвать исключение.
     */
    throw exception{ __MYFUNCNAME__, "rhs (%s) must be compatible to 'this' (%s)", rhs.get_type_name().c_str(), get_type_name().c_str() };
  }

  /**
   * \file
   * * \copybrief express::AGGREGATE_GENERIC::check_compatibility(const express::GENERIC&) const
   */
  GENERIC::COMPAT AGGREGATE_GENERIC::check_compatibility(const GENERIC& rhs) const {

    /* оба типа данных являются типами данных ARRAY с совместимыми базисными типами данных и одинаковыми границами */
    if (((objtype() && OBJTYPE::OBJ_ARRAY) && (rhs.objtype() && OBJTYPE::OBJ_ARRAY)) &&
       ((dynamic_cast<const ARRAY_GENERIC&>(*this).get_loindex() == dynamic_cast<const ARRAY_GENERIC&>(rhs).get_loindex() &&
         dynamic_cast<const ARRAY_GENERIC&>(*this).get_hiindex() == dynamic_cast<const ARRAY_GENERIC&>(rhs).get_hiindex()))) {
        return dynamic_cast<const ARRAY_GENERIC&>(*this).get_undef().check_compatibility(dynamic_cast<const ARRAY_GENERIC&>(rhs).get_undef());
     }
#if 0
    /* оба типа данных являются типами данных LIST с совместимыми базисными типами данных */
    if ((objtype() && OBJTYPE::OBJ_LIST) && (rhs.objtype() && OBJTYPE::OBJ_LIST)) {
      return dynamic_cast<const LIST_GENERIC&>(*this).get_undef().check_compatibility(dynamic_cast<const LIST_GENERIC&>(rhs).get_undef());
    }

    /* оба типа данных являются типами данных BAG или SET с совместимыми базисными типами данных */
    if ((objtype() && OBJTYPE::OBJ_BAG) && (rhs.objtype() && OBJTYPE::OBJ_BAG)) {
      return dynamic_cast<const BAG_GENERIC&>(*this).get_undef().check_compatibility(dynamic_cast<const BAG_GENERIC&>(rhs).get_undef());
    }
    if ((objtype() && OBJTYPE::OBJ_BAG) && (rhs.objtype() && OBJTYPE::OBJ_SET)) {
      return dynamic_cast<const BAG_GENERIC&>(*this).get_undef().check_compatibility(dynamic_cast<const SET_GENERIC&>(rhs).get_undef());
    }
    if ((objtype() && OBJTYPE::OBJ_SET) && (rhs.objtype() && OBJTYPE::OBJ_SET)) {
      return dynamic_cast<const SET_GENERIC&>(*this).get_undef().check_compatibility(dynamic_cast<const SET_GENERIC&>(rhs).get_undef());
    }
    if ((objtype() && OBJTYPE::OBJ_SET) && (rhs.objtype() && OBJTYPE::OBJ_BAG)) {
      return dynamic_cast<const SET_GENERIC&>(*this).get_undef().check_compatibility(dynamic_cast<const BAG_GENERIC&>(rhs).get_undef());
    }
#endif
    return COMPAT::COMPAT_NONE;
  }

  /**
   * \file
   * * \copybrief express::AGGREGATE_GENERIC::AGGREGATE_GENERIC()
   */
  AGGREGATE_GENERIC::AGGREGATE_GENERIC() :
    GENERIC(false), bound_1(0), bound_2(INTEGER()), optional(false), uniq(false), ordered(false) {
    GENERIC::append_to_parent_type_list();

#ifdef TRACE_AGGREGATE
      printf("%s: determinated=%s, bound_1=%s, bound_2=%s, ordered=%s, optional=%s, uniq=%s\n",
       __MYFUNCNAME__, determinated ? "yes" : "no", bound_1.print_value().c_str(), bound_2.print_value().c_str(),
       ordered ? "yes" : "no", optional ? "yes" : "no", uniq ? "yes" : "no");
#endif

  }

  /**
   * \file
   * * \copybrief express::AGGREGATE_GENERIC::AGGREGATE_GENERIC(const express::INTEGER&, const express::INTEGER&)
   */
  AGGREGATE_GENERIC::AGGREGATE_GENERIC(const INTEGER& Bound_1, const INTEGER& Bound_2) :
    GENERIC(false), bound_1(Bound_1), bound_2(Bound_2), optional(false), uniq(false), ordered(false) {
    GENERIC::append_to_parent_type_list();

#ifdef TRACE_AGGREGATE
      printf("%s: determinated=%s, bound_1=%s, bound_2=%s, ordered=%s, optional=%s, uniq=%s\n",
       __MYFUNCNAME__, determinated ? "yes" : "no", bound_1.print_value().c_str(), bound_2.print_value().c_str(),
       ordered ? "yes" : "no", optional ? "yes" : "no", uniq ? "yes" : "no");
#endif
  }

  /**
   * \file
   * * \copybrief express::AGGREGATE_GENERIC::operator[](const express::INTEGER&) const
   */
  const GENERIC& AGGREGATE_GENERIC::operator[](const INTEGER& index) const {

#ifdef TRACE_ARRAY
    printf("%s: (index = %s)\n", __MYFUNCNAME__, index.print_value().c_str());
#endif

    /**
     * Алгоритм получения элемента совокупности по значению индекса:
     *
     * 1. Если совокупность имеет неопределённое (?) значение, то результатом также
     * будет неопределённое (?) значение.
     */
    if (!determinated || !index.is_determinated()) {
      return get_undef();
    }

    /**
     * 2. Если индекс лежит вне пределов списка, вернуть неопределённое (?) значение.
     */
    if (index.get_integer_value() < get_loindex() ||
        index.get_integer_value() > get_hiindex()) {
      return get_undef();
    }

    /**
     *  3. Вернуть элемент по значению индекса.
     */
    return get_constant_internal_element(index.get_integer_value() - get_loindex());
  }

  /**
   * \file
   * * \copybrief express::AGGREGATE_GENERIC::operator[](const express::INTEGER&)
   */
  GENERIC& AGGREGATE_GENERIC::operator[](const INTEGER& index) {


#ifdef TRACE_ARRAY
    printf("%s: (index = %s)\n", __MYFUNCNAME__, index.print_value().c_str());
#endif

    /**
     * Алгоритм уточнения элементом совокупности:
     *
     * 1. Если совокупность имеет неопределённое (?) значение, вызвать исключение.
     */
    if (!determinated) {
      throw exception{ __MYFUNCNAME__, "AGGREGATE_GENERIC (index qualified) can not be indeterminated" };
    }
    /**
     * 2. Если совокупность не является упорядоченной (массив ARRAY, список LIST), вызвать исключение.
     */
    if (!ordered) {
      throw exception{ __MYFUNCNAME__, "Element of AGGREGATE_GENERIC type '%s' defined as Not ORDERED can not be assigned by the index qualifier", get_type_name().c_str() };
    }
    /**
     * 3. Если index имеет неопределённое (?) значение, вызвать исключение.
     */
    if (!index.is_determinated()) {
      throw exception{ __MYFUNCNAME__, "Index can not be indeterminated" };
    }

    /**
     * 4. Если индекс лежит вне пределов совокупности, вызвать исключение.
     */
    if (index.get_integer_value() < get_loindex() ||
        index.get_integer_value() > get_hiindex()) {
      throw exception{ __MYFUNCNAME__, "Index = %lli can not be out of borders (from %lli to %lli)",
        index.get_integer_value(), get_loindex(), get_hiindex() };
    }

    /** 5. Вернуть элемент по значению индекса. */
    return get_internal_element(index.get_integer_value() - get_loindex());
  }


  /**
   * \file
   * * \copybrief express::AGGREGATE_GENERIC::set_element(const express::INTEGER&, const express::GENERIC&)
   */
  void AGGREGATE_GENERIC::set_element(const INTEGER& index, const GENERIC& element) {

    /**
     * Алгоритм уточнения элементом совокупности с проверкой:
     *
     * 1. Проверить возможность присвоения неопределённого элемента.
     */
    if (!optional && !element.is_determinated()) {
      throw exception{ __MYFUNCNAME__, "Undeterminated element '%s' may not be assigned to AGGREGATE_GENERIC type '%s' defined as Not OPTIONAL",
        element.get_type_name().c_str(), get_type_name().c_str()};
    }
    /**
     * 2. Проверить возможность присвоения неуникального элемента.
     */
    if (uniq && !is_unique(element)) {
      throw exception{ __MYFUNCNAME__, "Not unique element '%s' may not be assigned to AGGREGATE_GENERIC type '%s' defined as UNIQUE",
        element.get_type_name().c_str(), get_type_name().c_str()};
    }
    operator[](index) = element;
  }


  /**
   * \file
   * * \copybrief express::AGGREGATE_GENERIC::print_value() const
   */
  std::string AGGREGATE_GENERIC::print_value() const {

#if defined(TRACE_NUMBER) || defined(TRACE_REAL) || defined(TRACE_INTEGER) || \
    defined(TRACE_LOGICAL) || defined(TRACE_BOOLEAN) || defined(TRACE_STRING) || defined(TRACE_BINARY) || \
    defined(TRACE_AGGREGATE) || defined(TRACE_ARRAY) || defined(TRACE_LIST)  || defined(TRACE_SET) 
    if (!determinated) {
      return std::string("INDETERMINATED");
    }
#else
    throw exception{__MYFUNCNAME__, "value may not be indeterminate (?)"};
#endif

    std::stringstream s;
    s << "(";
    for (integer_type i = 0; i < get_elements_size(); ++i) {
      const GENERIC& g = get_constant_internal_element(i);
      if (!g.is_determinated()) {
        if (!optional) {
          throw exception{__MYFUNCNAME__, "element #%i shall not be indetrminated in AGGREGATE_GENERIC defined as Not OPTIONAL", i};
        }
        s << "$";
      } else {
        s << g.print_value();
      }
      if (i != get_elements_size() - 1) {
        s << STEP_SPACER;
      }
    }
    s << ")";
    return s.str();
  }

  /**
   * \file
   * * \copybrief express::AGGREGATE_GENERIC::print_value() const
   */
  const std::string AGGREGATE_GENERIC::get_value_type_name() const {
    return get_undef().get_type_name();
  }

  /**
   * \file
   * Функции класса ARRAY:
   */

  /**
   * \file
   * * \copybrief express::integer_type express::ARRAY_GENERIC::get_loindex() const
   */
  integer_type ARRAY_GENERIC::get_loindex() const {
    return bound_1.get_integer_value();
  }

  /**
   * \file
   * * \copybrief express::integer_type express::ARRAY_GENERIC::get_hiindex() const
   */
  integer_type ARRAY_GENERIC::get_hiindex() const {
    return bound_2.get_integer_value();
  }

  /**
   * \file
   * * \copybrief express::ARRAY_GENERIC::OBJTYPE objtype() const
   */
  GENERIC::OBJTYPE ARRAY_GENERIC::objtype() const {
    return OBJTYPE::OBJ_AGGREGATE | OBJTYPE::OBJ_ARRAY;
  }

  /**
   * \file
   * * \copybrief express::ARRAY_GENERIC::is_array_equal(const express::ARRAY_GENERIC&, bool) const
   */
  LOGICAL ARRAY_GENERIC::is_array_equal(const ARRAY_GENERIC& rhs, bool compare_value) const {

#ifdef TRACE_ARRAY
    printf("%s: %s compare with %s\n", __MYFUNCNAME__, print_value().c_str(), rhs.print_value().c_str());
#endif

    /**
     * Алгоритм:
     *
     * 1. Если какой-либо из операндов имеет неопределенное (?) значение, то результат будет иметь
     * значение UNKNOWN.
     */
    if (!determinated || !rhs.is_determinated()) {
      return UNKNOWN;
    }

    /**
     * 2. Если начальный и конечный индексы массивов не совпадают, то результат будет иметь значение FALSE.
     */
    if (bound_1.get_integer_value() != rhs.bound_1.get_integer_value() || bound_2.get_integer_value() != rhs.bound_2.get_integer_value()) {
      return FALSE;
    }
    /**
     * 3. Два массива а и b равны тогда и только тогда, когда значение каждого элемента из а
     * равно значению элемента из b, расположенного в той же позиции, то есть a[i] = b[i].
     */

     /** Поэтому сравниваем все элементы подряд: */
    bool was_unknown = false;
    for (auto i = 0; i < rhs.get_uniq_size(); ++i) {
      LOGICAL cmp = get_constant_uniq_element(i).is_equal(rhs.get_constant_uniq_element(i), compare_value);
      /**
       * * Если результат хотя бы одного сравнения равен FALSE, то результат будет иметь
       * значение FALSE.
       */
      if (cmp.is_false()) {
        return FALSE;
      }
      if (cmp.is_unknown()) {
        was_unknown = true;
      }
    }
    /**
     * * Если результатом одного или нескольких сравнений элементов при сравнении массивов является UNKNOWN,
     * а результатом остальных сравнений является TRUE, то результатом сравнения массивов является UNKNOWN.
     */
    if (was_unknown) return UNKNOWN;

    /**
     * * Во всех других случаях результатом сравнения массивов является TRUE.
     */
    return TRUE;
  }

  /**
   * \file
   * * \copybrief express::ARRAY_GENERIC::ARRAY_GENERIC()
   */
  ARRAY_GENERIC::ARRAY_GENERIC() {
    GENERIC::append_to_parent_type_list();

    ordered = true;

#ifdef TRACE_ARRAY
      printf("%s: determinated=%s, bound_1=%s, bound_2=%s, ordered=%s, optional=%s, uniq=%s\n",
       __MYFUNCNAME__, determinated ? "yes" : "no", bound_1.print_value().c_str(), bound_2.print_value().c_str(),
       ordered ? "yes" : "no", optional ? "yes" : "no", uniq ? "yes" : "no");
#endif

  }

  /**
   * \file
   * * \copybrief express::ARRAY_GENERIC::ARRAY_GENERIC(const express::INTEGER& Bound_1, const express::INTEGER& Bound_2, unsigned Options)
   */
  ARRAY_GENERIC::ARRAY_GENERIC(const INTEGER& Bound_1, const INTEGER& Bound_2, unsigned Options) {
    GENERIC::append_to_parent_type_list();

    if (!Bound_1.is_determinated()) {
      throw exception{__MYFUNCNAME__, "bound_1 may not be indeterminate (?)"};
    }
    if (!Bound_2.is_determinated()) {
      throw exception{__MYFUNCNAME__, "bound_2 may not be indeterminate (?)"};
    }
    if (Bound_1.get_integer_value() > Bound_2.get_integer_value()) {
      throw exception{ __MYFUNCNAME__, "bound_1 shall be less than or equal to bound_2" };
    }

    bound_1 = Bound_1;
    bound_2 = Bound_2;
    if (Options & UNIQUE) uniq = true;
    if (Options & OPTIONAL) optional = true;
    ordered = true;

#ifdef TRACE_ARRAY
      printf("%s: determinated=%s, bound_1=%s, bound_2=%s, ordered=%s, optional=%s, uniq=%s\n",
       __MYFUNCNAME__, determinated ? "yes" : "no", bound_1.print_value().c_str(), bound_2.print_value().c_str(),
       ordered ? "yes" : "no", optional ? "yes" : "no", uniq ? "yes" : "no");
#endif
  }


  ARRAY_GENERIC& ARRAY_GENERIC::operator=(std::initializer_list<const GENERIC> Elements) {

#ifdef TRACE_ARRAY
      printf("Assign list '%s'(%lli, %lli)\n", __MYFUNCNAME__, bound_1.get_integer_value(), bound_2.get_integer_value());
#endif

      if (static_cast<integer_type>(Elements.size()) > bound_2.get_integer_value() - bound_1.get_integer_value() + 1) {
        throw exception{__MYFUNCNAME__, "initializer_list size %u shall not be greater than ARRAY size %lli", Elements.size(), bound_2.get_integer_value() - bound_1.get_integer_value() + 1};
      }

      if (!optional && static_cast<integer_type>(Elements.size()) < bound_2.get_integer_value() - bound_1.get_integer_value() + 1) {
        throw exception{__MYFUNCNAME__, "initializer_list shall have same size (%u) as ARRAY (size %lli) defined as Not OPTIONAL", Elements.size(), bound_2.get_integer_value() - bound_1.get_integer_value() + 1};
      }

      determinated = true;
      clear();

      /* Скопировать список инициализации в массив */
      for (auto& i : Elements) {

#ifdef TRACE_ARRAY
          printf("Assigning element %lli '%s'\n", size, i.print_value().c_str());
#endif

        if (!optional && !i.is_determinated()) {
          throw exception{__MYFUNCNAME__, "initializer_list element #%lli shall not be indetrminated in ARRAY defined as Not OPTIONAL", size};
        }
        if (uniq && !is_unique(i)) {
          throw exception{__MYFUNCNAME__, "initializer_list element #%lli shall be unique in ARRAY defined as Not UNIQUE", size};
        }
        add_element(i);
      }

      if (optional) {
        /* При необходимости дополнить массив неопределёнными элементами */
        for (auto i = get_uniq_size(); i < static_cast<size_t>(bound_2.get_integer_value() - bound_1.get_integer_value() + 1); ++i) {

#ifdef TRACE_ARRAY
          printf("Assigning undefined element %lli\n", AGGREGATE<T>::size);
#endif
        add_element(get_undef());
      }
    }
    return *this;
  }

  /**
   * \file
   * * \copybrief express::ARRAY_GENERIC::operator=(const express::ARRAY_GENERIC&)
   */
  ARRAY_GENERIC& ARRAY_GENERIC::operator=(const ARRAY_GENERIC& rhs) {

#ifdef TRACE_ARRAY
      printf("%s(%lli, %lli) := %s\n", __MYFUNCNAME__, bound_1.get_integer_value(), bound_2.get_integer_value(), rhs.get_type_name().c_str());
#endif

      /* Выполнить проверки */
      if (!rhs.is_determinated()) {
        determinated = false;
        clear();
        return *this;
      }
      if (rhs.get_elements_size() > bound_2.get_integer_value() - bound_1.get_integer_value() + 1) {
        throw exception{__MYFUNCNAME__, "rhs shall not be greater than ARRAY size"};
      }
      if (!optional && rhs.get_elements_size() < bound_2.get_integer_value() - bound_1.get_integer_value() + 1) {
        throw exception{__MYFUNCNAME__, "rhs shall have same size as ARRAY defined as Not OPTIONAL"};
      }

      /* Скопировать элементы */
      determinated = true;
      clear();
      for (auto n = rhs.get_loindex(); n <= rhs.get_hiindex(); ++n) {
        const GENERIC& t = rhs[n];
        if (!optional && !t.is_determinated()) {
          throw exception{__MYFUNCNAME__, "rhs element #%i shall not be indetrminated in ARRAY defined as Not OPTIONAL", n};
        }
        if (uniq && !is_unique(t)) {
          throw exception{__MYFUNCNAME__, "rhs element #%i shall be unique in ARRAY defined as Not UNIQUE", n};
        }
        add_element(t);
      }
      return *this;
    }



  /**
   * \file
   * Функции класса LIST:
   */

#if 0

  /**
   * \file
   * * \copybrief express::LIST_GENERIC::get_loindex() const
   */
  integer_type LIST_GENERIC::get_loindex() const {
    return 1;
  }

  /**
   * \file
   * * \copybrief express::LIST_GENERIC::get_hiindex() const
   */
  integer_type LIST_GENERIC::get_hiindex() const {
    return get_elements_size();
  }

  /**
   * \file
   * * \copybrief express::LIST_GENERIC::objtype() const
   */
  GENERIC::OBJTYPE LIST_GENERIC::objtype() const {
    return OBJTYPE::OBJ_AGGREGATE | OBJTYPE::OBJ_LIST;
  }

  /**
   * \file
   * * \copybrief express::LIST_GENERIC::is_list_equal(const express::LIST_GENERIC&, bool) const
   */
  LOGICAL LIST_GENERIC::is_list_equal(const LIST_GENERIC& rhs, bool compare_value) const {
  /**
   * Алгоритм:
   *
     * 1. Если какой-либо из операндов имеет неопределенное (?) значение, то результат будет иметь
     * значение UNKNOWN.
     */
    if (!determinated || !rhs.determinated) {
      return UNKNOWN;
    }

    /**
     * 2. Если размеры списков не совпадают, то результат будет иметь значение FALSE.
     */
    if (static_cast<integer_type>(get_elements_size()) != rhs.get_elements_size()) {
      return FALSE;
    }

    /* Сравнить элементы */
    bool was_unknown = false;
    for (integer_type n = rhs.get_loindex(); n <= rhs.get_hiindex(); ++n) {
      LOGICAL cmp = compare_value ? (*this)[n].is_value_equal(rhs[n]) : (*this)[n].is_instance_equal(rhs[n]);
      /**
       * Если результат хотя бы одного сравнения равен FALSE, то результат будет иметь значение FALSE.
       */
      if (cmp.is_false()) {
        return FALSE;
      }
      if (cmp.is_unknown()) {
        was_unknown = true;
      }
    }
    /**
     * Если результатом одного или нескольких сравнений элементов при сравнении списков является UNKNOWN,
     * а результатом остальных сравнений является TRUE, то результатом сравнения списков является UNKNOWN.
     */
    if (was_unknown) return UNKNOWN;

    /**
     * Во всех других случаях результатом сравнения списков является TRUE.
     */
    return TRUE;
  }

  /**
   * \file
   * * \copybrief express::LIST_GENERIC::LIST_GENERIC(const express::INTEGER&, const express::INTEGER&, unsigned)
   */
  LIST_GENERIC::LIST_GENERIC(const INTEGER& Bound_1, const INTEGER& Bound_2, unsigned Options) :
    AGGREGATE_GENERIC(Bound_1, Bound_2) {

#ifdef TRACE_AGGREGATE
printf("Construct '%s' (", __MYFUNCNAME__);
if (bound_1.is_determinated()) printf("%lli ", bound_1.get_integer_value()); else printf("? ");
if (bound_2.is_determinated()) printf("%lli ", bound_2.get_integer_value()); else printf("? ");
printf(")\n");
#endif

    append_to_parent_type_list();
    if (!Bound_1.is_determinated()) {
      throw exception{__MYFUNCNAME__, "lower bound shall not evaluate to the indeterminate (?) value"};
    }
    if ((Bound_1 < 0).is_true()) {
      throw exception{__MYFUNCNAME__, "lower bound must be greater of equal to 0"};
    }
    if (Bound_2.is_determinated() && (Bound_1 > Bound_2).is_true()) {
      throw exception{__MYFUNCNAME__, "lower bound shall be less than or equal to upper bound"};
    }
    ordered = true;
    if (Options & UNIQUE) uniq = true;
  }

  /**
   * \file
   * Функции класса BAG:
   */

  /**
   * \file
   * * \copybrief express::BAG_GENERIC::get_loindex() const
   */
  integer_type BAG_GENERIC::get_loindex() const {
    return 1;
  }

  /**
   * \brief Получить верхний индекс \ref express::BAG_GENERIC "множества BAG"
   * \return значение верхнего индекса \ref express::BAG_GENERIC "множества BAG".
   *
   * Если типом данных является \ref express::BAG_GENERIC "множество BAG", верхний индекс
   * равен числу элементов \ref express::BAG_GENERIC "множества BAG".
   */
  integer_type BAG_GENERIC::get_hiindex() const {
    return get_elements_size();
  }

  /**
   * \brief Получить тип данных множества
   * \return тип данных множества в виде элемента перечисления OBJTYPE.
   */
  GENERIC::OBJTYPE BAG_GENERIC::objtype() const {
    return OBJTYPE::OBJ_AGGREGATE | OBJTYPE::OBJ_BAG;
  }

  LOGICAL BAG_GENERIC::is_bag_equal(const BAG_GENERIC& rhs, bool compare_value) const {
    /**
     * Алгоритм:
     *
     * 1. Если какой-либо из операндов имеет неопределенное (?) значение, то результат будет иметь
     * значение UNKNOWN.
     */
    if (!determinated || !rhs.is_determinated()) {
      return UNKNOWN;
    }

    /**
     * 2. Если множество rhs на самом деле является набором, использовать существующую функцию.
     */
    if (rhs.objtype() && OBJTYPE::OBJ_SET) {
      return is_set_equal(dynamic_cast<const SET_GENERIC&>(rhs), compare_value);
    }

    /**
     * 3. Если размеры множеств или количества уникальных элементов не совпадают, то результат
     * будет иметь значение FALSE.
     */
    if (get_uniq_size() != rhs.get_uniq_size() || get_elements_size() != rhs.get_elements_size()) {
      return FALSE;
    }

    /**
     * 4. Два множества а и b равны тогда и только тогда, когда каждый элемент VALUE_IN а
     * встречается в VALUE_IN b равное число раз, а каждый элемент VALUE_IN b также встречается
     * в VALUE_IN а равное число раз. Так что учитывая предыдущую проверку, достаточно убедиться,
     * что в нашем множестве есть столько же групп таких же уникальных элементов, что и в
     * множестве rhs.
     */

     /** Поэтому сравниваем уникальные элементы: */
    bool was_unknown = false;
    for (integer_type i = 0; i < rhs.get_uniq_size(); ++i) {


      auto res = check_same_element(rhs.get_uniq_element(i), compare_value);
      /**
       * * Если в нашем множестве нет i-го элемента из множества rhs, результат FALSE.
       */
      if (res == 0) {
        return FALSE;
      }
      /**
       * * Если результат сравнения неизестен, запомнить это и сравнивать дальше.
       */
      else if (res < 0) {
        was_unknown = true;
      }
      /**
       * * Если в нашем множестве есть i-й элемент из множества rhs, но не в таком же количестве, результат FALSE.
       */
      else {
        if (rhs.get_uniq_count(i) != res) {
          return FALSE;
        }
      }
    }
    /**
     * 5. Если результатом одного или нескольких сравнений элементов при сравнении списков является UNKNOWN,
     * а результатом остальных не был FALSE, то результатом сравнения списков является UNKNOWN.
     */
    if (was_unknown) return UNKNOWN;
    /**
     * 6. Во всех других случаях результатом сравнения списков является TRUE.
     */
    return TRUE;
  }

  LOGICAL BAG_GENERIC::is_set_equal(const SET_GENERIC& rhs, bool compare_value) const {
    /**
     * Алгоритм:
     *
     * 1. Если какой-либо из операндов имеет неопределенное (?) значение, то результат будет иметь
     * значение UNKNOWN.
     */
    if (!determinated || !rhs.is_determinated()) {
      return UNKNOWN;
    }

    /**
     * 2. Если множество содержит неуникальные элементы или размеры множества и набора не совпадают, то результат
     * будет иметь значение FALSE.
     */
    if (get_elements_size() != get_uniq_size() || get_elements_size() != rhs.get_elements_size()) {
      return FALSE;
    }

    /**
     * 3. Множество и набор а и b равны тогда и только тогда, когда каждый элемент VALUE_IN а
     * имеется в VALUE_IN b, а каждый элемент VALUE_IN b также имеется в VALUE_IN. Так что
     * учитывая предыдущую проверку, достаточно убедиться, что в множестве есть каждый элемент
     * из набора.
     */

     /* Поэтому перебираем элементы набора: */
    bool was_unknown = false;
    for (integer_type i = 0; i < rhs.get_elements_size(); ++i) {
      auto res = check_same_element(rhs[i], compare_value);
      /**
       * * Если в множестве нет i-го элемента набора, результат FALSE.
       */
      if (res < 0) {
        return FALSE;
      }
      /**
       * * Если результат сравнения неизестен, запомнить это и сравнивать дальше.
       */
      else if (res == 0) {
        was_unknown = true;
      }
      /* * Если в множестве есть i-й элемент набора, продолжаем сравнение. */
    }
    /**
     * 4. Если результатом одного или нескольких сравнений элементов при сравнении списков является UNKNOWN,
     * а результатом остальных не был FALSE, то результатом сравнения списков является UNKNOWN.
     */
    if (was_unknown) return UNKNOWN;
    /**
     * 5. Во всех других случаях результатом сравнения списков является TRUE.
     */
    return TRUE;
  }

  /**
   * \brief Конструктор \ref express::BAG_GENERIC "множества BAG", имеющего неопределённое (<B>?</B>) значение
   * \param [in] Bound_1 минимальное число элементов, которое может содержаться в \ref express::BAG_GENERIC "множестве BAG".
   * По умолчанию ноль.
   * \param [in] Bound_2 максимальное число элементов, которое может содержаться в \ref express::BAG_GENERIC "множестве BAG".
   * По умолчанию имеет неопределённое значение.
   */
  BAG_GENERIC::BAG_GENERIC(const INTEGER& Bound_1, const INTEGER& Bound_2) : AGGREGATE_GENERIC(Bound_1, Bound_2) {

#ifdef TRACE_AGGREGATE
    printf("%s\n", __MYFUNCNAME__);
#endif

    GENERIC::append_to_parent_type_list();
    if (!Bound_1.is_determinated()) {
      throw exception{ __MYFUNCNAME__, "lower bound shall not evaluate to the indeterminate (?) value" };
    }
    if (Bound_1.get_integer_value() < 0) {
      throw exception{ __MYFUNCNAME__, "lower bound must be greater of equal to 0" };
    }
    if (Bound_2.is_determinated() && Bound_1.get_integer_value() > Bound_2.get_integer_value()) {
      throw exception{ __MYFUNCNAME__, "lower bound shall be less than or equal to upper bound" };
    }
  }


  /**
   * \file
   * Функции класса SET:
   */

  GENERIC::OBJTYPE SET_GENERIC::objtype() const {
    return OBJTYPE::OBJ_AGGREGATE | OBJTYPE::OBJ_SET;
  }

  SET_GENERIC::SET_GENERIC(const INTEGER& Bound_1, const INTEGER& Bound_2) : BAG_GENERIC(Bound_1, Bound_2) {
    append_to_parent_type_list();
    uniq = true;
  }
#endif
}