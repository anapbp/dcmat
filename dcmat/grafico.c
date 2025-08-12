#include "grafico.h"



// ERASED PLOT caso estiver ON/ATIVO:
void erased(char quadro[EIXO_Y][EIXO_X]){
    for (int i = 0; i < EIXO_Y; i++) {
        for (int j = 0; j < EIXO_X; j++) {
            quadro[i][j] = ' ';
        }
    }
}



// DRAWN AXIS ON 
void desenhar_eixos(int eixox, int eixoy, char quadro[EIXO_Y][EIXO_X]){

    if (eixox >= 0 && eixox < EIXO_Y) {
        for (int j = 0; j < EIXO_X; j++) {
            quadro[eixox][j] = '-';
        }
    }

    if (eixoy >= 0 && eixoy < EIXO_X) {
        for (int i = 0; i < EIXO_Y; i++) {
            quadro[i][eixoy] = '|';
        }
    }

    if (eixox >= 0 && eixox < EIXO_Y && eixoy >= 0 && eixoy < EIXO_X) {
        quadro[eixox][eixoy] = '+';
    }
}



// Funcao para impressao do grafico como especificado no DCMAT
void plotar_Grafico(TreeNode* arvoreAux, 
                    float ho, float hi, float vo, float vi, 
                    bool eixo_s_n, bool apaga_s_n, char quadro[EIXO_Y][EIXO_X]) {
    
    float x, y;
    int px, py, eixox, eixoy;

    // Caso nao tiver expressao
    if (arvoreAux == 0) {
        printf("ERRO: insira uma expressao para plotar o grafico :(\n");
        return;
    }


    // ERASED PLOT ON: apagar os graficos anteriores
    if(apaga_s_n) {
        erased(quadro);
    }


    if (fabs(vo) > fabs(vi)) {
        eixox = (int)((1 - (0 - vo) / (vi - vo)) * EIXO_Y);
    } else {
        eixox = (int)((0 - vo) / (vi - vo) * EIXO_Y);
    }


    eixoy = (int)((0 - ho) / (hi - ho) * EIXO_X);


    // DRAWN AXIS ON
    if(eixo_s_n) {
        desenhar_eixos(eixox, eixoy, quadro);
    }


    for (int col = 0; col < EIXO_X; col++) {
        x = ho + col * (hi - ho) / EIXO_X;
        y = calcular_No(arvoreAux, x);

        if (y >= vo && y <= vi) {

            py = (int)((y - vo) / (vi - vo) * EIXO_Y);
            py = EIXO_Y - py - 1;

            if (py >= 0 && py < EIXO_Y) {
                quadro[py][col] = '*';
            }
        }
    }

    for (int i = 0; i < EIXO_Y; i++) {
        for (int j = 0; j < EIXO_X; j++) {
            putchar(quadro[i][j]);
        }
        putchar('\n');
    }
}