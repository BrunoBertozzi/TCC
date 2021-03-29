/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 17/02/2021
*
***************************************************************/

#include <iostream>
#include <vector>

using namespace std;

//HEADERS
#include "head_struct.h"
#include "head_buscalocal.h"
#include "head_delta_mov.h"
#include "head_mov_buscalocal.h"


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

    return delta_melhor;
}
int busca_local_ILS3(vector<Tbin> &bins, const vector<Titem> itens, TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww, int start_time,int time_limit, int tipoILS){
    int iten1 = 0, iten2 = 0, iten3 = 0;
    int  iten1_m = 0, iten2_m = 0, iten3_m = 0;
    int bin1_m = 0, bin2_m = 0;
    int deltaMovimento = 0, delta_melhor = 0;
    int movimento = 0;
    int aleatorio = 0;
    int rand_vet[3] = {1 ,2 ,3};

    //double cpu_time_used = 0;

    vector<int> bins_c_conflito;

    bins_c_conflito = carrega_vetor_bins_conflito(bins);

    if(bins_c_conflito.size() > 0){
    	unsigned int i = 0;
    	while(i < bins_c_conflito.size() && movimento == 0){
    		unsigned int j = 0;
    		while(j < bins.size() && movimento == 0){
    			movimento = 0;
    			if(bins_c_conflito[i] != bins[j].id_bin-1){
    				if(bins[i].id_bin != bins[j].id_bin){
                        randomize(rand_vet, 3);
                        aleatorio = 0;
    					while(aleatorio < 3 && movimento == 0){

                            if(movimento == 0 && rand_vet[aleatorio] == 1){
                                deltaMovimento = calcula_delta_swap(bins, itens, bins_c_conflito[i], bins[j].id_bin-1, &iten1, &iten2, infoBins, (const int**)matriz_adj, wc, ww, tipoILS);

                                if(deltaMovimento < delta_melhor){
                                    delta_melhor = deltaMovimento;
                                    movimento = 1;
                                    iten1_m = iten1;
                                    iten2_m = iten2;
                                    bin1_m = bins_c_conflito[i];
                                    bin2_m = bins[j].id_bin-1;
                                    break;
                                }
                            }

                            if(movimento == 0 && rand_vet[aleatorio] == 2 && bins[bins_c_conflito[i]].items.size() > 1 ){
                                deltaMovimento = calcula_delta_realocate(bins, itens, bins_c_conflito[i], bins[j].id_bin-1, &iten1, infoBins, (const int**)matriz_adj, wc, ww, tipoILS);
                                if(deltaMovimento < delta_melhor){
                                    delta_melhor = deltaMovimento;
                                    movimento = 2;
                                    iten1_m = iten1;
                                    bin1_m = bins_c_conflito[i];
                                    bin2_m = bins[j].id_bin-1;
                                    break;
                                }
                            }

                            if(movimento == 0 && rand_vet[aleatorio] == 3 && bins[bins_c_conflito[i]].items.size() >= 2 && bins[bins[j].id_bin-1].items.size() >= 1){
                                deltaMovimento = calcula_delta_swap_2_1(bins, itens, bins_c_conflito[i], bins[j].id_bin-1, &iten1, &iten2, &iten3, infoBins, (const int**)matriz_adj, wc, ww, tipoILS);

                                if(deltaMovimento < delta_melhor){
                                    delta_melhor = deltaMovimento;
                                    movimento = 3;
                                    iten1_m = iten1;
                                    iten2_m = iten2;
                                    iten3_m = iten3;
                                    bin1_m = bins_c_conflito[i];
                                    bin2_m = bins[j].id_bin-1;
                                    break;
                                }
                            }
                            aleatorio++;
                        }
    				}
    			}
    			j++;
    		}
    		i++;
    	}

   	if(movimento == 1 )Swap(iten1_m, iten2_m, bin1_m, bin2_m, bins, itens, (const int**)matriz_adj, infoBins.quantItens);
    if(movimento == 2 )realocate(iten1_m, bin1_m, bin2_m, bins, itens, (const int**)matriz_adj, infoBins.quantItens);
    if(movimento == 3)Swap2_1(iten1_m, iten2_m, iten3_m, bin1_m, bin2_m, bins, itens, (const int**)matriz_adj, infoBins.quantItens);
    if(movimento == 0) delta_melhor = 0;
    }

   	return delta_melhor;
}

int busca_local_ILS2(vector<Tbin> &bins, const vector<Titem> itens, TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww, int tipoILS){
    int iten1 = 0, iten2 = 0, iten3 = 0;
    int  iten1_m = 0, iten2_m = 0, iten3_m = 0;
    int bin1_m = 0, bin2_m = 0;

    int delta_movimento = 0, delta_melhor = 0;
    int movimento = 0;

    int bin1, bin2;

    vector<int> bins_c_conflito = carrega_vetor_bins_conflito(bins);


    if(bins_c_conflito.size() > 0){
        bin1 = rand() % bins_c_conflito.size();
        bin1 = bins_c_conflito[bin1];

        do{
            bin2 = rand() % bins.size();
        }while(bins[bin1].id_bin == bins[bin2].id_bin);

    }else{
        bin1 = rand() % bins.size();

        do{
            bin2 = rand() % bins.size();
        }while(bin1 == bin2);
    }

    delta_movimento = calcula_delta_swap(bins, itens, bin1, bin2, &iten1, &iten2, infoBins, (const int**)matriz_adj, wc, ww, tipoILS);
    if(delta_movimento < delta_melhor){
        delta_melhor = delta_movimento;
        movimento = 1;
        iten1_m = iten1;
        iten2_m = iten2;
        bin1_m = bin1;
        bin2_m = bin2;
    }

    if(bins[bin1].items.size() > 1 ){
        delta_movimento = calcula_delta_realocate(bins, itens, bin1, bin2, &iten1, infoBins, (const int**)matriz_adj, wc, ww, tipoILS);
        if(delta_movimento < delta_melhor){
            delta_melhor = delta_movimento;
            movimento = 2;
            iten1_m = iten1;
            bin1_m = bin1;
            bin2_m = bin2;
        }
    }

    if(bins[bin2].items.size() >= 2 && bins[bin1].items.size() >= 1){
        delta_movimento = calcula_delta_swap_2_1(bins, itens, bin1, bin2, &iten1, &iten2, &iten3, infoBins, (const int**)matriz_adj, wc, ww, tipoILS);
        if(delta_movimento < delta_melhor){
            delta_melhor = delta_movimento;
            movimento = 3;
            iten1_m = iten1;
            iten2_m = iten2;
            iten3_m = iten3;
            bin1_m = bin1;
            bin2_m = bin2;
        }
    }

    if(movimento == 1 )Swap(iten1_m, iten2_m, bin1_m, bin2_m, bins, itens, (const int**)matriz_adj, infoBins.quantItens);
    if(movimento == 2 )realocate(iten1_m, bin1_m, bin2_m, bins, itens, (const int**)matriz_adj, infoBins.quantItens);
    if(movimento == 3)Swap2_1(iten1_m, iten2_m, iten3_m, bin1_m, bin2_m, bins, itens, (const int**)matriz_adj, infoBins.quantItens);
    if(movimento == 0) delta_melhor = 0;

    return delta_melhor;
}

//_______________________________________TOOLS BUSCA LOCAL______________________________________


void swap1 (int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

vector<int> carrega_vetor_bins_conflito(const vector<Tbin> &bins){
    vector<int> bins_c_conflito;

    for(const auto& bin: bins)
        if(bin.numConflitos > 0 || bin.pesoLivre < 0)
            bins_c_conflito.push_back((bin.id_bin-1));

    return bins_c_conflito;
}

void randomize (int arr[], int n){
    for (int i = n - 1; i > 0; i--){
        int j = rand() % (i + 1);
        swap1(&arr[i], &arr[j]);
    }
}
