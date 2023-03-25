/**
 * \file
 *
 * \brief Файл с некоторыми функциями, использующими API Windows.
 */


#if defined(_MSC_VER)

#pragma warning( push )
#pragma warning( disable : 5039)

/* temporary fix */
#define MICROSOFT_WINDOWS_WINBASE_H_DEFINE_INTERLOCKED_CPLUSPLUS_OVERLOADS 0
#define _WIN32_WINNT_WIN10_TH2 0x0A000001 /* ABRACADABRA_WIN10_TH2 */
#define _WIN32_WINNT_WIN10_RS1 0x0A000002 /* ABRACADABRA_WIN10_RS1 */
#define _WIN32_WINNT_WIN10_RS2 0x0A000003 /* ABRACADABRA_WIN10_RS2 */
#define _WIN32_WINNT_WIN10_RS3 0x0A000004 /* ABRACADABRA_WIN10_RS3 */
#define _WIN32_WINNT_WIN10_RS4 0x0A000005 /* ABRACADABRA_WIN10_RS4 */
#define _WIN32_WINNT_WIN10_RS5 0x0A000006 /* ABRACADABRA_WIN10_RS5 */

#include <windows.h>
#include "stdafx.h"

#pragma warning( pop ) 


uint64_t get_sys_time() {
  SYSTEMTIME systime;
  FILETIME filetime;

  GetSystemTime(&systime);
  if (!SystemTimeToFileTime(&systime, &filetime)) {
    return 0;
  }

  union {
    uint64_t qword;
    struct {
      uint32_t low;
      uint32_t high;
    } dword;
  } ns_since_1601 = { 0 };

  // copy the result into the ULARGE_INTEGER; this is actually
  // copying the result into the ns_since_1601 int64_t.
  ns_since_1601.dword.low = filetime.dwLowDateTime;
  ns_since_1601.dword.high = filetime.dwHighDateTime;

  // Compute the number of milliseconds since 1601; we have to
  // divide by 10,000, since the current value is the number of 100ns
  // intervals since 1601, not ms.
  return (ns_since_1601.qword / 10000);
}

unsigned short set_color(int color) {
  WORD old = 0;
  HANDLE consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO Info;
  if (consoleOutput != INVALID_HANDLE_VALUE) {
    GetConsoleScreenBufferInfo(consoleOutput, &Info);
    old = Info.wAttributes;
    SetConsoleTextAttribute(consoleOutput, ((color == 31 || color == 33) ? FOREGROUND_RED : 0) | ((color == 32 || color == 33) ? FOREGROUND_GREEN : 0U));
  }
  return old;
}

void restore_color(unsigned short attr) {
  HANDLE consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(consoleOutput, attr);
}

#endif
