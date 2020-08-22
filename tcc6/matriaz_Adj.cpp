/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 06/08/2020
*
***************************************************************/
#include <iostream>
#include <vector>
#include<fstream>
#include <sstream>

using namespace std;

//HEADERS
#include "structs.h"
#include "arquivo.h"
#include "ILS_1.h"
#include "matriaz_Adj.h"

int **alocar_matriz (const int linha, const int coluna){
    int **matriz = new int*[linha];

    for (int i = 0; i < linha; ++i)
        matriz[i] = new int[coluna];

    zerar_matriz(matriz, linha, coluna);

    return matriz;
}

void zerar_matriz (int **matriz, const int linha, const int coluna){
    for(int i = 0; i < linha; i++)
        for(int j = 0; j < coluna; j++)
            matriz[i][j] = 0;
}

void carrega_matrizAdj(int **matriz, const char *nome_arquivo){
    ifstream infile;
    int quantidade_itens = 0, aux = 0; // aux: usado para percorrer o arquivo
    string linha;

    infile.open(nome_arquivo);

    if(infile.is_open()){
        infile >> quantidade_itens;
        infile >> aux;

        for(int i = 0; i < quantidade_itens; i++){
            infile >> aux;
            infile >> aux;
            getline(infile, linha);
            vector<string> v{explodes(linha, ' ')};
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

void carrega_matrizAdj_linux(int **matriz, const char *nome_arquivo){
    ifstream infile;
    int quantidade_itens, aux;
    string linha, tok;

    infile.open(nome_arquivo);

    if(infile.is_open()){
    	getline(infile, linha);
    	stringstream ss1(linha);
    	getline(ss1, tok, ' ');
    	quantidade_itens = stoi(tok);
    	getline(ss1, tok, ' ');
    	aux = stoi(tok);

        for(int i = 0; i < quantidade_itens; i++){
        	vector<string> v;
        	getline(infile, linha);
        	stringstream ss2(linha);
        	getline(ss2, tok, ' ');//descarta num item
        	getline(ss2, tok, ' ');//descarta peso item
        	while (getline(ss2, tok, ' ')) {
        		v.push_back(tok);
        	}

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

const vector<string> explodes(const string& s, const char& c){
	string aux{""};
	vector<string> v;

	for(auto n:s){
		if(n != c) aux+=n; else
            if(n == c && aux != ""){
                 v.push_back(aux); aux = "";
            }
	}
	if(aux != "") v.push_back(aux);
	return v;
}

void imprime_matriz (int **matriz_adj, const int linha, const int coluna){
    for(int i = 0; i < linha; i++){
        cout << i+1 << "\t";
        for(int j = 0; j < coluna; j++){
            cout << matriz_adj[i][j] << " ";
        }
        cout << endl;
    }
}

int **libera_matriz (int **matriz, const int quant_iten){
    for (int count = 0; count < quant_iten; count++){
        delete[] matriz[count];
    }

	delete[] matriz;
	matriz = NULL;

	return 0;
}
