#include "../include/base.h"

PtrString make_string_n(char *src, long long n)
{
  size_t length = n < 0 ? strlen(src) : n;
  char *dst = (char *)malloc(length + 1);
  memcpy(dst, src, length);
  dst[length] = 0;
  PtrString s = (PtrString)malloc(sizeof(String));
  s->str = dst;
  s->len = length;
  return s;
}

PtrString make_string(char *src)
{
  return make_string_n(src, -1);
}

PtrString make_string_s(PtrString s)
{
  return make_string_n(s->str, s->len);
}

void append_string_n(PtrString s, char *src, long long n)
{
  size_t length = n < 0 ? strlen(src) : n;
  s->str = (char *)realloc(s->str, s->len + length + 1);
  memcpy(s->str + s->len, src, length);
  s->len += length;
  s->str[s->len] = 0;
}

void append_string(PtrString s, char *src)
{
  append_string_n(s, src, -1);
}

void append_string_s(PtrString s, PtrString src)
{
  append_string_n(s, src->str, src->len);
}

void free_string(PtrString s)
{
  free(s->str);
  s->str = NULL;
  free(s);
  s = NULL;
}

PtrList split_string_n(PtrString s, char *delimt, long long n)
{
  char *tmp = s->str;
  PtrList list = make_list();
  if (n == 0)
    goto next;
  size_t delimt_len = strlen(delimt);
  char *result = strstr(tmp, delimt);
  size_t count, _n = 0;
  while (result)
  {
    count = result - tmp;
    push_list(list, make_string_n(tmp, count));
    tmp += count + delimt_len;
    if (n > 0 && ++_n >= n)
      break;
    result = strstr(tmp, delimt);
  }
next:
  if (tmp - s->str < s->len)
    push_list(list, make_string(tmp));
  return list;
}

PtrList split_string(PtrString s, char *delimt)
{
  return split_string_n(s, delimt, -1);
}

PtrList split_str_n(char *src, char *delimt, long long n)
{
  char *tmp = src;
  PtrList list = make_list();
  if (n == 0)
    goto next;
  size_t delimt_len = strlen(delimt);
  char *result = strstr(tmp, delimt);
  size_t count, _n = 0;
  while (result)
  {
    count = result - tmp;
    push_list(list, make_string_n(tmp, count));
    tmp += count + delimt_len;
    if (n > 0 && ++_n >= n)
      break;
    result = strstr(tmp, delimt);
  }
next:
  if (tmp - src < strlen(src))
    push_list(list, make_string(tmp));
  return list;
}

PtrList split_str(char *src, char *delimt)
{
  return split_str_n(src, delimt, -1);
}

PtrString slice_string_n(PtrString s, size_t index, long long n)
{
  if (index >= s->len)
    return make_string("");
  return make_string_n(s->str + index, n);
}

PtrString slice_string(PtrString s, size_t index)
{
  if (index >= s->len)
    return make_string("");
  return make_string(s->str + index);
}

PtrString slice_str_n(char *src, size_t index, long long n)
{
  if (index >= strlen(src))
    return make_string("");
  return make_string_n(src + index, n);
}

PtrString slice_str(char *src, size_t index)
{
  if (index > strlen(src))
    return make_string("");
  return make_string(src + index);
}

PtrWString make_wstring_n(wchar_t *src, long long n)
{
  size_t length = n < 0 ? wcslen(src) : n;
  wchar_t *dst = (wchar_t *)calloc(sizeof(wchar_t), length + 1);
  wcsncpy(dst, src, length);
  dst[length] = 0;
  PtrWString s = (PtrWString)malloc(sizeof(WString));
  s->str = dst;
  s->len = length;
  return s;
}

PtrWString make_wstring(wchar_t *src)
{
  return make_wstring_n(src, -1);
}

PtrWString make_wstring_s(PtrWString ws)
{
  return make_wstring_n(ws->str, ws->len);
}

void append_wstring_n(PtrWString ws, wchar_t *src, long long n)
{
  size_t length = n < 0 ? wcslen(src) : n;
  ws->str = (wchar_t *)realloc(ws->str, ws->len + length + 1);
  wcsncpy(ws->str + ws->len, src, length);
  ws->len += length;
  ws->str[ws->len] = 0;
}

void append_wstring(PtrWString ws, wchar_t *src)
{
  append_wstring_n(ws, src, -1);
}

void append_wstring_s(PtrWString ws, PtrWString src)
{
  append_wstring_n(ws, src->str, src->len);
}

void free_wstring(PtrWString ws)
{
  free(ws->str);
  ws->str = NULL;
  free(ws);
  ws = NULL;
}

PtrList split_wstring_n(PtrWString ws, wchar_t *delimt, long long n)
{
  wchar_t *tmp = ws->str;
  PtrList list = make_list();
  if (n == 0)
    goto next;
  size_t delimt_len = wcslen(delimt);
  wchar_t *result = wcsstr(tmp, delimt);
  size_t count, _n = 0;
  while (result)
  {
    count = result - tmp;
    push_list(list, make_wstring_n(tmp, count));
    tmp += count + delimt_len;
    if (n > 0 && ++_n >= n)
      break;
    result = wcsstr(tmp, delimt);
  }
next:
  if (tmp - ws->str < ws->len)
    push_list(list, make_wstring(tmp));
  return list;
}

PtrList split_wstring(PtrWString ws, wchar_t *delimt)
{
  split_wstring_n(ws, delimt, -1);
}

PtrList split_wstr_n(wchar_t *src, wchar_t *delimt, long long n)
{
  wchar_t *tmp = src;
  PtrList list = make_list();
  if (n == 0)
    goto next;
  size_t delimt_len = wcslen(delimt);
  wchar_t *result = wcsstr(tmp, delimt);
  size_t count, _n = 0;
  while (result)
  {
    count = result - tmp;
    push_list(list, make_wstring_n(tmp, count));
    tmp += count + delimt_len;
    if (n > 0 && ++_n >= n)
      break;
    result = wcsstr(tmp, delimt);
  }
next:
  if (tmp - src < wcslen(src))
    push_list(list, make_wstring(tmp));
  return list;
}

PtrList split_wstr(wchar_t *src, wchar_t *delimt)
{
  return split_wstr_n(src, delimt, -1);
}

PtrWString slice_wstring_n(PtrWString ws, size_t index, long long n)
{
  if (index >= ws->len)
    return make_wstring(L"");
  return make_wstring_n(ws->str + index, n);
}

PtrWString slice_wstring(PtrWString ws, size_t index)
{
  if (index >= ws->len)
    return make_wstring(L"");
  return make_wstring(ws->str + index);
}

PtrWString slice_wstr_n(wchar_t *src, size_t index, long long n)
{
  if (index >= wcslen(src))
    return make_wstring(L"");
  return make_wstring_n(src + index, n);
}

PtrWString slice_wstr(wchar_t *src, size_t index)
{
  if (index >= wcslen(src))
    return make_wstring(L"");
  return make_wstring(src + index);
}

PtrList make_list()
{
  void **c = (void **)calloc(DEFAULT_ALLOC_COUNT, sizeof(void *));
  PtrList list = (PtrList)malloc(sizeof(List));
  list->start = c;
  list->len = 0;
  list->alloc_count = DEFAULT_ALLOC_COUNT;
}

PtrList make_list_n(size_t n, ...)
{
  size_t length = n < DEFAULT_ALLOC_COUNT ? DEFAULT_ALLOC_COUNT : n + DEFAULT_ALLOC_COUNT;
  void **c = (void **)calloc(length, sizeof(void *));
  __builtin_va_list args;
  __builtin_va_start(args, n);
  size_t index = 0;
  void *var;
  while (index < n)
  {
    var = __builtin_va_arg(args, void *);
    c[index++] = var;
  }
  __builtin_va_end(args);
  PtrList list = (PtrList)malloc(sizeof(List));
  list->start = c;
  list->len = index;
  list->alloc_count = length;
  return list;
}

PtrList make_list_s(PtrList list)
{
  void **c = (void **)calloc(list->alloc_count, sizeof(void *));
  size_t index = 0;
  while (index < list->len)
    c[index++] = list->start[index];
  PtrList l = (PtrList)malloc(sizeof(List));
  l->start = c;
  l->len = index;
  l->alloc_count = list->alloc_count;
  return l;
}

void push_list(PtrList list, void *src)
{
  if (list->len + 1 > list->alloc_count)
  {
    size_t c = list->alloc_count / 10;
    if (c < DEFAULT_ALLOC_COUNT)
      c = DEFAULT_ALLOC_COUNT;
    list->alloc_count += c;
    list->start = (void **)realloc(list->start, list->alloc_count);
  }
  list->start[list->len++] = src;
}

errno_t push_list_index(PtrList list, void *src, size_t index)
{
  if (index > list->len)
    return 0;
  push_list(list, src);
  size_t last = list->len - 1;
  size_t c = last - index, _c = 0;
  while (_c < c)
  {
    list->start[last--] = list->start[last - 1];
    ++_c;
  }
  list->start[index] = src;
  return 1;
}

PtrListItem pop_list(PtrList list)
{
  void *tmp = list->start[--list->len];
  list->start[list->len] = 0;
  size_t c;
  if (list->len > 256 || (c = (list->len << 1) + DEFAULT_ALLOC_COUNT) < list->alloc_count)
  {
    list->alloc_count = c;
    list->start = (void **)realloc(list->start, c);
  }
  return tmp;
}

PtrListItem pop_list_index(PtrList list, size_t index)
{
  size_t last = list->len - 1;
  if (index > last)
    return NULL;
  void *tmp = list->start[index];
  size_t c = last - index, _c = 0;
  size_t i = index;
  while (_c < c)
  {
    list->start[i++] = list->start[i + 1];
    ++_c;
  }
  list->start[last] = tmp;
  return pop_list(list);
}

void free_list(PtrList list)
{
  free(list->start);
  list->start = NULL;
  free(list);
  list = NULL;
}