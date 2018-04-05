/* This file was automatically generated.  Do not edit! */
#include <stdbool.h>
typedef struct environment environment;
typedef struct hash_table hash_table;
struct environment {                                                    
  struct environment* outer; // NULL for global env                             
  struct hash_table* table;                                                     
};
typedef struct environment env;
env *new_env(int size,env *outer);
int main(int argc,char **argv);
typedef struct list_node list_node;
struct list_node {
  bool atom;
  void* data;
  struct list_node* next;
};
typedef struct list_node node;
void s_print(node *sexp);
void repl(env *G);
FILE *buff_stdin();
node *eval(node *exp,env *E);
node *eval(node *exp,env *E);
node *parse_exp(FILE *src);
void interpret(char *fname,env *G);
extern const int LINE_LENGTH;
extern const int GLOBAL_SIZE;
typedef struct table_entry table_entry;
struct table_entry {
  char* key;
  void* data;
};
typedef struct table_entry entry;
struct hash_table {
  int size;
  entry** table;
};
