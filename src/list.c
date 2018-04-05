#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

const int MAX_SYMBOL_LENGTH;

// functions

node* new_node(bool atom, void* data) {
  node* new = (node*) malloc(sizeof(node));
  new->atom = atom;
  new->data = data;
  return new;
}

list* new_list() {
  list* new = (list*) malloc(sizeof(list));
  new->start = new_node(false, NULL);
  new->end = new_node(false, NULL); // points to last element
  new->start->next = new->end;
  new->end->next = new->start;

  return new;
}

void insert(list* L, node* n) { // adds to beginning
  if (L == NULL || n == NULL) return;
  n->next = L->start->next;
  if (n->next == L->end) L->end->next = n;
  L->start->next = n;
}

void add(list* L, node* n) { // adds to end
  if (L == NULL || n == NULL) return;
  L->end->next->next = n;
  n->next = L->end;
  L->end->next = n;
}

node* car(list* L) {
  if (L == NULL || L->start->next == L->end) return NULL;
  return nd_copy(L->start->next);
}

list* cdr(list* L) {
  if (L == NULL || L->start->next == L->end) return NULL;
  list* new = ls_copy(L);
  node* tmp = new->start;
  new->start = new->start->next;
  nd_destroy(tmp);
  return new;
}

// deep copy
node* nd_copy(node* n) {
  if (n == NULL) return NULL;
  if (n->atom) {
    char* data = (char*) malloc(MAX_SYMBOL_LENGTH+1);
    return new_node(n->atom, strcpy(data, (char*) n->data));
  }
  
  return new_node(false, ls_copy((list*) n->data));
}

// deep copy
list* ls_copy(list* L) {
  if (L == NULL) return NULL;
  list* new = new_list();
  
  node* n = L->start->next;
  while (n != L->end) {
    add(new, nd_copy(n));
    n = n->next;
  }

  return new;
}

bool ls_compare(list* L1, list* L2) {
  if (L1 == NULL || L2 == NULL) return NULL;
  node* n = L1->start->next;
  node* m = L2->start->next;

  while (n != L1->end && m != L2->end) {
    if (n->atom != m->atom) return false;
    if (n->atom) {
      bool equal = !strcmp((char*) n->data, (char*) m->data);
      if (!equal) return false;
    }
    else {
      bool equal = ls_compare((list*) n->data, (list*) m->data);
      if (!equal) return false;
    }
  }

  if (n != L1->end || m != L2->end) return false;

  return true;
}

void nd_destroy(node* n) {
  if (n == NULL) return;
  if (n->atom) {
    free(n->data);
    free(n);
    return;
  }
  ls_destroy((list*) n->data);
  free(n);
}

void ls_destroy(list* L) {
  if (L == NULL) return;
  
  node* n = L->start;
  while (n != L->end) {
    node* tmp = n->next;
    nd_destroy(n);
    n = tmp;
  }
  nd_destroy(L->end);
  free(L);
}

