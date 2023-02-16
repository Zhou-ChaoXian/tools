#include "../include/node.h"

PtrNode make_node()
{
  PtrNode node = (PtrNode)malloc(sizeof(Node));
  node->first = NULL;
  node->last = NULL;
  node->count = 0;
  return node;
}

PtrNodeItem make_node_item(NodeItemDetail detail)
{
  PtrNodeItem item = (PtrNodeItem)malloc(sizeof(NodeItem));
  item->detail = detail;
  item->before = NULL;
  item->after = NULL;
  return item;
}

void push_item_last(PtrNode node, PtrNodeItem item)
{
  if (node->count == 0)
  {
    NODE_NULL;
  }
  else
  {
    node->last->after = item;
    item->before = node->last;
    node->last = item;
  }
  ++node->count;
}

void push_item_first(PtrNode node, PtrNodeItem item)
{
  if (node->count == 0)
  {
    NODE_NULL;
  }
  else
  {
    node->first->before = item;
    item->after = node->first;
    node->first = item;
  }
  ++node->count;
}

PtrNodeItem pop_item_last(PtrNode node)
{
  if (node->count == 0)
    return NULL;
  PtrNodeItem last = node->last;
  node->last = last->before;
  --node->count;
  return last;
}

PtrNodeItem pop_item_first(PtrNode node)
{
  if (node->count == 0)
    return NULL;
  PtrNodeItem first = node->first;
  node->first = first->after;
  --node->count;
  return first;
}

errno_t check_item(PtrNode node, PtrNodeItem item)
{
  PtrNodeItem tmp = node->first;
  int index = 0;
  while (index < node->count)
  {
    if (item == tmp)
      return 1;
    tmp = tmp->after;
  }
  return 0;
}

errno_t insert_item_after(PtrNode node, PtrNodeItem dst, PtrNodeItem item)
{
  if (check_item(node, dst))
  {
    if (dst->after == NULL)
    {
      dst->after = item;
      item->before = dst;
      node->last = item;
    }
    else
    {
      item->before = dst;
      item->after = dst->after;
      dst->after->before = item;
      dst->after = item;
    }
    ++node->count;
    return 1;
  }
  return 0;
}

errno_t insert_item_before(PtrNode node, PtrNodeItem dst, PtrNodeItem item)
{
  if (check_item(node, dst))
  {
    if (dst->before == NULL)
    {
      item->after = dst;
      dst->before = item;
      node->first = item;
    }
    else
    {
      item->after = dst;
      item->before = dst->before;
      dst->before->after = item;
      dst->before = item;
    }
    ++node->count;
    return 1;
  }
  return 0;
}

PtrNodeItem pop_item_after(PtrNode node, PtrNodeItem dst)
{
  if (check_item(node, dst))
  {
    if (dst->after == NULL)
      return NULL;
    PtrNodeItem tmp = dst->after;
    if (tmp->after == NULL)
    {
      dst->after = NULL;
      node->last = dst;
    }
    else
    {
      dst->after = tmp->after;
      tmp->after->before = dst;
    }
    --node->count;
    return tmp;
  }
  return NULL;
}

PtrNodeItem pop_item_before(PtrNode node, PtrNodeItem dst)
{
  if (check_item(node, dst))
  {
    if (dst->before == NULL)
      return NULL;
    PtrNodeItem tmp = dst->before;
    if (tmp->before == NULL)
    {
      dst->before = NULL;
      node->first = dst;
    }
    else
    {
      tmp->before->after = dst;
      dst->before = tmp->before;
    }
    --node->count;
    return tmp;
  }
  return NULL;
}

void free_node(PtrNode node)
{
  PtrNodeItem first = node->first;
  PtrNodeItem tmp;
  while (first)
  {
    tmp = first->after;
    free(first);
    first = tmp;
  }
  free(node);
}

void free_node_with_item_detail(PtrNode node, void (*free_item_detail)(NodeItemDetail))
{
  PtrNodeItem first = node->first;
  PtrNodeItem tmp;
  while (first)
  {
    tmp = first->after;
    free_item_detail(first->detail);
    free(first);
    first = tmp;
  }
  free(node);
}