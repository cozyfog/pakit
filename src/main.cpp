#include <fstream>
#include <sstream>
#include "typedef.h"
#include "lexer.h"
#include "parser.h"

i32 main(i32 argc, char **argv) {
  if (argc < 2) {
    printf("error: no input file given.");
    return 0;
  }

  std::ifstream file(argv[1]);
	std::ostringstream stream;
	stream << file.rdbuf();
	string source = stream.str();
	
	vector<Token> tokens = generateTokens(source);
  for (Token token : tokens) {
    fprintf(stdout, "{%s : %d} ", token.data.c_str(), token.type);
  }
  fprintf(stdout, "\n");

	return 0;
}
