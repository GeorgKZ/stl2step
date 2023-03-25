/**
 * \file
 *
 * \brief Коды ошибок
 */

#ifndef _ERR_H
#define _ERR_H

/**
 * \defgroup error_codes Error codes
 * \ingroup infrastructure
 * \{
 */

/** Определения констант кодов ошибки.        */
enum
#if !defined(__DOXYGEN__)
      class
#endif 
  err_enum_t
#if !defined(__DOXYGEN__)
      : int
#endif 
 {
/** Ошибок нет, всё в порядке.                */
  ERROR_OK         =  0,
/** Ошибка формата командной строки.          */
  ERROR_CMD_FORMAT = -1,
/** Ошибка чтения/записи файла.               */
  ERROR_FILE_IO    = -2,
/** Ошибка при импорте файла STL.             */
  ERROR_IMPORT     = -3,
/** Внутренняя ошибка, котоой не должно быть. */
  ERROR_INTERNAL   = -4
};

namespace express {

  /** \brief Убрать избыточные префиксы из имени функции или класса */
  std::string convert_name(const char* name);

  /**
   * \brief Класс исключения при выполнении функций, реализующих язык Express
   */
  class exception : public std::runtime_error {

  private:

    /** \brief Имя функции, в которой было вызвано исключение */
    std::string funcname;

    /** \brief Текст сообщения об ошибке */
    std::string errmsg;

    std::string vformat(const char* format, va_list args) const;

  public:

    /** \brief Конструктор */
    exception(char const* fname, char const* fmt, ...) noexcept;

    /** \brief Получить текст сообщения об ошибке */
    virtual const char* what() const throw() override;

    /** \brief Получить имя функции, в которой было вызвано исключение */
    const char* where() const throw();
  };
}

/**
 * \}
 */

#endif /* _ERR_H */