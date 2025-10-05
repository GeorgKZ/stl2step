/**
 * \file
 *
 * \brief Заголовочный файл с описанием простых типов данных языка EXPRESS (ГОСТ Р ИСО 10303-11, 8.1; ГОСТ Р ИСО 10303-21, 6.3)
 *
 * <B>ГОСТ Р ИСО 10303-11, 8.1 Простые типы данных</B><BR>
 * Простые типы данных определяют области определения элементарных единиц данных в языке
 * EXPRESS. To есть они не могут быть разделены на элементы, распознаваемые в языке EXPRESS.
 * Простыми типами данных являются <B>NUMBER</B> (числовой), <B>REAL</B> (действительный), <B>INTEGER</B> (целочисленный),
 * <B>STRING</B> (строковый), <B>BOOLEAN</B> (булев), <B>LOGICAL</B> (логический) и <B>BINARY</B> (двоичный).
 * <BR>
 * <B>ГОСТ Р ИСО 10303-21, 6.3 Кодирование простых типов данных</B>
 * В структурах обмена используют кодирование шести простых типов данных: целое (integer),
 * вещественно (real), строка (string), имя экземпляра объекта (entity instance name), перечисление
 * (enumeration) и двоичное (binary).
 * </BLOCKQUOTE>
 */

#include "precision.h"

namespace express {

/** 
 * \brief Простой тип <B>\ref NUMBER</B> - Числовой тип данных (ГОСТ Р ИСО 10303-11, 8.1.1)
 *
 * <B>8.1.1 Числовой тип данных</B><BR>
 * Областью определения типа данных <B>\ref NUMBER</B> являются все числовые значения в языке EXPRESS.
 * Числовой тип данных должен использоваться, когда не важно более конкретное представление чисел.
 */
class NUMBER : public SIMPLE {

/**
 * <B>ISO 10303-21, 10.1.1.7 Тип данных \ref NUMBER (числовой)</B><BR>
 * Значения данных в EXPRESS типа <B>\ref NUMBER</B> должны быть отображены в структуру обмена
 * как вещественный тип данных. Формирование вещественного типа данных — по 6.3.2
 */

};

/** 
 * \brief Простой тип <B>\ref REAL</B> - Действительное число (ГОСТ Р ИСО 10303-11, 8.1.2)
 *
 * <B>8.1.2 Действительный тип данных</B><BR>
 * Областью определения типа данных <B>\ref REAL</B> являются все рациональные, иррациональные и
 * экспоненциально представленные числа. Данный тип данных является конкретизацией
 * типа данных <B>\ref NUMBER</B>.
 */
class REAL : public NUMBER {
  private:

    double x_;

  public:

    REAL() { x_ = 0; }
    REAL(const double v) { x_ = v;}

   /**
    * \brief Вывести значение типа (ГОСТ Р ИСО 10303-21, 6.3.2, 10.1.1.5).
    *
    * <B>6.3.2 Вещественное (\ref REAL)</B><BR>
    * Вещественное должно быть закодировано, как указано в таблице 2:<BR>
    * <TT>REAL = [SIGN] DIGIT { DIGIT } “.” { DIGIT } [ “E” [SIGN] DIGIT { DIGIT } ] .</TT><BR>
    * Код должен состоять из десятичной мантиссы, за которой (необязательно) следует десятичный
    * показатель степени. Десятичная мантисса состоит в порядке следования из необязательного
    * <I>знака плюс</I> “+” или <I>минус</I> “-”, последовательности из одной или более цифр,
    * <I>точки</I> “.”, последовательности из нуля или нескольких цифр. Десятичный показатель
    * степени состоит из <I>прописной буквы E</I>, за которой следует необязательный <I>знак
    * плюс</I> “+” или <I>минус</I> “—” с одной или несколькими цифрами.
    *
    * <B>10.1.1.5 Тип данных \ref REAL (вещественный)</B><BR>
    * Значения данных в EXPRESS типа \ref REAL должны быть отображены в структуру обмена как
    * вещественный тип данных. В 6.3.2 описано содержание вещественного типа данных.
    */
   virtual std::string print_value(void) const {
      char Buff[50];

#if defined(_MSC_VER)
      sprintf_s(Buff, sizeof(Buff), "%.7f", x_);
#elif defined(__GNUC__) || defined(__DOXYGEN__)
      sprintf(Buff, "%.7f", x_);
#else
#error Unknown C++ compiler
#endif

      return std::string(Buff);
    }

    /** \brief Получить значение типа */
    double getval(void) const { return x_; }

    /** \brief Умножение типов */
    const REAL operator*(const REAL& x) const {
      return REAL(x.x_ * x_);
    }

    /** \brief Сложение типов */
    const REAL operator+(const REAL& x) const {
      return REAL(x.x_ + x_);
    }

    bool operator==(const REAL& r) const { return fabs(this->x_ - r.x_) < EPSILON_X; }
    bool operator>(const REAL& r)  const { return this->x_ > r.x_; }
    bool operator<(const REAL& r)  const { return !(*this >= r); }
    bool operator!=(const REAL& r) const { return !(*this == r); }
    bool operator>=(const REAL& r) const { return (*this > r || *this == r); }
    bool operator<=(const REAL& r) const { return !(*this > r); }
};

/** 
 * \brief Простой тип <B>\ref INTEGER</B> - Целое число (ГОСТ Р ИСО 10303-11, 8.1.3)
 *
 * <B>8.1.3 Целочисленный тип данных</B><BR>
 * Областью определения типа данных <B>\ref INTEGER</B> являются все целые числа. Данный тип данных
 * является конкретизацией типа данных <B>\ref REAL</B>.
 */
class INTEGER : public NUMBER {

private:

  long long int x_;

public:

  INTEGER() { x_ = 0; }
  INTEGER(const int v) { x_ = v;}
  INTEGER(const size_t v) { x_ = v; }
  INTEGER(const long long v) { x_ = v; }

 /**
  * \brief Вывод значения типа (ГОСТ Р ИСО 10303-21, 6.3.1, 10.1.1.1).
  *
  * <B>6.3.1 Целое (Integer)</B><BR>
  * Целое должно быть закодировано как последовательность из одной или нескольких цифр,
  * согласно таблице 2, которой может (но необязательно) предшествовать <I>знак плюс</I> “+” или
  * <I>минус</I> “—”. Целое должно быть выражено в десятичном основании. Если целое не имеет знака,
  * его считают положительным.
  *
  * <B>10.1.1.1 Тип данных \ref INTEGER (целое)</B><BR>
  * Значения данных в EXPRESS типа \ref INTEGER отображаются в структуру обмена как целочисленный
  * тип данных. Состав целочисленного типа данных описан в 6.3.1.
  */
  virtual std::string print_value(void) const {
    std::stringstream ss;
    ss << x_;
    return ss.str();
  }

  long long int getval(void) const { return x_; }

  /** \brief Умножение типов */
  const INTEGER operator*(const INTEGER& x) const {
    return INTEGER(x.x_ * x_);
  }

  /** \brief Сложение типов */
  const INTEGER operator+(const INTEGER& x) const {
    return INTEGER(x.x_ + x_);
  }

  bool operator==(const INTEGER& i) const { return this->getval() == i.getval(); }
  bool operator> (const INTEGER& i) const { return this->getval() > i.getval(); }
  bool operator< (const INTEGER& i) const { return !(*this >= i); }
  bool operator!=(const INTEGER& i) const { return !(*this == i); }
  bool operator>=(const INTEGER& i) const { return (*this > i || *this == i); }
  bool operator<=(const INTEGER& i) const { return !(*this > i); }
};

/** 
 * \brief Простой тип <B>\ref STRING</B> - Строка (ГОСТ Р ИСО 10303-11, 8.1.6)
 *
 * <B>ISO 10303-11, 8.1.6 Строковый тип данных</B><BR>
 * Областью определения типа данных <B>STRING</b> являются последовательности символов. Символами,
 * допустимыми в строковых значениях, являются символы ИСО/МЭК 10646-1 из позиций 09, 0A, 0D и
 * графические символы, расположенные в позициях от 20 до 7Е и от А0 до 10FFFE.
 */
class STRING : public SIMPLE {

private:

  std::string x_;

public:

  /** \brief Конструктор по умолчанию */
  STRING() {
  }

  /** \brief Конструктор из строки std::string */
  STRING(const std::string &v) : x_(v) {
  }

  /** \brief Конструктор из строки char* */
  STRING(const char *v) : x_(v) {
  }

 /**
  * \brief Вывод значения типа (ГОСТ Р ИСО 10303-21, 6.3.3, 10.1.1.2)
  *
  * <B>6.3.3 Строка (String)</B><BR>
  * Строка должна быть закодирована как <I>апостроф</I> “'”, за которым следует нуль или несколько
  * 8-битных байтов, и заканчиваться “'”. Нулевая строка (строка нулевой длины) должна быть
  * закодирована последовательностью из двух <I>апострофов</I> “''”. Внутри строки единичный <I>апостроф</I>
  * должен быть закодирован как два последовательных <I>апострофа</I>. Внутри строки единичная <I>косая обратная
  * черта</I> “\” должна быть закодирована как две <I>косые обратные черты</I> “\\” 8-битные байты,
  * разрешенные внутри строки, являются десятичными эквивалентами чисел от 32 до 126 (включительно)
  * по ИСО/М ЭК 8859-1, которые определяют графические символы основного алфавита.
  *
  * <B>10.1.1.2 Тип данных \ref STRING (строковый)</B><BR>
  * Значения данных в EXPRESS типа <B>\ref STRING</B> отображаются в структуру обмена как строковый
  * тип данных. Состав строкового типа данных описан в 6.3.3.
  */
  virtual std::string print_value(void) const {
    std::stringstream s;
    if (x_.empty()) {
      s << "''";
    } else {
      s << "'" << x_ << "'";
    }
    return s.str();
  }

  /** \brief Значение пустое? */
  bool is_empty() const {
    return x_.empty();
  }

  /** \brief Получитьь значение. */
  const char* getval() const {
    return x_.c_str();
  }
};

/** 
 * \brief Простой тип <B>\ref BOOLEAN</B> - булево значение (ГОСТ Р ИСО 10303-11, 8.1.5)
 *
 * <B>8.1.5 Булев тип данных</B><BR>
 * Областью определения типа данных <B>\ref BOOLEAN</B> являются два литерала: <B>TRUE</B> и <B>FALSE</B>. Тип данных
 * <B>\ref BOOLEAN</B> является конкретизацией типа данных <B>\ref LOGICAL</B>.<BR>
 * Для значений типа данных <B>\ref BOOLEAN</B> установлен тот же порядок, что и для значений типа данных
 * <B>\ref LOGICAL</B><B>: FALSE < TRUE</B>.
 */
class BOOLEAN : public SIMPLE {

public:

  enum class value {
    FALSE = 0,
    TRUE = 1
  };

private:

  value x_;

public:

  BOOLEAN() { x_ = value::FALSE;}
  BOOLEAN(value v) { x_ = v;}

  /** 
   * \brief Вывод значения типа (ГОСТ Р ИСО 10303-21, 10.1.1.3).
   *
   * <B>10.1.1.3 Тип данных boolean (булевский)</B><BR>
   * Значения данных в EXPRESS типа <B>\ref BOOLEAN</B> отображаются в структуру обмена как данные
   * перечисляемого типа. Состав данных перечисляемого типа описан в 6.3.5. EXPRESS-данные типа
   * \ref BOOLEAN должны быть обработаны как предопределенный перечисляемый тип данных со значением,
   * кодированным графическим символом <B>“Т”</B> или <B>“F”</B>. Эти значения соответствуют true (истина)
   * и false (ложь).
   */
  virtual std::string print_value(void) const {
    std::stringstream s;
    switch(x_) {
    case value::FALSE:
      s << ".F.";
      break;
   case value::TRUE:
      s << ".T.";
      break;
   default:
      s << "";
      break;
    }
    return s.str();
  }

  BOOLEAN operator!() const {
    return x_ == value::FALSE ? value::TRUE : value::FALSE;
  }

  bool getval() const { return x_ == value::TRUE; }

  bool operator==(const BOOLEAN& b) const { return this->getval() == b.getval(); }
  bool operator!=(const BOOLEAN& b) const { return !(*this == b); }
};

const BOOLEAN::value BTrue = BOOLEAN::value::TRUE;
const BOOLEAN::value BFalse = BOOLEAN::value::FALSE;

/** 
 * \brief Простой тип <B>\ref LOGICAL</B> - логическое значение (ISO 10303-11, 8.1.4)
 *
 * <B>8.1.4 Логический тип данных</B><BR>
 * Областью определения типа данных <B>LOGICAL</B> являются три литерала: <B>TRUE</B>, <B>FALSE</B> и <B>UNKNOWN</B>.
 * Значения логического типа данных упорядочены следующим образом: <B>FALSE \< UNKNOWN \< TRUE.</B>
 * Тип данных <B>LOGICAL</B> совместим с типом данных <B>BOOLEAN</B>, за исключением того, что
 * булевой переменной не может быть присвоено значение <B>UNKNOWN</B>.
 */
class LOGICAL : public SIMPLE {
public:

  enum class value {
    FALSE,
    UNKNOWN,
    TRUE,
  };

private:

  value x_;

public:

  LOGICAL() { x_ = value::UNKNOWN;}
  LOGICAL(value v) { x_ = v;}

  /**
   * \brief Вывод значения типа (ГОСТ Р ИСО 10303-21, 10.1.1.4)
   *
   * <B>10.1.1.4 Тип данных \ref LOGICAL (логический)</B><BR>
   * Значения данных в EXPRESS типа \ref LOGICAL отображаются в структуру обмена как данные
   * перечисляемого типа. В 6.3.5 описан состав перечисляемого типа данных. EXPRESS-данные типа
   * \ref LOGICAL должны быть обработаны как предопределенный перечисляемый тип данных со значением,
   * кодированным графическими символами “Т”, “F” или “U ”. Эти значения соответствуют true
   * (истина), false (ложь) и unknown (неизвестно).
   */
  virtual std::string print_value(void) const {
    std::stringstream s;
    switch(x_) {
    case value::FALSE:
      s << ".F.";
      break;
    case value::UNKNOWN:
      s << ".U.";
      break;
    case value::TRUE:
      s << ".T.";
      break;
    default:
      s << "";
      break;
    }
    return s.str();
  }
};

}
