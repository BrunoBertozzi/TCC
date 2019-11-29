#include <iostream>
#include <vector>
#include <iostream>
#include<fstream>
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

int calcula_delta_swap(const vector<Tbin> bins, const vector<Titem> itens, const int bin1, const int bin2, int *iten_1, int *iten_2, const TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww){
    int deltaG = 0, deltaP = 0, deltaC = 0;
    int melhor = -1;

    for(const auto& iten1: bins[bin1].items){
        for(const auto& iten2: bins[bin2].items){
            deltaP = delta_peso(bins, itens, bin1, bin2, iten1, iten2, infoBins) * ww;
            deltaC = delta_conflito2(iten1, iten2, bin1, bin2, (const int**)matriz_adj, bins) * wc;
            deltaG = deltaP - deltaC;

            if(deltaG > melhor){
                *iten_1 = iten1;
                *iten_2 = iten2;
                melhor = deltaG;
            }
        }
    }
    return melhor;
}

int delta_peso(const vector<Tbin> bins, const vector<Titem> itens, const int bin1, const int bin2, const int iten1, const int iten2, const TinfoBins infoBins){
    int peso_bin1_LA, peso_bin2_LA; // peso livro Antes da troca
    int peso_bin1_LD, peso_bin2_LD; // peso livre Depois da troca
    int peso_bin1, peso_bin2;       // peso geral dos bins;

    peso_bin1 = bins[bin1].pesoUsado - itens[iten1-1].peso + itens[iten2-1].peso;
    peso_bin2 = bins[bin2].pesoUsado - itens[iten2-1].peso + itens[iten1-1].peso;

    peso_bin1_LA = bins[bin1].pesoLivre;
    peso_bin2_LA = bins[bin2].pesoLivre;

    peso_bin1_LD = infoBins.pesoBin - peso_bin1;
    peso_bin2_LD = infoBins.pesoBin - peso_bin2;

    if(peso_bin1_LA > 0) peso_bin1_LA = 0;
    if(peso_bin2_LA > 0) peso_bin2_LA = 0;

    if(peso_bin1_LD > 0) peso_bin1_LD = 0;
    if(peso_bin2_LD > 0) peso_bin2_LD = 0;

    return ((peso_bin1_LD + peso_bin2_LD) - (peso_bin1_LA + peso_bin2_LA));
}

int delta_conflito2(const int id_item1, const int id_item2, const int pos_bin1, const int pos_bin2, const int **matriz_adj, const vector<Tbin> bins){
    double conflito_Antes = 0, conflito_Depois = 0;

    for(const auto& x: bins[pos_bin1].items)
        if(matriz_adj[x-1][id_item1-1] == 1 || matriz_adj[id_item1-1][x-1] == 1)
            conflito_Antes += 1;

    for(const auto& x: bins[pos_bin2].items)
        if(matriz_adj[x-1][id_item2-1] == 1 || matriz_adj[id_item2-1][x-1] == 1)
            conflito_Antes += 1;

    for(const auto& x: bins[pos_bin1].items)
        if(x != id_item1)
            if(matriz_adj[x-1][id_item2-1] == 1 || matriz_adj[id_item2-1][x-1] == 1)
                conflito_Depois += 1;

    for(const auto& x: bins[pos_bin2].items)
        if(x != id_item2)
            if(matriz_adj[x-1][id_item1-1] == 1 || matriz_adj[id_item1-1][x-1] == 1)
                conflito_Depois += 1;

    return (conflito_Depois - conflito_Antes);
}

int calcula_delta_realocate (const vector<Tbin> bins, const vector<Titem> itens, const int bin1, const int bin2, int *iten_1, const TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww){
    int melhor = -1, deltaP = 0, deltaC = 0, deltaG = 0;

    for(const auto& iten1: bins[bin1].items){
        deltaP = delta_peso_realocete(bins, itens, iten1, bin1, bin2, infoBins.pesoBin) * ww;
        deltaC = delta_conflito_realocate2 (iten1, bin1, bin2, matriz_adj, bins) * wc;
        deltaG = deltaP - deltaC;

        if(deltaG > melhor){
            *iten_1 = iten1;
            melhor = deltaG;
        }
    }
    return melhor;
}

int delta_peso_realocete(const vector<Tbin> bins, const vector<Titem> itens, const int item1, const int bin1, const int bin2, const int peso_bim){
    int peso_bin1, peso_bin2;
    int peso_bin1_LA, peso_bin2_LA;
    int peso_bin1_LD, peso_bin2_LD;

    peso_bin1 = bins[bin1].pesoUsado - itens[item1-1].peso;
    peso_bin2 = bins[bin2].pesoUsado + itens[item1-1].peso;

    peso_bin1_LA = bins[bin1].pesoLivre;
    peso_bin2_LA = bins[bin2].pesoLivre;

    peso_bin1_LD = peso_bim - peso_bin1;
    peso_bin2_LD = peso_bim - peso_bin2;

    if(peso_bin1_LA > 0) peso_bin1_LA = 0;
    if(peso_bin2_LA > 0) peso_bin2_LA = 0;

    if(peso_bin1_LD > 0) peso_bin1_LD = 0;
    if(peso_bin2_LD > 0) peso_bin2_LD = 0;

    return ((peso_bin1_LD + peso_bin2_LD) - (peso_bin1_LA + peso_bin2_LA));
}

int delta_conflito_realocate2(const int id_item1, const int pos_bin1, const int pos_bin2, const int **matriz_adj, const vector<Tbin> bins){
    double conflito_Antes = 0, conflito_Depois = 0;

    for(const auto& x: bins[pos_bin1].items)
        if(matriz_adj[x-1][id_item1-1] == 1 || matriz_adj[id_item1-1][x-1] == 1)
            conflito_Antes += 1;

    for(const auto& x: bins[pos_bin2].items)
            if(matriz_adj[x-1][id_item1-1] == 1 || matriz_adj[id_item1-1][x-1] == 1)
                conflito_Depois += 1;

    return (conflito_Depois - conflito_Antes);
}

int calcula_delta_swap_2_1(const vector<Tbin> bins, const vector<Titem> itens, const int bin1, const int bin2, int *iten_1, int *iten_2, int *iten_3, const TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww){
    int deltaG = 0, deltaP = 0, deltaC = 0;
    int melhor = -1;

    for(const auto& iten3: bins[bin2].items){
        for(const auto& iten1: bins[bin1].items){
            for(const auto& iten2: bins[bin1].items){
                if(iten1 != iten2){
                    deltaP = delta_peso_swap_2_1(bins, itens, bin1, bin2, iten1, iten2, iten3, infoBins) * ww;
                    deltaC = delta_conflito_swap_2_1_2(iten1, iten2, iten3, bin1, bin2, (const int**)matriz_adj, bins) * wc;
                    deltaG = deltaP - deltaC;

                    if(deltaG > melhor){
                        *iten_1 = iten1;
                        *iten_2 = iten2;
                        *iten_3 = iten3;
                        melhor = deltaG;
                    }
                }
            }
        }
    }
    return melhor;
}

int delta_peso_swap_2_1(const vector<Tbin> bins, const vector<Titem> itens, const int bin1, const int bin2, const int iten1, const int iten2, const int iten3, const TinfoBins infoBins){
    int peso_bin1_LA, peso_bin2_LA;
    int peso_bin1_LD, peso_bin2_LD;
    int peso_bin1, peso_bin2;

    peso_bin1 = (bins[bin1].pesoUsado - (itens[iten1-1].peso + itens[iten2-1].peso) + itens[iten3-1].peso);
    peso_bin2 = (bins[bin2].pesoUsado - itens[iten3-1].peso + (itens[iten1-1].peso + itens[iten2-1].peso));

    peso_bin1_LA = bins[bin1].pesoLivre;
    peso_bin2_LA = bins[bin2].pesoLivre;

    peso_bin1_LD = infoBins.pesoBin - peso_bin1;
    peso_bin2_LD = infoBins.pesoBin - peso_bin2;

    if(peso_bin1_LA > 0) peso_bin1_LA = 0;
    if(peso_bin2_LA > 0) peso_bin2_LA = 0;

    if(peso_bin1_LD > 0) peso_bin1_LD = 0;
    if(peso_bin2_LD > 0) peso_bin2_LD = 0;

    return ((peso_bin1_LD + peso_bin2_LD) - (peso_bin1_LA + peso_bin2_LA));
}

int delta_conflito_swap_2_1_2(const int id_item1, const int id_item2, const int id_item3, const int pos_bin1, const int pos_bin2, const int **matriz_adj, const vector<Tbin> bins){
    double conflito_Antes = 0, conflito_Depois = 0;

    for(const auto& x: bins[pos_bin1].items)
        if((x != id_item1) && (x != id_item2))
            if(matriz_adj[x-1][id_item1-1] == 1 || matriz_adj[id_item1-1][x-1] == 1  || matriz_adj[x-1][id_item2-1] == 1 || matriz_adj[id_item2-1][x-1])
                conflito_Antes += 1;

    for(const auto& x: bins[pos_bin2].items)
        if((x != id_item3))
            if(matriz_adj[x-1][id_item3-1] == 1 || matriz_adj[id_item3-1][x-1] == 1)
                conflito_Antes += 1;

    for(const auto& x: bins[pos_bin1].items)
        if((x != id_item1) && (x != id_item2))
            if(matriz_adj[x-1][id_item3-1] == 1 || matriz_adj[id_item3-1][x-1] == 1)
                conflito_Depois += 1;

    for(const auto& x: bins[pos_bin2].items)
        if((x != id_item3))
            if(matriz_adj[x-1][id_item1-1] == 1 || matriz_adj[id_item1-1][x-1] == 1 || matriz_adj[x-1][id_item2-1] == 1 || matriz_adj[id_item2-1][x-1])
                conflito_Depois += 1;

    return (conflito_Depois - conflito_Antes);
}



int delta_remove_peso(vector<Tbin> &bins, const vector<Titem> itens, const int iten, const int bin_recebe, const int peso_max_bin){
    int retorno;

    if(bins[bin_recebe].pesoUsado < peso_max_bin){
        int sobra = ((bins[bin_recebe].pesoUsado + itens[iten].peso) - peso_max_bin);
        int peso_livre_novo = (bins[bin_recebe].pesoLivre) + ((-1) * sobra);

        retorno = ((-1) * (peso_livre_novo - bins[bin_recebe].pesoLivre));

        if(retorno >= 0)
            return retorno;

        return 0;

    }else{
        int peso_livre_novo = (bins[bin_recebe].pesoLivre) + ((-1) * itens[iten].peso);

        retorno = ((-1) * (peso_livre_novo - bins[bin_recebe].pesoLivre));

        if(retorno >= 0)
            return retorno;
        return 0;
    }
}

int delta_remove_conflito(const int id_item1, const int bin, const int **matriz_adj, const vector<int> itens){
    double conflito_Depois = 0;

    for(const auto& iten: itens)
            if(matriz_adj[iten-1][id_item1] == 1 || matriz_adj[id_item1][iten-1] == 1)
                conflito_Depois += 1;
    return conflito_Depois;
}
