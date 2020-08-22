/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 20/07/2020
*
***************************************************************/
#include <iostream>
#include <vector>
#include <iostream>
#include<fstream>

using namespace std;

//HEADERS
#include "structs.h"
#include "arquivo.h"

vector<Titem> ler_arquivo_instancias (TinfoBins *infoBins, const char *nome_arquivo){
    ifstream infile;

    infile.open(nome_arquivo);

    if(infile.is_open()){
        Titem item;
        vector <Titem> items;
        int aux=0, i = 0;
        char c;

        infile >> aux;
        infoBins->quantItens = aux;
        infile >> aux;
        infoBins->pesoBin = aux;

        while(i < (infoBins->quantItens)){
            infile >> aux;
            item.idItem = aux;
            infile >> aux;
            item.peso = aux;

            items.push_back(item);

            do{
               c = infile.get();
            }while(c != '\n' && c != EOF);
            i++;
        }

        infile.close();

        return items;
    }else{
        cout << "[INFO] Erro na leitura do arquivo";
        infile.close();
        return {};
    }
}

void imprimi_itens(const vector<Titem> items, const TinfoBins info_bins){
    int i = 0;

    cout << "Peso Max: " << info_bins.pesoBin << " Quant Itens: " << info_bins.quantItens << endl;

    for(auto it = items.begin(); it != items.end(); it++){
        cout << "ID: " << it->idItem << " Peso: " << it->peso<< endl;
        i++;
    }

    cout << "Quantidade de itens: " << i << endl;
}
