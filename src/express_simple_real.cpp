/**
 * \file
 *
 * \brief Файл с определениями функций класса REAL, соответствующего ГОСТ Р ИСО 10303-11-2009, п.8.1.2
 *
 * Здесь определены функции, реализующие функции-члены класса REAL, соответствующему типу данных
 * действительных чисел языка EXPRESS.
 */

#include "stdafx.h"
#include "express.h"

namespace express {

  /**
   * \file
   * Для типа REAL определены следующие члены-методы (функции):<BR><BR>
   *
   * Функции округления и сравнения действительных чисел:
   */

  /**
   * \file
   * * \copybrief express::REAL::round_m()
   */
  bool REAL::round_m(std::vector<unsigned>& mantissa, unsigned precision, int sign) {
    bool special = false;

    /**
     * Алгоритм:
     *
     * a) проверить mantissa - мантиссу экспоненциального представления числа */
    assert(!mantissa.empty());
    if (precision == 0) {
      special = true;
    } else {
      assert(mantissa.size() > static_cast<size_t>(precision));
    }

    /** b) установить указатель разряда k на р-ю позицию справа от десятичной точки; */
    std::vector<unsigned>::size_type k = precision;

    /** c) если действительное число является положительным, то выполняются следующие действия: */
    if (sign >= 0) {
      /** - если цифра, расположенная на позиции k, принадлежит к диапазону от 5 до 9, */ 
      if (mantissa[k] >= 5 && mantissa[k] <= 9) {
        if (special) return true;

        /** то добавить 1 к цифре, расположенной на позиции k–1, */
        mantissa[static_cast<std::vector<unsigned>::size_type>(k) - 1] ++;
        /** а цифры, начиная с позиции k и далее, отбросить. */
        mantissa.resize(k);
        /**  Перейти к шагу по перечислению e); */
      }
      /** - если цифра, расположенная на позиции k, принадлежит к диапазону от 0 до 4,*/
      else {
        /** то цифры, начиная с позиции k и далее, отбросить. */
        mantissa.resize(k);
        /** Перейти к шагу по перечислению h);  */
        return false;
      }
    /** d) если действительное число является отрицательным, то выполняются следующие действия: */
    } else {
      /** - если цифра, расположенная на позиции k, принадлежит к диапазону от 6 до 9, */
      if (mantissa[k] >= 6 && mantissa[k] <= 9) {
        if (special) return true;

        /** то добавить 1 к цифре, расположенной на позиции k–1,*/
        mantissa[static_cast<std::vector<unsigned>::size_type>(k) - 1] ++;
        /** а цифры, начиная с позиции k и далее, отбросить. */
        mantissa.resize(k);
        /** Перейти к шагу по перечислению e); */
      }
      /** - если цифра, расположенная на позиции k, принадлежит к диапазону от 0 до 5, */
      else { 
        /** то цифры, начиная с позиции k и далее, отбросить. */
        mantissa.resize(k);
        /** Перейти к шагу по перечислению h);  */
        return false;
      }
    }

    for (; k != 0;) {
      /** e) присвоить указателю разряда k значение k–1;  */
      k--;

      /** f) если цифра, расположенная на позиции k, принадлежит к диапазону от 0 до 9, */
      if (mantissa[k] <= 9) {
        /** то перейти к шагу по перечислению h); */
        return false;
      }

      /** g) если цифра, расположенная на позиции k, имеет значение 10, */
      if (mantissa[k] == 10) {
        /** то добавить 1 к цифре, расположенной на позиции k–1, */
        if (k >= 1) {
          mantissa[static_cast<std::vector<unsigned>::size_type>(k) - 1] ++;
        }
        /** и установить цифру, расположенную на позиции k, в 0. */
        mantissa[k] = 0;
        /** Перейти к шагу по перечислению e);  */
      } else return false;
    }
    /** h) округление действительного числа завершено. */
    return false;
  }

  /**
   * \file
   * * \copybrief express::REAL::round()
   */
  real_type REAL::round(real_type src, unsigned precision, std::vector<unsigned>* r_mant, int* r_exp, int* r_sign) {

    /**
     * Алгоритм:
     *
     * * Проверить значение точности - слишком большое значение считается максимальным.
     */
    if (precision >= precision_max) precision = precision_max;

    /**
     * * Проверить на значение нуля или около того.
     */
    if (abs(src) < std::numeric_limits<real_type>::min()) {
      if (r_mant != nullptr) {
        r_mant->clear();
        r_mant->push_back(0);
      }
      if (r_sign != nullptr) *r_sign = 0;
      if (r_exp != nullptr) *r_exp = 0;

#ifdef TRACE_REAL
    printf("%s: return zero value\n", __MYFUNCNAME__);
#endif

      return 0;
    }

    /**
     * * Для использования алгоритма округления согласно п.12.1 ГОСТ Р ИСО 10303-11-2009
     * преобразовать представление числа в экспоненциальный формат с удалением всех предшествующих нулей.
     */

    /** * Определить знак числа */
    int sign = src < 0 ? -1 : 1;
    /** * Определить экспоненту числа */
    int exponent = real_to_int(log10(abs(src)));
    /** * Определить мантиссу числа (сдвинутую в целочисленную часть действительного числа) */
    real_type mantissa = abs(src) * pow(10.0, static_cast<int>(precision_max) - exponent);

    /** * Определить мантиссу числа в виде ряда цифр от старшего разряда к младшему,
       с дополнительным разрядом к максимальной точности */
    std::vector<unsigned> mant;
    for (unsigned i = 0; i <= precision_max; ++i) {
      real_type m_next = mantissa / 10;
      mant.insert(mant.begin(), static_cast<unsigned>(real_to_int(std::trunc(mantissa) - std::trunc(m_next) * 10)));
      mantissa = m_next;
    }

#ifdef TRACE_REAL
    std::vector<int> mant_src = mant;
#endif

    /** * Использовать алгоритм округления согласно п.12.1 ГОСТ Р ИСО 10303-11-2009. */
    bool round_to_1 = round_m(mant, precision, sign);


#ifdef TRACE_REAL
    printf("%s: '", __MYFUNCNAME__);
    for (auto i = mant_src.cbegin(); i != mant_src.cend(); ++i) {
      printf("%c", *i + '0');
    }
    printf("' -> '");
    for (auto i = mant.cbegin(); i != mant.cend(); ++i) {
      printf("%c", *i + '0');
    }
    printf("'\n");
#endif

    /**
     * * Специальное значение точности, равное нулю, приводит к округлению до нуля или единицы
     * разряда, стоящего слева от старшего разряда мантиссы.
     */
    if (precision == 0) {
      if (r_mant != nullptr) {
        r_mant->clear();
        r_mant->push_back(round_to_1 ? 1U : 0U);
      }
      if (r_sign != nullptr) *r_sign = round_to_1 ? sign : 0;
      if (r_exp != nullptr) *r_exp = round_to_1 ? exponent + 1 : 0;
      return round_to_1 ? sign * pow(10.0, exponent + 1) : 0;
    }

    /** * При  необходимости установить возвращаемые величины. */
    if (r_mant != nullptr) *r_mant = mant;
    if (r_exp != nullptr)  *r_exp = exponent;
    if (r_sign != nullptr) *r_sign = sign;

    /**
     * * По мантиссе, экспоненте и знаку сформировать новое значение округлённого числа
     * и вернуть его.
     */
    long double mantissa2 = 0.0;
    real_type power = static_cast<real_type>(powl(10.0, exponent));
    for (unsigned i = 0; i < precision; ++i, power /= 10.0) {
      if (mant[i] == 0) continue;
      mantissa2 += mant[i] * power;
    }
    return static_cast<real_type>(sign > 0 ? mantissa2 : -mantissa2);
  }

  /**
   * \file
   * * \copybrief express::REAL::compare()
   */
  int REAL::compare(real_type x, unsigned precision_x, real_type y, unsigned precision_y) {
    int signx, signy;

    /**  
     * Алгоритм:
     *
     * * Проверить на исчезающе малое значение величину значения x (для double это примерно 2.23e-308).
     */
    if (abs(x) < std::numeric_limits<real_type>::min()) {
      signx = 0;
    } else {
      /** * Определить знак значения x */
      signx = x < 0 ? -1 : 1;
    }

    /** * Проверить на исчезающе малое значение величину значения y (для double это примерно 2.23e-308). */
    if (abs(y) < std::numeric_limits<real_type>::min()) {
      signy = 0;
    } else {
      /** * Определить знак значения y */
      signy = y < 0 ? -1 : 1;
    }

    /** * Сравнить знаки значений x и y, если знаки разные, сразу вернуть результат. */
    if (signx < signy) {

#ifdef TRACE_REAL
      printf("%s: sign %i < %i -> -1\n", __MYFUNCNAME__, signx, signy);
#endif

      return -1;
    }
    if (signx > signy) {

#ifdef TRACE_REAL
      printf("%s: sign %i > %i -> 1\n", __MYFUNCNAME__, signx, signy);
#endif

      return  1;
    }
    /** * Сравнить знаки значений x и y, если оба равны нулю, сразу вернуть результат. */
    if (signx == 0 && signy == 0) {

#ifdef TRACE_REAL
      printf("%s: sign %i == %i == 0 -> 0\n", __MYFUNCNAME__, signx, signy);
#endif

      return 0;
    }

    /** * Определить экспоненты значений x и y*/
    int exponentx = real_to_int(log10(abs(x)));
    int exponenty = real_to_int(log10(abs(y)));

    /** * Сравнить экспоненты значений x и y, если они не равны, сразу вернуть результат. */
    if (exponentx > exponenty) {

#ifdef TRACE_REAL
      printf("%s: (%c) xxx E %i > (%c) xxx E %i -> %i\n",
        __MYFUNCNAME__, signx ? '+' : '-', exponentx, signy ? '+' : '-',  exponenty, signx);
#endif

      return signx;
    }

    if (exponentx < exponenty) {

#ifdef TRACE_REAL
      printf("%s: (%c) xxx E %i < (%c) xxx E %i -> %i\n",
        __MYFUNCNAME__, signx ? '+' : '-', exponentx, signy ? '+' : '-',  exponenty, -signx);
#endif

      return -signx;
    }

    /** * Получить мантиссы, округлённые согласно заданной точности. */
    std::vector<unsigned>mant_x, mant_y;
    x = round(x, precision_x, &mant_x);
    y = round(y, precision_y, &mant_y);


    /** * Сравнить мантиссы, перебирая цифры до обнаружения различия. */
    for (unsigned i = 0; i < std::min(mant_x.size(), mant_y.size()); ++i) {
      unsigned digit_x = i >= mant_x.size() ? 0U : mant_x[i];
      unsigned digit_y = i >= mant_y.size() ? 0U : mant_y[i];

      if (digit_x > digit_y) {

#ifdef TRACE_REAL
        std::string sx;
        for (unsigned k = 0; k < mant_x.size(); ++k) {
          if (k == i) { sx += '['; sx += digit_x + '0'; sx += ']'; }
          else sx += mant_x[k] + '0';
        }

        std::string sy;
        for (unsigned k = 0; k < mant_y.size(); ++k) {
          if (k == i) { sy += '['; sy += digit_y + '0'; sy += ']'; }
          else sy += mant_y[k] + '0';
        }

        printf("%s: (%c) %s E %i<%u> > (%c) %s E %i<%u> -> %i\n",
          __MYFUNCNAME__, signx ? '+' : '-', sx.c_str(), exponentx, precision_x,
          signy ? '+' : '-', sy.c_str(), exponenty, precision_y, signx);
#endif
        return signx;
      }
      else if (digit_x < digit_y) {

#ifdef TRACE_REAL
        std::string sx;
        for (unsigned k = 0; k < mant_x.size(); ++k) {
          if (k == i) { sx += '['; sx += digit_x + '0'; sx += ']'; }
          else sx += mant_x[k] + '0';
        }

        std::string sy;
        for (unsigned k = 0; k < mant_y.size(); ++k) {
          if (k == i) { sy += '['; sy += digit_y + '0'; sy += ']'; }
          else sy += mant_y[k] + '0';
        }

        printf("%s: (%c) %s E %i<%u> < (%c) %s E %i<%u> -> %i\n",
          __MYFUNCNAME__, signx ? '+' : '-', sx.c_str(), exponentx, precision_x,
          signy ? '+' : '-', sy.c_str(), exponenty, precision_y, signx);
#endif
        return -signx;
      }
    }

#ifdef TRACE_REAL
      printf("%s: (%c) xxx E %i == (%c) xxx E %i -> 0\n",
        __MYFUNCNAME__, signx ? '+' : '-', exponentx, signy ? '+' : '-',  exponenty);
#endif


    return 0;
  }

  /**
   * \file
   * Конструкторы (неопределённого значения, копирующий (из базового и дочерних
   * типов) и конструктор из значения) и оператор присваивания:
   */

#if 0
  /**
   * \file
   * * \copybrief express::REAL::REAL()
   */
  REAL::REAL() {
    append_to_parent_type_list("REAL");
    _r = 0.0;
#ifdef TRACE_REAL
    printf("%s\n", __MYFUNCNAME__);
#endif
  }

  /**
   * \file
   * * \copybrief express::REAL::REAL(const express::REAL&,unsigned)
   */
  REAL::REAL(const REAL& src, unsigned precision) : NUMBER() {
    append_to_parent_type_list("REAL");
    precision_spec = precision;
    if (!src.is_determinated()) {
      determinated = false;
      _r = 0.0;
    } else {
      determinated = true;
      if (precision_spec == src.get_number_precision()) {
        _r = src.get_number_value();
      } else {
        _r = round(src.get_number_value(), precision_spec);
      }
    }
#ifdef TRACE_REAL
    printf("%s: %s <- %s\n", __MYFUNCNAME__, print_value().c_str(), src.print_value().c_str());
#endif
  }

  /**
   * \file
   * * \copybrief express::REAL::REAL(express::real_type,unsigned)
   */
  REAL::REAL(real_type src, unsigned precision) : NUMBER() {
    append_to_parent_type_list("REAL");
    precision_spec = precision;
    determinated = true;
    _r = round(src, precision_spec);
#ifdef TRACE_REAL
    printf("%s: %s (%.20e) <- %.20e\n", __MYFUNCNAME__, print_value().c_str(), _r, src);
#endif
  }
#endif
  /**
   * \file
   * * \copybrief express::REAL::operator=()
   */
  REAL& REAL::operator=(const REAL& rhs) {
    if (this != std::addressof(rhs)) {
      if (rhs.is_determinated()) {
        determinated = true;
        if (precision_spec == rhs.get_number_precision()) {
          _r = rhs.get_number_value();
        } else {
          _r = round(rhs.get_number_value(), precision_spec);
        }
      }
      else {
        determinated = false;
        _r = 0;
      }
    }

#ifdef TRACE_REAL
    printf("%s: %s := %s\n", __MYFUNCNAME__, print_value().c_str(), rhs.print_value().c_str());
#endif

    return *this;
  }

  /**
   * \file
   * Получение значения и свойств типа:
   */

  /**
   * \file
   * * \copybrief express::REAL::get_number_value() const
   */
  number_type REAL::get_number_value() const {
    if (!determinated) {
      throw exception{__MYFUNCNAME__, "can not get indeterminate (?) value"};
    }
    return _r;
  }

  /**
   * \file
   * * \copybrief express::REAL::get_number_precision() const
   */
  unsigned REAL::get_number_precision() const {
    return precision_spec;
  }

  /**
   * \file
   * * \copybrief express::REAL::objtype() const
   */
  GENERIC::OBJTYPE REAL::objtype() const {
    return OBJTYPE::OBJ_SIMPLE | OBJTYPE::OBJ_REAL;
  }

  /**
   * \file
   * Арифметические операторы:
   */

  /**
   * \file
   * * \copybrief express::REAL::operator+() const
   */
  REAL REAL::operator+() const {
    REAL r;
    if (determinated) {
      r = _r;
    }
    return r;
  }

  /**
   * \file
   * * \copybrief express::REAL::operator-() const
   */
  REAL REAL::operator-() const {
    REAL r;
    if (determinated) {
      r = -_r;
    }
    return r;
  }

  /**
   * \file
   * * \copybrief express::REAL::operator+(express::real_type) const
   */
  REAL REAL::operator+(real_type rhs) const {
    REAL out;
    if (determinated) {
      out = get_number_value() + rhs;
    }

#ifdef TRACE_REAL
    printf("%s: %s = %s + %f\n", __MYFUNCNAME__, out.print_value().c_str(), print_value().c_str(), rhs);
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::REAL::operator+(const express::INTEGER&,express::real_type)
   */
  REAL operator+(const INTEGER& lhs, real_type rhs) {
    REAL out;
    if (lhs.is_determinated()) {
      out = lhs.get_number_value() + rhs;
    }

#ifdef TRACE_REAL
    printf("%s: %s = %s + %f\n", __MYFUNCNAME__, out.print_value().c_str(), x.print_value().c_str(), y);
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::REAL::operator-(express::real_type) const
   */
  REAL REAL::operator-(real_type rhs) const {
    REAL out;
    if (determinated) {
      out = get_number_value() - rhs;
    }

#ifdef TRACE_REAL
    printf("%s: %s = %s - %f\n", __MYFUNCNAME__, out.print_value().c_str(), print_value().c_str(), rhs);
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::REAL::operator-(const express::INTEGER&,express::real_type)
   */
  REAL operator-(const INTEGER& lhs, real_type rhs) {
    REAL out;
    if (lhs.is_determinated()) {
      out = lhs.get_number_value() - rhs;
    }

#ifdef TRACE_REAL
    printf("%s: %s = %s + %f\n", __MYFUNCNAME__, out.print_value().c_str(), x.print_value().c_str(), y);
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::REAL::operator*(express::real_type) const
   */
  REAL REAL::operator*(real_type rhs) const {
    REAL out;
    if (determinated) {
      out = get_number_value() * rhs;
    }

#ifdef TRACE_REAL
    printf("%s: %s = %s * %f\n", __MYFUNCNAME__, out.print_value().c_str(), print_value().c_str(), rhs);
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::REAL::operator*(const express::INTEGER&,express::real_type)
   */
  REAL operator*(const INTEGER& lhs, real_type rhs) {
    REAL out;
    if (lhs.is_determinated()) {
      out = lhs.get_number_value() * rhs;
    }

#ifdef TRACE_REAL
    printf("%s: %s = %s * %f\n", __MYFUNCNAME__, out.print_value().c_str(), x.print_value().c_str(), y);
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::REAL::operator/(express::real_type) const
   */
  REAL REAL::operator/(real_type rhs) const {
    REAL out;
    if (determinated) {
      out = get_number_value() / rhs;
    }

#ifdef TRACE_REAL
    printf("%s: %s = %s / %f\n", __MYFUNCNAME__, out.print_value().c_str(), print_value().c_str(), rhs);
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::REAL::operator/(const express::INTEGER&,express::real_type)
   */
  REAL operator/(const INTEGER& lhs, real_type rhs) {
    REAL out;
    if (lhs.is_determinated()) {
      out = lhs.get_number_value() / rhs;
    }

#ifdef TRACE_REAL
    printf("%s: %s = %s / %f\n", __MYFUNCNAME__, out.print_value().c_str(), x.print_value().c_str(), y);
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::REAL::operator>>(express::real_type)
   */
  INTEGER REAL::operator>>(real_type rhs) {
    INTEGER out;
    if (determinated) {
      integer_type a = objtype() && OBJTYPE::OBJ_INTEGER ?  get_integer_value() : real_to_integer(get_number_value());
      out = a / real_to_integer(rhs);
    }

#ifdef TRACE_REAL
    printf("%s: %s = %s DIV %f\n", __MYFUNCNAME__, out.print_value().c_str(), print_value().c_str(), rhs);
#endif

    return out;
  }

  /**
   * \file
   * * \copybrief express::REAL::operator%(express::real_type)
   */
  INTEGER REAL::operator%(real_type rhs) {
    INTEGER out;
    if (determinated) {
      integer_type a = objtype() && OBJTYPE::OBJ_INTEGER ?  get_integer_value() : real_to_integer(get_number_value());
      out = a % real_to_integer(rhs);
    }

#ifdef TRACE_REAL
    printf("%s: %s = %s MOD %f\n", __MYFUNCNAME__, out.print_value().c_str(), print_value().c_str(), rhs);
#endif

    return out;
  }
}
