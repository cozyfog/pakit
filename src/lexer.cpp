#include "typedef.h"
#include "lexer.h"

bool in_string = false;

const char *alphabet = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char *digits = "01234561789";

bool char_in_string(char c, const char *s) {
	i32 i = -1;
	while (s[++i] != c && s[i] != '\0');
	
	return s[i] == c;
}

u64 line_num = 0;
TokenType charTokenType(char c) {
	if (c == '\'') {
		in_string = !in_string;
		return TOKEN_STRING;
	}
	
	if (c == '\"') {
		in_string = !in_string;
		return TOKEN_STRING;
	}
	
	if (in_string) return TOKEN_STRING;
	
	switch (c) {
		case  ' ': return TOKEN_WHITESPACE;
		
		case '\n': {
			++line_num;
			return TOKEN_WHITESPACE;
		}
		
		case '\r': return TOKEN_WHITESPACE;
		case '\t': return TOKEN_WHITESPACE;
		
		case '(': return TOKEN_PAREN_OPEN;
		case ')': return TOKEN_PAREN_CLOSE;
		
		case '{': return TOKEN_CURLY_OPEN;
		case '}': return TOKEN_CURLY_CLOSE;
		
		case ':': return TOKEN_COLON;
		case ';': return TOKEN_SEMICOLON;
		case '.': return TOKEN_DOT;
		case ',': return TOKEN_COMMA;
		
		case '=': return TOKEN_EQUALS;
		case '<': return TOKEN_SMALLER;
		case '>': return TOKEN_BIGGER;
		case '!': return TOKEN_NOT;
		case '&': return TOKEN_AMPERSAND;
		case '|': return TOKEN_VERTICAL;
		
		case '+': return TOKEN_PLUS;
		case '-': return TOKEN_MINUS;
		case '*': return TOKEN_STAR;
		case '/': return TOKEN_SLASH;
		case '%': return TOKEN_PERCENT;
		
		default: break;
	}
	
	if (char_in_string(c, alphabet)) return TOKEN_IDENTIFIER;
	if (char_in_string(c, digits)) return TOKEN_INTENGER;
	
	std::cout << "Error: Unknown Token '" << c << "' in line " << line_num << "." << std::endl;
	exit(1);
	return TOKEN_UNDEFINED;
}

TokenType advancedTokenType(const char *token) {
	if (!strcmp(token,   "return")) return TOKEN_RETURN;
	if (!strcmp(token,       "if")) return TOKEN_IF;
	if (!strcmp(token,     "else")) return TOKEN_ELSE;
	if (!strcmp(token,      "for")) return TOKEN_FOR;
	if (!strcmp(token,    "while")) return TOKEN_WHILE;
	if (!strcmp(token,   "switch")) return TOKEN_AND;
	if (!strcmp(token,     "case")) return TOKEN_CASE;
	if (!strcmp(token,    "break")) return TOKEN_BREAK;
	if (!strcmp(token,  "default")) return TOKEN_DEFAULT;
	if (!strcmp(token, "continue")) return TOKEN_CONTINUE;
	if (!strcmp(token,     "null")) return TOKEN_NULL;
	if (!strcmp(token,     "true")) return TOKEN_TRUE;
	if (!strcmp(token,    "false")) return TOKEN_FALSE;
	if (!strcmp(token,     "enum")) return TOKEN_ENUM;
	if (!strcmp(token,   "struct")) return TOKEN_STRUCT;
	
	return TOKEN_IDENTIFIER;
}

void fullTokenType(Token *token) {
  if (token->type == TOKEN_IDENTIFIER) {
		token->type = advancedTokenType(token->data.c_str());
  }
}

vector<Token> generateTokens(string source) {
	line_num = 1;
	vector<Token> tokens;
	
	const char *c_str = source.c_str();
	Token full = {" ", TOKEN_WHITESPACE};
	
	for (u64 i = 0; i < source.size() + 1; ++i) {
		char c = c_str[i];
		
		Token curr;
		curr.type = charTokenType(c);
		
    // ? && =
    if (curr.type == TOKEN_EQUALS) {
		  switch (full.type) {
        case TOKEN_EQUALS :   full.type = TOKEN_EQUIVALENT;     break;
	  	  case TOKEN_SMALLER:   full.type = TOKEN_SMALLER_EQUALS; break;
        case TOKEN_BIGGER :   full.type = TOKEN_BIGGER_EQUALS;  break;
        case TOKEN_NOT    :   full.type = TOKEN_NOT_EQUALS;     break;
        case TOKEN_PLUS   :   full.type = TOKEN_PLUS_EQUALS;    break;
        case TOKEN_MINUS  :   full.type = TOKEN_MINUS_EQUALS;   break;
        case TOKEN_STAR   :   full.type = TOKEN_STAR_EQUALS;    break;
        case TOKEN_SLASH  :   full.type = TOKEN_SLASH_EQUALS;   break;
        default: ; break;
      }
			full.data.push_back({c});
		}

		// FLOATS
		if (full.type == TOKEN_INTENGER && curr.type == TOKEN_DOT) {
			full.type = TOKEN_FLOAT;
			full.data.push_back({c});
		}		
		
		// IF BOTH ARE SAME AND STUFF
		else if ((curr.type == full.type) ||
						 (full.type == TOKEN_IDENTIFIER && curr.type == TOKEN_INTENGER) || (full.type == TOKEN_FLOAT && curr.type == TOKEN_INTENGER)) {
      switch (full.type) {
        case TOKEN_AMPERSAND:   full.type = TOKEN_AND;              break;
        case TOKEN_VERTICAL :   full.type = TOKEN_OR;               break;
        case TOKEN_PLUS     :   full.type = TOKEN_INCREMENT;        break;
        case TOKEN_MINUS    :   full.type = TOKEN_DECREMENT;        break;
        case TOKEN_STAR     :   full.type = TOKEN_EXPONENTIATION;   break;
        case TOKEN_SLASH    :   full.type = TOKEN_FLOOR_DIVISION;   break;
        default: break;
      }

			full.data.push_back({c});
		}
		
		// ADDING TO VECTOR
		else {
			curr.data = string({c});
			fullTokenType(&full);
      
      if (full.type != TOKEN_WHITESPACE) {
			  tokens.push_back(full);
      }
			
      full = curr;
		}
	}
	
	return tokens;
}
