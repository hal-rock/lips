/* This file was automatically generated.  Do not edit! */
#include <stdbool.h>
typedef struct environment environment;
typedef struct hash_table hash_table;
struct environment {                                                    
  struct environment* outer; // NULL for global env                             
  struct hash_table* table;                                                     
};
typedef struct environment env;
void env_destroy(env *E);
typedef struct list_node list_node;
struct list_node {
  bool atom;
  void* data;
  struct list_node* next;
};
typedef struct list_node node;
void define(char *sym,node *val,env *E);
env *new_env(int size,env *outer);
typedef struct linked_list linked_list;
struct linked_list {
  node* start;
  node* end;
};
typedef struct linked_list list;
list *cdr(list *L);
node *car(list *L);
node *call(node *func,list *passed_args,env *E);
extern const int ENV_SIZE;
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
