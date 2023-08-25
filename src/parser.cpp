#include "typedef.h"
#include "lexer.h"
#include "parser.h"

vector<Node> generateAst(vector<Token> &tokens) {
  vector<Node> ast;

  for (u64 i = 0; i < tokens.size(); ++i) {
    Node node = {NODE_UNDEFINED, {}};
    Token token = tokens[i];
    Token last_token = tokens[i - 1];
    Token next_token = tokens[i + 1];

    switch (token.type) {
      case TOKEN_COLON:
        if (last_token.type == TOKEN_IDENTIFIER &&  next_token.type == TOKEN_IDENTIFIER) {
          node.type = NODE_VARIABLE_NEW;
          node.data = {last_token.data, next_token.data};
        }
        break;
      case TOKEN_EQUALS:
        break;
    }

    ast.push_back(node);
  }

  return ast;
}
