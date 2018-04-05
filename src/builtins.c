#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "builtins.h"

const int MAX_DIGITS = 33; // maximum number of digits plus optional sign

node* builtins(char* op, list* args) {
  // math
  if (!strcmp(op, "+")) return plus(args);
  if (!strcmp(op, "*")) return mul(args);
  if (!strcmp(op, "-")) return sub(args);
  if (!strcmp(op, "/")) return divi(args);
  
  // comparisons
  if (!strcmp(op, ">")) return gth(args);
  if (!strcmp(op, "<")) return lth(args);
  if (!strcmp(op, "=")) return equ(args);

  // list operations
  if (!strcmp(op, "car")) return bcar(args);
  if (!strcmp(op, "cdr")) return bcdr(args);
  if (!strcmp(op, "cons")) return cons(args);
  if (!strcmp(op, "list")) return blist(args);
  if (!strcmp(op, "eq?")) return lequ(args);

  // printing
  if (!strcmp(op, "display")) return display(args);
  
  return NULL;
}

// Utility to get numbers from strings and vice-versa

char* ltoa(long num) {
  char* convert = calloc(MAX_DIGITS+1, sizeof(char)); 
  int i = 0;
  long anum = abs(num);

  if (anum == 0) {
    convert[MAX_DIGITS - 1] = '0';
    return convert + MAX_DIGITS - 1;
  }

  while (anum > 0L) {
    convert[MAX_DIGITS-i-1] = '0' + (char) (anum % 10);
    anum /= 10;
    i++;
  }

  if (num < 0) {
    convert[MAX_DIGITS-i-1] = '-';
    return convert + (MAX_DIGITS - i - 1);
  }

  return convert + (MAX_DIGITS - i);
}

long p_strtol(char* str, char** end) {
  // the p is for perfect, no whitespace or other symbols in front
  long num = 0;
  char* i = str;

  while (*i != '\0') {
    if (i == str && *i == '-') {
      i++; 
      continue;
    }
    if ((*i < 47 || *i > 57)) *end = NULL; // non-numeric
    num *= 10;
    num += (long) *i - '0';
    i++;
  }
  if (*end == NULL) *end = str;
  if (*str == '-') num = -num;
  return num;
}

// Implementations
// math, operates on numbers or character values

node* plus(list* args) {
  long sum = 0L;
  char* dummy;

  node* n = args->start->next;
  while (n != args->end) {
    sum = sum + p_strtol((char*) n->data, &dummy);
    n = n->next;
  }

  return new_node(true, (void*) ltoa(sum));
}

node* mul(list* args) {
  long prod = 1L;
  char* dummy;

  node* n = args->start->next;
  while (n != args->end) {
    prod = prod * p_strtol((char*) n->data, &dummy);
    n = n->next;
  }

  return new_node(true, (void*) ltoa(prod));
}

node* sub(list* args) {
  if (args->start->next == args->end) return NULL;
  long sum = 0L;
  char* dummy;

  // needs at least one argument, has different behavior for only one arg
  if (args->start->next->next != args->end) 
    sum += 2 * p_strtol((char*) args->start->next->data, &dummy);

  node* n = args->start->next;
  while (n != args->end) {
    sum = sum - p_strtol((char*) n->data, &dummy);
    n = n->next;
  }

  return new_node(true, (void*) ltoa(sum));
}

node* divi(list* args) {
  // needs at least one argument
  if (args->start->next == args->end) return NULL;
  long prod = 1L;
  char* dummy;

  // has different behavior depending on first arg
  long num = p_strtol((char*) args->start->next->data, &dummy);
  if (args->start->next->next == args->end) {
    if (num == 0L) return NULL;
    prod /= num; // always 0 or 1
  }
  else {
    prod = num;
  }


  node* n = args->start->next->next;
  while (n != args->end) {
    num = p_strtol((char*) n->data, &dummy);
    if (num == 0L) return NULL;
    prod = prod / num;
    n = n->next;
  }

  return new_node(true, (void*) ltoa(prod));
}

// comparisons

node* gth(list* args) {
  char* truth = "1";
  char* dummy;

  node* n = args->start->next;
  while (n != args->end) {
    node* m = n->next;
    if (m != args->end) {
      long nl = p_strtol((char*) n->data, &dummy);
      long ml = p_strtol((char*) m->data, &dummy);
      if (nl <= ml) truth = "0";
    }
    n = m;
  }

  return new_node(true, (void*) truth);
}

node* lth(list* args) {
  char* truth = "1";
  char* dummy;

  node* n = args->start->next;
  while (n != args->end) {
    node* m = n->next;
    if (m != args->end) {
      long nl = p_strtol((char*) n->data, &dummy);
      long ml = p_strtol((char*) m->data, &dummy);
      if (nl >= ml) truth = "0";
    }
    n = m;
  }

  return new_node(true, (void*) truth);
}


node* equ(list* args) {
  char* truth = "1";
  char* dummy;

  node* n = args->start->next;
  while (n != args->end) {
    node* m = n->next;
    if (m != args->end) {
      long nl = p_strtol((char*) n->data, &dummy);
      long ml = p_strtol((char*) m->data, &dummy);
      if (nl != ml) truth = "0";
    }
    n = m;
  }

  return new_node(true, (void*) truth);
}

// list operations 

node* bcar(list* args) {
  node* n = car(args);
  if (n->atom) return NULL;
  list* l = (list*) n->data;
  return car(l);
}

node* bcdr(list* args) {
  node* n = car(args);
  if (n->atom) return NULL;
  list* l = (list*) n->data;
  return new_node(false, (void*) cdr(l));
}

node* cons(list* args) {
  if (args->start->next == args->end || args->start->next->next == args->end) 
    return NULL;

  node* ca = args->start->next;
  node* cd = args->start->next->next;

  if (cd->atom) {
    list* new = new_list();
    insert(new, cd);
    insert(new, ca);
    return new_node(false, (void*) new);
  }

  insert((list*) cd->data, new_node(ca->atom, (void*) ca->data));

  return args->start->next->next;
}

node* blist(list* args) {
  return new_node(false, (void*) args);
}

node* lequ(list* args) {
  // check equality of 2 arbitrary sexps (symbols or lists)
  if (args->start->next == args->end || args->start->next->next == args->end)
    return NULL;
  if (args->start->next->next->next != args->end) return NULL;

  node* ca = args->start->next;
  node* cd = args->start->next->next;

  if (ca->atom && cd->atom) {
    return equ(args);
  }
  char* eq = "1";
  if (!ca->atom && !cd->atom) {
    bool equal =  ls_compare((list*) ca->data, (list*) cd->data);
    if (!equal) eq = "0";
  }
  else eq = "0";

  return new_node(true, (void*) eq); // lists and atoms are not equal
}

// printing

node* display(list* args) {
  if (args->start->next == args->end) return NULL;
  s_print(args->start->next);
  printf("\n");

  Returntype ret = DISPLAYED;
  return (node*) ret;
}
