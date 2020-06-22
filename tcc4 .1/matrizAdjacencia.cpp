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
#include <string>
#include <sstream>

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


int **alocar_matriz (const int linha, const int coluna){
    int **matriz = new int*[linha];

    for (int i = 0; i < linha; ++i)
        matriz[i] = new int[coluna];

    zerar_matriz(matriz, linha, coluna);

    return matriz;
}


int **libera_matriz (int **matriz, const int quant_iten){
    for (int count = 0; count < quant_iten; count++){
        delete[] matriz[count];
    }

	delete[] matriz;
	matriz = NULL;

	return 0;
}


void imprime_matriz (const int **matriz_adj, const int linha, const int coluna){
    for(int i = 0; i < linha; i++){
        cout << i+1 << "\t";
        for(int j = 0; j < coluna; j++){
            cout << matriz_adj[i][j] << " ";
        }
        cout << endl;
    }
}

void zerar_matriz (int **matriz, const int linha, const int coluna){
    for(int i = 0; i < linha; i++)
        for(int j = 0; j < coluna; j++)
            matriz[i][j] = 0;
}

void carrega_matrizAdj(int **matriz, const char *nome_arquivo){
    ifstream infile;
    int quantidade_itens, aux;
    string linha;

    infile.open(nome_arquivo);

    if(infile.is_open()){
        infile >> quantidade_itens;
        infile >> aux;

        for(int i = 0; i < quantidade_itens; i++){
            infile >> aux;
            infile >> aux;
            getline(infile, linha);
            vector<string> v{explode(linha, ' ')};
            for(auto n:v){
                aux = stoi(n);
                matriz[i][aux-1] = 1;
                matriz[aux-1][i] = 1;
            }
        }
    }else{
        cout << "[INFO] Erro na leitura do arquivo";
        infile.close();
    }
}

const vector<string> explode(const string& s, const char& c){
	string buff{""};
	vector<string> v;

	for(auto n:s){
		if(n != c) buff+=n; else
            if(n == c && buff != ""){
                 v.push_back(buff); buff = "";
            }
	}
	if(buff != "") v.push_back(buff);
	return v;
}
