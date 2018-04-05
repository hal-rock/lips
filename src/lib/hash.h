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
entry *hsearch(char *key,htab *H);
bool hoverwrite(entry *new,htab *H);
void hdestroy(htab *H);
htab *hcreate(int size);
int hash(char *key);
