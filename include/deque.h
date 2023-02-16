/**
 * @file deque.h
 * @author 白云城主叶孤城
 * @brief 双端队列
 * @version 0.1
 * @date 2000-01-01
 * 
 * @copyright Copyright (c) 2000
 * 
 * 双端队列及一些操作
 */

#ifndef _DEQUE_INC
#define _DEQUE_INC

#include <stdlib.h>

#ifdef _cplusplus
extern "C"
{
#endif

  typedef void *DequeItemPtr;

  typedef struct Deque
  {
    DequeItemPtr *table;
    size_t count;
    size_t alloc_count;
    size_t first_index;
    size_t last_index;
  } Deque, *DequePtr;

  static size_t deque_default_count = 64;

  DequePtr _cdecl deque_make();
  void _cdecl deque_change_default_count(size_t count);
  static void _cdecl _deque_check_alloc(DequePtr deque);
  void _cdecl deque_push_right(DequePtr deque, DequeItemPtr item);
  void _cdecl deque_push_left(DequePtr deque, DequeItemPtr item);
  DequeItemPtr _cdecl deque_pop_right(DequePtr deque);
  DequeItemPtr _cdecl deque_pop_left(DequePtr deque);
  DequeItemPtr _cdecl deque_index(DequePtr deque, size_t index);
  void _cdecl deque_free(DequePtr deque);

#ifdef _cplusplus
}
#endif

#endif