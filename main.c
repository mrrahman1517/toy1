//#include <stdio.h>
#include "codegen.h"
#include "parser.h"
#include "lexer.h"

int main() {
  next_token();
  T_statement_list statement_list = parse_statement_list();
  gencode_statement_list(statement_list);
  //printf("nice try :)\n");
  return 0;
}
