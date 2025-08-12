#ifndef HASH_H
#define HASH_H

/*
 *	Modulo responsavel pela manipulacao da Tabela Hash adaptada para o DCMAT.
 * 	Essa tabela ira conter:
 * 		- Uma variavel (especificada no modulo variavel.h, que trata operacoes utilizando 
 *        variaveis, bem como suas caracteristicas)
 * 		- Chave (para identificar determinada variavel)
 * 
 * 	Sendo assim, este modulo contem metodos como:
 *  	- Criar Tabela Hash;
 *      - Atualizar valores;
 * 		- Buscar pelo valor associado (chave);
 * 		- Remover e liberar;
 * 		- Imprimir a Tabela Hash atual;
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "variaveis.h"

// Definir tamanho:
#define TAMANHO 100
 


typedef struct Node {
    varTypes *var;
    char *chave;
    struct Node *prox;
} Node;




typedef struct Hashtable {
	Node **tabela; 
} Hashtable;



Hashtable *criar_Tabela_Hash();

void imprimir_Tabela_Hash(Hashtable *hasht);

void atualizar_Tabela_Hash(Hashtable *hasht, char *chave, varTypes *var);

varTypes *procurar_Na_Tabela_Hash(Hashtable *hasht, char *chave);

void free_Tabela_Hash(Hashtable *hasht);

#endif