/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 17/02/2021
*
***************************************************************/

#include <iostream>
#include <vector>
#include <ctime>


using namespace std;

//HEADERS
#include "head_struct.h"
#include "head_ILS.h"
#include "head_bins.h"
#include "head_buscalocal.h"
#include "head_pertubacao.h"

//TODOS COM TODOS

vector<Tbin> ILS1(vector<Tbin> &S_inicial ,const int **matriz_adj, const TinfoBins info_bins, char *argv[], const vector<Titem> items, int *phyS_Inicial, int Klb){
    // VARIAVEIS - VECTOR
    vector <Tbin> S_best;
    vector <Tbin> S_linha;
    vector <Tbin> S_linha_linha;

    // VARIAVEIS - Time
    clock_t start_time = clock();

    // VARIAVEIS - Int
    int deltaPhy = 0;
    int iShack = 0;
    int phyS_best = 0;
    int phyLinha = 0;
    int bl = 1;
    int tipoILS = atoi(argv[2]);
    int nSchak = atoi(argv[3]);
    int ww = atoi(argv[6]);
    int wc = atoi(argv[7]);
    int Sshack = atoi(argv[8]);

    // VARIAVEIS - Double
    double cpu_time_used;
    double time_limit = atof(argv[9]);

    phyS_best = *phyS_Inicial;
    phyLinha = phyS_best;

    S_best = S_inicial;
    S_linha = S_best;

    while(S_linha.size() > (unsigned)Klb && phyLinha <= phyS_best && (cpu_time_used < time_limit)){

        S_linha = S_best;
        phyLinha = phyS_best;
        phyLinha = remove_bin_phy (S_linha, items, (const int**)matriz_adj, ww, wc, phyLinha);


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

    *phyS_Inicial = phyS_best;

    return S_best;
}



vector<Tbin> ILS2(vector<Tbin> &S_inicial ,const int **matriz_adj, const TinfoBins info_bins, char *argv[], const vector<Titem> items, int *phyS_Inicial, int Klb){
    // VARIAVEIS - VECTOR
    vector <Tbin> S_best;
    vector <Tbin> S_linha;
    vector <Tbin> S_linha_linha;

    // VARIAVEIS - Time
    clock_t start_time = clock();

    // VARIAVEIS - Int
    int phyS_best = 0;
    int phyLinha = 0;
    int deltaPhy = 0;
    int iShack = 0;
    int tipoILS = atoi(argv[2]);
    int nSchak  = atoi(argv[3]);
    int Nls = atoi(argv[4]);
    int Nsc = atoi(argv[5]);
    int iNsc = 0;
    int ww = atoi(argv[6]);
    int wc = atoi(argv[7]);
    int Sshack = atoi(argv[8]);
    int bl = 0;

    // VARIAVEIS - Double
    double cpu_time_used;
    double time_limit = atof(argv[9]);

    phyS_best = *phyS_Inicial;
    phyLinha = phyS_best;

    S_best = S_inicial;
    S_linha = S_best;

    while(S_linha.size() > (unsigned)Klb && phyLinha <= phyS_best && (cpu_time_used < time_limit)){
        S_linha = S_best;
        phyLinha = phyS_best;
        phyLinha = remove_bin_phy (S_linha, items, (const int**)matriz_adj, ww, wc, phyLinha);
        S_linha_linha = S_linha;
        iShack = 0;
        iNsc = 0;
        bl = 0;

        while(((phyLinha > phyS_best) && (iShack < nSchak))&& (cpu_time_used < time_limit)){
            iNsc = 0;
            bl = 0;
            for(int j = 0; j < Nls; j++){
                bl = busca_local_ILS2(S_linha_linha, items, info_bins, (const int**)matriz_adj, wc, ww, tipoILS);
                phyLinha = phyLinha + bl;
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
                    deltaPhy = pertubacao(S_linha_linha, items, Sshack, info_bins, (const int**)matriz_adj, ww, wc);
                    phyLinha = phyLinha + deltaPhy;

                    iShack++;
                    bl = 0;
                    iNsc = 0;
                }
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

    *phyS_Inicial = phyS_best;

    return S_best;
}

vector<Tbin> ILS3(vector<Tbin> &S_inicial ,const int **matriz_adj, const TinfoBins info_bins, char *argv[], const vector<Titem> items, int *phyS_Inicial, int Klb){
    // VARIAVEIS - VECTOR
    vector <Tbin> S_best;
    vector <Tbin> S_linha;
    vector <Tbin> S_linha_linha;

    // VARIAVEIS - Time
    clock_t start_time = clock();

    // VARIAVEIS - Int
    int deltaPhy = 0;
    int phyS_best = 0;
    int phyLinha = 0;
    int iShack = 0;
    int bl = 1;
    int tipoILS = atoi(argv[2]);
    int nSchak = atoi(argv[3]);
    int ww = atoi(argv[6]);
    int wc = atoi(argv[7]);
    int Sshack = atoi(argv[8]);

    // VARIAVEIS - Double
    double cpu_time_used;
    double time_limit = atof(argv[9]);

    phyS_best = *phyS_Inicial;

    S_best = S_inicial;
    S_linha = S_best;

    while(S_linha.size() > (unsigned)Klb && phyLinha <= phyS_best && (cpu_time_used < time_limit)){
        S_linha = S_best;
        phyLinha = phyS_best;
        phyLinha = remove_bin_phy (S_linha, items, (const int**)matriz_adj, ww, wc, phyLinha);

        S_linha_linha = S_linha;
        iShack = 0;

        while(((phyLinha > phyS_best) && (iShack < nSchak)) && (cpu_time_used < time_limit)){
            bl = 1;

            while(bl != 0 ){
                bl = busca_local_ILS3(S_linha_linha, items, info_bins, (const int**)matriz_adj, wc, ww, start_time, time_limit, tipoILS);
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

    *phyS_Inicial = phyS_best;

    return S_best;
}
