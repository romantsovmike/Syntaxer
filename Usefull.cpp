#include "Usefull.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

//----Getting length of the string----//
int getlen(char *str)
{
	int len=0;
	while (str[len]){
		len++;
	}
	return len;
}

//----Filling buffer with string in brackets----//
char* FillBuf(char *str)
{
	int len=getlen(str), i=0;
	char *buf=new char[len+1];
	while (str[i]){
		buf[i]=str[i];
		i++;
	}
	buf[i]=0;
	return buf;
}
//----Checks if c=one of separators----//
int CheckSep(char c)
{
	return (c=='-' || c=='+' || c=='=' || c=='(' || 
			c==')' || c=='<' || c=='>' || c=='/' || 
			c=='*' || c=='%' || c=='[' || c==']' ||
			c=='&' || c=='|' || c==',' || c==';');
}

//----Adds symbol to string----//
char* addChar(char *str, char symb)
{
	int len=0;
	len=getlen(str);
	char *buf=new char[len+2];
	int i=0;
	while (str[i]){
		buf[i]=str[i];
		i++;
	}
	buf[i]=symb;
	i++;
	buf[i]=0;
	delete [] str;
	return buf;
}

//----Checks if strings are equivalent----//
int StrEq(char *str, const char *key)
{
	char *lexeme=str;
	int i=0, len_str=getlen(lexeme);
	while (key[i])
		i++;
	if (len_str!=i)
		return 0;
	for (i=0; i<len_str; i++){
		if ((lexeme[i])!=(key[i]))
			return 0;
	}
	return 1;
}

//----Checks if str is one of keywords----//
int CheckKey(char *str)
{
	return (StrEq(str, "if") || StrEq(str, "jmp") ||
			StrEq(str, "buy") || StrEq(str, "sell") ||
			StrEq(str, "prod") || StrEq(str, "build") ||
			StrEq(str, "print") || StrEq(str, "endturn") ||
			StrEq(str, "then") || StrEq(str, "begin") ||
			StrEq(str, "end"));
}

int CanSeparate(char symb)
{
	return ((CheckSep(symb)) || (symb == ' ') ||
			(symb == '\t') || (symb == ':') ||
			(symb==EOF));
}


//----Prints list of lexemes----//
/*void Print(struct Lexeme *ZeroLex)
{
	struct Lexeme *Current=ZeroLex->next;
	while (Current){
		printf("[%s, %s, %d]\n",
			Current->str, Current->type, Current->str_num);
		Current=Current->next;
	}

}
*/
//----Opens file----//
FILE* FileOpen(char *filename)
{
	FILE *fd;
	if ((fd=fopen(filename, "r")))
		return fd;
	printf("Error File\n");
	exit(1);
}
