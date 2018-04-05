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
enum Returntype {DISPLAYED = 0x1};
typedef enum Returntype Returntype;
void s_print(node *sexp);
