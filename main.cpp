#include <FlexLexer.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

int yyFlexLexer::yywrap() { return 1; }

int main(int argc, char* argv[]) {
  --argc;
  ++argv;
  std::vector<std::string> args(argv, argv + argc);
  if (args.empty()) { return 1; }
  fs::path file(args.front());
  fs::path new_name(file.parent_path() / file.stem());
  std::ifstream file_in(file);
  std::ofstream file_out(new_name);
  FlexLexer* lexer = new yyFlexLexer(file_in, file_out);
  while (lexer->yylex()) {
    // do nothing
  }
  delete lexer;
  return 0;
}
