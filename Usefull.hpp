#ifndef USEFULL_HPP
#define USEFULL_HPP
#include <stdio.h>

enum types
	{
		lex_number=1,
		lex_variable=2,
		lex_point=3,
		lex_function=4,
		lex_string=5,
	};

int getlen (char *str);
char* FillBuf(char *str);
int CheckSep(char c);
char* addChar(char *str, char symb);
int StrEq(char *str, const char *key);
int CheckKey(char *str);
int CanSeparate(char symb);
//void Print(struct Lexeme *ZeroLex);
FILE* FileOpen(char *filename);

#endif
