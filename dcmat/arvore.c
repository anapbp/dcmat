#include "arvore.h"



// Criando novo no:
TreeNode *criar_No(int tipo, TreeNode *no_esquerdo, TreeNode *no_direito, float valor) {

	TreeNode *aux = (TreeNode *)malloc(sizeof(TreeNode));

	aux->tipo_no = tipo;
	aux->num = valor;
	aux->no_direito = no_direito;
	aux->no_esquerdo = no_esquerdo;
	aux->nome = NULL;

	return aux;
}



TreeNode *alterar_ID_Arvore(int tipo, TreeNode *no_esquerdo, TreeNode *no_direito, char* nome) {

	TreeNode *aux = (TreeNode *)malloc(sizeof(TreeNode));

	aux->tipo_no = tipo;
	aux->no_esquerdo = no_esquerdo;
	aux->no_direito = no_direito;
	aux->num = 0;
	aux->nome = strdup(nome);

	return aux;
}



// FUNCAO ESPECIFICA PARA O DCMAT E CALCULOS MATEMATICOS!!
float calcular_No(TreeNode* node, float nmr) {

    if(node == 0) {
		return 0;
	}

    switch (node->tipo_no) {

		case X:   // Variavel
			return nmr;

        case FLOAT: // FLOAT
			return node->num;

        case ADD: // Adicionar
            if(!node->no_esquerdo) {
              return calcular_No(node->no_direito, nmr);
            }

            return calcular_No(node->no_esquerdo, nmr) + calcular_No(node->no_direito, nmr);

        case SUB: // Subtrair
            if(!node->no_esquerdo) {
              return -calcular_No(node->no_direito, nmr);
            }
            return calcular_No(node->no_esquerdo, nmr) - calcular_No(node->no_direito, nmr);

		case DIV: // Dividir
			return calcular_No(node->no_esquerdo, nmr) / calcular_No(node->no_direito, nmr);

        case MULT: // Multiplicar
			return calcular_No(node->no_esquerdo, nmr) * calcular_No(node->no_direito, nmr);

		case ABS: // Absoluto
			return fabs(calcular_No(node->no_esquerdo, nmr));

        case EXP: //Exponencial
			return powf(calcular_No(node->no_esquerdo, nmr), calcular_No(node->no_direito, nmr));

        case SEN: // Seno
			return sinf(calcular_No(node->no_esquerdo, nmr));

        case COS: // Cosseno
			return cosf(calcular_No(node->no_esquerdo, nmr));

        case TAN: // Tangente
			return tanf(calcular_No(node->no_esquerdo, nmr));

        default: return 0;
    }
}



// Deletar:
void remover_Arvore(TreeNode *tree) {

	if(tree) {
		remover_Arvore(tree->no_esquerdo);
		remover_Arvore(tree->no_direito);
		free(tree);
	}
}



//
// FUNCAO ESPECIAL PARA TRATAR RPN!
//
void arvore_RPN(TreeNode *tree) {
	
	if(tree) {
		arvore_RPN(tree->no_esquerdo);
		arvore_RPN(tree->no_direito);
		switch (tree->tipo_no)
		{
		case ADD:
		{
			printf("+ ");
		};
		break;
		case SUB:
		{
			printf("- ");
		};
		break;
		case MULT:
		{
			printf("* ");
		};
		break;
		case DIV:
		{
			printf("/ ");
		};
		break;
		case FLOAT:
		{
			printf("%f ", tree->num);
		};
		break;
		case IDENTIFIER:
		{	
			printf("%s ", tree->nome);
		};
		break;
		case EXP:
		{
			printf("^ ");
		};
		break;
		case MOD:
		{
			printf("%% ");
		};
		break;
		case SEN:
		{
			printf("SEN ");
		};
		break;
		case COS:
		{
			printf("COS ");
		};
		break;
		case TAN:
		{
			printf("TAN ");
		};
		break;
		case X:
		{
			printf("x ");
		};
		break;
		default:
		{
			printf("ERROR: INVALID tipo ");
		};
		break;
		}
	}
}