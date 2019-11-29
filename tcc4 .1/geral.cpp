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
#include "ILS2.h"


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
        cout << it->pesoUsado << " " << it->pesoLivre << " " << it->items.size() << " " << it->id_bin << " " << it->numConflitos << endl;
    }
}

void imprimi_itens(const vector<Titem> items){
        for(auto it = items.begin(); it != items.end(); it++)
            cout << it->peso << " " << it->idItem << endl;
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

void erase_int (vector<int> &v, int pos){
    if(!v.empty()){
        std::swap(v[pos], v.back());
        v.pop_back();
    }
}

vector<int> erase_int1 (vector<int> v, int pos){
    if(v.size() == 1){
        v.pop_back();
    }else{
        int swap_;
        swap_ = v[v.size()-1];
        v[v.size()-1] = v[pos];
        v[pos] = swap_;

        v.pop_back();
    }
    return v;
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
        for(unsigned int i = pos; i < v.size(); i++)
            v[i].id_bin = ++id;
    }
}

void confere_peso (const vector<Tbin> bins, const vector<Titem> items){
    int peso_geral = 0;
    int aux = -1;
    for(auto & bin: bins){
        peso_geral = 0;
        for(auto & iten : bin.items){
            peso_geral += items[iten-1].peso;
        }
        if(peso_geral == bin.pesoUsado){
            aux = -1;
        }else{
            aux = bin.id_bin;
        }
    }
     if(aux == -1){
        cout<< "okkkkkkkkk" << endl;
     }else{
        cout<< "Erro" << endl;
     }
}

void confere_conflitos(const vector<Tbin> bins, const int **matriz_adj){
    int conflito = 0;

    for(auto & bin: bins){
        conflito = 0;
        for(auto & iten1 : bin.items){
            for(auto & iten2 : bin.items){
                if(iten1 != iten2){
                    if(matriz_adj[iten1-1][iten2-1] == 1){
                        conflito++;
                    }
                }
            }
        }
        cout << "Bin: "<< bin.id_bin <<" Conflito: " << conflito;
        if(conflito > 0 ){
            cout << "  CONFLITOOOOOOOOO " << endl;
        }else{
            cout << "  ok " << endl;
        }
    }
}
