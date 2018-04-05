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
void add(list *L,node *n);
node *builtins(char *op,list *args);
list *new_list();
node *new_node(bool atom,void *data);
typedef struct environment environment;
typedef struct hash_table hash_table;
struct environment {                                                    
  struct environment* outer; // NULL for global env                             
  struct hash_table* table;                                                     
};
typedef struct environment env;
void define(char *sym,node *val,env *E);
bool truth(node *n);
node *call(node *func,list *passed_args,env *E);
list *cdr(list *L);
list *evaluate(list *exps,env *E);
node *car(list *L);
node *lookup(char *sym,env *E);
long p_strtol(char *str,char **end);
enum Returntype {DISPLAYED = 0x1};
typedef enum Returntype Returntype;
node *eval(node *exp,env *E);
node *eval(node *exp,env *E);
typedef struct table_entry table_entry;
struct table_entry {
  char* key;
  void* data;
};
typedef struct table_entry entry;
struct hash_table {
  int size;
  entry** table;
};
