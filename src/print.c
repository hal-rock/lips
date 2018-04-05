#include <stdio.h>
#include <string.h>
#include "print.h"

void s_print(node* sexp) {
  if (sexp == NULL || (Returntype) sexp == DISPLAYED) return;
  else if (sexp->atom) {
    printf((char*) sexp->data);
    printf(" ");
  }

  else {
    printf("(");
    list* ls = (list*) sexp->data;
    node* n = ls->start->next;
    while (n != ls->end) {
      s_print(n);
      n = n->next;
    }
    if (n == ls->start->next) printf(" ");
    printf("\b) ");
  }
  fflush(stdout);
  return;
}
