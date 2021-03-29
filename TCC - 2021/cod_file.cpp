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

using namespace std;

//HEADERS
#include "head_struct.h"
#include "head_file.h"

//

void ler_info_bins (TinfoBins *infoBins, const char *nome_arquivo){
    ifstream infile;

    infile.open(nome_arquivo);

    if(infile.is_open()){
        infile >> infoBins->quantItens;
        infile >> infoBins->pesoBin;

    }else{
        cout << "[INFO] Erro na leitura do arquivo - FUNCAO LER INFO BINS";
        return;
    }
    infile.close();
}

vector<Titem> ler_itens (const TinfoBins infoBins, const char *nome_arquivo){
    ifstream infile;

    infile.open(nome_arquivo);

    if(infile.is_open()){
        Titem item;
        vector <Titem> vect_item;

        int aux = 0, i = 0;
        char c;

        infile >> aux;
        infile >> aux;

        while(i < (infoBins.quantItens)){
            infile >> aux;
            item.idItem = aux;
            infile >> aux;
            item.peso = aux;

            vect_item.push_back(item);

            do{
               c = infile.get();
            }while(c != '\n' && c != EOF);
            i++;
        }

        infile.close();

        return vect_item;
    }else{
        cout << "[INFO] Erro na leitura do arquivo - FUNCAO LER ITENS";
        infile.close();
        return {};
    }
}

void imprimi_itens(const TinfoBins info_bins,const vector<Titem> items){
    int i = 0;

    cout << "Peso Max: " << info_bins.pesoBin << " Quant Itens: " << info_bins.quantItens << endl;

    for(auto it = items.begin(); it != items.end(); it++){
        cout << "ID: " << it->idItem << " Peso: " << it->peso<< endl;
        i++;
    }

    cout << "Quantidade de itens: " << i << endl;
}
