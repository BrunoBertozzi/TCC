/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 06/08/2020
*
***************************************************************/
#include <iostream>
#include <vector>
#include <iostream>
#include<fstream>
#include <iostream>

using namespace std;

//HEADERS
#include "structs.h"
#include "ILS_1.h"
#include "ILS_2.h"
#include "ILS_3.h"
#include <time.h>


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
    srand (time(NULL));

        if(argc == 10){
        int op = atoi(argv[2]);

        switch (op){
        case 1:
            ILS_1(argv);
            break;
        case 2:
            ILS_2(argv);
            break;
        case 3:
            ILS_3(argv);
            break;

        default:
           cout << "[ERROR] Opcao de ILS invalida" << endl;
        }
    }else{
        cout << "[ERROR] Falta argumento!" << endl;
    }

    return 0;
}
