/* This file was automatically generated.  Do not edit! */
#include <stdbool.h>
enum Returntype {DISPLAYED = 0x1};
typedef enum Returntype Returntype;
typedef struct list_node list_node;
struct list_node {
  bool atom;
  void* data;
  struct list_node* next;
};
typedef struct list_node node;
void s_print(node *sexp);
typedef struct linked_list linked_list;
struct linked_list {
  node* start;
  node* end;
};
typedef struct linked_list list;
bool ls_compare(list *L1,list *L2);
void insert(list *L,node *n);
list *new_list();
list *cdr(list *L);
node *car(list *L);
bool truth(node *n);
node *new_node(bool atom,void *data);
long p_strtol(char *str,char **end);
char *ltoa(long num);
node *display(list *args);
node *lequ(list *args);
node *blist(list *args);
node *cons(list *args);
node *bcdr(list *args);
node *bcar(list *args);
node *equ(list *args);
node *lth(list *args);
node *gth(list *args);
node *divi(list *args);
node *sub(list *args);
node *mul(list *args);
node *plus(list *args);
node *builtins(char *op,list *args);
extern const int MAX_DIGITS;
