#ifndef _STRPTIME_INC
#define _STRPTIME_INC

#include <stdio.h>
#include <time.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

  static char hash_table[] = {0, 0, 0, 0, 0, 0, 0, 34, 0, 0, 0, 0, 33, 0, 0, 0, 0, 0, 32, 0,
                              0, 0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 35, 0, 0, 0, 0,
                              0, 55, 0, 0, 36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 22, 0, 0, 0};

  enum TmSymbol
  {
    Y = 0x45,
    m = 0x24,
    d = 0x23,
    H = 0x22,
    M = 0x21,
    S = 0x20,
    w = 0x16,
    j = 0x37,
  };

  errno_t _cdecl strptime(struct tm *st, char *str, char *format);
  errno_t _cdecl wstrptime(struct tm *st, wchar_t *str, wchar_t *format);

#ifdef __cplusplus
}
#endif

#endif