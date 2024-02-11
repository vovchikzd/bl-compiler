#include <iostream>
#include <FlexLexer.h>

int yyFlexLexer::yywrap() {
  return 1;
}

int main() {
  FlexLexer* lexer = new yyFlexLexer;
  while (lexer->yylex()) {
    // do nothing
  }
  delete lexer;
}
