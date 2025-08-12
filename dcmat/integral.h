#ifndef INTEGRAL_H
#define INTEGRAL_H

/*
 *	Modulo responsavel apenas pelo calculo de Integrais.
 * 	Para a resolucao desses calculos, ira contar com metodos presentes em modulos, como:
 * 		- hash.h
 * 		- variaveis.h
 * 		- arvore.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "bison.tab.h"
#include "hash.h"
#include "arvore.h"
#include "variaveis.h"


float calcular_Integral(TreeNode *arv, Hashtable *hasht, float li, float lo, int p, int pr);

float calcular_No_integral(TreeNode *arv, float valor, Hashtable *hasht);

#endif
