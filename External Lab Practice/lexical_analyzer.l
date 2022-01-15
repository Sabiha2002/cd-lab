%{
	#include<math.h>
	FILE *fp;
%}

digit [0-9]+
header "#include<"[a-z]+".h>"
inbuilt [\t]*"printf(".*")"|[\t]*"scanf(".*")"|[\t]*"clrscr()"|[\t]*"exit(".+")"|[\t]*"getch()"
comment [\t]*"/*".*"*/"[\t]*\n
main_function "void main()"
function [\t]*[a-zA-Z]+"(".*")"[\t]*\n
datatype [\t]*"int"|[\t]*"char"|[\t]*"float"
operator "+"|"-"|"*"|"/"|"%"
terminator ";"
bracket1 [\t]*"{"[\t]*
bracket2 [\t]*"}"[\t]*
loop [\t]*"if(".*")"|[\t]*"else"|[\t]*"for"|[\t]*"while"|[\t]*"do"
relational [\t]*"<"|">"|"<="|">="|"=="|"!="
assignment [\t]*"="
logical [\t]*"&&"|"||"
word [a-z]+[a-z0-9]*

%%
{digit} {printf("\nNumbers :: %s", yytext);}
{header} {printf("\nHeader file :: %s", yytext);}
{inbuilt} {printf("\nFunction :: %s", yytext);}
{comment} {printf("\nComment :: %s", yytext);}
{main_function} {printf("\nMain function :: %s", yytext);}
{function} {printf("\nUser function :: %s", yytext);}
{datatype} {printf("\nData type :: %s", yytext);}
{operator} {printf("\nOperator :: %s", yytext);}
{terminator} {printf("\nTerminator :: %s", yytext);}
{bracket1} {printf("\nOpening curly bracket :: %s", yytext);}
{bracket2} {printf("\nClocing curly bracket :: %s", yytext);}
{relational} {printf("\nRelational operator :: %s", yytext);}
{assignment} {printf("\nAssignment Operator :: %s", yytext);}
{loop} {printf("\nLoop statement :: %s", yytext);}
{logical} {printf("\nLogical Operator :: %s", yytext);}
{word} {printf("\nVariables :: %s", yytext);}

%%

int main(int argc, char *argv[]){
	fp = fopen(argv[1], "r");
	if(fp!=NULL){
		yyin = fp;
		yylex();
	}
	return 0;
}

