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

void ILS(){
    vector <Titem> items;

    TinfoBins info_bins;

    vector <Tbin> S_inicial;
    vector <Tbin> S_best;
    vector <Tbin> S_linha;
    vector <Tbin> S_linha_linha;


    int **matriz_adj;
    int Klb;
    int phyS_best, phyInicial, phyLinha;

    items = ler_arquivo_instancias(&info_bins, "BPPC_1_1_5.txt");
    matriz_adj = alocar_matriz(info_bins.quantItens, info_bins.quantItens);
    carrega_matrizAdj(matriz_adj, "BPPC_1_1_5.txt");
    S_inicial = criar_bins(info_bins);
    bestFit(S_inicial, items, info_bins, (const int**)matriz_adj);

    //_______________________________________________________________________

    //imprimir_bins(S_inicial, items);
    phyInicial = somatorio_phi(S_inicial, 1, 1);
    phyS_best = phyInicial;
    Klb = calcula_Klb(items, info_bins);
    int iShack = 0, nSchak = 50;
    int bl = 1;

    cout << "phi: "<< phyS_best << " klb: " << Klb << endl;

    S_best = S_inicial;
    S_linha = S_best;

    while(S_linha.size() > (unsigned)Klb){
        remove_bin(S_linha, items, (const int**)matriz_adj);

        phyLinha = somatorio_phi(S_linha, 1, 1);
        S_linha_linha = S_linha;

        iShack = 0;

        while(((phyLinha > phyS_best) && (iShack < nSchak))){
            bl = 1;

            while(bl != 0){
                bl = busca_local(S_linha_linha, items, info_bins, (const int**)matriz_adj, &phyLinha);
            }

            if(phyLinha < phyS_best){
                phyS_best = phyLinha;
                S_best = S_linha_linha;
            }else{

                pertubacao(S_linha_linha, items, 3, info_bins, (const int**)matriz_adj);
                phyLinha = somatorio_phi(S_linha_linha, 1, 1);
                iShack++;
            }
        }
    }

    imprimir_bins(S_best, items);

    //_______________________________________________________________________
    items.clear();
    S_inicial.clear();
    S_best.clear();
    items.shrink_to_fit();
    S_inicial.shrink_to_fit();
    S_best.shrink_to_fit();

    matriz_adj = libera_matriz(matriz_adj, info_bins.quantItens);
    delete matriz_adj;

}

double calcula_Klb(const vector<Titem> items, const TinfoBins infoBins){
    double klb = 0;

    for(const auto & item : items)
    //for(auto it = items.begin(); it != items.end(); it++)
        klb += item.peso;

    return (double)klb / infoBins.pesoBin;
}

void remove_bin(vector<Tbin> &bins, const vector<Titem> items,  const int **matriz_adj){
    std::srand(std::time(nullptr));
    vector <int> aux;
    int item;

    int bim_rand = std::rand() % bins.size();
    aux = bins[bim_rand].items;

    bins.erase(bins.begin()+bim_rand);
    //bins = erase_bin(bins, bim_rand);

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

