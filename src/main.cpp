#include <fstream>
#include <sstream>
#include "typedef.h"
#include "lexer.h"
#include "parser.h"

i32 main(i32 argc, char **argv) {
  if (argc < 2) {
    printf("siz_error: no input file given.");
    return 0;
  }

  std::ifstream file(argv[1]);
	std::ostringstream stream;
	stream << file.rdbuf();
	string source = stream.str();
	
	//vector<Siz_Token> tokens = Siz_generateTokens(source);
	
	return 0;
}
