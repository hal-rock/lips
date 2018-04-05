/* This file was automatically generated.  Do not edit! */
#include <stdbool.h>
typedef struct table_entry table_entry;
struct table_entry {
  char* key;
  void* data;
};
typedef struct table_entry entry;
typedef struct hash_table hash_table;
struct hash_table {
  int size;
  entry** table;
};
typedef struct hash_table htab;
bool hoverwrite(entry *new,htab *H);
typedef struct list_node list_node;
struct list_node {
  bool atom;
  void* data;
  struct list_node* next;
};
typedef struct list_node node;
typedef struct environment environment;
struct environment {                                                    
  struct environment* outer; // NULL for global env                             
  struct hash_table* table;                                                     
};
typedef struct environment env;
void define(char *sym,node *val,env *E);
entry *hsearch(char *key,htab *H);
node *lookup(char *sym,env *E);
void hdestroy(htab *H);
void env_destroy(env *E);
htab *hcreate(int size);
env *new_env(int size,env *outer);
