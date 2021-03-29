/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 17/02/2021
*
***************************************************************/

#include <iostream>
#include <vector>
#include<fstream>
#include <sstream>

using namespace std;

//HEADERS
#include "head_struct.h"
#include "head_file.h"
#include "head_matrix.h"

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

int **copy_matriz (int **matriz, const int tam){
    int **new_matriz = alocar_matriz(tam, tam);

    for(int i = 0; i < tam; i++)
        for(int j = 0; j < tam; j++)
            new_matriz[i][j] = matriz[i][j];

    return new_matriz;
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
