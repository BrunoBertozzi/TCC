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
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>

using namespace std;

//HEADERS
#include "structs.h"
#include "arquivo.h"
#include "ILS_1.h"
#include "matriaz_Adj.h"
#include "bins.h"
#include "solucao_Inicial.h"
#include "algoritmo_Verificacao.h"
#include "Phy.h"
#include "delta_Movimentoa.h"
#include "movimento_BL.h"
#include "pertubacao.h"

void ILS_1(char *argv[]){
//VARIAVEIS
   clock_t start_time = clock();

    TinfoBins info_bins;

    vector <Titem> items;
    vector <Tbin> S_inicial;
    vector <Tbin> S_best;
    vector <Tbin> S_linha;
    vector <Tbin> S_linha_linha;

    int **matriz_adj;
    int Klb;
    int phyS_best, phyLinha = 0;
    int deltaPhy = 0;
    int iShack = 0;
    int tipoILS = atoi(argv[2]);
    int nSchak = atoi(argv[3]);
    int bl = 1;
    int ww = atoi(argv[6]);
    int wc = atoi(argv[7]);
    int Sshack = atoi(argv[8]);

    double cpu_time_used;
    double time_limit = atof(argv[9]);

//PRE CARREGAMENTO
    items = ler_arquivo_instancias(&info_bins, argv[1]);
    matriz_adj = alocar_matriz(info_bins.quantItens, info_bins.quantItens);
    carrega_matrizAdj_linux(matriz_adj, argv[1]);
    criar_bins(S_inicial , info_bins);
    firstFit_ordenado(S_inicial, items, info_bins, (const int**)matriz_adj);
    //_______________________________________________________________________

    phyS_best = somatorio_phi(S_inicial, wc, ww);
    phyLinha = phyS_best;
    Klb = calcula_Klb(items, info_bins);

    S_best = S_inicial;
    S_linha = S_best;


       while(S_linha.size() > (unsigned)Klb && phyLinha <= phyS_best && (cpu_time_used < time_limit)){

        S_linha = S_best;
        phyLinha = phyS_best;
        phyLinha = remove_bin_phy2 (S_linha, items, (const int**)matriz_adj, ww, wc, phyLinha);


        S_linha_linha = S_linha;

        iShack = 0;

        while(((phyLinha > phyS_best) && (iShack < nSchak))&& (cpu_time_used < time_limit)){
            bl = 1;

            while(bl != 0 && (cpu_time_used < time_limit)){
                bl = buscaLocalILS1(S_linha_linha, items, info_bins, (const int**)matriz_adj, wc, ww, tipoILS);
                phyLinha = phyLinha + bl;
                cpu_time_used = ((double) (clock() - start_time)) / CLOCKS_PER_SEC;
            }

            if(phyLinha < phyS_best){
                phyS_best = phyLinha;
                S_best = S_linha_linha;
            }else{
                deltaPhy = pertubacao(S_linha_linha, items, Sshack, info_bins, (const int**)matriz_adj, ww, wc);
                phyLinha = phyLinha + deltaPhy;

                iShack++;
            }
            cpu_time_used = ((double) (clock() - start_time)) / CLOCKS_PER_SEC;
        }
        cpu_time_used = ((double) (clock() - start_time)) / CLOCKS_PER_SEC;
    }
    //_______________________________________________________________________
    clock_t end_time = clock();

    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    imprimir_bins_2 (S_best, items, cpu_time_used);

    //imprimir_bins(S_best, items);
    //Vconfere_conflitos(S_best, matriz_adj);
    //Vconfere_peso(S_best,items, info_bins.quantItens);
    //Vconfere_peso_limite (S_best, info_bins.pesoBin);

    matriz_adj = libera_matriz(matriz_adj, info_bins.quantItens);
    delete matriz_adj;

}

int buscaLocalILS1 (vector<Tbin> &bins, const vector<Titem> itens, TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww, int tipoILS){
    int iten1 = 0, iten2 = 0, iten3 = 0;        // itens auxiliares para calculo de delta
    int iten1_m = 0, iten2_m = 0, iten3_m = 0;  // melhores itens para movimento depois do calculo de delta
    int bin1_m = 0, bin2_m = 0;                 // melhores bins para movimento depois do calculo de delta

    int delta_movimento = 0;
    int delta_melhor = 0;                       //Melhor Delta

    int movimento = 0;                          //Movimento executado
    int size_bins_c_conflito = 0;

    vector<int> bins_c_conflito = carrega_vetor_bins_conflito(bins);    // Vetor de bins com conflito ou peso + que limite

    size_bins_c_conflito = bins_c_conflito.size();

    if(size_bins_c_conflito > 0){
        for(int i = 0; i < size_bins_c_conflito; i++){
            for(unsigned int j = 0; j < bins.size(); j++){
                if(bins_c_conflito[i] != bins[j].id_bin-1){
                    if(bins[i].id_bin != bins[j].id_bin){
                        if(bins[bins_c_conflito[i]].items.size() > 1 ){
                            delta_movimento = calcula_delta_realocate(bins, itens, bins_c_conflito[i], bins[j].id_bin-1, &iten1, infoBins, (const int**)matriz_adj, wc, ww, tipoILS);
                            if(delta_movimento < delta_melhor){
                                delta_melhor = delta_movimento;
                                movimento = 2;
                                iten1_m = iten1;
                                bin1_m = bins_c_conflito[i];
                                bin2_m = bins[j].id_bin-1;
                            }
                        }
                        delta_movimento = calcula_delta_swap(bins, itens, bins_c_conflito[i], bins[j].id_bin-1, &iten1, &iten2, infoBins, (const int**)matriz_adj, wc, ww, tipoILS);
                        if(delta_movimento < delta_melhor){
                            delta_melhor = delta_movimento;
                            movimento = 1;
                            iten1_m = iten1;
                            iten2_m = iten2;
                            bin1_m = bins_c_conflito[i];
                            bin2_m = bins[j].id_bin-1;
                        }
                        if(bins[bins_c_conflito[i]].items.size() >= 2 && bins[bins[j].id_bin-1].items.size() >= 1){
                            delta_movimento = calcula_delta_swap_2_1(bins, itens, bins_c_conflito[i], bins[j].id_bin-1, &iten1, &iten2, &iten3, infoBins, (const int**)matriz_adj, wc, ww, tipoILS);
                            if(delta_movimento < delta_melhor){
                                delta_melhor = delta_movimento;
                                movimento = 3;
                                iten1_m = iten1;
                                iten2_m = iten2;
                                iten3_m = iten3;
                                bin1_m = bins_c_conflito[i];
                                bin2_m = bins[j].id_bin-1;
                            }
                        }
                    }
                }
            }
        }
    }

    if(movimento == 1) Swap(iten1_m, iten2_m, bin1_m, bin2_m, bins, itens, (const int**)matriz_adj, infoBins.quantItens);
    if(movimento == 2) realocate(iten1_m, bin1_m, bin2_m, bins, itens, (const int**)matriz_adj, infoBins.quantItens);
    if(movimento == 3) Swap2_1(iten1_m, iten2_m, iten3_m, bin1_m, bin2_m, bins, itens, (const int**)matriz_adj, infoBins.quantItens);
    if(movimento == 0) delta_melhor = 0;

    //cout << " movimento: " << movimento << " bin1: "<< bin1_m << " iten1: " << iten1_m <<  " iten2: " << iten2_m << " bin2: "<< bin2_m << " iten3: " << iten3_m << " delta melhor: " << delta_melhor << endl;


    return delta_melhor;
}

vector<int> carrega_vetor_bins_conflito(const vector<Tbin> &bins){
    vector<int> bins_c_conflito;

    for(const auto& bin: bins)
        if(bin.numConflitos > 0 || bin.pesoLivre < 0)
            bins_c_conflito.push_back((bin.id_bin-1));

    return bins_c_conflito;
}

