#ifndef PARSER_H
#define PARSER_H

#include "typedef.h"
#include "lexer.h"

enum NodeType {
  NODE_ROOT,
};

struct Node {
  NodeType type;
  string value;
};

#endif // PARSER_H
