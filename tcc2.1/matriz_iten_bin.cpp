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

void matriz_bin_item (vector<Tbin> bins, int **matriz_adj, int **matriz_iten_bin, int quant_itens){
    zerar_matriz(matriz_iten_bin, quant_itens, bins.size());

    for(int i = 0; i < quant_itens; i++)
        for(auto&& bin: bins)
            for(auto&& iten: bin.items)
                if(matriz_adj[i][iten-1] == 1 || matriz_adj[iten-1][i] == 1)
                    matriz_iten_bin[i][(bin.id_bin) -1] +=1;
}

void atualizar_conflito_iten_bin(int **matriz_adj, int **matriz_iten_bin, int quant_itens, int id_bin1, int id_bin2, int id_item){
    for(int i = 0; i < quant_itens; i++)
        if(matriz_adj[id_item-1][i] == 1){
            matriz_iten_bin[i][id_bin1] = matriz_iten_bin[i][id_bin1] - 1;
            matriz_iten_bin[i][id_bin2] = matriz_iten_bin[i][id_bin2] + 1;
        }
}
