/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 17/02/2021
*
***************************************************************/

#include <iostream>
#include <vector>

using namespace std;

//HEADERS
#include "head_struct.h"
#include "head_mov_buscalocal.h"

void realocate(int id_item, int id_bin1, int id_bin2, vector<Tbin> &bins, const vector<Titem> itens, const int **matriz_adj, const int quant_itens){
    for(unsigned int i = 0; i <bins[id_bin1].items.size(); i++){    //procura o item a ser excluido
        if(bins[id_bin1].items[i] == id_item){
            erase_int(bins[id_bin1].items, i);                      //exclui o item do bim
            break;
        }
    }

    bins[id_bin1].pesoUsado -= itens[id_item-1].peso;
    bins[id_bin1].pesoLivre += itens[id_item-1].peso;

    for(const auto& iten: bins[id_bin1].items){
        if(matriz_adj[iten-1][id_item-1] == 1 || matriz_adj[id_item-1][iten-1] == 1){
            bins[id_bin1].numConflitos -= 2;
        }
    }

    bins[id_bin2].items.push_back(id_item);
    bins[id_bin2].pesoUsado += itens[id_item-1].peso;
    bins[id_bin2].pesoLivre -= itens[id_item-1].peso;

    for(const auto& iten: bins[id_bin2].items){
        if(iten != id_item)
            if(matriz_adj[iten-1][id_item-1] == 1 || matriz_adj[id_item-1][iten-1] == 1)
                bins[id_bin2].numConflitos += 2;
   	}
}

void erase_int (vector<int> &v, int pos){
    if(!v.empty()){
        std::swap(v[pos], v.back());
        v.pop_back();
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
