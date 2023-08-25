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
  vector<Node> ast = generateAst(tokens);

  for (Node n : ast) {
    fprintf(stdout, "%d ->", n.type);
    for (string s : n.data) {
      fprintf(stdout, " %s", s.c_str());
    }
    fprintf(stdout, "\n");
  }

  return 0;
}
