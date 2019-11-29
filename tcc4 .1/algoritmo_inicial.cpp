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
#include <algorithm>
#include <bits/stdc++.h>

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



void bestFit (vector<Tbin> &bins, const vector<Titem> itens, const TinfoBins infoBins, const int **matriz_adj){
    int binIndex = 0;
    int binTamanho = 0;
    int pesoLivre = 0;
    int aux = 0;
    Titem item;
    int contador = 0;

    for(int i = 0; i < infoBins.quantItens ; i++){
        binTamanho = infoBins.pesoBin;
        binIndex = -1;

        item.idItem = itens[i].idItem;
        item.peso = itens[i].peso;

        unsigned int j;
        j = 0;
        while(j <= bins.size() && binIndex == -1){
            binIndex = -1;
            pesoLivre = bins[j].pesoLivre;
            aux = confere_conflito(item.idItem, bins, j, matriz_adj);

            if((pesoLivre >= item.peso) && ((pesoLivre - item.peso) < binTamanho) && aux == 0){
                binIndex = j;
                binTamanho = pesoLivre - item.peso;
            }
            j++;
        }
        bins[binIndex].items.push_back(item.idItem);
        bins[binIndex].pesoLivre -= item.peso;
        bins[binIndex].pesoUsado += item.peso;

        if(binIndex >= contador){
            contador++;
        }
    }
    bins.resize(contador);
}



void firstFit_ordenado (vector<Tbin> &bins, const vector<Titem> itens, const TinfoBins infoBins, const int **matriz_adj){
    vector<Titem> itens_ordenados = itens;
    int contador_bins = 0, aux = -1;
    int j;

    sort(itens_ordenados.begin(), itens_ordenados.end(), sort_peso);

    for(unsigned int i = 0; i < itens_ordenados.size(); i++){
        for(j = 0; j < contador_bins; j++){
            aux = -1;
            aux = confere_conflito(itens_ordenados[i].idItem, bins, j, matriz_adj);

            if(bins[j].pesoLivre >= itens_ordenados[i].peso && aux == 0){
                bins[j].pesoUsado += itens_ordenados[i].peso;
                bins[j].pesoLivre -= itens_ordenados[i].peso;
                bins[j].items.push_back(itens_ordenados[i].idItem);
                break;
            }
        }
        if(j == contador_bins){
            bins[contador_bins].pesoUsado += itens_ordenados[i].peso;
            bins[contador_bins].pesoLivre -= itens_ordenados[i].peso;
            bins[contador_bins].items.push_back(itens_ordenados[i].idItem);
            contador_bins++;
        }
    }
    bins.resize(contador_bins);
}

void bestFit_ordenado (vector<Tbin> &bins, const vector<Titem> itens, const TinfoBins infoBins, const int **matriz_adj){
    vector<Titem> itens_ordenados = itens;
    int contador_bins = 0, aux = -1;
    int mini, best_bin;
    int j;

    sort(itens_ordenados.begin(), itens_ordenados.end(), sort_peso);

    for(unsigned int i = 0; i < itens_ordenados.size(); i++){
        mini = infoBins.pesoBin+1;
        best_bin = 0;

        for(j = 0; j < contador_bins; j++){
            aux = -1;
            aux = confere_conflito(itens_ordenados[i].idItem, bins, j, matriz_adj);

            if(bins[j].pesoLivre >= itens_ordenados[i].peso && aux == 0){
                best_bin = j;
                mini = (bins[j].pesoLivre - itens_ordenados[i].peso);
            }
        }

        if(mini == (infoBins.pesoBin+1)){
            bins[contador_bins].pesoUsado += itens_ordenados[i].peso;
            bins[contador_bins].pesoLivre -= itens_ordenados[i].peso;
            bins[contador_bins].items.push_back(itens_ordenados[i].idItem);
            contador_bins++;
        }else{
            bins[best_bin].pesoUsado += itens_ordenados[i].peso;
            bins[best_bin].pesoLivre -= itens_ordenados[i].peso;
            bins[best_bin].items.push_back(itens_ordenados[i].idItem);
        }
    }
    bins.resize(contador_bins);
}

bool sort_peso (const Titem &a, const Titem &b){
    return a.peso > b.peso;
}

int confere_conflito(int id_obj, const vector<Tbin> bins, int j , const int **matriz_adj){
    unsigned int i = 0;

    if(bins[j].items.size() == 0){
        return 0;
    }

    while(i < bins[j].items.size()){
        if(matriz_adj[bins[j].items[i]-1][(id_obj-1)] == 1 || matriz_adj [id_obj-1][bins[j].items[i]-1] == 1){
            return 1;
        }
        i++;
    }
    return 0;
}
