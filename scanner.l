%{
#include "tn.h"
#include "sym_table_lab.h"
#include "hash_func.h"
%}

letter	[a-zA-Z_]
digit	[0-9]

%%
"const"					return(TCONST);
"int"			        		return(TINT);
"float"					return(TFLOAT);
"return"			    		return(TRETURN);
"void"		            		return(TVOID);
"while"		        		return(TWHILE);
"if"	                    			return(TIF);
"else"						return(TELSE);
"+"             				return(TADD);
"-"             				return(TSUB);
"*"             				return(TMUL);
"/"             				return(TDIV);
"%"             				return(TMOD);
"!"             				return(TNOT);
"&&"            				return(TAND);
"||"            					return(TOR);
"=="						return(TEQUAL);
"!="						return(TNOTEQU);
"<="						return(TLESSE);
">="						return(TGREATE);
"<"             				return(TLESS);
">"             				return(TGREAT);
"++"						return(TINC);
"--"						return(TDEC);
"="             				return(TASSIGN);
"+="						return(TADDASSIGN);
"-="						return(TSUBASSIGN);
"*="						return(TMULASSIGN);
"/="						return(TDIVASSIGN);
"%="						return(TMODASSIGN);
"("             				return(TLPAREN);
")"             				return(TRPAREN);
"{"             				return(TLBRACE);
"}"             				return(TRBRACE);
","						return(TCOMMA);
"["						return(TLBRACKET);
"]"						return(TRBRACKET);
";"						return(TSEMI);
"/*"([^*]|"*"+[^*/])*"*"+"/"    		{
                                    			startLineNumber = lineNumber;
                                    			for(int i = 0; i<yyleng; i++)
                                    			{
                                        			if(yytext[i] == '\n')
                                            			lineNumber++;
                                    			}
                                    			return(TCOMMENT);
                                		} 
"//".*                          		{
                                    			startLineNumber = lineNumber; 
                                    			return(TCOMMENT);
                                		}
{letter}({letter}|{digit})*			{
    							if(yyleng >= 15)
    							{
    								ReportError(illid_long);
    								return(TERROR);
    							}
    							SymbolTable(yytext, yyleng);
    							return(TIDENT);
						}
[+|-]?([1-9][0-9]*|0([0-7]+|(x|X)[0-9A-Fa-f]+)?)	return(TNUMBER); //정수 상수
{digit}+"."{digit}+(e[+-]?{digit}+)?		return(TFNUMBER); //실수 상수
{digit}+[A-Za-z0-9_]+			{
							ReportError(illid_digit); 
							return(TERROR);
						}
"\n"     					lineNumber++;
[ \t\r]   					;
.                       				{ 
							ReportError(illch);
							return(TERROR);
						} 
%%

int yywrap()
{
	return 1;
}
