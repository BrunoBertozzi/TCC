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


vector<Tbin> criar_bins (const TinfoBins infoBins){
    vector<Tbin> bins;
    Tbin bin;
    int i = 0;

    while(i < (infoBins.quantItens)){
        bin.pesoUsado = 0;
        bin.pesoLivre = (infoBins.pesoBin);
        bin.id_bin = i+1;
        bin.numConflitos = 0;

        bins.push_back(bin);
        i++;
    }
    return bins;
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

    for(unsigned int i = 0; i < bins.size(); i++){
        j = 0;

        while(j < bins[i].items.size()){

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
}

vector<int> erase_int (vector<int> v, int pos){
    int swap_;

    swap_ = v[v.size()-1];
    v[v.size()-1] = v[pos];
    v[pos] = swap_;

    v.pop_back();

    return v;
}



vector<Tbin> erase_bin (vector<Tbin> v, int pos){
    Tbin swap_;

    swap_.id_bin = v[v.size()-1].id_bin;
    swap_.items = v[v.size()-1].items;
    swap_.numConflitos = v[v.size()-1].numConflitos;
    swap_.pesoLivre = v[v.size()-1].pesoLivre;
    swap_.pesoUsado = v[v.size()-1].pesoUsado;

    v[v.size()-1].id_bin = v[pos].id_bin;
    v[v.size()-1].items = v[pos].items;
    v[v.size()-1].numConflitos = v[pos].numConflitos;
    v[v.size()-1].pesoLivre = v[pos].pesoLivre;
    v[v.size()-1].pesoUsado = v[pos].pesoUsado;

    v[pos].id_bin = swap_.id_bin;
    v[pos].items = swap_.items;
    v[pos].numConflitos = swap_.numConflitos;
    v[pos].pesoLivre = swap_.pesoLivre;
    v[pos].pesoUsado = swap_.pesoUsado;

    v.pop_back();

    return v;
}
