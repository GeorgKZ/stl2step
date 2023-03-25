/**
 * \file
 * \brief Файл, включающий все необходимые заголовочные файлы для реализации языка Express.
 */

#ifndef _EXPRESS_H
#define _EXPRESS_H

#ifdef __DOXYGEN__
#include "express_doc.h"
#endif

#include "err.h"
#include "express_typelist.h"

namespace express {
  /** \brief Разделитель при выводе атрибутов объекта */
  constexpr auto STEP_SPACER = ",";
}

#include "express_generic.h"
#include "express_entity.h"
#include "express_select.h"
#include "express_enumeration.h"
#include "express_simple.h"
#include "express_simple_number.h"
#include "express_simple_real.h"
#include "express_simple_integer.h"
#include "express_simple_logical.h"
#include "express_simple_boolean.h"
#include "express_simple_string.h"
#include "express_simple_binary.h"
#include "express_constants.h"
#include "express_aggregate.h"
#include "express_aggregate_array.h"
//#include "express_aggregate_list.h"
//#include "express_aggregate_bag.h"
//#include "express_aggregate_set.h"
//#include "express_aggregate_bag_and_set.h"
#include "express_functions.h"

#ifndef TESTONLY

#define  ISO130303_41_FIRST
#include "iso10303_41.h"
#undef   ISO130303_41_FIRST
#define  ISO130303_43_FIRST
#include "iso10303_43.h"
#undef   ISO130303_43_FIRST
#include "iso10303_41.h"
#include "iso10303_43.h"
#include "iso10303_46.h"
#include "iso10303_42.h"
#include "iso10303_44.h"
#include "iso10303_511.h"
#include "iso10303_514.h"
#include "iso10303_517.h"

#endif /* TESTONLY */

#endif /* _EXPRESS_H */
