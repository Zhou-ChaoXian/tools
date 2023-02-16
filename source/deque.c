#include "../include/deque.h"

DequePtr deque_make()
{
  DequePtr deque = (DequePtr)malloc(sizeof(Deque));
  DequeItemPtr *table = (DequeItemPtr *)calloc(deque_default_count, sizeof(DequeItemPtr));
  deque->table = table;
  deque->count = 0;
  deque->alloc_count = deque_default_count;
  deque->first_index = 0;
  deque->last_index = 0;
}

void deque_change_default_count(size_t count)
{
  deque_default_count = count;
}

static void _deque_check_alloc(DequePtr deque)
{
  if (deque->count + 1 > deque->alloc_count)
  {
    size_t new_alloc_count = deque->alloc_count + deque_default_count;
    DequeItemPtr *new_table = (DequeItemPtr *)realloc(deque->table, new_alloc_count);
    if (deque->first_index > 0)
    {
      size_t dis = deque->alloc_count - deque->first_index;
      size_t s1 = new_alloc_count - 1;
      size_t s2 = deque->alloc_count - 1;
      for (int i = 0; i < dis; ++i)
      {
        new_table[s1--] = deque->table[s2];
        deque->table[s2] = NULL;
        --s2;
      }
      deque->table = new_table;
      deque->alloc_count = new_alloc_count;
      deque->first_index = s1 + 1;
    }
  }
}

void deque_push_right(DequePtr deque, DequeItemPtr item)
{
  _deque_check_alloc(deque);
  deque->table[deque->last_index++] = item;
  ++deque->count;
  if (deque->last_index == deque->alloc_count)
    deque->last_index = 0;
}

void deque_push_left(DequePtr deque, DequeItemPtr item)
{
  _deque_check_alloc(deque);
  if (deque->first_index == 0)
    deque->first_index = deque->alloc_count - 1;
  else
    --deque->first_index;
  deque->table[deque->first_index] = item;
  ++deque->count;
}

DequeItemPtr deque_pop_right(DequePtr deque)
{
  if (deque->count == 0)
    return NULL;
  if (deque->last_index == 0)
    deque->last_index = deque->alloc_count - 1;
  else
    --deque->last_index;
  DequeItemPtr item = deque->table[deque->last_index];
  deque->table[deque->last_index] = NULL;
  --deque->count;
  return item;
}

DequeItemPtr deque_pop_left(DequePtr deque)
{
  if (deque->count == 0)
    return NULL;
  DequeItemPtr item = deque->table[deque->first_index];
  deque->table[deque->first_index] = NULL;
  --deque->count;
  if (++deque->first_index == deque->alloc_count)
    deque->first_index = 0;
  return item;
}

DequeItemPtr deque_index(DequePtr deque, size_t index)
{
  if (index >= deque->alloc_count)
    return NULL;
  index += deque->first_index;
  if (index >= deque->alloc_count)
    index -= deque->alloc_count;
  return deque->table[index];
}

void deque_free(DequePtr deque)
{
  free(deque->table);
  deque->table = NULL;
  free(deque);
}