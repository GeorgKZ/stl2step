/**
 * \file
 *
 * \brief Файл с определениями встроенных функций, соответствующих ГОСТ Р ИСО 10303-11-2009, п.15
 *
 * Здесь определены встроенные функции языка EXPRESS.
 */

#include "stdafx.h"
#include "express.h"

namespace express {

  bool format_check_picture(const std::string& s);
  void format_parse_symbolic(const std::string& s, int& sign, int& width, bool& width_with_zero, int& decimals);

  /**
   * \brief Отобразить мантиссу в виде целого числа или действительного числа с фиксированной запятой.
   * \param [in] m вектор цифр мантиссы.
   * \param [in] n_sign знак отображаемого числа (0, 1, -1).
   * \param [in] width минимальное количество символов для отображения числа.
   * \param [in] sign формат отображения знака числа (0, 1, -1).
   * \param [in] zero_padding true, если заполнение слева выполняется нулями, false, если пробелами.
   * \param [in] right_zero_padding количество нулей, заполняющих справа, или 0.
   * \param [in] dot_pos цифра мантиссы, после которой ставится десятичная точка, может быть меньше нуля.
   * \return строковое представление числа.
   */
  std::string format_m_to_string(const std::vector<unsigned>& m, int n_sign, int width, int sign, bool zero_padding = false, int right_zero_padding = 0, int dot_pos = 10000);

  std::string format_int_to_string(integer_type val, int width, int sign, bool zero_padding) ;
  int format_check_digits(const std::string& s);
  std::string format_i(const NUMBER &N, const std::string& s);
  std::string format_f(const NUMBER &N, const std::string& s);
  std::string format_e(const NUMBER &N, const std::string& s);
  std::string format_t(const NUMBER &N, const std::string& s);



  //!!! сделать v IN agg (-> v >> agg)

  /* Оператор IN 12.2.3 */
  LOGICAL IN(const GENERIC& V, const AGGREGATE_GENERIC& C) {
    if (!V.is_determinated() || !C.is_determinated()) {
      return UNKNOWN;
    }
    integer_type res = C.check_same_element(V, true);
    if (res > 0) return TRUE;
    if (res < 0) return UNKNOWN;
    return FALSE;
  }

  /* 15.1 */
  REAL ABS(const REAL& V) {
    REAL r;
    if (V.is_determinated()) {
      r = fabs(V.get_number_value());
    }
    return r;
  }

  /* 15.1 */
  INTEGER ABS(const INTEGER& V) {
    INTEGER i;
    if (EXISTS(V).is_true()) {
      i = abs(V.get_integer_value());
    }
    return i;
  }

  /* 15.2 */
  REAL ACOS(const NUMBER& V) {
    REAL out;
    if (EXISTS(V).is_true()) {
      if (V.get_number_value() > 1.0 || V.get_number_value() < -1.0) throw exception{__MYFUNCNAME__, "V is out of range"};
      out = acos(V.get_number_value());
    }
    return out;
  }

  /* 15.3 */
  REAL ASIN(const NUMBER& V) {
    REAL out;
    if (EXISTS(V).is_true()) {
      if (V.get_number_value() > 1.0 || V.get_number_value() < -1.0) throw exception{__MYFUNCNAME__, "V is out of range"};
      out = asin(V.get_number_value());
    }
    return out;
  }

  /* 15.4 */
  REAL ATAN(const NUMBER& V1, const NUMBER& V2) {
    REAL out;
    if (EXISTS(V1).is_true() && EXISTS(V2).is_true()) {

      if ((V2 == 0.0).is_true()) {
        if ((V1 == 0.0).is_true()) {
          throw exception{ __MYFUNCNAME__, "V1 == 0 and V2 == 0" };
        }
        out = V1.get_number_value() > 0.0 ? PI / 2.0 : -PI / 2.0;
      } else {
        out = atan(V1.get_number_value() / V2.get_number_value());
      }
    }
    return out;
  }

  /* 15.5 */
//  INTEGER BLENGTH(const BINARY& V);

  /* 15.6 */
  REAL COS(const NUMBER& V) {
    REAL out;
    if (EXISTS(V).is_true()) {
      out = cos(V.get_number_value());
    }
    return out;
  }

  /* 15.7 */
  BOOLEAN EXISTS(const GENERIC& V) {
    return V.is_determinated() ? TRUE : FALSE;
  }

  /* 15.8 */
  REAL EXP(const NUMBER& V) {
    REAL out;
    if (EXISTS(V).is_true()) {
      out = exp(V.get_number_value());
    }
    return out;
  }

  /* 15.9 */


  /**
   * \brief Преобразование строкового представления ширины/точности в числовое с проверкой корректности.
   * \param s [in] Строковое представление ширины/точности.
   * \return Числовое представление ширины/точности.
   */
  int format_check_digits(const std::string& s) {
    for (auto k = s.cbegin(); k != s.cend(); ++k) {
      if (*k >= '0' && *k <= '9') continue;
      throw exception{__MYFUNCNAME__, "F contains wrong 'width' or 'decimals' field"};
    }
    return atoi(s.c_str());
  }

  /**
   * \brief Проверка корректности строки, содержащей описание шаблона представления числа.
   * \param s [in] Строка, содержащая описание шаблона представления числа.
   * \return true, если описание шаблона корректно и false в противном случае.
   */
  bool format_check_picture(const std::string& s) {
    /** Строка, содержащая описание шаблона представления числа, не может быть пустой. */
    if (s.empty()) return false;

    bool first_dot = false;
    bool first_comma = false;

    for (auto k = s.cbegin(); k != s.cend(); ++k) {
      /** Открывающая скобка может быть только в начале строки. */
      if (*k == '(') {
        if (k != s.cbegin()) return false;
      /** Закрывающая скобка может быть только в конце строки. */
      } else if (*k == ')') {
        if (k != s.cend() - 1) return false;
      /** Если были запятые, точка может быть только один раз. */
      } else if (*k == '.') {
        if (first_comma && first_dot) return false;
        first_dot = true;
      /** Если были точки, запятая может быть только один раз. */
      } else if (*k == ',') {
        if (first_dot && first_comma) return false;
        first_comma = true;
      } else if (*k == '+' || *k == '-') {
      /** Знак может быть в начале строки или после открывающей скобки. */
        if (k != s.cbegin() && !(k == s.cbegin() + 1 && s[0] == '(')) return false;
      /** Кроме этих символов может быть только октагон. */
      } else if (*k != '#') return false;
    }
    return true;
  }

  /**
   * \brief Разбор символьного представления числа на поля.
   * \param s [in] Символьное представление (или формат).
   * \param sign [out] Знак символьного представления числа: 1 или -1, и 0, если знак не указан.
   * \param width [out] Ширина символьного представления.
   * \param width_with_zero [out] true, если указанная в символьном представлении ширина начинается с нуля.
   * \param decimals [out] Точность символьного представления или -1, если точность не указана.
   */
  void format_parse_symbolic(const std::string& s, int& sign, int& width, bool& width_with_zero, int& decimals) {

    /** Установить начальное значение итератора обработки строки символьного представления числа */
    std::string::const_iterator k = s.begin();

    if (*k == '+') {
      sign = 1;
      ++k;
    } else if (*k == '-') {
      sign = -1;
      ++k;
    } else sign = 0;
    /** Определить строковое представление ширины символьного представления числа и */
    std::string s_width;
    /** строковое представление точности символьного представления числа, */
    std::string s_decimals;
    bool process_width = true;
    for (std::string::const_iterator l = k; l != s.end() - 1; ++l) {
      if (*l == '.') {
        process_width = false;
        continue;
      }
      if (process_width) {
        s_width += *l; 
      } else {
        s_decimals += *l; 
      }
    }
    if (s_width.empty()) {
      throw exception{__MYFUNCNAME__, "F contains empty 'width' field"};
    } else {
      if ('0' == *s_width.begin()) {
        width_with_zero = true;
      }
      width = format_check_digits(s_width);
    }
    if (s_decimals.empty()) {
      decimals = -1;
    } else {
      decimals = format_check_digits(s_decimals);
    };
  }

  /**
   * \brief Добавление знака к строковому представленю числа.
   * \param s [in] Строковое представление числа или nullptr.
   * \param sign [in] Знак символьного представления числа: 1 или -1, и 0, если знак не указан.
   * \param n_sign [in] Знак числа: 1 или -1, и 0, если знак не указан.
   * \return true, если знак был добавлен.
   */
  static bool format_sign(std::string *s, int sign, int n_sign) {
    if (sign == -1 || sign == 0) {
      if (n_sign == -1) {
        if (s != nullptr) *s += '-';
        return true;
      }
    } else {
      if (n_sign == -1) {
        if (s != nullptr) *s += '-';
        return true;
      }
      if (n_sign == 1) {
        if (s != nullptr) *s += '+';
        return true;
      }
      if (n_sign == 0) {
//        if (s != nullptr) *s += ' ';
//        return true;
        return false;
      }
    }
    return false;
  }

  std::string format_m_to_string(const std::vector<unsigned>& m, int n_sign, int width, int sign, bool zero_padding, int right_zero_padding, int dot_pos) {

    /** Алгоритм: */

    /** 1 Определить количество цифр в мантиссе. */
    int m_len = static_cast<int>(m.size());

    /** 2 Рассчитать необходимую длину заполнения слева. */
    int pad_len = width <= m_len ? 0 : width - m_len;
    /** - Учесть наличие знака. */
    if (pad_len > 0 && format_sign(nullptr, sign, n_sign)) pad_len --;
    /** - Учесть наличие десятичной точки. */
    if (pad_len > 0 && dot_pos < static_cast<int>(m_len + right_zero_padding)) pad_len --;

    /** 3 При заполнении слева нулями вставить знак (при необходимости) перед заполнением. */
    std::string S;
    if (zero_padding && (dot_pos > 0)) {
      format_sign(&S, sign, n_sign);
    }

    /** 4 Если есть место для заполнения, заполнить нулями или пробелами. */
    for (int i = 0; i < pad_len; ++i) {
      if (i == pad_len - 1 + dot_pos) format_sign(&S, sign, n_sign);
      if (pad_len - i == -dot_pos) S += '.';
      S += (zero_padding || (i >= pad_len - 1 + dot_pos)) ? '0' : ' ';
    }

    /** 5 При заполнении слева пробелами вставить знак (при необходимости) после заполнения. */
    if (!zero_padding && (dot_pos > 0)) {
      format_sign(&S, sign, n_sign);
    }

    /** 6 Отобразить содержимое мантиссы. */
    for (int i = 0; i < m_len; ++i) {
      if (i == dot_pos) S += '.';
      S += static_cast<char>(m[static_cast<size_t>(i)] + '0');
    }

    /** 7 При необходимости вывести справа указанное количество нулей. */
    for (int i = 0; i < right_zero_padding; ++i) {
      if (static_cast<int>(i + m_len) == dot_pos) S += '.';
      S += '0';
    }
    return S;
  }

  /**
   * \brief Отобразить целое число в целочисленном формате 'I'.
   * \param [in] val целое число, строковое представление которого необходимо получить.
   * \param [in] width минимальное количество символов для отображения числа.
   * \param [in] sign формат отображения знака числа (0, 1, -1).
   * \param [in] zero_padding true, если заполнение слева выполняется нулями, false, если пробелами.
   * \return строковое представление числа val.
   */
  std::string format_int_to_string(integer_type val, int width, int sign, bool zero_padding) {

    /** Алгоритм: */

    /** 1 Определить знак числа val. */
    int n_sign = val == 0 ? 0 : val > 0 ? 1 : -1;
    val = abs(val);

    /** 2 Определить представление числа val в виде массива цифр. */
    std::vector<unsigned> m;
    do {
      m.insert(m.begin(), static_cast<unsigned>(val % 10));
      val /= 10;
    } while(val);

    /** 3 Окончательно сформировать результат. */
    return format_m_to_string(m, n_sign, width, sign, zero_padding, 0);
  }

  /**
   * \brief Представление числа N в целочисленном формате 'I'.
   * \param [in] N Число, которое требуется представить в целочисленном формате.
   * \param [in] s символьное описание требуемого представления (формат).
   * \return строковое представление числа в целочисленном формате, определённом строкой s.
   */
  std::string format_i(const NUMBER &N, const std::string& s) {

    /**
     * Алгоритм:
     *
     * 1 Выполнить разбор строки символьного представления и определить:
     */

    /** * знак символьного представления F: 1 или -1, или 0, если знак не указан; */
    int sign;
    /** * ширину символьного представления F; */
    int width;
    /** * начинается ли с нуля строковое представление ширины символьного представления F;  */
    bool width_with_zero = false;
    /** * точность символьного представления F (-1, если точность не указана). */
    int decimals;

    format_parse_symbolic(s, sign, width, width_with_zero, decimals);

    /** 2 Убедиться, что элемент decimals не должен быть задан, */
    if (decimals != -1) {
      throw exception{__MYFUNCNAME__, "if type field in STRING F is 'I', decimals shall not be specifed"};
    }
    /** и значение элемента width должно быть не менее двух. */
    if (width < 2) {
      throw exception{__MYFUNCNAME__, "if type field in STRING F is 'I', the width specification shall be at least two"};
    }

    /**
     * 3 Установить представление real_type числа N, если оно имеет тип REAL,
     * а также признак --- true, если число N имеет тип REAL или NUMBER, и false, если оно имеет тип INTEGER
     */
    bool is_real = N.is_real() || N.is_number();
    /** и точность представления (кол-во дейструющих разрядов) мантиссы если число N имеет тип REAL. */
    int n_precision = static_cast<int>(N.get_number_precision());

    /** 4 Если число N имеет тип REAL, преобразовать к целому типу с округлением: */
    if (is_real) {
      /** * определить экспоненту числа; */
      int n_exponent = real_to_int(log10(abs(N.get_number_value())));
      /** * определить количество отображаемых цифр мантиссы; */
      int prec_part = std::min(n_precision, n_exponent + 1);
      /** * определить количество заполняющих нулей до разряда единиц; */
      int padding = n_exponent - n_precision + 1 > 0 ? n_exponent - n_precision + 1  : 0;
      /** * отобразить все цифры мантиссы с округлением и при необходимости нули до разряда единиц. */
      int n_sign;
      std::vector<unsigned> n_mantiss;
      if (prec_part < 0) {
        n_mantiss.push_back(0);
        n_exponent = 0;
        n_sign = 0;
      } else {
        REAL::round(N.get_number_value(), static_cast<unsigned>(prec_part), &n_mantiss, &n_exponent, &n_sign);
      }
      return format_m_to_string(n_mantiss, n_sign, width - padding, sign, width_with_zero, padding);
    /** 5 Если число N имеет тип INTEGER, вывести его полностью с заполнением при необходимости. */
    } else {
      return format_int_to_string(N.get_integer_value(), width, sign, width_with_zero);
    }
  }

  /**
   * \brief Представление числа N в формате действительного числа с фиксированной десятичной
   * точкой 'F'.
   * \param [in] N Число, которое требуется представить в формате действительного числа с
   * фиксированной десятичной точкой.
   * \param [in] s символьное описание требуемого представления (формат).
   * \return строковое представление числа в в формате действительного числа с фиксированной
   * десятичной точкой, определённом строкой s.
   */
  std::string format_f(const NUMBER &N, const std::string& s) {

    /**
     * Алгоритм:
     *
     * 1 Выполнить разбор строки символьного представления и определить:
     */

    /** * знак символьного представления F: 1 или -1, или 0, если знак не указан; */
    int sign;
    /** * ширину символьного представления F; */
    int width;
    /** * начинается ли с нуля строковое представление ширины символьного представления F;  */
    bool width_with_zero = false;
    /** * точность символьного представления F (-1, если точность не указана). */
    int decimals;

    format_parse_symbolic(s, sign, width, width_with_zero, decimals);

    /** 2 Убедиться, что значение элемента decimals, если он задан, должно быть не менее единицы, */
    if (decimals != -1 && decimals < 1) {
      throw exception{__MYFUNCNAME__, "if type field in STRING F is 'F', the decimals, if specified, shall be at least one"};
    }
    /** а если элемент decimals не задан, то используется его значение по умолчанию равное двум, */
    if (decimals == -1) {
      decimals = 2;
    }
    /** и значение элемента width должно быть не менее четырёх. */
    if (width < 4) {
      throw exception{__MYFUNCNAME__, "if type field in STRING F is 'F', the width specification shall be at least four"};
    }

    /** 3 Установить представление REAL числа N, если оно имеет тип REAL, */
    /** или представление INTEGER числа N, если оно имеет тип INTEGER, */
    /** а также признак --- true, если число N имеет тип REAL или NUMBER, и false, если оно имеет тип INTEGER, */
    bool is_real = N.is_real() || N.is_number();
    /** и точность представления (кол-во дейструющих разрядов) мантиссы, если число N имеет тип REAL */
    int n_precision = static_cast<int>(N.get_number_precision());

    /**
     * 4 Если число N имеет тип INTEGER, сформировать его строковое представление
     * с учётом значений полей 'знак' и 'ширина', указанных в символьном представлении 'F',
     */
    if (!is_real) {
      std::string Si = format_int_to_string(N.get_integer_value(), width - decimals - 1, sign, false);
      /** добавить десятичную точку */
      Si += '.';
      /** и нули в количестве, определяемом полем 'точность' символьного представления F. */
      for (auto i = 0; i < decimals; ++i) {
        Si += '0';
      }
      return Si;
    /**
     * 5 Если число N имеет тип REAL, сдвинуть влево на decimals десятичных разрядов,
     * при наличии разрядов вне мантиссы определив "хвост" из нулей:
     */
    } else {
      /** * определить экспоненту числа; */
      int n_exponent = real_to_int(log10(abs(N.get_number_value())));
      /** * определить количество отображаемых цифр мантиссы; */
      int prec_part = std::min(n_precision, n_exponent + 1 + decimals);
      /** * определить количество заполняющих справа нулей до разряда единиц; */
      int padding = n_exponent - n_precision + 1 + decimals;
      if (padding < 0) padding = 0;
      /** * отобразить все цифры мантиссы с округлением и при необходимости нули до разряда единиц. */
      int n_sign;
      std::vector<unsigned> n_mantiss;
      if (prec_part < 0) {
        n_mantiss.push_back(0);
        n_exponent = 0;
        n_sign = 0;
      } else {
        REAL::round(N.get_number_value(), static_cast<unsigned>(prec_part), &n_mantiss, &n_exponent, &n_sign);
      }
      return format_m_to_string(n_mantiss, n_sign, width - padding, sign, false, padding, n_sign ? n_exponent + 1 : 1 - decimals);
    }
  }

  /**
   * \brief Представление числа N в формате действительного числа в экспоненциальной форме 'E'.
   * \param [in] N Число, которое требуется представить в в формате действительного числа в
   * экспоненциальной форме.
   * \param [in] s символьное описание требуемого представления (формат).
   * \return строковое представление числа в экспоненциальном формате, определённом строкой s.
   */
  std::string format_e(const NUMBER &N, const std::string& s) {

    /**
     * Алгоритм:
     *
     * 1 Выполнить разбор строки символьного представления и определить:
     */

    /** * знак символьного представления F: 1 или -1, или 0, если знак не указан; */
    int sign;
    /** * ширину символьного представления F; */
    int width;
    /** * начинается ли с нуля строковое представление ширины символьного представления F;  */
    bool width_with_zero = false;
    /** * точность символьного представления F (-1, если точность не указана). */
    int decimals;

    format_parse_symbolic(s, sign, width, width_with_zero, decimals);

    /** 2 Убедиться, что элемент decimals задан, */
    if (decimals == -1) {
      throw exception{__MYFUNCNAME__, "decimals shall always be specified for a type E"};
    }

    /** значение элемента decimals не менее единицы, */
    if (decimals < 1) {
      throw exception{__MYFUNCNAME__, "the decimals specification shall be at least one for a type E"};
    }

    /** а значение элемента width не менее семи. */
    if (width < 7) {
      throw exception{__MYFUNCNAME__, "the width specification shall be at least seven (7)"};
    }

    /**
     * 4 Если число N имеет тип INTEGER, сформировать его строковое представление
     * с учётом значений полей 'знак' и 'ширина', указанных в символьном представлении F:
     */
    if (N.is_integer()) {
      integer_type val = N.get_integer_value();

      /** * определить знак числа val; */
      int n_sign = val == 0 ? 0 : val > 0 ? 1 : -1;
      val = abs(val);

      /** * привести число val к строковому представлению; */
      std::vector<unsigned> n_mantiss;
      while(val) {
        n_mantiss.insert(n_mantiss.begin(), static_cast<unsigned>(val % 10));
        val /= 10;
      };
      n_mantiss.push_back(0);

      /**
       * * если в элементе width задан предшествующий ноль, то первыми двумя символами мантиссы
       * будут '0' и '.';
       */
      int out_exp = width_with_zero ? 0 : 1;

      /** * определить отображаемую точность представления (кол-во дейструющих разрядов) мантиссы; */
      int n_precision = std::min(decimals + out_exp, static_cast<int>(n_mantiss.size()) - 1);

      /** * экспоненциальная часть будет содержать, по меньшей мере, два символа с обязательным знаком; */
      int exponent = static_cast<int>(n_mantiss.size()) - 1 - out_exp;
      std::string s_exp = std::to_string(exponent);
      if (s_exp.length() < 2) s_exp = '0' + s_exp;
      if (exponent >= 0) s_exp = '+' + s_exp;
      /** * добавить перед значением экспоненты отображаемый символ 'Е' --- прописной буквой (символом верхнего регистра); */
      s_exp = 'E' + s_exp;

      /**
       * * предусмотреть вариант, когда требуемое количество разрядов после запятой больше размера
       * мантиссы и потребуется "хвост" из нулей;
       */
      int r_padding = decimals - (n_precision - out_exp);
      if (r_padding < 0) r_padding = 0;

      /** * выполнить округление до отображаемой дины мантиссы; */
      REAL::round_m(n_mantiss, static_cast<unsigned>(n_precision), sign);

      /** * выполнить отображение мантиссы; */
      std::string S = format_m_to_string(n_mantiss, n_sign, width - static_cast<int>(s_exp.length()) - r_padding, sign, false, r_padding, out_exp);

      /** * добавить в отображение экспоненту. */
      S += s_exp;
      return S;
    /**
     * 5 Если число N имеет тип REAL, сдвинуть влево на decimals десятичных разрядов,
     * при наличии разрядов вне мантиссы определив "хвост" из нулей:
     */
    } else {
      /** * если в элементе width задан предшествующий ноль, то первыми двумя символами мантиссы будут '0' и '.'; */
      int out_exp = width_with_zero ? 0 : 1;
      /** * определить отображаемую точность представления (кол-во дейструющих разрядов) мантиссы; */
      int n_precision = std::min(decimals + out_exp, static_cast<int>(N.get_number_precision()));
      /** * определить мантиссу (с округлением при необходимости), экспоненту и знак числа; */
      std::vector<unsigned> n_mantiss;
      int n_exponent;
      int n_sign;
      REAL::round(N.get_number_value(), static_cast<unsigned>(n_precision), &n_mantiss, &n_exponent, &n_sign);

      /** * Экспоненциальная часть будет содержать, по меньшей мере, два символа с обязательным знаком; */
      int exponent = n_exponent + 1 - out_exp;
      std::string s_exp = std::to_string(exponent);
      if (s_exp.length() < 2) s_exp = '0' + s_exp;
      if (exponent >= 0) s_exp = '+' + s_exp;
      /** * добавить перед значением экспоненты отображаемый символ 'Е' --- прописной буквой (символом верхнего регистра); */
      s_exp = 'E' + s_exp;

      /**
       * * предусмотреть вариант, когда требуемое количество разрядов после запятой больше размера
       * мантиссы и потребуется "хвост" из нулей;
       */
      int r_padding = decimals - (n_precision - out_exp);
      if (r_padding < 0) r_padding = 0;

      /** * выполнить отображение мантиссы; */
      std::string S = format_m_to_string(n_mantiss, n_sign, width - static_cast<int>(s_exp.length()) - r_padding, sign, false, r_padding, out_exp);

      /** * добавить в отображение экспоненту. */
      S += s_exp;
      return S;
    }
  }

  /**
   * \brief Представление числа N в форме, определённой шаблоном.
   * \param [in] N Число, которое требуется представить в форме, определённой шаблоном.
   * \param [in] s описание шаблона требуемого представления (формат).
   * \return строковое представление числа шаблоном, определённом строкой s.
   */
  std::string format_t(const NUMBER &N, const std::string& s) {

    /** 1 Установить представление REAL числа N, если оно имеет тип REAL, */
    real_type r_val;
    /** или представление INTEGER числа N, если оно имеет тип INTEGER, */
    integer_type i_val;
    /** а также признак --- true, если число N имеет тип REAL или NUMBER, и false, если оно имеет тип INTEGER, */
    bool is_real = N.is_real() || N.is_number();
    /**  и точность представления (кол-во дейструющих разрядов) мантиссы, если число N имеет тип REAL. */
    int n_precision = static_cast<int>(N.get_number_precision());

    if (!format_check_picture(s)) {
      throw exception{__MYFUNCNAME__, "STRING F has wrong 'picture' format"};
    }

    /** 2 Определить требуемое число знаков после запятой и десятичный разделитель. */
    int decimals = 0;
    bool dot_is_decimal_point = false;
    bool comma_is_decimal_point = false;
    for (auto i = s.crbegin(); i != s.crend(); ++i, ++decimals) {
      if (*i == '.' ) {
        dot_is_decimal_point = true;
        break;
      }
      if (*i == ',') {
        comma_is_decimal_point = true;
        break;
      }
    }
    if (!dot_is_decimal_point && !comma_is_decimal_point) decimals = 0;

    /** 3 Определить требуемое символов до десятичного разделителя. */
    int width = 0;
    for (auto i = s.cbegin(); i != s.cend(); ++i) {
      if (*i == '.' && dot_is_decimal_point) break;
      if (*i == ',' && comma_is_decimal_point) break;
      if (*i == '#' ) width ++;
    }

    /**
     * 4 Если число N имеет тип INTEGER, сформировать его строковое представление
     * и подставить в шаблон:
     */
    if (!is_real) {

      i_val = N.get_integer_value();

      /** * определить знак числа val; */
      int n_sign = i_val >= 0 ? 1 : -1;

      /** * определить представление числа val в виде массива цифр; */
      integer_type val = abs(i_val);
      std::vector<unsigned> mantissa;
      do {
        mantissa.insert(mantissa.begin(), static_cast<unsigned>(val % 10));
        val /= 10;
      } while(val);

      /**
       * * внимание, в стандарте не определено! Если число не укладывается в шаблон, вместо цифр будут
       * выведены символы '#';
       */
      std::string C;
      if (static_cast<int>(mantissa.size()) > width) {
        for (auto i = 0; i < width; ++i) C.push_back('#');
      } else {
        /** * Сформировать строковое представление числа длиной width с заполнением проделами слева. */
        C = format_m_to_string(mantissa, 0, width, 0, false, 0);
      }

      /**
       * * заполнить шаблон цифрами (нулями после окончания строкового представления числа)
       * строкового представления числа.
       */
      std::string S;
      for (auto i = s.cbegin(), k = C.cbegin(); i != s.cend(); ++i) {
        if (*i == '#') {
          if (k == C.cend()) {
            S.push_back('0');
          } else {
            S.push_back(*k);
            ++k;
          }
        }
        else if (*i == '(' || *i == ')') S.push_back(n_sign == 1 ? ' ' : *i);
        else if (*i == '+' || *i == '-') S.push_back(n_sign == 1 ? '+' : '-');
        else if (*i == '.' || *i == ',') S.push_back(*i);
        else  {
          throw exception{__MYFUNCNAME__, "STRING F contains wrong 'picture' char"};
        }
      }
      return S;

    /**
     * 5 Если число N имеет тип REAL, сдвинуть влево на decimals десятичных разрядов,
     * при наличии разрядов вне мантиссы определив "хвост" из нулей:
     */
    } else {

      r_val = N.get_number_value();

      /** * определить экспоненту числа; */
      int n_exponent = real_to_int(log10(abs(r_val)));
      /** * определить количество отображаемых цифр мантиссы; */
      int prec_part = std::min(n_precision, n_exponent + 1 + decimals);
      /** * определить количество заполняющих справа нулей до разряда единиц; */
      int padding = n_exponent - n_precision + 1 + decimals;
      if (padding < 0) padding = 0;

      /** * подготовить округлённую мантиссу; */
      int n_sign;
      std::vector<unsigned> mantissa;
      if (prec_part < 0) {
        mantissa.push_back(0);
        n_exponent = 0;
        n_sign = 0;
      } else {
        REAL::round(r_val, static_cast<unsigned>(prec_part), &mantissa, &n_exponent, &n_sign);
      }

      /**
       * * внимание, в стандарте не определено! Если число не укладывается в шаблон, вместо цифр
       * будут выведены символы '#';
       */
      std::string C;
      if (static_cast<int>(mantissa.size()) - decimals > width) {
        for (auto i = 0; i < width; ++i) C.push_back('#');
      } else {
        /**
         * * сформировать строковое представление числа длиной width + decimals с заполнением
         *  пробелами слева и при необходимости нулями до разряда единиц.
         */
        C = format_m_to_string(mantissa, 0, width + decimals - padding, 0, false, padding);
      }

      /** * заполнить шаблон цифрами мантиссы. */
      std::string S;
      for (auto i = s.cbegin(), k = C.cbegin(); i != s.cend(); ++i) {
        if (*i == '#') {
          if (k == C.cend()) {
            throw exception{__MYFUNCNAME__, "internal error during rendering 'picture' string"};
          } else {
            S.push_back(*k);
            ++k;
          }
        }
        else if (*i == '(' || *i == ')') S.push_back(n_sign == 1 ? ' ' : *i);
        else if (*i == '+' || *i == '-') S.push_back(n_sign == 1 ? '+' : '-');
        else if (*i == '.' || *i == ',') S.push_back(*i);
        else  {
          throw exception{__MYFUNCNAME__, "STRING F contains wrong 'picture' char"};
        }
      }
      return S;
    }
  }

  STRING FORMAT(const NUMBER& N, const STRING& F) {

    /**
     * Возвратить неопределенный (?) результат, если был передан хотя бы один
     * параметр с неопределенным (?) значением.
     */
    if (EXISTS(N).is_false() || EXISTS(F).is_false()) {
      return STRING();
    }

    const std::string& s = F.get_value();

    if (!s.empty()) {

      /** a) строка форматирования может задавать символьное описание представления результата
            "[sign] width [.decimals] type": */
      switch (s.back()) {
        /**
         * a.1) если в качестве элемента type задана буква I, то результат должен быть представлен в виде
         * целого числа.
         */
        case 'I':
          return  format_i(N, s);
        /**
         * a.2) если в качестве элемента type задана буква F, то результат должен быть представлен в виде
         * действительного числа с фиксированной десятичной точкой.
         */
        case 'F':
          return  format_f(N, s);
        /**
         * a.3) если в качестве элемента type задана буква Е, то результат должен быть представлен в виде
         * действительного числа в экспоненциальной форме.
         */
        case 'E':
          return format_e(N, s);
        /** b) строка форматирования может задавать описание шаблона представления результата; */
        default:
          return format_t(N, s);
      }
    } else {
      /** c) если строка форматирования пуста, то производится стандартное представление результата (15.9.3): */
      if (N.is_type_name("INTEGER")) {
        /** стандартным представлением для целых чисел является '7I'; */
        return format_i(N, std::string("7I"));
      } else {
        /** стандартным представлением для действительных чисел является '10.1E'. */
        return format_e(N, std::string("10.1E"));
      }
    }
  }

  /* 15.10 */
  INTEGER HIBOUND(const AGGREGATE_GENERIC& V) {
    INTEGER out;
    if (V.is_hibound()) {
      out = V.get_hibound();
    }
    return out;
  }

  INTEGER HIINDEX(const AGGREGATE_GENERIC& V) {
    return V.get_hiindex();
  }

  /* 15.12 */
  INTEGER LENGTH(const STRING& V) {
    return static_cast<integer_type>(V._s.length());
  }

  /* 15.13 */
  INTEGER LOBOUND(const AGGREGATE_GENERIC& V) {
    return V.get_lobound();
  }

  /* 15.14 */
  REAL LOG(const NUMBER& V) {
    REAL out;
    if (EXISTS(V).is_true()) {
      if (V.get_number_value() <= 0) throw exception{__MYFUNCNAME__, "V is out of range"};
      out = log(V.get_number_value());
    }
    return out;
  }

  /* 15.15 */
  REAL LOG2(const NUMBER& V) {
    REAL out;
    if (EXISTS(V).is_true()) {
      if (V.get_number_value() <= 0) throw exception{__MYFUNCNAME__, "V is out of range"};
      out = log2(V.get_number_value());
    }
    return out;
  }

  /* 15.16 */
  REAL LOG10(const NUMBER& V) {
    REAL out;
    if (EXISTS(V).is_true()) {
      if (V.get_number_value() <= 0) throw exception{__MYFUNCNAME__, "V is out of range"};
      out = log10(V.get_number_value());
    }
    return out;
  }

  /* 15.17 */
  INTEGER LOINDEX(const AGGREGATE_GENERIC& V) {
    return V.get_loindex();
  }

  /* 15.19 */
  LOGICAL ODD(const INTEGER& V) {
    if (EXISTS(V).is_false()) {
      return LOGICAL();
    }

    integer_type v = V.get_integer_value();
    if (v == 0) return LOGICAL::FALSE;

    if ((v % 2) == 1) return LOGICAL::TRUE;
    return LOGICAL::FALSE;
  }

  /* 15.20 */
//  SET_GENERIC& ROLESOF(const GENERIC_ENTITY& V);

  /* 15.21 */
  REAL SIN(const NUMBER& V) {
    REAL out;
    if (EXISTS(V).is_true()) {
      out = sin(V.get_number_value());
    }
    return out;
  }

  /* 15.22 */
  INTEGER SIZEOF(const AGGREGATE_GENERIC& V) {
    return V.get_hiindex() - V.get_loindex() + 1;
  }

  /* 15.23 */
  REAL SQRT(const NUMBER& V) {
    REAL out;
    if (EXISTS(V).is_true()) {
      if (V.get_number_value() < 0) throw exception{__MYFUNCNAME__, "V is out of range"};
      out = sqrt(V.get_number_value());
    }
    return out;
  }

  /* 15.24 */
  REAL TAN(const NUMBER& V) {
    REAL out;
    if (EXISTS(V).is_true()) {
      out = tan(V.get_number_value());
    }
    return out;
  }

  /* 15.25 */
//  SET_GENERIC& TYPEOF(const GENERIC& V);

  /* Универсальная функция USEDIN, 15.26 */
//  BAG_GENERIC& USEDIN(const GENERIC& T, const STRING& R);

  /* Арифметическая функция VALUE, 15.27 */
  NUMBER VALUE(const STRING& V) {
    NUMBER n;
    const std::string& v = V.get_value();
    bool decimal_dot = false;
    for (auto i = v.cbegin(); i != v.cend(); ++i) {
      if (*i == '-' && i == v.cbegin()) continue;
      if (*i >= '0' && *i <= '9') continue;
      if (!decimal_dot && *i == '.') {
        decimal_dot = true;
        continue;
      }
      return n;
    }
    if (decimal_dot) {
//!!!
      return n;
    } else {
//!!!
      return n;
    }
  }

  /* 15.28 */
  LOGICAL VALUE_IN(const AGGREGATE_GENERIC& C, const GENERIC& V) {
    if (!V.is_determinated() || !C.is_determinated()) {
      return UNKNOWN;
    }
    integer_type res = C.check_same_element(V, false);
    if (res > 0) return TRUE;
    if (res < 0) return UNKNOWN;
    return FALSE;
  }

  /* 15.29 */
//  LOGICAL VALUE_UNIQUE(const AGGREGATE_GENERIC& V);
}