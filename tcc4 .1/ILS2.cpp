#include <iostream>
#include <vector>
#include <iostream>
#include<fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>


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

void ILS2(){
    vector <Titem> items;

    TinfoBins info_bins;

    vector <Tbin> S_inicial;
    vector <Tbin> S_best;
    vector <Tbin> S_linha;
    vector <Tbin> S_linha_linha;


    int **matriz_adj;
    int Klb;
    int phyS_best = 0;
    int phyInicial = 0;
    int phyLinha = 0;
    int iShack = 0, nSchak = 50, Nls = 100, Nsc = 25, iNsc = 0;

    items = ler_arquivo_instancias(&info_bins, "BPPC_1_1_10.txt");
    matriz_adj = alocar_matriz(info_bins.quantItens, info_bins.quantItens);
    carrega_matrizAdj(matriz_adj, "BPPC_1_1_10.txt");
    criar_bins(S_inicial , info_bins);
    firstFit_ordenado(S_inicial, items, info_bins, (const int**)matriz_adj);

    //_______________________________________________________________________

    imprimir_bins(S_inicial, items);
    phyInicial = somatorio_phi(S_inicial, 10, 5);
    phyS_best = phyInicial;
    Klb = calcula_Klb(items, info_bins);
    int bl = 0;

    cout << "phi: "<< phyS_best << " klb: " << Klb << endl;

    S_best = S_inicial;
    S_linha = S_best;

    while(S_linha.size() > (unsigned)Klb && phyLinha <= phyS_best){
        remove_bin(S_linha, items, (const int**)matriz_adj);
        phyLinha = somatorio_phi(S_linha, 10, 5);
        S_linha_linha = S_linha;
        iShack = 0;
        iNsc = 0;
        bl = 0;

        while(((phyLinha > phyS_best) && (iShack < nSchak))){
            iNsc = 0;
            bl = 0;
            for(int j = 0; j < Nls; j++){
                bl = busca_local_ILS2(S_linha_linha, items, info_bins, (const int**)matriz_adj, &phyLinha, 10, 5);
                //cout <<"iShack: " <<iShack << " j: " << j << " iNsc: " << iNsc <<endl;
                if(phyLinha < phyS_best){
                    phyS_best = phyLinha;
                    S_best = S_linha_linha;
                }
                if(bl == 0){
                    iNsc++;
                    bl = 0;
                }else{
                    iNsc = 0;
                }
                if(iNsc == Nsc){
                    pertubacao(S_linha_linha, items, 3, info_bins, (const int**)matriz_adj);
                    phyLinha = somatorio_phi(S_linha_linha, 10, 5);
                    iShack++;
                    bl = 0;
                    iNsc = 0;
                }
            }
        }
    }
    imprimir_bins(S_best, items);
    confere_peso(S_best, items);
    confere_conflitos(S_best, (const int**)matriz_adj);
    phyS_best = somatorio_phi(S_best, 10, 5);
    cout << "phi: "<< phyS_best << " klb: " << Klb << endl;

    //_______________________________________________________________________
    items.clear();
    S_inicial.clear();
    //S_best.clear();
    items.shrink_to_fit();
    S_inicial.shrink_to_fit();
    //S_best.shrink_to_fit();

    matriz_adj = libera_matriz(matriz_adj, info_bins.quantItens);
    delete matriz_adj;
}
