/**
 * @file base.h
 * @author 白云城主叶孤城
 * @brief 列表，字符串，宽字符串
 * @version 0.1
 * @date 2000-01-01
 * 
 * @copyright Copyright (c) 2000
 * 
 * 自动申请空间
 */

#ifndef _BASE_INC
#define _BASE_INC

#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

  typedef void *PtrListItem;

  /**
   * @brief 列表
   *
   */
  typedef struct List
  {
    PtrListItem *start;
    size_t len;
    size_t alloc_count;
  } List, *PtrList;

#define DEFAULT_ALLOC_COUNT 10
#define convert_list_index(list, index, type) ((type)list->start[index])
#define convert_list_item(item, type) ((type)item)

  PtrList _cdecl make_list();
  PtrList _cdecl make_list_n(size_t n, ...);
  PtrList _cdecl make_list_s(PtrList list);
  void _cdecl push_list(PtrList list, void *src);
  errno_t _cdecl push_list_index(PtrList list, void *src, size_t index);
  PtrListItem _cdecl pop_list(PtrList list);
  PtrListItem _cdecl pop_list_index(PtrList list, size_t index);
  void _cdecl free_list(PtrList list);

  /**
   * @brief 字符串
   *
   */
  typedef struct String
  {
    char *str;
    size_t len;
  } String, *PtrString;

#define string_len(s) (s->len)
#define string_to_str(s) (s->str)

  PtrString _cdecl make_string_n(char *src, long long n);
  PtrString _cdecl make_string(char *src);
  PtrString _cdecl make_string_s(PtrString s);
  void _cdecl append_string_n(PtrString s, char *src, long long n);
  void _cdecl append_string(PtrString s, char *src);
  void _cdecl append_string_s(PtrString s, PtrString src);
  void _cdecl free_string(PtrString s);
  PtrList _cdecl split_string_n(PtrString s, char *delimt, long long n);
  PtrList _cdecl split_string(PtrString s, char *delimt);
  PtrList _cdecl split_str_n(char *src, char *delimt, long long n);
  PtrList _cdecl split_str(char *src, char *delimt);
  PtrString _cdecl slice_string_n(PtrString s, size_t index, long long n);
  PtrString _cdecl slice_string(PtrString s, size_t index);
  PtrString _cdecl slice_str_n(char *src, size_t index, long long n);
  PtrString _cdecl slice_str(char *src, size_t index);

  /**
   * @brief 中文字符串
   *
   */
  typedef struct WString
  {
    wchar_t *str;
    size_t len;
  } WString, *PtrWString;

#define wstring_len(ws) (ws->len)
#define wstring_to_str(ws) (ws->str)

  PtrWString _cdecl make_wstring_n(wchar_t *src, long long n);
  PtrWString _cdecl make_wstring(wchar_t *src);
  PtrWString _cdecl make_wstring_s(PtrWString ws);
  void _cdecl append_wstring_n(PtrWString ws, wchar_t *src, long long n);
  void _cdecl append_wstring(PtrWString ws, wchar_t *src);
  void _cdecl append_wstring_s(PtrWString ws, PtrWString src);
  void _cdecl free_wstring(PtrWString ws);
  PtrList _cdecl split_wstring_n(PtrWString ws, wchar_t *delimt, long long n);
  PtrList _cdecl split_wstring(PtrWString ws, wchar_t *delimt);
  PtrList _cdecl split_wstr_n(wchar_t *src, wchar_t *delimt, long long n);
  PtrList _cdecl split_wstr(wchar_t *src, wchar_t *delimt);
  PtrWString slice_wstring_n(PtrWString ws, size_t index, long long n);
  PtrWString _cdecl slice_wstring(PtrWString ws, size_t index);
  PtrWString _cdecl slice_wstr_n(wchar_t *src, size_t index, long long n);
  PtrWString _cdecl slice_wstr(wchar_t *src, size_t index);

#ifdef __cplusplus
}
#endif

#endif