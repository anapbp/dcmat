%{
	#include <stdbool.h>
	#include <stdio.h>
    #include <stdlib.h>
	#include <math.h>

	#include "bison.tab.h"
	#include "arvore.h"
	#include "hash.h"
    #include "grafico.h"
	#include "integral.h"
	#include "matriz.h"
	#include "comandos.h"


	// Pegando do flex:
	extern int yylex();
	extern char *yytext;
	extern int erroLexico;

	// Na forma padrao do documento do DCMAT:
	float h_view_lo = -6.500000;
	float h_view_hi = 6.500000;
	float v_view_lo = -3.500000;
	float v_view_hi = 3.500000;
	int float_precision = 6;
	int integral_steps = 1000;
	bool draw_axis = true;
	bool erase_plots = true;
	bool draw_connected_dots = false;
    char tela[EIXO_Y][EIXO_X]; // Tela para impressao dos graficos com tamanho padrao

	// Inicializando arvores e tabelas:
	TreeNode* arvore = NULL;
	Hashtable* hash = NULL;
	varTypes* cmc = NULL;
	float** mat;
	Matriz* auxmat = NULL;
	char buffer[10000];

	// Auxiliares:
	int auxL = 0;
	int auxC = 0;
	int auxML = 0;
	int auxMC = 0;
	int ext = 0;
	int UF = 0;
	int auxlo, auxi =0;



	void input_scanner(char *input);

	void empty_buffer();

	void yyerror(void *s) {	

		if (erroLexico) {
			erroLexico = 0;
			printf("Invalid Symbol: %s\n", yytext);
		} else if (strcmp(yytext, "\n") == 0) {
			printf("Syntax Error: Incomplete Command\n");
		} else {
			printf("Syntax Error: [%s]\n", yytext);
		}

	};

	// Colocando nos valores padrao:
	void reset_Settings_Comando() {
		h_view_lo = -6.500000;
		h_view_hi = 6.500000;
		v_view_lo = -3.500000;
		v_view_hi = 3.500000;
		float_precision = 6;
		integral_steps = 1000;
		draw_axis = true;
		erase_plots = true;
		draw_connected_dots = false;
	}

%}



%union{
	void *arvore;
	void *variavel;
	int inteir;
	float ft;
	char *strg;
}



%token ADD
%token SUB
%token MULT
%token DIV
%token EXP
%token MOD
%token PARENTERES_ESQ
%token PARENTERES_DIR
%token COLON
%token IGUAL
%token ATRIBUICAO
%token COLCHETES_ESQ
%token COLCHETES_DIR
%token SEMICOLON
%token COMMA

%token ABOUT
%token ABS
%token AXIS
%token CONNECTED_DOTS
%token COS
%token DETERMINANT
%token EULER
%token ERASE
%token FLOAT_TOKEN
%token H_VIEW
%token INTEGRAL_STEPS
%token INTEGRATE
%token LINEAR_SYSTEM
%token MATRIX
%token OFF
%token ON
%token PI
%token PLOT
%token PRECISION
%token QUIT
%token RESET
%token RPN
%token SEN
%token SET
%token SETTINGS
%token SHOW
%token SOLVE
%token SUM
%token SYMBOLS
%token TAN
%token V_VIEW
%token X
%token EOL


%type <arvore> FatoracaoI

%type <arvore> RpnI
%type <arvore> ExponenciacaoI
%type <arvore> TermoI
%type <arvore> NumeroLiteralI

%type <variavel> Atribuicao
%type <variavel> NumeroLiteral
%type <variavel> Matematica
%type <variavel> Fatoracao
%type <variavel> Termo
%type <variavel> Exponenciacao
%type <variavel> Comparacao
%type <variavel> CalcularMatriz

%token <inteir> INTEIRO

%token <ft> FLOAT
%type <ft> SequenciaDeNumeros
%type <ft> Sequencia
%type <ft> SequenciaI

%token <strg> IDENTIFIER
%token <strg> ERROR


%start iniciar

%%
iniciar:
	| Matematica EOL { 
			if ($1 == NULL) {return 0;} 
			imprimir_Valor_Da_Variavel($1, float_precision); 
			return 0;
		}
	| Dado SEMICOLON EOL { return 0; }
	| EOL { return 0; }
;


Dado:
	| IDENTIFIER { 
			imprimir_Valor_E_Nome_Da_Variavel(procurar_Na_Tabela_Hash(hash,$1), float_precision, $1); 
		}
	| IDENTIFIER ATRIBUICAO Atribuicao { 
			if($3 == NULL){return 0;} atualizar_Tabela_Hash(hash, $1, $3); printf("\n"); imprimir_Valor_Da_Variavel($3, float_precision); printf("\n");
		}
	| ABOUT {
			printf("\n"); show_About_Comando();
		}
	| MATRIX IGUAL Comparacao { cmc = $3;}
	| Funcoes { }
	| Resetar { }
	| SHOW Opcoes { }
	| PLOT Plotar { }
	| SET Intervalo { }
	| CalcularMatriz { }
	| QUIT { ext = 1; return 0; }
;


Funcoes: INTEGRATE PARENTERES_ESQ NumeroLiteral COLON NumeroLiteral COMMA RpnI PARENTERES_DIR {
            float li = *getFloat($3);
            float lo = *getFloat($5);
            int p = integral_steps;  
            arvore = $7;
            float resultado = calcular_Integral(arvore, hash, li, lo, p, float_precision);
        }
	| RPN PARENTERES_ESQ RpnI PARENTERES_DIR { 
			arvore = $3; 
			printf("Expression in RPN format:\n"); 
			arvore_RPN(arvore);
			printf("\n");
		}
	| SUM PARENTERES_ESQ IDENTIFIER COMMA Limites COMMA RpnI PARENTERES_DIR { arvore = $7;  } 
;


Opcoes: SYMBOLS { 
			imprimir_Tabela_Hash(hash); 
		}
	| SETTINGS {
			printf("\n"); 
			show_Settings_Comando(h_view_lo, h_view_hi, v_view_lo, v_view_hi,
                   				  float_precision, integral_steps, draw_axis, erase_plots, 
								  draw_connected_dots);
		}
	| MATRIX { 
			if(cmc == NULL) {
				printf("No Matrix defined!\n");
				return 0;
			} 
			imprimir_Matriz(getMatriz(cmc), float_precision);
		}
;


CalcularMatriz: SOLVE LINEAR_SYSTEM {
			if(cmc == NULL) {
				printf("No Matrix defined!\n");
				return 0;
			}
			if(!checar_Sistema_Linear_Matriz(getMatriz(cmc))){
				printf("Matrix format incorrect!\n");
				return 0;
			} 
			imprimir_Sistema_Linear_Matriz(calcular_Sistema_Linear_Matriz(getMatriz(cmc)), float_precision);
		}
	|SOLVE DETERMINANT { 
			if(cmc == NULL) {
				printf("No Matrix defined!\n");
				return 0;
			}
			if(!checar_Matriz_Quadrada(getMatriz(cmc))){
				printf("Matrix format incorrect!\n"); 
				return 0;
			} 
			
			printf("%.*f\n", float_precision, calcular_determinante_Matriz(getMatriz(cmc), (getMatriz(cmc))->linhas ));
		}
;


Resetar: RESET SETTINGS { reset_Settings_Comando(); }
;


Intervalo: 
	AXIS set_axis { }
	| H_VIEW set_h_view { }
	| V_VIEW set_v_view { }
	| ERASE PLOT set_erase_plot { }
	| FLOAT_TOKEN PRECISION INTEIRO { 
			if($3 < 0 || $3 > 8) {
				printf("ERROR: float precision must be from 0 to 8\n"); 
				return 0;
			} 
			float_precision = $3;
		}
	| INTEGRAL_STEPS NumeroLiteral { 
			if(*getFloat($2) <= 0){
				printf("ERROR: integral_steps must be a positive non-zero integer\n"); 
				return 0;
			} 
			integral_steps = *getFloat($2);
		}
;


set_h_view: NumeroLiteral COLON NumeroLiteral { 
			if(*getFloat($1) >= *getFloat($3)){
				printf("ERROR: h_view_lo must be smaller than h_view_hi\n"); 
				return 0;
			}
				h_view_lo = *getFloat($1);
				h_view_hi = *getFloat($3);
		}
;


set_v_view: NumeroLiteral COLON NumeroLiteral {
			if(*getFloat($1) >= *getFloat($3)){
				printf("ERROR: v_view_lo must be smaller than v_view_hi\n"); 
				return 0;
			}
			v_view_lo = *getFloat($1);
			v_view_hi = *getFloat($3);
		}
;


Limites: NumeroLiteral COLON NumeroLiteral {
			if(*getFloat($1) >= *getFloat($3)){
				printf("ERROR: lower limit must be smaller than upper limit\n"); 
				return 0;
			}
				auxlo = (int)*getFloat($1);
				auxi = (int)*getFloat($3);
		}
;


NumeroLiteral: 
	FLOAT { float* wrapper= malloc(sizeof(float)); *wrapper= $1; varTypes* value = criar_Nova_Variavel(1,wrapper); $$ = value; } 
	| ADD FLOAT { float* wrapper= malloc(sizeof(float)); *wrapper= $2; varTypes* value = criar_Nova_Variavel(1,wrapper); $$ = value; } 
	| SUB FLOAT { float* wrapper= malloc(sizeof(float)); *wrapper= -$2; varTypes* value = criar_Nova_Variavel(1,wrapper); $$ = value; }
	| PI { float* wrapper = malloc(sizeof(float)); *wrapper = 3.14159265; varTypes* value = criar_Nova_Variavel(1,wrapper); $$ = value;} 
	| EULER { float* wrapper = malloc(sizeof(float)); *wrapper = 2.71828182; varTypes* value = criar_Nova_Variavel(1,wrapper); $$ = value; } 
	| INTEIRO { float* wrapper= malloc(sizeof(float)); *wrapper= (float)$1; varTypes* value = criar_Nova_Variavel(1,wrapper); $$ = value; }
	| SUB PI { float* wrapper = malloc(sizeof(float)); *wrapper = -3.14159265; varTypes* value = criar_Nova_Variavel(1,wrapper); $$ = value; }  
	| ADD INTEIRO { float* wrapper= malloc(sizeof(float)); *wrapper= (float)$2; varTypes* value = criar_Nova_Variavel(1,wrapper); $$ = value; }
	| SUB INTEIRO { float* wrapper= malloc(sizeof(float)); *wrapper= (float)(-$2); varTypes* value = criar_Nova_Variavel(1,wrapper); $$ = value; }
	| SUB EULER { float* wrapper = malloc(sizeof(float)); *wrapper = -2.71828182; varTypes* value = criar_Nova_Variavel(1, wrapper); $$ = value; }
	| IDENTIFIER {
            if(procurar_Na_Tabela_Hash(hash,$1) == NULL) {
                printf("Undefined Symbol [%s]\n", $1); 
                UF = 1;
                $$ = NULL;
            } else { 
                $$ = procurar_Na_Tabela_Hash(hash,$1);
            }; 
        }
		| SUB IDENTIFIER {
            varTypes* value = procurar_Na_Tabela_Hash(hash, $2);
            if (value == NULL) {
                printf("Undefined Symbol [%s]\n", $2);
                UF = 1;
                $$ = NULL;
            } else {
                $$ = negativar_Variavel(value);
            } 
        }
		| X { printf("The x variable cannot be present on expressions.\n"); return 0;}
        | PARENTERES_ESQ Matematica PARENTERES_DIR { 
                  $$ = $2; 
              }
;


Plotar:  { printf("No function defined!\n"); }
	| PARENTERES_ESQ RpnI PARENTERES_DIR { 
        arvore = $2; 
        bool definido_s_n = true;
		
        if(arvore->tipo_no == IDENTIFIER) {
            varTypes* value = procurar_Na_Tabela_Hash(hash, $2);

                if(value == NULL) {
                    printf("Undefined Symbol [%s]\n", arvore->nome);
                    definido_s_n = false;
                }
        }

        if(definido_s_n) {
            plotar_Grafico(arvore, h_view_lo, h_view_hi, v_view_lo, v_view_hi, draw_axis, erase_plots, tela);
        }
    }
;

			
set_axis: 
	ON { draw_axis=true; }
	| OFF { draw_axis=false; }
;

set_erase_plot: 
	ON { erase_plots=true;}
	| OFF { erase_plots=false; }
;


Atribuicao: 
	NumeroLiteral { $$ = $1;}
	| Comparacao { $$ = $1;}
	| Matematica { $$ = $1;}
;


Matematica: 
	Fatoracao { $$=$1; }
	| Matematica ADD Fatoracao { 
			varTypes* val1 = $1; 
			varTypes* val2 = $3; 
			$$ = somar_Variaveis(val1,val2); 
		}
	| Matematica SUB Fatoracao { 
			varTypes* val1 = $1; 
			varTypes* val2 = $3; 
			$$ = subtrair_Variaveis(val1,val2); 
		}
;


Fatoracao: 
	Exponenciacao { $$ = $1; }
	| Fatoracao DIV Exponenciacao { 
			varTypes* val1 = $1; 
			varTypes* val2 = $3; 
			$$ = dividir_Variaveis(val1,val2); 
		}
	| Fatoracao MOD Exponenciacao { 
			varTypes* val1 = $1; 
			varTypes* val2 = $3; 
			$$ = modulo_Das_Variaveis(val1,val2); 
		}
	| Fatoracao MULT Exponenciacao { 
			varTypes* val1 = $1; 
			varTypes* val2 = $3; 
			$$ = multiplicar_Variaveis(val1,val2); 
		}
;


Exponenciacao: 
	Termo { $$ = $1; }
	|Exponenciacao EXP Termo { 
			varTypes* val1 = $1; 
			varTypes* val2 = $3; 
			$$ = elevar_Variaveis(val1,val2); 
		}
;


Termo: 
	NumeroLiteral { $$ = $1; }
	| ADD Termo { $$ = $2; } 
    | SUB Termo { $$ = negativar_Variavel($2); } 
	| ABS PARENTERES_ESQ Termo PARENTERES_DIR { $$ = absoluto_Variavel($3); }
	| SEN PARENTERES_ESQ Matematica PARENTERES_DIR { $$ = seno_Variavel($3); }
	| COS PARENTERES_ESQ Matematica PARENTERES_DIR { $$ = cosseno_Variavel($3); }
	| TAN PARENTERES_ESQ Matematica PARENTERES_DIR { $$ = tangente_Variavel($3); }
;


SequenciaDeNumeros: COLCHETES_ESQ Sequencia COLCHETES_DIR {   
			auxL++;
			auxMC = auxMC > auxC ? auxMC : auxC;
			auxML = auxL;
			auxC=0;
		}
;


Sequencia: 
	NumeroLiteral { 
			mat[auxL][auxC] = *getFloat($1); auxC++; 
		}
	| Sequencia COMMA NumeroLiteral { 
			mat[auxL][auxC] = *getFloat($3); auxC++;
		}
;


SequenciaI: 
	SequenciaDeNumeros {  }
	| SequenciaI COMMA SequenciaDeNumeros { }
;


Comparacao: COLCHETES_ESQ SequenciaI COLCHETES_DIR { 
			varTypes* dummy; 

			if(auxML>10||auxMC>10){
				matriz_Error(); 
				return 0;
			} 
			
			auxmat = criar_Matriz(mat,auxML,auxMC); 
			dummy = criar_Nova_Variavel(2,auxmat); 
			$$ = dummy;
		}
;


NumeroLiteralI: 
	FLOAT {$$ = criar_No(FLOAT, NULL, NULL, $1);}
	| X {$$ = criar_No(X, NULL, NULL, 0);}
	| PI {$$ = criar_No(FLOAT, NULL, NULL, 3.14159265);}
	| EULER {$$ = criar_No(FLOAT, NULL, NULL, 2.71828182);}
	| INTEIRO {$$ = criar_No(FLOAT, NULL, NULL, (float)$1);}
	| IDENTIFIER { $$ = alterar_ID_Arvore(IDENTIFIER, NULL, NULL, $1);}
;


RpnI: 
	FatoracaoI { $$=$1; }
	| RpnI ADD FatoracaoI { $$ = criar_No(ADD, $1, $3, 0); }
	| RpnI SUB FatoracaoI { $$ = criar_No(SUB, $1, $3, 0); }
;


FatoracaoI: 
	ExponenciacaoI { $$ = $1; }
	| FatoracaoI MULT ExponenciacaoI { $$ = criar_No(MULT, $1, $3, 0);}
	| FatoracaoI DIV ExponenciacaoI { $$ = criar_No(DIV, $1, $3, 0);}
	| FatoracaoI MOD ExponenciacaoI { $$ = criar_No(MOD, $1, $3, 0);}
;


ExponenciacaoI: 
	TermoI { $$ = $1; }
	|ExponenciacaoI EXP TermoI { $$ = criar_No(EXP, $1, $3, 0);}
;


TermoI: NumeroLiteralI { $$ = $1; }
	| COS PARENTERES_ESQ RpnI PARENTERES_DIR { $$ = criar_No(COS, $3, NULL, 0); }
	| SEN PARENTERES_ESQ RpnI PARENTERES_DIR { $$ = criar_No(SEN, $3, NULL, 0);}
	| TAN PARENTERES_ESQ RpnI PARENTERES_DIR { $$ = criar_No(TAN, $3, NULL, 0);}
	| ABS PARENTERES_ESQ TermoI PARENTERES_DIR { $$ = criar_No(ABS, $3, NULL, 0);}
	| SUB TermoI { $$ = criar_No(SUB, NULL, $2, 0); }
	| PARENTERES_ESQ RpnI PARENTERES_DIR { $$ = $2; }
;
%%


int main(int argc, char **argv){

    for (int i = 0; i < EIXO_Y; i++) {
        for (int j = 0; j < EIXO_X; j++) {
            tela[i][j] = ' ';
        }
    }


	mat = (float**)malloc(20*sizeof(float*));

	// Passando pela matriz
	for(int i = 0; i < 20; i++){
		mat[i] = (float*)malloc(20*sizeof(float));
	}


	hash = criar_Tabela_Hash();

	while(ext == 0){

		auxL = 0;
		auxC = 0;
		auxMC = 0;
		auxML = 0;

		zerar_Matriz(mat,20,20);
		printf(">");

		if(fgets(buffer, 10000, stdin) == NULL){
			break;
		}

		printf("\n");
		input_scanner(buffer);
		yyparse();
		empty_buffer();
		printf("\n");
	}

	// Liberando memoria:
	free_Tabela_Hash(hash);
	remover_Arvore(arvore);

	return 0;
}
