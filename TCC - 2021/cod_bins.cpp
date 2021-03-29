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
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>

using namespace std;

//HEADERS
#include "head_struct.h"
#include "head_bins.h"

void criar_bins (vector<Tbin> &bins, const TinfoBins infoBins){
    Tbin bin;
    int i = 0;

    while(i < infoBins.quantItens){
        bin.pesoUsado = 0;
        bin.pesoLivre = infoBins.pesoBin;
        bin.id_bin = i+1;
        bin.numConflitos = 0;

        bins.push_back(bin);
        i++;
    }
}

void imprimir_info_bins(const vector<Tbin> bins){
    for(auto it = bins.begin(); it != bins.end(); it++){
        cout << "ID bin: " << it->id_bin;
        cout << " Peso Usado: " << it->pesoUsado;
        cout << " Peso Livre: " << it->pesoLivre;
        cout << " Quant Itens: " << it->items.size();
        cout << " Conflitos: " << it->numConflitos << endl;

    }
}

void imprimir_bins(const vector<Tbin> bins, const vector<Titem> items){
    unsigned int j = 0;
    int cont = 0;

    for(unsigned int i = 0; i < bins.size(); i++){
        j = 0;

        while(j < bins[i].items.size()){
            cont++;
            cout << " Bin " << bins[i].id_bin
                 << " \tPeso do Bin " << bins[i].pesoUsado
                 << " \tPeso Livre "  << bins[i].pesoLivre
                 << " \tId iten "     << bins[i].items[j]
                 << " \tPeso Iten "   << items[(bins[i].items[j])-1].peso
                 << " \tQuant itens " << bins[i].items.size()
                 << " \tConflitos "   << bins[i].numConflitos;

                 if( bins[i].numConflitos > 0){
                    cout << " >>>>>>>>>>>>>>>>>>>>>>";
                 }
                cout << endl;
            j++;
        }
    }
    cout << "Quantidade de itens: "<<cont << endl;
}

int remove_bin_phy(vector<Tbin> &bins, const vector<Titem> items,  const int **matriz_adj, int ww, int wc, int phy){
    int item;
    int binNovoAntes =0;
    int binNovoDepois =0;
    int deltaPhy = 0;
    int tam_bins;
    int bim_rand;
    int phyBinRemovido = 0;
    int pesoBinRemovido = 0;

    vector <int> vetor_itens;

    //Escolhe o bin para remover
    tam_bins = bins.size();
    bim_rand = std::rand() % tam_bins;

    if(bins[bim_rand].pesoLivre < 0){
        pesoBinRemovido = ((bins[bim_rand].pesoLivre * (-1))* ww);
    }else{
        pesoBinRemovido = 0;
    }

    phyBinRemovido = pesoBinRemovido + (bins[bim_rand].numConflitos * wc);

    phy = phy - phyBinRemovido - 1;

    vetor_itens = bins[bim_rand].items;

    erase_bin(bins, bim_rand);

    for(unsigned int i = 0; i < vetor_itens.size(); i++){
        bim_rand = std::rand() % (tam_bins-1);

        if(bins[bim_rand].pesoLivre < 0) binNovoAntes = ((bins[bim_rand].pesoLivre * (-1))* ww);
        else binNovoAntes = 0;

        binNovoAntes = binNovoAntes + (bins[bim_rand].numConflitos * wc);

        item = vetor_itens[i];
        bins[bim_rand].items.push_back(item);
        bins[bim_rand].pesoUsado += items[item-1].peso;
        bins[bim_rand].pesoLivre -= items[item-1].peso;
        bins[bim_rand].numConflitos += (conflito_por_bin(bins[bim_rand].items, item, (const int**)matriz_adj));

        if(bins[bim_rand].pesoLivre < 0)binNovoDepois = ((bins[bim_rand].pesoLivre * (-1))* ww);
        else binNovoDepois = 0;

        binNovoDepois += (bins[bim_rand].numConflitos * wc);

        deltaPhy = (binNovoDepois - binNovoAntes);
        phy = phy + deltaPhy;

    }
    return phy;
}

void erase_bin (vector<Tbin> &v, int pos){
    int id = v[pos].id_bin;

    if(v.size() == 1){
        v.pop_back();
    }else{
        if(!v.empty()){
            std::swap(v[pos], v.back());
            v.pop_back();
        }
        for(unsigned int i = pos; i < v.size(); i++){
            v[i].id_bin = id;
            id++;
        }
    }
}

int conflito_por_bin(const vector<int> items, const int item, const int **matriz_adj){
     int cont = 0;

     for(const auto& x: items){
        if(x != item){
            if(matriz_adj[item-1][x-1] == 1)cont++;
            if(matriz_adj[x-1][item-1] == 1)cont++;
        }
    }
    return cont;
}


void imprimir_bins_2(const vector<Tbin> bins, const vector<Titem> items, double cpu_time_used){
    cout << bins.size() << " " << cpu_time_used << endl;
    unsigned int j = 0;

    for(unsigned int i = 0; i < bins.size(); i++){
        j = 0;
        cout << i+1 <<" ";
        while(j < bins[i].items.size()){
            cout << bins[i].items[j] << " ";
            j++;
        }
        cout << endl;
    }
}
