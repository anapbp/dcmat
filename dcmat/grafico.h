#ifndef GRAFICO_H
#define GRAFICO_H

/*
 *  Modulo cujo unico intuito eh a manipulacao de graficos para o DCMAT!!!!
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "bison.tab.h"
#include "hash.h"
#include "matriz.h"
#include "arvore.h"


/* Quantidades: */
#define EIXO_X  80 
#define EIXO_Y 25



void plotar_Grafico(TreeNode *arvoreAux, float ho, float hi, float vo, float vi, 
                                         bool eixos_s_n, bool apagar_s_n, 
                                         char quadro_de_pixeis[EIXO_Y][EIXO_X]);



// ERASED PLOT caso estiver ON/ATIVO:
void erased(char quadro[EIXO_Y][EIXO_X]);

// DRAWN AXIS ON 
void desenhar_eixos(int eixox, int eixoy, char quadro[EIXO_Y][EIXO_X]);


#endif
