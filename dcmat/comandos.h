#ifndef COMANDOS_H
#define COMANDOS_H

/*
 * Este modulo contem funcoes para imprimir determinados comandos especificados no DCMAT
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "comandos.h"
#include "bison.tab.h"



void matriz_Error();


void show_Settings_Comando(float ho, float hi, float vo, float vi,
                   int pr, int p, bool draw, bool erase, bool dots);


void show_About_Comando();

#endif