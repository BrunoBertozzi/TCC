/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 20/07/2020
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
#include "Phy.h"
#include "delta_Movimentoa.h"
#include "movimento_BL.h"

void realocate(int id_item, int id_bin1, int id_bin2, vector<Tbin> &bins, const vector<Titem> itens, const int **matriz_adj, const int quant_itens){
    for(unsigned int i = 0; i <bins[id_bin1].items.size(); i++){    //procura o item a ser excluido
        if(bins[id_bin1].items[i] == id_item){
            erase_int(bins[id_bin1].items, i);                      //exclui o item do bim
        }
    }

    bins[id_bin1].pesoUsado -= itens[id_item-1].peso;
    bins[id_bin1].pesoLivre += itens[id_item-1].peso;
    bins[id_bin1].numConflitos = 0;

    for(const auto& iten: bins[id_bin1].items){
        for(const auto& iten2: bins[id_bin1].items){
            if(iten != iten2){
                if(matriz_adj[iten-1][iten2-1] == 1 || matriz_adj[iten2-1][iten-1] == 1)bins[id_bin1].numConflitos++;
            }
        }
    }

    bins[id_bin2].items.push_back(id_item);
    bins[id_bin2].pesoUsado += itens[id_item-1].peso;
    bins[id_bin2].pesoLivre -= itens[id_item-1].peso;
    bins[id_bin2].numConflitos = 0;

    for(const auto& iten: bins[id_bin2].items){
        for(const auto& iten2: bins[id_bin2].items){
            if(iten != iten2){
                if(matriz_adj[iten-1][iten2-1] == 1 || matriz_adj[iten2-1][iten-1] == 1)bins[id_bin2].numConflitos++;
            }
        }
    }
}

void Swap (const int id_item1, const int id_item2, const int id_bin1, const int id_bin2, vector<Tbin> &bins, const vector<Titem> itens, const int **matriz_adj, const int quant_itens){
    realocate(id_item1, id_bin1, id_bin2, bins, itens, (const int**)matriz_adj, quant_itens);
    realocate(id_item2, id_bin2, id_bin1, bins, itens, (const int**)matriz_adj, quant_itens);
}

void Swap2_1(const int id_item1, const int id_item2, const int id_item3, const int id_bin1, const int id_bin2, vector<Tbin> &bins, const vector<Titem> itens, const int **matriz_adj, const int quant_itens){
    realocate(id_item1, id_bin1, id_bin2, bins, itens, (const int**)matriz_adj, quant_itens);
    realocate(id_item2, id_bin1, id_bin2, bins, itens, (const int**)matriz_adj, quant_itens);
    realocate(id_item3, id_bin2, id_bin1, bins, itens, (const int**)matriz_adj, quant_itens);
}

void erase_int (vector<int> &v, int pos){
    if(!v.empty()){
        std::swap(v[pos], v.back());
        v.pop_back();
    }
}
