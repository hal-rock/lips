// parse lisp-like s-expressions

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "parse.h"

const int MAX_SYMBOL_LENGTH = 32;

bool sym_end(int c) {
  return c == ' ' || c == '\t' || c == '\n' || c == EOF
              || c == '(' || c == ')' || c == '\'';
}

char* next_token(FILE* src) {
  char* tok = (char*) malloc(MAX_SYMBOL_LENGTH+1);
  int i = 0;
  int c = ' ';

  // get past whitespace
  while (c == ' ' || c == '\t' || c == '\n') c = getc(src);

  while (i < MAX_SYMBOL_LENGTH && !sym_end(c)) {
    tok[i] = (char) c;
    c = getc(src);
    i++;
  }
  // kind of messy logic due to how whitespaces are skipped over
  // and i is never incremented if a paren is found immediately
  // but appears to function now
  if (c == ')') {
    if (tok[0] != '\0') {
      ungetc(c, src);
      tok[i] = '\0';
    } else {
      tok[0] = c;
      tok[1] = '\0';
    }
  }
  else if (c == '(' || c == '\'') {
    tok[0] = c;
    tok[1] = '\0';
  }
  else tok[i] = '\0';


  // need to determine EOF somehow in main
  if (i == 0 && c == EOF) tok[0] = '\0';

  return tok;
}

// src is already open
node* parse_exp(FILE* src) {
  char* tok = next_token(src);
  if (tok[0] == '(') {
    return parse_list(src);
  }

  if (tok[0] == '\'') {
    return parse_quote(src);
  }

  if (tok[0] == '\0') {
    return NULL;
  }

  return parse_atom(tok);
}

node* parse_quote(FILE* src) {
  list* tree = new_list();
  add(tree, new_node(true, (void*) "quote"));
  add(tree, parse_exp(src));
  return new_node(false, tree);
}

node* parse_atom(char* tok) {
  return new_node(true, tok);
}

node* parse_list(FILE* src) {
  char* tok = next_token(src);
  list* tree = new_list();
  
  while (tok[0] != '\0' && tok[0] != ')') {
    if (tok[0] == '\'') {
      node* quote = new_node(true, (void*) "quote");
      node* next = parse_exp(src);
      list* both = new_list();
      add(both, quote); add(both, next);
      add(tree, new_node(false, (void*) both));
    }

    else if (tok[0] == '(') {
      node* new = parse_list(src);
      add(tree, new);
    }

    // must be atom
    else {
      node* new = new_node(true, (void*) tok);
      add(tree, new);
    }

    tok = next_token(src);
  }

  if (tok[0] == '\0') {
    perror("syntax error: mismatched parentheses\n"); // ???
    return new_node(false, (void*) new_list());
  }

  return new_node(false, (void*) tree);
}
