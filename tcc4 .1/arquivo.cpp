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


vector<Titem> ler_arquivo_instancias (TinfoBins *infoBins, const char *nome_arquivo){
    ifstream infile;

    infile.open(nome_arquivo);

    if(infile.is_open()){
        Titem item;
        vector <Titem> items;
        int aux=0, aux1=0, i = 0;
        char c;

        infile >> aux;
        infile >> aux1;

        infoBins->quantItens = aux;
        infoBins->pesoBin = aux1;

        while(i < (infoBins->quantItens)){
            infile >> aux;
            infile >> aux1;
            item.idItem = aux;
            item.peso = aux1;

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
