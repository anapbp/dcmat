%option noyywrap


%{
	#include <bison.tab.h>

	int erroLexico = 0;

	void input_scanner(char *input){
		yy_scan_string(input);
	}
	void empty_buffer(){
		yy_delete_buffer(YY_CURRENT_BUFFER);
	}
	
%}



%%
" " 	{}
"+"		{ return ADD; }
"-" 	{ return SUB; }
"*"		{ return MULT;}
"/"		{ return DIV; }
"^" 	{ return EXP; }
"%"		{ return MOD; }
"("		{ return PARENTERES_ESQ; }
")"		{ return PARENTERES_DIR; }
":" 	{ return COLON;}
"=" 	{ return IGUAL; }
":=" 	{ return ATRIBUICAO; }
"[" 	{ return COLCHETES_ESQ; }
"]" 	{ return COLCHETES_DIR; }
";"		{ return SEMICOLON; }
"," 	{ return COMMA; }

about                   { return ABOUT; }
abs                     { return ABS; }
axis                    { return AXIS; }
connected_dots          { return CONNECTED_DOTS; }
cos                     { return COS; }
determinant             { return DETERMINANT; }
erase                   { return ERASE; }
float                   { return FLOAT_TOKEN; }
h_view                  { return H_VIEW; }
integral_steps          { return INTEGRAL_STEPS; }
integrate               { return INTEGRATE; }
linear_system           { return LINEAR_SYSTEM; }
matrix                  { return MATRIX; }
off                     { return OFF; }
on                      { return ON; }
plot                    { return PLOT; }
precision               { return PRECISION; }
quit                    { return QUIT; }
reset                   { return RESET; }
rpn                     { return RPN; }
sen                     { return SEN; }
set                     { return SET; }
settings				{ return SETTINGS; }
show					{ return SHOW; }
solve                   { return SOLVE; }
sum                     { return SUM; }
symbols                 { return SYMBOLS; }
tan                     { return TAN; }
v_view                  { return V_VIEW; }
[xX]                    { return X; }
[pP][iI] 				{ return PI; }
[Ee] 					{ return EULER; }

[0-9]+ 					{ yylval.inteir = atoi(yytext); return INTEIRO; }
[0-9]+"."[0-9]+ 		{ yylval.ft = atof(yytext); return FLOAT;}
[a-zA-Z]+[_0-9a-zA-Z]*	{ yylval.strg = strdup(yytext); return IDENTIFIER; }
("\n"|"\r")             { return EOL; }
.						{ yylval.strg = strdup(yytext); erroLexico=1; return ERROR; }
<<EOF>> 				{ return EOL; }
%%
