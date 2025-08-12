#include "matriz.h"


int espacar(Matriz* mat, int col){

	int espaco = 0;

	for(int i = 0; i < mat->linhas; i++){

		int curretMin = 0;
		int currentVal = mat->mat[i][col];

		if(currentVal < 0){
			curretMin++;
			currentVal *= -1;
		}

		while(currentVal > 0){
			currentVal /= 10;
			curretMin++;
		}

		if(curretMin > espaco){
			espaco = curretMin;
		}
	}
	return espaco;
}


void calculo_AUX(Matriz* auxMat, Matriz* mAIuff, int p, int q, int n) {
    int i = 0, j = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                mAIuff->mat[i][j++] = auxMat->mat[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}


Matriz* criar_Matriz(float** mArr, int li, int co) {
    Matriz* m = (Matriz*)malloc(sizeof(Matriz));

    m->linhas = li;
    m->colunas = co;

    m->mat = (float **)malloc(li * sizeof(float *));

    for (int i = 0; i < li; i++) {
        m->mat[i] = (float *)malloc(co * sizeof(float));
        for (int j = 0; j < co; j++) {
            m->mat[i][j] = mArr[i][j];
        }
    }

    return m;
}


void zerar_Matriz(float** auxMat, int li, int co) {

    for (int i = 0; i < li; i++) {
        for (int j = 0; j < co; j++) {
            auxMat[i][j] = 0.0;
        }
    }
}


void padrao_Impressao(int co, int* espaco) {

	printf("+-");

	// Conforme especificado no documento DCMAT (o padrao)
	for(int i = 0; i < co; i++){
		for(int j = 0; j < espaco[i]; j++){
			printf(" ");
		}
		if(i < co - 1){
			printf(" ");
		}
	}

	printf("-+\n");
}



void imprimir_Matriz(Matriz* mat, int prec){

	int spc[mat->colunas];

	for(int i = 0; i < mat->colunas; i++){
		spc[i] = espacar(mat, i);

		if(prec > 0){
			spc[i] += prec + 1;
		}
	}

	// Bordas:
	padrao_Impressao(mat->colunas, spc);

	for(int i = 0; i < mat->linhas; i++){

		printf("| ");

		for(int j = 0; j < mat->colunas; j++){
			printf("%*.*f ", spc[j], prec, mat->mat[i][j]);
		}

		printf("|\n");
	}

	padrao_Impressao(mat->colunas, spc);
}


Matriz* adicao_De_Matriz(Matriz* mA, Matriz* mAI) {
	
	if(mA == NULL || mAI == NULL){
		return NULL;
	}

    if (mA->linhas != mAI->linhas || mA->colunas != mAI->colunas) {
        printf("Matrix format incorrect!\n");
        return NULL;
    }

    float** value_buffer = (float**)malloc(10*sizeof(float*));

	for(int i = 0; i < 10; i++){
		value_buffer[i] = (float*)malloc(10*sizeof(float));
	}

	Matriz* resultado = criar_Matriz(value_buffer, mA->linhas, mAI->colunas);

    for (int i = 0; i < mA->linhas; ++i) {
        resultado->mat[i] = (float*)malloc(mA->colunas * sizeof(float));
        for (int j = 0; j < mA->colunas; ++j) {
            resultado->mat[i][j] = mA->mat[i][j] + mAI->mat[i][j];
        }
    }

    return resultado;
}


Matriz* subtracao_De_Matriz(Matriz* mA, Matriz* mAI) {

    if (mA->linhas != mAI->linhas || mA->colunas != mAI->colunas) {
        return NULL;
    }

    float** value_buffer = (float**)malloc(10*sizeof(float*));

	for(int i = 0; i < 10; i++){
		value_buffer[i] = (float*)malloc(10*sizeof(float));
	}

	Matriz* resultado = criar_Matriz(value_buffer, mA->linhas, mAI->colunas);

    for (int i = 0; i < mA->linhas; ++i) {

        resultado->mat[i] = (float*)malloc(mA->colunas * sizeof(float));

        for (int j = 0; j < mA->colunas; ++j) {
            resultado->mat[i][j] = mA->mat[i][j] - mAI->mat[i][j];
        }
    }

    return resultado;
}


Matriz* multiplicacao_De_Matriz(Matriz* mA, Matriz* mAI) {

    if (mA->colunas != mAI->linhas) {
        return NULL;
    }

	float** value_buffer = (float**)malloc(10*sizeof(float*));

	for(int i = 0; i < 10; i++){
		value_buffer[i] = (float*)malloc(10*sizeof(float));
	}

	Matriz* resultado = criar_Matriz(value_buffer, mA->linhas, mAI->colunas);

    for (int i = 0; i < mA->linhas; ++i) {
        resultado->mat[i] = (float*)malloc(mAI->colunas * sizeof(float));
        for (int j = 0; j < mAI->colunas; ++j) {
            resultado->mat[i][j] = 0.0;
            for (int k = 0; k < mA->colunas; ++k) {
                resultado->mat[i][j] += mA->mat[i][k] * mAI->mat[k][j];
            }
        }
    }

    return resultado;
}


Matriz* multiplicacao_Escalar_De_Matriz(Matriz* auxMat, float valor) {

	float** value_buffer = (float**)malloc(10*sizeof(float*));

	for(int i = 0; i < 10; i++){
		value_buffer[i] = (float*)malloc(10*sizeof(float));
	}

    Matriz* resultado = criar_Matriz(value_buffer, auxMat->linhas, auxMat->colunas);

    for (int i = 0; i < auxMat->linhas; ++i) {

        resultado->mat[i] = (float*)malloc(auxMat->colunas * sizeof(float));

        for (int j = 0; j < auxMat->colunas; ++j) {
            resultado->mat[i][j] = auxMat->mat[i][j] * valor;
        }
    }

	for(int i = 0; i < 10; i++){
		free(value_buffer[i]);
	}

	free(value_buffer);

    return resultado;
}


int checar_Matriz_Quadrada(Matriz* m) {
	if(m->linhas == m->colunas){
		return 1;
	}
	return 0;
}


int checar_Sistema_Linear_Matriz(Matriz* m){
	if(m->linhas == m->colunas - 1){
		return 1;
	}
	return 0;
}


void imprimir_Sistema_Linear_Matriz(Matriz* m, int precision){
	if(m == NULL){
		return;
	}
	if(m->colunas != 1){
		return;
	}
	printf("\n");
	for(int i = 0; i < m->linhas; i++){
		printf("%.*f\n", precision, m->mat[i][0]);
	}
}


float calcular_determinante_Matriz(Matriz* m, int n) {
	float D = 0;

	if (n == 1) {
		return m->mat[0][0];
	}

	float** temp = (float**)malloc(10*sizeof(float*));

	for(int i = 0; i < 10; i++){
		temp[i] = (float*)malloc(10*sizeof(float));
	}

	Matriz* t = criar_Matriz(temp, m->linhas, m->colunas);
	int sign = 1;

	for (int f = 0; f < n; f++) {
		calculo_AUX(m, t, 0, f, n);
		D += sign * m->mat[0][f] * calcular_determinante_Matriz(t, n - 1);
		sign = -sign;
	}

	for(int i = 0; i < 10; i++){
		free(temp[i]);
	}

	free(temp);

	return D;
}


Matriz* calcular_Sistema_Linear_Matriz(Matriz* m){

	if(m == NULL){
		return NULL;
	}

	Matriz* temp = criar_Matriz(m->mat, m->linhas, m->colunas);
	float** resmat = NULL;
	resmat = (float**)malloc(10*sizeof(float*));

	for(int i = 0; i < 10; i++){
		resmat[i] = (float*)malloc(10*sizeof(float));
	}

	for(int i = 0; i < m->linhas; i++){
		for(int j = i+1; j < m->linhas; j++){
			float ratio = temp->mat[j][i]/temp->mat[i][i];
			for(int k = 0; k < m->colunas; k++){
				temp->mat[j][k] -= ratio * temp->mat[i][k];
			}
		}
	}	

	if(temp->mat[temp->linhas -1][temp->colunas -2] == 0){
		if(temp->mat[temp->linhas -1][temp->colunas -1] == 0){
			printf("SPI - The Linear System has infinitely many solutions\n");
			return NULL;
		} else {
			printf("SI - The Linear System has no solution\n");
			return NULL;
		}
	}

	for(int i = temp->linhas - 1; i >= 0; i--){
		resmat[i][0] = temp->mat[i][temp->colunas - 1];
		for(int j = i + 1; j < temp->linhas; j++){
			resmat[i][0] -= temp->mat[i][j] * resmat[j][0];
		}
		resmat[i][0] /= temp->mat[i][i];
	}
	

	Matriz* result = criar_Matriz(resmat, temp->linhas, 1);

	return result;
	
}


void free_Matriz(Matriz* m) {
    for (int i = 0; i < m->linhas; i++) {
        free(m->mat[i]);
    }
    free(m->mat);
}
