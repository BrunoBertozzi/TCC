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
#include <algorithm>
#include <cmath>

using namespace std;

//HEADERS
#include "structs.h"
#include "arquivo.h"
#include "ILS_2.h"
#include "ILS_1.h"
#include "matriaz_Adj.h"
#include "bins.h"
#include "solucao_Inicial.h"
#include "algoritmo_Verificacao.h"
#include "Phy.h"
#include "delta_Movimentoa.h"
#include "movimento_BL.h"
#include "pertubacao.h"


void ILS_2(char *argv[]){
    clock_t start_time = clock();

    vector <Titem> items;
    vector <Tbin> S_inicial;
    vector <Tbin> S_best;
    vector <Tbin> S_linha;
    vector <Tbin> S_linha_linha;

    TinfoBins info_bins;

    int **matriz_adj;
    int Klb;
    int iShack = 0;
    int tipoILS = atoi(argv[2]);
    int nSchak  = atoi(argv[3]);
    int Nls = atoi(argv[4]);
    int Nsc = atoi(argv[5]);
    int iNsc = 0;
    int ww = atoi(argv[6]);
    int wc = atoi(argv[7]);
    int Sshack = atoi(argv[8]);
    int bl = 0;

    double phyS_best = 0;
    double phyLinha = 0;
    double deltaPhy = 0;
    double time_limit = atof(argv[9]);
    double cpu_time_used;

    items = ler_arquivo_instancias(&info_bins, argv[1]);
    matriz_adj = alocar_matriz(info_bins.quantItens, info_bins.quantItens);
    carrega_matrizAdj_linux(matriz_adj, argv[1]);
    criar_bins(S_inicial , info_bins);
    firstFit_ordenado(S_inicial, items, info_bins, (const int**)matriz_adj);

    //_______________________________________________________________________

    phyS_best = somatorio_phi(S_inicial, wc, ww);
    phyLinha = phyS_best;
    Klb = calcula_Klb(items, info_bins);

    S_best = S_inicial;
    S_linha = S_best;

    while(S_linha.size() > (unsigned)Klb && phyLinha <= phyS_best && (cpu_time_used < time_limit)){

        S_linha = S_best;
        phyLinha = phyS_best;
        phyLinha = remove_bin_phy2 (S_linha, items, (const int**)matriz_adj, ww, wc, phyLinha);
        S_linha_linha = S_linha;
        iShack = 0;
        iNsc = 0;
        bl = 0;

        while(((phyLinha > phyS_best) && (iShack < nSchak))&& (cpu_time_used < time_limit)){
            iNsc = 0;
            bl = 0;
            for(int j = 0; j < Nls; j++){
                bl = busca_local_ILS2(S_linha_linha, items, info_bins, (const int**)matriz_adj, wc, ww, tipoILS);
                phyLinha = phyLinha + bl;
                if(phyLinha < phyS_best){
                    phyS_best = phyLinha;
                    S_best = S_linha_linha;
                }
                if(bl == 0){
                    iNsc++;
                    bl = 0;
                }else{
                    iNsc = 0;
                }
                if(iNsc == Nsc){
                    deltaPhy = pertubacao(S_linha_linha, items, Sshack, info_bins, (const int**)matriz_adj, ww, wc);
                    phyLinha = phyLinha + deltaPhy;

                    iShack++;
                    bl = 0;
                    iNsc = 0;
                }
            }
            cpu_time_used = ((double) (clock() - start_time)) / CLOCKS_PER_SEC;
        }
        cpu_time_used = ((double) (clock() - start_time)) / CLOCKS_PER_SEC;
    }
    //_______________________________________________________________________
    clock_t end_time = clock();

    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    imprimir_bins_2 (S_best, items, cpu_time_used);
    //imprimir_bins(S_best, items);

    matriz_adj = libera_matriz(matriz_adj, info_bins.quantItens);
    delete matriz_adj;
}

double busca_local_ILS2(vector<Tbin> &bins, const vector<Titem> itens, TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww, int tipoILS){
    int iten1 = 0, iten2 = 0, iten3 = 0;
    int  iten1_m = 0, iten2_m = 0, iten3_m = 0;
    int bin1_m = 0, bin2_m = 0;

    double delta_movimento = 0, delta_melhor = 0;
    int movimento = 0;

    int bin1, bin2;

    vector<int> bins_c_conflito = carrega_vetor_bins_conflito(bins);


    if(bins_c_conflito.size() > 0){
        bin1 = rand() % bins_c_conflito.size();
        bin1 = bins_c_conflito[bin1];

        do{
            bin2 = rand() % bins.size();
        }while(bins[bin1].id_bin == bins[bin2].id_bin);

    }else{
        bin1 = rand() % bins.size();

        do{
            bin2 = rand() % bins.size();
        }while(bin1 == bin2);
    }

    delta_movimento = calcula_delta_swap(bins, itens, bin1, bin2, &iten1, &iten2, infoBins, (const int**)matriz_adj, wc, ww, tipoILS);
    if(delta_movimento < delta_melhor){
        delta_melhor = delta_movimento;
        movimento = 1;
        iten1_m = iten1;
        iten2_m = iten2;
        bin1_m = bin1;
        bin2_m = bin2;
    }

    if(bins[bin1].items.size() > 1 ){
        delta_movimento = calcula_delta_realocate(bins, itens, bin1, bin2, &iten1, infoBins, (const int**)matriz_adj, wc, ww, tipoILS);
        if(delta_movimento < delta_melhor){
            delta_melhor = delta_movimento;
            movimento = 2;
            iten1_m = iten1;
            bin1_m = bin1;
            bin2_m = bin2;
        }
    }

    if(bins[bin2].items.size() >= 2 && bins[bin1].items.size() >= 1){
        delta_movimento = calcula_delta_swap_2_1(bins, itens, bin1, bin2, &iten1, &iten2, &iten3, infoBins, (const int**)matriz_adj, wc, ww, tipoILS);
        if(delta_movimento < delta_melhor){
            delta_melhor = delta_movimento;
            movimento = 3;
            iten1_m = iten1;
            iten2_m = iten2;
            iten3_m = iten3;
            bin1_m = bin1;
            bin2_m = bin2;
        }
    }

    if(movimento == 1 )Swap(iten1_m, iten2_m, bin1_m, bin2_m, bins, itens, (const int**)matriz_adj, infoBins.quantItens);
    if(movimento == 2 )realocate(iten1_m, bin1_m, bin2_m, bins, itens, (const int**)matriz_adj, infoBins.quantItens);
    if(movimento == 3)Swap2_1(iten1_m, iten2_m, iten3_m, bin1_m, bin2_m, bins, itens, (const int**)matriz_adj, infoBins.quantItens);
    if(movimento == 0) delta_melhor = 0;

    //cout <<  movimento << endl;

    return delta_melhor;
}
