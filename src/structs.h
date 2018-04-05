#include <stdbool.h>

typedef struct table_entry {
  char* key;
  void* data;
} entry;

typedef struct hash_table {
  int size;
  entry** table;
} htab;

typedef struct environment {                                                    
  struct environment* outer; // NULL for global env                             
  struct hash_table* table;                                                     
} env;

typedef struct list_node {
  bool atom;
  void* data;
  struct list_node* next;
} node;

typedef struct linked_list {
  node* start;
  node* end;
} list;

enum Returntype {DISPLAYED = 0x1}
