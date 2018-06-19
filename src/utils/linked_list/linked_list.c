#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

/* Allocate memory for new node */
List_Node *allocate_new_node() {
  List_Node *node = (List_Node *)malloc(sizeof(List_Node));
  node->next = NULL;
  node->data = NULL;
  return node;
}

List_Node *get_new_list() { return allocate_new_node(); }

// note: convestion to (void *) is implicit.
List_Node *append(List_Node *head, void *data, size_t size) {
  if (!head) {  // head is null
    head = allocate_new_node();
  } else {
    while (head->next) {  // iterate to the end of the list
      head = head->next;
    }=
  }
  head->next = allocate_new_node();
  List_Node *new_node = head->next;
  new_node->data = malloc(size);
  memmove(new_node->data, data,
          size);  // copy contents of data to the new_node -> data

  return new_node;
}

void delete_list(List_Node *head) {
  if (head) {
    delete_list(head->next);
    if (head->data) {
      free(head->data);
    }
    free(head);
  }
}

List_Node *get_tail(List_Node *head) {
  if (!head) {  // head is null
    return NULL;
  } else {
    while (head->next) {  // iterate to the end of the list
      head = head->next;
    }
  }
  return head;
}
