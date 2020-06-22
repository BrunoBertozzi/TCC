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
#include <cmath>


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

void ILS(char *argv[]){
    clock_t start_time = clock();
    TinfoBins info_bins;
    vector <Titem> items;
    vector <Tbin> S_inicial;
    vector <Tbin> S_best;
    vector <Tbin> S_linha;
    vector <Tbin> S_linha_linha;
    int **matriz_adj;
    int Klb;
    int phyS_best, phyInicial, phyLinha = 0;
    int iShack = 0;
    int nSchak = atoi(argv[3]);
    int bl = 1;
    int ww = atoi(argv[6]);
    int wc = atoi(argv[7]);
    int Sshack = atoi(argv[8]);
    double cpu_time_used;
    double time_limit = atof(argv[9]);

    ww = correcao_peso(ww, wc);
    items = ler_arquivo_instancias(&info_bins, argv[1]);
    matriz_adj = alocar_matriz(info_bins.quantItens, info_bins.quantItens);
    carrega_matrizAdj(matriz_adj, argv[1]);
    criar_bins(S_inicial , info_bins);
    firstFit_ordenado(S_inicial, items, info_bins, (const int**)matriz_adj);

    //_______________________________________________________________________

    phyInicial = somatorio_phi(S_inicial, wc, ww);
    phyS_best = phyInicial;
    Klb = calcula_Klb(items, info_bins);

    S_best = S_inicial;
    S_linha = S_best;

    while(S_linha.size() > (unsigned)Klb && phyLinha <= phyS_best && (cpu_time_used < time_limit)){
        remove_bin(S_linha, items, (const int**)matriz_adj);
        phyLinha = somatorio_phi(S_linha, wc, ww);
        S_linha_linha = S_linha;
        iShack = 0;

        while(((phyLinha > phyS_best) && (iShack < nSchak))&& (cpu_time_used < time_limit)){
            bl = 1;

            while(bl != 0 && (cpu_time_used < time_limit)){
                bl = busca_local(S_linha_linha, items, info_bins, (const int**)matriz_adj, &phyLinha, wc, ww);
                cpu_time_used = ((double) (clock() - start_time)) / CLOCKS_PER_SEC;
            }

            if(phyLinha < phyS_best){
                phyS_best = phyLinha;
                S_best = S_linha_linha;
            }else{
                pertubacao(S_linha_linha, items, Sshack, info_bins, (const int**)matriz_adj);
                phyLinha = somatorio_phi(S_linha_linha, wc, ww);
                iShack++;
            }
            cpu_time_used = ((double) (clock() - start_time)) / CLOCKS_PER_SEC;
        }
        cpu_time_used = ((double) (clock() - start_time)) / CLOCKS_PER_SEC;
    }
    //_______________________________________________________________________
    clock_t end_time = clock();

    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    imprimir_bins_2 (S_best, items, cpu_time_used);

    matriz_adj = libera_matriz(matriz_adj, info_bins.quantItens);
    delete matriz_adj;
}

int calcula_Klb(const vector<Titem> items, const TinfoBins infoBins){
    float klb = 0;

    for(const auto & item : items)
        klb += item.peso;

    klb = (float)klb / infoBins.pesoBin;
    klb = ceil(klb);

    return klb;
}



void remove_bin(vector<Tbin> &bins, const vector<Titem> items,  const int **matriz_adj){
    vector <int> aux;
    int item;
    int bim_rand = std::rand() % bins.size();

    aux = bins[bim_rand].items;
    erase_bin(bins, bim_rand);

    for(unsigned int i = bim_rand; i < bins.size(); i++)
        bins[i].id_bin -=1;

    for(unsigned int i = 0; i < aux.size(); i++){
        bim_rand = std::rand() % bins.size();
        item = aux[i];
        bins[bim_rand].items.push_back(item);
        bins[bim_rand].pesoUsado += items[item-1].peso;
        bins[bim_rand].pesoLivre -= items[item-1].peso;
        bins[bim_rand].numConflitos += (2* conflito_por_bin(bins[bim_rand].items, item, (const int**)matriz_adj));
    }
}

double conflito_por_bin(const vector<int> items, const int item, const int **matriz_adj){
     double cont = 0;

     for(const auto& x: items){
        if(matriz_adj[x-1][item-1] == 1 || matriz_adj[item-1][x-1] == 1){
            cont += 0.5;
        }
    }
    return cont;
}

