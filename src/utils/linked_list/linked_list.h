#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>

typedef struct linked_list_node {
  void *data;
  struct linked_list_node *next;
} List_Node;

/* Returns empty head node that can be used as list */
List_Node *get_new_list();

/*
 * Arguments:
 * head = head of the list we want to insert to
 * data = data we want to insert to new node
 * size = size of the data we are inserting
 * Append new node to the list given by head.
 * Will reach the end if given list, create new node there and insert data into
 * that node. return new tail of the list
 */
List_Node *append(List_Node *head, void *data, size_t size);

void delete_node(List_Node *head, void *data);

/*
 * safely deletes whole list starting from head
 * WARNING: should be only used on head obtained by get_new_list()
 */
void delete_list(List_Node *head);

/*
 * Iterates until the end of the list and returns pointer to the last node of
 * the list
 */
List_Node *get_tail(List_Node *head);

#endif
