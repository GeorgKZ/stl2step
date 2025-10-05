/**
 * \file
 * \brief Заголовочный файл с объявлением класса \ref arg_parser "arg_parser",
 * предназначенного для разбора командной строки 
 */

#ifndef ARG_PARSER_H
#define ARG_PARSER_H

/**
 * \brief Класс, реализующий простой разбор командной строки, состоящей из конструкций
 * ("аргументов") типа флаг/параметры "--flag [param ...]"
 * \details Флаг предваряют два символа минус ('-'), так как параметром флага
 * может являться отрицательное число, также начинающееся с символа минус.
 */
class arg_parser {

  private:

  /**
   * \brief Класс, реализующий вспомогательную структуру из двух строк ---
   * флага (ключевого слова) и параметров
   */
  /**
   * \brief Класс, реализующий вспомогательную структуру из \ref arg_parser::argument::flag "флага" (ключевого слова)
   * и <a href="https://en.cppreference.com/w/cpp/container/vector.html">вектора</a> \ref arg_parser::argument::parameters "параметров"
   */
  class argument {

    public:

    /** \brief Ключевое слово для параметров в виде <a href="https://en.cppreference.com/w/cpp/string.html">строки</a> */
    std::string flag;

    /** \brief <a href="https://en.cppreference.com/w/cpp/container/vector.html">Вектор</a> параметров--<a href="https://en.cppreference.com/w/cpp/string.html">строк</a> */
    std::vector<std::string> parameters;
  };

  /** 
   * \brief <a href="https://en.cppreference.com/w/cpp/container/vector.html">Вектор</a> разобранных \ref arg_parser::argument "аргументов"
   */
  std::vector<argument> args;

  /** 
   * \brief Добавить новый \ref arg_parser::argument "аргумент", установив значение \ref arg_parser::argument::flag "флага"
   *
   * \param [in] flag <a href="https://en.cppreference.com/w/cpp/string.html">строка</a>, содержащая флаг (ключевое слово)
   */
  void add_new_flag(const char *flag);

  /** 
   * \brief Дополнить \ref arg_parser::argument::parameters "параметр" последнего \ref arg_parser::argument "аргумента"
   *
   * \param [in] param <a href="https://en.cppreference.com/w/cpp/string.html">строка</a>, содержащая параметр
   */
  void add_new_param(const char *param);

  public:

  /** 
   * \brief Конструктор по умолчанию
   */
  arg_parser();

  /** 
   * \brief Обработать командную строку
   *
   * \param[in] cmdline массив строк аргументов командной строки
   * \param[in] cmdnum количество аргументов командной строки
   * \retval -1 если первый аргумент командной строки не является флагом (ключевым словом),
   * то есть не начинается с символов '--';
   * \retval 0 в случае успешного завершения.
   */
  int process_cmdline(const char *cmdline[], size_t cmdnum);

  /** 
   * \brief Получить \ref arg_parser::argument::flag "флаг" указанного \ref arg_parser::argument "аргумента"
   *
   * \param[in] index номер (индекс) \ref argument "аргумента"
   * \return значение \ref arg_parser::argument::flag "флага" указанного \ref argument "аргумента" в виде <a href="https://en.cppreference.com/w/cpp/string.html">строки</a>
   */
  const std::string& get_flag(size_t index) const;

  /** 
   * \brief Получить \ref arg_parser::argument::parameters "параметры" указанного \ref arg_parser::argument "аргумента" в виде <a href="https://en.cppreference.com/w/cpp/string.html">строки</a>
   *
   * \param [in] index номер \ref argument "аргумента"
   * \return параметры указанного \ref argument "аргумента" в виде константной ссылки на <a href="https://en.cppreference.com/w/cpp/string.html">строку</a>.
   */
  std::string get_parameters(size_t index) const;

  /** 
   * \brief Получить набор \ref arg_parser::argument::parameters "параметров" указанного \ref arg_parser::argument "аргумента" в виде <a href="https://en.cppreference.com/w/cpp/container/vector.html">вектора</a> <a href="https://en.cppreference.com/w/cpp/string.html">строк</a>
   *
   * \param [in] index номер (индекс) аргумента
   * \return arg_parser::argument::parameters "параметры" указанного \ref arg_parser::argument "аргумента" в виде <a href="https://en.cppreference.com/w/cpp/container/vector.html">вектора</a> <a href="https://en.cppreference.com/w/cpp/string.html">строк</a>.
   */
  const std::vector<std::string>& get_parameters_set(size_t index) const;

  /** 
   * \brief Получить количество \ref arg_parser::argument "аргументов"
   *
   * \return количество \ref arg_parser::argument "аргументов"
   */
  size_t get_arg_num() const;
};

#endif // ARG_PARSER_H
