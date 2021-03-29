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
#include <iostream>

using namespace std;

#include "head_struct.h"
#include "head_ILS.h"
#include "head_matrix.h"
#include "head_file.h"
#include "head_bins.h"
#include "head_phi.h"
#include "head_solucaoInicial.h"
#include "head_buscalocal.h"
#include "head_mov_buscalocal.h"
#include "head_LAHC.h"

/*
argumentos:
-nome arquivo
-tipo de ILS
-nSchak, quantidade de pertubações
-Nls, Movimento de busca local
-Nsc, movimento de busca local sem melhora
-wc, peso conflito
-ww, peso a mais no bin
-Sshack, quantidade de movimentos feito em cada pertubacao
-Time_Limit, tempo limite de execucao;
*/

int main(int argc, char *argv[]){
    // VARIAVEIS - TED
    TinfoBins info_bins;

    //VARIAVEIS - VECTOR
    vector <Titem> items;
    vector <Tbin> S_inicial;
    vector <Tbin> S_Best;


    // VARIAVEIS - INT
    int **matriz_adj;
    int phy_Inicial;
    int Klb;

    // PRE SET
    ler_info_bins(&info_bins, argv[1]);
    items = ler_itens(info_bins, argv[1]);
    Klb = calcula_Klb(items, info_bins);
    matriz_adj = alocar_matriz(info_bins.quantItens, info_bins.quantItens);
    carrega_matrizAdj_linux(matriz_adj, argv[1]);
    criar_bins(S_inicial , info_bins);
    firstFit_ordenado(S_inicial, items, info_bins, (const int**)matriz_adj);
    phy_Inicial = S_inicial.size();


    // ILS 1 - All 4 All
    S_Best = ILS1(S_inicial, (const int**)matriz_adj, info_bins, argv, items, &phy_Inicial, Klb);

    // ILS 2 - RANDOM
    //S_Best = ILS2(S_inicial, (const int**)matriz_adj, info_bins, argv, items, &phy_Inicial, Klb);

    // ILS 3 - FIRST
    //S_Best = ILS3(S_inicial, (const int**)matriz_adj, info_bins, argv, items, &phy_Inicial, Klb);

    // LAHC
    S_Best = LAHC(S_Best, (const int**)matriz_adj, info_bins, argv, items, &phy_Inicial, Klb, 100);

    return 0;
}
