/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 17/02/2021
*
***************************************************************/

#include <iostream>
#include <vector>
#include <iostream>
#include<fstream>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

#include "head_struct.h"
#include "head_solucaoInicial.h"

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


bool sort_peso (const Titem &a, const Titem &b){
    return a.peso > b.peso;
}

int confere_conflito(int id_obj, const vector<Tbin> bins, int j , const int **matriz_adj){
    int quant_itens = bins[j].items.size();

    if(quant_itens == 0){
        return 0;
    }

    int i = 0;

    while(i < quant_itens){
        if(matriz_adj[bins[j].items[i]-1][(id_obj-1)] == 1 || matriz_adj [id_obj-1][bins[j].items[i]-1] == 1){
            return 1;
        }
        i++;
    }
    return 0;
}
