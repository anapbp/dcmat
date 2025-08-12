#ifndef MATRIZ_H
#define MATRIZ_H

/*
 *	Modulo responsavel pela manipulacao da Matrizes.
 * 	As matrizes serao tratadas conforme especificado no documento do DCMAT, apresentando metodos como:
 *  	- criar matriz;
 * 		- zerar matriz;
 * 		- operacoes basicas: adicao, multiplicacao, subtracao, divisao;
 * 		- Tratamento de sistemas lineares;
 * 		- CASOS ESPECIAIS: 
 * 				- tratamentos de erros especificos para o DCMAT (se for matriz quadrada ou nao, ter solucao ou nao);
 * 				- impressoes em formato especifico;
 */

#include <stdio.h>
#include <stdlib.h>


typedef struct Matriz {
	float **mat;
	int linhas;
	int colunas;
} Matriz;


Matriz* criar_Matriz(float** mat, int linhas, int colunas);

void imprimir_Matriz(Matriz* mat, int floatPrecision);

Matriz* adicao_De_Matriz(Matriz* m1, Matriz* m2);

Matriz* subtracao_De_Matriz(Matriz* m1, Matriz* m2);

Matriz* multiplicacao_De_Matriz(Matriz* m1, Matriz* m2);

Matriz* multiplicacao_Escalar_De_Matriz(Matriz* m, float scalar);

int checar_Matriz_Quadrada(Matriz* m);

int checar_Sistema_Linear_Matriz(Matriz* m);

float calcular_determinante_Matriz(Matriz* m, int n);

Matriz* calcular_Sistema_Linear_Matriz(Matriz* m);

void imprimir_Sistema_Linear_Matriz(Matriz* m, int precision);

void zerar_Matriz(float** mat, int li, int co);

void free_Matriz(Matriz* m);

#endif
