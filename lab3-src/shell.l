
/*
 *
 * CS-252 Fall 2013
 * shell.l: lexical analyzer for shell
 * You have to extend it.
 *
 */

%{

#include <string.h>
#include "y.tab.h"

%}

%%

\n 	{
		return NEWLINE;
	}

[ \t] 	{
		/* Discard spaces and tabs */
     	}	

">" 	{
		return GREAT;
	}

"<"	{
		return LESS;
	}
">>"	{
		return GREATGREAT;
	}
"<<"	{
		return LESSLESS;
	}
">&"	{
		return GREATAMPERSAND;
	}
">>&"	{
		return GREATGREATAMPERSAND;
	}
"|"	{
		return PIPE;
	}
"&"	{
		return AMPERSAND;
	}



[^ \t\n][^ \t\n]*  {
		/* Assume that file names have only alpha chars */
		yylval.string_val = strdup(yytext);
		return WORD;
	}

.	{
		/* Invalid character in input */
		return NOTOKEN;
	}

%%
	
