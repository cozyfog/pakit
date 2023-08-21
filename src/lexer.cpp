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

size_t line_num = 0;
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
	if (strcmp(token,   "return")) return TOKEN_RETURN;
	if (strcmp(token,       "if")) return TOKEN_IF;
	if (strcmp(token,     "else")) return TOKEN_ELSE;
	if (strcmp(token,      "for")) return TOKEN_FOR;
	if (strcmp(token,    "while")) return TOKEN_WHILE;
	if (strcmp(token,   "switch")) return TOKEN_AND;
	if (strcmp(token,     "case")) return TOKEN_CASE;
	if (strcmp(token,    "break")) return TOKEN_BREAK;
	if (strcmp(token,  "default")) return TOKEN_DEFAULT;
	if (strcmp(token, "continue")) return TOKEN_CONTINUE;
	if (strcmp(token,     "null")) return TOKEN_NULL;
	if (strcmp(token,     "true")) return TOKEN_TRUE;
	if (strcmp(token,    "false")) return TOKEN_FALSE;
	if (strcmp(token,     "enum")) return TOKEN_ENUM;
	if (strcmp(token,   "struct")) return TOKEN_STRUCT;
	
	return TOKEN_IDENTIFIER;
}

void fullTokenType(Token *token) {
	switch (token->type) {
		case TOKEN_IDENTIFIER: {
			token->type = advancedTokenType(token->data.c_str());
		} break;
		
		case TOKEN_AMPERSAND: {
			if (token->data == "&&") token->type = TOKEN_AND;
		} break;
		
		default: break;
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
		
		// FLOATS
		if (full.type == TOKEN_INTENGER && curr.type == TOKEN_DOT) {
			full.type = TOKEN_FLOAT;
			full.data.push_back({c});
		}
		
		// ==
		else if (full.type == TOKEN_EQUALS && curr.type == TOKEN_EQUALS) {
			full.type = TOKEN_EQUIVALENT;
			full.data.push_back({c});
		}
		
		// <=
		else if (full.type == TOKEN_SMALLER && curr.type == TOKEN_EQUALS) {
			full.type = TOKEN_SMALLER_EQUALS;
			full.data.push_back({c});
		}
		
		// >=
		else if (full.type == TOKEN_BIGGER && curr.type == TOKEN_EQUALS) {
			full.type = TOKEN_BIGGER_EQUALS;
			full.data.push_back({c});
		}
		
		// !=
		else if (full.type == TOKEN_NOT && curr.type == TOKEN_EQUALS) {
			full.type = TOKEN_NOT_EQUALS;
			full.data.push_back({c});
		}
		
		// &&
		else if (full.type == TOKEN_AMPERSAND && curr.type == TOKEN_AMPERSAND) {
			full.type = TOKEN_AND;
			full.data.push_back({c});
		}
		
		// ||
		else if (full.type == TOKEN_VERTICAL && curr.type == TOKEN_VERTICAL) {
			full.type = TOKEN_OR;
			full.data.push_back({c});
		}
		
		// +=
		else if (full.type == TOKEN_PLUS && curr.type == TOKEN_EQUALS) {
			full.type = TOKEN_PLUS_EQUALS;
			full.data.push_back({c});
		}
		
		// -=
		else if (full.type == TOKEN_MINUS && curr.type == TOKEN_EQUALS) {
			full.type = TOKEN_MINUS_EQUALS;
			full.data.push_back({c});
		}
		
		// *=
		else if (full.type == TOKEN_STAR && curr.type == TOKEN_EQUALS) {
			full.type = TOKEN_STAR_EQUALS;
			full.data.push_back({c});
		}
		
		// /=
		else if (full.type == TOKEN_SLASH && curr.type == TOKEN_EQUALS) {
			full.type = TOKEN_SLASH_EQUALS;
			full.data.push_back({c});
		}
		
		// ++
		else if (full.type == TOKEN_PLUS && curr.type == TOKEN_PLUS) {
			full.type = TOKEN_INCREMENT;
			full.data.push_back({c});
		}
		
		// --
		else if (full.type == TOKEN_MINUS && curr.type == TOKEN_MINUS) {
			full.type = TOKEN_DECREMENT;
			full.data.push_back({c});
		}
		
		// **
		else if (full.type == TOKEN_STAR && curr.type == TOKEN_STAR) {
			full.type = TOKEN_EXPONENTIATION;
			full.data.push_back({c});
		}
		
		// //
		else if (full.type == TOKEN_SLASH && curr.type == TOKEN_SLASH) {
			full.type = TOKEN_FLOOR_DIVISION;
			full.data.push_back({c});
		}
		
		// IF BOTH ARE SAME AND STUFF
		else if ((curr.type == full.type) ||
						 (full.type == TOKEN_IDENTIFIER && curr.type == TOKEN_INTENGER) || (full.type == TOKEN_FLOAT && curr.type == TOKEN_INTENGER)) {
			full.data.push_back({c});
		}
		
		// ADDING TO VECTOR
		else {
			curr.data = string({c});
			fullTokenType(&full);
			tokens.push_back(full);
			full = curr;
		}
	}
	
	return tokens;
}
