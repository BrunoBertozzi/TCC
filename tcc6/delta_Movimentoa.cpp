/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 06/08/2020
*
***************************************************************/
#include <iostream>
#include <vector>
#include <iostream>
#include<fstream>
#include <ctime>

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

int calcula_delta_realocate(const vector<Tbin> bins, const vector<Titem> itens, const int bin1, const int bin2, int *iten_1, const TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww, int tipoILS){
    int PhyAntes = 0;
    int PhyDepois = 0;
    int PesoBin1Depois = 0;
    int PesoBin2Depois = 0;
    int ConflitoBin1Depois = 0;
    int ConflitoBin2Depois = 0;
    int PesoBin1Antes = 0;
    int pesoBin2Antes = 0;
    int delta = 0;
    int melhor = 0;

    if(bins[bin1].pesoLivre < 0) PesoBin1Antes = ((bins[bin1].pesoLivre * (-1))* ww);
    else PesoBin1Antes = 0;

    if(bins[bin2].pesoLivre < 0) pesoBin2Antes = ((bins[bin2].pesoLivre * (-1))* ww);
    else pesoBin2Antes = 0;

    PhyAntes = PesoBin1Antes + pesoBin2Antes + (bins[bin1].numConflitos * wc) + (bins[bin2].numConflitos * wc);

    for(const auto& iten1: bins[bin1].items){

        PesoBin1Depois = ((bins[bin1].pesoLivre + itens[iten1-1].peso));
        PesoBin2Depois = ((bins[bin2].pesoLivre - itens[iten1-1].peso));

        if(PesoBin1Depois < 0) PesoBin1Depois = ((PesoBin1Depois * (-1))* ww);
        else PesoBin1Depois = 0;

        if(PesoBin2Depois < 0) PesoBin2Depois = ((PesoBin2Depois * (-1))* ww);
        else PesoBin2Depois = 0;

        ConflitoBin1Depois = 0;

        for(const auto& x: bins[bin1].items){
            if(x != iten1){
                if(matriz_adj[x-1][iten1-1] == 1)ConflitoBin1Depois += 1;
                if(matriz_adj[iten1-1][x-1] == 1)ConflitoBin1Depois += 1;
            }
        }

        ConflitoBin1Depois = (bins[bin1].numConflitos - ConflitoBin1Depois) * wc;

        ConflitoBin2Depois = 0;

        for(const auto& x: bins[bin2].items){
            if(matriz_adj[x-1][iten1-1] == 1 )ConflitoBin2Depois += 1;
            if( matriz_adj[iten1-1][x-1] == 1)ConflitoBin2Depois += 1;
        }

        ConflitoBin2Depois = (bins[bin2].numConflitos + ConflitoBin2Depois) * wc;

        PhyDepois = (PesoBin1Depois + PesoBin2Depois) + (ConflitoBin1Depois + ConflitoBin2Depois);

        delta = PhyDepois - PhyAntes;

        if(delta < melhor){
            *iten_1 = iten1;
            melhor = delta;
            if(tipoILS == 3)break;
        }

    }

    return melhor;
}

int calcula_delta_swap(const vector<Tbin> bins, const vector<Titem> itens, const int bin1, const int bin2, int *iten_1, int *iten_2, const TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww, int tipoILS){
    int PhyAntes = 0;
    int PhyDepois = 0;
    int PesoBin1Depois = 0;
    int PesoBin2Depois = 0;
    int ConflitoIten1 = 0;
    int ConflitoIten2 = 0;
    int ConflitoBin1Depois = 0;
    int ConflitoBin2Depois = 0;
    int PesoBin1Antes = 0;
    int pesoBin2Antes = 0;
    int delta = 0;
    int melhor = 0;

    if(bins[bin1].pesoLivre < 0) PesoBin1Antes = ((bins[bin1].pesoLivre * (-1))* ww);
    else PesoBin1Antes = 0;

    if(bins[bin2].pesoLivre < 0) pesoBin2Antes = ((bins[bin2].pesoLivre * (-1))* ww);
    else pesoBin2Antes = 0;

    PhyAntes = PesoBin1Antes + pesoBin2Antes + (bins[bin1].numConflitos * wc) + (bins[bin2].numConflitos * wc);

    for(const auto& iten1: bins[bin1].items){
        for(const auto& iten2: bins[bin2].items){

            PesoBin1Depois = ((bins[bin1].pesoLivre + itens[iten1-1].peso - itens[iten2-1].peso));
            PesoBin2Depois = ((bins[bin2].pesoLivre - itens[iten1-1].peso + itens[iten2-1].peso));

            if(PesoBin1Depois < 0) PesoBin1Depois = ((PesoBin1Depois * (-1))* ww);
            else PesoBin1Depois = 0;

            if(PesoBin2Depois < 0) PesoBin2Depois = ((PesoBin2Depois * (-1))* ww);
            else PesoBin2Depois = 0;

            ConflitoBin1Depois = 0;
            ConflitoIten1 = 0;
            ConflitoIten2 = 0;

            for(const auto& x: bins[bin1].items){
                if(matriz_adj[x-1][iten1-1] == 1)ConflitoIten1 += 1;
                if(matriz_adj[iten1-1][x-1] == 1)ConflitoIten1 += 1;
            }

            for(const auto& x: bins[bin1].items){
                if(x != iten1){
                    if(matriz_adj[x-1][iten2-1] == 1)ConflitoIten2 += 1;
                    if(matriz_adj[iten2-1][x-1] == 1)ConflitoIten2 += 1;
                }
            }

            ConflitoBin1Depois = (bins[bin1].numConflitos - ConflitoIten1 + ConflitoIten2) * wc;

            ConflitoBin2Depois = 0;
            ConflitoIten1 = 0;
            ConflitoIten2 = 0;

            for(const auto& x: bins[bin2].items){
                if(x != iten2){
                    if(matriz_adj[x-1][iten1-1] == 1)ConflitoIten1 += 1;
                    if(matriz_adj[iten1-1][x-1] == 1)ConflitoIten1 += 1;
                }
            }

            for(const auto& x: bins[bin2].items){
                if(matriz_adj[iten2-1][x-1] == 1)ConflitoIten2 += 1;
                if(matriz_adj[x-1][iten2-1] == 1)ConflitoIten2 += 1;
            }

            ConflitoBin2Depois = (bins[bin2].numConflitos + ConflitoIten1 - ConflitoIten2) * wc;

            PhyDepois = (PesoBin1Depois + PesoBin2Depois) + (ConflitoBin1Depois + ConflitoBin2Depois);

            delta = PhyDepois - PhyAntes;

            if(delta < melhor){
                *iten_1 = iten1;
                *iten_2 = iten2;
                melhor = delta;

                if(tipoILS == 3)break;
            }

        }
            if(tipoILS == 3 && (delta < 0))break;

    }

    return melhor;
}

int calcula_delta_swap_2_1(const vector<Tbin> bins, const vector<Titem> itens, const int bin1, const int bin2, int *iten_1, int *iten_2, int*iten_3, const TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww, int tipoILS){
	int PhyAntes = 0;
	int PhyDepois = 0;
	int delta = 0;
	int PesoBin1LivreAntes = 0;
	int PesoBin2LivreAntes = 0;
	int PesoBin1LivreDepois = 0;
	int PesoBin2LivreDepois = 0;
    int ConflitoBin1Depois = 0;
    int ConflitoBin2Depois = 0;
    int ConflitoIten1 = 0;
    int ConflitoIten2 = 0;
    int melhor = 0;

    if(bins[bin1].pesoLivre < 0) PesoBin1LivreAntes = ((bins[bin1].pesoLivre * (-1))* ww);
    else PesoBin1LivreAntes = 0;

    if(bins[bin2].pesoLivre < 0) PesoBin2LivreAntes = ((bins[bin2].pesoLivre * (-1))* ww);
    else PesoBin2LivreAntes = 0;

    PhyAntes = PesoBin1LivreAntes + PesoBin2LivreAntes + (bins[bin1].numConflitos * wc) + (bins[bin2].numConflitos * wc);



	for(const auto& iten3: bins[bin2].items){
        for(const auto& iten2: bins[bin1].items){
            for(const auto& iten1: bins[bin1].items){
            	if(iten1 != iten2){

            		PesoBin1LivreDepois = (bins[bin1].pesoLivre + itens[iten1-1].peso + itens[iten2-1].peso - itens[iten3-1].peso);
                    PesoBin2LivreDepois = (bins[bin2].pesoLivre - itens[iten1-1].peso - itens[iten2-1].peso + itens[iten3-1].peso);

					if(PesoBin1LivreDepois < 0) PesoBin1LivreDepois = ((PesoBin1LivreDepois * -1) * ww);
					else PesoBin1LivreDepois = 0;

					if(PesoBin2LivreDepois < 0) PesoBin2LivreDepois = ((PesoBin2LivreDepois * -1) * ww);
					else PesoBin2LivreDepois = 0;

                    ConflitoBin1Depois = 0;
                    ConflitoIten1 = 0;
                    ConflitoIten2 = 0;


                    for(const auto& x: bins[bin1].items){
                        if(x != iten2){
                            if(matriz_adj[x-1][iten1-1] == 1)ConflitoIten1++;
                            if(matriz_adj[iten1-1][x-1] == 1)ConflitoIten1++;
                        }
                        if(x != iten1){
                            if(matriz_adj[x-1][iten2-1] == 1)ConflitoIten1++;
                            if(matriz_adj[iten2-1][x-1] == 1)ConflitoIten1++;
                        }
                    }

                    if(matriz_adj[iten1-1][iten2-1] == 1)ConflitoIten1++;
                    if(matriz_adj[iten2-1][iten1-1] == 1)ConflitoIten1++;

                    for(const auto& x: bins[bin1].items){
                        if(x != iten1 && x != iten2){
                            if(matriz_adj[x-1][iten3-1] == 1)ConflitoIten2++;
                            if(matriz_adj[iten3-1][x-1] == 1)ConflitoIten2++;
                        }
                    }

                    ConflitoBin1Depois = (bins[bin1].numConflitos - ConflitoIten1 + ConflitoIten2) * wc;

                    ConflitoBin2Depois = 0;
                    ConflitoIten1 = 0;
                    ConflitoIten2 = 0;

                    for(const auto& x: bins[bin2].items){
                        if(x != iten3){
                            if(matriz_adj[x-1][iten1-1] == 1)ConflitoIten1++;
                            if(matriz_adj[iten1-1][x-1] == 1)ConflitoIten1++;
                            if(matriz_adj[x-1][iten2-1] == 1)ConflitoIten1++;
                            if(matriz_adj[iten2-1][x-1] == 1)ConflitoIten1++;
                        }
                    }

                    if(matriz_adj[iten1-1][iten2-1] == 1)ConflitoIten1++;
                    if(matriz_adj[iten2-1][iten1-1] == 1)ConflitoIten1++;

                    for(const auto& x: bins[bin2].items){
                            if(matriz_adj[x-1][iten3-1] == 1)ConflitoIten2++;
                            if(matriz_adj[iten3-1][x-1] == 1)ConflitoIten2++;
                    }

                    ConflitoBin2Depois = (bins[bin2].numConflitos + ConflitoIten1 - ConflitoIten2) * wc;

                    PhyDepois = (PesoBin1LivreDepois + PesoBin2LivreDepois) + (ConflitoBin1Depois + ConflitoBin2Depois);

                    delta = PhyDepois - PhyAntes;

                    if(delta < melhor){
                        *iten_1 = iten1;
                        *iten_2 = iten2;
                        *iten_3 = iten3;
                        melhor = delta;

                        if(tipoILS == 3)break;
                    }
            	}
            }
            if(tipoILS == 3 && (delta < 0))break;
        }
        if(tipoILS == 3 && (delta < 0))break;
    }

    return melhor;
}
