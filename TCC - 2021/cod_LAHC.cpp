/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 17/02/2021
*
***************************************************************/

#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

//HEADERS
#include "head_struct.h"
#include "head_LAHC.h"
#include "head_bins.h"
#include "head_buscalocal.h"

vector<Tbin> LAHC(vector<Tbin> &S_inicial ,const int **matriz_adj, const TinfoBins info_bins, char *argv[], const vector<Titem> items, int *phyS_Inicial, int Klb, int tamanhoVetor){
    // VARIAVEIS - VECTOR
    vector <Tbin> S_best;
    vector <Tbin> S_linha;
    vector <TCusto> Lista_Custo;

    // VARIAVEIS - Time
    clock_t start_time = clock();

    // VARIAVEIS - Inteira
    int phy_Linha;
    int phyS_best;
    int tipoILS = atoi(argv[2]);
    int ww = atoi(argv[6]);
    int wc = atoi(argv[7]);
    int bl = 0;
    int i = 0;
    int v = 0;

    // VARIAVEIS - Double
    double cpu_time_used;
    double time_limit = atof(argv[9]);

    phyS_best = *phyS_Inicial;
    S_best = S_inicial;

    Lista_Custo.resize(tamanhoVetor);

    for(int i = 0; i < tamanhoVetor; i++){
        Lista_Custo[i].phy = *phyS_Inicial;
    }

    i = 0;

    S_linha = S_best;
    phy_Linha = phyS_best;

    while((cpu_time_used < time_limit) && S_linha.size() > (unsigned)Klb){ // Quantidade de bl sem melhora, KLB
        // REMOVER BIN

       phy_Linha = remove_bin_phy (S_linha, items, (const int**)matriz_adj, ww, wc, phy_Linha);

        while(bl != 0 ){
            bl = busca_local_ILS3(S_linha, items, info_bins, (const int**)matriz_adj, wc, ww, start_time, time_limit, tipoILS);
            phy_Linha = phy_Linha + bl;
            cpu_time_used = ((double) (clock() - start_time)) / CLOCKS_PER_SEC;
        }

        v = i % tamanhoVetor;

        if(phy_Linha <=  Lista_Custo[v].phy || phy_Linha < *phyS_Inicial){
            S_inicial = S_linha;
            *phyS_Inicial = phy_Linha;

            if(*phyS_Inicial < phyS_best){
                S_best = S_inicial;
                phyS_best = *phyS_Inicial;
            }
        }

        Lista_Custo[v].phy = *phyS_Inicial;

        i++;

        cpu_time_used = ((double) (clock() - start_time)) / CLOCKS_PER_SEC;
    }

    imprimir_bins_2 (S_best, items, cpu_time_used);

    return S_best;
}
