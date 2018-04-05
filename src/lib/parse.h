/* This file was automatically generated.  Do not edit! */
#include <stdbool.h>
typedef struct list_node list_node;
struct list_node {
  bool atom;
  void* data;
  struct list_node* next;
};
typedef struct list_node node;
node *new_node(bool atom,void *data);
typedef struct linked_list linked_list;
struct linked_list {
  node* start;
  node* end;
};
typedef struct linked_list list;
void add(list *L,node *n);
list *new_list();
node *parse_atom(char *tok);
node *parse_quote(FILE *src);
node *parse_list(FILE *src);
node *parse_exp(FILE *src);
char *next_token(FILE *src);
bool sym_end(int c);
extern const int MAX_SYMBOL_LENGTH;
extern const int MAX_SYMBOL_LENGTH;
