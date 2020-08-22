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

using namespace std;

//HEADERS
#include "structs.h"
#include "arquivo.h"
#include "ILS_1.h"
#include "matriaz_Adj.h"
#include "bins.h"
#include "solucao_Inicial.h"
#include "algoritmo_Verificacao.h"

void Vconfere_peso (const vector<Tbin> bins, const vector<Titem> items, int quant_iten_max){
    int peso_geral = 0;
    int aux = -1;
    int quant_itens = 0;
    for(auto & bin: bins){
        peso_geral = 0;
        for(auto & iten : bin.items){
            peso_geral += items[iten-1].peso;
            quant_itens++;
        }
        if(peso_geral == bin.pesoUsado){
            aux = -1;
        }else{
            aux = bin.id_bin;
        }
    }

    if(quant_itens == quant_iten_max){
        cout << "[INFO] Quantidade de itens OK: " << quant_iten_max << " = " << quant_itens << endl;
    }else{
        cout << "[INFO] Quantidade de itens ERROR: " << quant_iten_max << " = " << quant_itens << endl;
    }

     if(aux == -1){
        cout<< "[INFO] Peso em cada bin: OK "<< endl;
     }else{
        cout<< "[INFO] Peso em cada bin: ERRO "<< endl;
     }
}

void Vconfere_conflitos(const vector<Tbin> bins, int **matriz_adj){
    int conflito = 0;

    for(auto & bin: bins){
        for(auto & iten1 : bin.items){
            for(auto & iten2 : bin.items){
                if(iten1 != iten2){
                    if(matriz_adj[iten1-1][iten2-1] == 1 || matriz_adj[iten2-1][iten1-1] == 1){
                        conflito++;
                    }
                }
            }
        }
    }

    cout << "[INFO] Quantidade de Conflitos: " << conflito << endl;
}

void Vconfere_peso_limite (const vector<Tbin> bins, int peso_max){
    int aux = -1;
    int peso_ultrapassado = 0;

    for(auto & bin: bins){
        if(bin.pesoUsado > peso_max){
            aux = 0;
        }
        if(bin.pesoLivre < 0){
            peso_ultrapassado += bin.pesoLivre;
        }
    }

     if(aux == -1){
        cout<< "[INFO] Peso LIMITE em cada bin: OK "<< endl;
     }else{
        cout<< "[INFO] Peso LIMITE em cada bin: "<< peso_ultrapassado << endl;
     }

}
