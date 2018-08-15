#include "Usefull.hpp"
#include "Lexer.hpp"
#include "Syntaxer.hpp"
#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE* fd;
	char c;
	Lexer L;
	fd=FileOpen(argv[1]);
	while ((c=getc(fd))!=EOF)
		L.Identify(c);
	fclose(fd);
	Syntaxer S;
	try{
		S.GetList(L.GiveList());
	}catch (Exception *e){
		printf ("Error: %s, %d\n", e->message, e->lexeme->str_num);
		return 1;
	}
	printf("Synthax is ok\n");
	return 0;
}
