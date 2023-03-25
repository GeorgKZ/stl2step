/**
 * \file
 *
 * \brief Синтаксический сахар с привкусом горького миндаля
 *
 * Возможность использования вместо операторов и ключевых слов, принятых в C++,
 * операторов и ключевых слов языка EXPRESS.
 */


#define SELF               *this
#define LOCAL
#define END_LOCAL
#define IF(a)              if(LOGICAL(a).is_true())
#define ELSE               }else{
#define THEN               {
#define BEGIN              {
#define END                }
#define END_IF             }
#define END_FUNCTION       }
#define SKIP               break;
#define OTHERWISE          default
#define END_CASE           }

/**
 * \brief RETURN (ГОСТ Р ИСО 10303-11-2009, 13.10)
 *
 * Возможность использования вместо оператора return, принятого в C++,
 * применяемого в языке EXPRESS оператора \ref p11_s13_10 "RETURN".
 */
#define RETURN(a) return(a)

/**
 * \brief NOT (ГОСТ Р ИСО 10303-11-2009, 12.4.1)
 *
 * Возможность использования вместо оператора \ref express::LOGICAL::operator!() "LOGICAL::operator!()",
 * принятого в C++, применяемого в языке EXPRESS логического оператора \ref p11_s12_4_1 "NOT".
 */
#define NOT !

/**
 * \brief AND (ГОСТ Р ИСО 10303-11-2009, 12.4.2)
 *
 * Возможность использования вместо оператора \ref express::LOGICAL::operator&&() "LOGICAL::operator&&()",
 * принятого в C++, применяемого в языке EXPRESS логического оператора \ref p11_s12_4_2 "AND".
 */
#define AND &&

/**
 * \brief OR (ГОСТ Р ИСО 10303-11-2009, 12.4.3)
 *
 * Возможность использования вместо оператора \ref express::LOGICAL::operator||() "LOGICAL::operator||()",
 * принятого в C++, применяемого в языке EXPRESS логического оператора \ref p11_s12_4_3 "OR".
 */
#define OR ||

/**
 * \brief XOR (ГОСТ Р ИСО 10303-11-2009, 12.4.4)
 *
 * Возможность использования вместо оператора \ref express::LOGICAL::operator^() "LOGICAL::operator^()",
 * принятого в C++, применяемого в языке EXPRESS логического оператора \ref p11_s12_4_4 "XOR".
 */
#define XOR ^

/**
 * \brief DIV (ГОСТ Р ИСО 10303-11-2009, 12.1)
 *
 * Возможность использования вместо оператора '>>',
 * принятого в C++, применяемого в языке EXPRESS арифметического оператора \ref p11_s12_4_4 "DIV".
 */
#define DIV >>

/**
 * \brief MOD (ГОСТ Р ИСО 10303-11-2009, 12.1)
 *
 * Возможность использования вместо оператора '%',
 * принятого в C++, применяемого в языке EXPRESS арифметического оператора \ref p11_s12_4_4 "MOD".
 */
#define MOD %

/**
 * \brief POW (ГОСТ Р ИСО 10303-11-2009, 12.1)
 *
 * Возможность использования вместо оператора '<<',
 * принятого в C++, оператора POW (применяемый в языке EXPRESS арифметический оператор
 * \ref p11_s12_4_4 "**" использовать не получится).
 */
#define POW <<
