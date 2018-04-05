#include <stdlib.h>
#include <stdio.h>
#include "func.h"

node* eval(node* exp, env* E);

const int ENV_SIZE = 10; // shouldn't be more function arguments than this

node* call(node* func, list* passed_args, env* E) {
  // func is list w/ two elements, args and body
  list* fn = (list*) func->data;
  list* fn_args = (list*) car(fn)->data;
  list* fn_body = cdr(fn);

  env* fn_env = new_env(ENV_SIZE, E);

  node* arg1 = fn_args->start->next;
  node* arg2 = passed_args->start->next;
  while (arg1 != fn_args->end && arg2 != passed_args->end) {
    // minimal concern for safety, since they should be same length
    define((char*) arg1->data, arg2, fn_env);
    arg1 = arg1->next;
    arg2 = arg2->next;
  }

  if (arg1 != fn_args->end || arg2 != passed_args->end) {
    perror("Function called with wrong number of arguments");
    return NULL;
  }

  node* retval;
  node* n = fn_body->start->next;
  while (n != fn_body->end) {
    retval = eval(n, fn_env);
    n = n->next;
  }

  env_destroy(fn_env);

  return retval;
}
  
