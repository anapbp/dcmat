#include "integral.h"



// FUNCAO AUXILIAR PARA O METODO calcular_Integral();
float calcular_No_integral(TreeNode* node, float x, Hashtable* tabela) {

    // Nesse caso, retorna:
    if (node == 0) {
        return 0;
    }

    float aux_calc;

    switch (node->tipo_no) {

        case X: 
            return x;

        case FLOAT: 
            return node->num;

        case IDENTIFIER: {
            varTypes* content = procurar_Na_Tabela_Hash(tabela, node->nome);

            if (content == NULL) {
                return 0;
            }

            if (content->type == 1) { 
                return *content->f;
            }
        }

        case ADD:
            aux_calc = calcular_No_integral(node->no_esquerdo, x, tabela) 
                        + calcular_No_integral(node->no_direito, x, tabela);
            return aux_calc;
        
        case SUB:
            aux_calc = calcular_No_integral(node->no_esquerdo, x, tabela) 
                        - calcular_No_integral(node->no_direito, x, tabela);
            return aux_calc;

        case MULT:
            aux_calc = calcular_No_integral(node->no_esquerdo, x, tabela) 
                        * calcular_No_integral(node->no_direito, x, tabela);
            return aux_calc;

        case DIV:
            aux_calc = calcular_No_integral(node->no_esquerdo, x, tabela) 
                        / calcular_No_integral(node->no_direito, x, tabela);
            return aux_calc;
        
        case ABS:
            aux_calc = fabs(calcular_No_integral(node->no_esquerdo, x, tabela));
            return aux_calc;
        
        case EXP:
            aux_calc = powf(calcular_No_integral(node->no_esquerdo, x, tabela), 
                            calcular_No_integral(node->no_direito, x, tabela));
            return aux_calc;
       
        case SEN:
            aux_calc = sinf(calcular_No_integral(node->no_esquerdo, x, tabela));
            return aux_calc;
       
        case COS:
            aux_calc = cosf(calcular_No_integral(node->no_esquerdo, x, tabela));
            return aux_calc;
       
        case TAN:
            aux_calc = tanf(calcular_No_integral(node->no_esquerdo, x, tabela));
            return aux_calc;
       
        default:
            return 0;
    }
}



// Metodo responsavel pelo comando integrate especificado no documento do DCMAT
float calcular_Integral(TreeNode* arvore, Hashtable* tabela, float limi, float limo, int p, int prec) {
    

    if (!arvore) {
        printf("Error: No valid expression to integrate.\n");
        return 0.0;
    }

    if (p <= 0) {
        printf("ERROR: integral_steps must be a positive non-zero integer\n");
        return 0.0;
    }


    // Analisando o limite inf e sup:
    if (limi > limo) {
        printf("ERROR: lower limit must be smaller than upper limit\n");
        return 0.0;
    }

    if (limi == limo) {
        return 0.0; // Da pra calcular ja
    }

    float resultado = 0.0;
    float dx = (limo - limi)/p; 


    for (int i = 0; i < p; i++) {
        float x = limi + i * dx + dx/2; 
        resultado += calcular_No_integral(arvore, x, tabela) * dx; 
    }

    printf("%.*f\n", prec, resultado);

    return resultado;
}