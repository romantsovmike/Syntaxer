#ifndef SYNT_HPP
#define SYNT_HPP

#include <stdio.h>

struct Exception{
	struct Lexeme *lexeme;
	const char *message;
	void ThrowException(struct Lexeme*, const char*);
};


class Syntaxer{
	struct Lexeme *list;
	struct Exception err;

	void Next();
	void Start();
	void Body();
	void Command();
	void Execute();
	void Func();
	void Arg();
	void Var();
	void Mas();
	void Expression();
	void Left();
	void Right();
	void Part1();
	void Part2();
	void Base1();
	void Base2();


public:
	Syntaxer();
	~Syntaxer();
	void GetList(struct Lexeme*);
};
#endif
