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


void bestFit (vector<Tbin> &bins, const vector<Titem> itens, const TinfoBins infoBins, const int **matriz_adj){
    int binIndex = 0;
    int binTamanho = 0;
    int pesoLivre = 0;
    int aux = 0;
    Titem item;
    int contador = 0;

    for(int i = 0; i < infoBins.quantItens ; i++){
        binTamanho = infoBins.pesoBin;
        binIndex = 0;

        item.idItem = itens[i].idItem;
        item.peso = itens[i].peso;

        for(int j = 0; j <= (contador); j++){
            if(j != infoBins.quantItens){
                pesoLivre = bins[j].pesoLivre;

                aux = confere_conflito(item.idItem, bins[j], matriz_adj);

                if((pesoLivre >= item.peso) && ((pesoLivre - item.peso) < binTamanho) && aux == 0){
                    binIndex = j;
                    binTamanho = pesoLivre - item.peso;
                }
            }
        }
        bins[binIndex].items.push_back(item.idItem);
        bins[binIndex].pesoLivre -= item.peso;
        bins[binIndex].pesoUsado += item.peso;

        if(binIndex >= contador)
            contador++;
    }
    bins.resize(contador);
}

vector<Tbin> nextFit (vector<Tbin> bins, vector<Titem> itens, TinfoBins *infoBins, const int **matriz_adj){
    bool placed = false;
    int j=0, aux = 0;
    Titem item;
    int contador = 0;

    for(int i = 0; i < infoBins->quantItens ; i++){
        placed = false;
        item.idItem = itens[i].idItem;
        item.peso = itens[i].peso;

        while( !placed && (j < infoBins->quantItens)){
            aux = confere_conflito(item.idItem, bins[j], (const int**)matriz_adj);

            if(aux == 0){
                if(bins[j].pesoLivre >= item.peso){
                    bins[j].items.push_back(item.idItem);
                    bins[j].pesoLivre -= item.peso;
                    bins[j].pesoUsado += item.peso;
                    placed = true;

                    if(j >= contador){
                        contador++;
                    }
                }else{
                    j++;
                }
            }else{
                j++;
            }
        }
        if(!placed){
            cout << "[INFO] Erro nextFit";
            return {};
        }
    }

    return bins;
}

vector<Tbin> firstFit (vector<Tbin> bins, vector<Titem> itens, TinfoBins *infoBins, const int **matriz_adj){
    bool placed = false;
    int j=0, aux = 0;
    Titem item;
    int contador;

    for(int i = 0; i < infoBins->quantItens ; i++){
        placed = false;
        item.idItem = itens[i].idItem;
        item.peso = itens[i].peso;
        j = 0;

        while( !placed && (j < infoBins->quantItens)){
            aux = confere_conflito(item.idItem, bins[j], (const int**) matriz_adj);

            if(aux == 0){
                if(bins[j].pesoLivre >= item.peso){
                    bins[j].items.push_back(item.idItem);
                    bins[j].pesoLivre -= item.peso;
                    bins[j].pesoUsado += item.peso;
                    placed = true;

                    if(j >= contador){
                        contador++;
                    }
                }
            }
            j++;
        }
        if(!placed){
            cout << "[INFO] Erro firstFit";
            return {};
        }
    }

    return bins;
}

int confere_conflito(int id_obj, Tbin bin , const int **matriz_adj){
    unsigned int i = 0;

    while(i < bin.items.size()){
        if(matriz_adj[bin.items[i]-1][id_obj-1] == 1 || matriz_adj [id_obj-1][bin.items[i]-1] == 1){
            return 1;
        }
        i++;
    }
    return 0;
}


