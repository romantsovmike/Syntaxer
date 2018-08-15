#include "Usefull.hpp"
#include "Lexer.hpp"
#include "Syntaxer.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

Lexer::Lexer()
{
	state=start;
	str_num=1;
	curr_lex=new char[1];
	curr_lex[0]=0;
	curr_type=NULL;
	ZeroLex=new Lexeme;
	ZeroLex->next=NULL;
	CurrLex=ZeroLex;
}

Lexer::~Lexer()
{
	struct Lexeme *Current, *Temp;
	Current=ZeroLex->next;;
	while (Current){
		Temp=Current->next;
		delete [] Current->str;
		delete Current;
		Current=Temp;
	}
	delete ZeroLex;
}


struct Lexeme *Lexer::GiveList(){return ZeroLex->next;}


void Lexer::Identify(char c)
{
	symb=c;
	switch(state){
		case start:
			AnalyzeFirst();
			break;
		case number:
			AnalyzeNumber();
			break;
		case special:
			AnalyzeSpecial();
			break;
		case string:
			AnalyzeString();
			break;
		case keyword:
			AnalyzeKeyword();
			break;
		case eq:
			AnalyzeEq();
			break;
		default:
			printf("Error Identify, %d\n", str_num);
			exit(1);
	}
}

void Lexer::AnalyzeFirst()
{
	if (symb==':'){
		if (getlen(curr_lex))
			Output();
		curr_lex=addChar(curr_lex,symb);
		state=eq;
		return;
	}

	if (CheckSep(symb)){
		AnalyzeSeparator();
		return;
	}

	if ((symb==' ') || (symb=='\t')){
		if (getlen(curr_lex)){
			Output();
			return;
		}
		state=start;
		return;
	}

	if (symb=='\n'){
		str_num++;
		return;
	}
	if (symb=='$'){
		curr_lex=addChar(curr_lex,symb);
		curr_type="variable";
		CurrType=lex_variable;
		state=special;
		return;
	}
	if (symb=='?'){
		curr_lex=addChar(curr_lex,symb);
		curr_type="function";
		CurrType=lex_function;
		state=special;
		return;
	}
	if (symb=='@'){
		curr_lex=addChar(curr_lex,symb);
		curr_type="point";
		CurrType=lex_point;
		state=special;
		return;
	}
	if (symb=='"'){
		curr_type="string";
		state=string;
		CurrType=lex_string;
		return;
	}
	if (symb<='9' && symb>='0'){
		curr_type="number";
		CurrType=lex_number;
		state=number;
		curr_lex=addChar(curr_lex,symb);
		return;
	}
	if ((symb<='Z' && symb>='A') || (symb<='z' && symb>='a')){
		curr_type="keyword";
		CurrType=lex_string;
		state=keyword;
		curr_lex=(addChar(curr_lex,symb));
		return;
	}
}



void Lexer::AnalyzeSpecial()
{
	if ((symb<='z' && symb>='a') ||
		(symb<='Z' && symb>='A') ||
		(symb<='9' && symb>='0') ||
		(symb=='_'))
	{
		curr_lex=addChar(curr_lex,symb);
		state=special;
		return;
	}else{
		if (symb=='\n'){
			Output();
			str_num++;
			return;
		}
		if (CanSeparate(symb)){
			Output();
			AnalyzeFirst();
			return;
		}
	}
	printf("Error Special\n");
	exit(1);
}



void Lexer::AnalyzeString()
{
	if ((symb=='\n') || (symb==EOF)){
		printf("String error, %d\n",str_num);
		exit(1);
	}
	if (symb=='"'){
		Output();
		return;
	}else{
		curr_lex=addChar(curr_lex, symb);
		state=string;
		return;
	}
}

void Lexer::AnalyzeEq()
{
	if (symb=='='){
		curr_type="assignment";
		curr_lex=addChar(curr_lex,symb);
		Output();
		return;
	}else{
		curr_type="separator";
		Output();
		AnalyzeFirst();
		return;
	}
	printf("Error EQ\n");
	exit(1);
}

void Lexer::AnalyzeNumber()
{
	if (symb<='9' && symb>='0'){
		curr_lex=addChar(curr_lex, symb);
		state=number;
		return;
	}else{
		if (symb=='\n'){
			str_num++;
			Output();
			return;
		}
		if (CanSeparate(symb)){
			Output();
			AnalyzeFirst();
			return;
		}
		printf("Error number\n");
		exit(1);
	}	
}

void Lexer::AnalyzeSeparator()
{
	if (getlen(curr_lex))
		Output();
	curr_lex=addChar(curr_lex,symb);
	curr_type="separator";
	Output();
}


void Lexer::AnalyzeKeyword()
{
	if (symb<='z' && symb>='a'){
		curr_lex=addChar(curr_lex,symb);
		state=keyword;
		return;
	}else{
		if (symb=='\n' || symb==EOF){
			if (CheckKey(curr_lex)){
				str_num++;
				Output();
				return;
			}
			printf("Error keyword, %d\n", str_num);
			exit(1);
		}
		if (CanSeparate(symb)){
			Output();
			AnalyzeFirst();
			return;
		}
	}
	printf("Error keyword\n");
	exit(1);
}


void Lexer::Output()
{
	if (!curr_lex)
		return;
	CurrLex->next=new Lexeme;
	CurrLex=CurrLex->next;
	CurrLex->next=NULL;
	CurrLex->str=FillBuf(curr_lex);
//	printf("%s\n", curr_lex);
	CurrLex->type=curr_type;
	CurrLex->Type=CurrType;
	CurrLex->str_num=str_num;
	delete [] curr_lex;
	curr_type=NULL;
	curr_lex=new char[1];
	curr_lex[0]=0;
	state=start;
	return;
}
