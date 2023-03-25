/**
 * \file
 *
 * \brief Файл с определениями функций класса GENERIC, соответствующих ГОСТ Р ИСО 10303-11-2009, п.9.5.3.2
 *
 * Здесь определены функции, реализующие функции-члены класса GENERIC, соответствующему обобщённому
 * типу данных языка EXPRESS.
 */

#include "stdafx.h"
#include "express.h"

namespace express {

  /* Преобразовать тип данных в строку */
  std::string GENERIC::objtype_to_string(OBJTYPE t) {
    if (t && OBJTYPE::OBJ_GENERIC)        return "GENERIC";
    if (t && OBJTYPE::OBJ_SIMPLE)         return "SIMPLE";
    if (t && OBJTYPE::OBJ_AGGREGATE)      return "AGGREGATE";
    if (t && OBJTYPE::OBJ_ENTITY)         return "ENTITY";
    if (t && OBJTYPE::OBJ_ENTITY_COMPLEX) return "ENTITY_COMPLEX";
    if (t && OBJTYPE::OBJ_DEFINED)        return "DEFINED";
    if (t && OBJTYPE::OBJ_ENUMERATION)    return "ENUMERATION";
    if (t && OBJTYPE::OBJ_SELECT)         return "SELECT";
    return "";
  }


  /**
   * \file
   * * \copybrief express::GENERIC::is_number() const
   */
  bool GENERIC::is_number() const {
    return objtype() && OBJTYPE::OBJ_NUMBER;
  }

  /**
   * \file
   * * \copybrief express::GENERIC::is_real() const
   */
  bool GENERIC::is_real() const {
    return objtype() && OBJTYPE::OBJ_REAL;
  }

  /**
   * \file
   * * \copybrief express::GENERIC::is_integer() const
   */
  bool GENERIC::is_integer() const {
    return objtype() && OBJTYPE::OBJ_INTEGER;
  }

  /**
   * \file
   * * \copybrief express::GENERIC::is_logical() const
   */
  bool GENERIC::is_logical() const {
    return objtype() && OBJTYPE::OBJ_LOGICAL;
  }

  /**
   * \file
   * * \copybrief express::GENERIC::is_boolean() const
   */
  bool GENERIC::is_boolean() const {
    return objtype() && OBJTYPE::OBJ_BOOLEAN;
  }

  /**
   * \file
   * * \copybrief express::GENERIC::is_binary() const
   */
  bool GENERIC::is_binary() const {
    return objtype() && OBJTYPE::OBJ_BINARY;
  }

  /**
   * \file
   * * \copybrief express::GENERIC::is_string() const
   */
  bool GENERIC::is_string() const {
    return objtype() && OBJTYPE::OBJ_STRING;
  }



  /* Добавить имя типа в список родительских типов */
  void GENERIC::append_to_parent_type_list(const char* override) {
    if (override != nullptr) {
      parent_type_list.push_back(override);
      return;
    }

    std::string new_name = get_type_name();

    /* Удалить из имени префиксы "express::", "class " */
    std::string toErase1("express::");
    for (;;) {
      size_t pos = new_name.find(toErase1);
      if (pos == std::string::npos) break;
      new_name.erase(pos, toErase1.length());
    }
    std::string toErase2("class ");
    for (;;) {
      size_t pos = new_name.find(toErase2);
      if (pos == std::string::npos) break;
      new_name.erase(pos, toErase2.length());
    }

    if (new_name == "BAG_GENERIC") new_name = "BAG<GENERIC>";
    else if (new_name == "SET_GENERIC") new_name = "SET<GENERIC>";
    else if (new_name == "LIST_GENERIC") new_name = "LIST<GENERIC>";
    else if (new_name == "ARRAY_GENERIC") new_name = "ARRAY<GENERIC>";

    /* Пропустить уже имеющееся имя */
    for (auto i = parent_type_list.cbegin(); i != parent_type_list.cend(); ++i) {
      if (*i == new_name) return;
    }
    parent_type_list.push_back(new_name);
  }

  /* Конструктор обобщённого типа, имеющего определённое или неопределённое (?) значение */
  GENERIC::GENERIC(bool Determinated) : determinated(Determinated) {
    append_to_parent_type_list();
  }

  bool GENERIC::is_determinated() const {
    return determinated;
  }


  /* Отладочный вывод списка родительских типов */
  std::string GENERIC::debug_print_type_list() const {
    std::stringstream s;

    for (auto i = parent_type_list.cbegin(); i != parent_type_list.cend(); ++i) {
      s << (*i).c_str();
      if (i != parent_type_list.cend() - 1) s << " -> ";
    }
    return s.str();
  }

  /* Получить принадлёжность типа данных к одной из групп */
//  constexpr GENERIC::OBJTYPE GENERIC::objtype() const {
//    return OBJTYPE::OBJ_GENERIC;
//  }

  /* Получить имя типа данных в виде строки */
  std::string GENERIC::get_type_name() const {
    const char* realname = typeid(*this).name();
#if defined(__GNUC__) || defined(__DOXYGEN__)
    /* Для GCC выполнить преобразование имени класса Demangle */
    int status;
    realname = abi::__cxa_demangle(realname, 0, 0, &status);
#endif
    std::string classname = convert_name(realname);

    if (classname.compare(0, 5, "REAL<") == 0) {
      classname = "REAL";
    }

    return classname;
  }

  /* Проверить, имеет ли тип данных указанное имя */
  bool GENERIC::is_type_name(const char* Typename) const {
    return get_type_name().compare(Typename) == 0;
  }

  /* Проверить, имеет ли тип данных указанное имя у себя или у предков */
  bool GENERIC::is_parent_name(const char* Typename) const {
    for (auto i = parent_type_list.cbegin(); i != parent_type_list.cend(); ++i) {
      if (Typename == *i) return true;
    }
    return false;
  }

  /* Получить тип данных вложенного типа (для SELECT и агрегированныъх типов) */
  GENERIC::OBJTYPE GENERIC::get_value_objtype() const {
    throw exception{__MYFUNCNAME__, "pure virtual function called by class '%s'", get_type_name().c_str()};
  }

  /* Получить имя типа данных вложенного типа (для SELECT и агрегированных типов) */
  const std::string GENERIC::get_value_type_name() const {
    throw exception{__MYFUNCNAME__, "pure virtual function called by class '%s'", get_type_name().c_str()};
  }

  /**
   * \file
   * * \copybrief express::GENERIC::operator==(const express::GENERIC& rhs) const
   */
  LOGICAL GENERIC::operator==(const GENERIC& rhs) const {
    return is_equal(rhs, true);
  }

  /**
   * \file
   * * \copybrief express::GENERIC::operator!=(const express::GENERIC& rhs) const
   */
  LOGICAL GENERIC::operator!=(const GENERIC& rhs) const {
    return ! is_equal(rhs, true);
  }

  /**
   * \file
   * * \copybrief express::GENERIC::is_instance_equal(const express::GENERIC& rhs) const
   */
  LOGICAL GENERIC::is_instance_equal(const GENERIC& rhs) const {
    return is_equal(rhs, false);
  }


  /**
   * \file
   * * \copybrief express::GENERIC::print_enum_value(const char* const [], size_t, size_t) const
   */
  std::string GENERIC::print_enum_value(const char* const str[], size_t maxstr, size_t index) const {
    if (!determinated) {
#ifdef TRACE_GENERIC
      return std::string("INDETERMINATED");
#else
      throw exception{__MYFUNCNAME__, "value may not be indeterminate (?)"};
#endif
    }
    if (index >= maxstr) {
      throw exception{__MYFUNCNAME__, "index is out of bound"};
    }

    std::string s(str[index]);
    for (auto& c : s) c = static_cast<char>(toupper(c));
    return "." + s + ".";
  }


}
