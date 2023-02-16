/**
 * @file node.h
 * @author 白云城主叶孤城
 * @brief 双向链表
 * @version 0.1
 * @date 2000-01-01
 * 
 * @copyright Copyright (c) 2000
 * 
 * 双向链表以及一些操作
 */

#ifndef _NODE_INC
#define _NODE_INC

#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define convert_item_detail(item, type) ((type *)item->detail)
#define NODE_NULL     \
  node->first = item; \
  node->last = item;

  typedef void *NodeItemDetail;
  typedef struct NodeItem NodeItem, *PtrNodeItem;

  /**
   * @brief 节点
   *
   */
  struct NodeItem
  {
    NodeItemDetail detail;
    PtrNodeItem before;
    PtrNodeItem after;
  };

  /**
   * @brief 双向链表
   *
   */
  typedef struct Node
  {
    PtrNodeItem first;
    PtrNodeItem last;
    size_t count;
  } Node, *PtrNode;

  PtrNode _cdecl make_node();
  PtrNodeItem _cdecl make_node_item(NodeItemDetail detail);
  void _cdecl push_item_last(PtrNode node, PtrNodeItem item);
  void _cdecl push_item_first(PtrNode node, PtrNodeItem item);
  PtrNodeItem _cdecl pop_item_last(PtrNode node);
  PtrNodeItem _cdecl pop_item_first(PtrNode node);
  errno_t _cdecl check_item(PtrNode node, PtrNodeItem item);
  errno_t _cdecl insert_item_after(PtrNode node, PtrNodeItem dst, PtrNodeItem item);
  errno_t _cdecl insert_item_before(PtrNode node, PtrNodeItem dst, PtrNodeItem item);
  PtrNodeItem _cdecl pop_item_after(PtrNode node, PtrNodeItem dst);
  PtrNodeItem _cdecl pop_item_before(PtrNode node, PtrNodeItem dst);
  void _cdecl free_node(PtrNode node);
  void _cdecl free_node_with_item_detail(PtrNode node, void (*free_item_detail)(NodeItemDetail));

#ifdef __cplusplus
}
#endif

#endif