#include "../include/strptime.h"

void _init_hash_table()
{
  hash_table['Y' - 65] = Y;
  hash_table['m' - 65] = m;
  hash_table['d' - 65] = d;
  hash_table['H' - 65] = H;
  hash_table['M' - 65] = M;
  hash_table['S' - 65] = S;
  hash_table['w' - 65] = w;
  hash_table['j' - 65] = j;
}

errno_t strptime(struct tm *st, char *str, char *format)
{
  int *tmp_st = (int *)st;
  char *last = format + strlen(format);
  char *tmp_str = str;
  char *tmp_format = format;
  char *r = strchr(tmp_format, '%');
  char mask;
  int c, length;
  char f[] = "%2d";
  while (r)
  {
    if (r + 1 == last)
      break;
    tmp_str += r - tmp_format;
    mask = hash_table[r[1] - 65];
    if (mask & 0xff)
    {
      length = mask >> 4;
      f[1] = length + 48;
      if (!sscanf(tmp_str, f, &c))
        return 0;
      tmp_st[mask & 15] = c;
      tmp_str += length;
    }
    else
      tmp_str += 2;
    tmp_format = r + 2;
    r = strchr(tmp_format, '%');
  }
  tmp_st[Y & 15] -= 1900;
  tmp_st[m & 15] -= 1;
  return 1;
}

errno_t wstrptime(struct tm *st, wchar_t *str, wchar_t *format)
{
  int *tmp_st = (int *)st;
  wchar_t *last = format + wcslen(format);
  wchar_t *tmp_str = str;
  wchar_t *tmp_format = format;
  wchar_t *r = wcschr(tmp_format, '%');
  char mask;
  int c, length;
  wchar_t f[] = L"%2d";
  while (r)
  {
    if (r + 1 == last)
      break;
    tmp_str += r - tmp_format;
    mask = hash_table[r[1] - 65];
    if (mask & 0xff)
    {
      length = mask >> 4;
      f[1] = length + 48;
      if (!swscanf(tmp_str, f, &c))
        return 0;
      tmp_st[mask & 15] = c;
      tmp_str += length;
    }
    else
      tmp_str += 2;
    tmp_format = r + 2;
    r = wcschr(tmp_format, '%');
  }
  tmp_st[Y & 15] -= 1900;
  tmp_st[m & 15] -= 1;
  return 1;
}