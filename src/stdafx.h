/**
 * \file
 *
 * \brief Стандартный заголовочный файл для Visual Studio
 *
 * Включаемый файл для стандартных системных включаемых файлов
 * или включаемых файлов для конкретного проекта, которые часто
 * используются, но не часто изменяются.
 */

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <stdint.h>
#include <filesystem>
#include <stdexcept>
#include <any>
#include <variant>
#include <functional>
#include <optional>
#include <string>
#include <typeinfo>
#include <list>
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <array>
#include <cstdint>
#include <string_view>

#if defined(_MSC_VER)
#  define WIN32_LEAN_AND_MEAN
#  include <conio.h>
#  include <io.h>
#  define __MYFUNCNAME__ __FUNCSIG__
#  if defined(_DEBUG)
#    define __CRTDBG_MAP_ALLOC
#    include <crtdbg.h>
#    define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
#    define new DEBUG_NEW
#    include <crtdbg.h>
#    include <errno.h>
#  endif
#  pragma warning( disable : 4820) // 'bytes' bytes padding added after construct 'member_name'
#  pragma warning( disable : 4514) // 'function' : unreferenced inline function has been removed
#  pragma warning( disable : 5045) // Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
#elif defined(__GNUC__) || defined(__DOXYGEN__)
#  include <inttypes.h>
#  include <dirent.h>
#  include <fnmatch.h>
#  include <cxxabi.h>
#  define _MAX_PATH 256
#  define __MYFUNCNAME__ __PRETTY_FUNCTION__
#elif
#  error Unknown C++ compiler
#endif

void run_tests(bool);
