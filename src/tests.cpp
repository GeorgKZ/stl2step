/**
 * \file
 *
 * \brief Файл с определениями функции тестирования
 *
 * Здесь определены функции тестирования встроенных функций языка EXPRESS.
 */

#include "stdafx.h"
#include "express.h"
#include "express_sugar.h"


using namespace express;

#if defined(_MSC_VER)
unsigned short set_color(int color);
void restore_color(unsigned short attr);
#elif defined(__GNUC__)
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#elif
#error Unknown C++ compiler
#endif

/** \brief Коды завершения теста. */
enum
#if !defined(__DOXYGEN__)
      class
#endif 
  test_t {
  /** \brief Тест завершён без ошибок. */
  TEST_OK,
  /** \brief Во время выпонения теста были одна или больше ошибок. */
  TEST_ERR,
  /** \brief Тест не выполнялся (ещё не реализован). */
  TEST_NOT_IMPL,
};

static const size_t max_msg_len = 70;

static void print_res(bool details, const char *msg, test_t ok) {

  if (details == false && *msg != '\0') return;
  if (details == true  && *msg == '\0') return;

  assert(strlen(msg) < max_msg_len);

  size_t len;

  if (*msg == '\0') {
    len = details ? max_msg_len : 0U;
  } else {
    printf("%s", msg);
    len = max_msg_len - strlen(msg);
  }
  for (size_t i = 0; i < len; ++i) {
    printf(" ");
  }
  printf("- ");

  int color;
  switch(ok) {
    case test_t::TEST_OK:
      color = 32; break;
    case test_t::TEST_ERR:
      color = 31; break;
    case test_t::TEST_NOT_IMPL:
      color = 33; break;
    default:
      color = 0; break;
  };

#if defined(_MSC_VER)
  unsigned short old = set_color(color);
#elif defined(__GNUC__) || defined(__DOXYGEN__)
  printf("\x1b[%im", color);
#elif
#error Unknown C++ compiler
#endif

  switch(ok) {
    case test_t::TEST_OK:
      printf("OK"); break;
    case test_t::TEST_ERR:
      printf("BAD"); break;
    case test_t::TEST_NOT_IMPL:
      printf("NOT YET IMPLEMENTED"); break;
    default:
      break;
  };

#if defined(_MSC_VER)
  restore_color(old);
#elif defined(__GNUC__) || defined(__DOXYGEN__)
  printf("\x1b[m");
#elif
#error Unknown C++ compiler
#endif
  printf("\n");
}

static void print_title(bool details, const char *name) {

  assert(strlen(name) < max_msg_len);

#if defined(_MSC_VER)
  unsigned short old = set_color(33);
#elif defined(__GNUC__) || defined(__DOXYGEN__)
  printf("\x1b[33m");
#elif
#error Unknown C++ compiler
#endif
  printf("%s", name);
  size_t len;
  if (details) {
    len = max_msg_len + 4 - strlen(name);
  } else {
    len = max_msg_len - strlen(name);
  }
  for (size_t i = 0; i < len; ++i) {
    if (details) printf("-");
    else printf(" ");
  }
#if defined(_MSC_VER)
  restore_color(old);
#elif defined(__GNUC__) || defined(__DOXYGEN__)
  printf("\x1b[m");
#elif
#error Unknown C++ compiler
#endif
  if (details) printf("\n");
}

static void print_double(const char* msg) {
  if (msg != nullptr && strlen(msg) != 0) {

    assert(strlen(msg) + 5 < max_msg_len);

    printf("=== %s ", msg);
    for (size_t i = 0; i < max_msg_len - 5 - strlen(msg); ++i) {
      printf("=");
    }
  }
  else {
    for (size_t i = 0; i < max_msg_len; ++i) {
      printf("=");
    }
  }
  printf("\n");
}

static void unitest(bool check, bool details, const char* name, test_t& err) {
  if (check) {
    print_res(details, name, test_t::TEST_OK);
  } else {
    print_res(details, name, test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }
}

static bool test_number_init(bool details) {
  print_title(details, "NUMBER");
  test_t err = test_t::TEST_OK;
  NUMBER n;

  unitest(!n.is_determinated(), details, "Default definition", err);

  n = NUMBER(12345.6789);
  unitest((n == 12345.6789).is_true(), details, "NUMBER := NUMBER", err);

  n = REAL(12345.6789);
  unitest((n == 12345.6789).is_true(), details, "NUMBER := REAL", err);

  n = INTEGER(12345);
  unitest((n == 12345).is_true(), details, "NUMBER := INTEGER", err);

  n = number_type(12345.6789);
  unitest((n == 12345.6789).is_true(), details, "NUMBER := number_type", err);

  n = static_cast<int>(12345);
  unitest((n == 12345).is_true(), details, "NUMBER := int", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_real_init(bool details) {
  print_title(details, "REAL");
  test_t err = test_t::TEST_OK;
  REAL r;

  unitest(!r.is_determinated(), details, "Default definition", err);

  r = REAL(12345.6789);
  unitest((r == 12345.6789).is_true(), details, "REAL := REAL", err);

  r = INTEGER(12345);
  unitest((r == 12345).is_true(), details, "REAL := INTEGER", err);

  r = static_cast<real_type>(12345.6789);
  unitest((r == 12345.6789).is_true(), details, "REAL := real_type", err);

  r = static_cast<int>(12345);
  unitest((r == 12345).is_true(), details, "REAL := int", err);

  /* Пример из 12.1 */
  REAL r0(PREC(6));
  REAL x1 = 0, x2 = 10, y1 = 0, y2 = 11, z1 = 0, z2 = 12;

  r0 = SQRT((x2-x1) * (x2-x1) + (y2-y1) * (y2-y1) + (z2-z1) * (z2-z1));
  unitest((r0 == 19.1050).is_true(), details, "Precision check from ISO 10303-11, 12.1", err);

  REAL r1(PREC(8));
  r1 = 1234567890123.4;
  unitest((r1 == 1234567900000.0).is_true(), details, "REAL(8) := ...", err);

  REAL r3(PREC(8));
  r3 = -3210987650987.6;
  unitest((r3 == -3210987600000.0).is_true(), details, "REAL(8) := -...", err);

  REAL r2{ PREC{4} };
  r2 = 12.345678901234;
  unitest((r2 == 12.35).is_true(), details, "REAL(4) := ...", err);

  REAL r4(PREC(7));
  r4 = -321098760987.6;
  unitest((r4 == -321098800000.0).is_true(), details, "REAL(7) := ...", err);

  REAL r4x{ PREC(REAL::precision_max) };
  r4x = -5432109876098765432101234567.6;
  unitest((r4x == -5432109876098800000000000000.0).is_true(), details, "REAL := ... (maximum precision)", err);

  REAL r5 = 12345;
  unitest((r5 == 12345).is_true(), details, "REAL := ... (default precision)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_integer_init(bool details) {
  print_title(details, "INTEGER");
  test_t err = test_t::TEST_OK;
  INTEGER i;

  unitest(EXISTS(i).is_false(), details, "Default definition", err);

  i = INTEGER(123456);
  unitest((i == 123456).is_true(), details, "INTEGER := INTEGER", err);

  i = static_cast<integer_type>(123456);
  unitest((i == 123456).is_true(), details, "INTEGER := integer_type", err);

  i = static_cast<int>(123456);
  unitest((i == 123456).is_true(), details, "INTEGER := int", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}


static bool test_logical_init(bool details) {
  print_title(details, "LOGICAL ");
  test_t err = test_t::TEST_OK;
  LOGICAL l, l1, l2;
  BOOLEAN bt(TRUE), bf(FALSE);

  unitest(!l.is_determinated(), details, "Default definition", err);

  l = LOGICAL(TRUE); l1 = LOGICAL(FALSE); l2 = LOGICAL(UNKNOWN);
  unitest(l.is_true() && l1.is_false() && l2.is_unknown(), details, "LOGICAL := LOGICAL", err);

  l1 = bt; l2 = bf;
  unitest(l1.is_true() && l2.is_false(), details, "LOGICAL := BOOLEAN", err);

  l = LOGICAL::TRUE;
  unitest(l.is_true(), details, "LOGICAL := LOGICAL::TRUE", err);

  l = LOGICAL::FALSE;
  unitest(l.is_false(), details, "LOGICAL := LOGICAL::FALSE", err);

  l = LOGICAL::UNKNOWN;
  unitest(l.is_unknown(), details, "LOGICAL := LOGICAL::UNKNOWN", err);

  l = BOOLEAN::TRUE;
  unitest(l.is_true(), details, "LOGICAL := BOOLEAN::TRUE", err);

  l = BOOLEAN::FALSE;
  unitest(l.is_false(), details, "LOGICAL := BOOLEAN::FALSE", err);

  l = TRUE;
  unitest(l.is_true(), details, "LOGICAL := TRUE", err);

  l = FALSE;
  unitest(l.is_false(), details, "LOGICAL := FALSE", err);

  l = UNKNOWN;
  unitest(l.is_unknown(), details, "LOGICAL := UNKNOWN", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_boolean_init(bool details) {
  print_title(details, "BOOLEAN ");
  test_t err = test_t::TEST_OK;
  BOOLEAN b, b1;

  unitest(!b.is_determinated(), details, "Default definition", err);

  b = BOOLEAN(TRUE); b1 = BOOLEAN(FALSE);
  unitest(b.is_true() && b1.is_false(), details, "BOOLEAN := BOOLEAN", err);

  b = BOOLEAN::TRUE;
  unitest(b.is_true(), details, "BOOLEAN := BOOLEAN::TRUE", err);

  b = BOOLEAN::FALSE;
  unitest(b.is_false(), details, "BOOLEAN := BOOLEAN::FALSE", err);

  b = TRUE;
  unitest(b.is_true(), details, "BOOLEAN := TRUE", err);

  b = FALSE;
  unitest(b.is_false(), details, "BOOLEAN := FALSE", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_string_init(bool details) {
  print_title(details, "STRING ");
  test_t err = test_t::TEST_OK;
  STRING s;

  unitest(!s.is_determinated(), details, "Default definition", err);

  s = STRING("");
  unitest((s == STRING("")).is_true(), details, "STRING := STRING (empty)", err);

  s = STRING("abcd12345");
  unitest((s == STRING("abcd12345")).is_true(), details, "STRING := STRING", err);

  s = "12345abcd";
  unitest((s == STRING("12345abcd")).is_true(), details, "STRING := \"XXXXX\"", err);

  s = "";
  unitest((s == STRING("")).is_true(), details, "STRING := \"\"", err);

  s = STRING("abcd12345"); s[1] = 'A';
  unitest((s == STRING("Abcd12345")).is_true(), details, "STRING[x] := 'X'", err);

//  s = STRING("abcd12345"); s[{2, 4}] = "BCD";
//  unitest((s == STRING("aBCD12345")).is_true(), details, "STRING[x] := 'X'", err);


  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_binary_init(bool details) {
  print_title(details, "BINARY ");

  test_t err = test_t::TEST_NOT_IMPL;

  /**
   * \file
   * \todo Добавить тестирование инициализации BINARY
   */

  print_res(details, "TEST", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_number_rel_eq(bool details) {
  print_title(details, "NUMBER RELATIONS '=' ");
  test_t err = test_t::TEST_OK;

  /* равно NUMBER */

  unitest((NUMBER(1.2) == NUMBER(1.2)).is_true() &&
          (NUMBER(1.2) == NUMBER(3.5)).is_false() &&
          (NUMBER(3.5) == NUMBER(1.2)).is_false(), details, "NUMBER = NUMBER", err);
  unitest((NUMBER() == NUMBER(1.2)).is_unknown(), details, "? (NUMBER) = NUMBER", err);
  unitest((NUMBER(1.2) == NUMBER()).is_unknown(), details, "NUMBER = ? (NUMBER)", err);
  unitest((NUMBER() == NUMBER()).is_unknown(), details, "? (NUMBER) = ? (NUMBER)", err);

  /* равно REAL */

  unitest((NUMBER(1.2) == REAL(1.2)).is_true() &&
          (NUMBER(1.2) == REAL(3.5)).is_false() &&
          (NUMBER(3.5) == REAL(1.2)).is_false(), details, "NUMBER = REAL", err);
  unitest((NUMBER() == REAL(1.2)).is_unknown(), details, "? (NUMBER) = REAL", err);
  unitest((NUMBER(1.2) == REAL()).is_unknown(), details, "NUMBER = ? (REAL)", err);
  unitest((NUMBER() == REAL()).is_unknown(), details, "? (NUMBER) = ? (REAL)", err);

  unitest((REAL(1.2) == NUMBER(1.2)).is_true() &&
          (REAL(1.2) == NUMBER(3.5)).is_false() &&
          (REAL(3.5) == NUMBER(1.2)).is_false(), details, "REAL = NUMBER", err);
  unitest((REAL() == NUMBER(1.2)).is_unknown(), details, "? (REAL) = NUMBER", err);
  unitest((REAL(1.2) == NUMBER()).is_unknown(), details, "REAL = ? (NUMBER)", err);
  unitest((REAL() == NUMBER()).is_unknown(), details, "? (REAL) = ? (NUMBER)", err);

  /* равно INTEGER */

  unitest((NUMBER(1) == INTEGER(1)).is_true() &&
          (NUMBER(1) == INTEGER(3)).is_false() &&
          (NUMBER(3) == INTEGER(1)).is_false(), details, "NUMBER = INTEGER", err);
  unitest((NUMBER() == INTEGER(1)).is_unknown(), details, "? (NUMBER) = INTEGER", err);
  unitest((NUMBER(1.2) == INTEGER()).is_unknown(), details, "NUMBER = ? (INTEGER)", err);
  unitest((NUMBER() == INTEGER()).is_unknown(), details, "? (NUMBER) = ? (INTEGER)", err);

  unitest((INTEGER(1) == NUMBER(1)).is_true() &&
          (INTEGER(1) == NUMBER(3)).is_false() &&
          (INTEGER(3) == NUMBER(1)).is_false(), details, "INTEGER = NUMBER", err);
  unitest((INTEGER() == NUMBER(1)).is_unknown(), details, "? (INTEGER) = NUMBER", err);
  unitest((INTEGER(1) == NUMBER()).is_unknown(), details, "INTEGER = ? (NUMBER)", err);
  unitest((INTEGER() == NUMBER()).is_unknown(), details, "? (INTEGER) = ? (NUMBER)", err);

  /* равно real_type */

  unitest((NUMBER(1.2) == static_cast<real_type>(1.2)).is_true() &&
          (NUMBER(1.2) == static_cast<real_type>(2.2)).is_false() &&
          (NUMBER(2.2) == static_cast<real_type>(1.2)).is_false(), details, "NUMBER = real_type", err);
  unitest((NUMBER() == static_cast<real_type>(1.2)).is_unknown(), details, "? (NUMBER) = real_type", err);

  unitest((static_cast<real_type>(1.2) == NUMBER(1.2)).is_true() &&
          (static_cast<real_type>(2.2) == NUMBER(1.2)).is_false() &&
          (static_cast<real_type>(1.2) == NUMBER(2.2)).is_false(), details, "real_type = NUMBER", err);
  unitest((static_cast<real_type>(1.2) == NUMBER()).is_unknown(), details, "real_type = ? (NUMBER)", err);

  /* равно integer_type */

  unitest((NUMBER(1) == static_cast<integer_type>(1)).is_true() &&
          (NUMBER(1) == static_cast<integer_type>(2)).is_false() &&
          (NUMBER(2) == static_cast<integer_type>(1)).is_false(), details, "NUMBER = integer_type", err);
  unitest((NUMBER() == static_cast<integer_type>(1)).is_unknown(), details, "? (NUMBER) = integer_type", err);

  unitest((static_cast<integer_type>(1) == NUMBER(1)).is_true() &&
          (static_cast<integer_type>(2) == NUMBER(1)).is_false() &&
          (static_cast<integer_type>(1) == NUMBER(2)).is_false(), details, "integer_type = NUMBER", err);
  unitest((static_cast<integer_type>(1) == NUMBER()).is_unknown(), details, "integer_type = ? (NUMBER)", err);

  /* равно int */

  unitest((NUMBER(1) == static_cast<int>(1)).is_true() &&
          (NUMBER(1) == static_cast<int>(2)).is_false() &&
          (NUMBER(2) == static_cast<int>(1)).is_false(), details, "NUMBER = int", err);
  unitest((NUMBER() == static_cast<int>(1)).is_unknown(), details, "? (NUMBER) = int", err);

  unitest((static_cast<int>(1) == NUMBER(1)).is_true() &&
          (static_cast<int>(2) == NUMBER(1)).is_false() &&
          (static_cast<int>(1) == NUMBER(2)).is_false(), details, "int = NUMBER", err);
  unitest((static_cast<int>(1) == NUMBER()).is_unknown(), details, "int = ? (NUMBER)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_number_rel_neq(bool details) {
  print_title(details, "NUMBER RELATIONS '<>' ");
  test_t err = test_t::TEST_OK;

  /* не равно NUMBER */

  unitest((NUMBER(1.2) != NUMBER(1.2)).is_false() &&
          (NUMBER(1.2) != NUMBER(3.5)).is_true() &&
          (NUMBER(3.5) != NUMBER(1.2)).is_true(), details, "NUMBER <> NUMBER", err);
  unitest((NUMBER() != NUMBER(1.2)).is_unknown(), details, "? (NUMBER) <> NUMBER", err);
  unitest((NUMBER(1.2) != NUMBER()).is_unknown(), details, "NUMBER <> ? (NUMBER)", err);
  unitest((NUMBER() != NUMBER()).is_unknown(), details, "? (NUMBER) <> ? (NUMBER)", err);

  /* не равно REAL */

  unitest((NUMBER(1.2) != REAL(1.2)).is_false() &&
          (NUMBER(1.2) != REAL(3.5)).is_true() &&
          (NUMBER(3.5) != REAL(1.2)).is_true(), details, "NUMBER <> REAL", err);
  unitest((NUMBER() != REAL(1.2)).is_unknown(), details, "? (NUMBER) <> REAL", err);
  unitest((NUMBER(1.2) != REAL()).is_unknown(), details, "NUMBER <> ? (REAL)", err);
  unitest((NUMBER() != REAL()).is_unknown(), details, "? (NUMBER) <> ? (REAL)", err);

  unitest((REAL(1.2) != NUMBER(1.2)).is_false() &&
          (REAL(1.2) != NUMBER(3.5)).is_true() &&
          (REAL(3.5) != NUMBER(1.2)).is_true(), details, "REAL <> NUMBER", err);
  unitest((REAL() != NUMBER(1.2)).is_unknown(), details, "? (REAL) <> NUMBER", err);
  unitest((REAL(1.2) != NUMBER()).is_unknown(), details, "REAL <> ? (NUMBER)", err);
  unitest((REAL() != NUMBER()).is_unknown(), details, "? (REAL) <> ? (NUMBER)", err);

  /* не равно INTEGER */

  unitest((NUMBER(1) != INTEGER(1)).is_false() &&
          (NUMBER(1) != INTEGER(3)).is_true() &&
          (NUMBER(3) != INTEGER(1)).is_true(), details, "NUMBER <> INTEGER", err);
  unitest((NUMBER() != INTEGER(1)).is_unknown(), details, "? (NUMBER) <> INTEGER", err);
  unitest((NUMBER(1.2) != INTEGER()).is_unknown(), details, "NUMBER <> ? (INTEGER)", err);
  unitest((NUMBER() != INTEGER()).is_unknown(), details, "? (NUMBER) <> ? (INTEGER)", err);

  unitest((INTEGER(1) != NUMBER(1)).is_false() &&
          (INTEGER(1) != NUMBER(3)).is_true() &&
          (INTEGER(3) != NUMBER(1)).is_true(), details, "INTEGER <> NUMBER", err);
  unitest((INTEGER() != NUMBER(1)).is_unknown(), details, "? (INTEGER) <> NUMBER", err);
  unitest((INTEGER(1) != NUMBER()).is_unknown(), details, "INTEGER <> ? (NUMBER)", err);
  unitest((INTEGER() != NUMBER()).is_unknown(), details, "? (INTEGER) <> ? (NUMBER)", err);

  /* не равно real_type */

  unitest((NUMBER(1.2) != static_cast<real_type>(1.2)).is_false() &&
          (NUMBER(1.2) != static_cast<real_type>(2.2)).is_true() &&
          (NUMBER(2.2) != static_cast<real_type>(1.2)).is_true(), details, "NUMBER <> real_type", err);
  unitest((NUMBER() != static_cast<real_type>(1.2)).is_unknown(), details, "? (NUMBER) <> real_type", err);

  unitest((static_cast<real_type>(1.2) != NUMBER(1.2)).is_false() &&
          (static_cast<real_type>(2.2) != NUMBER(1.2)).is_true() &&
          (static_cast<real_type>(1.2) != NUMBER(2.2)).is_true(), details, "real_type <> NUMBER", err);
  unitest((static_cast<real_type>(1.2) != NUMBER()).is_unknown(), details, "real_type <> ? (NUMBER)", err);

  /* не равно integer_type */

  unitest((NUMBER(1) != static_cast<integer_type>(1)).is_false() &&
          (NUMBER(1) != static_cast<integer_type>(2)).is_true() &&
          (NUMBER(2) != static_cast<integer_type>(1)).is_true(), details, "NUMBER <> integer_type", err);
  unitest((NUMBER() != static_cast<integer_type>(1)).is_unknown(), details, "? (NUMBER) <> integer_type", err);

  unitest((static_cast<integer_type>(1) != NUMBER(1)).is_false() &&
          (static_cast<integer_type>(2) != NUMBER(1)).is_true() &&
          (static_cast<integer_type>(1) != NUMBER(2)).is_true(), details, "integer_type <> NUMBER", err);
  unitest((static_cast<integer_type>(1) != NUMBER()).is_unknown(), details, "integer_type <> ? (NUMBER)", err);

  /* не равно int */

  unitest((NUMBER(1) != static_cast<int>(1)).is_false() &&
          (NUMBER(1) != static_cast<int>(2)).is_true() &&
          (NUMBER(2) != static_cast<int>(1)).is_true(), details, "NUMBER <> int", err);
  unitest((NUMBER() != static_cast<int>(1)).is_unknown(), details, "? (NUMBER) <> int", err);

  unitest((static_cast<int>(1) != NUMBER(1)).is_false() &&
          (static_cast<int>(2) != NUMBER(1)).is_true() &&
          (static_cast<int>(1) != NUMBER(2)).is_true(), details, "int <> NUMBER", err);
  unitest((static_cast<int>(1) != NUMBER()).is_unknown(), details, "int <> ? (NUMBER)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_number_rel_bt(bool details) {
  print_title(details, "NUMBER RELATIONS '>' ");
  test_t err = test_t::TEST_OK;

  /* больше NUMBER */

  unitest((NUMBER(3.5) > NUMBER(1.2)).is_true() &&
          (NUMBER(1.2) > NUMBER(3.5)).is_false() &&
          (NUMBER(3.5) > NUMBER(3.5)).is_false(), details, "NUMBER > NUMBER", err);
  unitest((NUMBER() > NUMBER(1.2)).is_unknown(), details, "? (NUMBER) > NUMBER", err);
  unitest((NUMBER(1.2) > NUMBER()).is_unknown(), details, "NUMBER > ? (NUMBER)", err);
  unitest((NUMBER() > NUMBER()).is_unknown(), details, "? (NUMBER) > ? (NUMBER)", err);

  /* больше REAL */

  unitest((NUMBER(3.5) > REAL(1.2)).is_true() &&
          (NUMBER(1.2) > REAL(3.5)).is_false() &&
          (NUMBER(3.5) > REAL(3.5)).is_false(), details, "NUMBER > REAL", err);
  unitest((NUMBER() > REAL(1.2)).is_unknown(), details, "? (NUMBER) > REAL", err);
  unitest((NUMBER(1.2) > REAL()).is_unknown(), details, "NUMBER > ? (REAL)", err);
  unitest((NUMBER() > REAL()).is_unknown(), details, "? (NUMBER) > ? (REAL)", err);

  unitest((REAL(3.5) > NUMBER(1.2)).is_true() &&
          (REAL(1.2) > NUMBER(3.5)).is_false() &&
          (REAL(3.5) > NUMBER(3.5)).is_false(), details, "REAL > NUMBER", err);
  unitest((REAL() > NUMBER(1.2)).is_unknown(), details, "? (REAL) > NUMBER", err);
  unitest((REAL(1.2) > NUMBER()).is_unknown(), details, "REAL > ? (NUMBER)", err);
  unitest((REAL() > NUMBER()).is_unknown(), details, "? (REAL) > ? (NUMBER)", err);

  /* больше INTEGER */

  unitest((NUMBER(3) > INTEGER(1)).is_true() &&
          (NUMBER(1) > INTEGER(3)).is_false() &&
          (NUMBER(3) > INTEGER(3)).is_false(), details, "NUMBER > INTEGER", err);
  unitest((NUMBER() > INTEGER(1)).is_unknown(), details, "? (NUMBER) > INTEGER", err);
  unitest((NUMBER(1.2) > INTEGER()).is_unknown(), details, "NUMBER > ? (INTEGER)", err);
  unitest((NUMBER() > INTEGER()).is_unknown(), details, "? (NUMBER) > ? (INTEGER)", err);

  unitest((INTEGER(3) > NUMBER(1)).is_true() &&
          (INTEGER(1) > NUMBER(3)).is_false() &&
          (INTEGER(3) > NUMBER(3)).is_false(), details, "INTEGER > NUMBER", err);
  unitest((INTEGER() > NUMBER(1)).is_unknown(), details, "? (INTEGER) > NUMBER", err);
  unitest((INTEGER(1) > NUMBER()).is_unknown(), details, "INTEGER > ? (NUMBER)", err);
  unitest((INTEGER() > NUMBER()).is_unknown(), details, "? (INTEGER) > ? (NUMBER)", err);


  /* больше real_type */

  unitest((NUMBER(3.5) > static_cast<real_type>(1.2)).is_true() &&
          (NUMBER(1.2) > static_cast<real_type>(3.5)).is_false() &&
          (NUMBER(3.5) > static_cast<real_type>(3.5)).is_false(), details, "NUMBER > real_type", err);
  unitest((NUMBER() > static_cast<real_type>(1.2)).is_unknown(), details, "? (NUMBER) > real_type", err);

  unitest((static_cast<real_type>(3.5) > NUMBER(1.2)).is_true() &&
          (static_cast<real_type>(1.2) > NUMBER(3.5)).is_false() &&
          (static_cast<real_type>(3.5) > NUMBER(3.5)).is_false(), details, "real_type > NUMBER", err);
  unitest((static_cast<real_type>(1.2) > NUMBER()).is_unknown(), details, "real_type > ? (NUMBER)", err);

  /* больше integer_type */

  unitest((NUMBER(3) > static_cast<integer_type>(1)).is_true() &&
          (NUMBER(1) > static_cast<integer_type>(3)).is_false() &&
          (NUMBER(3) > static_cast<integer_type>(3)).is_false(), details, "NUMBER > integer_type", err);
  unitest((NUMBER()  > static_cast<integer_type>(1)).is_unknown(), details, "? (NUMBER) > integer_type", err);

  unitest((static_cast<integer_type>(3) > NUMBER(1)).is_true() &&
          (static_cast<integer_type>(1) > NUMBER(3)).is_false() &&
          (static_cast<integer_type>(3) > NUMBER(3)).is_false(), details, "integer_type > NUMBER", err);
  unitest((static_cast<integer_type>(1) > NUMBER()).is_unknown(), details, "integer_type > ? (NUMBER)", err);

  /* больше int */

  unitest((NUMBER(3) > static_cast<int>(1)).is_true() &&
          (NUMBER(1) > static_cast<int>(3)).is_false() &&
          (NUMBER(3) > static_cast<int>(3)).is_false(), details, "NUMBER > int", err);
  unitest((NUMBER()  > static_cast<int>(1)).is_unknown(), details, "? (NUMBER) > int", err);

  unitest((static_cast<int>(3) > NUMBER(1)).is_true() &&
          (static_cast<int>(1) > NUMBER(3)).is_false() &&
          (static_cast<int>(3) > NUMBER(3)).is_false(), details, "int > NUMBER", err);
  unitest((static_cast<int>(1) > NUMBER()).is_unknown(), details, "int > ? (NUMBER)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_number_rel_beq(bool details) {
  print_title(details, "NUMBER RELATIONS '>=' ");
  test_t err = test_t::TEST_OK;
  LOGICAL l;

  /* больше или равно NUMBER */

  unitest((NUMBER(3.5) >= NUMBER(1.2)).is_true() &&
          (NUMBER(1.2) >= NUMBER(3.5)).is_false() &&
          (NUMBER(3.5) >= NUMBER(3.5)).is_true(), details, "NUMBER >= NUMBER", err);
  unitest((NUMBER() >= NUMBER(1.2)).is_unknown(), details, "? (NUMBER) >= NUMBER", err);
  unitest((NUMBER(1.2) >= NUMBER()).is_unknown(), details, "NUMBER >= ? (NUMBER)", err);
  unitest((NUMBER() >= NUMBER()).is_unknown(), details, "? (NUMBER) >= ? (NUMBER)", err);


  /* больше или равно REAL */

  unitest((NUMBER(3.5) >= REAL(1.2)).is_true() &&
          (NUMBER(1.2) >= REAL(3.5)).is_false() &&
          (NUMBER(3.5) >= REAL(3.5)).is_true(), details, "NUMBER >= REAL", err);
  unitest((NUMBER() >= REAL(1.2)).is_unknown(), details, "? (NUMBER) >= REAL", err);
  unitest((NUMBER(1.2) >= REAL()).is_unknown(), details, "NUMBER >= ? (REAL)", err);
  unitest((NUMBER() >= REAL()).is_unknown(), details, "? (NUMBER) >= ? (REAL)", err);

  unitest((REAL(3.5) >= NUMBER(1.2)).is_true() &&
          (REAL(1.2) >= NUMBER(3.5)).is_false() &&
          (REAL(3.5) >= NUMBER(3.5)).is_true(), details, "REAL >= NUMBER", err);
  unitest((REAL() >= NUMBER(1.2)).is_unknown(), details, "? (REAL) >= NUMBER", err);
  unitest((REAL(1.2) >= NUMBER()).is_unknown(), details, "REAL >= ? (NUMBER)", err);
  unitest((REAL() >= NUMBER()).is_unknown(), details, "? (REAL) >= ? (NUMBER)", err);


  /* больше или равно INTEGER */

  unitest((NUMBER(3) >= INTEGER(1)).is_true() &&
          (NUMBER(1) >= INTEGER(3)).is_false() &&
          (NUMBER(3) >= INTEGER(3)).is_true(), details, "NUMBER >= INTEGER", err);
  unitest((NUMBER() >= INTEGER(1)).is_unknown(), details, "? (NUMBER) >= INTEGER", err);
  unitest((NUMBER(1.2) >= INTEGER()).is_unknown(), details, "NUMBER >= ? (INTEGER)", err);
  unitest((NUMBER() >= INTEGER()).is_unknown(), details, "? (NUMBER) >= ? (INTEGER)", err);

  unitest((INTEGER(3) >= NUMBER(1)).is_true() &&
          (INTEGER(1) >= NUMBER(3)).is_false() &&
          (INTEGER(3) >= NUMBER(3)).is_true(), details, "INTEGER >= NUMBER", err);
  unitest((INTEGER() >= NUMBER(1)).is_unknown(), details, "? (INTEGER) >= NUMBER", err);
  unitest((INTEGER(1) >= NUMBER()).is_unknown(), details, "INTEGER >= ? (NUMBER)", err);
  unitest((INTEGER() >= NUMBER()).is_unknown(), details, "? (INTEGER) >= ? (NUMBER)", err);

  /* больше или равно real_type */

  unitest((NUMBER(3.5) >= static_cast<real_type>(1.2)).is_true() &&
          (NUMBER(1.2) >= static_cast<real_type>(3.5)).is_false() &&
          (NUMBER(3.5) >= static_cast<real_type>(3.5)).is_true(), details, "NUMBER >= real_type", err);
  unitest((NUMBER() >= static_cast<real_type>(1.2)).is_unknown(), details, "? (NUMBER) >= real_type", err);

  unitest((static_cast<real_type>(3.5) >= NUMBER(1.2)).is_true() &&
          (static_cast<real_type>(1.2) >= NUMBER(3.5)).is_false() &&
          (static_cast<real_type>(3.5) >= NUMBER(3.5)).is_true(), details, "real_type >= NUMBER", err);
  unitest((static_cast<real_type>(1.2) >= NUMBER()).is_unknown(), details, "real_type >= ? (NUMBER)", err);

  /* больше или равно integer_type */

  unitest((NUMBER(3) >= static_cast<integer_type>(1)).is_true() &&
          (NUMBER(1) >= static_cast<integer_type>(3)).is_false() &&
          (NUMBER(3) >= static_cast<integer_type>(3)).is_true(), details, "NUMBER >= integer_type", err);
  unitest((NUMBER()  >= static_cast<integer_type>(1)).is_unknown(), details, "? (NUMBER) >= integer_type", err);

  unitest((static_cast<integer_type>(3) >= NUMBER(1)).is_true() &&
          (static_cast<integer_type>(1) >= NUMBER(3)).is_false() &&
          (static_cast<integer_type>(3) >= NUMBER(3)).is_true(), details, "integer_type >= NUMBER", err);
  unitest((static_cast<integer_type>(1) >= NUMBER()).is_unknown(), details, "integer_type >= ? (NUMBER)", err);

  /* больше int */

  unitest((NUMBER(3) >= static_cast<int>(1)).is_true() &&
          (NUMBER(1) >= static_cast<int>(3)).is_false() &&
          (NUMBER(3) >= static_cast<int>(3)).is_true(), details, "NUMBER > int", err);
  unitest((NUMBER()  >= static_cast<int>(1)).is_unknown(), details, "? (NUMBER) > int", err);

  unitest((static_cast<int>(3) >= NUMBER(1)).is_true() &&
          (static_cast<int>(1) >= NUMBER(3)).is_false() &&
          (static_cast<int>(3) >= NUMBER(3)).is_true(), details, "int > NUMBER", err);
  unitest((static_cast<int>(1) >= NUMBER()).is_unknown(), details, "int > ? (NUMBER)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_number_rel_lt(bool details) {
  print_title(details, "NUMBER RELATIONS '<' ");
  test_t err = test_t::TEST_OK;

  /* меньше NUMBER */

  unitest((NUMBER(3.5) < NUMBER(1.2)).is_false() &&
          (NUMBER(1.2) < NUMBER(3.5)).is_true() &&
          (NUMBER(3.5) < NUMBER(3.5)).is_false(), details, "NUMBER < NUMBER", err);
  unitest((NUMBER() < NUMBER(1.2)).is_unknown(), details, "? (NUMBER) < NUMBER", err);
  unitest((NUMBER(1.2) < NUMBER()).is_unknown(), details, "NUMBER < ? (NUMBER)", err);
  unitest((NUMBER() < NUMBER()).is_unknown(), details, "? (NUMBER) < ? (NUMBER)", err);

  /* меньше REAL */

  unitest((NUMBER(3.5) < REAL(1.2)).is_false() &&
          (NUMBER(1.2) < REAL(3.5)).is_true() &&
          (NUMBER(3.5) < REAL(3.5)).is_false(), details, "NUMBER < REAL", err);
  unitest((NUMBER() < REAL(1.2)).is_unknown(), details, "? (NUMBER) < REAL", err);
  unitest((NUMBER(1.2) < REAL()).is_unknown(), details, "NUMBER < ? (REAL)", err);
  unitest((NUMBER() < REAL()).is_unknown(), details, "? (NUMBER) < ? (REAL)", err);

  unitest((REAL(3.5) < NUMBER(1.2)).is_false() &&
          (REAL(1.2) < NUMBER(3.5)).is_true() &&
          (REAL(3.5) < NUMBER(3.5)).is_false(), details, "REAL < NUMBER", err);
  unitest((REAL() < NUMBER(1.2)).is_unknown(), details, "? (REAL) < NUMBER", err);
  unitest((REAL(1.2) < NUMBER()).is_unknown(), details, "REAL < ? (NUMBER)", err);
  unitest((REAL() < NUMBER()).is_unknown(), details, "? (REAL) < ? (NUMBER)", err);

  /* меньше INTEGER */

  unitest((NUMBER(3) < INTEGER(1)).is_false() &&
          (NUMBER(1) < INTEGER(3)).is_true() &&
          (NUMBER(3) < INTEGER(3)).is_false(), details, "NUMBER < INTEGER", err);
  unitest((NUMBER() < INTEGER(1)).is_unknown(), details, "? (NUMBER) < INTEGER", err);
  unitest((NUMBER(1.2) < INTEGER()).is_unknown(), details, "NUMBER < ? (INTEGER)", err);
  unitest((NUMBER() < INTEGER()).is_unknown(), details, "? (NUMBER) < ? (INTEGER)", err);

  unitest((INTEGER(3) < NUMBER(1)).is_false() &&
          (INTEGER(1) < NUMBER(3)).is_true() &&
          (INTEGER(3) < NUMBER(3)).is_false(), details, "INTEGER < NUMBER", err);
  unitest((INTEGER() < NUMBER(1)).is_unknown(), details, "? (INTEGER) < NUMBER", err);
  unitest((INTEGER(1) < NUMBER()).is_unknown(), details, "INTEGER < ? (NUMBER)", err);
  unitest((INTEGER() < NUMBER()).is_unknown(), details, "? (INTEGER) < ? (NUMBER)", err);

  /* меньше real_type */

  unitest((NUMBER(3.5) < static_cast<real_type>(1.2)).is_false() &&
          (NUMBER(1.2) < static_cast<real_type>(3.5)).is_true() &&
          (NUMBER(3.5) < static_cast<real_type>(3.5)).is_false(), details, "NUMBER < real_type", err);
  unitest((NUMBER() < static_cast<real_type>(1.2)).is_unknown(), details, "? (NUMBER) < real_type", err);

  unitest((static_cast<real_type>(3.5) < NUMBER(1.2)).is_false() &&
          (static_cast<real_type>(1.2) < NUMBER(3.5)).is_true() &&
          (static_cast<real_type>(3.5) < NUMBER(3.5)).is_false(), details, "real_type < NUMBER", err);
  unitest((static_cast<real_type>(1.2) < NUMBER()).is_unknown(), details, "real_type < ? (NUMBER)", err);

  /* меньше integer_type */

  unitest((NUMBER(3) < static_cast<integer_type>(1)).is_false() &&
          (NUMBER(1) < static_cast<integer_type>(3)).is_true() &&
          (NUMBER(3) < static_cast<integer_type>(3)).is_false(), details, "NUMBER < integer_type", err);
  unitest((NUMBER()  < static_cast<integer_type>(1)).is_unknown(), details, "? (NUMBER) < integer_type", err);

  unitest((static_cast<integer_type>(3) < NUMBER(1)).is_false() &&
          (static_cast<integer_type>(1) < NUMBER(3)).is_true() &&
          (static_cast<integer_type>(3) < NUMBER(3)).is_false(), details, "integer_type < NUMBER", err);
  unitest((static_cast<integer_type>(1) < NUMBER()).is_unknown(), details, "integer_type < ? (NUMBER)", err);

  /* меньше int */

  unitest((NUMBER(3) < static_cast<int>(1)).is_false() &&
          (NUMBER(1) < static_cast<int>(3)).is_true() &&
          (NUMBER(3) < static_cast<int>(3)).is_false(), details, "NUMBER < int", err);
  unitest((NUMBER()  < static_cast<int>(1)).is_unknown(), details, "? (NUMBER) < int", err);

  unitest((static_cast<int>(3) < NUMBER(1)).is_false() &&
          (static_cast<int>(1) < NUMBER(3)).is_true() &&
          (static_cast<int>(3) < NUMBER(3)).is_false(), details, "int < NUMBER", err);
  unitest((static_cast<int>(1) < NUMBER()).is_unknown(), details, "int < ? (NUMBER)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_number_rel_leq(bool details) {
  print_title(details, "NUMBER RELATIONS '<=' ");
  test_t err = test_t::TEST_OK;
  LOGICAL l;

  /* меньше или равно NUMBER */

  unitest((NUMBER(3.5) <= NUMBER(1.2)).is_false() &&
          (NUMBER(1.2) <= NUMBER(3.5)).is_true() &&
          (NUMBER(3.5) <= NUMBER(3.5)).is_true(), details, "NUMBER <= NUMBER", err);
  unitest((NUMBER() <= NUMBER(1.2)).is_unknown(), details, "? (NUMBER) <= NUMBER", err);
  unitest((NUMBER(1.2) <= NUMBER()).is_unknown(), details, "NUMBER <= ? (NUMBER)", err);
  unitest((NUMBER() <= NUMBER()).is_unknown(), details, "? (NUMBER) <= ? (NUMBER)", err);

  /* меньше или равно REAL */

  unitest((NUMBER(3.5) <= REAL(1.2)).is_false() &&
          (NUMBER(1.2) <= REAL(3.5)).is_true() &&
          (NUMBER(3.5) <= REAL(3.5)).is_true(), details, "NUMBER <= REAL", err);
  unitest((NUMBER() <= REAL(1.2)).is_unknown(), details, "? (NUMBER) <= REAL", err);
  unitest((NUMBER(1.2) <= REAL()).is_unknown(), details, "NUMBER <= ? (REAL)", err);
  unitest((NUMBER() <= REAL()).is_unknown(), details, "? (NUMBER) <= ? (REAL)", err);

  unitest((REAL(3.5) <= NUMBER(1.2)).is_false() &&
          (REAL(1.2) <= NUMBER(3.5)).is_true() &&
          (REAL(3.5) <= NUMBER(3.5)).is_true(), details, "REAL <= NUMBER", err);
  unitest((REAL() <= NUMBER(1.2)).is_unknown(), details, "? (REAL) <= NUMBER", err);
  unitest((REAL(1.2) <= NUMBER()).is_unknown(), details, "REAL <= ? (NUMBER)", err);
  unitest((REAL() <= NUMBER()).is_unknown(), details, "? (REAL) <= ? (NUMBER)", err);

  /* меньше или равно INTEGER */

  unitest((NUMBER(3) <= INTEGER(1)).is_false() &&
          (NUMBER(1) <= INTEGER(3)).is_true() &&
          (NUMBER(3) <= INTEGER(3)).is_true(), details, "NUMBER <= INTEGER", err);
  unitest((NUMBER() <= INTEGER(1)).is_unknown(), details, "? (NUMBER) <= INTEGER", err);
  unitest((NUMBER(1.2) <= INTEGER()).is_unknown(), details, "NUMBER <= ? (INTEGER)", err);
  unitest((NUMBER() <= INTEGER()).is_unknown(), details, "? (NUMBER) <= ? (INTEGER)", err);

  unitest((INTEGER(3) <= NUMBER(1)).is_false() &&
          (INTEGER(1) <= NUMBER(3)).is_true() &&
          (INTEGER(3) <= NUMBER(3)).is_true(), details, "INTEGER <= NUMBER", err);
  unitest((INTEGER() <= NUMBER(1)).is_unknown(), details, "? (INTEGER) <= NUMBER", err);
  unitest((INTEGER(1) <= NUMBER()).is_unknown(), details, "INTEGER <= ? (NUMBER)", err);
  unitest((INTEGER() <= NUMBER()).is_unknown(), details, "? (INTEGER) <= ? (NUMBER)", err);

  /* меньше или равно real_type */

  unitest((NUMBER(3.5) <= static_cast<real_type>(1.2)).is_false() &&
          (NUMBER(1.2) <= static_cast<real_type>(3.5)).is_true() &&
          (NUMBER(3.5) <= static_cast<real_type>(3.5)).is_true(), details, "NUMBER <= real_type", err);
  unitest((NUMBER() <= static_cast<real_type>(1.2)).is_unknown(), details, "? (NUMBER) <= real_type", err);

  unitest((static_cast<real_type>(3.5) <= NUMBER(1.2)).is_false() &&
          (static_cast<real_type>(1.2) <= NUMBER(3.5)).is_true() &&
          (static_cast<real_type>(3.5) <= NUMBER(3.5)).is_true(), details, "real_type <= NUMBER", err);
  unitest((static_cast<real_type>(1.2) <= NUMBER()).is_unknown(), details, "real_type <= ? (NUMBER)", err);

  /* меньше или равно integer_type */

  unitest((NUMBER(3) <= static_cast<integer_type>(1)).is_false() &&
          (NUMBER(1) <= static_cast<integer_type>(3)).is_true() &&
          (NUMBER(3) <= static_cast<integer_type>(3)).is_true(), details, "NUMBER <= integer_type", err);
  unitest((NUMBER()  <= static_cast<integer_type>(1)).is_unknown(), details, "? (NUMBER) <= integer_type", err);

  unitest((static_cast<integer_type>(3) <= NUMBER(1)).is_false() &&
          (static_cast<integer_type>(1) <= NUMBER(3)).is_true() &&
          (static_cast<integer_type>(3) <= NUMBER(3)).is_true(), details, "integer_type <= NUMBER", err);
  unitest((static_cast<integer_type>(1) <= NUMBER()).is_unknown(), details, "integer_type <= ? (NUMBER)", err);

  /* меньше или равно int */

  unitest((NUMBER(3) <= static_cast<int>(1)).is_false() &&
          (NUMBER(1) <= static_cast<int>(3)).is_true() &&
          (NUMBER(3) <= static_cast<int>(3)).is_true(), details, "NUMBER <= int", err);
  unitest((NUMBER()  <= static_cast<int>(1)).is_unknown(), details, "? (NUMBER) <= int", err);

  unitest((static_cast<int>(3) <= NUMBER(1)).is_false() &&
          (static_cast<int>(1) <= NUMBER(3)).is_true() &&
          (static_cast<int>(3) <= NUMBER(3)).is_true(), details, "int <= NUMBER", err);
  unitest((static_cast<int>(1) <= NUMBER()).is_unknown(), details, "int <= ? (NUMBER)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_real_rel_eq(bool details) {
  print_title(details, "REAL RELATIONS '=' ");
  test_t err = test_t::TEST_OK;

  /* равно REAL */

  unitest((REAL(1.2) == REAL(1.2)).is_true() &&
          (REAL(1.2) == REAL(3.5)).is_false() &&
          (REAL(3.5) == REAL(1.2)).is_false(), details, "REAL = REAL", err);
  unitest((REAL() == REAL(1.2)).is_unknown(), details, "? (REAL) = REAL", err);
  unitest((REAL(1.2) == REAL()).is_unknown(), details, "REAL = ? (REAL)", err);
  unitest((REAL() == REAL()).is_unknown(), details, "? (REAL) = ? (REAL)", err);

  /* равно INTEGER */

  unitest((REAL(1) == INTEGER(1)).is_true() &&
          (REAL(1) == INTEGER(3)).is_false() &&
          (REAL(3) == INTEGER(1)).is_false(), details, "REAL = INTEGER", err);
  unitest((REAL() == INTEGER(1)).is_unknown(), details, "? (REAL) = INTEGER", err);
  unitest((REAL(1.2) == INTEGER()).is_unknown(), details, "REAL = ? (INTEGER)", err);
  unitest((REAL() == INTEGER()).is_unknown(), details, "? (REAL) = ? (INTEGER)", err);

  unitest((INTEGER(1) == REAL(1)).is_true() &&
          (INTEGER(1) == REAL(3)).is_false() &&
          (INTEGER(3) == REAL(1)).is_false(), details, "INTEGER = REAL", err);
  unitest((INTEGER() == REAL(1)).is_unknown(), details, "? (INTEGER) = REAL", err);
  unitest((INTEGER(1) == REAL()).is_unknown(), details, "INTEGER = ? (REAL)", err);
  unitest((INTEGER() == REAL()).is_unknown(), details, "? (INTEGER) = ? (REAL)", err);

  /* равно real_type */

  unitest((REAL(1.2) == static_cast<real_type>(1.2)).is_true() &&
          (REAL(1.2) == static_cast<real_type>(2.2)).is_false() &&
          (REAL(2.2) == static_cast<real_type>(1.2)).is_false(), details, "REAL = real_type", err);
  unitest((REAL() == static_cast<real_type>(1.2)).is_unknown(), details, "? (REAL) = real_type", err);

  unitest((static_cast<real_type>(1.2) == REAL(1.2)).is_true() &&
          (static_cast<real_type>(2.2) == REAL(1.2)).is_false() &&
          (static_cast<real_type>(1.2) == REAL(2.2)).is_false(), details, "real_type = REAL", err);
  unitest((static_cast<real_type>(1.2) == REAL()).is_unknown(), details, "real_type = ? (REAL)", err);

  /* равно integer_type */

  unitest((REAL(1) == static_cast<integer_type>(1)).is_true() &&
          (REAL(1) == static_cast<integer_type>(2)).is_false() &&
          (REAL(2) == static_cast<integer_type>(1)).is_false(), details, "REAL = integer_type", err);
  unitest((REAL() == static_cast<integer_type>(1)).is_unknown(), details, "? (REAL) = integer_type", err);

  unitest((static_cast<integer_type>(1) == REAL(1)).is_true() &&
          (static_cast<integer_type>(2) == REAL(1)).is_false() &&
          (static_cast<integer_type>(1) == REAL(2)).is_false(), details, "integer_type = REAL", err);
  unitest((static_cast<integer_type>(1) == REAL()).is_unknown(), details, "integer_type = ? (REAL)", err);

  /* равно int */

  unitest((REAL(1) == static_cast<int>(1)).is_true() &&
          (REAL(1) == static_cast<int>(2)).is_false() &&
          (REAL(2) == static_cast<int>(1)).is_false(), details, "REAL = int", err);
  unitest((REAL() == static_cast<int>(1)).is_unknown(), details, "? (REAL) = int", err);

  unitest((static_cast<int>(1) == REAL(1)).is_true() &&
          (static_cast<int>(2) == REAL(1)).is_false() &&
          (static_cast<int>(1) == REAL(2)).is_false(), details, "int = REAL", err);
  unitest((static_cast<int>(1) == REAL()).is_unknown(), details, "int = ? (REAL)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_real_rel_neq(bool details) {
  print_title(details, "REAL RELATIONS '<>' ");
  test_t err = test_t::TEST_OK;

  /* не равно REAL */

  unitest((REAL(1.2) != REAL(1.2)).is_false() &&
          (REAL(1.2) != REAL(3.5)).is_true() &&
          (REAL(3.5) != REAL(1.2)).is_true(), details, "REAL <> REAL", err);
  unitest((REAL() != REAL(1.2)).is_unknown(), details, "? (REAL) <> REAL", err);
  unitest((REAL(1.2) != REAL()).is_unknown(), details, "REAL <> ? (REAL)", err);
  unitest((REAL() != REAL()).is_unknown(), details, "? (REAL) <> ? (REAL)", err);

  /* не равно INTEGER */

  unitest((REAL(1) != INTEGER(1)).is_false() &&
          (REAL(1) != INTEGER(3)).is_true() &&
          (REAL(3) != INTEGER(1)).is_true(), details, "REAL <> INTEGER", err);
  unitest((REAL() != INTEGER(1)).is_unknown(), details, "? (REAL) <> INTEGER", err);
  unitest((REAL(1.2) != INTEGER()).is_unknown(), details, "REAL <> ? (INTEGER)", err);
  unitest((REAL() != INTEGER()).is_unknown(), details, "? (REAL) <> ? (INTEGER)", err);

  unitest((INTEGER(1) != REAL(1)).is_false() &&
          (INTEGER(1) != REAL(3)).is_true() &&
          (INTEGER(3) != REAL(1)).is_true(), details, "INTEGER <> REAL", err);
  unitest((INTEGER() != REAL(1)).is_unknown(), details, "? (INTEGER) <> REAL", err);
  unitest((INTEGER(1) != REAL()).is_unknown(), details, "INTEGER <> ? (REAL)", err);
  unitest((INTEGER() != REAL()).is_unknown(), details, "? (INTEGER) <> ? (REAL)", err);

  /* не равно real_type */

  unitest((REAL(1.2) != static_cast<real_type>(1.2)).is_false() &&
          (REAL(1.2) != static_cast<real_type>(2.2)).is_true() &&
          (REAL(2.2) != static_cast<real_type>(1.2)).is_true(), details, "REAL <> real_type", err);
  unitest((REAL() != static_cast<real_type>(1.2)).is_unknown(), details, "? (REAL) <> real_type", err);

  unitest((static_cast<real_type>(1.2) != REAL(1.2)).is_false() &&
          (static_cast<real_type>(2.2) != REAL(1.2)).is_true() &&
          (static_cast<real_type>(1.2) != REAL(2.2)).is_true(), details, "real_type <> REAL", err);
  unitest((static_cast<real_type>(1.2) != REAL()).is_unknown(), details, "real_type <> ? (REAL)", err);

  /* не равно integer_type */

  unitest((REAL(1) != static_cast<integer_type>(1)).is_false() &&
          (REAL(1) != static_cast<integer_type>(2)).is_true() &&
          (REAL(2) != static_cast<integer_type>(1)).is_true(), details, "REAL <> integer_type", err);
  unitest((REAL() != static_cast<integer_type>(1)).is_unknown(), details, "? (REAL) <> integer_type", err);

  unitest((static_cast<integer_type>(1) != REAL(1)).is_false() &&
          (static_cast<integer_type>(2) != REAL(1)).is_true() &&
          (static_cast<integer_type>(1) != REAL(2)).is_true(), details, "integer_type <> REAL", err);
  unitest((static_cast<integer_type>(1) != REAL()).is_unknown(), details, "integer_type <> ? (REAL)", err);

  /* не равно int */

  unitest((REAL(1) != static_cast<int>(1)).is_false() &&
          (REAL(1) != static_cast<int>(2)).is_true() &&
          (REAL(2) != static_cast<int>(1)).is_true(), details, "REAL <> int", err);
  unitest((REAL() != static_cast<int>(1)).is_unknown(), details, "? (REAL) <> int", err);

  unitest((static_cast<int>(1) != REAL(1)).is_false() &&
          (static_cast<int>(2) != REAL(1)).is_true() &&
          (static_cast<int>(1) != REAL(2)).is_true(), details, "int <> REAL", err);
  unitest((static_cast<int>(1) != REAL()).is_unknown(), details, "int <> ? (REAL)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_real_rel_bt(bool details) {
  print_title(details, "REAL RELATIONS '>' ");
  test_t err = test_t::TEST_OK;

  /* больше REAL */

  unitest((REAL(3.567891234, PREC{ 4 }) > REAL(3.567891234, PREC{ 5 })).is_true() &&
          (REAL(3.567891234, PREC{ 5 }) > REAL(3.567891234, PREC{ 4 })).is_false() &&
          (REAL(3.567891234, PREC{ 5 }) > REAL(3.567891234, PREC{ 5 })).is_false(), details, "REAL > REAL", err);
  unitest((REAL() > REAL(1.2)).is_unknown(), details, "? (REAL) > REAL", err);
  unitest((REAL(1.2) > REAL()).is_unknown(), details, "REAL > ? (REAL)", err);
  unitest((REAL() > REAL()).is_unknown(), details, "? (REAL) > ? (REAL)", err);

  /* больше INTEGER */

  unitest((REAL(3) > INTEGER(1)).is_true() &&
          (REAL(1) > INTEGER(3)).is_false() &&
          (REAL(3) > INTEGER(3)).is_false(), details, "REAL > INTEGER", err);
  unitest((REAL() > INTEGER(1)).is_unknown(), details, "? (REAL) > INTEGER", err);
  unitest((REAL(1.2) > INTEGER()).is_unknown(), details, "REAL > ? (INTEGER)", err);
  unitest((REAL() > INTEGER()).is_unknown(), details, "? (REAL) > ? (INTEGER)", err);

  unitest((INTEGER(3) > REAL(1)).is_true() &&
          (INTEGER(1) > REAL(3)).is_false() &&
          (INTEGER(3) > REAL(3)).is_false(), details, "INTEGER > REAL", err);
  unitest((INTEGER() > REAL(1)).is_unknown(), details, "? (INTEGER) > REAL", err);
  unitest((INTEGER(1) > REAL()).is_unknown(), details, "INTEGER > ? (REAL)", err);
  unitest((INTEGER() > REAL()).is_unknown(), details, "? (INTEGER) > ? (REAL)", err);

  /* больше real_type */

  unitest((REAL(3.5) > static_cast<real_type>(1.2)).is_true() &&
          (REAL(1.2) > static_cast<real_type>(3.5)).is_false() &&
          (REAL(3.5) > static_cast<real_type>(3.5)).is_false(), details, "REAL > real_type", err);
  unitest((REAL() > static_cast<real_type>(1.2)).is_unknown(), details, "? (REAL) > real_type", err);

  unitest((static_cast<real_type>(3.5) > REAL(1.2)).is_true() &&
          (static_cast<real_type>(1.2) > REAL(3.5)).is_false() &&
          (static_cast<real_type>(3.5) > REAL(3.5)).is_false(), details, "real_type > REAL", err);
  unitest((static_cast<real_type>(1.2) > REAL()).is_unknown(), details, "real_type > ? (REAL)", err);

  /* больше integer_type */

  unitest((REAL(3) > static_cast<integer_type>(1)).is_true() &&
          (REAL(1) > static_cast<integer_type>(3)).is_false() &&
          (REAL(3) > static_cast<integer_type>(3)).is_false(), details, "REAL > integer_type", err);
  unitest((REAL()  > static_cast<integer_type>(1)).is_unknown(), details, "? (REAL) > integer_type", err);

  unitest((static_cast<integer_type>(3) > REAL(1)).is_true() &&
          (static_cast<integer_type>(1) > REAL(3)).is_false() &&
          (static_cast<integer_type>(3) > REAL(3)).is_false(), details, "integer_type > REAL", err);
  unitest((static_cast<integer_type>(1) > REAL()).is_unknown(), details, "integer_type > ? (REAL)", err);

  /* больше int */

  unitest((REAL(3) > static_cast<int>(1)).is_true() &&
          (REAL(1) > static_cast<int>(3)).is_false() &&
          (REAL(3) > static_cast<int>(3)).is_false(), details, "REAL > int", err);
  unitest((REAL()  > static_cast<int>(1)).is_unknown(), details, "? (REAL) > int", err);

  unitest((static_cast<int>(3) > REAL(1)).is_true() &&
          (static_cast<int>(1) > REAL(3)).is_false() &&
          (static_cast<int>(3) > REAL(3)).is_false(), details, "int > REAL", err);
  unitest((static_cast<int>(1) > REAL()).is_unknown(), details, "int > ? (REAL)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_real_rel_beq(bool details) {
  print_title(details, "REAL RELATIONS '>=' ");
  test_t err = test_t::TEST_OK;

  /* больше или равно REAL */

  unitest((REAL(3.567891234, PREC{ 4 }) >= REAL(3.567891234, PREC{ 5 })).is_true() &&
          (REAL(3.567891234, PREC{ 5 }) >= REAL(3.567891234, PREC{ 4 })).is_false() &&
          (REAL(3.567891234, PREC{ 5 }) >= REAL(3.567891234, PREC{ 5 })).is_true(), details, "REAL >= REAL", err);
  unitest((REAL() >= REAL(1.2)).is_unknown(), details, "? (REAL) >= REAL", err);
  unitest((REAL(1.2) >= REAL()).is_unknown(), details, "REAL >= ? (REAL)", err);
  unitest((REAL() >= REAL()).is_unknown(), details, "? (REAL) >= ? (REAL)", err);

  /* больше или равно INTEGER */

  unitest((REAL(3) >= INTEGER(1)).is_true() &&
          (REAL(1) >= INTEGER(3)).is_false() &&
          (REAL(3) >= INTEGER(3)).is_true(), details, "REAL >= INTEGER", err);
  unitest((REAL() >= INTEGER(1)).is_unknown(), details, "? (REAL) >= INTEGER", err);
  unitest((REAL(1.2) >= INTEGER()).is_unknown(), details, "REAL >= ? (INTEGER)", err);
  unitest((REAL() >= INTEGER()).is_unknown(), details, "? (REAL) >= ? (INTEGER)", err);

  unitest((INTEGER(3) >= REAL(1)).is_true() &&
          (INTEGER(1) >= REAL(3)).is_false() &&
          (INTEGER(3) >= REAL(3)).is_true(), details, "INTEGER >= REAL", err);
  unitest((INTEGER() >= REAL(1)).is_unknown(), details, "? (INTEGER) >= REAL", err);
  unitest((INTEGER(1) >= REAL()).is_unknown(), details, "INTEGER >= ? (REAL)", err);
  unitest((INTEGER() >= REAL()).is_unknown(), details, "? (INTEGER) >= ? (REAL)", err);

  /* больше или равно real_type */

  unitest((REAL(3.5) >= static_cast<real_type>(1.2)).is_true() &&
          (REAL(1.2) >= static_cast<real_type>(3.5)).is_false() &&
          (REAL(3.5) >= static_cast<real_type>(3.5)).is_true(), details, "REAL >= real_type", err);
  unitest((REAL() >= static_cast<real_type>(1.2)).is_unknown(), details, "? (REAL) >= real_type", err);

  unitest((static_cast<real_type>(3.5) >= REAL(1.2)).is_true() &&
          (static_cast<real_type>(1.2) >= REAL(3.5)).is_false() &&
          (static_cast<real_type>(3.5) >= REAL(3.5)).is_true(), details, "real_type >= REAL", err);
  unitest((static_cast<real_type>(1.2) >= REAL()).is_unknown(), details, "real_type >= ? (REAL)", err);

  /* больше или равно integer_type */

  unitest((REAL(3) >= static_cast<integer_type>(1)).is_true() &&
          (REAL(1) >= static_cast<integer_type>(3)).is_false() &&
          (REAL(3) >= static_cast<integer_type>(3)).is_true(), details, "REAL >= integer_type", err);
  unitest((REAL()  >= static_cast<integer_type>(1)).is_unknown(), details, "? (REAL) >= integer_type", err);

  unitest((static_cast<integer_type>(3) >= REAL(1)).is_true() &&
          (static_cast<integer_type>(1) >= REAL(3)).is_false() &&
          (static_cast<integer_type>(3) >= REAL(3)).is_true(), details, "integer_type >= REAL", err);
  unitest((static_cast<integer_type>(1) >= REAL()).is_unknown(), details, "integer_type >= ? (REAL)", err);

  /* больше или равно int */

  unitest((REAL(3) >= static_cast<int>(1)).is_true() &&
          (REAL(1) >= static_cast<int>(3)).is_false() &&
          (REAL(3) >= static_cast<int>(3)).is_true(), details, "REAL >= int", err);
  unitest((REAL()  >= static_cast<int>(1)).is_unknown(), details, "? (REAL) >= int", err);

  unitest((static_cast<int>(3) >= REAL(1)).is_true() &&
          (static_cast<int>(1) >= REAL(3)).is_false() &&
          (static_cast<int>(3) >= REAL(3)).is_true(), details, "int >= REAL", err);
  unitest((static_cast<int>(1) >= REAL()).is_unknown(), details, "int >= ? (REAL)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_real_rel_lt(bool details) {
  print_title(details, "REAL RELATIONS '<' ");
  test_t err = test_t::TEST_OK;

  /* меньше REAL */

  unitest((REAL(3.567891234, PREC{ 4 }) < REAL(3.567891234, PREC{ 5 })).is_false() &&
          (REAL(3.567891234, PREC{ 5 }) < REAL(3.567891234, PREC{ 4 })).is_true() &&
          (REAL(3.567891234, PREC{ 5 }) < REAL(3.567891234, PREC{ 5 })).is_false(), details, "REAL < REAL", err);
  unitest((REAL() < REAL(1.2)).is_unknown(), details, "? (REAL) < REAL", err);
  unitest((REAL(1.2) < REAL()).is_unknown(), details, "REAL < ? (REAL)", err);
  unitest((REAL() < REAL()).is_unknown(), details, "? (REAL) < ? (REAL)", err);

  /* меньше INTEGER */

  unitest((REAL(3) < INTEGER(1)).is_false() &&
          (REAL(1) < INTEGER(3)).is_true() &&
          (REAL(3) < INTEGER(3)).is_false(), details, "REAL < INTEGER", err);
  unitest((REAL() < INTEGER(1)).is_unknown(), details, "? (REAL) < INTEGER", err);
  unitest((REAL(1.2) < INTEGER()).is_unknown(), details, "REAL < ? (INTEGER)", err);
  unitest((REAL() < INTEGER()).is_unknown(), details, "? (REAL) < ? (INTEGER)", err);

  unitest((INTEGER(3) < REAL(1)).is_false() &&
          (INTEGER(1) < REAL(3)).is_true() &&
          (INTEGER(3) < REAL(3)).is_false(), details, "INTEGER < REAL", err);
  unitest((INTEGER() < REAL(1)).is_unknown(), details, "? (INTEGER) < REAL", err);
  unitest((INTEGER(1) < REAL()).is_unknown(), details, "INTEGER < ? (REAL)", err);
  unitest((INTEGER() < REAL()).is_unknown(), details, "? (INTEGER) < ? (REAL)", err);

  /* меньше real_type */

  unitest((REAL(3.5) < static_cast<real_type>(1.2)).is_false() &&
          (REAL(1.2) < static_cast<real_type>(3.5)).is_true() &&
          (REAL(3.5) < static_cast<real_type>(3.5)).is_false(), details, "REAL < real_type", err);
  unitest((REAL() < static_cast<real_type>(1.2)).is_unknown(), details, "? (REAL) < real_type", err);

  unitest((static_cast<real_type>(3.5) < REAL(1.2)).is_false() &&
          (static_cast<real_type>(1.2) < REAL(3.5)).is_true() &&
          (static_cast<real_type>(3.5) < REAL(3.5)).is_false(), details, "real_type < REAL", err);
  unitest((static_cast<real_type>(1.2) < REAL()).is_unknown(), details, "real_type < ? (REAL)", err);

  /* меньше integer_type */

  unitest((REAL(3) < static_cast<integer_type>(1)).is_false() &&
          (REAL(1) < static_cast<integer_type>(3)).is_true() &&
          (REAL(3) < static_cast<integer_type>(3)).is_false(), details, "REAL < integer_type", err);
  unitest((REAL()  < static_cast<integer_type>(1)).is_unknown(), details, "? (REAL) < integer_type", err);

  unitest((static_cast<integer_type>(3) < REAL(1)).is_false() &&
          (static_cast<integer_type>(1) < REAL(3)).is_true() &&
          (static_cast<integer_type>(3) < REAL(3)).is_false(), details, "integer_type < REAL", err);
  unitest((static_cast<integer_type>(1) < REAL()).is_unknown(), details, "integer_type < ? (REAL)", err);

  /* меньше int */

  unitest((REAL(3) < static_cast<int>(1)).is_false() &&
          (REAL(1) < static_cast<int>(3)).is_true() &&
          (REAL(3) < static_cast<int>(3)).is_false(), details, "REAL < int", err);
  unitest((REAL()  < static_cast<int>(1)).is_unknown(), details, "? (REAL) < int", err);

  unitest((static_cast<int>(3) < REAL(1)).is_false() &&
          (static_cast<int>(1) < REAL(3)).is_true() &&
          (static_cast<int>(3) < REAL(3)).is_false(), details, "int < REAL", err);
  unitest((static_cast<int>(1) < REAL()).is_unknown(), details, "int < ? (REAL)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_real_rel_leq(bool details) {
  print_title(details, "REAL RELATIONS '<=' ");
  test_t err = test_t::TEST_OK;

  /* меньше или равно REAL */

  unitest((REAL(3.567891234, PREC{ 4 }) <= REAL(3.567891234, PREC{ 5 })).is_false() &&
          (REAL(3.567891234, PREC{ 5 }) <= REAL(3.567891234, PREC{ 4 })).is_true() &&
          (REAL(3.567891234, PREC{ 5 }) <= REAL(3.567891234, PREC{ 5 })).is_true(), details, "REAL <= REAL", err);
  unitest((REAL() <= REAL(1.2)).is_unknown(), details, "? (REAL) <= REAL", err);
  unitest((REAL(1.2) <= REAL()).is_unknown(), details, "REAL <= ? (REAL)", err);
  unitest((REAL() <= REAL()).is_unknown(), details, "? (REAL) <= ? (REAL)", err);

  /* меньше или равно INTEGER */

  unitest((REAL(3) <= INTEGER(1)).is_false() &&
          (REAL(1) <= INTEGER(3)).is_true() &&
          (REAL(3) <= INTEGER(3)).is_true(), details, "REAL <= INTEGER", err);
  unitest((REAL() <= INTEGER(1)).is_unknown(), details, "? (REAL) <= INTEGER", err);
  unitest((REAL(1.2) <= INTEGER()).is_unknown(), details, "REAL <= ? (INTEGER)", err);
  unitest((REAL() <= INTEGER()).is_unknown(), details, "? (REAL) <= ? (INTEGER)", err);

  unitest((INTEGER(3) <= REAL(1)).is_false() &&
          (INTEGER(1) <= REAL(3)).is_true() &&
          (INTEGER(3) <= REAL(3)).is_true(), details, "INTEGER <= REAL", err);
  unitest((INTEGER() <= REAL(1)).is_unknown(), details, "? (INTEGER) <= REAL", err);
  unitest((INTEGER(1) <= REAL()).is_unknown(), details, "INTEGER <= ? (REAL)", err);
  unitest((INTEGER() <= REAL()).is_unknown(), details, "? (INTEGER) <= ? (REAL)", err);

  /* меньше или равно real_type */

  unitest((REAL(3.5) <= static_cast<real_type>(1.2)).is_false() &&
          (REAL(1.2) <= static_cast<real_type>(3.5)).is_true() &&
          (REAL(3.5) <= static_cast<real_type>(3.5)).is_true(), details, "REAL <= real_type", err);
  unitest((REAL() <= static_cast<real_type>(1.2)).is_unknown(), details, "? (REAL) <= real_type", err);

  unitest((static_cast<real_type>(3.5) <= REAL(1.2)).is_false() &&
          (static_cast<real_type>(1.2) <= REAL(3.5)).is_true() &&
          (static_cast<real_type>(3.5) <= REAL(3.5)).is_true(), details, "real_type <= REAL", err);
  unitest((static_cast<real_type>(1.2) <= REAL()).is_unknown(), details, "real_type <= ? (REAL)", err);

  /* меньше или равно integer_type */

  unitest((REAL(3) <= static_cast<integer_type>(1)).is_false() &&
          (REAL(1) <= static_cast<integer_type>(3)).is_true() &&
          (REAL(3) <= static_cast<integer_type>(3)).is_true(), details, "REAL <= integer_type", err);
  unitest((REAL()  <= static_cast<integer_type>(1)).is_unknown(), details, "? (REAL) <= integer_type", err);

  unitest((static_cast<integer_type>(3) <= REAL(1)).is_false() &&
          (static_cast<integer_type>(1) <= REAL(3)).is_true() &&
          (static_cast<integer_type>(3) <= REAL(3)).is_true(), details, "integer_type <= REAL", err);
  unitest((static_cast<integer_type>(1) <= REAL()).is_unknown(), details, "integer_type <= ? (REAL)", err);

  /* меньше или равно int */

  unitest((REAL(3) <= static_cast<int>(1)).is_false() &&
          (REAL(1) <= static_cast<int>(3)).is_true() &&
          (REAL(3) <= static_cast<int>(3)).is_true(), details, "REAL <= int", err);
  unitest((REAL()  <= static_cast<int>(1)).is_unknown(), details, "? (REAL) <= int", err);

  unitest((static_cast<int>(3) <= REAL(1)).is_false() &&
          (static_cast<int>(1) <= REAL(3)).is_true() &&
          (static_cast<int>(3) <= REAL(3)).is_true(), details, "int <= REAL", err);
  unitest((static_cast<int>(1) <= REAL()).is_unknown(), details, "int <= ? (REAL)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_integer_rel_eq(bool details) {
  print_title(details, "INTEGER RELATIONS '=' ");
  test_t err = test_t::TEST_OK;

  /* равно INTEGER */

  unitest((INTEGER(1) == INTEGER(1)).is_true() &&
          (INTEGER(1) == INTEGER(3)).is_false() &&
          (INTEGER(3) == INTEGER(1)).is_false(), details, "INTEGER = INTEGER", err);
  unitest((INTEGER() == INTEGER(1)).is_unknown(), details, "? (INTEGER) = INTEGER", err);
  unitest((INTEGER(1) == INTEGER()).is_unknown(), details, "INTEGER = ? (INTEGER)", err);
  unitest((INTEGER() == INTEGER()).is_unknown(), details, "? (INTEGER) = ? (INTEGER)", err);

  /* равно real_type */

  unitest((INTEGER(1) == static_cast<real_type>(1)).is_true() &&
          (INTEGER(1) == static_cast<real_type>(2)).is_false() &&
          (INTEGER(2) == static_cast<real_type>(1)).is_false(), details, "INTEGER = real_type", err);
  unitest((INTEGER() == static_cast<real_type>(1)).is_unknown(), details, "? (INTEGER) = real_type", err);

  unitest((static_cast<real_type>(1.0) == INTEGER(1)).is_true() &&
          (static_cast<real_type>(2.0) == INTEGER(1)).is_false() &&
          (static_cast<real_type>(1.0) == INTEGER(2)).is_false(), details, "real_type = INTEGER", err);
  unitest((static_cast<real_type>(1.0) == INTEGER()).is_unknown(), details, "real_type = ? (INTEGER)", err);

  /* равно integer_type */

  unitest((INTEGER(1) == static_cast<integer_type>(1)).is_true() &&
          (INTEGER(1) == static_cast<integer_type>(2)).is_false() &&
          (INTEGER(2) == static_cast<integer_type>(1)).is_false(), details, "INTEGER = integer_type", err);
  unitest((INTEGER() == static_cast<integer_type>(1)).is_unknown(), details, "? (INTEGER) = integer_type", err);

  unitest((static_cast<integer_type>(1) == INTEGER(1)).is_true() &&
          (static_cast<integer_type>(2) == INTEGER(1)).is_false() &&
          (static_cast<integer_type>(1) == INTEGER(2)).is_false(), details, "integer_type = INTEGER", err);
  unitest((static_cast<integer_type>(1) == INTEGER()).is_unknown(), details, "integer_type = ? (INTEGER)", err);

  /* равно int */

  unitest((INTEGER(1) == static_cast<int>(1)).is_true() &&
          (INTEGER(1) == static_cast<int>(2)).is_false() &&
          (INTEGER(2) == static_cast<int>(1)).is_false(), details, "INTEGER = int", err);
  unitest((INTEGER() == static_cast<int>(1)).is_unknown(), details, "? (INTEGER) = int", err);

  unitest((static_cast<int>(1) == INTEGER(1)).is_true() &&
          (static_cast<int>(2) == INTEGER(1)).is_false() &&
          (static_cast<int>(1) == INTEGER(2)).is_false(), details, "int = INTEGER", err);
  unitest((static_cast<int>(1) == INTEGER()).is_unknown(), details, "int = ? (INTEGER)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_integer_rel_neq(bool details) {
  print_title(details, "INTEGER RELATIONS '<>' ");
  test_t err = test_t::TEST_OK;

  /* не равно INTEGER */

  unitest((INTEGER(1) != INTEGER(1)).is_false() &&
          (INTEGER(1) != INTEGER(3)).is_true()  &&
          (INTEGER(3) != INTEGER(1)).is_true(), details, "INTEGER <> INTEGER", err);
  unitest((INTEGER() != INTEGER(1)).is_unknown(), details, "? (INTEGER) <> INTEGER", err);
  unitest((INTEGER(1) != INTEGER()).is_unknown(), details, "INTEGER <> ? (INTEGER)", err);
  unitest((INTEGER() != INTEGER()).is_unknown(), details, "? (INTEGER) <> ? (INTEGER)", err);

  /* не равно real_type */

  unitest((INTEGER(1) != static_cast<real_type>(1)).is_false() &&
          (INTEGER(1) != static_cast<real_type>(2)).is_true()  &&
          (INTEGER(2) != static_cast<real_type>(1)).is_true(), details, "INTEGER <> real_type", err);
  unitest((INTEGER() != static_cast<real_type>(1)).is_unknown(), details, "? (INTEGER) <> real_type", err);

  unitest((static_cast<real_type>(1) != INTEGER(1)).is_false() &&
          (static_cast<real_type>(2) != INTEGER(1)).is_true()  &&
          (static_cast<real_type>(1) != INTEGER(2)).is_true(), details, "real_type <> INTEGER", err);
  unitest((static_cast<real_type>(1) != INTEGER()).is_unknown(), details, "real_type <> ? (INTEGER)", err);

  /* не равно integer_type */

  unitest((INTEGER(1) != static_cast<integer_type>(1)).is_false() &&
          (INTEGER(1) != static_cast<integer_type>(2)).is_true()  &&
          (INTEGER(2) != static_cast<integer_type>(1)).is_true(), details, "INTEGER <> integer_type", err);
  unitest((INTEGER() != static_cast<integer_type>(1)).is_unknown(), details, "? (INTEGER) <> integer_type", err);

  unitest((static_cast<integer_type>(1) != INTEGER(1)).is_false() &&
          (static_cast<integer_type>(2) != INTEGER(1)).is_true()  &&
          (static_cast<integer_type>(1) != INTEGER(2)).is_true(), details, "integer_type <> INTEGER", err);
  unitest((static_cast<integer_type>(1) != INTEGER()).is_unknown(), details, "integer_type <> ? (INTEGER)", err);

  /* не равно int */

  unitest((INTEGER(1) != static_cast<int>(1)).is_false() &&
          (INTEGER(1) != static_cast<int>(2)).is_true()  &&
          (INTEGER(2) != static_cast<int>(1)).is_true(), details, "INTEGER <> int", err);
  unitest((INTEGER() != static_cast<int>(1)).is_unknown(), details, "? (INTEGER) <> int", err);

  unitest((static_cast<int>(1) != INTEGER(1)).is_false() &&
          (static_cast<int>(2) != INTEGER(1)).is_true()  &&
          (static_cast<int>(1) != INTEGER(2)).is_true(), details, "int <> INTEGER", err);
  unitest((static_cast<int>(1) != INTEGER()).is_unknown(), details, "int <> ? (INTEGER)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_integer_rel_bt(bool details) {
  print_title(details, "INTEGER RELATIONS '>' ");
  test_t err = test_t::TEST_OK;

  /* больше INTEGER */

  unitest((INTEGER(1) > INTEGER(1)).is_false() &&
          (INTEGER(1) > INTEGER(3)).is_false()  &&
          (INTEGER(3) > INTEGER(1)).is_true(), details, "INTEGER > INTEGER", err);
  unitest((INTEGER() > INTEGER(1)).is_unknown(), details, "? (INTEGER) > INTEGER", err);
  unitest((INTEGER(1) > INTEGER()).is_unknown(), details, "INTEGER > ? (INTEGER)", err);
  unitest((INTEGER() > INTEGER()).is_unknown(), details, "? (INTEGER) > ? (INTEGER)", err);

  /* больше real_type */

  unitest((INTEGER(1) > static_cast<real_type>(1)).is_false() &&
          (INTEGER(1) > static_cast<real_type>(2)).is_false()  &&
          (INTEGER(2) > static_cast<real_type>(1)).is_true(), details, "INTEGER > real_type", err);
  unitest((INTEGER() > static_cast<real_type>(1)).is_unknown(), details, "? (INTEGER) > real_type", err);

  unitest((static_cast<real_type>(1) > INTEGER(1)).is_false() &&
          (static_cast<real_type>(2) > INTEGER(1)).is_true()  &&
          (static_cast<real_type>(1) > INTEGER(2)).is_false(), details, "real_type > INTEGER", err);
  unitest((static_cast<real_type>(1) > INTEGER()).is_unknown(), details, "real_type > ? (INTEGER)", err);

  /* больше integer_type */

  unitest((INTEGER(1) > static_cast<integer_type>(1)).is_false() &&
          (INTEGER(1) > static_cast<integer_type>(2)).is_false()  &&
          (INTEGER(2) > static_cast<integer_type>(1)).is_true(), details, "INTEGER > integer_type", err);
  unitest((INTEGER() > static_cast<integer_type>(1)).is_unknown(), details, "? (INTEGER) > integer_type", err);

  unitest((static_cast<integer_type>(1) > INTEGER(1)).is_false() &&
          (static_cast<integer_type>(2) > INTEGER(1)).is_true()  &&
          (static_cast<integer_type>(1) > INTEGER(2)).is_false(), details, "integer_type > INTEGER", err);
  unitest((static_cast<integer_type>(1) > INTEGER()).is_unknown(), details, "integer_type > ? (INTEGER)", err);

  /* больше int */

  unitest((INTEGER(1) > static_cast<int>(1)).is_false() &&
          (INTEGER(1) > static_cast<int>(2)).is_false()  &&
          (INTEGER(2) > static_cast<int>(1)).is_true(), details, "INTEGER > int", err);
  unitest((INTEGER() > static_cast<int>(1)).is_unknown(), details, "? (INTEGER) > int", err);

  unitest((static_cast<int>(1) > INTEGER(1)).is_false() &&
          (static_cast<int>(2) > INTEGER(1)).is_true()  &&
          (static_cast<int>(1) > INTEGER(2)).is_false(), details, "int > INTEGER", err);
  unitest((static_cast<int>(1) > INTEGER()).is_unknown(), details, "int > ? (INTEGER)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_integer_rel_beq(bool details) {
  print_title(details, "INTEGER RELATIONS '>=' ");
  test_t err = test_t::TEST_OK;

  /* больше или равно INTEGER */

  unitest((INTEGER(1) >= INTEGER(1)).is_true() &&
          (INTEGER(1) >= INTEGER(3)).is_false()  &&
          (INTEGER(3) >= INTEGER(1)).is_true(), details, "INTEGER >= INTEGER", err);
  unitest((INTEGER() >= INTEGER(1)).is_unknown(), details, "? (INTEGER) >= INTEGER", err);
  unitest((INTEGER(1) >= INTEGER()).is_unknown(), details, "INTEGER >= ? (INTEGER)", err);
  unitest((INTEGER() >= INTEGER()).is_unknown(), details, "? (INTEGER) >= ? (INTEGER)", err);

  /* больше или равно real_type */

  unitest((INTEGER(1) >= static_cast<real_type>(1)).is_true() &&
          (INTEGER(1) >= static_cast<real_type>(2)).is_false()  &&
          (INTEGER(2) >= static_cast<real_type>(1)).is_true(), details, "INTEGER >= real_type", err);
  unitest((INTEGER() >= static_cast<real_type>(1)).is_unknown(), details, "? (INTEGER) >= real_type", err);

  unitest((static_cast<real_type>(1) >= INTEGER(1)).is_true() &&
          (static_cast<real_type>(2) >= INTEGER(1)).is_true()  &&
          (static_cast<real_type>(1) >= INTEGER(2)).is_false(), details, "real_type >= INTEGER", err);
  unitest((static_cast<real_type>(1) >= INTEGER()).is_unknown(), details, "real_type >= ? (INTEGER)", err);

  /* больше или равно integer_type */

  unitest((INTEGER(1) >= static_cast<integer_type>(1)).is_true() &&
          (INTEGER(1) >= static_cast<integer_type>(2)).is_false()  &&
          (INTEGER(2) >= static_cast<integer_type>(1)).is_true(), details, "INTEGER >= integer_type", err);
  unitest((INTEGER() >= static_cast<integer_type>(1)).is_unknown(), details, "? (INTEGER) >= integer_type", err);

  unitest((static_cast<integer_type>(1) >= INTEGER(1)).is_true() &&
          (static_cast<integer_type>(2) >= INTEGER(1)).is_true()  &&
          (static_cast<integer_type>(1) >= INTEGER(2)).is_false(), details, "integer_type >= INTEGER", err);
  unitest((static_cast<integer_type>(1) >= INTEGER()).is_unknown(), details, "integer_type >= ? (INTEGER)", err);

  /* больше или равно int */

  unitest((INTEGER(1) >= static_cast<int>(1)).is_true() &&
          (INTEGER(1) >= static_cast<int>(2)).is_false()  &&
          (INTEGER(2) >= static_cast<int>(1)).is_true(), details, "INTEGER >= int", err);
  unitest((INTEGER() >= static_cast<int>(1)).is_unknown(), details, "? (INTEGER) >= int", err);

  unitest((static_cast<int>(1) >= INTEGER(1)).is_true() &&
          (static_cast<int>(2) >= INTEGER(1)).is_true()  &&
          (static_cast<int>(1) >= INTEGER(2)).is_false(), details, "int >= INTEGER", err);
  unitest((static_cast<int>(1) >= INTEGER()).is_unknown(), details, "int >= ? (INTEGER)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_integer_rel_lt(bool details) {
  print_title(details, "INTEGER RELATIONS '<' ");
  test_t err = test_t::TEST_OK;

  /* меньше INTEGER */

  unitest((INTEGER(1) < INTEGER(1)).is_false() &&
          (INTEGER(1) < INTEGER(3)).is_true()  &&
          (INTEGER(3) < INTEGER(1)).is_false(), details, "INTEGER < INTEGER", err);
  unitest((INTEGER() < INTEGER(1)).is_unknown(), details, "? (INTEGER) < INTEGER", err);
  unitest((INTEGER(1) < INTEGER()).is_unknown(), details, "INTEGER < ? (INTEGER)", err);
  unitest((INTEGER() < INTEGER()).is_unknown(), details, "? (INTEGER) < ? (INTEGER)", err);

  /* меньше real_type */

  unitest((INTEGER(1) < static_cast<real_type>(1)).is_false() &&
          (INTEGER(1) < static_cast<real_type>(2)).is_true()  &&
          (INTEGER(2) < static_cast<real_type>(1)).is_false(), details, "INTEGER < real_type", err);
  unitest((INTEGER() < static_cast<real_type>(1)).is_unknown(), details, "? (INTEGER) < real_type", err);

  unitest((static_cast<real_type>(1) < INTEGER(1)).is_false() &&
          (static_cast<real_type>(2) < INTEGER(1)).is_false()  &&
          (static_cast<real_type>(1) < INTEGER(2)).is_true(), details, "real_type < INTEGER", err);
  unitest((static_cast<real_type>(1) < INTEGER()).is_unknown(), details, "real_type < ? (INTEGER)", err);

  /* меньше integer_type */

  unitest((INTEGER(1) < static_cast<integer_type>(1)).is_false() &&
          (INTEGER(1) < static_cast<integer_type>(2)).is_true()  &&
          (INTEGER(2) < static_cast<integer_type>(1)).is_false(), details, "INTEGER < integer_type", err);
  unitest((INTEGER() < static_cast<integer_type>(1)).is_unknown(), details, "? (INTEGER) < integer_type", err);

  unitest((static_cast<integer_type>(1) < INTEGER(1)).is_false() &&
          (static_cast<integer_type>(2) < INTEGER(1)).is_false()  &&
          (static_cast<integer_type>(1) < INTEGER(2)).is_true(), details, "integer_type < INTEGER", err);
  unitest((static_cast<integer_type>(1) < INTEGER()).is_unknown(), details, "integer_type < ? (INTEGER)", err);

  /* меньше int */

  unitest((INTEGER(1) < static_cast<int>(1)).is_false() &&
          (INTEGER(1) < static_cast<int>(2)).is_true()  &&
          (INTEGER(2) < static_cast<int>(1)).is_false(), details, "INTEGER < int", err);
  unitest((INTEGER() < static_cast<int>(1)).is_unknown(), details, "? (INTEGER) < int", err);

  unitest((static_cast<int>(1) < INTEGER(1)).is_false() &&
          (static_cast<int>(2) < INTEGER(1)).is_false()  &&
          (static_cast<int>(1) < INTEGER(2)).is_true(), details, "int < INTEGER", err);
  unitest((static_cast<int>(1) < INTEGER()).is_unknown(), details, "int < ? (INTEGER)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_integer_rel_leq(bool details) {
  print_title(details, "INTEGER RELATIONS '<=' ");
  test_t err = test_t::TEST_OK;

  /* меньше или равно INTEGER */

  unitest((INTEGER(1) <= INTEGER(1)).is_true() &&
          (INTEGER(1) <= INTEGER(3)).is_true()  &&
          (INTEGER(3) <= INTEGER(1)).is_false(), details, "INTEGER <= INTEGER", err);
  unitest((INTEGER() <= INTEGER(1)).is_unknown(), details, "? (INTEGER) <= INTEGER", err);
  unitest((INTEGER(1) <= INTEGER()).is_unknown(), details, "INTEGER <= ? (INTEGER)", err);
  unitest((INTEGER() <= INTEGER()).is_unknown(), details, "? (INTEGER) <= ? (INTEGER)", err);

  /* меньше или равно real_type */

  unitest((INTEGER(1) <= static_cast<real_type>(1)).is_true() &&
          (INTEGER(1) <= static_cast<real_type>(2)).is_true()  &&
          (INTEGER(2) <= static_cast<real_type>(1)).is_false(), details, "INTEGER <= real_type", err);
  unitest((INTEGER() <= static_cast<real_type>(1)).is_unknown(), details, "? (INTEGER) <= real_type", err);

  unitest((static_cast<real_type>(1) <= INTEGER(1)).is_true() &&
          (static_cast<real_type>(2) <= INTEGER(1)).is_false()  &&
          (static_cast<real_type>(1) <= INTEGER(2)).is_true(), details, "real_type <= INTEGER", err);
  unitest((static_cast<real_type>(1) <= INTEGER()).is_unknown(), details, "real_type <= ? (INTEGER)", err);

  /* меньше или равно integer_type */

  unitest((INTEGER(1) <= static_cast<integer_type>(1)).is_true() &&
          (INTEGER(1) <= static_cast<integer_type>(2)).is_true()  &&
          (INTEGER(2) <= static_cast<integer_type>(1)).is_false(), details, "INTEGER <= integer_type", err);
  unitest((INTEGER() <= static_cast<integer_type>(1)).is_unknown(), details, "? (INTEGER) <= integer_type", err);

  unitest((static_cast<integer_type>(1) <= INTEGER(1)).is_true() &&
          (static_cast<integer_type>(2) <= INTEGER(1)).is_false()  &&
          (static_cast<integer_type>(1) <= INTEGER(2)).is_true(), details, "integer_type <= INTEGER", err);
  unitest((static_cast<integer_type>(1) <= INTEGER()).is_unknown(), details, "integer_type <= ? (INTEGER)", err);

  /* меньше или равно int */

  unitest((INTEGER(1) <= static_cast<int>(1)).is_true() &&
          (INTEGER(1) <= static_cast<int>(2)).is_true()  &&
          (INTEGER(2) <= static_cast<int>(1)).is_false(), details, "INTEGER <= int", err);
  unitest((INTEGER() <= static_cast<int>(1)).is_unknown(), details, "? (INTEGER) <= int", err);

  unitest((static_cast<int>(1) <= INTEGER(1)).is_true() &&
          (static_cast<int>(2) <= INTEGER(1)).is_false()  &&
          (static_cast<int>(1) <= INTEGER(2)).is_true(), details, "int <= INTEGER", err);
  unitest((static_cast<int>(1) <= INTEGER()).is_unknown(), details, "int <= ? (INTEGER)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_logical_rel_eq(bool details) {
  print_title(details, "LOGICAL RELATIONS '=' ");
  test_t err = test_t::TEST_OK;
  LOGICAL l1, l2, l3, l4, l5, l6, lt1, lt2, lf1, lf2, lu1, lu2;
  lt1 = TRUE;
  lt2 = TRUE;
  lf1 = FALSE;
  lf2 = FALSE;
  lu1 = UNKNOWN;
  lu2 = UNKNOWN;
  BOOLEAN bt, bf;
  bt = TRUE;
  bf = FALSE;

  /* равно */

  unitest((lt1 == lt2).is_true()  &&
          (lt1 == lu2).is_false() &&
          (lt1 == lf2).is_false() &&
          (lu1 == lt2).is_false() &&
          (lu1 == lu2).is_true()  &&
          (lu1 == lf2).is_false() &&
          (lf1 == lt2).is_false() &&
          (lf1 == lu2).is_false() &&
          (lf1 == lf2).is_true(), details, "LOGICAL == LOGICAL", err);

  l1 = LOGICAL() == lt1;
  l2 = LOGICAL() == lu1;
  l3 = LOGICAL() == lf1;
  unitest(l1.is_unknown() &&
          l2.is_unknown() &&
          l3.is_unknown(), details, "? == LOGICAL", err);

  l1 = lt1 == LOGICAL();
  l2 = lu1 == LOGICAL();
  l3 = lf1 == LOGICAL();
  l4 = lt1 == BOOLEAN();
  l5 = lu1 == BOOLEAN();
  l6 = lf1 == BOOLEAN();
  unitest(l1.is_unknown() &&
          l2.is_unknown() &&
          l3.is_unknown() &&
          l4.is_unknown() &&
          l5.is_unknown() &&
          l6.is_unknown(), details, "LOGICAL == ?", err);

  unitest((lt1 == bt).is_true() &&
          (lt1 == bf).is_false() &&
          (lu1 == bt).is_false() &&
          (lu1 == bf).is_false() &&
          (lf1 == bt).is_false() &&
          (lf1 == bf).is_true(), details, "LOGICAL == BOOLEAN", err);

  l1 = LOGICAL() == bt;
  l2 = LOGICAL() == bf;
  unitest(l1.is_unknown() &&
          l2.is_unknown(), details, "? == BOOLEAN", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_logical_rel_neq(bool details) {
  print_title(details, "LOGICAL RELATIONS '<>' ");
  test_t err = test_t::TEST_OK;
  LOGICAL l1, l2, l3, l4, l5, l6, lt1, lt2, lf1, lf2, lu1, lu2;
  lt1 = TRUE;
  lt2 = TRUE;
  lf1 = FALSE;
  lf2 = FALSE;
  lu1 = UNKNOWN;
  lu2 = UNKNOWN;
  BOOLEAN bt, bf;
  bt = TRUE;
  bf = FALSE;

  /* не равно */

  unitest((lt1 != lt2).is_false() &&
          (lt1 != lu2).is_true() &&
          (lt1 != lf2).is_true() &&
          (lu1 != lt2).is_true() &&
          (lu1 != lu2).is_false() &&
          (lu1 != lf2).is_true() &&
          (lf1 != lt2).is_true() &&
          (lf1 != lu2).is_true() &&
          (lf1 != lf2).is_false(), details, "LOGICAL != LOGICAL", err);

  l1 = LOGICAL() != lt1;
  l2 = LOGICAL() != lu1;
  l3 = LOGICAL() != lf1;
  unitest(l1.is_unknown() &&
          l2.is_unknown() &&
          l3.is_unknown(), details, "? != LOGICAL", err);

  l1 = lt1 != LOGICAL();
  l2 = lu1 != LOGICAL();
  l3 = lf1 != LOGICAL();
  l4 = lt1 != BOOLEAN();
  l5 = lu1 != BOOLEAN();
  l6 = lf1 != BOOLEAN();
  unitest(l1.is_unknown() &&
          l2.is_unknown() &&
          l3.is_unknown() &&
          l4.is_unknown() &&
          l5.is_unknown() &&
          l6.is_unknown(), details, "LOGICAL != ?", err);

  unitest((lt1 != bf).is_true() &&
          (lf1 != bt).is_true() &&
          (lt1 != bt).is_false() &&
          (lf1 != bf).is_false(), details, "LOGICAL != BOOLEAN", err);

  l1 = LOGICAL() != bf;
  l2 = LOGICAL() != bt;
  if (l1.is_unknown() && l2.is_unknown()) {
    print_res(details, "? != BOOLEAN", test_t::TEST_OK);
  } else {
    print_res(details, "? != BOOLEAN", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_logical_rel_bt(bool details) {
  print_title(details, "LOGICAL RELATIONS '>' ");
  test_t err = test_t::TEST_OK;
  LOGICAL l1, l2, l3, l4, l5, l6, lt1, lt2, lf1, lf2, lu1, lu2;
  lt1 = TRUE;
  lt2 = TRUE;
  lf1 = FALSE;
  lf2 = FALSE;
  lu1 = UNKNOWN;
  lu2 = UNKNOWN;
  BOOLEAN bt, bf;
  bt = TRUE;
  bf = FALSE;

  /* больше чем */

  IF (!(lt1 > lt2) &&  (lt1 > lu2) &&  (lt1 > lf2) &&
      !(lu1 > lt2) && !(lu1 > lu2) &&  (lu1 > lf2) &&
      !(lf1 > lt2) && !(lf1 > lu2) && !(lf1 > lf2)) {
    print_res(details, "LOGICAL > LOGICAL", test_t::TEST_OK);
  } else {
    print_res(details, "LOGICAL > LOGICAL", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l1 = LOGICAL() > lf1;
  l2 = LOGICAL() > lu1;
  l3 = LOGICAL() > lt1;
  if (l1.is_unknown() && l2.is_unknown() && l3.is_unknown()) {
    print_res(details, "? > LOGICAL", test_t::TEST_OK);
  } else {
    print_res(details, "? > LOGICAL", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l1 = lf1 > LOGICAL();
  l2 = lu1 > LOGICAL();
  l3 = lt1 > LOGICAL();
  l4 = lt1 > BOOLEAN();
  l5 = lu1 > BOOLEAN();
  l6 = lf1 > BOOLEAN();
  if (l1.is_unknown() && l2.is_unknown() && l3.is_unknown() &&
      l4.is_unknown() && l5.is_unknown() && l6.is_unknown()) {
    print_res(details, "LOGICAL > ?", test_t::TEST_OK);
  } else {                          
    print_res(details, "LOGICAL > ?", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  IF (!(lt1 > bt) &&  (lt1 > bf) &&
      !(lu1 > bt) &&  (lu1 > bf) &&
      !(lf1 > bt) && !(lf1 > bf)) {
    print_res(details, "LOGICAL > BOOLEAN", test_t::TEST_OK);
  } else {
    print_res(details, "LOGICAL > BOOLEAN", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_logical_rel_beq(bool details) {
  print_title(details, "LOGICAL RELATIONS '>=' ");
  test_t err = test_t::TEST_OK;
  LOGICAL l1, l2, l3, l4, l5, l6, lt1, lt2, lf1, lf2, lu1, lu2;
  lt1 = TRUE;
  lt2 = TRUE;
  lf1 = FALSE;
  lf2 = FALSE;
  lu1 = UNKNOWN;
  lu2 = UNKNOWN;
  BOOLEAN bt, bf;
  bt = TRUE;
  bf = FALSE;

  /* больше или равно */

  IF ( (lt1 >= lt2) &&  (lt1 >= lu2) &&  (lt1 >= lf2) &&
      !(lu1 >= lt2) &&  (lu1 >= lu2) &&  (lu1 >= lf2) &&
      !(lf1 >= lt2) && !(lf1 >= lu2) &&  (lf1 >= lf2)) {
    print_res(details, "LOGICAL >= LOGICAL", test_t::TEST_OK);
  } else {
    print_res(details, "LOGICAL >= LOGICAL", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l1 = LOGICAL() >= lf1;
  l2 = LOGICAL() >= lu1;
  l3 = LOGICAL() >= lt1;
  if (l1.is_unknown() && l2.is_unknown() && l3.is_unknown()) {
    print_res(details, "? >= LOGICAL", test_t::TEST_OK);
  } else {
    print_res(details, "? >= LOGICAL", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l1 = lf1 >= LOGICAL();
  l2 = lu1 >= LOGICAL();
  l3 = lt1 >= LOGICAL();
  l4 = lt1 >= BOOLEAN();
  l5 = lu1 >= BOOLEAN();
  l6 = lf1 >= BOOLEAN();
  if (l1.is_unknown() && l2.is_unknown() && l3.is_unknown() &&
      l4.is_unknown() && l5.is_unknown() && l6.is_unknown()) {
    print_res(details, "LOGICAL >= ?", test_t::TEST_OK);
  } else {                          
    print_res(details, "LOGICAL >= ?", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  IF ( (lt1 >= bt) &&  (lt1 >= bf) &&
      !(lu1 >= bt) &&  (lu1 >= bf) &&
      !(lf1 >= bt) &&  (lf1 >= bf)) {
    print_res(details, "LOGICAL >= BOOLEAN", test_t::TEST_OK);
  } else {
    print_res(details, "LOGICAL >= BOOLEAN", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_logical_rel_lt(bool details) {
  print_title(details, "LOGICAL RELATIONS '<' ");
  test_t err = test_t::TEST_OK;
  LOGICAL l1, l2, l3, l4, l5, l6, lt1, lt2, lf1, lf2, lu1, lu2;
  lt1 = TRUE;
  lt2 = TRUE;
  lf1 = FALSE;
  lf2 = FALSE;
  lu1 = UNKNOWN;
  lu2 = UNKNOWN;
  BOOLEAN bt, bf;
  bt = TRUE;
  bf = FALSE;

  /* меньше чем */

  IF (!(lt1 < lt2) && !(lt1 < lu2) && !(lt1 < lf2) &&
       (lu1 < lt2) && !(lu1 < lu2) && !(lu1 < lf2) &&
       (lf1 < lt2) &&  (lf1 < lu2) && !(lf1 < lf2)) {
    print_res(details, "LOGICAL < LOGICAL", test_t::TEST_OK);
  } else {
    print_res(details, "LOGICAL < LOGICAL", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l1 = LOGICAL() < lf1;
  l2 = LOGICAL() < lu1;
  l3 = LOGICAL() < lt1;
  if (l1.is_unknown() && l2.is_unknown() && l3.is_unknown()) {
    print_res(details, "? < LOGICAL", test_t::TEST_OK);
  } else {
    print_res(details, "? < LOGICAL", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l1 = lf1 < LOGICAL();
  l2 = lu1 < LOGICAL();
  l3 = lt1 < LOGICAL();
  l4 = lt1 < BOOLEAN();
  l5 = lu1 < BOOLEAN();
  l6 = lf1 < BOOLEAN();
  if (l1.is_unknown() && l2.is_unknown() && l3.is_unknown() &&
      l4.is_unknown() && l5.is_unknown() && l6.is_unknown()) {
    print_res(details, "LOGICAL < ?", test_t::TEST_OK);
  } else {                          
    print_res(details, "LOGICAL < ?", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  IF (!(lt1 < bt) && !(lt1 < bf) &&
       (lu1 < bt) && !(lu1 < bf) &&
       (lf1 < bt) && !(lf1 < bf)) {
    print_res(details, "LOGICAL < BOOLEAN", test_t::TEST_OK);
  } else {
    print_res(details, "LOGICAL < BOOLEAN", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}


static bool test_logical_rel_leq(bool details) {
  print_title(details, "LOGICAL RELATIONS '<=' ");
  test_t err = test_t::TEST_OK;
  LOGICAL l1, l2, l3, l4, l5, l6, lt1, lt2, lf1, lf2, lu1, lu2;
  lt1 = TRUE;
  lt2 = TRUE;
  lf1 = FALSE;
  lf2 = FALSE;
  lu1 = UNKNOWN;
  lu2 = UNKNOWN;
  BOOLEAN bt, bf;
  bt = TRUE;
  bf = FALSE;

  /* меньше или равно */

  IF ( (lt1 <= lt2) && !(lt1 <= lu2) && !(lt1 <= lf2) &&
       (lu1 <= lt2) &&  (lu1 <= lu2) && !(lu1 <= lf2) &&
       (lf1 <= lt2) &&  (lf1 <= lu2) &&  (lf1 <= lf2)) {
    print_res(details, "LOGICAL <= LOGICAL", test_t::TEST_OK);
  } else {
    print_res(details, "LOGICAL <= LOGICAL", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l1 = LOGICAL() <= lf1;
  l2 = LOGICAL() <= lu1;
  l3 = LOGICAL() <= lt1;
  if (l1.is_unknown() && l2.is_unknown() && l3.is_unknown()) {
    print_res(details, "? <= LOGICAL", test_t::TEST_OK);
  } else {
    print_res(details, "? <= LOGICAL", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l1 = lf1 <= LOGICAL();
  l2 = lu1 <= LOGICAL();
  l3 = lt1 <= LOGICAL();
  l4 = lt1 <= BOOLEAN();
  l5 = lu1 <= BOOLEAN();
  l6 = lf1 <= BOOLEAN();
  if (l1.is_unknown() && l2.is_unknown() && l3.is_unknown() &&
      l4.is_unknown() && l5.is_unknown() && l6.is_unknown()) {
    print_res(details, "LOGICAL <= ?", test_t::TEST_OK);
  } else {                          
    print_res(details, "LOGICAL <= ?", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  IF ( (lt1 <= bt) && !(lt1 <= bf) &&
       (lu1 <= bt) && !(lu1 <= bf) &&
       (lf1 <= bt) &&  (lf1 <= bf)) {
    print_res(details, "LOGICAL <= BOOLEAN", test_t::TEST_OK);
  } else {
    print_res(details, "LOGICAL <= BOOLEAN", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_boolean_rel(bool details) {
  print_title(details, "BOOLEAN RELATIONS ");
  test_t err = test_t::TEST_OK;
  LOGICAL l1, l2, l3, l4, lt, lf, lu;
  lt = TRUE;
  lf = FALSE;
  lu = UNKNOWN;
  BOOLEAN bt1, bt2, bf1, bf2;
  bt1 = TRUE;
  bt2 = TRUE;
  bf1 = FALSE;
  bf2 = FALSE;

  /* равно */

  IF ( (bt1 == bt2) && !(bt1 == bf2) &&
      !(bf1 == bt2) &&  (bf1 == bf2)) {
    print_res(details, "BOOLEAN == BOOLEAN", test_t::TEST_OK);
  } else {
    print_res(details, "BOOLEAN == BOOLEAN", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l1 = BOOLEAN() == bt1;
  l2 = BOOLEAN() == bf1;
  if (l1.is_unknown() && l2.is_unknown()) {
    print_res(details, "? == BOOLEAN", test_t::TEST_OK);
  } else {
    print_res(details, "? == BOOLEAN", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l1 = bt1 == BOOLEAN();
  l2 = bf1 == BOOLEAN();
  l3 = bt1 == LOGICAL();
  l4 = bf1 == LOGICAL();
  if (l1.is_unknown() && l2.is_unknown() && l3.is_unknown() && l4.is_unknown()) {
    print_res(details, "BOOLEAN == ?", test_t::TEST_OK);
  } else {                          
    print_res(details, "BOOLEAN == ?", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  IF ( (bt1 == lt) && !(bt1 == lu) && !(bt1 == lf) &&
      !(bf1 == lt) && !(bf1 == lu) &&  (bf1 == lf)) {
    print_res(details, "BOOLEAN == LOGICAL", test_t::TEST_OK);
  } else {
    print_res(details, "BOOLEAN == LOGICAL", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l1 = BOOLEAN() == lt;
  l2 = BOOLEAN() == lf;
  l3 = BOOLEAN() == lu;
  if (l1.is_unknown() && l2.is_unknown() && l3.is_unknown()) {
    print_res(details, "? == LOGICAL", test_t::TEST_OK);
  } else {
    print_res(details, "? == LOGICAL", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }


  /* не равно */

  IF (!(bt1 != bt2) &&  (bt1 != bf2) &&
       (bf1 != bt2) && !(bf1 != bf2)) {
    print_res(details, "BOOLEAN != BOOLEAN", test_t::TEST_OK);
  } else {
    print_res(details, "BOOLEAN != BOOLEAN", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l1 = BOOLEAN() != bt1;
  l2 = BOOLEAN() != bf1;
  if (l1.is_unknown() && l2.is_unknown()) {
    print_res(details, "? != BOOLEAN", test_t::TEST_OK);
  } else {
    print_res(details, "? != BOOLEAN", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l1 = bt1 != BOOLEAN();
  l2 = bf1 != BOOLEAN();
  l3 = bt1 != LOGICAL();
  l4 = bf1 != LOGICAL();
  if (l1.is_unknown() && l2.is_unknown() && l3.is_unknown() && l4.is_unknown()) {
    print_res(details, "BOOLEAN != ?", test_t::TEST_OK);
  } else {                          
    print_res(details, "BOOLEAN != ?", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  IF (!(bt1 != lt) && (bt1 != lu) &&  (bt1 != lf) &&
       (bf1 != lt) && (bf1 != lu) && !(bf1 != lf))  {
    print_res(details, "BOOLEAN != LOGICAL", test_t::TEST_OK);
  } else {
    print_res(details, "BOOLEAN != LOGICAL", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l1 = BOOLEAN() != lt;
  l2 = BOOLEAN() != lf;
  l3 = BOOLEAN() != lu;
  if (l1.is_unknown() && l2.is_unknown() && l3.is_unknown()) {
    print_res(details, "? != LOGICAL", test_t::TEST_OK);
  } else {
    print_res(details, "? != LOGICAL", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  /* больше чем */

  IF (!(bt1 > bt2) &&  (bt1 > bf2) &&
      !(bf1 > bt2) && !(bf1 > bf2)) {
    print_res(details, "BOOLEAN > BOOLEAN", test_t::TEST_OK);
  } else {
    print_res(details, "BOOLEAN > BOOLEAN", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l1 = BOOLEAN() > bt1;
  l2 = BOOLEAN() > bf1;
  if (l1.is_unknown() && l2.is_unknown()) {
    print_res(details, "? > BOOLEAN", test_t::TEST_OK);
  } else {
    print_res(details, "? > BOOLEAN", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l1 = bt1 > BOOLEAN();
  l2 = bf1 > BOOLEAN();
  l3 = bt1 > LOGICAL();
  l4 = bf1 > LOGICAL();
  if (l1.is_unknown() && l2.is_unknown() && l3.is_unknown() && l4.is_unknown()) {
    print_res(details, "BOOLEAN > ?", test_t::TEST_OK);
  } else {                          
    print_res(details, "BOOLEAN > ?", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  IF (!(bt1 > lt) &&  (bt1 > lu) &&  (bt1 > lf) &&
      !(bf1 > lt) && !(bf1 > lu) && !(bf1 > lf))  {
    print_res(details, "BOOLEAN > LOGICAL", test_t::TEST_OK);
  } else {
    print_res(details, "BOOLEAN > LOGICAL", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  /* больше или равно */

  IF ( (bt1 >= bt2) && (bt1 >= bf2) &&
      !(bf1 >= bt2) && (bf1 >= bf2)) {
    print_res(details, "BOOLEAN >= BOOLEAN", test_t::TEST_OK);
  } else {
    print_res(details, "BOOLEAN >= BOOLEAN", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l1 = BOOLEAN() >= bt1;
  l2 = BOOLEAN() >= bf1;
  if (l1.is_unknown() && l2.is_unknown()) {
    print_res(details, "? >= BOOLEAN", test_t::TEST_OK);
  } else {
    print_res(details, "? >= BOOLEAN", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l1 = bt1 >= BOOLEAN();
  l2 = bf1 >= BOOLEAN();
  l3 = bt1 >= LOGICAL();
  l4 = bf1 >= LOGICAL();
  if (l1.is_unknown() && l2.is_unknown() && l3.is_unknown() && l4.is_unknown()) {
    print_res(details, "BOOLEAN >= ?", test_t::TEST_OK);
  } else {                          
    print_res(details, "BOOLEAN >= ?", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  IF ( (bt1 >= lt) &&  (bt1 >= lu) && (bt1 >= lf) &&
      !(bf1 >= lt) && !(bf1 >= lu) && (bf1 >= lf))  {
    print_res(details, "BOOLEAN >= LOGICAL", test_t::TEST_OK);
  } else {
    print_res(details, "BOOLEAN >= LOGICAL", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  /* меньше чем */

  IF (!(bt1 < bt2) && !(bt1 < bf2) &&
       (bf1 < bt2) && !(bf1 < bf2)) {
    print_res(details, "BOOLEAN < BOOLEAN", test_t::TEST_OK);
  } else {
    print_res(details, "BOOLEAN < BOOLEAN", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l1 = BOOLEAN() < bt1;
  l2 = BOOLEAN() < bf1;
  if (l1.is_unknown() && l2.is_unknown()) {
    print_res(details, "? < BOOLEAN", test_t::TEST_OK);
  } else {
    print_res(details, "? < BOOLEAN", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l1 = bt1 < BOOLEAN();
  l2 = bf1 < BOOLEAN();
  l3 = bt1 < LOGICAL();
  l4 = bf1 < LOGICAL();
  if (l1.is_unknown() && l2.is_unknown() && l3.is_unknown() && l4.is_unknown()) {
    print_res(details, "BOOLEAN < ?", test_t::TEST_OK);
  } else {                          
    print_res(details, "BOOLEAN < ?", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  IF (!(bt1 < lt) && !(bt1 < lu) && !(bt1 < lf) &&
       (bf1 < lt) &&  (bf1 < lu) && !(bf1 < lf))  {
    print_res(details, "BOOLEAN < LOGICAL", test_t::TEST_OK);
  } else {
    print_res(details, "BOOLEAN < LOGICAL", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  /* меньше или равно */

  IF ((bt1 <= bt2) && !(bt1 <= bf2) &&
      (bf1 <= bt2) &&  (bf1 <= bf2)) {
    print_res(details, "BOOLEAN <= BOOLEAN", test_t::TEST_OK);
  } else {
    print_res(details, "BOOLEAN <= BOOLEAN", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l1 = BOOLEAN() <= bt1;
  l2 = BOOLEAN() <= bf1;
  if (l1.is_unknown() && l2.is_unknown()) {
    print_res(details, "? <= BOOLEAN", test_t::TEST_OK);
  } else {
    print_res(details, "? <= BOOLEAN", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l1 = bt1 <= BOOLEAN();
  l2 = bf1 <= BOOLEAN();
  l3 = bt1 <= LOGICAL();
  l4 = bf1 <= LOGICAL();
  if (l1.is_unknown() && l2.is_unknown() && l3.is_unknown() && l4.is_unknown()) {
    print_res(details, "BOOLEAN <= ?", test_t::TEST_OK);
  } else {                          
    print_res(details, "BOOLEAN <= ?", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  IF ((bt1 <= lt) && !(bt1 <= lu) && !(bt1 <= lf) &&
      (bf1 <= lt) &&  (bf1 <= lu) &&  (bf1 <= lf))  {
    print_res(details, "BOOLEAN <= LOGICAL", test_t::TEST_OK);
  } else {
    print_res(details, "BOOLEAN <= LOGICAL", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_string_rel(bool details) {
  print_title(details, "STRING RELATIONS ");

  test_t err = test_t::TEST_NOT_IMPL;

  /**
   * \file
   * \todo Добавить тестирование отношений строк
   */

  print_res(details, "TEST", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}


static bool test_binary_rel(bool details) {
  print_title(details, "BINARY RELATIONS ");

  test_t err = test_t::TEST_NOT_IMPL;

  /**
   * \file
   * \todo Добавить тестирование отношений BINARY
   */

  print_res(details, "TEST", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 12.4.1 */

static bool test_not(bool details) {
  print_title(details, "NOT");
  test_t err = test_t::TEST_OK;
  LOGICAL l;

  l = NOT TRUE;
  if (l.is_false()) {
    print_res(details, "NOT TRUE", test_t::TEST_OK);
  } else {
    print_res(details, "NOT TRUE", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = NOT UNKNOWN;
  if (l.is_unknown()) {
    print_res(details, "NOT UNKNOWN", test_t::TEST_OK);
  } else {
    print_res(details, "NOT UNKNOWN", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = NOT LOGICAL();
  if (l.is_unknown()) {
    print_res(details, "NOT ?", test_t::TEST_OK);
  } else {
    print_res(details, "NOT ?", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = NOT FALSE;
  if (l.is_true()) {
    print_res(details, "NOT FALSE", test_t::TEST_OK);
  } else {
    print_res(details, "NOT FALSE", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 12.4.2 */

static bool test_and(bool details) {
  print_title(details, "AND");
  test_t err = test_t::TEST_OK;
  LOGICAL l;

  l = TRUE AND TRUE;
  unitest(l.is_true(), details, "TRUE AND TRUE", err);

  l = TRUE AND UNKNOWN;
  unitest(l.is_unknown(), details, "TRUE AND UNKNOWN", err);

  l = TRUE AND LOGICAL();
  unitest(l.is_unknown(), details, "TRUE AND ?", err);

  l = TRUE AND FALSE;
  unitest(l.is_false(), details, "TRUE AND FALSE", err);

  l = UNKNOWN AND TRUE;
  unitest(l.is_unknown(), details, "UNKNOWN AND TRUE", err);

  l = LOGICAL() AND TRUE;
  unitest(l.is_unknown(), details, "? AND TRUE", err);

  l = UNKNOWN AND UNKNOWN;
  unitest(l.is_unknown(), details, "UNKNOWN AND UNKNOWN", err);

  l = LOGICAL() AND UNKNOWN;
  unitest(l.is_unknown(), details, "? AND UNKNOWN", err);

  l = UNKNOWN AND LOGICAL();
  unitest(l.is_unknown(), details, "UNKNOWN AND ?", err);

  l = LOGICAL() AND LOGICAL();
  unitest(l.is_unknown(), details, "? AND ?", err);

  l = UNKNOWN AND FALSE;
  unitest(l.is_false(), details, "UNKNOWN AND FALSE", err);

  l = LOGICAL() AND FALSE;
  unitest(l.is_false(), details, "? AND FALSE", err);

  l = FALSE AND TRUE;
  unitest(l.is_false(), details, "FALSE AND TRUE", err);

  l = FALSE AND UNKNOWN;
  unitest(l.is_false(), details, "FALSE AND UNKNOWN", err);

  l = FALSE AND LOGICAL();
  unitest(l.is_false(), details, "FALSE AND ?", err);

  l = FALSE AND FALSE;
  unitest(l.is_false(), details, "FALSE AND FALSE", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 12.4.3 */

static bool test_or(bool details) {
  print_title(details, "OR");
  test_t err = test_t::TEST_OK;
  LOGICAL l;

  l = TRUE OR TRUE;
  if (l.is_true()) {
    print_res(details, "TRUE OR TRUE", test_t::TEST_OK);
  } else {
    print_res(details, "TRUE OR TRUE", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = TRUE OR UNKNOWN;
  if (l.is_true()) {
    print_res(details, "TRUE OR UNKNOWN", test_t::TEST_OK);
  } else {
    print_res(details, "TRUE OR UNKNOWN", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = TRUE OR LOGICAL();
  if (l.is_true()) {
    print_res(details, "TRUE OR ?", test_t::TEST_OK);
  } else {
    print_res(details, "TRUE OR ?", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = TRUE OR FALSE;
  if (l.is_true()) {
    print_res(details, "TRUE OR FALSE", test_t::TEST_OK);
  } else {
    print_res(details, "TRUE OR FALSE", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = UNKNOWN OR TRUE;
  if (l.is_true()) {
    print_res(details, "UNKNOWN OR TRUE", test_t::TEST_OK);
  } else {
    print_res(details, "UNKNOWN OR TRUE", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = LOGICAL() OR TRUE;
  if (l.is_true()) {
    print_res(details, "? OR TRUE", test_t::TEST_OK);
  } else {
    print_res(details, "? OR TRUE", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = UNKNOWN OR UNKNOWN;
  if (l.is_unknown()) {
    print_res(details, "UNKNOWN OR UNKNOWN", test_t::TEST_OK);
  } else {
    print_res(details, "UNKNOWN OR UNKNOWN", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = LOGICAL() OR UNKNOWN;
  if (l.is_unknown()) {
    print_res(details, "? OR UNKNOWN", test_t::TEST_OK);
  } else {
    print_res(details, "? OR UNKNOWN", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = UNKNOWN OR LOGICAL();
  if (l.is_unknown()) {
    print_res(details, "UNKNOWN OR ?", test_t::TEST_OK);
  } else {
    print_res(details, "UNKNOWN OR ?", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = LOGICAL() OR LOGICAL();
  if (l.is_unknown()) {
    print_res(details, "? OR ?", test_t::TEST_OK);
  } else {
    print_res(details, "? OR ?", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = UNKNOWN OR FALSE;
  if (l.is_unknown()) {
    print_res(details, "UNKNOWN OR FALSE", test_t::TEST_OK);
  } else {
    print_res(details, "UNKNOWN OR FALSE", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = LOGICAL() OR FALSE;
  if (l.is_unknown()) {
    print_res(details, "? OR FALSE", test_t::TEST_OK);
  } else {
    print_res(details, "? OR FALSE", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = FALSE OR TRUE;
  if (l.is_true()) {
    print_res(details, "FALSE OR TRUE", test_t::TEST_OK);
  } else {
    print_res(details, "FALSE OR TRUE", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = FALSE OR UNKNOWN;
  if (l.is_unknown()) {
    print_res(details, "FALSE OR UNKNOWN", test_t::TEST_OK);
  } else {
    print_res(details, "FALSE OR UNKNOWN", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = FALSE OR LOGICAL();
  if (l.is_unknown()) {
    print_res(details, "FALSE OR ?", test_t::TEST_OK);
  } else {
    print_res(details, "FALSE OR ?", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = FALSE OR FALSE;
  if (l.is_false()) {
    print_res(details, "FALSE OR FALSE", test_t::TEST_OK);
  } else {
    print_res(details, "FALSE OR FALSE", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 12.4.4 */

static bool test_xor(bool details) {
  print_title(details, "XOR");
  test_t err = test_t::TEST_OK;
  LOGICAL l;

  l = TRUE XOR TRUE;
  if (l.is_false()) {
    print_res(details, "TRUE XOR TRUE", test_t::TEST_OK);
  } else {
    print_res(details, "TRUE XOR TRUE", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = TRUE XOR UNKNOWN;
  if (l.is_unknown()) {
    print_res(details, "TRUE XOR UNKNOWN", test_t::TEST_OK);
  } else {
    print_res(details, "TRUE XOR UNKNOWN", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = TRUE XOR LOGICAL();
  if (l.is_unknown()) {
    print_res(details, "TRUE XOR ?", test_t::TEST_OK);
  } else {
    print_res(details, "TRUE XOR ?", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = TRUE XOR FALSE;
  if (l.is_true()) {
    print_res(details, "TRUE XOR FALSE", test_t::TEST_OK);
  } else {
    print_res(details, "TRUE XOR FALSE", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = UNKNOWN XOR TRUE;
  if (l.is_unknown()) {
    print_res(details, "UNKNOWN XOR TRUE", test_t::TEST_OK);
  } else {
    print_res(details, "UNKNOWN XOR TRUE", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = LOGICAL() XOR TRUE;
  if (l.is_unknown()) {
    print_res(details, "? XOR TRUE", test_t::TEST_OK);
  } else {
    print_res(details, "? XOR TRUE", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = UNKNOWN XOR UNKNOWN;
  if (l.is_unknown()) {
    print_res(details, "UNKNOWN XOR UNKNOWN", test_t::TEST_OK);
  } else {
    print_res(details, "UNKNOWN XOR UNKNOWN", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = LOGICAL() XOR UNKNOWN;
  if (l.is_unknown()) {
    print_res(details, "? XOR UNKNOWN", test_t::TEST_OK);
  } else {
    print_res(details, "? XOR UNKNOWN", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = UNKNOWN XOR LOGICAL();
  if (l.is_unknown()) {
    print_res(details, "UNKNOWN XOR ?", test_t::TEST_OK);
  } else {
    print_res(details, "UNKNOWN XOR ?", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = LOGICAL() XOR LOGICAL();
  if (l.is_unknown()) {
    print_res(details, "? XOR ?", test_t::TEST_OK);
  } else {
    print_res(details, "? XOR ?", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = UNKNOWN XOR FALSE;
  if (l.is_unknown()) {
    print_res(details, "UNKNOWN XOR FALSE", test_t::TEST_OK);
  } else {
    print_res(details, "UNKNOWN XOR FALSE", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = LOGICAL() XOR FALSE;
  if (l.is_unknown()) {
    print_res(details, "? XOR FALSE", test_t::TEST_OK);
  } else {
    print_res(details, "? XOR FALSE", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = FALSE XOR TRUE;
  if (l.is_true()) {
    print_res(details, "FALSE XOR TRUE", test_t::TEST_OK);
  } else {
    print_res(details, "FALSE XOR TRUE", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = FALSE XOR UNKNOWN;
  if (l.is_unknown()) {
    print_res(details, "FALSE XOR UNKNOWN", test_t::TEST_OK);
  } else {
    print_res(details, "FALSE XOR UNKNOWN", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = FALSE XOR LOGICAL();
  if (l.is_unknown()) {
    print_res(details, "FALSE XOR ?", test_t::TEST_OK);
  } else {
    print_res(details, "FALSE XOR ?", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = FALSE XOR FALSE;
  if (l.is_false()) {
    print_res(details, "FALSE XOR FALSE", test_t::TEST_OK);
  } else {
    print_res(details, "FALSE XOR FALSE", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 15.1 */

static bool test_abs(bool details) {
  print_title(details, "ABS");
  test_t err = test_t::TEST_OK;

  REAL r;
  INTEGER i;

  r = -12345.0;
  r = ABS(r);
  unitest((r == 12345.0).is_true(), details, "REAL Value", err);
 
  i = -12345;
  i = ABS(i);
  IF (i == 12345) {
    print_res(details, "INTEGER Value", test_t::TEST_OK);
  } else {
    print_res(details, "INTEGER Value", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = REAL();
  r = ABS(r);
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate REAL arg", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate REAL arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  i = ABS(INTEGER());
  if (EXISTS(i).is_false()) {
    print_res(details, "Indeterminate INTEGER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate INTEGER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 15.2 */

static bool test_acos(bool details) {
  print_title(details, "ACOS");
  test_t err = test_t::TEST_OK;

  REAL r;
  INTEGER i;
  NUMBER n;

  n = 0.3;
  r = ACOS(n);
  IF (r == 1.26610367277949911126) {
    print_res(details, "NUMBER Value", test_t::TEST_OK);
  } else {
    print_res(details, "NUMBER Value", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = 0.3;
  r = ACOS(r);
  IF (r == 1.26610367277949911126) {
    print_res(details, "REAL Value", test_t::TEST_OK);
  } else {
    print_res(details, "REAL Value", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  i = 1;
  r = ACOS(i);
  IF (r == 0.0) {
    print_res(details, "INTEGER Value check 1", test_t::TEST_OK);
  } else {
    print_res(details, "INTEGER Value check 1", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  i = -1;
  r = ACOS(i);
  IF (r == PI) {
    print_res(details, "INTEGER Value check 2", test_t::TEST_OK);
  } else {
    print_res(details, "INTEGER Value check 2", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = ACOS(NUMBER());
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate NUMBER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate NUMBER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = ACOS(REAL());
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate REAL arg", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate REAL arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = ACOS(INTEGER());
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate INTEGER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate INTEGER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  bool catched = false;
  try {
   n = 2.0;
   r = ACOS(n);
  } catch(exception&) {
    catched = true;
  }
  if (catched) {
    print_res(details, "Out of range NUMBER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Out of range NUMBER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  catched = false;
  try {
    r = 2.0;
    r = ACOS(r);
  } catch(exception&) {
    catched = true;
  }
  if (catched) {
    print_res(details, "Out of range REAL arg", test_t::TEST_OK);
  } else {
    print_res(details, "Out of range REAL arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  catched = false;
  try {
    i = 2;
    r = ACOS(i);
  } catch(exception&) {
    catched = true;
  }
  if (catched) {
    print_res(details, "Out of range INTEGER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Out of range INTEGER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 15.3 */

static bool test_asin(bool details) {
  print_title(details, "ASIN");
  test_t err = test_t::TEST_OK;

  REAL r;
  NUMBER n;

  n = 0.3;
  r = ASIN(n);
  IF (r == 0.30469265401539750797) {
    print_res(details, "NUMBER Value", test_t::TEST_OK);
  } else {
    print_res(details, "NUMBER Value", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = 0.3;
  r = ASIN(r);
  IF (r == 0.30469265401539750797) {
    print_res(details, "REAL Value", test_t::TEST_OK);
  } else {
    print_res(details, "REAL Value", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  INTEGER i;
  i = 1;
  r = ASIN(i);
  IF (r == PI/2.0) {
    print_res(details, "INTEGER Value check 1", test_t::TEST_OK);
  } else {
    print_res(details, "INTEGER Value check 1", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  i = -1;
  r = ASIN(i);
  IF (r == -PI/2.0) {
    print_res(details, "INTEGER Value check 2", test_t::TEST_OK);
  } else {
    print_res(details, "INTEGER Value check 2", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = ASIN(NUMBER());
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate NUMBER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate NUMBER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = ASIN(REAL());
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate REAL arg", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate REAL arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = ASIN(INTEGER());
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate INTEGER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate INTEGER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  bool catched = false;
  try {
   n = 2.0;
   r = ASIN(n);
  } catch(exception&) {
    catched = true;
  }
  if (catched) {
    print_res(details, "Out of range NUMBER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Out of range NUMBER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  catched = false;
  try {
    r = 2.0;
    r = ASIN(r);
  } catch(exception&) {
    catched = true;
  }
  if (catched) {
    print_res(details, "Out of range REAL arg", test_t::TEST_OK);
  } else {
    print_res(details, "Out of range REAL arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  catched = false;
  try {
    i = 2;
    r = ASIN(i);
  } catch(exception&) {
    catched = true;
  }
  if (catched) {
    print_res(details, "Out of range INTEGER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Out of range INTEGER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 15.4 */

static bool test_atan(bool details) {
  print_title(details, "ATAN");
  test_t err = test_t::TEST_OK;

  REAL r = ATAN(NUMBER(-5.5), NUMBER(3.0));
  IF (r == -1.07144960511476653363) {
    print_res(details, "NUMBER Value", test_t::TEST_OK);
  } else {
    print_res(details, "NUMBER Value", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = ATAN(REAL(-5.5), REAL(3.0));
  IF (r == -1.07144960511476653363) {
    print_res(details, "REAL Value", test_t::TEST_OK);
  } else {
    print_res(details, "REAL Value", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = ATAN(INTEGER(-5), INTEGER(3));
  IF (r == -1.03037682652431246379) {
    print_res(details, "INTEGER Value", test_t::TEST_OK);
  } else {
    print_res(details, "INTEGER Value", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = ATAN(NUMBER(), NUMBER(1));
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate arg check 1", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate arg check 1", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = ATAN(NUMBER(1), NUMBER());
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate arg check 2", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate arg check 2", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = ATAN(NUMBER(), NUMBER());
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate arg check 3", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate arg check 3", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  bool catched = false;
  try {
    r = ATAN(REAL(0.0), REAL(0.0));
  } catch(exception&) {
    catched = true;
  }
  if (catched) {
    print_res(details, "V1, V2 zero", test_t::TEST_OK);
  } else {
    print_res(details, "V1, V2 zero", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = ATAN(NUMBER(5.5), INTEGER(0));
  if ((r == PI/2.0).is_true()) {
    print_res(details, "V2 zero check 1", test_t::TEST_OK);
  } else {
    print_res(details, "V2 zero check 1", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = ATAN(NUMBER(-5.5), INTEGER(0));
  if ((r == -PI/2.0).is_true()) {
    print_res(details, "V2 zero check 2", test_t::TEST_OK);
  } else {
    print_res(details, "V2 zero check 2", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }


  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 15.5 */

static bool test_blength(bool details) {
  print_title(details, "BLENGTH");
  test_t err = test_t::TEST_NOT_IMPL;

  /**
   * \file
   * \todo Добавить тестирование функции BLENGTH
   */

  print_res(details, "TEST", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 15.6 */

static bool test_cos(bool details) {
  print_title(details, "COS");
  test_t err = test_t::TEST_OK;

  REAL r;
  NUMBER n;
  INTEGER i;

  n = 0.5;
  r = COS(n);
  IF (r == 0.87758256189037271612) {
    print_res(details, "NUMBER Value", test_t::TEST_OK);
  } else {
    print_res(details, "NUMBER Value", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = 0.5;
  r = COS(r);
  IF (r == 0.87758256189037271612) {
    print_res(details, "REAL Value", test_t::TEST_OK);
  } else {
    print_res(details, "REAL Value", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  i = 1;
  r = COS(i);
  IF (r == 0.5403023058681397174) {
    print_res(details, "INTEGER Value check 1", test_t::TEST_OK);
  } else {
    print_res(details, "INTEGER Value check 1", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  i = -1;
  r = COS(i);
  IF (r == 0.5403023058681397174) {
    print_res(details, "INTEGER Value check 2", test_t::TEST_OK);
  } else {
    print_res(details, "INTEGER Value check 2", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = COS(NUMBER());
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate NUMBER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate NUMBER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = COS(REAL());
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate REAL arg", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate REAL arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = COS(INTEGER());
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate INTEGER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate INTEGER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 15.7 */

static bool test_exists(bool details) {
  print_title(details, "EXISTS");
  test_t err = test_t::TEST_OK;

  REAL r1, r2;
  r2 = 1.0;
  INTEGER i1, i2;
  i2 = 1;
  BOOLEAN b1, b2;
  b2 = TRUE;
  STRING s1, s2("abcd");

  if (EXISTS(r2).is_true() && EXISTS(r1).is_false()) {
    print_res(details, "REAL arg", test_t::TEST_OK);
  } else {
    print_res(details, "REAL arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  if (EXISTS(i2).is_true() && EXISTS(i1).is_false()) {
    print_res(details, "INTEGER arg", test_t::TEST_OK);
  } else {
    print_res(details, "INTEGER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  if (EXISTS(b2).is_true() && EXISTS(b1).is_false()) {
    print_res(details, "BOOLEAN arg", test_t::TEST_OK);
  } else {
    print_res(details, "BOOLEAN arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  if (EXISTS(s2).is_true() && EXISTS(s1).is_false()) {
    print_res(details, "STRING arg", test_t::TEST_OK);
  } else {
    print_res(details, "STRING arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 15.8 */

static bool test_exp(bool details) {
  print_title(details, "EXP");
  test_t err = test_t::TEST_OK;

  NUMBER n;
  REAL r;
  INTEGER i;

  n = 0.5;
  r = EXP(n);
  IF (r == 1.64872127070012814685) {
    print_res(details, "NUMBER Value", test_t::TEST_OK);
  } else {
    print_res(details, "NUMBER Value", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = 0.5;
  r = EXP(r);
  IF (r == 1.64872127070012814685) {
    print_res(details, "REAL Value", test_t::TEST_OK);
  } else {
    print_res(details, "REAL Value", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  i = 1;
  r = EXP(i);
  IF (r == CONST_E) {
    print_res(details, "INTEGER Value check 1", test_t::TEST_OK);
  } else {
    print_res(details, "INTEGER Value check 1", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  i = 0;
  r = EXP(i);
  IF (r == 1.0) {
    print_res(details, "INTEGER Value check 2", test_t::TEST_OK);
  } else {
    print_res(details, "INTEGER Value check 2", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = EXP(NUMBER());
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate NUMBER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate NUMBER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = EXP(REAL());
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate REAL arg", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate REAL arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = EXP(INTEGER());
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate INTEGER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate INTEGER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 15.9 */

static bool test_format(bool details) {
  print_title(details, "FORMAT");
  test_t err = test_t::TEST_OK;

  STRING s;
  INTEGER i;
  REAL r;

  s = FORMAT(NUMBER(), "7I");
  unitest(EXISTS(s).is_false(), details, "Indeterminate check FORMAT(?, '7I')", err);

  s = FORMAT(NUMBER(), STRING());
  unitest(EXISTS(s).is_false(), details, "Indeterminate check FORMAT(?, ?)", err);

  s = FORMAT(i, STRING());
  unitest(EXISTS(s).is_false(), details, "Indeterminate check FORMAT(10, ?)", err);

  i = 10;
  s = FORMAT(i, "+7I");
  unitest(s.get_value() == "    +10", details, "ISO 10303-11-2004, p15.9, Table 20(1)", err);

  i = 10;
  s = FORMAT(i, "+07I");
  unitest(s.get_value() == "+000010", details, "ISO 10303-11-2004, p15.9, Table 20(2)", err);

  i = 10;
  s = FORMAT(i, "10.3E");
  unitest(s.get_value() == " 1.000E+01", details, "ISO 10303-11-2004, p15.9, Table 20(3)", err);

  r = 123.456789;
  s = FORMAT(r, "8.2F");
  unitest(s.get_value() == "  123.46", details, "ISO 10303-11-2004, p15.9, Table 20(4)", err);

  r = 123.456789;
  s = FORMAT(r, "8.2E");
  unitest(s.get_value() == "1.23E+02", details, "ISO 10303-11-2004, p15.9, Table 20(5)", err);

  r = 123.456789;
  s = FORMAT(r, "08.2E");
  unitest(s.get_value() == "0.12E+03", details, "ISO 10303-11-2004, p15.9, Table 20(6)", err);

  r = 9.876E123;
  s = FORMAT(r, "8.2E");
  unitest(s.get_value() == "9.88E+123", details, "ISO 10303-11-2004, p15.9, Table 20(7)", err);

  r = 32.777;
  s = FORMAT(r, "6I");
  unitest(s.get_value() == "    33", details, "ISO 10303-11-2004, p15.9, Table 20(8)", err);

  r = 9812345678901255.5;
  s = FORMAT(r, "020I");
  unitest(s.get_value() == "00009812345678901300", details, "'I' with REAL check 1", err);

  r = 981234567890125.5;
  s = FORMAT(r, "020I");
  unitest(s.get_value() == "00000981234567890130", details, "'I' with REAL check 2", err);

  r = 98123456789012.5;
  s = FORMAT(r, "020I");
  unitest(s.get_value() == "00000098123456789013", details, "'I' with REAL check 3", err);

  r = 9812345678901.5;
  s = FORMAT(r, "020I");
  unitest(s.get_value() == "00000009812345678902", details, "'I' with REAL check 4", err);

  r = 981234567890.55;
  s = FORMAT(r, "020I");
  unitest(s.get_value() == "00000000981234567891", details, "'I' with REAL check 5", err);

  r = 981234.56789012;
  s = FORMAT(r, "20I");
  unitest(s.get_value() == "              981235", details, "'I' with REAL check 6a", err);

  r = 981234.56789012;
  s = FORMAT(r, "+20I");
  unitest(s.get_value() == "             +981235", details, "'I' with REAL check 6b", err);

  r = 981234.56789012;
  s = FORMAT(r, "-20I");
  unitest(s.get_value() == "              981235", details, "'I' with REAL check 6c", err);

  r = -981234.56789012;
  s = FORMAT(r, "20I");
  unitest(s.get_value() == "             -981234", details, "'I' with REAL check 6d", err);

  r = -981234.56789012;
  s = FORMAT(r, "+20I");
  unitest(s.get_value() == "             -981234", details, "'I' with REAL check 6e", err);

  r = -981234.56789012;
  s = FORMAT(r, "-20I");
  unitest(s.get_value() == "             -981234", details, "'I' with REAL check 6f", err);

  r = 981234.56789012;
  s = FORMAT(r, "020I");
  unitest(s.get_value() == "00000000000000981235", details, "'I' with REAL check 6g", err);

  r = 981234.56789012;
  s = FORMAT(r, "+020I");
  unitest(s.get_value() == "+0000000000000981235", details, "'I' with REAL check 6h", err);

  r = 981234.56789012;
  s = FORMAT(r, "-020I");
  unitest(s.get_value() == "00000000000000981235", details, "'I' with REAL check 6i", err);

  r = -981234.56789012;
  s = FORMAT(r, "020I");
  unitest(s.get_value() == "-0000000000000981234", details, "'I' with REAL check 6j", err);

  r = -981234.56789012;
  s = FORMAT(r, "+020I");
  unitest(s.get_value() == "-0000000000000981234", details, "'I' with REAL check 6k", err);

  r = -981234.56789012;
  s = FORMAT(r, "-020I");
  unitest(s.get_value() == "-0000000000000981234", details, "'I' with REAL check 6l", err);

  r = 0.546789012345678;
  s = FORMAT(r, "020I");
  unitest(s.get_value() == "00000000000000000001", details, "'I' with REAL check 7", err);

  r = 0.123456789012340;
  s = FORMAT(r, "020I");
  unitest(s.get_value() == "00000000000000000000", details, "'I' with REAL check 8", err);

  r = 0.09812345678901;
  s = FORMAT(r, "020I");
  unitest(s.get_value() == "00000000000000000000", details, "'I' with REAL check 9a", err);

  r = 0.009812345678901;
  s = FORMAT(r, "020I");
  unitest(s.get_value() == "00000000000000000000", details, "'I' with REAL check 9b", err);

  r = 9.876E123;
  s = FORMAT(r, "8.2F");
  unitest(s.get_value() == "9876000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000.00", details, "'F' with REAL check 1", err);

  r = 5.6789012345;
  s = FORMAT(r, "8.4F");
  unitest(s.get_value() == "  5.6789", details, "'F' with REAL check 2", err);

  r = 0.56789012345;
  s = FORMAT(r, "8.4F");
  unitest(s.get_value() == "  0.5679", details, "'F' with REAL check 3", err);

  r = 0.56789012345;
  s = FORMAT(r, "+8.4F");
  unitest(s.get_value() == " +0.5679", details, "'F' with REAL check 4", err);

  r = 0.56789012345;
  s = FORMAT(r, "-8.4F");
  unitest(s.get_value() == "  0.5679", details, "'F' with REAL check 5", err);

  r = -0.56789012345;
  s = FORMAT(r, "8.4F");
  unitest(s.get_value() == " -0.5679", details, "'F' with REAL check 6", err);

  r = -0.56789012345;
  s = FORMAT(r, "+8.4F");
  unitest(s.get_value() == " -0.5679", details, "'F' with REAL check 7", err);

  r = -0.56789012345;
  s = FORMAT(r, "-8.4F");
  unitest(s.get_value() == " -0.5679", details, "'F' with REAL check 8", err);

  r = 0.056789012345;
  s = FORMAT(r, "8.4F");
  unitest(s.get_value() == "  0.0568", details, "'F' with REAL check 9", err);

  r = 0.0056789012345;
  s = FORMAT(r, "8.4F");
  unitest(s.get_value() == "  0.0057", details, "'F' with REAL check 10", err);

  r = 0.00056789012345;
  s = FORMAT(r, "8.4F");
  unitest(s.get_value() == "  0.0006", details, "'F' with REAL check 11", err);

  r = -0.00056789012345;
  s = FORMAT(r, "8.4F");
  unitest(s.get_value() == " -0.0006", details, "'F' with REAL check 12", err);

  r = 0.000056789012345;
  s = FORMAT(r, "8.4F");
  unitest(s.get_value() == "  0.0001", details, "'F' with REAL check 13a", err);

  r = 0.000045678901234;
  s = FORMAT(r, "8.4F");
  unitest(s.get_value() == "  0.0000", details, "'F' with REAL check 13b", err);

  r = 0.0000056789012345;
  s = FORMAT(r, "8.4F");
  unitest(s.get_value() == "  0.0000", details, "'F' with REAL check 14a", err);

  r = 0.00000056789012345;
  s = FORMAT(r, "8.4F");
  unitest(s.get_value() == "  0.0000", details, "'F' with REAL check 14b", err);

  r = 0.000000056789012345;
  s = FORMAT(r, "8.4F");
  unitest(s.get_value() == "  0.0000", details, "'F' with REAL check 14c", err);

  i = 98123456789012555;
  s = FORMAT(i, "8.4F");
  unitest(s.get_value() == "98123456789012555.0000", details, "'F' with INTEGER", err);

  r = -9.876E123;
  s = FORMAT(r, "8.2E");
  unitest(s.get_value() == "-9.88E+123", details, "'E' with REAL check 1", err);

  r = 9.876E123;
  s = FORMAT(r, "+8.2E");
  unitest(s.get_value() == "+9.88E+123", details, "'E' with REAL check 2", err);

  r = -9.876E123;
  s = FORMAT(r, "27.20E");
  unitest(s.get_value() == "-9.87600000000000000000E+123", details, "'E' with REAL check 3", err);

  i = 1234567;
  s = FORMAT(i, "20.20E");
  unitest(s.get_value() == "1.23456700000000000000E+06", details, "'E' with INTEGER check 1", err);

  i = 1234567;
  s = FORMAT(i, "10.3E");
  unitest(s.get_value() == " 1.235E+06", details, "'E' with INTEGER check 2a", err);

  i = 1234567;
  s = FORMAT(i, "010.3E");
  unitest(s.get_value() == " 0.123E+07", details, "'E' with INTEGER check 2b", err);

  i = 2345678;
  s = FORMAT(i, "010.3E");
  unitest(s.get_value() == " 0.235E+07", details, "'E' with INTEGER check 2c", err);

  i = 10;
  s = FORMAT(i, "###");
  unitest(s.get_value() == " 10", details, "ISO 10303-11-2004, p15.9, Table 22(1)", err);

  i = 10;
  s = FORMAT(i, "(###)");
  unitest(s.get_value() == "  10 ", details, "ISO 10303-11-2004, p15.9, Table 22(2)", err);

  i = -10;
  s = FORMAT(i, "(###)");
  unitest(s.get_value() == "( 10)", details, "ISO 10303-11-2004, p15.9, Table 22(3)", err);

  r = 7123.456;
  s = FORMAT(r, "###,###.##");
  unitest(s.get_value() == "  7,123.46", details, "ISO 10303-11-2004, p15.9, Table 22(4)", err);

  r = 7123.456;
  s = FORMAT(r, "###.###,##");
  unitest(s.get_value() == "  7.123,46", details, "ISO 10303-11-2004, p15.9, Table 22(5)", err);

  r = 1234.1234567;
  s = FORMAT(r, "####");
  unitest(s.get_value() == "1234", details, "'Template' with REAL check 1", err);

  r = 1000;
  s = FORMAT(r, "###");
  unitest(s.get_value() == "###", details, "'Template' with REAL check 2", err);

  r = -1234.1234567;
  s = FORMAT(r, "-####");
  unitest(s.get_value() == "-1234", details, "'Template' with REAL check 3", err);

  r = 123123123123123123.456;
  s = FORMAT(r, "###.###.###.###.###.###,###");
  unitest(s.get_value() == "123.123.123.123.120.000,000", details, "'Template' with REAL check 4", err);

  r = -0.00012341234567;
  s = FORMAT(r, "-####");
//!!!
  unitest(s.get_value() == "-   0", details, "'Template' with REAL check 5", err);

  i = -123123123123123123;
  s = FORMAT(i, "###.###.###.###.###.###,###");
  unitest(s.get_value() == "123.123.123.123.123.123,000", details, "'Template' with INTEGER check 1", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 15.10 */

static bool test_hibound(bool details) {
  print_title(details, "HIBOUND");
  test_t err = test_t::TEST_OK;

  ARRAY<INTEGER> Array(15, 18, AGGREGATE_GENERIC::OPTIONAL);
  unitest((HIBOUND(Array) == 18).is_true(), details, "ARRAY[15, 18]", err);
#if 0
  LIST<INTEGER> List1(15, 18);
  unitest((HIBOUND(List1) == 18).is_true(), details, "LIST[15, 18]", err);

  LIST<INTEGER> List2(15);
  unitest(EXISTS(HIBOUND(List2)).is_false(), details, "LIST[15]", err);

  LIST<INTEGER> List3;
  unitest(EXISTS(HIBOUND(List3)).is_false(), details, "LIST", err);

  SET<INTEGER> Set1(15, 18);
  unitest((HIBOUND(Set1) == 18).is_true(), details, "SET[15, 18]", err);

  SET<INTEGER> Set2(15);
  unitest(EXISTS(HIBOUND(Set2)).is_false(), details, "SET[15]", err);

  SET<INTEGER> Set3;
  unitest(EXISTS(HIBOUND(Set3)).is_false(), details, "SET", err);

  BAG<INTEGER> Bag1(15, 18);
  unitest((HIBOUND(Bag1) == 18).is_true(), details, "BAG[15, 18]", err);

  BAG<INTEGER> Bag2(15);
  unitest(EXISTS(HIBOUND(Bag2)).is_false(), details, "BAG[15]", err);

  BAG<INTEGER> Bag3;
  unitest(EXISTS(HIBOUND(Bag3)).is_false(), details, "BAG", err);
#endif
  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 15.11 */

static bool test_hiindex(bool details) {
  print_title(details, "HIINDEX");
  test_t err = test_t::TEST_OK;

  ARRAY<INTEGER> Array(15, 18, AGGREGATE_GENERIC::OPTIONAL);
  unitest((HIINDEX(Array) == 18).is_true(), details, "ARRAY[15, 18]", err);

  /**
   * \file
   * \todo Уточнить тестирование HIINDEX для аггрегатов кроме массива.
   */
#if 0
  LIST<INTEGER> List(15, 18);
  unitest((HIINDEX(List) == 0).is_true(), details, "LIST[15, 18]", err);

  BAG<INTEGER> Bag(15, 18);
  unitest((HIINDEX(Bag) == 0).is_true(), details, "BAG[15, 18]", err);

  SET<INTEGER> Set(15, 18);
  unitest((HIINDEX(Set) == 0).is_true(), details, "SET[15, 18]", err);
#endif

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 15.12 */

static bool test_length(bool details) {
  print_title(details, "LENGTH");
  test_t err = test_t::TEST_OK;


  unitest(LENGTH(STRING("")).get_integer_value() == 0, details, "LENGTH('') -> 0", err);

  unitest(LENGTH(STRING("abcD")).get_integer_value() == 4, details, "LENGTH('abcD') -> 4", err);


  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 15.13 */

static bool test_lobound(bool details) {
  print_title(details, "LOBOUND");
  test_t err = test_t::TEST_OK;

  ARRAY<INTEGER> Array(15, 18, AGGREGATE_GENERIC::OPTIONAL);
  unitest((LOBOUND(Array) == 15).is_true(), details, "Array", err);


  /**
   * \file
   * \todo Добавить тестирование функции LOBOUND для аггрегатов кроме массива.
   */

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 15.14 */

static bool test_log(bool details) {
  print_title(details, "LOG");
  test_t err = test_t::TEST_OK;

  NUMBER n;
  REAL r;
  INTEGER i;

  n = 0.3;
  r = LOG(n);
  unitest((r == -1.20397280432593599262).is_true(), details, "NUMBER Value", err);

  r = LOG(CONST_E);
  unitest((r == 1.0).is_true(), details, "REAL Value", err);

  i = 1;
  r = LOG(i);
  unitest((r == 0.0).is_true(), details, "INTEGER Value check 1", err);

  i = 10;
  r = LOG(i);
  unitest((r == 2.30258509299404568402).is_true(), details, "INTEGER Value check 2", err);

  r = LOG(NUMBER());
  unitest(EXISTS(r).is_false(), details, "Indeterminate NUMBER arg", err);

  r = LOG(REAL());
  unitest(EXISTS(r).is_false(), details, "Indeterminate REAL arg", err);

  r = LOG(INTEGER());
  unitest(EXISTS(r).is_false(), details, "Indeterminate INTEGER arg", err);

  bool catched = false;
  try {
   n = -1.0;
   r = LOG(n);
  } catch(exception&) {
    catched = true;
  }
  unitest(catched, details, "Out of range NUMBER arg", err);

  catched = false;
  try {
    r = -2.0;
    r = LOG(r);
  } catch(exception&) {
    catched = true;
  }
  unitest(catched, details, "Out of range REAL arg", err);

  catched = false;
  try {
   i = 0;
   r = LOG(i);
  } catch(exception&) {
    catched = true;
  }
  unitest(catched, details, "Out of range INTEGER arg", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 15.15 */

static bool test_log2(bool details) {
  print_title(details, "LOG2");
  test_t err = test_t::TEST_OK;

  NUMBER n;
  REAL r;
  INTEGER i;

  n = 0.3;
  r = LOG2(n);
  unitest((r == -1.73696559416620616642).is_true(), details, "NUMBER Value", err);

  r = 2.0;
  r = LOG2(r);
  unitest((r == 1.0).is_true(), details, "REAL Value", err);

  i = 1;
  r = LOG2(i);
  unitest((r == 0.0).is_true(), details, "INTEGER Value check 1", err);

  i = 10;
  r = LOG2(i);
  unitest((r == 3.32192809488736234787).is_true(), details, "INTEGER Value check 2", err);

  r = LOG2(NUMBER());
  unitest(EXISTS(r).is_false(), details, "Indeterminate NUMBER arg", err);

  r = LOG2(REAL());
  unitest(EXISTS(r).is_false(), details, "Indeterminate REAL arg", err);

  r = LOG2(INTEGER());
  unitest(EXISTS(r).is_false(), details, "Indeterminate INTEGER arg", err);

  bool catched = false;
  try {
    n = -1.0;
    r = LOG2(n);
  } catch(exception&) {
    catched = true;
  }
  if (catched) {
    print_res(details, "Out of range NUMBER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Out of range NUMBER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  catched = false;
  try {
    r = -2.0;
    r = LOG2(r);
  } catch(exception&) {
    catched = true;
  }
  if (catched) {
    print_res(details, "Out of range REAL arg", test_t::TEST_OK);
  } else {
    print_res(details, "Out of range REAL arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  catched = false;
  try {
    i = 0;
    r = LOG2(i);
  } catch(exception&) {
    catched = true;
  }
  if (catched) {
    print_res(details, "Out of range INTEGER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Out of range INTEGER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 15.16 */

static bool test_log10(bool details) {
  print_title(details, "LOG10");
  test_t err = test_t::TEST_OK;

  NUMBER n;
  REAL r;
  INTEGER i;

  r = 0.3;
  r = LOG10(r);
  if ((r == -0.5228787452803375627).is_true()) {
    print_res(details, "NUMBER Value", test_t::TEST_OK);
  } else {
    print_res(details, "NUMBER Value", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = 10.0;
  r = LOG10(r);
  IF (r == 1.0) {
    print_res(details, "REAL Value", test_t::TEST_OK);
  } else {
    print_res(details, "REAL Value", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  i = 1;
  r = LOG10(i);
  IF (r == 0.0) {
    print_res(details, "INTEGER Value check 1", test_t::TEST_OK);
  } else {
    print_res(details, "INTEGER Value check 1", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  i = 100;
  r = LOG10(i);
  IF (r == 2.0) {
    print_res(details, "INTEGER Value check 2", test_t::TEST_OK);
  } else {
    print_res(details, "INTEGER Value check 2", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = LOG10(NUMBER());
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate NUMBER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate NUMBER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }
  
  r = LOG10(REAL());
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate REAL arg", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate REAL arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = LOG10(INTEGER());
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate INTEGER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate INTEGER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  bool catched = false;
  try {
    n = -1.0;
    r = LOG10(n);
  } catch(exception&) {
    catched = true;
  }
  if (catched) {
    print_res(details, "Out of range NUMBER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Out of range NUMBER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  catched = false;
  try {
    r = -2.0;
    r = LOG10(r);
  } catch(exception&) {
    catched = true;
  }
  if (catched) {
    print_res(details, "Out of range REAL arg", test_t::TEST_OK);
  } else {
    print_res(details, "Out of range REAL arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  catched = false;
  try {
   i = 0;
   r = LOG10(i);
  } catch(exception&) {
    catched = true;
  }
  if (catched) {
    print_res(details, "Out of range INTEGER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Out of range INTEGER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 15.17 */

static bool test_loindex(bool details) {
  print_title(details, "LOINDEX");
  test_t err = test_t::TEST_OK;

  ARRAY<INTEGER> Array(15, 18, AGGREGATE_GENERIC::OPTIONAL);
  unitest((LOINDEX(Array) == 15).is_true(), details, "ARRAY[15, 18]", err);

  /**
   * \file
   * \todo Добавить тестирование функции LOINDEX для аггрегатов кроме массивов.
   */


  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}


/* 15.18 */

static bool test_nvl(bool details) {
  print_title(details, "NVL");
  test_t err = test_t::TEST_OK;
  INTEGER i1, i2, i3;
  REAL r1, r2, r3;

  i2 = 2;
  i3 = NVL<INTEGER>(i1, i2);
  if (EXISTS(i3).is_true() && (i3 == i2).is_true()) {
    print_res(details, "INTEGER Values check 1", test_t::TEST_OK);
  } else {
    print_res(details, "INTEGER values check 1", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }
  i1 = 3;
  i3 = NVL<INTEGER>(i1, i2);
  if (EXISTS(i3).is_true() && (i3 == i1).is_true()) {
    print_res(details, "INTEGER Values check 2", test_t::TEST_OK);
  } else {
    print_res(details, "INTEGER values check 2", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r2 = 2;
  r3 = NVL<REAL>(r1, r2);
  if (EXISTS(r3).is_true() && (r3 == r2).is_true()) {
    print_res(details, "REAL Values check 1", test_t::TEST_OK);
  } else {
    print_res(details, "REAL values check 1", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }
  r1 = 3;
  r3 = NVL<REAL>(r1, r2);
  if (EXISTS(r3).is_true() && (r3 == r1).is_true()) {
    print_res(details, "REAL Values check 2", test_t::TEST_OK);
  } else {
    print_res(details, "REAL values check 2", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 15.19 */

static bool test_odd(bool details) {
  print_title(details, "ODD");
  test_t err = test_t::TEST_OK;

  LOGICAL l;
  INTEGER i;

  i = 121;
  l = ODD(i);
  if (l.is_true()) {
    print_res(details, "INTEGER Value check 1", test_t::TEST_OK);
  } else {
    print_res(details, "INTEGER Value check 1", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  i = 120;
  l = ODD(i);
  if (l.is_false()) {
    print_res(details, "INTEGER Value check 2", test_t::TEST_OK);
  } else {
    print_res(details, "INTEGER Value check 2", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  i = 0;
  l = ODD(i);
  if (l.is_false()) {
    print_res(details, "INTEGER Value check 3", test_t::TEST_OK);
  } else {
    print_res(details, "INTEGER Value check 3", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  l = ODD(INTEGER());
  if (EXISTS(l).is_false()) {
    print_res(details, "Indeterminate INTEGER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate INTEGER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 15.20 */

static bool test_rolesof(bool details) {
  print_title(details, "ROLESOF");
  test_t err = test_t::TEST_NOT_IMPL;

  /**
   * \file
   * \todo Добавить тестирование функции ROLESOF
   */

  print_res(details, "TEST", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 15.21 */

static bool test_sin(bool details) {
  print_title(details, "SIN");
  test_t err = test_t::TEST_OK;

  NUMBER n;
  REAL r;
  INTEGER i;

  n = 0.5;
  r = SIN(n);
  IF (r == 0.47942553860420300027) {
    print_res(details, "NUMBER Value", test_t::TEST_OK);
  } else {
    print_res(details, "NUMBER Value", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = 0.5;
  r = SIN(r);
  IF (r == 0.47942553860420300027) {
    print_res(details, "REAL Value", test_t::TEST_OK);
  } else {
    print_res(details, "REAL Value", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  i = 1;
  r = SIN(i);
  IF (r == 0.84147098480789650665) {
    print_res(details, "INTEGER Value check 1", test_t::TEST_OK);
  } else {
    print_res(details, "INTEGER Value check 1", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  i = -1;
  r = SIN(i);
  IF (r == -0.84147098480789650665) {
    print_res(details, "INTEGER Value check 2", test_t::TEST_OK);
  } else {
    print_res(details, "INTEGER Value check 2", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = SIN(NUMBER());
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate NUMBER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate NUMBER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = SIN(REAL());
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate REAL arg", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate REAL arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = SIN(INTEGER());
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate INTEGER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate INTEGER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 15.22 */

static bool test_sizeof(bool details) {
  print_title(details, "SIZEOF");
  test_t err = test_t::TEST_OK;

  INTEGER i1, i2, i3, i4, i5;
  i1 = 1;
  i2 = 2;
  i3 = 3;
  i4 = 4;
  i5 = 5;

  ARRAY<INTEGER> Array(-3, 1, AGGREGATE_GENERIC::OPTIONAL);
  Array = {i1, i2, i3, i4, i5};

  unitest((SIZEOF(Array) == 5).is_true(), details, "ARRAY[-3, 2]", err);
#if 0
  LIST<INTEGER> List(0, 5);
  List = {i1, i2, i3};

  unitest((SIZEOF(List) == 3).is_true(), details, "LIST[0, 5]", err);

  BAG<INTEGER> Bag(0, 5);
  Bag = {i1, i2, i3, i4};

  unitest((SIZEOF(Bag) == 4).is_true(), details, "BAG[0, 5]", err);

  SET<INTEGER> Set(0, 5);
  Set = {i1, i2, i3, i4, i5};

  unitest((SIZEOF(Set) == 5).is_true(), details, "SET[0, 5]", err);
#endif
  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 15.23 */

static bool test_sqrt(bool details) {
  print_title(details, "SQRT");
  test_t err = test_t::TEST_OK;

  NUMBER n;
  REAL r;
  INTEGER i;

  n = 12345.0;
  r = SQRT(n);
  IF (r == 111.108055513540511245) {
    print_res(details, "NUMBER Value", test_t::TEST_OK);
  } else {
    print_res(details, "NUMBER Value", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = 6789.0;
  r = SQRT(r);
  IF (r == 82.39538822045806709107) {
    print_res(details, "REAL Value", test_t::TEST_OK);
  } else {
    print_res(details, "REAL Value", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  i = 25;
  r = SQRT(i);
  IF (r == 5.0) {
    print_res(details, "INTEGER Value check 1", test_t::TEST_OK);
  } else {
    print_res(details, "INTEGER Value check 1", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  i = 36;
  r = SQRT(i);
  IF (r == 6.0) {
    print_res(details, "INTEGER Value check 2", test_t::TEST_OK);
  } else {
    print_res(details, "INTEGER Value check 2", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = SQRT(NUMBER());
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate NUMBER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate NUMBER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = SQRT(REAL());
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate REAL arg", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate REAL arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = SQRT(INTEGER());
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate INTEGER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate INTEGER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }


  bool catched = false;
  try {
    r = -1.0;
    r = SQRT(r);
  } catch(exception&) {
    catched = true;
  }
  if (catched) {
    print_res(details, "Out of range NUMBER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Out of range NUMBER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  catched = false;
  try {
    r = -1.0;
    r = SQRT(r);
  } catch(exception&) {
    catched = true;
  }
  if (catched) {
    print_res(details, "Out of range REAL arg", test_t::TEST_OK);
  } else {
    print_res(details, "Out of range REAL arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  catched = false;
  try {
   i = -1;
   r = SQRT(i);
  } catch(exception&) {
    catched = true;
  }
  if (catched) {
    print_res(details, "Out of range INTEGER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Out of range INTEGER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 15.24 */

static bool test_tan(bool details) {
  print_title(details, "TAN");
  test_t err = test_t::TEST_OK;

  NUMBER n;
  REAL r;
  INTEGER i;

  n = 0.5;
  r = TAN(n);
  IF (r == 0.54630248984379051326) {
    print_res(details, "NUMBER Value", test_t::TEST_OK);
  } else {
    print_res(details, "NUMBER Value", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = 0.5;
  r = TAN(r);
  IF (r == 0.54630248984379051326) {
    print_res(details, "REAL Value", test_t::TEST_OK);
  } else {
    print_res(details, "REAL Value", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  i = 1;
  r = TAN(i);
  IF (r == 1.55740772465490223051) {
    print_res(details, "INTEGER Value check 1", test_t::TEST_OK);
  } else {
    print_res(details, "INTEGER Value check 1", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  i = -1;
  r = TAN(i);
  IF (r == -1.55740772465490223051) {
    print_res(details, "INTEGER Value check 2", test_t::TEST_OK);
  } else {
    print_res(details, "INTEGER Value check 2", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = TAN(NUMBER());
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate NUMBER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate NUMBER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = TAN(REAL());
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate REAL arg", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate REAL arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  r = TAN(INTEGER());
  if (EXISTS(r).is_false()) {
    print_res(details, "Indeterminate INTEGER arg", test_t::TEST_OK);
  } else {
    print_res(details, "Indeterminate INTEGER arg", test_t::TEST_ERR);
    err = test_t::TEST_ERR;
  }

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 15.25 */

static bool test_typeof(bool details) {
  print_title(details, "TYPEOF");
  test_t err = test_t::TEST_NOT_IMPL;

  /**
   * \file
   * \todo Добавить тестирование функции TYPEOF
   */

  print_res(details, "TEST", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 15.26 */

static bool test_usedin(bool details) {
  print_title(details, "USEDIN");
  test_t err = test_t::TEST_NOT_IMPL;

  /**
   * \file
   * \todo Добавить тестирование функции USEDIN
   */

  print_res(details, "TEST", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 15.27 */

static bool test_value(bool details) {
  print_title(details, "VALUE");
  test_t err = test_t::TEST_NOT_IMPL;

  /**
   * \file
   * \todo Добавить тестирование функции VALUE
   */
  print_res(details, "TEST", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 15.28 */

static bool test_value_in(bool details) {
  print_title(details, "VALUE_IN");
  test_t err = test_t::TEST_NOT_IMPL;

  /**
   * \file
   * \todo Добавить тестирование функции VALUE_IN
   */

  print_res(details, "TEST", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 16.1 */
#if 0
static bool test_insert(bool details) {
  print_title(details, "INSERT");
  test_t err = test_t::TEST_NOT_IMPL;

  /**
   * \file
   * \todo Добавить тестирование функции INSERT
   */
  print_res(details, "TEST", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

/* 16.2 */

static bool test_remove(bool details) {
  print_title(details, "REMOVE");
  test_t err = test_t::TEST_NOT_IMPL;

  /**
   * \file
   * \todo Добавить тестирование функции REMOVE
   */
  print_res(details, "TEST", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}
#endif
static bool test_number_arith_add(bool details) {
  print_title(details, "NUMBER ARITHMETIC - '+'");
  test_t err = test_t::TEST_OK;
  REAL r;

  /* Унарный плюс */

  r = +NUMBER(3.0);
  unitest((r == 3).is_true(), details, "+NUMBER", err);

  r = +NUMBER();
  unitest(!r.is_determinated(), details, "+? (NUMBER)", err);

  /* Сложение с NUMBER */

  r = NUMBER(3.0) + NUMBER(5.0);
  unitest((r == 8).is_true(), details, "NUMBER + NUMBER", err);

  r = NUMBER() + NUMBER(5.0);
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) + NUMBER", err);

  r = NUMBER(3.0) + NUMBER();
  unitest(EXISTS(r).is_false(), details, "NUMBER + ? (NUMBER)", err);

  /* Сложение с real_type */

  r = NUMBER(3.0) + static_cast<real_type>(5.0);
  unitest((r == 8).is_true(), details, "NUMBER + real_type", err);

  r = NUMBER() + static_cast<real_type>(5.0);
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) + real_type", err);

  r = static_cast<real_type>(5.0) + NUMBER(3);
  unitest((r == 8).is_true(), details, "real_type + NUMBER", err);

  r = static_cast<real_type>(3.0) + NUMBER();
  unitest(EXISTS(r).is_false(), details, "real_type + ? (NUMBER)", err);

  /* Сложение с integer_type */

  r = NUMBER(3.2) + static_cast<integer_type>(5);
  unitest((r == 8.2).is_true(), details, "NUMBER + integer_type", err);

  r = NUMBER() + static_cast<integer_type>(5);
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) + integer_type", err);

  r = static_cast<integer_type>(5) + NUMBER(3.2);
  unitest((r == 8.2).is_true(), details, "integer_type + NUMBER", err);

  r = static_cast<integer_type>(3) + NUMBER();
  unitest(EXISTS(r).is_false(), details, "integer_type + ? (NUMBER)", err);

  /* Сложение с int */

  r = NUMBER(3.2) + static_cast<int>(5);
  unitest((r == 8.2).is_true(), details, "NUMBER + int", err);

  r = NUMBER() + static_cast<int>(5);
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) + int", err);

  r = static_cast<int>(5) + NUMBER(3.2);
  unitest((r == 8.2).is_true(), details, "int + NUMBER", err);

  r = static_cast<int>(3) + NUMBER();
  unitest(EXISTS(r).is_false(), details, "int + ? (NUMBER)", err);

  /* Сложение с REAL */

  r = NUMBER(3.2) + REAL(5.0);
  unitest((r == 8.2).is_true(), details, "NUMBER + REAL", err);

  r = NUMBER() + REAL(3.0);
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) + REAL", err);

  r = NUMBER(3.0) + REAL();
  unitest(EXISTS(r).is_false(), details, "NUMBER + ? (REAL)", err);

  r = REAL(5.0) + NUMBER(3.2);
  unitest((r == 8.2).is_true(), details, "REAL + NUMBER", err);

  r = REAL() + NUMBER(3.0);
  unitest(EXISTS(r).is_false(), details, "? (REAL) + NUMBER", err);

  r = REAL(3.0) + NUMBER();
  unitest(EXISTS(r).is_false(), details, "REAL + ? (NUMBER)", err);

  /* Сложение с INTEGER */

  r = NUMBER(3.2) + INTEGER(5);
  unitest((r == 8.2).is_true(), details, "NUMBER + INTEGER", err);

  r = NUMBER() + INTEGER(5);
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) + INTEGER", err);

  r = NUMBER(3.2) + INTEGER();
  unitest(EXISTS(r).is_false(), details, "NUMBER + ? (INTEGER)", err);

  r = INTEGER(5) + NUMBER(3.2);
  unitest((r == 8.2).is_true(), details, "INTEGER + NUMBER", err);

  r = INTEGER() + NUMBER(3.2);
  unitest(EXISTS(r).is_false(), details, "? (INTEGER) + NUMBER", err);

  r = INTEGER(5) + NUMBER();
  unitest(EXISTS(r).is_false(), details, "INTEGER + ? (NUMBER)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_number_arith_sub(bool details) {
  print_title(details, "NUMBER ARITHMETIC - '-'");
  test_t err = test_t::TEST_OK;
  REAL r;

  /* Унарный минус */

  r = -NUMBER(3.0);
  unitest((r == -3).is_true(), details, "-NUMBER", err);

  r = -NUMBER();
  unitest(!r.is_determinated(), details, "-? (NUMBER)", err);

  /* Вычитание NUMBER */

  r = NUMBER{5.3} - NUMBER(3.2);
  unitest((r == 2.1).is_true(), details, "NUMBER + NUMBER", err);

  r = NUMBER() - NUMBER(3.2);
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) + NUMBER", err);

  r = NUMBER{5.3} - NUMBER();
  unitest(EXISTS(r).is_false(), details, "NUMBER + ? (NUMBER)", err);

  /* Вычитание real_type */

  r = NUMBER{5.3} - static_cast<real_type>(3.2);
  unitest((r == 2.1).is_true(), details, "NUMBER - real_type", err);

  r = NUMBER() - static_cast<real_type>(3.2);
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) - real_type", err);

  r = real_type{5.3} - NUMBER(3.2);
  unitest((r == 2.1).is_true(), details, "real_type - NUMBER", err);

  r = real_type{5.3} - NUMBER();
  unitest(EXISTS(r).is_false(), details, "real_type - ? (NUMBER)", err);

  /* Вычитание integer_type */

  r = NUMBER{5.3} - static_cast<integer_type>(3);
  unitest((r == 2.3).is_true(), details, "NUMBER - integer_type", err);

  r = NUMBER() - static_cast<integer_type>(3);
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) - integer_type", err);

  r = static_cast<integer_type>(5) - NUMBER(3.2);
  unitest((r == 1.8).is_true(), details, "integer_type - NUMBER", err);

  r = static_cast<integer_type>(5) - NUMBER();
  unitest(EXISTS(r).is_false(), details, "integer_type - ? (NUMBER)", err);

  /* Вычитание int */

  r = NUMBER{5.3} - static_cast<int>(3);
  unitest((r == 2.3).is_true(), details, "NUMBER - int", err);

  r = NUMBER() - static_cast<int>(3);
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) - int", err);

  r = static_cast<int>(5) - NUMBER(3.2);
  unitest((r == 1.8).is_true(), details, "int - NUMBER", err);

  r = static_cast<int>(5) - NUMBER();
  unitest(EXISTS(r).is_false(), details, "int - ? (NUMBER)", err);

  /* Вычитание REAL */

  r = NUMBER{5.3} - REAL(3.2);
  unitest((r == 2.1).is_true(), details, "NUMBER - REAL", err);

  r = NUMBER() - REAL(3.2);
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) - REAL", err);

  r = NUMBER{5.3} - REAL();
  unitest(EXISTS(r).is_false(), details, "NUMBER - ? (REAL)", err);

  r = REAL{5.3} - NUMBER(3.2);
  unitest((r == 2.1).is_true(), details, "REAL - NUMBER", err);

  r = REAL() - NUMBER(3.2);
  unitest(EXISTS(r).is_false(), details, "? (REAL) - NUMBER", err);

  r = REAL{5.3} - NUMBER();
  unitest(EXISTS(r).is_false(), details, "REAL - ?", err);

  /* Вычитание INTEGER */

  r = NUMBER{5.3} - INTEGER(3);
  unitest((r == 2.3).is_true(), details, "NUMBER - INTEGER", err);

  r = NUMBER() - INTEGER(3);
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) - INTEGER", err);

  r = NUMBER{5.3} - INTEGER();
  unitest(EXISTS(r).is_false(), details, "NUMBER - ? (INTEGER)", err);

  r = INTEGER(5) - NUMBER(3.2);
  unitest((r == 1.8).is_true(), details, "INTEGER - NUMBER", err);

  r = INTEGER() - NUMBER(3.2);
  unitest(EXISTS(r).is_false(), details, "? (INTEGER) - NUMBER", err);

  r = INTEGER(5) - NUMBER();
  unitest(EXISTS(r).is_false(), details, "INTEGER - ? (NUMBER)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_number_arith_mul(bool details) {
  print_title(details, "NUMBER ARITHMETIC - '*'");
  test_t err = test_t::TEST_OK;
  REAL r;

  /* Умножение на NUMBER */

  r = NUMBER(3.2) * NUMBER{5.3};
  unitest((r == 16.96).is_true(), details, "NUMBER * NUMBER", err);

  r = NUMBER() * NUMBER{5.3};
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) * NUMBER", err);

  r = NUMBER(3.2) * NUMBER();
  unitest(EXISTS(r).is_false(), details, "NUMBER * ? (NUMBER)", err);

  /* Умножение на real_type */

  r = NUMBER(3.2) * real_type{5.3};
  unitest((r == 16.96).is_true(), details, "NUMBER * real_type", err);

  r = NUMBER() * real_type{5.3};
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) * real_type", err);

  r = real_type{5.3} * NUMBER(3.2);
  unitest((r == 16.96).is_true(), details, "real_type * NUMBER", err);

  r = real_type{5.3} * NUMBER();
  unitest(EXISTS(r).is_false(), details, "real_type * ? (NUMBER)", err);

  /* Умножение на integer_type */

  r = NUMBER{3.3} * static_cast<integer_type>(5);
  unitest((r == 16.5).is_true(), details, "NUMBER * integer_type", err);

  r = NUMBER() * static_cast<integer_type>(5);
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) * integer_type", err);

  r = static_cast<integer_type>(5) * NUMBER{3.3};
  unitest((r == 16.5).is_true(), details, "integer_type * NUMBER", err);

  r = static_cast<integer_type>(5) * NUMBER();
  unitest(EXISTS(r).is_false(), details, "integer_type * ? (NUMBER)", err);

  /* Умножение на int */

  r = NUMBER{3.3} * static_cast<int>(5);
  unitest((r == 16.5).is_true(), details, "NUMBER * int", err);

  r = NUMBER() * static_cast<int>(5);
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) * int", err);

  r = static_cast<int>(5) * NUMBER{3.3};
  unitest((r == 16.5).is_true(), details, "int * NUMBER", err);

  r = static_cast<int>(5) * NUMBER();
  unitest(EXISTS(r).is_false(), details, "int * ? (NUMBER)", err);

  /* Умножение на REAL */

  r = NUMBER(3.2) * REAL{5.3};
  unitest((r == 16.96).is_true(), details, "NUMBER * REAL", err);

  r = NUMBER() * REAL{5.3};
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) * REAL", err);

  r = NUMBER(3.2) * REAL();
  unitest(EXISTS(r).is_false(), details, "NUMBER * ? (REAL)", err);

  r = REAL{5.3} * NUMBER(3.2);
  unitest((r == 16.96).is_true(), details, "REAL * NUMBER", err);

  r = REAL() * NUMBER(3.2);
  unitest(EXISTS(r).is_false(), details, "? (REAL) * NUMBER", err);

  r = REAL{5.3} * NUMBER();
  unitest(EXISTS(r).is_false(), details, "REAL * ? (NUMBER)", err);

  /* Умножение на INTEGER */

  r = NUMBER{3.3} * INTEGER(5);
  unitest((r == 16.5).is_true(), details, "NUMBER * INTEGER", err);

  r = NUMBER() * INTEGER(5);
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) * INTEGER", err);

  r = NUMBER(3.0) * INTEGER();
  unitest(EXISTS(r).is_false(), details, "NUMBER * ? (INTEGER)", err);

  r = INTEGER(5) * NUMBER{3.3};
  unitest((r == 16.5).is_true(), details, "INTEGER * NUMBER", err);

  r = INTEGER() * NUMBER{3.3};
  unitest(EXISTS(r).is_false(), details, "? (INTEGER) * NUMBER", err);

  r = INTEGER(5) * NUMBER();
  unitest(EXISTS(r).is_false(), details, "INTEGER * ? (NUMBER)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_number_arith_div(bool details) {
  print_title(details, "NUMBER ARITHMETIC - '/'");
  test_t err = test_t::TEST_OK;
  REAL r;

  /* Деление на NUMBER */

  r = NUMBER{16.96} / NUMBER{5.3};
  unitest((r == 3.2).is_true(), details, "NUMBER / NUMBER", err);

  r = NUMBER() / NUMBER{5.3};
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) / NUMBER", err);

  r = NUMBER(3.2) / NUMBER();
  unitest(EXISTS(r).is_false(), details, "NUMBER / ? (NUMBER)", err);

  /* Деление на real_type */

  r = NUMBER{16.96} / real_type{5.3};
  unitest((r == 3.2).is_true(), details, "NUMBER / real_type", err);

  r = NUMBER() / real_type{5.3};
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) / real_type", err);

  r = real_type{16.96} / NUMBER(3.2);
  unitest((r == 5.3).is_true(), details, "real_type / NUMBER", err);

  r = real_type{16.96} / NUMBER();
  unitest(EXISTS(r).is_false(), details, "real_type / ? (NUMBER)", err);

  /* Деление на integer_type */

  r = NUMBER{16.5} / static_cast<integer_type>(5);
  unitest((r == 3.3).is_true(), details, "NUMBER / integer_type", err);

  r = NUMBER() / static_cast<integer_type>(5);
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) / integer_type", err);

  r = integer_type{16} / NUMBER(3.2);
  unitest((r == 5).is_true(), details, "integer_type / NUMBER", err);

  r = integer_type{16} / NUMBER();
  unitest(EXISTS(r).is_false(), details, "integer_type / ? (NUMBER)", err);

  /* Деление на int */

  r = NUMBER{16.5} / static_cast<int>(5);
  unitest((r == 3.3).is_true(), details, "NUMBER / int", err);

  r = NUMBER() / static_cast<int>(5);
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) / int", err);

  r = int{16} / NUMBER(3.2);
  unitest((r == 5).is_true(), details, "int / NUMBER", err);

  r = static_cast<int>(5) / NUMBER();
  unitest(EXISTS(r).is_false(), details, "int / ? (NUMBER)", err);

  /* Деление на REAL */

  r = NUMBER{16.96} / REAL{5.3};
  unitest((r == 3.2).is_true(), details, "NUMBER / REAL", err);

  r = NUMBER() / REAL{5.3};
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) / REAL", err);

  r = NUMBER{16.96} / REAL();
  unitest(EXISTS(r).is_false(), details, "NUMBER / ? (REAL)", err);

  r = REAL{16.96} / NUMBER(3.2);
  unitest((r == 5.3).is_true(), details, "REAL / NUMBER", err);

  r = REAL() / NUMBER(3.2);
  unitest(EXISTS(r).is_false(), details, "? (REAL) / NUMBER", err);

  r = REAL{16.96} / NUMBER();
  unitest(EXISTS(r).is_false(), details, "REAL / ? (NUMBER)", err);

  /* Деление на INTEGER */

  r = NUMBER{16.5} / INTEGER(5);
  unitest((r == 3.3).is_true(), details, "NUMBER / INTEGER", err);

  r = NUMBER() / INTEGER(5);
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) / INTEGER", err);

  r = NUMBER{16.5} / INTEGER();
  unitest(EXISTS(r).is_false(), details, "NUMBER / ? (INTEGER)", err);

  r = INTEGER{16} / NUMBER(3.2);
  unitest((r == 5).is_true(), details, "INTEGER / NUMBER", err);

  r = INTEGER() / NUMBER(3.2);
  unitest(EXISTS(r).is_false(), details, "? (INTEGER) / NUMBER", err);

  r = INTEGER{16} / NUMBER();
  unitest(EXISTS(r).is_false(), details, "INTEGER / ? (NUMBER)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_number_arith_pow(bool details) {
  print_title(details, "NUMBER ARITHMETIC - '**'");
  test_t err = test_t::TEST_OK;
  REAL r;

  /* Возведение в степень NUMBER */

  r = NUMBER(2) POW NUMBER(3);
  unitest((r == 8).is_true(), details, "NUMBER ** NUMBER", err);

  r = NUMBER() POW NUMBER(3);
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) ** NUMBER", err);

  r = NUMBER(2) POW NUMBER();
  unitest(EXISTS(r).is_false(), details, "NUMBER ** ? (NUMBER)", err);

  /* Возведение в степень real_type */

  r = NUMBER(2) POW static_cast<real_type>(3);
  unitest((r == 8).is_true(), details, "NUMBER ** real_type", err);

  r = NUMBER() POW static_cast<real_type>(3);
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) ** real_type", err);

  r = static_cast<real_type>(2) POW NUMBER(3);
  unitest((r == 8).is_true(), details, "real_type ** NUMBER", err);

  r = static_cast<real_type>(2) POW NUMBER();
  unitest(EXISTS(r).is_false(), details, "real_type ** ? (NUMBER)", err);

  /* Возведение в степень integer_type */

  r = NUMBER(2) POW static_cast<integer_type>(3);
  unitest((r == 8).is_true(), details, "NUMBER POW integer_type", err);

  r = NUMBER() POW static_cast<integer_type>(5);
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) POW integer_type", err);

  r = static_cast<integer_type>(2) POW NUMBER(3);
  unitest((r == 8).is_true(), details, "integer_type POW NUMBER", err);

  r = static_cast<integer_type>(2) POW NUMBER();
  unitest(EXISTS(r).is_false(), details, "integer_type POW ? (NUMBER)", err);

  /* Возведение в степень int */

  r = NUMBER(2) POW static_cast<int>(3);
  unitest((r == 8).is_true(), details, "NUMBER POW int", err);

  r = NUMBER() POW static_cast<int>(3);
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) POW int", err);

  r = static_cast<int>(2) POW NUMBER(3);
  unitest((r == 8).is_true(), details, "int POW NUMBER", err);

  r = static_cast<int>(2) POW NUMBER();
  unitest(EXISTS(r).is_false(), details, "int POW ? (NUMBER)", err);


  /* Возведение в степень REAL */

  r = NUMBER(2) POW REAL(3);
  unitest((r == 8).is_true(), details, "NUMBER ** REAL", err);

  r = NUMBER() POW REAL(3);
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) ** REAL", err);

  r = NUMBER(2) POW REAL();
  unitest(EXISTS(r).is_false(), details, "NUMBER ** ? (REAL)", err);

  r = REAL(2) POW NUMBER(3);
  unitest((r == 8).is_true(), details, "REAL ** NUMBER", err);

  r = REAL() POW NUMBER(3);
  unitest(EXISTS(r).is_false(), details, "? (REAL) ** NUMBER", err);

  r = REAL(2) POW NUMBER();
  unitest(EXISTS(r).is_false(), details, "REAL ** ? (NUMBER)", err);

  /* Возведение в степень INTEGER */

  r = NUMBER(2) POW INTEGER(3);
  unitest((r == 8).is_true(), details, "NUMBER POW INTEGER", err);

  r = NUMBER() POW INTEGER(3);
  unitest(EXISTS(r).is_false(), details, "? (NUMBER) POW INTEGER", err);

  r = NUMBER(2) POW INTEGER();
  unitest(EXISTS(r).is_false(), details, "NUMBER POW ? (INTEGER)", err);

  r = INTEGER(2) POW NUMBER(3);
  unitest((r == 8).is_true(), details, "INTEGER POW NUMBER", err);

  r = INTEGER() POW NUMBER(3);
  unitest(EXISTS(r).is_false(), details, "? (INTEGER) POW NUMBER", err);

  r = INTEGER(2) POW NUMBER();
  unitest(EXISTS(r).is_false(), details, "INTEGER POW ? (NUMBER)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_number_arith_idiv(bool details) {
  print_title(details, "NUMBER ARITHMETIC - 'DIV'");
  test_t err = test_t::TEST_OK;
  INTEGER i;

  /* Деление на NUMBER */

  i = NUMBER{ 16.96 } DIV NUMBER{ 5.3 };
  unitest((i == 3).is_true(), details, "NUMBER DIV NUMBER", err);

  i = NUMBER() DIV NUMBER{ 5.3 };
  unitest(!i.is_determinated(), details, "? (NUMBER) DIV NUMBER", err);

  i = NUMBER{ 16.96 } DIV NUMBER();
  unitest(!i.is_determinated(), details, "NUMBER DIV ? (NUMBER)", err);

  /* Деление на real_type */

  i = NUMBER{ 16.96 } DIV real_type{ 5.3 };
  unitest((i == 3).is_true(), details, "NUMBER DIV real_type", err);

  i = NUMBER() DIV real_type{ 5.3 };
  unitest(!i.is_determinated(), details, "? (NUMBER) DIV real_type", err);

  i = real_type{ 16.96 } DIV NUMBER{ 5.3 };
  unitest((i == 3).is_true(), details, "real_type DIV NUMBER", err);

  i = real_type{ 16.96 } DIV NUMBER();
  unitest(!i.is_determinated(), details, "real_type DIV ? (NUMBER)", err);

  /* Деление на integer_type */

  i = NUMBER{ 16.96 } DIV integer_type{ 5 };
  unitest((i == 3).is_true(), details, "NUMBER DIV integer_type", err);

  i = NUMBER() DIV integer_type{ 5 };
  unitest(!i.is_determinated(), details, "? (NUMBER) DIV integer_type", err);

  i = integer_type{ 16 } DIV NUMBER{ 5.3 };
  unitest((i == 3).is_true(), details, "integer_type DIV NUMBER", err);

  i = integer_type{ 16 } DIV NUMBER();
  unitest(!i.is_determinated(), details, "integer_type DIV ? (NUMBER)", err);

  /* Деление на int */

  i = NUMBER{ 16.96 } DIV int{ 5 };
  unitest((i == 3).is_true(), details, "NUMBER DIV int", err);

  i = NUMBER() DIV int{ 5 };
  unitest(!i.is_determinated(), details, "? (NUMBER) DIV int", err);

  i = int{ 16 } DIV NUMBER{ 5.3 };
  unitest((i == 3).is_true(), details, "int DIV NUMBER", err);

  i = int{ 16 } DIV NUMBER();
  unitest(!i.is_determinated(), details, "int DIV ? (NUMBER)", err);

  /* Деление на REAL */

  i = NUMBER{ 16.96 } DIV REAL{ 5.3 };
  unitest((i == 3).is_true(), details, "NUMBER DIV REAL", err);

  i = NUMBER() DIV REAL{ 5.3 };
  unitest(!i.is_determinated(), details, "? (NUMBER) DIV REAL", err);

  i = NUMBER{ 16.96 } DIV REAL();
  unitest(!i.is_determinated(), details, "NUMBER DIV ? (REAL)", err);

  i = REAL{ 16.96 } DIV NUMBER{ 5.3 };
  unitest((i == 3).is_true(), details, "REAL DIV NUMBER", err);

  i = REAL() DIV NUMBER{ 5.3 };
  unitest(!i.is_determinated(), details, "? (REAL) DIV NUMBER", err);

  i = REAL{ 16.96 } DIV NUMBER();
  unitest(!i.is_determinated(), details, "REAL DIV ? (NUMBER)", err);

  /* Деление на INTEGER */

  i = NUMBER{ 16.96 } DIV INTEGER{ 5 };
  unitest((i == 3).is_true(), details, "NUMBER DIV INTEGER", err);

  i = NUMBER() DIV INTEGER{ 5 };
  unitest(!i.is_determinated(), details, "? (NUMBER) DIV INTEGER", err);

  i = NUMBER{ 16.96 } DIV INTEGER();
  unitest(!i.is_determinated(), details, "NUMBER DIV ? (INTEGER)", err);

  i = INTEGER{ 16 } DIV NUMBER{ 5.3 };
  unitest((i == 3).is_true(), details, "INTEGER DIV NUMBER", err);

  i = INTEGER() DIV NUMBER(5.3);
  unitest(!i.is_determinated(), details, "? (INTEGER) DIV NUMBER", err);

  i = INTEGER{ 16 } DIV NUMBER();
  unitest(!i.is_determinated(), details, "INTEGER DIV ? (NUMBER)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_number_arith_imod(bool details) {
  print_title(details, "NUMBER ARITHMETIC - 'MOD'");
  test_t err = test_t::TEST_OK;
  INTEGER i;

  /* Остаток от деления на NUMBER */

  i = NUMBER{ 16.96 } MOD NUMBER{ 5.3 };
  unitest((i == 1).is_true(), details, "NUMBER MOD NUMBER", err);

  i = NUMBER() MOD NUMBER{ 5.3 };
  unitest(!i.is_determinated(), details, "? (NUMBER) MOD NUMBER", err);

  i = NUMBER{ 16.96 } MOD NUMBER();
  unitest(!i.is_determinated(), details, "NUMBER MOD ? (NUMBER)", err);

  /* Остаток от деления на real_type */

  i = NUMBER{ 16.96 } MOD real_type{ 5.3 };
  unitest((i == 1).is_true(), details, "NUMBER MOD real_type", err);

  i = NUMBER() MOD real_type{ 5.3 };
  unitest(!i.is_determinated(), details, "? (NUMBER) MOD real_type", err);

  i = real_type{ 16.96 } MOD NUMBER{ 5.3 };
  unitest((i == 1).is_true(), details, "real_type MOD NUMBER", err);

  i = real_type{ 16.96 } MOD NUMBER();
  unitest(!i.is_determinated(), details, "real_type MOD ? (NUMBER)", err);

  /* Остаток от деления на integer_type */

  i = NUMBER{ 16.96 } MOD integer_type{ 5 };
  unitest((i == 1).is_true(), details, "NUMBER MOD integer_type", err);

  i = NUMBER() MOD integer_type{ 5 };
  unitest(!i.is_determinated(), details, "? (NUMBER) MOD integer_type", err);

  i = integer_type{ 16 } MOD NUMBER{ 5.3 };
  unitest((i == 1).is_true(), details, "integer_type MOD NUMBER", err);

  i = integer_type{ 16 } MOD NUMBER();
  unitest(!i.is_determinated(), details, "integer_type MOD ? (NUMBER)", err);

  /* Остаток от деления на int */

  i = NUMBER{ 16.96 } MOD int{ 5 };
  unitest((i == 1).is_true(), details, "NUMBER MOD int", err);

  i = NUMBER() MOD int{ 5 };
  unitest(!i.is_determinated(), details, "? (NUMBER) MOD int", err);

  i = int{ 16 } MOD NUMBER{ 5.3 };
  unitest((i == 1).is_true(), details, "int MOD NUMBER", err);

  i = int{ 16 } MOD NUMBER();
  unitest(!i.is_determinated(), details, "int MOD ? (NUMBER)", err);

  /* Остаток от деления на REAL */

  i = NUMBER{ 16.96 } MOD REAL{ 5.3 };
  unitest((i == 1).is_true(), details, "NUMBER MOD REAL", err);

  i = NUMBER() MOD REAL{ 5.3 };
  unitest(!i.is_determinated(), details, "? (NUMBER) MOD REAL", err);

  i = NUMBER{ 16.96 } MOD REAL();
  unitest(!i.is_determinated(), details, "NUMBER MOD ? (REAL)", err);

  i = REAL{ 16.96 } MOD NUMBER{ 5.3 };
  unitest((i == 1).is_true(), details, "REAL MOD NUMBER", err);

  i = REAL() MOD NUMBER{ 5.3 };
  unitest(!i.is_determinated(), details, "? (REAL) MOD NUMBER", err);

  i = REAL{ 16.96 } MOD NUMBER();
  unitest(!i.is_determinated(), details, "REAL MOD ? (NUMBER)", err);

  /* Остаток от деления на INTEGER */

  i = NUMBER{ 16.96 } MOD INTEGER{ 5 };
  unitest((i == 1).is_true(), details, "NUMBER MOD INTEGER", err);

  i = NUMBER() MOD INTEGER{ 5 };
  unitest(!i.is_determinated(), details, "? (NUMBER) MOD INTEGER", err);

  i = NUMBER{ 16.96 } MOD INTEGER();
  unitest(!i.is_determinated(), details, "NUMBER MOD ? (INTEGER)", err);

  i = INTEGER{ 16 } MOD NUMBER{ 5.3 };
  unitest((i == 1).is_true(), details, "INTEGER MOD NUMBER", err);

  i = INTEGER() MOD NUMBER(5.3);
  unitest(!i.is_determinated(), details, "? (INTEGER) MOD NUMBER", err);

  i = INTEGER{ 16 } MOD NUMBER();
  unitest(!i.is_determinated(), details, "INTEGER MOD ? (NUMBER)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_real_arith_add(bool details) {
  print_title(details, "REAL ARITHMETIC - '+'");
  test_t err = test_t::TEST_OK;
  REAL r;

  /* Унарный плюс */

  r = +REAL{3.5};
  unitest((r == 3.5).is_true(), details, "+REAL", err);

  r = +REAL();
  unitest(EXISTS(r).is_false(), details, "+? (REAL)", err);

  /* Сложение с REAL */

  r = REAL(3.2) + REAL{5.2};
  unitest((r == 8.4).is_true(), details, "REAL + REAL", err);

  r = REAL() + REAL{5.2};
  unitest(EXISTS(r).is_false(), details, "? (REAL) + REAL", err);

  r = REAL(3.2) + REAL();
  unitest(EXISTS(r).is_false(), details, "REAL + ? (REAL)", err);

  /* Сложение с real_type */

  r = REAL(3.2) + real_type(5.2);
  unitest((r == 8.4).is_true(), details, "REAL + real_type", err);

  r = REAL() + real_type{5.2};
  unitest(EXISTS(r).is_false(), details, "? (REAL) + real_type", err);

  r = real_type{5.2} + REAL(3.2);
  unitest((r == 8.4).is_true(), details, "real_type + REAL", err);

  r = static_cast<real_type>(3.2) + REAL();
  unitest(EXISTS(r).is_false(), details, "real_type + ? (REAL)", err);

  /* Сложение с integer_type */

  r = REAL(3.2) + static_cast<integer_type>(5);
  unitest((r == 8.2).is_true(), details, "REAL + integer_type", err);

  r = REAL() + static_cast<integer_type>(5);
  unitest(EXISTS(r).is_false(), details, "? (REAL) + integer_type", err);

  r = static_cast<integer_type>(5) + REAL(3.2);
  unitest((r == 8.2).is_true(), details, "integer_type + REAL", err);

  r = static_cast<integer_type>(3) + REAL();
  unitest(EXISTS(r).is_false(), details, "integer_type + ? (REAL)", err);

  /* Сложение с int */

  r = REAL(3.2) + static_cast<int>(5);
  unitest((r == 8.2).is_true(), details, "REAL + int", err);

  r = REAL() + static_cast<int>(5);
  unitest(EXISTS(r).is_false(), details, "? (REAL) + int", err);

  r = static_cast<int>(5) + REAL(3.2);
  unitest((r == 8.2).is_true(), details, "int + REAL", err);

  r = static_cast<int>(3) + REAL();
  unitest(EXISTS(r).is_false(), details, "int + ? (REAL)", err);

  /* Сложение с INTEGER */

  r = REAL(3.2) + INTEGER(5);
  unitest((r == 8.2).is_true(), details, "REAL + INTEGER", err);

  r = REAL() + INTEGER(5);
  unitest(EXISTS(r).is_false(), details, "? (REAL) + INTEGER", err);

  r = REAL(3.2) + INTEGER();
  unitest(EXISTS(r).is_false(), details, "REAL + ? (INTEGER)", err);

  r = INTEGER(5) + REAL(3.2);
  unitest((r == 8.2).is_true(), details, "INTEGER + REAL", err);

  r = INTEGER(3) + REAL();
  unitest(EXISTS(r).is_false(), details, "INTEGER + ? (REAL)", err);

  r = INTEGER() + REAL(3.2);
  unitest(EXISTS(r).is_false(), details, "? (INTEGER) + REAL", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_real_arith_sub(bool details) {
  print_title(details, "REAL ARITHMETIC - '-'");
  test_t err = test_t::TEST_OK;
  REAL r;

  /* Унарный минус */

  r = -REAL{3.5};
  unitest((r == -3.5).is_true(), details, "-REAL", err);

  r = -REAL();
  unitest(EXISTS(r).is_false(), details, "-?", err);

  /* Вычитание REAL */

  r = REAL{5.3} - REAL(3.2);
  unitest((r == 2.1).is_true(), details, "REAL - REAL", err);

  r = REAL() - REAL(3.2);
  unitest(EXISTS(r).is_false(), details, "? (REAL) - REAL", err);

  r = REAL{5.3} - REAL();
  unitest(EXISTS(r).is_false(), details, "REAL - ? (REAL)", err);

  /* Вычитание real_type */

  r = REAL{5.3} - static_cast<real_type>(3.2);
  unitest((r == 2.1).is_true(), details, "REAL - real_type", err);

  r = REAL() - static_cast<real_type>(3.2);
  unitest(EXISTS(r).is_false(), details, "? (REAL) - real_type", err);

  r = real_type{5.3} - REAL(3.2);
  unitest((r == 2.1).is_true(), details, "real_type - REAL", err);

  r = real_type{5.3} - REAL();
  unitest(EXISTS(r).is_false(), details, "real_type - ? (REAL)", err);

  /* Вычитание integer_type */

  r = REAL{5.3} - static_cast<integer_type>(3);
  unitest((r == 2.3).is_true(), details, "REAL - integer_type", err);

  r = REAL() - static_cast<integer_type>(3);
  unitest(EXISTS(r).is_false(), details, "? (REAL) - integer_type", err);

  r = static_cast<integer_type>(5) - REAL(3.2);
  unitest((r == 1.8).is_true(), details, "integer_type - REAL", err);

  r = static_cast<integer_type>(5) - REAL();
  unitest(EXISTS(r).is_false(), details, "integer_type - ? (REAL)", err);

  /* Вычитание int */

  r = REAL{5.3} - static_cast<int>(3);
  unitest((r == 2.3).is_true(), details, "REAL - int", err);

  r = REAL() - static_cast<int>(3);
  unitest(EXISTS(r).is_false(), details, "? (REAL) - int", err);

  r = static_cast<int>(5) - REAL(3.2);
  unitest((r == 1.8).is_true(), details, "int - REAL", err);

  r = static_cast<int>(5) - REAL();
  unitest(EXISTS(r).is_false(), details, "int - ? (REAL)", err);

  /* Вычитание INTEGER */

  r = REAL{5.3} - INTEGER(3);
  unitest((r == 2.3).is_true(), details, "REAL - INTEGER", err);

  r = REAL() - INTEGER(3);
  unitest(EXISTS(r).is_false(), details, "? (REAL) - INTEGER", err);

  r = REAL(5.3) - INTEGER();
  unitest(EXISTS(r).is_false(), details, "REAL - ? (INTEGER)", err);

  r = INTEGER(5) - REAL(3.2);
  unitest((r == 1.8).is_true(), details, "INTEGER - REAL", err);

  r = INTEGER(5) - REAL();
  unitest(EXISTS(r).is_false(), details, "INTEGER - ? (REAL)", err);

  r = INTEGER() - REAL(3.2);
  unitest(EXISTS(r).is_false(), details, "? (INTEGER) - REAL", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_real_arith_mul(bool details) {
  print_title(details, "REAL ARITHMETIC - '*'");
  test_t err = test_t::TEST_OK;
  REAL r;

  /* Умножение на REAL */

  r = REAL{5.3} * REAL(3.2);
  unitest((r == 16.96).is_true(), details, "REAL * REAL", err);

  r = REAL() * REAL(3.2);
  unitest(EXISTS(r).is_false(), details, "? (REAL) * REAL", err);

  r = REAL{5.3} - REAL();
  unitest(EXISTS(r).is_false(), details, "REAL * ? (REAL)", err);

  /* Умножение на real_type */

  r = REAL{5.3} * static_cast<real_type>(3.2);
  unitest((r == 16.96).is_true(), details, "REAL * real_type", err);

  r = REAL() * static_cast<real_type>(3.2);
  unitest(EXISTS(r).is_false(), details, "? (REAL) * real_type", err);

  r = real_type{5.3} * REAL(3.2);
  unitest((r == 16.96).is_true(), details, "real_type * REAL", err);

  r = real_type{5.3} * REAL();
  unitest(EXISTS(r).is_false(), details, "real_type * ? (REAL)", err);

  /* Умножение на integer_type */

  r = REAL{5.3} * static_cast<integer_type>(3);
  unitest((r == 15.9).is_true(), details, "REAL * integer_type", err);

  r = REAL() * static_cast<integer_type>(3);
  unitest(EXISTS(r).is_false(), details, "? (REAL) * integer_type", err);

  r = static_cast<integer_type>(5) * REAL{3.3};
  unitest((r == 16.5).is_true(), details, "integer_type * REAL", err);

  r = static_cast<integer_type>(5) * REAL();
  unitest(EXISTS(r).is_false(), details, "integer_type * ? (REAL)", err);

  /* Умножение на int */

  r = REAL{5.3} * static_cast<int>(3);
  unitest((r == 15.9).is_true(), details, "REAL * int", err);

  r = REAL() * static_cast<int>(3);
  unitest(EXISTS(r).is_false(), details, "? (REAL) * int", err);

  r = static_cast<int>(5) * REAL{3.3};
  unitest((r == 16.5).is_true(), details, "int * REAL", err);

  r = static_cast<int>(5) * REAL();
  unitest(EXISTS(r).is_false(), details, "int * ? (REAL)", err);

  /* Умножение на INTEGER */

  r = REAL{5.3} * INTEGER(3);
  unitest((r == 15.9).is_true(), details, "REAL * INTEGER", err);

  r = REAL() * INTEGER(3);
  unitest(EXISTS(r).is_false(), details, "? (REAL) * INTEGER", err);

  r = REAL(5.3) * INTEGER();
  unitest(EXISTS(r).is_false(), details, "REAL * ? (INTEGER)", err);

  r = INTEGER(5) * REAL{3.3};
  unitest((r == 16.5).is_true(), details, "INTEGER * REAL", err);

  r = INTEGER(5) * REAL();
  unitest(EXISTS(r).is_false(), details, "INTEGER * ? (REAL)", err);

  r = INTEGER() * REAL(3.2);
  unitest(EXISTS(r).is_false(), details, "? (INTEGER) * REAL", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_real_arith_div(bool details) {
  print_title(details, "REAL ARITHMETIC - '/'");
  test_t err = test_t::TEST_OK;
  REAL r;

  /* Деление на REAL */

  r = REAL(5.3) / REAL(3.2);
  unitest((r == 1.65625).is_true(), details, "REAL / REAL", err);

  r = REAL() / REAL(3.2);
  unitest(EXISTS(r).is_false(), details, "? (REAL) / REAL", err);

  r = REAL(5.3) - REAL();
  unitest(EXISTS(r).is_false(), details, "REAL / ? (REAL)", err);

  /* Деление на real_type */

  r = REAL(5.3) / static_cast<real_type>(3.2);
  unitest((r == 1.65625).is_true(), details, "REAL / real_type", err);

  r = REAL() / static_cast<real_type>(3.2);
  unitest(EXISTS(r).is_false(), details, "? (REAL) / real_type", err);

  r = static_cast<real_type>(5.3) / REAL(3.2);
  unitest((r == 1.65625).is_true(), details, "real_type / REAL", err);

  r = static_cast<real_type>(5.3) / REAL();
  unitest(EXISTS(r).is_false(), details, "real_type / ? (REAL)", err);

  /* Деление на integer_type */

  r = REAL{5.3} / static_cast<integer_type>(2);
  unitest((r == 2.65).is_true(), details, "REAL / integer_type", err);

  r = REAL() / static_cast<integer_type>(3);
  unitest(EXISTS(r).is_false(), details, "? (REAL) / integer_type", err);

  r = static_cast<integer_type>(5) / REAL(3.2);
  unitest((r == 1.5625).is_true(), details, "integer_type / REAL", err);

  r = static_cast<integer_type>(5) / REAL();
  unitest(EXISTS(r).is_false(), details, "integer_type / ? (REAL)", err);

  /* Деление на int */

  r = REAL{5.3} / static_cast<int>(2);
  unitest((r == 2.65).is_true(), details, "REAL / int", err);

  r = REAL() / static_cast<int>(3);
  unitest(EXISTS(r).is_false(), details, "? (REAL) / int", err);

  r = static_cast<int>(5) / REAL(3.2);
  unitest((r == 1.5625).is_true(), details, "int / REAL", err);

  r = static_cast<int>(5) / REAL();
  unitest(EXISTS(r).is_false(), details, "int / ? (REAL)", err);

  /* Деление на INTEGER */

  r = REAL{5.3} / INTEGER(2);
  unitest((r == 2.65).is_true(), details, "REAL / INTEGER", err);

  r = REAL() / INTEGER(3);
  unitest(EXISTS(r).is_false(), details, "? (REAL) / INTEGER", err);

  r = REAL(5.3) / INTEGER();
  unitest(EXISTS(r).is_false(), details, "REAL / ? (INTEGER)", err);

  r = INTEGER(5) / REAL(3.2);
  unitest((r == 1.5625).is_true(), details, "INTEGER / REAL", err);

  r = INTEGER(5) / REAL();
  unitest(EXISTS(r).is_false(), details, "INTEGER / ? (REAL)", err);

  r = INTEGER() / REAL(3.2);
  unitest(EXISTS(r).is_false(), details, "? (INTEGER) / REAL", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_real_arith_pow(bool details) {
  print_title(details, "REAL ARITHMETIC - '**'");
  test_t err = test_t::TEST_OK;
  REAL r;

  /* Возведение в степень REAL */

  r = REAL(2) POW REAL(3);
  unitest((r == 8).is_true(), details, "REAL ** REAL", err);

  r = REAL() POW REAL(3);
  unitest(EXISTS(r).is_false(), details, "? (REAL) ** REAL", err);

  r = REAL(2) POW REAL();
  unitest(EXISTS(r).is_false(), details, "REAL ** ? (REAL)", err);

  /* Возведение в степень real_type */

  r = REAL(2) POW static_cast<real_type>(3);
  unitest((r == 8).is_true(), details, "REAL ** real_type", err);

  r = REAL() POW static_cast<real_type>(3);
  unitest(EXISTS(r).is_false(), details, "? (REAL) ** real_type", err);

  r = static_cast<real_type>(2) POW REAL(3);
  unitest((r == 8).is_true(), details, "real_type ** REAL", err);

  r = static_cast<real_type>(2) POW REAL();
  unitest(EXISTS(r).is_false(), details, "real_type ** ? (REAL)", err);

  /* Возведение в степень integer_type */

  r = REAL(2) POW static_cast<integer_type>(3);
  unitest((r == 8).is_true(), details, "REAL POW integer_type", err);

  r = REAL() POW static_cast<integer_type>(5);
  unitest(EXISTS(r).is_false(), details, "? (REAL) POW integer_type", err);

  r = static_cast<integer_type>(2) POW REAL(3);
  unitest((r == 8).is_true(), details, "integer_type POW REAL", err);

  r = static_cast<integer_type>(2) POW REAL();
  unitest(EXISTS(r).is_false(), details, "integer_type POW ? (REAL)", err);

  /* Возведение в степень int */

  r = REAL(2) POW static_cast<int>(3);
  unitest((r == 8).is_true(), details, "REAL POW int", err);

  r = REAL() POW static_cast<int>(3);
  unitest(EXISTS(r).is_false(), details, "? (REAL) POW int", err);

  r = static_cast<int>(2) POW REAL(3);
  unitest((r == 8).is_true(), details, "int POW REAL", err);

  r = static_cast<int>(2) POW REAL();
  unitest(EXISTS(r).is_false(), details, "int POW ? (REAL)", err);

  /* Возведение в степень INTEGER */

  r = REAL(2) POW INTEGER(3);
  unitest((r == 8).is_true(), details, "REAL POW INTEGER", err);

  r = REAL() POW INTEGER(3);
  unitest(EXISTS(r).is_false(), details, "? (REAL) POW INTEGER", err);

  r = REAL(2) POW INTEGER();
  unitest(EXISTS(r).is_false(), details, "REAL POW ? (INTEGER)", err);

  r = INTEGER(2) POW REAL(3);
  unitest((r == 8).is_true(), details, "INTEGER POW REAL", err);

  r = INTEGER() POW REAL(3);
  unitest(EXISTS(r).is_false(), details, "? (INTEGER) POW REAL", err);

  r = INTEGER(2) POW REAL();
  unitest(EXISTS(r).is_false(), details, "INTEGER POW ? (REAL)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_real_arith_idiv(bool details) {
  print_title(details, "REAL ARITHMETIC - 'DIV'");
  test_t err = test_t::TEST_OK;
  INTEGER i;

  /* Деление на REAL */

  i = REAL{ 16.96 } DIV REAL{ 5.3 };
  unitest((i == 3).is_true(), details, "REAL DIV REAL", err);

  i = REAL() DIV REAL{ 5.3 };
  unitest(!i.is_determinated(), details, "? (REAL) DIV REAL", err);

  i = REAL{ 16.96 } DIV REAL();
  unitest(!i.is_determinated(), details, "REAL DIV ? (REAL)", err);

  /* Деление на real_type */

  i = REAL{ 16.96 } DIV real_type{ 5.3 };
  unitest((i == 3).is_true(), details, "REAL DIV real_type", err);

  i = REAL() DIV real_type{ 5.3 };
  unitest(!i.is_determinated(), details, "? (REAL) DIV real_type", err);

  i = real_type{ 16.96 } DIV REAL{ 5.3 };
  unitest((i == 3).is_true(), details, "real_type DIV REAL", err);

  i = real_type{ 16.96 } DIV REAL();
  unitest(!i.is_determinated(), details, "real_type DIV ? (REAL)", err);

  /* Деление на integer_type */

  i = REAL{ 16.96 } DIV integer_type{ 5 };
  unitest((i == 3).is_true(), details, "REAL DIV integer_type", err);

  i = REAL() DIV integer_type{ 5 };
  unitest(!i.is_determinated(), details, "? (REAL) DIV integer_type", err);

  i = integer_type{ 16 } DIV REAL{ 5.3 };
  unitest((i == 3).is_true(), details, "integer_type DIV REAL", err);

  i = integer_type{ 16 } DIV REAL();
  unitest(!i.is_determinated(), details, "integer_type DIV ? (REAL)", err);

  /* Деление на int */

  i = REAL{ 16.96 } DIV int{ 5 };
  unitest((i == 3).is_true(), details, "REAL DIV int", err);

  i = REAL() DIV int{ 5 };
  unitest(!i.is_determinated(), details, "? (REAL) DIV int", err);

  i = int{ 16 } DIV REAL{ 5.3 };
  unitest((i == 3).is_true(), details, "int DIV REAL", err);

  i = int{ 16 } DIV REAL();
  unitest(!i.is_determinated(), details, "int DIV ? (REAL)", err);

  /* Деление на INTEGER */

  i = REAL{ 16.96 } DIV INTEGER{ 5 };
  unitest((i == 3).is_true(), details, "REAL DIV INTEGER", err);

  i = REAL() DIV INTEGER{ 5 };
  unitest(!i.is_determinated(), details, "? (REAL) DIV INTEGER", err);

  i = REAL{ 16.96 } DIV INTEGER();
  unitest(!i.is_determinated(), details, "REAL DIV ? (INTEGER)", err);

  i = INTEGER{ 16 } DIV REAL{ 5.3 };
  unitest((i == 3).is_true(), details, "INTEGER DIV REAL", err);

  i = INTEGER() DIV REAL(5.3);
  unitest(!i.is_determinated(), details, "? (INTEGER) DIV REAL", err);

  i = INTEGER{ 16 } DIV REAL();
  unitest(!i.is_determinated(), details, "INTEGER DIV ? (REAL)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_real_arith_imod(bool details) {
  print_title(details, "REAL ARITHMETIC - 'MOD'");
  test_t err = test_t::TEST_OK;
  INTEGER i;

  /* Остаток от деления на REAL */

  i = REAL{ 16.96 } MOD REAL{ 5.3 };
  unitest((i == 1).is_true(), details, "REAL MOD REAL", err);

  i = REAL() MOD REAL{ 5.3 };
  unitest(!i.is_determinated(), details, "? (REAL) MOD REAL", err);

  i = REAL{ 16.96 } MOD REAL();
  unitest(!i.is_determinated(), details, "REAL MOD ? (REAL)", err);

  /* Остаток от деления на real_type */

  i = REAL{ 16.96 } MOD real_type{ 5.3 };
  unitest((i == 1).is_true(), details, "REAL MOD real_type", err);

  i = REAL() MOD real_type{ 5.3 };
  unitest(!i.is_determinated(), details, "? (REAL) MOD real_type", err);

  i = real_type{ 16.96 } MOD REAL{ 5.3 };
  unitest((i == 1).is_true(), details, "real_type MOD REAL", err);

  i = real_type{ 16.96 } MOD REAL();
  unitest(!i.is_determinated(), details, "real_type MOD ? (REAL)", err);

  /* Остаток от деления на integer_type */

  i = REAL{ 16.96 } MOD integer_type{ 5 };
  unitest((i == 1).is_true(), details, "REAL MOD integer_type", err);

  i = REAL() MOD integer_type{ 5 };
  unitest(!i.is_determinated(), details, "? (REAL) MOD integer_type", err);

  i = integer_type{ 16 } MOD REAL{ 5.3 };
  unitest((i == 1).is_true(), details, "integer_type MOD REAL", err);

  i = integer_type{ 16 } MOD REAL();
  unitest(!i.is_determinated(), details, "integer_type MOD ? (REAL)", err);

  /* Остаток от деления на int */

  i = REAL{ 16.96 } MOD int{ 5 };
  unitest((i == 1).is_true(), details, "REAL MOD int", err);

  i = REAL() MOD int{ 5 };
  unitest(!i.is_determinated(), details, "? (REAL) MOD int", err);

  i = int{ 16 } MOD REAL{ 5.3 };
  unitest((i == 1).is_true(), details, "int MOD REAL", err);

  i = int{ 16 } MOD REAL();
  unitest(!i.is_determinated(), details, "int MOD ? (REAL)", err);

  /* Остаток от деления на INTEGER */

  i = REAL{ 16.96 } MOD INTEGER{ 5 };
  unitest((i == 1).is_true(), details, "REAL MOD INTEGER", err);

  i = REAL() MOD INTEGER{ 5 };
  unitest(!i.is_determinated(), details, "? (REAL) MOD INTEGER", err);

  i = REAL{ 16.96 } MOD INTEGER();
  unitest(!i.is_determinated(), details, "REAL MOD ? (INTEGER)", err);

  i = INTEGER{ 16 } MOD REAL{ 5.3 };
  unitest((i == 1).is_true(), details, "INTEGER MOD REAL", err);

  i = INTEGER() MOD REAL(5.3);
  unitest(!i.is_determinated(), details, "? (INTEGER) MOD REAL", err);

  i = INTEGER{ 16 } MOD REAL();
  unitest(!i.is_determinated(), details, "INTEGER MOD ? (REAL)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_integer_arith_add(bool details) {
  print_title(details, "INTEGER ARITHMETIC - '+'");
  test_t err = test_t::TEST_OK;
  INTEGER i;
  REAL r;

  /* Унарный плюс */

  i = +INTEGER(3);
  unitest((i == 3).is_true(), details, "+INTEGER", err);

  i = +INTEGER();
  unitest(EXISTS(i).is_false(), details, "+?", err);

  /* Сложение с INTEGER */

  i = INTEGER(3) + INTEGER(5);
  unitest((i == 8).is_true(), details, "INTEGER + INTEGER", err);

  i = INTEGER() + INTEGER(5);
  unitest(EXISTS(i).is_false(), details, "? (INTEGER) + INTEGER", err);

  i = INTEGER(3) + INTEGER();
  unitest(EXISTS(i).is_false(), details, "INTEGER + ? (INTEGER)", err);

  /* Сложение с real_type */

  r = INTEGER(3) + real_type(5.5);
  unitest((r == 8.5).is_true(), details, "INTEGER + real_type", err);

  r = INTEGER() + real_type{5.5};
  unitest(EXISTS(r).is_false(), details, "? (INTEGER) + real_type", err);

  r = real_type{5.5} + INTEGER(3);
  unitest((r == 8.5).is_true(), details, "real_type + INTEGER", err);

  r = real_type{5.5} + INTEGER();
  unitest(EXISTS(r).is_false(), details, "real_type + ? (INTEGER)", err);

  /* Сложение с integer_type */

  i = INTEGER(3) + static_cast<integer_type>(5);
  unitest((i == 8).is_true(), details, "INTEGER + integer_type", err);

  i = INTEGER() + static_cast<integer_type>(5);
  unitest(EXISTS(i).is_false(), details, "? (INTEGER) + integer_type", err);

  i = static_cast<integer_type>(5) + INTEGER(3);
  unitest((i == 8).is_true(), details, "integer_type + INTEGER", err);

  i = static_cast<integer_type>(3) + INTEGER();
  unitest(EXISTS(i).is_false(), details, "integer_type + ? (INTEGER)", err);


  /* Сложение с int */

  i = INTEGER(3) + static_cast<int>(5);
  unitest((i == 8).is_true(), details, "INTEGER + int", err);

  i = INTEGER() + static_cast<int>(5);
  unitest(EXISTS(i).is_false(), details, "? (INTEGER) + int", err);

  i = static_cast<int>(5) + INTEGER(3);
  unitest((i == 8).is_true(), details, "int + INTEGER", err);

  i = static_cast<int>(3) + INTEGER();
  unitest(EXISTS(i).is_false(), details, "int + ? (INTEGER)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_integer_arith_sub(bool details) {
  print_title(details, "INTEGER ARITHMETIC - '-'");
  test_t err = test_t::TEST_OK;
  INTEGER i;
  REAL r;

  /* Унарный минус */

  i = -INTEGER(3);
  unitest((i == -3).is_true(), details, "-INTEGER", err);

  i = -INTEGER();
  unitest(EXISTS(i).is_false(), details, "-?", err);

  /* Вычитание INTEGER */

  i = INTEGER(5) - INTEGER(3);
  unitest((i == 2).is_true(), details, "INTEGER - INTEGER", err);

  i = INTEGER() - INTEGER(3);
  unitest(EXISTS(i).is_false(), details, "? (INTEGER) - INTEGER", err);

  i = INTEGER(5) - INTEGER();
  unitest(EXISTS(i).is_false(), details, "INTEGER - ? (INTEGER)", err);

  /* Вычитание real_type */

  r = INTEGER(6) - real_type{5.5};
  unitest((r == 0.5).is_true(), details, "INTEGER - real_type", err);

  r = INTEGER() - real_type{5.5};
  unitest(EXISTS(r).is_false(), details, "? (INTEGER) - real_type", err);

  r = real_type{6.5} - INTEGER(3);
  unitest((r == 3.5).is_true(), details, "real_type - INTEGER", err);

  r = real_type{6.5} - INTEGER();
  unitest(EXISTS(r).is_false(), details, "real_type - ? (INTEGER)", err);

  /* Вычитание integer_type */

  i = INTEGER(8) - static_cast<integer_type>(5);
  unitest((i == 3).is_true(), details, "INTEGER - integer_type", err);

  i = INTEGER() - static_cast<integer_type>(5);
  unitest(EXISTS(i).is_false(), details, "? (INTEGER) - integer_type", err);

  i = static_cast<integer_type>(8) - INTEGER(5);
  unitest((i == 3).is_true(), details, "integer_type - INTEGER", err);

  i = static_cast<integer_type>(8) - INTEGER();
  unitest(EXISTS(i).is_false(), details, "integer_type - ? (INTEGER)", err);


  /* Вычитание int */

  i = INTEGER(8) - static_cast<int>(5);
  unitest((i == 3).is_true(), details, "INTEGER - int", err);

  i = INTEGER() - static_cast<int>(5);
  unitest(EXISTS(i).is_false(), details, "? (INTEGER) - int", err);

  i = static_cast<int>(8) - INTEGER(5);
  unitest((i == 3).is_true(), details, "int - INTEGER", err);

  i = static_cast<int>(3) - INTEGER();
  unitest(EXISTS(i).is_false(), details, "int - ? (INTEGER)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_integer_arith_mul(bool details) {
  print_title(details, "INTEGER ARITHMETIC - '*'");
  test_t err = test_t::TEST_OK;
  INTEGER i;
  REAL r;

  /* Умножение на INTEGER */

  i = INTEGER(3) * INTEGER(5);
  unitest((i == 15).is_true(), details, "INTEGER * INTEGER", err);

  i = INTEGER() * INTEGER(5);
  unitest(EXISTS(i).is_false(), details, "? (INTEGER) * INTEGER", err);

  i = INTEGER(5) * INTEGER();
  unitest(EXISTS(i).is_false(), details, "INTEGER * ? (INTEGER)", err);

  /* Умножение на real_type */

  r = INTEGER(3) * static_cast<real_type>(5);
  unitest((r == 15).is_true(), details, "INTEGER * real_type", err);

  r = INTEGER() * static_cast<real_type>(5);
  unitest(EXISTS(r).is_false(), details, "? (INTEGER) * real_type", err);

  r = static_cast<real_type>(3) * INTEGER(5);
  unitest((r == 15).is_true(), details, "real_type * INTEGER", err);

  r = static_cast<real_type>(3) * INTEGER();
  unitest(EXISTS(r).is_false(), details, "real_type * ? (INTEGER)", err);

  /* Умножение на integer_type */

  i = INTEGER(3) * static_cast<integer_type>(5);
  unitest((i == 15).is_true(), details, "INTEGER * integer_type", err);

  i = INTEGER() * static_cast<integer_type>(5);
  unitest(EXISTS(i).is_false(), details, "? (INTEGER) * integer_type", err);

  i = static_cast<integer_type>(3) * INTEGER(5);
  unitest((i == 15).is_true(), details, "integer_type * INTEGER", err);

  i = static_cast<integer_type>(3) * INTEGER();
  unitest(EXISTS(i).is_false(), details, "integer_type * ? (INTEGER)", err);

  /* Умножение на int */

  i = INTEGER(3) * static_cast<int>(5);
  unitest((i == 15).is_true(), details, "INTEGER * int", err);

  i = INTEGER() * static_cast<int>(5);
  unitest(EXISTS(i).is_false(), details, "? (INTEGER) * int", err);

  i = static_cast<int>(3) * INTEGER(5);
  unitest((i == 15).is_true(), details, "int * INTEGER", err);

  i = static_cast<int>(3) * INTEGER();
  unitest(EXISTS(i).is_false(), details, "int * ? (INTEGER)", err);


  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_integer_arith_div(bool details) {
  print_title(details, "INTEGER ARITHMETIC - '/'");
  test_t err = test_t::TEST_OK;
  REAL r;

  /* Деление на INTEGER */

  r = INTEGER(15) / INTEGER(4);
  unitest((r == 3.75).is_true(), details, "INTEGER / INTEGER", err);

  r = INTEGER() / INTEGER(4);
  unitest(EXISTS(r).is_false(), details, "? (INTEGER) / INTEGER", err);

  r = INTEGER(15) / INTEGER();
  unitest(EXISTS(r).is_false(), details, "INTEGER / ? (INTEGER)", err);

  /* Деление на real_type */

  r = INTEGER(15) / static_cast<real_type>(3.2);
  unitest((r == 4.6875).is_true(), details, "INTEGER / real_type", err);

  r = INTEGER() / static_cast<real_type>(3.2);
  unitest(EXISTS(r).is_false(), details, "? (INTEGER) / real_type", err);

  r = static_cast<real_type>(15.5) / INTEGER(4);
  unitest((r == 3.875).is_true(), details, "real_type / INTEGER", err);

  r = static_cast<real_type>(15.5) / INTEGER();
  unitest(EXISTS(r).is_false(), details, "real_type / ? (INTEGER)", err);

  /* Деление на integer_type */

  r = INTEGER(15) / static_cast<integer_type>(4);
  unitest((r == 3.75).is_true(), details, "INTEGER / integer_type", err);

  r = INTEGER() / static_cast<integer_type>(4);
  unitest(EXISTS(r).is_false(), details, "? (INTEGER) / integer_type", err);

  r = static_cast<integer_type>(15) / INTEGER(4);
  unitest((r == 3.75).is_true(), details, "integer_type / INTEGER", err);

  r = static_cast<integer_type>(15) / INTEGER();
  unitest(EXISTS(r).is_false(), details, "integer_type / ? (INTEGER)", err);

  /* Деление на int */

  r = INTEGER(15) / static_cast<int>(4);
  unitest((r == 3.75).is_true(), details, "INTEGER / int", err);

  r = INTEGER() / static_cast<int>(4);
  unitest(EXISTS(r).is_false(), details, "? (INTEGER) / int", err);

  r = static_cast<int>(15) / INTEGER(4);
  unitest((r == 3.75).is_true(), details, "int / INTEGER", err);

  r = static_cast<int>(15) / INTEGER();
  unitest(EXISTS(r).is_false(), details, "int / ? (INTEGER)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_integer_arith_pow(bool details) {
  print_title(details, "INTEGER ARITHMETIC - '**'");
  test_t err = test_t::TEST_OK;
  INTEGER i, i1;
  REAL r;

  /* INTEGER возвести в степень INTEGER */

  i = INTEGER(2) POW INTEGER(3);
  unitest((i == 8).is_true(), details, "INTEGER ** INTEGER", err);

  i = INTEGER() POW INTEGER(3);
  unitest(EXISTS(i).is_false(), details, "? (INTEGER) ** INTEGER", err);

  i = INTEGER(2) POW INTEGER();
  unitest(EXISTS(i).is_false(), details, "INTEGER ** ? (INTEGER)", err);

  /* Возведение в степень real_type */

  r = INTEGER(4) POW static_cast<real_type>(3.5);
  unitest((r == 128).is_true(), details, "INTEGER ** real_type", err);

  r = INTEGER() POW static_cast<real_type>(3.5);
  unitest(EXISTS(r).is_false(), details, "? (INTEGER) ** real_type", err);

  r = static_cast<real_type>(2.5) POW INTEGER(3);
  unitest((r == 15.625).is_true(), details, "real_type ** INTEGER", err);

  r = static_cast<real_type>(2.5) POW INTEGER();
  unitest(EXISTS(r).is_false(), details, "real_type ** ? (INTEGER)", err);

  /* Возведение в степень integer_type */

  i = INTEGER(2) POW static_cast<integer_type>(3);
  unitest((i == 8).is_true(), details, "INTEGER ** integer_type", err);

  i = INTEGER() POW static_cast<integer_type>(3);
  unitest(EXISTS(i).is_false(), details, "? (INTEGER) ** integer_type", err);

  i = static_cast<integer_type>(2) POW INTEGER(3);
  unitest((i == 8).is_true(), details, "integer_type ** INTEGER", err);

  i = static_cast<integer_type>(2) POW INTEGER();
  unitest(EXISTS(i).is_false(), details, "integer_type ** ? (INTEGER)", err);

  /* Возведение в степень int */

  i = INTEGER(2) POW static_cast<int>(3);
  unitest((i == 8).is_true(), details, "INTEGER ** int", err);

  i = INTEGER() POW static_cast<int>(3);
  unitest(EXISTS(i).is_false(), details, "? (INTEGER) ** int", err);

  i = static_cast<int>(2) POW INTEGER(3);
  unitest((i == 8).is_true(), details, "int ** INTEGER", err);

  i = static_cast<int>(2) POW INTEGER();
  unitest(EXISTS(i).is_false(), details, "int ** ? (INTEGER)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_integer_arith_idiv(bool details) {
  print_title(details, "INTEGER ARITHMETIC - 'DIV'");
  test_t err = test_t::TEST_OK;
  REAL i;

  /* Деление на INTEGER */

  i = INTEGER(15) DIV INTEGER(4);
  unitest((i == 3).is_true(), details, "INTEGER DIV INTEGER", err);

  i = INTEGER() DIV INTEGER(4);
  unitest(EXISTS(i).is_false(), details, "? (INTEGER) DIV INTEGER", err);

  i = INTEGER(15) DIV INTEGER();
  unitest(EXISTS(i).is_false(), details, "INTEGER DIV ? (INTEGER)", err);

  /* Деление на real_type */

  i = INTEGER(16) DIV static_cast<real_type>(3.2);
  unitest((i == 5).is_true(), details, "INTEGER DIV real_type", err);

  i = INTEGER() DIV static_cast<real_type>(3.2);
  unitest(EXISTS(i).is_false(), details, "? (INTEGER) DIV real_type", err);

  i = static_cast<real_type>(16.5) DIV INTEGER(3);
  unitest((i == 5).is_true(), details, "real_type DIV INTEGER", err);

  i = static_cast<real_type>(16.5) DIV INTEGER();
  unitest(EXISTS(i).is_false(), details, "real_type DIV ? (INTEGER)", err);

  /* Деление на integer_type */

  i = INTEGER(15) DIV static_cast<integer_type>(4);
  unitest((i == 3).is_true(), details, "INTEGER DIV integer_type", err);

  i = INTEGER() DIV static_cast<integer_type>(4);
  unitest(EXISTS(i).is_false(), details, "? (INTEGER) DIV integer_type", err);

  i = static_cast<integer_type>(15) DIV INTEGER(4);
  unitest((i == 3).is_true(), details, "integer_type DIV INTEGER", err);

  i = static_cast<integer_type>(15) DIV INTEGER();
  unitest(EXISTS(i).is_false(), details, "integer_type DIV ? (INTEGER)", err);

  /* Деление на int */

  i = INTEGER(15) DIV static_cast<int>(4);
  unitest((i == 3).is_true(), details, "INTEGER DIV int", err);

  i = INTEGER() DIV static_cast<int>(4);
  unitest(EXISTS(i).is_false(), details, "? (INTEGER) DIV int", err);

  i = static_cast<int>(15) DIV INTEGER(4);
  unitest((i == 3).is_true(), details, "int DIV INTEGER", err);

  i = static_cast<int>(15) DIV INTEGER();
  unitest(EXISTS(i).is_false(), details, "int DIV ? (INTEGER)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_integer_arith_imod(bool details) {
  print_title(details, "INTEGER ARITHMETIC - 'MOD'");
  test_t err = test_t::TEST_OK;
  REAL i;

  /* Остаток от деления на INTEGER */

  i = INTEGER(15) MOD INTEGER(4);
  unitest((i == 3).is_true(), details, "INTEGER MOD INTEGER", err);

  i = INTEGER() MOD INTEGER(4);
  unitest(EXISTS(i).is_false(), details, "? (INTEGER) MOD INTEGER", err);

  i = INTEGER(15) MOD INTEGER();
  unitest(EXISTS(i).is_false(), details, "INTEGER MOD ? (INTEGER)", err);

  /* Остаток от деления на real_type */

  i = INTEGER(16) MOD static_cast<real_type>(3.2);
  unitest((i == 1).is_true(), details, "INTEGER MOD real_type", err);

  i = INTEGER() MOD static_cast<real_type>(3.2);
  unitest(EXISTS(i).is_false(), details, "? (INTEGER) MOD real_type", err);

  i = static_cast<real_type>(16.5) MOD INTEGER(3);
  unitest((i == 1).is_true(), details, "real_type MOD INTEGER", err);

  i = static_cast<real_type>(16.5) MOD INTEGER();
  unitest(EXISTS(i).is_false(), details, "real_type MOD ? (INTEGER)", err);

  /* Остаток от деления на integer_type */

  i = INTEGER(15) MOD static_cast<integer_type>(4);
  unitest((i == 3).is_true(), details, "INTEGER MOD integer_type", err);

  i = INTEGER() MOD static_cast<integer_type>(4);
  unitest(EXISTS(i).is_false(), details, "? (INTEGER) MOD integer_type", err);

  i = static_cast<integer_type>(15) MOD INTEGER(4);
  unitest((i == 3).is_true(), details, "integer_type MOD INTEGER", err);

  i = static_cast<integer_type>(15) MOD INTEGER();
  unitest(EXISTS(i).is_false(), details, "integer_type MOD ? (INTEGER)", err);

  /* Остаток от деления на int */

  i = INTEGER(15) MOD static_cast<int>(4);
  unitest((i == 3).is_true(), details, "INTEGER MOD int", err);

  i = INTEGER() MOD static_cast<int>(4);
  unitest(EXISTS(i).is_false(), details, "? (INTEGER) MOD int", err);

  i = static_cast<int>(15) MOD INTEGER(4);
  unitest((i == 3).is_true(), details, "int MOD INTEGER", err);

  i = static_cast<int>(15) MOD INTEGER();
  unitest(EXISTS(i).is_false(), details, "int MOD ? (INTEGER)", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}


static bool test_array_init(bool details) {
  print_title(details, "ARRAY INIT ");
  test_t err = test_t::TEST_OK;

  ARRAY<INTEGER> ArrayN(15, 18);
  ARRAY<INTEGER> Array(15, 18, AGGREGATE_GENERIC::OPTIONAL);
  ARRAY<INTEGER> ArrayU(15, 18, AGGREGATE_GENERIC::OPTIONAL | AGGREGATE_GENERIC::UNIQUE);
  ARRAY<REAL> ArrayR(1,4);

  /* Инициализация списком инициализации */
  Array = { INTEGER(1), 2, INTEGER(3) };
  unitest((Array[15] == INTEGER(1)).is_true() &&
          (Array[16] == INTEGER(2)).is_true() &&
          (Array[17] == INTEGER(3)).is_true() &&
           EXISTS(Array[18]).is_false(), details, "ARRAY := {...}", err);

  bool catched = false;
  try {
  ArrayN = { INTEGER(1), 2, INTEGER(3) };
  } catch(exception&) {
    catched = true;
  }
  unitest(catched, details, "ARRAY<not optional> := { ? } -> error", err);

  catched = false;
  try {
  Array = { INTEGER(1), 2, INTEGER(3), 4, 5 };
  } catch(exception&) {
    catched = true;
  }
  unitest(catched, details, "ARRAY := { too big list } -> error", err);

  catched = false;
  try {
  ArrayN = { INTEGER(1), 2, INTEGER(3) };
  } catch(exception&) {
    catched = true;
  }
  unitest(catched, details, "ARRAY<not optional> := { too small list } -> error", err);

  catched = false;
  try {
  ArrayU = { INTEGER(1), 1, INTEGER(3) };
  } catch(exception&) {
    catched = true;
  }
  unitest(catched, details, "ARRAY<unique> := { 1,1,... } -> error", err);


  /* Присвоение уточнением элементов */
  Array[15] = 3;
  Array[16] = 2;
  Array[17] = INTEGER(1);
  unitest((Array[15] == INTEGER(3)).is_true() &&
          (Array[16] == INTEGER(2)).is_true() &&
          (Array[17] == INTEGER(1)).is_true() &&
           EXISTS(Array[18]).is_false(), details, "ARRAY[X] := X", err);

  catched = false;
  try {
  Array[14] = INTEGER(1);
  } catch(exception&) {
    catched = true;
  }
  unitest(catched, details, "ARRAY[out of borders] := X -> error", err);

  ArrayU = { 1,2,3,4 };

  catched = false;
  try {
  ArrayU.set_element(15, INTEGER(2));
  } catch(exception&) {
    catched = true;
  }
  unitest(catched, details, "ARRAY<unique>[X] := not unique value -> error", err);



  Array[18] = 4;

  /* Присвоение массива */
  ArrayR = Array;
  unitest((ArrayR[1] == 3.0).is_true() &&
          (ArrayR[2] == 2.0).is_true() &&
          (ArrayR[3] == 1.0).is_true() &&
          (ArrayR[4] == 4.0).is_true(), details, "ARRAY := ARRAY", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}
#if 0
static bool test_list_init(bool details) {
  print_title(details, "LIST INIT ");
  test_t err = test_t::TEST_OK;

  LIST<INTEGER> List(3, 5), List2;

  /* Инициализация списком инициализации */
  List = { INTEGER(1), INTEGER(2), 3, INTEGER(4) };

  unitest((List[1] == INTEGER(1)).is_true() &&
    (List[2] == INTEGER(2)).is_true() &&
    (List[3] == INTEGER(3)).is_true() &&
    (List[4] == INTEGER(4)).is_true(), details, "LIST := {...}", err);

  /* Присвоение уточнением элементов */
  List[1] = 4;
  List[2] = INTEGER(3);
  List[3] = 2;
  List[4] = 1;
  unitest((List[1] == INTEGER(4)).is_true() &&
    (List[2] == INTEGER(3)).is_true() &&
    (List[3] == INTEGER(2)).is_true() &&
    (List[4] == INTEGER(1)).is_true(), details, "LIST[X] := X", err);

  /* Присвоение списка того же типа */
  List2 = List;
  unitest((List2[1] == 4).is_true() &&
    (List2[2] == 3).is_true() &&
    (List2[3] == 2).is_true() &&
    (List2[4] == 1).is_true(), details, "LIST<INTEGER> := LIST<INTEGER>", err);

  /* Присвоение совместимого списка */
  LIST<REAL> ListR;
  ListR = List;
  unitest((ListR[1] == 4.0).is_true() &&
    (ListR[2] == 3.0).is_true() &&
    (ListR[3] == 2.0).is_true() &&
    (ListR[4] == 1.0).is_true(), details, "LIST<REAL> := LIST<INTEGER>", err);


  /* Присвоение совместимого списка #1 */
  LIST<LOGICAL> ListL;
  LIST<BOOLEAN> ListB(3, 5);
  ListB = { TRUE, FALSE, TRUE, FALSE };
  ListL = ListB;
  unitest((ListL[1] == TRUE).is_true() &&
    (ListL[2] == FALSE).is_true() &&
    (ListL[3] == TRUE).is_true() &&
    (ListL[4] == FALSE).is_true(), details, "LIST<LOGICAL> := LIST<BOOLEAN>", err);

  bool catched = false;
  try {
    ListL = List;
  }
  catch (exception& e) {
    catched = true;
    if (details) printf("Catched exception '%s'\nat '%s'\n", e.what(), e.where());
  }
  unitest(catched, details, "LIST<LOGICAL> := LIST<INTEGER> -> error", err);

  /* Присвоение совместимого списка #2 */
  catched = false;
  try {
    List = ListR;
  }
  catch (exception& e) {
    catched = true;
    if (details) printf("Catched exception '%s'\nat '%s'\n", e.what(), e.where());
  }
  unitest(catched, details, "LIST<INTEGER> := LIST<REAL> -> error", err);

  /* Присвоение совместимого списка #3 */
  LIST<LOGICAL> ListL2(3, 5);
  ListL2 = { TRUE, FALSE, TRUE };
  catched = false;
  try {
    List = ListL2;
  }
  catch (exception& e) {
    catched = true;
    if (details) printf("Catched exception '%s'\nat '%s'\n", e.what(), e.where());
  }
  unitest(catched, details, "LIST<INTEGER> := LIST<LOGICAL> -> error", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_bag_init(bool details) {
  print_title(details, "BAG INIT ");
  test_t err = test_t::TEST_OK;

  INTEGER i1 = 1, i2 = 2, i3 = 3;
  BAG<INTEGER> Bag(3, 5);
  BAG<REAL> BagR;

  /* Инициализация списком инициализации */
  Bag = {i1, 2, i3, i3};

  unitest(VALUE_IN<INTEGER>(Bag, i1).is_true() &&
          VALUE_IN<INTEGER>(Bag, 2).is_true() &&
          VALUE_IN<INTEGER>(Bag, i3).is_true(),
          details, "BAG := {...}", err);

  /* Присвоение множества */
  BagR = Bag;

  unitest(VALUE_IN<REAL>(BagR, i1).is_true() &&
          VALUE_IN<REAL>(BagR, 2).is_true() &&
          VALUE_IN<REAL>(BagR, i3).is_true(),
          details, "BAG := BAG", err);

  SET<INTEGER> Set(3, 5);
  Set = {i1, i2, i3};

  BagR = Set;

  unitest(VALUE_IN<REAL>(BagR, i1).is_true() &&
          VALUE_IN<REAL>(BagR, i2).is_true() &&
          VALUE_IN<REAL>(BagR, i3).is_true(),
          details, "BAG := SET", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_set_init(bool details) {
  print_title(details, "SET INIT ");
  test_t err = test_t::TEST_OK;

  INTEGER i1 = 1, i2 = 2, i3 = 3;
  SET<INTEGER> Set(3, 5);
  SET<REAL> SetR;

  /* Инициализация списком инициализации */
  Set = {i1, i2, i3};
  unitest(VALUE_IN<INTEGER>(Set, i1).is_true() &&
          VALUE_IN<INTEGER>(Set, i2).is_true() &&
          VALUE_IN<INTEGER>(Set, i3).is_true(),
          details, "SET := {...}", err);

  /* Присвоение набора */
  SetR = Set;
  unitest(VALUE_IN<REAL>(SetR, i1).is_true() &&
          VALUE_IN<REAL>(SetR, i2).is_true() &&
          VALUE_IN<REAL>(SetR, i3).is_true(),
          details, "SET := SET", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}
#endif
static bool test_aggr_rel(bool details) {
  print_title(details, "AGGREGATE RELATIONS");
  test_t err = test_t::TEST_OK;

  ARRAY<INTEGER> Array_indet1(0,5);
  ARRAY<INTEGER> Array_indet2(0,5);
  ARRAY<INTEGER> Array3(0,3);                     Array3  = {0,1,2,3};
  ARRAY<INTEGER> Array4(0,3);                     Array4  = {0,1,2,3};
  ARRAY<INTEGER> Array5(1,4);                     Array5  = {0,1,2,3};
  ARRAY<INTEGER> Array6(0,3);                     Array6  = {0,2,1,3};
  ARRAY<REAL> Array7(0,3);                        Array7  = {0,1,2,3};
  ARRAY<REAL> Array8(0,3,AGGREGATE_GENERIC::OPTIONAL);    Array8  = { 0, REAL(), REAL(), 3 };
  ARRAY<INTEGER> Array9(0,3,AGGREGATE_GENERIC::OPTIONAL); Array9  = { 0, 1, 2, INTEGER() };
  ARRAY<REAL> Array10(0,3,AGGREGATE_GENERIC::OPTIONAL);   Array10 = { REAL(), REAL(), REAL(), 3 };

  unitest((Array_indet1 == Array_indet2).is_unknown(), details, "? = ? -> UNKNOWN", err);
  unitest((Array_indet1 == Array3).is_unknown(), details, "? = ARRAY -> UNKNOWN", err);
  unitest((Array3 == Array_indet2).is_unknown(), details, "ARRAY = ? -> UNKNOWN", err);
  unitest((Array3 == Array4).is_true(), details, "ARRAY<INTEGER>{0,1,2,3} = ARRAY<INTEGER>{0,1,2,3} -> TRUE", err);
  unitest((Array3 == Array7).is_true(), details, "ARRAY<INTEGER>{0,1,2,3} = ARRAY<REAL>{0,1,2,3} -> TRUE", err);
  unitest((Array7 == Array3).is_true(), details, "ARRAY<REAL>{0,1,2,3} = ARRAY<INTEGER>{0,1,2,3} -> TRUE", err);
  unitest((Array8 == Array9).is_unknown(), details, "ARRAY<REAL>{0,?,?,3} = ARRAY<INTEGER>{0,1,2,?} -> UNKNOWN", err);
  unitest((Array9 == Array10).is_unknown(), details, "ARRAY<INTEGER>{0, 1, 2, ?} = ARRAY<REAL>{?,?,?,3} -> UNKNOWN", err);
  unitest((Array3 != Array5).is_true(), details, "ARRAY<INTEGER>[0,3] <> ARRAY<INTEGER>[1,4]", err);
  unitest((Array3 != Array6).is_true(), details, "ARRAY<INTEGER>{0,1,2,3} <> ARRAY<INTEGER>{0,2,1,3}", err);

  unitest((Array_indet1.is_instance_equal(Array_indet2)).is_unknown(), details, "? :=: ? -> UNKNOWN", err);
  unitest((Array_indet1.is_instance_equal(Array3)).is_unknown(), details, "? :=: ARRAY -> UNKNOWN", err);
  unitest((Array3.is_instance_equal(Array_indet2)).is_unknown(), details, "ARRAY :=: ? -> UNKNOWN", err);
  unitest((Array3.is_instance_equal(Array4)).is_true(), details, "ARRAY<INTEGER>{0,1,2,3} :=: ARRAY<INTEGER>{0,1,2,3} -> TRUE", err);
  unitest((Array3.is_instance_equal(Array7)).is_true(), details, "ARRAY<INTEGER>{0,1,2,3} :=: ARRAY<REAL>{0,1,2,3} -> TRUE", err);
  unitest((Array7.is_instance_equal(Array3)).is_true(), details, "ARRAY<REAL>{0,1,2,3} = ARRAY<INTEGER>{0,1,2,3} -> TRUE", err);
  unitest((Array8.is_instance_equal(Array9)).is_unknown(), details, "ARRAY<REAL>{0,?,?,3} :=: ARRAY<INTEGER>{0,1,2,?} -> UNKNOWN", err);
  unitest((Array9.is_instance_equal(Array10)).is_unknown(), details, "ARRAY<INTEGER>{0, 1, 2, ?} :=: ARRAY<REAL>{?,?,?,3} -> UNKNOWN", err);
  unitest((Array3.is_instance_equal(Array5)).is_false(), details, "ARRAY<INTEGER>[0,3] :<>: ARRAY<INTEGER>[1,4]", err);
  unitest((Array3.is_instance_equal(Array6)).is_false(), details, "ARRAY<INTEGER>{0,1,2,3} :<>: ARRAY<INTEGER>{0,2,1,3}", err);
#if 0
  LIST<INTEGER> List_indet1(0,5);
  LIST<INTEGER> List_indet2(0,5);
  LIST<INTEGER> List3(0,4);              List3 = {0,1,2,3};
  LIST<INTEGER> List4(0,4);              List4 = {0,1,2,3};
  LIST<INTEGER> List5(0,5);              List5 = {0,1,2,3};
  LIST<INTEGER> List6(0,4);              List6 = {0,2,1,3};
  LIST<REAL> List7(0,4);                 List7 = {0,1,2,3};

  unitest((List_indet1 == List_indet2).is_unknown(), details, "? = ? -> UNKNOWN", err);
  unitest((List_indet1 == List3).is_unknown(), details, "? = LIST -> UNKNOWN", err);
  unitest((List3 == List_indet2).is_unknown(), details, "LIST = ? -> UNKNOWN", err);
  unitest((List3 == List4).is_true(), details, "LIST<INTEGER>{0,1,2,3} = LIST<INTEGER>{0,1,2,3} -> TRUE", err);
  unitest((List3 == List7).is_true(), details, "LIST<INTEGER>{0,1,2,3} = LIST<REAL>{0,1,2,3} -> TRUE", err);
  unitest((List7 == List3).is_true(), details, "LIST<REAL>{0,1,2,3} = LIST<INTEGER>{0,1,2,3} -> TRUE", err);

  unitest((List_indet1.is_instance_equal(List_indet2)).is_unknown(), details, "? :=: ? -> UNKNOWN", err);
  unitest((List_indet1.is_instance_equal(List3)).is_unknown(), details, "? :=: LIST -> UNKNOWN", err);
  unitest((List3.is_instance_equal(List_indet2)).is_unknown(), details, "LIST :=: ? -> UNKNOWN", err);
  unitest((List3.is_instance_equal(List4)).is_true(), details, "LIST<INTEGER>{0,1,2,3} :=: LIST<INTEGER>{0,1,2,3} -> TRUE", err);
  unitest((List3.is_instance_equal(List7)).is_true(), details, "LIST<INTEGER>{0,1,2,3} :=: LIST<REAL>{0,1,2,3} -> TRUE", err);
  unitest((List7.is_instance_equal(List3)).is_true(), details, "LIST<REAL>{0,1,2,3} :=: LIST<INTEGER>{0,1,2,3} -> TRUE", err);

  BAG<INTEGER> Bag_indet1(0, 5);
  BAG<INTEGER> Bag_indet2(0, 5);
  BAG<INTEGER> Bag3(0, 4);              Bag3 = { 0,1,2,3 };
  BAG<INTEGER> Bag4(0, 4);              Bag4 = { 0,1,2,3 };
  BAG<INTEGER> Bag5(0, 5);              Bag5 = { 0,1,2,3 };
  BAG<INTEGER> Bag6(0, 4);              Bag6 = { 0,2,1,3 };
  BAG<REAL>    Bag7(0, 4);              Bag7 = { 0,1,2,3 };

  unitest((Bag_indet1 == Bag_indet2).is_unknown(), details, "? = ? -> UNKNOWN", err);
  unitest((Bag_indet1 == Bag3).is_unknown(), details, "? = Bag -> UNKNOWN", err);
  unitest((Bag3 == Bag_indet2).is_unknown(), details, "Bag = ? -> UNKNOWN", err);
  unitest((Bag3 == Bag4).is_true(), details, "BAG<INTEGER>{0,1,2,3} = BAG<INTEGER>{0,1,2,3} -> TRUE", err);
  unitest((Bag3 == Bag7).is_true(), details, "BAG<INTEGER>{0,1,2,3} = BAG<REAL>{0,1,2,3} -> TRUE", err);
  unitest((Bag7 == Bag3).is_true(), details, "BAG<REAL>{0,1,2,3} = BAG<INTEGER>{0,1,2,3} -> TRUE", err);

  unitest((Bag_indet1.is_instance_equal(Bag_indet2)).is_unknown(), details, "? :=: ? -> UNKNOWN", err);
  unitest((Bag_indet1.is_instance_equal(Bag3)).is_unknown(), details, "? :=: Bag -> UNKNOWN", err);
  unitest((Bag3.is_instance_equal(Bag_indet2)).is_unknown(), details, "Bag :=: ? -> UNKNOWN", err);
  unitest((Bag3.is_instance_equal(Bag4)).is_true(), details, "BAG<INTEGER>{0,1,2,3} :=: BAG<INTEGER>{0,1,2,3} -> TRUE", err);
  unitest((Bag3.is_instance_equal(Bag7)).is_true(), details, "BAG<INTEGER>{0,1,2,3} :=: BAG<REAL>{0,1,2,3} -> TRUE", err);
  unitest((Bag7.is_instance_equal(Bag3)).is_true(), details, "BAG<REAL>{0,1,2,3} :=: BAG<INTEGER>{0,1,2,3} -> TRUE", err);

#endif
  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_aggr_indexing(bool details) {
  print_title(details, "AGGREGATE INDEXING");
  test_t err = test_t::TEST_NOT_IMPL;

  /**
   * \file
   * \todo Добавить тестирование индексации аггрегатов
   */
  print_res(details, "TEST", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}
#if 0
static bool test_aggr_intersect(bool details) {
  print_title(details, "AGGREGATE INTERSECTION");
  test_t err = test_t::TEST_NOT_IMPL;

  /**
   * \file
   * \todo Добавить тестирование пересечения аггрегатов
   */
  print_res(details, "TEST", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}
#endif
#if 0
static bool test_list_union(bool details) {
  print_title(details, "LIST UNION");
  test_t err = test_t::TEST_OK;

  LIST<REAL> l1(0,3), l2(1,4), l3, l4;

  l1 = {1,2,INTEGER(3)};
  l2 = {4,5,6};

  //----------------------------------------------------------------------------------
  l3 = l3 + l4;
  unitest(EXISTS(l3).is_false(),
          details, "LIST = ? + ?", err);

  l3 = l4 + l1;
  unitest(EXISTS(l3).is_false(),
          details, "LIST = ? + LIST", err);

  l3 = l1 + l4;
  unitest(EXISTS(l3).is_false(),
          details, "LIST = LIST + ?", err);

  l4 = l1 + l2;

  unitest((SIZEOF(l4) == 6).is_true() &&
          (l4[1] == 1).is_true() && (l4[2] == 2).is_true() && (l4[3] == 3).is_true() &&
          (l4[4] == 4).is_true() && (l4[5] == 5).is_true() && (l4[6] == 6).is_true(),
          details, "LIST = LIST + LIST", err);

  l4 = l1 + 4LL;
  unitest((SIZEOF(l4) == 4).is_true() &&
          (l4[1] == 1).is_true() && (l4[2] == 2).is_true() && (l4[3] == 3).is_true() &&
          (l4[4] == 4).is_true(),
          details, "LIST = LIST + Element", err);

  l4 = 0 + l1;
  unitest((SIZEOF(l4) == 4).is_true() &&
          (l4[1] == 0).is_true() && (l4[2] == 1).is_true() && (l4[3] == 2).is_true() &&
          (l4[4] == 3).is_true(),
          details, "LIST = Element + LIST", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_set_union(bool details) {
  print_title(details, "SET UNION");
  test_t err = test_t::TEST_OK;

  SET<REAL> s1(0,3), s3, s4;
  SET<REAL> s2(1,4);
  s1 = {1,2,INTEGER(3)};
  s2 = {4,5,6};
  LIST<REAL> l2(1,4);
  l2 = {4,5,6};
  BAG<REAL> b2(1,4);
  b2 = {4,5,6};

  s3 = s3 + s4;
  unitest(EXISTS(s3).is_false(),
          details, "SET = ? + ?", err);

  s3 = s4 + s1;
  unitest(EXISTS(s3).is_false(),
          details, "SET = ? + SET", err);

  s3 = s1 + s4;
  unitest(EXISTS(s3).is_false(),
          details, "SET = SET + ?", err);

  s4 = s1 + s2;
  unitest((SIZEOF(s4) == 6).is_true() &&
    VALUE_IN(s4, REAL(1.0)).is_true() &&
    VALUE_IN(s4, REAL(2.0)).is_true() &&
    VALUE_IN(s4, REAL(3.0)).is_true() &&
    VALUE_IN(s4, REAL(4.0)).is_true() &&
    VALUE_IN(s4, REAL(5.0)).is_true() &&
    VALUE_IN(s4, REAL(6.0)).is_true(),
    details, "SET = SET + SET", err);

  s4 = s1 + REAL{4.5};
  unitest((SIZEOF(s4) == 4).is_true() &&
    VALUE_IN(s4, REAL(1.0)).is_true() &&
    VALUE_IN(s4, REAL(2.0)).is_true() &&
    VALUE_IN(s4, REAL(3.0)).is_true() &&
    VALUE_IN(s4, REAL(4.5)).is_true(),
    details, "SET = SET + Element (type)", err);

  s4 = s1 + INTEGER(4);
  unitest((SIZEOF(s4) == 4).is_true() &&
    VALUE_IN(s4, REAL(1.0)).is_true() &&
    VALUE_IN(s4, REAL(2.0)).is_true() &&
    VALUE_IN(s4, REAL(3.0)).is_true() &&
    VALUE_IN(s4, REAL(4.0)).is_true(),
    details, "SET = SET + Element (compat. type)", err);

  s4 = s1 + 4.5;
  unitest((SIZEOF(s4) == 4).is_true() &&
    VALUE_IN(s4, REAL(1.0)).is_true() &&
    VALUE_IN(s4, REAL(2.0)).is_true() &&
    VALUE_IN(s4, REAL(3.0)).is_true() &&
    VALUE_IN(s4, REAL(4.5)).is_true(),
    details, "SET = SET + Element (value)", err);

  s4 = s1 + 4;
  unitest((SIZEOF(s4) == 4).is_true() &&
    VALUE_IN(s4, REAL(1.0)).is_true() &&
    VALUE_IN(s4, REAL(2.0)).is_true() &&
    VALUE_IN(s4, REAL(3.0)).is_true() &&
    VALUE_IN(s4, REAL(4.0)).is_true(),
    details, "SET = SET + Element (compat. value)", err);

  s4 = REAL{0.5} + s1;
  unitest((SIZEOF(s4) == 4).is_true() &&
    VALUE_IN(s4, REAL(0.5)).is_true() &&
    VALUE_IN(s4, REAL(1.0)).is_true() &&
    VALUE_IN(s4, REAL(2.0)).is_true() &&
    VALUE_IN(s4, REAL(3.0)).is_true(),
          details, "SET = Element (type) + SET", err);

  s4 = INTEGER{0} + s1;
  unitest((SIZEOF(s4) == 4).is_true() &&
    VALUE_IN(s4, REAL(0.0)).is_true() &&
    VALUE_IN(s4, REAL(1.0)).is_true() &&
    VALUE_IN(s4, REAL(2.0)).is_true() &&
    VALUE_IN(s4, REAL(3.0)).is_true(),
          details, "SET = Element (compat. type) + SET", err);

  s4 = 5.5 + s1;
  unitest((SIZEOF(s4) == 4).is_true() &&
    VALUE_IN(s4, REAL(5.5)).is_true() &&
    VALUE_IN(s4, REAL(1.0)).is_true() &&
    VALUE_IN(s4, REAL(2.0)).is_true() &&
    VALUE_IN(s4, REAL(3.0)).is_true(),
          details, "SET = Element (value) + SET", err);

  s4 = 5 + s1;
  unitest((SIZEOF(s4) == 4).is_true() &&
    VALUE_IN(s4, REAL(5.0)).is_true() &&
    VALUE_IN(s4, REAL(1.0)).is_true() &&
    VALUE_IN(s4, REAL(2.0)).is_true() &&
    VALUE_IN(s4, REAL(3.0)).is_true(),
          details, "SET = Element (compat. value) + SET", err);

  s4 = s1 + b2;
  unitest((SIZEOF(s4) == 6).is_true() &&
    VALUE_IN(s4, REAL(1.0)).is_true() &&
    VALUE_IN(s4, REAL(2.0)).is_true() &&
    VALUE_IN(s4, REAL(3.0)).is_true() &&
    VALUE_IN(s4, REAL(4.0)).is_true() &&
    VALUE_IN(s4, REAL(5.0)).is_true() &&
    VALUE_IN(s4, REAL(6.0)).is_true(),
    details, "SET = SET + BAG", err);

  s4 = s1 + l2;
  unitest((SIZEOF(s4) == 6).is_true() &&
    VALUE_IN(s4, REAL(1.0)).is_true() &&
    VALUE_IN(s4, REAL(2.0)).is_true() &&
    VALUE_IN(s4, REAL(3.0)).is_true() &&
    VALUE_IN(s4, REAL(4.0)).is_true() &&
    VALUE_IN(s4, REAL(5.0)).is_true() &&
    VALUE_IN(s4, REAL(6.0)).is_true(),
    details, "SET = SET + LIST", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_bag_union(bool details) {
  print_title(details, "BAG UNION");
  test_t err = test_t::TEST_OK;

  BAG<REAL> b1(0,3), b2(1,4), b3, b4;
  b1 = {1,2,INTEGER(3)};
  b2 = {4,5,6};
  SET<REAL> s2(1,4);
  s2 = {4,5,6};
  LIST<REAL> l2(1,4);
  l2 = {4,5,6};

  b3 = b3 + b4;
  unitest(EXISTS(b3).is_false(),
    details, "BAG = ? + ?", err);

  b3 = b4 + b1;
  unitest(EXISTS(b3).is_false(),
    details, "BAG = ? + BAG", err);

  b3 = b1 + b4;
  unitest(EXISTS(b3).is_false(),
    details, "BAG = BAG + ?", err);

  b4 = b1 + b2;
  unitest((SIZEOF(b4) == 6).is_true() &&
    VALUE_IN(b4, REAL(1.0)).is_true() &&
    VALUE_IN(b4, REAL(2.0)).is_true() &&
    VALUE_IN(b4, REAL(3.0)).is_true() &&
    VALUE_IN(b4, REAL(4.0)).is_true() &&
    VALUE_IN(b4, REAL(5.0)).is_true() &&
    VALUE_IN(b4, REAL(6.0)).is_true(),
    details, "BAG = BAG + BAG", err);

  b4 = b1 + REAL(4.0);
  unitest((SIZEOF(b4) == 4).is_true() &&
    VALUE_IN(b4, REAL(1.0)).is_true() &&
    VALUE_IN(b4, REAL(2.0)).is_true() &&
    VALUE_IN(b4, REAL(3.0)).is_true() &&
    VALUE_IN(b4, REAL(4.0)).is_true(),
    details, "BAG = BAG + Element", err);

  b4 = REAL(0.0) + b1;
  unitest((SIZEOF(b4) == 4).is_true() &&
    VALUE_IN(b4, REAL(0.0)).is_true() &&
    VALUE_IN(b4, REAL(1.0)).is_true() &&
    VALUE_IN(b4, REAL(2.0)).is_true() &&
    VALUE_IN(b4, REAL(3.0)).is_true(),
          details, "BAG = Element + BAG", err);

  b4 = b1 + s2;
  unitest((SIZEOF(b4) == 6).is_true() &&
    VALUE_IN(b4, REAL(1.0)).is_true() &&
    VALUE_IN(b4, REAL(2.0)).is_true() &&
    VALUE_IN(b4, REAL(3.0)).is_true() &&
    VALUE_IN(b4, REAL(4.0)).is_true() &&
    VALUE_IN(b4, REAL(5.0)).is_true() &&
    VALUE_IN(b4, REAL(6.0)).is_true(),
    details, "BAG = BAG + SET", err);

  b4 = b1 + l2;
  unitest((SIZEOF(b4) == 6).is_true() &&
    VALUE_IN(b4, REAL(1.0)).is_true() &&
    VALUE_IN(b4, REAL(2.0)).is_true() &&
    VALUE_IN(b4, REAL(3.0)).is_true() &&
    VALUE_IN(b4, REAL(4.0)).is_true() &&
    VALUE_IN(b4, REAL(5.0)).is_true() &&
    VALUE_IN(b4, REAL(6.0)).is_true(),
    details, "BAG = BAG + LIST", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_aggr_differ(bool details) {
  print_title(details, "AGGREGATE DIFFERENCE");
  test_t err = test_t::TEST_NOT_IMPL;

  /**
   * \file
   * \todo Добавить тестирование разницы аггрегатов
   */
  print_res(details, "TEST", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_aggr_subset(bool details) {
  print_title(details, "AGGREGATE SUBSET");
  test_t err = test_t::TEST_NOT_IMPL;

  /**
   * \file
   * \todo Добавить тестирование подмножества аггрегатов
   */
  print_res(details, "TEST", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_aggr_superset(bool details) {
  print_title(details, "AGGREGATE SUPERSET");
  test_t err = test_t::TEST_NOT_IMPL;

  /**
   * \file
   * \todo Добавить тестирование надмножества аггрегатов
   */
  print_res(details, "TEST", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_aggr_query(bool details) {
  print_title(details, "AGGREGATE QUERY");
  test_t err = test_t::TEST_NOT_IMPL;

  /**
   * \file
   * \todo Добавить тестирование поиска в аггрегатах
   */
  print_res(details, "TEST", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}
#endif
static bool test_binary_indexing(bool details) {
  print_title(details, "BINARY INDEXING");
  test_t err = test_t::TEST_NOT_IMPL;

  /**
   * \file
   * \todo Добавить тестирование индексации бинарного типа
   */
  print_res(details, "TEST", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_binary_concat(bool details) {
  print_title(details, "BINARY CONCATINATION");
  test_t err = test_t::TEST_NOT_IMPL;

  /**
   * \file
   * \todo Добавить тестирование объединения бинарных типов
   */
  print_res(details, "TEST", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_string_like(bool details) {
  print_title(details, "LIKE");
  test_t err = test_t::TEST_NOT_IMPL;

  /**
   * \file
   * \todo Добавить тестирование функции LIKE
   */
  print_res(details, "TEST", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_string_indexing(bool details) {
  print_title(details, "STRING INDEXING");
  test_t err = test_t::TEST_NOT_IMPL;

  /**
   * \file
   * \todo Добавить тестирование индексации строк
   */
  print_res(details, "TEST", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}

static bool test_string_concat(bool details) {
  print_title(details, "STRING CONCATINATION");
  test_t err = test_t::TEST_NOT_IMPL;

  /**
   * \file
   * \todo Добавить тестирование объединения строк
   */
  print_res(details, "TEST", err);

  print_res(details, "", err);
  return err == test_t::TEST_ERR;
}


/** \brief Проверка операторов отношений простых и агрегированных типов */
static void run_tests_rel(bool details, int& err) {
  print_double("RELATIONAL OPERATORS");
  if (test_number_rel_eq(details))    err++; /* 12.2.1.1 */
  if (test_number_rel_neq(details))   err++; /* 12.2.1.1 */
  if (test_number_rel_bt(details))    err++; /* 12.2.1.1 */
  if (test_number_rel_beq(details))   err++; /* 12.2.1.1 */
  if (test_number_rel_lt(details))    err++; /* 12.2.1.1 */
  if (test_number_rel_leq(details))   err++; /* 12.2.1.1 */

  if (test_real_rel_eq(details))      err++; /* 12.2.1.1 */
  if (test_real_rel_neq(details))     err++; /* 12.2.1.1 */
  if (test_real_rel_bt(details))      err++; /* 12.2.1.1 */
  if (test_real_rel_beq(details))     err++; /* 12.2.1.1 */
  if (test_real_rel_lt(details))      err++; /* 12.2.1.1 */
  if (test_real_rel_leq(details))      err++; /* 12.2.1.1 */

  if (test_integer_rel_eq(details))   err++; /* 12.2.1.1 */
  if (test_integer_rel_neq(details))  err++; /* 12.2.1.1 */
  if (test_integer_rel_bt(details))   err++; /* 12.2.1.1 */
  if (test_integer_rel_beq(details))  err++; /* 12.2.1.1 */
  if (test_integer_rel_lt(details))   err++; /* 12.2.1.1 */
  if (test_integer_rel_leq(details))  err++; /* 12.2.1.1 */

  if (test_binary_rel(details))       err++; /* 12.2.1.2 */

  if (test_logical_rel_eq(details))   err++; /* 12.2.1.3 */
  if (test_logical_rel_neq(details))  err++; /* 12.2.1.3 */
  if (test_logical_rel_bt(details))   err++; /* 12.2.1.3 */
  if (test_logical_rel_beq(details))  err++; /* 12.2.1.3 */
  if (test_logical_rel_lt(details))   err++; /* 12.2.1.3 */
  if (test_logical_rel_leq(details))  err++; /* 12.2.1.3 */

  if (test_boolean_rel(details))      err++; /* 12.2.1.3 */
  if (test_string_rel(details))       err++; /* 12.2.1.4 */
  if (test_aggr_rel(details))         err++; /* 12.2.1.6, 12.2.2.1 */
} 

/** \brief Проверка инициализации и присвоений простых типов */
static void run_tests_simple_init(bool details, int& err) {
  print_double("SIMPLE TYPES INIT");
  if (test_number_init(details))      err++;
  if (test_real_init(details))        err++;
  if (test_integer_init(details))     err++;
  if (test_logical_init(details))     err++;
  if (test_boolean_init(details))     err++;
  if (test_string_init(details))      err++;
  if (test_binary_init(details))      err++;
}

/** \brief Проверка инициализации и присвоений агрегированных типов */
static void run_tests_aggr_init(bool details, int& err) {
  print_double("AGGREGATE TYPES INIT");
  if (test_array_init(details))       err++; /* 12.9 */
//  if (test_list_init(details))        err++; /* 12.9 */
//  if (test_bag_init(details))         err++; /* 12.9 */
//  if (test_set_init(details))         err++; /* 12.9 */
}

/** \brief Проверка арифметических операторов NUMBER/REAL/INTEGER */
static void run_tests_arith(bool details, int& err) {
  print_double("ARITHMETIC OPERATORS");
  if (test_number_arith_add(details))     err++; /* 12.1 */
  if (test_number_arith_sub(details))     err++; /* 12.1 */
  if (test_number_arith_mul(details))     err++; /* 12.1 */
  if (test_number_arith_div(details))     err++; /* 12.1 */
  if (test_number_arith_pow(details))     err++; /* 12.1 */
  if (test_number_arith_idiv(details))    err++; /* 12.1 */
  if (test_number_arith_imod(details))    err++; /* 12.1 */

  if (test_real_arith_add(details))       err++; /* 12.1 */
  if (test_real_arith_sub(details))       err++; /* 12.1 */
  if (test_real_arith_mul(details))       err++; /* 12.1 */
  if (test_real_arith_div(details))       err++; /* 12.1 */
  if (test_real_arith_pow(details))       err++; /* 12.1 */
  if (test_real_arith_idiv(details))      err++; /* 12.1 */
  if (test_real_arith_imod(details))      err++; /* 12.1 */

  if (test_integer_arith_add(details))    err++; /* 12.1 */
  if (test_integer_arith_sub(details))    err++; /* 12.1 */
  if (test_integer_arith_mul(details))    err++; /* 12.1 */
  if (test_integer_arith_div(details))    err++; /* 12.1 */
  if (test_integer_arith_pow(details))    err++; /* 12.1 */
  if (test_integer_arith_idiv(details))   err++; /* 12.1 */
  if (test_integer_arith_imod(details))   err++; /* 12.1 */
}

void run_tests(bool details) {
  int err = 0;



#if 1

  /** Проверка инициализации и присвоений простых типов */
  run_tests_simple_init(details, err);
  /** Проверка инициализации и присвоений агрегированных типов */
  run_tests_aggr_init(details, err);

  /** Проверка операторов отношений простых и агрегированных типов */
  run_tests_rel(details, err);

  /** Проверка операторов числовых типов */
  run_tests_arith(details, err);

  /** Проверка операторов бинарного типа */
  print_double("BINARY OPERATORS");
  if (test_binary_indexing(details))  err++; /* 12.3.1 */
  if (test_binary_concat(details))    err++; /* 12.3.2 */

  /** Проверка логических операторов */
  print_double("LOGICAL OPERATORS");
  if (test_not(details))              err++; /* 12.4.1 */
  if (test_and(details))              err++; /* 12.4.2 */
  if (test_or(details))               err++; /* 12.4.3 */
  if (test_xor(details))              err++; /* 12.4.4 */

  /** Проверка операторов строкового типа */
  print_double("STRING OPERATORS");
  if (test_string_like(details))      err++; /* 12.2.5 */
  if (test_string_indexing(details))  err++; /* 12.5.1 */
  if (test_string_concat(details))    err++; /* 12.5.2 */

  /** Проверка операторов агрегированных типов */
  print_double("AGGREGATE OPERATORS");
  if (test_aggr_indexing(details))    err++; /* 12.6.1 */
//  if (test_aggr_intersect(details))   err++; /* 12.6.2 */

//  if (test_list_union(details))       err++; /* 12.6.3 */
//  if (test_bag_union(details))        err++; /* 12.6.3 */
//  if (test_set_union(details))        err++; /* 12.6.3 */


//  if (test_aggr_differ(details))      err++; /* 12.6.4 */
//  if (test_aggr_subset(details))      err++; /* 12.6.5 */
//  if (test_aggr_superset(details))    err++; /* 12.6.6 */
//  if (test_aggr_query(details))       err++; /* 12.6.7 */


  /** Проверка встроенных функций */
  print_double("INTERNAL FUNCTIONS");
  if (test_abs(details))              err++; /* 15.1  */
  if (test_acos(details))             err++; /* 15.2  */
  if (test_asin(details))             err++; /* 15.3  */
  if (test_atan(details))             err++; /* 15.4  */
  if (test_blength(details))          err++; /* 15.5  */
  if (test_cos(details))              err++; /* 15.6  */
  if (test_exists(details))           err++; /* 15.7  */
  if (test_exp(details))              err++; /* 15.8  */
  if (test_format(details))           err++; /* 15.9  */
  if (test_hibound(details))          err++; /* 15.10 */
  if (test_hiindex(details))          err++; /* 15.11 */
  if (test_length(details))           err++; /* 15.12 */
  if (test_lobound(details))          err++; /* 15.13 */
  if (test_log(details))              err++; /* 15.14 */
  if (test_log2(details))             err++; /* 15.15 */
  if (test_log10(details))            err++; /* 15.16 */
  if (test_loindex(details))          err++; /* 15.17 */
  if (test_nvl(details))              err++; /* 15.18 */
  if (test_odd(details))              err++; /* 15.19 */
  if (test_rolesof(details))          err++; /* 15.20 */
  if (test_sin(details))              err++; /* 15.21 */
  if (test_sizeof(details))           err++; /* 15.22 */
  if (test_sqrt(details))             err++; /* 15.23 */
  if (test_tan(details))              err++; /* 15.24 */
  if (test_typeof(details))           err++; /* 15.25 */
  if (test_usedin(details))           err++; /* 15.26 */
  if (test_value(details))            err++; /* 15.27 */
  if (test_value_in(details))         err++; /* 15.28 */

  /** Проверка встроенных процедур */
  print_double("INTERNAL ROUTINES");
//  if (test_insert(details))           err++; /* 16.1  */
//  if (test_remove(details))           err++; /* 16.2  */
#else

  test_t err1 = test_t::TEST_OK;

  ARRAY<INTEGER> Array(15, 18, AGGREGATE_GENERIC::OPTIONAL);
  ARRAY<REAL> ArrayR(1,4);

  /* Инициализация списком инициализации */
  Array = { INTEGER(1), 2, INTEGER(3) };
  unitest((Array[15] == INTEGER(1)).is_true() &&
          (Array[16] == INTEGER(2)).is_true() &&
          (Array[17] == INTEGER(3)).is_true() &&
           EXISTS(Array[18]).is_false(), details, "ARRAY := {...}", err1);

  /* Присвоение уточнением элементов */
  Array[15] = 3;
  Array[16] = 2;
  Array[17] = INTEGER(1);
  unitest((Array[15] == INTEGER(3)).is_true() &&
          (Array[16] == INTEGER(2)).is_true() &&
          (Array[17] == INTEGER(1)).is_true() &&
           EXISTS(Array[18]).is_false(), details, "ARRAY[X] := X", err1);

  Array[18] = 4;

  /* Присвоение массива */
  ArrayR = Array;
  unitest((ArrayR[1] == 3.0).is_true() &&
          (ArrayR[2] == 2.0).is_true() &&
          (ArrayR[3] == 1.0).is_true() &&
          (ArrayR[4] == 4.0).is_true(), details, "ARRAY := ARRAY", err1);

#if 0


  BAG<INTEGER> Bag_indet1(0, 5);
  BAG<INTEGER> Bag_indet2(0, 5);
  BAG<INTEGER> Bag3(0, 4);              Bag3 = { 0,1,2,3 };
  BAG<INTEGER> Bag4(0, 4);              Bag4 = { 0,1,2,3 };
  BAG<INTEGER> Bag5(0, 5);              Bag5 = { 0,1,2,3 };
  BAG<INTEGER> Bag6(0, 4);              Bag6 = { 0,2,1,3 };
  BAG<REAL>    Bag7(0, 4);              Bag7 = { 0,1,2,3 };

  unitest((Bag_indet1 == Bag_indet2).is_unknown(), details, "? = ? -> UNKNOWN", err1);
  unitest((Bag_indet1 == Bag3).is_unknown(), details, "? = Bag -> UNKNOWN", err1);
  unitest((Bag3 == Bag_indet2).is_unknown(), details, "Bag = ? -> UNKNOWN", err1);
  unitest((Bag3 == Bag4).is_true(), details, "BAG<INTEGER>{0,1,2,3} = BAG<INTEGER>{0,1,2,3} -> TRUE", err1);
  unitest((Bag3 == Bag7).is_true(), details, "BAG<INTEGER>{0,1,2,3} = BAG<REAL>{0,1,2,3} -> TRUE", err1);
  unitest((Bag7 == Bag3).is_true(), details, "BAG<REAL>{0,1,2,3} = BAG<INTEGER>{0,1,2,3} -> TRUE", err1);

  unitest((Bag_indet1.is_instance_equal(Bag_indet2)).is_unknown(), details, "? :=: ? -> UNKNOWN", err1);
  unitest((Bag_indet1.is_instance_equal(Bag3)).is_unknown(), details, "? :=: Bag -> UNKNOWN", err1);
  unitest((Bag3.is_instance_equal(Bag_indet2)).is_unknown(), details, "Bag :=: ? -> UNKNOWN", err1);
  unitest((Bag3.is_instance_equal(Bag4)).is_true(), details, "BAG<INTEGER>{0,1,2,3} :=: BAG<INTEGER>{0,1,2,3} -> TRUE", err1);
  unitest((Bag3.is_instance_equal(Bag7)).is_true(), details, "BAG<INTEGER>{0,1,2,3} :=: BAG<REAL>{0,1,2,3} -> TRUE", err1);
  unitest((Bag7.is_instance_equal(Bag3)).is_true(), details, "BAG<REAL>{0,1,2,3} :=: BAG<INTEGER>{0,1,2,3} -> TRUE", err1);


  SET<INTEGER> Set_indet1(0, 5);
  SET<INTEGER> Set_indet2(0, 5);
  SET<INTEGER> Set3(0, 4);              Set3 = { 0,1,2,3 };
  SET<INTEGER> Set4(0, 4);              Set4 = { 0,1,2,3 };
  SET<INTEGER> Set5(0, 5);              Set5 = { 0,1,2,3 };
  SET<INTEGER> Set6(0, 4);              Set6 = { 0,2,1,3 };
  SET<REAL>    Set7(0, 4);              Set7 = { 0,1,2,3 };

  unitest((Set_indet1 == Set_indet2).is_unknown(), details, "? = ? -> UNKNOWN", err1);
  unitest((Set_indet1 == Set3).is_unknown(), details, "? = Set -> UNKNOWN", err1);
  unitest((Set3 == Set_indet2).is_unknown(), details, "Set = ? -> UNKNOWN", err1);
  unitest((Set3 == Set4).is_true(), details, "SET<INTEGER>{0,1,2,3} = SET<INTEGER>{0,1,2,3} -> TRUE", err1);
  unitest((Set3 == Set7).is_true(), details, "SET<INTEGER>{0,1,2,3} = SET<REAL>{0,1,2,3} -> TRUE", err1);
  unitest((Set7 == Set3).is_true(), details, "SET<REAL>{0,1,2,3} = SET<INTEGER>{0,1,2,3} -> TRUE", err1);

  unitest((Set_indet1.is_instance_equal(Set_indet2)).is_unknown(), details, "? :=: ? -> UNKNOWN", err1);
  unitest((Set_indet1.is_instance_equal(Set3)).is_unknown(), details, "? :=: Set -> UNKNOWN", err1);
  unitest((Set3.is_instance_equal(Set_indet2)).is_unknown(), details, "Set :=: ? -> UNKNOWN", err1);
  unitest((Set3.is_instance_equal(Set4)).is_true(), details, "SET<INTEGER>{0,1,2,3} :=: SET<INTEGER>{0,1,2,3} -> TRUE", err1);
  unitest((Set3.is_instance_equal(Set7)).is_true(), details, "SET<INTEGER>{0,1,2,3} :=: SET<REAL>{0,1,2,3} -> TRUE", err1);
  unitest((Set7.is_instance_equal(Set3)).is_true(), details, "SET<REAL>{0,1,2,3} :=: SET<INTEGER>{0,1,2,3} -> TRUE", err1);
#endif



  print_res(details, "", err1);

#endif

//  LOGICAL S1 = TRUE, S2 = UNKNOWN, S3 = FALSE;
//  printf("%s %s %s\n", S1.print_value().c_str(), S2.print_value().c_str(), S3.print_value().c_str());
//  BOOLEAN B1 = TRUE, B2 = FALSE;
//  printf("%s %s\n", B1.print_value().c_str(), B2.print_value().c_str());




  /** Итого */
  print_double(nullptr);
  print_res(true, "All tests", err == 0 ? test_t::TEST_OK : test_t::TEST_ERR);
}

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
