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
#include <cstdlib>
#include <ctime>


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

void pertubacao(vector<Tbin> &bins, const vector<Titem> itens, int Sshack, const TinfoBins infoBins, const int **matriz_adj){
    vector<int> bins_c_conflito = carrega_vetor_bins_conflito(bins);
    int bin1, bin2, iten, pos_bin = -1;

    for(int i = 0; i < Sshack; i++){
        pos_bin = -1;
        bin2 = -1;

        if(!bins_c_conflito.empty()){
            do{
                pos_bin = rand() % bins_c_conflito.size();
                bin2 = bins_c_conflito[pos_bin];

                if(bins_c_conflito.size() <= 1 && bins[bin2].items.size() == 1){
                    pos_bin = -1;
                    bin2 = rand() % bins.size();
                }
            }while(bins[bin2].items.size() < 1);

            do{
                bin1 = rand() % bins.size();
            }while(bins[bin1].id_bin == bins[bin2].id_bin);

            iten = pertubacao_iten_conflito(bins, matriz_adj, bin2);
            realocate(iten, bin2, bin1, bins, itens, matriz_adj, infoBins.quantItens);

            if(bins[bin2].pesoLivre >= 0  && bins[bin2].numConflitos == 0 && pos_bin != -1){
                erase_int(bins_c_conflito, pos_bin);
            }
        }else{
            do{
                bin1 = rand() % bins.size();
            }while(bins[bin1].items.size() < 1);

            do{
                bin2 = rand() % bins.size();
            }while(bins[bin1].id_bin == bins[bin2].id_bin);

            iten = rand() % bins[bin1].items.size();
            realocate(bins[bin1].items[iten], bin1, bin2, bins, itens, matriz_adj, infoBins.quantItens);
        }
    }
}

int pertubacao_iten_conflito(const vector<Tbin> &bins, const int **matriz_adj, const int bin_id){
    for(const auto& iten1: bins[bin_id].items){
        for(const auto& iten2: bins[bin_id].items){
            if(matriz_adj[iten1-1][iten2-1] == 1){
                return iten1;
            }
        }
    }
    int iten;
    iten =  rand() % bins[bin_id].items.size();
    return bins[bin_id].items[iten];
}
