#include <stdlib.h>
#include "env.h"

env* new_env(int size, env* outer) {
  env* E = (env*) malloc(sizeof(env));
  E->outer = outer; 
  E->table = hcreate(size);

  return E;
}

void env_destroy(env* E) {
  if (E == NULL) return;
  hdestroy(E->table);
  free(E);
}

node* lookup(char* sym, env* E) {
  if (E == NULL) return NULL;
  entry* var = (entry*) hsearch(sym, E->table);
  if (var == NULL) return lookup(sym, E->outer);
  return (node*) var->data;
}

void define(char* sym, node* val, env* E) {
  entry* var = (entry*) malloc(sizeof(entry));
  var->key = sym;
  var->data = (void*) val;

  hoverwrite(var, E->table);
}

