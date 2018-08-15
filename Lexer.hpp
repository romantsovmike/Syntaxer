#ifndef LEXER_HPP
#define LEXER_HPP
#include <stdio.h>

struct Lexeme{
	char *str;
	const char *type;
	int str_num, Type;
	struct Lexeme *next;
};


class Lexer{
	
	enum states
		{
			start=1,
			number=2,
			keyword=3,
			string=4,
			special=5,
			eq=6
		};

	enum types
		{
			lex_number=1,
			lex_variable=2,
			lex_point=3,
			lex_function=4,
			lex_string=5,
		};

	char symb, *curr_lex;
	const char *curr_type;
	struct Lexeme *CurrLex, *ZeroLex;
	int str_num, state, CurrType;

	void AnalyzeFirst();
	void AnalyzeNumber();
	void AnalyzeSpecial();
	void AnalyzeString();
	void AnalyzeEq();
	void AnalyzeSeparator();
	void AnalyzeKeyword();
	void Output();

public:
	Lexer();
	~Lexer();
	void Identify(char c);
	struct Lexeme *GiveList();
};

#endif
