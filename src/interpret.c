#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "interpret.h"

const int GLOBAL_SIZE = 31;
const int LINE_LENGTH = 1024;

void interpret(char* fname, env* G) {
  FILE* src = fopen(fname, "r");
  if (src == NULL) {
    printf("Error opening file.\n");
    exit(1);
  }

  while (!feof(src)) {
    node* tree = parse_exp(src);
    if (tree == NULL) break;
    eval(tree, G);
  }
  fclose(src);
}

// seems inefficient but dealing with stdin directly caused issues
FILE* buff_stdin() {
  char* str = (char*) malloc(LINE_LENGTH * sizeof(char));
  str = fgets(str, LINE_LENGTH, stdin);

  if (feof(stdin)) {
    printf("Moritorus te saluto.\n");
    exit(1);
  }

  if (str == NULL) {
    printf("read error, exiting\n");
    exit(1);
  }

  FILE* tmp = tmpfile();
  fputs(str, tmp);
  return tmp;
}

void repl(env* G) {
  while (1) { // exiting is handled in parse.c
    printf("-->  ");

    FILE* tmp = buff_stdin();
    freopen(NULL, "r", tmp);
    node* tree = parse_exp(tmp);
    fclose(tmp);

    s_print(eval(tree, G));
    printf("\n");
  }
}

int main(int argc, char** argv) {
  env* global = new_env(GLOBAL_SIZE, NULL);

  if (argc == 1) {
    repl(global);
    return 0;
  }

  bool interactive = false;
  for (int i=0;i<argc;i++) {
    char* arg = argv[i];
    if (!strcmp(arg, "-i") || !strcmp(arg, "--interactive")) {
      interactive = true;
    }
    else {
      interpret(argv[i], global);
    }
  }

  if (interactive) repl(global);
  return 0;
}
