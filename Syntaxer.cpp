#include "Lexer.hpp"
#include "Syntaxer.hpp"
#include "Usefull.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

Syntaxer::Syntaxer(){}

Syntaxer::~Syntaxer(){delete list;}

void Syntaxer::Next()
{
	list=list->next;
	if (list == NULL)
		err.ThrowException(list, "Unexpected end of file");
}




void Syntaxer::Start()
{
	if (!StrEq(list->str, "begin")){
		err.ThrowException(list, "expected 'begin'");
	}
	Next();
	Body();
	if (!StrEq(list->str, "end"))
		err.ThrowException(list, "expected 'end'");
}

void Syntaxer::Body()
{
	while (!StrEq(list->str, "end")){
		Command();
		Next();
	}
}

void Syntaxer::Command()
{
	if (list->Type==lex_point)
		Next();
	Execute();
	if (!StrEq(list->str, ";"))
		err.ThrowException(list, "expected ';'");
}


void Syntaxer::Execute()
{
	if (StrEq(list->str, "if")){
		Next();
		Expression();
		if (!StrEq(list->str, "then"))
			err.ThrowException(list, "expected 'then'");
		Next();
		if (StrEq(list->str, "begin")){
			Start();
			Next();
		}else
			Execute();
	}else if (StrEq(list->str, "jmp")){
		Next();
		if (list->Type!=lex_point)
			err.ThrowException(list, "expected type 'point'");
		Next();
	}else if (list->Type==lex_variable){
		Var();
		if (!StrEq(list->str, ":="))
			err.ThrowException(list, "expected ':='");
		Next();
		Expression();
	}else if (list->Type==lex_function){
		Func();
	}
}

void Syntaxer::Func()
{
	if (StrEq(list->str, "?turn") ||
		StrEq(list->str, "?info") ||
		StrEq(list->str, "?market") ||
		StrEq(list->str, "?build") ||
		StrEq(list->str, "?endturn") ||
		StrEq(list->str, "?my_id") ||
		StrEq(list->str, "?raw_price") ||
		StrEq(list->str, "?prod_price"))
	{
		Next();
	}
	}else if (StrEq(list->str, "?buy") ||
		StrEq(list->str, "?sell") ||
		StrEq(list->str, "?raw"))
	{
		Next();
		Expression();
		Expression();
	}else if (StrEq(list->str, "?print"))
	{
		Next();
		Arg();
	}else
		err.ThrowException(list, "expected type 'function'");
}

void Syntaxer::Arg()
{
	if (list->Type==lex_variable)
		Var();
	else if (list->Type==lex_string)
		Next();
	else 
		err.ThrowException(list, 
				"expected type 'string' or type 'var'");
}

void Syntaxer::Var()
{
	if (list->Type!=lex_variable  || (getlen(list->str)<=1))
		err.ThrowException(list, "expected type 'var'");
	Next();
	Mas();
}

void Syntaxer::Mas()
{
	if (StrEq(list->str, "[")){
		Next();
		Expression();
		if (!StrEq(list->str, "]"))
			err.ThrowException(list, "expected ']'");
		Next();
	}
}


void Syntaxer::Expression()
{
	Left();
	Right();
}

void Syntaxer::Left()
{
	Part1();
	Part2();
}

void Syntaxer::Right()
{
	if (StrEq(list->str, ">") ||
		StrEq(list->str, "<") ||
		StrEq(list->str, "="))
	{
		Next();
		Expression();
	}
}

void Syntaxer::Part1()
{
	Base1();
	Base2();
}

void Syntaxer::Part2()
{
	if (StrEq(list->str, "+") ||
		StrEq(list->str, "-") ||
		StrEq(list->str, "|"))
	{
		Next();
		Part1();
	}
}

void Syntaxer::Base1()
{
	if (StrEq(list->str, "!")){
		Next();
		Expression();
	}else if (StrEq(list->str, "(")){
		Next();
		Expression();
		if (!StrEq(list->str, ")"))
			err.ThrowException(list, "expected ')'");
		Next();
	}else if (StrEq(list->str, "-")){
		Next();
		Expression();
	}else if (list->Type==lex_variable || 
			  list->Type==lex_number)
		Next();
	else err.ThrowException(list, "bad expression");
}

void Syntaxer::Base2()
{
	if (StrEq(list->str, "*") ||
	StrEq(list->str, "/") ||
	StrEq(list->str, "%") ||
	StrEq(list->str, "&"))
	{
		Next();
		Left();
	}

}

void Syntaxer::GetList(struct Lexeme *first)
{
	list=first;
	Start();
}

void Exception::ThrowException(struct Lexeme *lex, const char *str)
{
	lexeme=lex;
	message=str;
	throw(this);
}

//int is_function
