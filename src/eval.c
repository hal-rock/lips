#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "eval.h"

node* eval(node* exp, env* E) { 
  if (exp == NULL || (Returntype) exp == DISPLAYED || E == NULL) {
    perror("NULL return type somewhere\n");
    return NULL;
  }

  if (exp->atom) {
    char* sym = (char*) exp->data;
    char* end = (char*) calloc(1, sizeof(char));
    p_strtol(sym, &end);

    if (end == sym) {
      // unsuccessful parse, it's a symbol
      return lookup(sym, E);
    }

    return exp;
  }

  // exp holds a list
  list* ls = (list*) exp->data;
  node* cr = car(ls);
  if (cr == NULL) return NULL; // should probably make this an error

  if (!(cr->atom)) {
    node* proc = eval(cr, E);
    list* args = evaluate(cdr(ls), E);
    return call(proc, args, E);
  }

  // special forms
  char* form = (char*) cr->data;

  if (!strcmp(form, "if")) {
    node* test = eval(car(cdr(ls)), E); // bad test
    if (truth(test)) return eval(car(cdr(cdr(ls))), E);
    return eval(car(cdr(cdr(cdr(ls)))), E);
  }

  else if (!strcmp(form, "def")) {
    define((char*) car(cdr(ls))->data, eval(car(cdr(cdr(ls))), E), E);
    return new_node(false, new_list());
  }

  else if (!strcmp(form, "quote")) {
    return car(cdr(ls)); 
  }

  list* args = evaluate(cdr(ls), E);
  node* result = builtins(form, args);

  if (result == NULL) {
    // not a builtin, must be user-defined procedure
    node* proc = eval(cr, E);
    return call(proc, args, E);
  }

  // builtin math, etc.
  return result;
}

// utilities

list* evaluate(list* exps, env* E) { 
  // evaluate each element of exps in E
  list* result = new_list();

  node* n = exps->start->next;
  while (n != exps->end) {
    node* n1 = new_node(n->atom, n->data);
    add(result, eval(n1, E));
    n = n->next;
  }

  return result;
}

bool truth(node* n) {
  if (n == NULL) return false;
  if (!n->atom) return true;
  
  char* dat = (char*) n->data;
  char* dum;
  return (bool) p_strtol(dat, &dum) != 0L;
}
