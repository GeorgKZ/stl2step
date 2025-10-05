/**
 * \file
 * \brief Файл с определениями функций-членов класса \ref arg_parser "arg_parser"
 */

#include "stdafx.h"
#include "err.h"
#include "arg_parser.h"

/**
 * \file
 * Функции, являющиеся методами класса \ref arg_parser "arg_parser":
 * <BR>
 */

/**
 * \file
 * * \copybrief arg_parser::arg_parser()
 */
arg_parser::arg_parser()
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201103L) || __cplusplus >= 201103L)
      = default;
#else
      {}
#endif

/**
 * \file
 * * \copybrief arg_parser::get_flag(size_t) const
 */
const std::string& arg_parser::get_flag(size_t index) const {
  return args.at(index).flag;
}

/**
 * \file
 * * \copybrief arg_parser::get_parameters(size_t) const
 */
std::string arg_parser::get_parameters(size_t index) const {
  const std::vector<std::string>& a = args.at(index).parameters;
  std::string str_parameters;
  for (auto it = a.begin(); it != a.end(); ++it) {
    if (it != a.begin()) {
      str_parameters += " ";
    }
    str_parameters += *it;
  }
  return str_parameters;
}

/**
 * \file
 * * \copybrief arg_parser::get_parameters_set(size_t) const
 */
const std::vector<std::string>& arg_parser::get_parameters_set(size_t index) const {
  return args.at(index).parameters;
}

/**
 * \file
 * * \copybrief arg_parser::get_arg_num() const
 */
size_t arg_parser::get_arg_num() const {
  return args.size();
}

/**
 * \file
 * * \copybrief arg_parser::add_new_flag(const char*)
 */
void arg_parser::add_new_flag(const char *flag) {
  argument new_arg;
  new_arg.flag = flag;
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 202002L) || __cplusplus >= 202002L)
  if (new_arg.flag.starts_with("--")) {
#else
  if (new_arg.flag.compare(0, 2, "--") == 0) {
#endif
//  if (strlen(flag) >= 2 && flag[0] == '-' && flag[1] == '-') {
    new_arg.flag.erase(0, 2);
  }
  args.push_back(new_arg);
}

/**
 * \file
 * * \copybrief arg_parser::add_new_param(const char*)
 */
void arg_parser::add_new_param(const char *param) {

  if (args.empty()) {
    add_new_flag("");
  }
  args.back().parameters.push_back(std::string(param));
}

/**
 * \file
 * * \copybrief arg_parser::process_cmdline(const char*[], size_t)
 */
int arg_parser::process_cmdline(const char *cmdline[], size_t cmdnum) {

  /** Алгоритм: */

  /**
   * 1 Разделить аргументы по пробелам, так как в одном строковом аргументе могут оказаться
   * несколько аргументов, разделённых пробелами.
   */
  std::vector<std::string> processed_cmdline;

  for (size_t argi = 0; argi < cmdnum; argi++) {
    std::string curr_str;
    for (size_t i = 0; i < strlen(cmdline[argi]); ++i) {
      if (cmdline[argi][i] != ' ') {
        curr_str = curr_str + cmdline[argi][i];
      } else {
        if (!curr_str.empty()) {
          processed_cmdline.push_back(curr_str);
          curr_str.clear();
        }
      }
    }
    if (!curr_str.empty()) {
      processed_cmdline.push_back(curr_str);
    }
  }
  size_t processed_cmdnum = processed_cmdline.size();

  /**
   * 2 Проверить: если в командной строке нет аргументов (или есть только нулевой
   * агрумент - сама программа), то это ошибка.
   */
  if (processed_cmdnum < 2) {
    return -2;
  }

  /** 3 Проверить: если командная строка не начинается с флага, то это ошибка. */
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 202002L) || __cplusplus >= 202002L)
  if (!processed_cmdline[1].starts_with("--")) {
#else
  if (processed_cmdline[1].compare(0, 2, "--") != 0) {
#endif
  // if (processed_cmdline[1].length() < 2 || processed_cmdline[1][0] != '-' || processed_cmdline[1][1] != '-') {
    add_new_flag(processed_cmdline[1].c_str());
    return -1;
  }

  /** 4 Проверить: если командная строка начинается с пустого флага, то это ошибка. */
  if (processed_cmdline[1].length() == 2) {
    add_new_flag(processed_cmdline[1].c_str());
    return -3;
  }

  /** 5 Добавить первый флаг в список обнаруженных флагов. */
  add_new_flag(processed_cmdline[1].c_str());

  /** 6 Перебрать оставшиеся аргументы. */
  for (size_t argi = 2; argi < processed_cmdnum; argi++) {
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 202002L) || __cplusplus >= 202002L)
    if (processed_cmdline[argi].starts_with("--")) {
#else
    if (processed_cmdline[argi].compare(0, 2, "--") == 0) {
#endif
//  /** \todo Заменить на сравнение начала с "--" */
//  if (processed_cmdline[argi].length() >= 2 && processed_cmdline[argi][0] == '-' && processed_cmdline[argi][1] == '-') {
      /**
       * 6.1 Если аргументом окажется флаг, добавить его в список
       * обнаруженных флагов и продолжить перебирать аргументы.
       */
      add_new_flag(processed_cmdline[argi].c_str());
      continue;
    }
    /** 6.2 Иначе добавить аргумент как параметр текущего флага. */
    add_new_param(processed_cmdline[argi].c_str());
  }
  return 0;
}
