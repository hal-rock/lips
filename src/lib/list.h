/* This file was automatically generated.  Do not edit! */
#include <stdbool.h>
typedef struct linked_list linked_list;
typedef struct list_node list_node;
struct list_node {
  bool atom;
  void* data;
  struct list_node* next;
};
typedef struct list_node node;
struct linked_list {
  node* start;
  node* end;
};
typedef struct linked_list list;
void ls_destroy(list *L);
bool ls_compare(list *L1,list *L2);
void nd_destroy(node *n);
list *ls_copy(list *L);
list *cdr(list *L);
node *nd_copy(node *n);
node *car(list *L);
void add(list *L,node *n);
void insert(list *L,node *n);
list *new_list();
node *new_node(bool atom,void *data);
extern const int MAX_SYMBOL_LENGTH;
extern const int MAX_SYMBOL_LENGTH;
