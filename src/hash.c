#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hash.h"

int hash(char* key) {
  int sum = 0;
  for ( ; *key != '\0'; key++) sum = (sum + *key) * 31;
  return sum;
}

htab* hcreate(int size) {
  htab* new = (htab*) calloc(1, sizeof(htab));
  new->size = size;
  new->table = (entry**) calloc(size, sizeof(entry*));
  return new;
}

void hdestroy(htab* H) {
  free(H); // may be expanded with garbage collection
}

// return true on success, false on failure
bool hoverwrite(entry* new, htab* H) {
  if (new == NULL || H == NULL) return false;

  int key = hash(new->key) % H->size;

  // linear probing to resolve conflicts
  for (int i = key; i < key + H->size; i++) {
    entry* spot = (H->table)[i % H->size];
    if (spot == NULL || !strcmp(new->key, spot->key)) {
      // overwrite value if it's already in the table
      (H->table)[i % H->size] = new;
      return true;
    }
  }

  // if there were no empty spots in the table
  return false;
}

// return NULL on failure
entry* hsearch(char* key, htab* H) {
  if (key == NULL || H == NULL) return NULL;

  int hkey = hash(key) % H->size;

  // entries are put in by linear probing
  for (int i = hkey; i < hkey + H->size; i++) {
    entry* spot = (H->table)[i % H->size];
    if (spot != NULL && !strcmp(key, spot->key)) {
      return spot;
    }
  }

  return NULL;
}
