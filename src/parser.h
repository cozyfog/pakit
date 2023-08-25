#ifndef PARSER_H
#define PARSER_H

#include "typedef.h"
#include "lexer.h"

enum NodeType {
  NODE_UNDEFINED,
  NODE_VARIABLE_NEW, // data[0] = variable_name, data[1] = variable_type
  NODE_VARIABLE_SET,
};

struct Node {
  NodeType type;
  vector<string> data;
};

vector<Node> generateAst(vector<Token> &tokens);

#endif // PARSER_H
