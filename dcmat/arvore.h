#ifndef ARVORE_H
#define ARVORE_H

/*
 *	Modulo responsavel pela manipulacao da Arvore.
 * 	Para a resolucao do DCMAT, a Arvore Contem Nos (representando variaveis) com os seguintes atributos:
 * 		- Valor (da variavel)
 * 		- Nome (que o usuario deu para a variavel)
 * 		- Tipo (pode ser de diferentes tipos, como FLOAT ou MATRIZ, por exemplo)
 * 
 * 	Sendo assim, este modulo contem metodos como:
 *  	- insercao e criacao de Arvores e Nos;
 * 		- remocao de Arvores e Nos;
 * 		- atualizacoes;
 * 		- CASOS ESPECIAIS: Metodos especiais, como calculo de dois nos da Arvore ou de RPN;
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "bison.tab.h"
#include "variaveis.h"
#include "hash.h"


typedef struct TreeNode {
	char* nome;
	float num; // Conteudo
	int tipo_no;
	struct TreeNode* no_esquerdo;
	struct TreeNode* no_direito;
} TreeNode;



// Metodos basicos:

TreeNode *criar_No(int i, TreeNode *no_esquerdo, TreeNode *no_direito, float nmr);

TreeNode *alterar_ID_Arvore(int i, TreeNode *no_esquerdo, TreeNode *no_direito, char* nome);

void remover_Arvore(TreeNode *removendo);



// METODOS ESPECIAIS PARA O DCMAT INSERIDOS:

/* Calculo dos Nos */
float calcular_No(TreeNode *node, float valor);

/* Tratar RPN */
void arvore_RPN(TreeNode *rpn);

#endif
