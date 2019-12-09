/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 24/10/2019
*
***************************************************************/


#include <iostream>
#include <vector>
#include <iostream>
#include<fstream>


using namespace std;

#include "arquivo.h"
#include "matrizAdjacencia.h"
#include "geral.h"
#include "algoritmo_inicial.h"
#include "ILS.h"
#include "funcao_avaliacao.h"
#include "matriz_iten_bin.h"
#include "busca_local.h"
#include "delta.h"
#include "pertubacao.h"
#include "ILS2.h"
#include "ILS3.h"


/*
argumentos:
-nome arquivo
-tipo de ILS
-nSchak, quantidade de pertubações
-Nls, Movimento de busca local
-Nsc, movimento de busca local sem melhora
-wc, peso conflito
-ww, peso a mais no bin
-Sshack, quantidade de movimentos feito em cada pertubacao
-Time_Limit, tempo limite de execucao;
*/
int main(int argc, char *argv[]){


    if(argc == 10){
        int op = atoi(argv[2]);

        switch (op){
        case 1:
            ILS(argv);
            break;
        case 2:
            ILS2(argv);
            break;
        case 3:
            ILS3(argv);
            break;

        default:
           cout << "[ERROR] Opcao de ILS invalida" << endl;
        }
    }else{
        cout << "[ERROR] Falta argumento!" << endl;
    }

    return 0;
}


