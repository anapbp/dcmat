#include "variaveis.h"

varTypes* criar_Nova_Variavel(int type, void* abobrinha){
	
	varTypes* newVar = (varTypes*)malloc(sizeof(varTypes));
	newVar->type = type;

	if (type == 1){
		newVar->f = abobrinha;
	} else if (type == 2){
		newVar->m = abobrinha;
	}
	return newVar;
}


// -------------------------------------------------------
// Impressao:

void imprimir_Valor_Da_Variavel(varTypes* abobrinha, int prec){

	if(abobrinha == NULL){
		return;
	}
	if(abobrinha->type == 1){
		float temp = *(abobrinha->f);
		printf("%.*f\n", prec, temp);
	}
	else if(abobrinha->type == 2){
		imprimir_Matriz(abobrinha->m, prec);
	}

}


void imprimir_Valor_E_Nome_Da_Variavel(varTypes* abobrinha,int prec, char* chuchu){

	if(abobrinha == NULL){
		printf("Undefined Symbol\n");
		return;
	}

	if(abobrinha->type == 1){
		float temp = *(abobrinha->f);
		printf("%s = %.*f\n", chuchu, prec, temp);
	}

	else if(abobrinha->type == 2){
		printf("\n");
		imprimir_Matriz(abobrinha->m, prec);
	}
}


// -------------------------------------------------------
// Gets:

float* getFloat(varTypes* a){

	if(a == NULL){
		return NULL;
	}
	if(a->type == 1){
		return a->f;
	}
	else{
		return NULL;
	}
}


Matriz* getMatriz(varTypes* a){
	if(a == NULL){
		return NULL;
	}
	if(a->type == 2){
		return a->m;
	}
	else{
		return NULL;
	}

}

// -------------------------------------------------------
// Operacoes Basicas:

varTypes* somar_Variaveis(varTypes* a, varTypes* b){
	varTypes* result = NULL;

	if(a == NULL || b == NULL){
		return NULL;
	}

	int nmr = a->type * 10 + b->type;

	// CASOS DE ERRO!
	switch(nmr)
	{
		case 11:
			float* temp = (float*)malloc(sizeof(float));
			*temp = *(a->f) + *(b->f);
			result = criar_Nova_Variavel(1, temp);
			return result;
		break;
		case 22:
			if (a->m->colunas != b->m->colunas || a->m->linhas != b->m->linhas)
			{
				printf("Incorrect dimensions for operator '+' - have MATRIX [%d][%d] and MATRIX [%d][%d]\n", a->m->linhas, a->m->colunas, b->m->linhas, b->m->colunas);
				return NULL;
			}
			
			varTypes* temp2 = criar_Nova_Variavel(2, adicao_De_Matriz(a->m, b->m));
			return temp2;
		break;
		case 12:
			printf("Incorrect type for operator '+' - have FLOAT and MATRIX\n");
			return NULL;
		case 21:
			printf("Incorrect type for operator '+' - have MATRIX and FLOAT\n");
			return NULL;
		break;
	}

}


varTypes* subtrair_Variaveis(varTypes* a, varTypes* b){
	varTypes* result = NULL;

	if(a == NULL || b == NULL){
		return NULL;
	}
	
	int nmr = a->type * 10 + b->type;
	switch (nmr)
	{
	case 11:
		float* temp2 = (float*)malloc(sizeof(float));
		*temp2 = *(a->f) - *(b->f);
		result = criar_Nova_Variavel(1, temp2);
		return result;
		break;
	case 22:
		if (a->m->colunas != b->m->colunas || a->m->linhas != b->m->linhas){
			printf("Incorrect dimensions for operator '-' - have MATRIX [%d][%d] and MATRIX [%d][%d]\n", a->m->linhas, a->m->colunas, b->m->linhas, b->m->colunas);
			return NULL;
		}
		varTypes* temp3 = criar_Nova_Variavel(2, subtracao_De_Matriz(a->m, b->m));
		return temp3;
		break;
	case 21:
		printf("Incorrect type for operator '-' - have MATRIX and FLOAT\n");
		return NULL;
	case 12:
		printf("Incorrect type for operator '-' - have FLOAT and MATRIX\n");
		return NULL;
	default:
		return NULL;
		break;
	}

}


varTypes* multiplicar_Variaveis(varTypes* a, varTypes* b){
	if(a == NULL || b == NULL){
		return NULL;
	}
	varTypes* result = NULL;
	int nmr = a->type * 10 + b->type;
	switch(nmr){
		case 11:
			float* temp = (float*)malloc(sizeof(float));
			*temp = *(a->f) * *(b->f);
			result = criar_Nova_Variavel(1, temp);
			return result;
		case 22:
			if(a->m->colunas != b->m->linhas){
				printf("Incorrect dimensions for operator '*' - have MATRIX [%d][%d] and MATRIX [%d][%d]\n", a->m->linhas, a->m->colunas, b->m->linhas, b->m->colunas);
				return NULL;
			}
			varTypes* twomat = criar_Nova_Variavel(2, multiplicacao_De_Matriz(a->m, b->m));
			return twomat;
		case 21:
			varTypes* matscal = criar_Nova_Variavel(2, multiplicacao_Escalar_De_Matriz(a->m, *(b->f)));
			return matscal;
		case 12:
			varTypes* scalmat = criar_Nova_Variavel(2, multiplicacao_Escalar_De_Matriz(b->m, *(a->f)));
			return scalmat;
		default:
			return NULL;
	}

}


varTypes* dividir_Variaveis(varTypes* a, varTypes* b){
	varTypes* result = NULL;

	if(a == NULL || b == NULL){
		return NULL;
	}

	if(a->type == 1 && b->type ==1){
		float* temp = (float*)malloc(sizeof(float));
		*temp = *(a->f) / *(b->f);
		result = criar_Nova_Variavel(1, temp);
		return result;
	}

	else if (a->type == 2 && b->type == 2){
		return NULL;
		
	} else {
		
		return NULL;
	}

}


varTypes* elevar_Variaveis(varTypes* a, varTypes* b){
	varTypes* result = NULL;

	if(a == NULL || b == NULL){
		return NULL;
	}

	if (a->type == 1 && b->type ==1){
		float* temp = (float*)malloc(sizeof(float));
		*temp = pow(*(a->f), *(b->f));
		result = criar_Nova_Variavel(1, temp);
		return result;
	} else if (a->type == 2 && b->type == 2){
		return NULL;
		
	} else {
		
		return NULL;
	}
}


varTypes* modulo_Das_Variaveis(varTypes* a, varTypes* b){
	varTypes* result = NULL;

	if(a == NULL || b == NULL){
		return NULL;
	}

	if (a->type == 1 && b->type ==1){
		float* temp = (float*)malloc(sizeof(float));
		*temp = fmod(*(a->f), *(b->f));
		result = criar_Nova_Variavel(1, temp);
		return result;
	} else if (a->type == 2 && b->type == 2){
		return NULL;
	} else {
		return NULL;
	}
}


varTypes* maximo_Das_Variaveis(varTypes* a, varTypes* b){
	varTypes* result = NULL;
	if(a == NULL || b == NULL){
		return NULL;
	}

	if(a->type == 1 && b->type ==1){
		float* temp = (float*)malloc(sizeof(float));
		*temp = fmax(*(a->f), *(b->f));
		result = criar_Nova_Variavel(1, temp);
		return result;

	} else if (a->type == 2 && b->type == 2){
		return NULL;

	} else{
		
		return NULL;
	}

}


varTypes* negativar_Variavel(varTypes* a){
	varTypes* result = NULL;
	if(a == NULL){
		return NULL;
	}
	if(a->type == 1){
		float* temp = (float*)malloc(sizeof(float));
		*temp = -(*(a->f));
		result = criar_Nova_Variavel(1, temp);
		return result;
	}
	else if(a->type == 2){
		varTypes* result = criar_Nova_Variavel(2, multiplicacao_Escalar_De_Matriz(a->m, -1));
		return result;
	}
	else{
		
		return NULL;
	}

}

varTypes* absoluto_Variavel(varTypes* a){
	varTypes* result = NULL;
	if(a == NULL){
		return NULL;
	}
	if(a->type == 1){
		float* temp = (float*)malloc(sizeof(float));
		*temp = fabs(*(a->f));
		result = criar_Nova_Variavel(1, temp);
		return result;
	}
	else if(a->type == 2){
		return NULL;
	}
	else{
		return NULL;
	}

}


varTypes* seno_Variavel(varTypes* a){

	if(a == NULL){
		return NULL;
	}

	if(a->type == 1){
		float* temp = (float*)malloc(sizeof(float));
		*temp = sin(*(a->f));
		varTypes* result = criar_Nova_Variavel(1, temp);
		return result;
	} else if (a->type == 2){
		printf("Incorrect type for operator 'SEN' - have MATRIX\n");
		return NULL;
	} else {
		return NULL;
	}
	return NULL;
}


varTypes* cosseno_Variavel(varTypes* a){

	if(a == NULL){
		return NULL;
	}

	if(a->type == 1){
		float* temp = (float*)malloc(sizeof(float));
		*temp = cos(*(a->f));
		varTypes* result = criar_Nova_Variavel(1, temp);
		return result;
	} else if (a->type == 2){
		printf("Incorrect type for operator 'COS' - have MATRIX\n");
		return NULL;
	} else {
		return NULL;
	}
}


varTypes* tangente_Variavel(varTypes* a){

	if(a == NULL){
		return NULL;
	}

	if (a->type == 1){
		float* temp = (float*)malloc(sizeof(float));
		*temp = tan(*(a->f));
		varTypes* result = criar_Nova_Variavel(1, temp);
		return result;
	} else if (a->type == 2){
		printf("Incorrect type for operator 'TAN' - have MATRIX\n");
		return NULL;
	} else {
		return NULL;
	}

	return NULL;
}
