
#include "hash.h"



// ********************************************
// FUNCOES AUXILIARES PARA CRIAR TABELA HASH
//

int criar_Tabela_Hash_Auxiliar(char *chave) {

	int hash = 0;

	for (int i = 0; chave[i] != '\0'; i++) {
		hash += chave[i];
	}
	int valor = hash % TAMANHO;

	return valor;
}


Node *criar_No_Auxiliar(char *chave, varTypes *var) {

	Node *aux = (Node*)malloc(sizeof(Node));

	aux->chave = chave;
	aux->var = var;
	aux->prox = NULL;

	return aux;
}

// ********************************************



Hashtable *criar_Tabela_Hash(){

	Hashtable *aux = (Hashtable*)malloc(sizeof(Hashtable));
	aux->tabela = (Node**)malloc(TAMANHO * sizeof(Node*));

	for (int i = 0; i < TAMANHO; i++){
		aux->tabela[i] = NULL;
	}

	return aux;
}



void imprimir_Tabela_Hash(Hashtable* imprimindo){

	// Nada para imprimir
	if (imprimindo == NULL) {
		return;
	}

	for (int i = 0; i < TAMANHO; i++) {

		Node *aux = imprimindo->tabela[i];

		while (aux != NULL) {

			varTypes* content = aux->var;

			// Relembrando...
			// TIPO 1: float
			// TIPO 2: matriz
			if (content->type == 1) {
				printf("%s - FLOAT\n", aux->chave);
			} else if (content->type == 2) {
				printf("%s - ", aux->chave);
				printf("MATRIX [%d][%d]\n", content->m->linhas, content->m->colunas);
			}

			aux = aux->prox;
		}
	}
}



void atualizar_Tabela_Hash(Hashtable *atualiz_hash, char *chave, varTypes *var){

	if (atualiz_hash == NULL || chave == NULL || var == NULL) {
		return;
	}

	int i = criar_Tabela_Hash_Auxiliar(chave);

	if (atualiz_hash->tabela[i] == NULL) {

		atualiz_hash->tabela[i] = criar_No_Auxiliar(chave, var);

	} else {

		Node *aux = atualiz_hash->tabela[i];
		Node *aux_2 = NULL;

		while (aux != NULL) {

			if (strcmp(aux->chave, chave) == 0) {
				aux->var = var;
				return;
			}

			aux_2 = aux;
			aux = aux->prox;
		}

		aux = criar_No_Auxiliar(chave, var);
		aux_2->prox = aux;
	}
}



varTypes *procurar_Na_Tabela_Hash(Hashtable *buscando, char *chave){

	if (buscando == NULL || chave == NULL) {
		return NULL;
	}

	int i = criar_Tabela_Hash_Auxiliar(chave);

	if (buscando->tabela[i] == NULL) {

		return NULL;

	} else {

		Node *aux = buscando->tabela[i];

		while( aux != NULL) {
			if (strcmp(aux->chave, chave) == 0) {
				return aux->var;
			}
			aux = aux->prox;
		}
	}

	return NULL;
}



void free_Tabela_Hash(Hashtable *liberando) {

	if (liberando == NULL) {
		return;
	}

	for (int i = 0; i < TAMANHO; i++) {

		Node* temporario = liberando->tabela[i];

		while (temporario != NULL) {
			
			Node* aux = temporario;
			temporario = temporario->prox;

			free(aux->chave);
			free(aux->var);
			free(aux);
		}
	}

	free(liberando->tabela);
	free(liberando);
}
