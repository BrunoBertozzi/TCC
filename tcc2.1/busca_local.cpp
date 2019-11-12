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
#include <cstdlib>
#include <ctime>
#include <algorithm>

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

int busca_local(vector<Tbin> &bins, const vector<Titem> itens, TinfoBins infoBins, const int **matriz_adj, int *phyI){
    int iten1 = 0, iten2 = 0, iten3 = 0;
    int  iten1_m = 0, iten2_m = 0, iten3_m = 0;
    int bin1_m = 0, bin2_m = 0;
    int delta_realocate = 0, delta_swap = 0, delta_swap_2_1 = 0, delta_melhor = 0;
    int movimento = 0;
    vector<int> bins_c_conflito = carrega_vetor_bins_conflito(bins);
    //int bin1, bin2;
    int cont_swap = 0, cont_realoc = 0, cont_swap2_1 = 0;

            //bin1 = rand() % bins.size();

            if(bins_c_conflito.size() > 0){

                for(unsigned int i = 0; i < bins_c_conflito.size(); i++){
                    for(unsigned int j = 0; j < bins.size(); j++){
                        if(bins_c_conflito[i] != bins[j].id_bin-1){
                        /*do{
                            bin2 = rand() % bins_c_conflito.size();

                            if(bin1 == 0 && bin2 == 0 && bins_c_conflito.size() == 1)
                                bin1 = rand() % bins.size();
                        }while(bins[bin1].id_bin == bins[bin2].id_bin);*/

                            if(bins[i].id_bin != bins[j].id_bin){
                                delta_swap = calcula_delta_swap(bins, itens, bins_c_conflito[i], bins[j].id_bin-1, &iten1, &iten2, infoBins, (const int**)matriz_adj);
                                if(delta_swap > delta_melhor){
                                    delta_melhor = delta_swap;
                                    movimento = 1;
                                    iten1_m = iten1;
                                    iten2_m = iten2;
                                    bin1_m = bins_c_conflito[i];
                                    bin2_m = bins[j].id_bin-1;
                                }

                                if(bins[bins_c_conflito[i]].items.size() > 1 ){
                                    delta_realocate = calcula_delta_realocate(bins, itens, bins_c_conflito[i], bins[j].id_bin-1, &iten1, infoBins, (const int**)matriz_adj);
                                    if(delta_realocate > delta_melhor){
                                        delta_melhor = delta_realocate;
                                        movimento = 2;
                                        iten1_m = iten1;
                                        bin1_m = bins_c_conflito[i];
                                        bin2_m = bins[j].id_bin-1;
                                    }
                                }

                                if(bins[bins_c_conflito[i]].items.size() >= 2 && bins[bins[j].id_bin-1].items.size() >= 1){
                                    delta_swap_2_1 = calcula_delta_swap_2_1(bins, itens, bins_c_conflito[i], bins[j].id_bin-1, &iten1, &iten2, &iten3, infoBins, (const int**)matriz_adj);
                                    if(delta_swap_2_1 > delta_melhor){
                                        delta_melhor = delta_swap_2_1;
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
                    }//
                }
            }
            /*else{
                do{
                    bin2 = rand() % bins.size();

                }while(bin1 == bin2);

                delta_swap = calcula_delta_swap(bins, itens, bins[bin2].id_bin-1, bins[bin1].id_bin-1, &iten1, &iten2, infoBins, (const int**)matriz_adj);

                if(delta_swap > delta_melhor){
                    delta_melhor = delta_swap;
                    movimento = 1;
                    iten1_m = iten1;
                    iten2_m = iten2;
                    bin1_m = bins[bin2].id_bin-1;
                    bin2_m = bins[bin1].id_bin-1;
                }

                delta_realocate = calcula_delta_realocate(bins, itens, bins[bin2].id_bin-1, bins[bin1].id_bin-1, &iten1, infoBins, (const int**)matriz_adj);

                if(delta_realocate > delta_melhor){
                    delta_melhor = delta_realocate;
                    movimento = 2;
                    iten1_m = iten1;
                    bin1_m = bins[bin2].id_bin-1;
                    bin2_m = bins[bin1].id_bin-1;
                }

                delta_swap_2_1 = calcula_delta_swap_2_1(bins, itens, bins[bin2].id_bin-1, bins[bin1].id_bin-1, &iten1, &iten2, &iten3, infoBins, (const int**)matriz_adj);

                if(delta_swap_2_1 > delta_melhor){
                    delta_melhor = delta_swap_2_1;
                    movimento = 3;
                    iten1_m = iten1;
                    iten2_m = iten2;
                    iten3_m = iten3;
                    bin1_m = bins[bin2].id_bin-1;
                    bin2_m = bins[bin1].id_bin-1;
                }
            }*/

   if(movimento == 1 ){
        //cout<< "SWAPPPPPPP" << endl;
        cont_swap++;
        Swap(iten1_m, iten2_m, bin1_m, bin2_m, bins, itens, (const int**)matriz_adj, infoBins.quantItens);
        *phyI = *phyI - delta_melhor;
    }

    if(movimento == 2 ){
            //cout<< "REALOCATEEEEEEEE" << endl;
            cont_realoc++;
        realocate(iten1_m, bin1_m, bin2_m, bins, itens, (const int**)matriz_adj, infoBins.quantItens);
        *phyI = *phyI - delta_melhor;
    }

    if(movimento == 3){
            //cout<< "SWAPPPPPPP        2 - 1" << endl;
            cont_swap2_1++;
        Swap2_1(iten1_m, iten2_m, iten3_m, bin2_m, bin1_m, bins, itens, (const int**)matriz_adj, infoBins.quantItens);
        *phyI = *phyI - delta_melhor;
    }

    //cout << "Phi: " << *phyI << endl;
    //cout << " movimento: " << movimento<< " swap: " << cont_swap << " realoc: " << cont_realoc << " swap2_1: " << cont_swap2_1
    //<< " bin1: "<< bin1_m << " iten1: " << iten1_m <<  " iten2: " << iten2_m << " bin2: "<< bin2_m << " iten3: " << iten3_m << " delta melhor: " << delta_melhor << endl;



    return movimento;
}

vector<int> carrega_vetor_bins_conflito(const vector<Tbin> &bins){
    vector<int> bins_c_conflito;

    for(const auto& bin: bins)
        if(bin.numConflitos > 0 || bin.pesoLivre < 0)
            bins_c_conflito.push_back(bin.id_bin-1);

    return bins_c_conflito;
}


void realocate(int id_item, int id_bin1, int id_bin2, vector<Tbin> &bins, const vector<Titem> itens, const int **matriz_adj, const int quant_itens){
        int cont = 0;

        for(auto&& iten: bins[id_bin1].items){
            if(iten == id_item){
                //bins[id_bin1].items.erase(bins[id_bin1].items.begin()+ cont);
                bins[id_bin1].items = erase_int(bins[id_bin1].items, cont);
            }
            cont++;
        }

        bins[id_bin1].pesoUsado -= itens[id_item-1].peso;
        bins[id_bin1].pesoLivre += itens[id_item-1].peso;
        bins[id_bin1].numConflitos = 0;

        for(const auto& iten: bins[id_bin1].items)
            bins[id_bin1].numConflitos += conflito_por_bin(bins[id_bin1].items, iten, (const int**)matriz_adj);

        bins[id_bin2].items.push_back(id_item);
        bins[id_bin2].pesoUsado += itens[id_item-1].peso;
        bins[id_bin2].pesoLivre -= itens[id_item-1].peso;
        bins[id_bin2].numConflitos = 0;

        for(const auto& iten: bins[id_bin2].items)
            bins[id_bin2].numConflitos += conflito_por_bin(bins[id_bin2].items, iten, (const int**)matriz_adj);

        //atualizar_conflito_iten_bin(matriz_adj, matriz_iten_bin, quant_itens, id_bin1, id_bin2, id_item);
}

void Swap (const int id_item1, const int id_item2, const int id_bin1, const int id_bin2, vector<Tbin> &bins, const vector<Titem> itens, const int **matriz_adj, const int quant_itens){
     realocate(id_item1, id_bin1, id_bin2, bins, itens, (const int**)matriz_adj, quant_itens);
     realocate(id_item2, id_bin2, id_bin1, bins, itens, (const int**)matriz_adj, quant_itens);

}

void Swap2_1(const int id_item1, const int id_item2, const int id_item3, const int id_bin1, const int id_bin2, vector<Tbin> &bins, const vector<Titem> itens, const int **matriz_adj, const int quant_itens){
    realocate(id_item1, id_bin2, id_bin1, bins, itens, (const int**)matriz_adj, quant_itens);
    realocate(id_item2, id_bin2, id_bin1, bins, itens, (const int**)matriz_adj, quant_itens);
    realocate(id_item3, id_bin1, id_bin2, bins, itens, (const int**)matriz_adj, quant_itens);
}


