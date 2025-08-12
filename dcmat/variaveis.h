#ifndef VARIAVEIS_H
#define VARIAVEIS_H

/*
 *	Modulo responsavel pela manipulacao de Variaveis.
 * 	Este modulo ira tratar os possiveis problemas gerados pela unicidade de cada tipo de variavel,
 *  uma vez que o DCMAT conta com tipos diversos, como FLOAT ou MATRIZ, necessitando de um tratamento
 * 	especial para cada caso. 
 *  Sendo assim, para tratar a variavel, vamos levar em conta os seguintes atributos:
 * 		- A expressao que contem a variavel (porque, caso for "a-b" e "-b", os componentes irao se comportar
 * 		de forma diferente);
 * 		- o tipo (se for FLOAT, MATRIZ ou qualquer outro - no caso, valor invalido);
 * 			- OBS: como trata matrizes tambem, contara com o modulo auxiliar matriz.h.
 * 		- caso for FLOAT, o valor da variavel, caso for MATRIZ, a matriz correspondente a variavel;
 * 
 * 	Para isso, estao presentes os seguintes metodos:
 *  	- Operacoes basicas como adicao, subtracao, etc;
 * 		- Gets dos atributos;
 * 		- Criar nova variavel;
 * 		- Impressao dos valores;
 * 		- Operacoes trigonometricas;
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matriz.h"

typedef struct varTypes {
	int type; 
	float* f;
	char* exp;
	Matriz *m;
} varTypes;

varTypes* criar_Nova_Variavel(int type, void* content);

// Impressao:
void imprimir_Valor_Da_Variavel(varTypes* content, int precision);
void imprimir_Valor_E_Nome_Da_Variavel(varTypes* content,int precision, char* name);

// Gets:
char* getKey(varTypes* content);
float* getFloat(varTypes* a);
Matriz* getMatriz(varTypes* a);

// Trigonometria:
varTypes* seno_Variavel(varTypes* a);
varTypes* cosseno_Variavel(varTypes* a);
varTypes* tangente_Variavel(varTypes* a);

//math function between two varTypes variables
varTypes* somar_Variaveis(varTypes* a, varTypes* b);
varTypes* subtrair_Variaveis(varTypes* a, varTypes* b);
varTypes* multiplicar_Variaveis(varTypes* a, varTypes* b);
varTypes* dividir_Variaveis(varTypes* a, varTypes* b);
varTypes* elevar_Variaveis(varTypes* a, varTypes* b);
varTypes* modulo_Das_Variaveis(varTypes* a, varTypes* b);
varTypes* maximo_Das_Variaveis(varTypes* a, varTypes* b);
varTypes* negativar_Variavel(varTypes* a);
varTypes* absoluto_Variavel(varTypes* a);

#endif
