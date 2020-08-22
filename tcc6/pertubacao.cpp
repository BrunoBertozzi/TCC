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
#include <cstdlib>
#include <ctime>


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
#include "pertubacao.h"

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

int pertubacao(vector<Tbin> &bins, const vector<Titem> itens, int Sshack, const TinfoBins infoBins, const int **matriz_adj, int ww, int wc){
    int bin1 = 0;
    int bin2 = 0;
    int iten = 0;
    int pos_bin = -1;
    int Deltaphy = 0;
    int PesoBin1Antes = 0;
    int pesoBin2Antes = 0;
    int PesoBin1Depois = 0;
    int PesoBin2Depois = 0;
    int ConflitoBin1Depois = 0;
    int ConflitoBin2Depois = 0;
    int PhyAntes = 0;
    int PhyDepois = 0;

    //cout << "Sshack: " << Sshack << endl;

    vector<int> bins_c_conflito = carrega_vetor_bins_conflito_pertubacao(bins);

    for(int i = 0; i < Sshack; i++){
        if(!bins_c_conflito.empty()){
            pos_bin = rand() % bins_c_conflito.size();
            bin1 = bins_c_conflito[pos_bin];

            do{
                bin2 = rand() % bins.size();
            }while(bins[bin1].id_bin == bins[bin2].id_bin);

            iten = pertubacao_iten_conflito(bins, matriz_adj, bin1);


            if(bins[bin1].pesoLivre >= 0  && bins[bin1].numConflitos == 0){
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
            iten = bins[bin1].items[iten];
        }

        PesoBin1Antes = 0;
        pesoBin2Antes = 0;

        if(bins[bin1].pesoLivre < 0) PesoBin1Antes = ((bins[bin1].pesoLivre * (-1))* ww);
        else PesoBin1Antes = 0;

        if(bins[bin2].pesoLivre < 0) pesoBin2Antes = ((bins[bin2].pesoLivre * (-1))* ww);
        else pesoBin2Antes = 0;

        PhyAntes = PesoBin1Antes + pesoBin2Antes + (bins[bin1].numConflitos * wc) + (bins[bin2].numConflitos * wc);

        realocate(iten, bin1, bin2, bins, itens, matriz_adj, infoBins.quantItens);

        PesoBin1Depois = ((bins[bin1].pesoLivre));
        PesoBin2Depois = ((bins[bin2].pesoLivre));

        if(bins[bin1].pesoLivre < 0) PesoBin1Depois = ((bins[bin1].pesoLivre * (-1))* ww);
        else PesoBin1Depois = 0;

        if(bins[bin2].pesoLivre < 0) PesoBin2Depois = ((bins[bin2].pesoLivre * (-1))* ww);
        else PesoBin2Depois = 0;

        PhyDepois = (PesoBin1Depois + PesoBin2Depois) + (ConflitoBin1Depois + ConflitoBin2Depois);

        PhyDepois = (PesoBin1Depois + PesoBin2Depois) + (bins[bin1].numConflitos * wc) + (bins[bin2].numConflitos * wc);

        Deltaphy += PhyDepois - PhyAntes;

        //cout << "PhyAntes: " << PhyAntes << endl;
    }

    //cout << "Deltaphy" << Deltaphy << endl;

    return Deltaphy;
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

vector<int> carrega_vetor_bins_conflito_pertubacao(const vector<Tbin> &bins){
    vector<int> bins_c_conflito;

    for(const auto& bin: bins)
        if((bin.numConflitos > 0 || bin.pesoLivre < 0) && (bin.items.size() > 1))
            bins_c_conflito.push_back((bin.id_bin-1));

    return bins_c_conflito;
}
