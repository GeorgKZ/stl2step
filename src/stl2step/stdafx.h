/**
 * \file
 *
 * \brief Стандартный заголовочный файл для Visual Studio
 *
 * Включаемый файл для стандартных системных включаемых файлов
 * или включаемых файлов для конкретного проекта, которые часто
 * используются, но не часто изменяются.
 */

#ifndef _STDAFX_H
#define _STDAFX_H

#include "targetver.h"

#include <stdio.h>
#include <iomanip>

#if defined(_MSC_VER)
# include <conio.h>
# include <io.h>
#pragma warning( push )
#pragma warning( disable : 5039)

/** Временная правка отсутствия этих определений в заголовочных файлах VisualStudio */
#ifndef MICROSOFT_WINDOWS_WINBASE_H_DEFINE_INTERLOCKED_CPLUSPLUS_OVERLOADS
# define MICROSOFT_WINDOWS_WINBASE_H_DEFINE_INTERLOCKED_CPLUSPLUS_OVERLOADS 0
#endif
#ifndef _WIN32_WINNT_WIN10_TH2
# define _WIN32_WINNT_WIN10_TH2 0x0A000001 /* ABRACADABRA_WIN10_TH2 */
#endif
#ifndef _WIN32_WINNT_WIN10_RS1
# define _WIN32_WINNT_WIN10_RS1 0x0A000002 /* ABRACADABRA_WIN10_RS1 */
#endif
#ifndef _WIN32_WINNT_WIN10_RS2
# define _WIN32_WINNT_WIN10_RS2 0x0A000003 /* ABRACADABRA_WIN10_RS2 */
#endif
#ifndef _WIN32_WINNT_WIN10_RS3
# define _WIN32_WINNT_WIN10_RS3 0x0A000004 /* ABRACADABRA_WIN10_RS3 */
#endif
#ifndef _WIN32_WINNT_WIN10_RS4
# define _WIN32_WINNT_WIN10_RS4 0x0A000005 /* ABRACADABRA_WIN10_RS4 */
#endif
#ifndef _WIN32_WINNT_WIN10_RS5
# define _WIN32_WINNT_WIN10_RS5 0x0A000006 /* ABRACADABRA_WIN10_RS5 */
#endif

#include <windows.h>

#pragma warning( pop ) 

#endif

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#if defined(_MSC_VER) || defined(__MINGW32__)
# include <windows.h>
# undef min
# undef max
# undef TRUE
# undef FALSE
#endif

#if defined(_MSC_VER) && defined(_DEBUG)
#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
 //  #define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

#include <crtdbg.h>
#include <errno.h>

#endif



// Дополнительные заголовки, требующиеся для программы
#if defined(__GNUC__) || defined(__DOXYGEN__)
# include <inttypes.h>
# include <dirent.h>
# if !defined(__MINGW32__)
#   include <fnmatch.h>
# endif
#endif

#include <time.h>

#include <string>
#include <typeinfo>
#include <list>
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <array>

#if defined(_MSC_VER)
typedef unsigned char      uint8_t;
typedef signed char        int8_t;
typedef unsigned short     uint16_t;
typedef signed short       int16_t;
typedef unsigned long long uint64_t;
typedef signed long long   int64_t;
#elif defined(__GNUC__) || defined(__DOXYGEN__)
# ifndef _MAX_PATH
#   define _MAX_PATH 256
# endif
#else
# error Unknown C++ compiler
#endif

#endif // _STDAFX_H
