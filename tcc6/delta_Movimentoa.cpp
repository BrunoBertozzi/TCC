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

double calcula_delta_realocate(const vector<Tbin> bins, const vector<Titem> itens, const int bin1, const int bin2, int *iten_1, const TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww, int tipoILS){
    double PhyAntes = 0;
    double PhyDepois = 0;
    double PesoBin1Depois = 0;
    double PesoBin2Depois = 0;
    double ConflitoBin1Depois = 0;
    double ConflitoBin2Depois = 0;
    double PesoBin1Antes = 0;
    double pesoBin2Antes = 0;
    double delta = 0;
    double melhor = 0;

    if(bins[bin1].pesoLivre < 0) PesoBin1Antes = (double)((bins[bin1].pesoLivre * (-1))* ww);
    else PesoBin1Antes = 0;

    if(bins[bin2].pesoLivre < 0) pesoBin2Antes = (double)((bins[bin2].pesoLivre * (-1))* ww);
    else pesoBin2Antes = 0;

    PhyAntes = PesoBin1Antes + pesoBin2Antes + (double)(bins[bin1].numConflitos * wc) + (double)(bins[bin2].numConflitos * wc);

    for(const auto& iten1: bins[bin1].items){

        PesoBin1Depois = (double)((bins[bin1].pesoLivre + itens[iten1-1].peso));
        PesoBin2Depois = (double)((bins[bin2].pesoLivre - itens[iten1-1].peso));

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

        ConflitoBin1Depois = (double)((bins[bin1].numConflitos - ConflitoBin1Depois) * wc);

        ConflitoBin2Depois = 0;

        for(const auto& x: bins[bin2].items){
            if(matriz_adj[x-1][iten1-1] == 1 )ConflitoBin2Depois += 1;
            if( matriz_adj[iten1-1][x-1] == 1)ConflitoBin2Depois += 1;
        }

        ConflitoBin2Depois = (double)((bins[bin2].numConflitos + ConflitoBin2Depois) * wc);

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

double calcula_delta_swap(const vector<Tbin> bins, const vector<Titem> itens, const int bin1, const int bin2, int *iten_1, int *iten_2, const TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww, int tipoILS){
    double PhyAntes = 0;
    double PhyDepois = 0;
    double PesoBin1Depois = 0;
    double PesoBin2Depois = 0;
    double ConflitoIten1 = 0;
    double ConflitoIten2 = 0;
    double ConflitoBin1Depois = 0;
    double ConflitoBin2Depois = 0;
    double PesoBin1Antes = 0;
    double pesoBin2Antes = 0;
    double delta = 0;
    double melhor = 0;

    if(bins[bin1].pesoLivre < 0) PesoBin1Antes = (double)((bins[bin1].pesoLivre * (-1))* ww);
    else PesoBin1Antes = 0;

    if(bins[bin2].pesoLivre < 0) pesoBin2Antes = (double)((bins[bin2].pesoLivre * (-1))* ww);
    else pesoBin2Antes = 0;

    PhyAntes = PesoBin1Antes + pesoBin2Antes + (double)(bins[bin1].numConflitos * wc) + (double)(bins[bin2].numConflitos * wc);

    for(const auto& iten1: bins[bin1].items){
        for(const auto& iten2: bins[bin2].items){

            PesoBin1Depois = (double)((bins[bin1].pesoLivre + itens[iten1-1].peso - itens[iten2-1].peso));
            PesoBin2Depois = (double)((bins[bin2].pesoLivre - itens[iten1-1].peso + itens[iten2-1].peso));

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

            ConflitoBin1Depois = (double)((bins[bin1].numConflitos - ConflitoIten1 + ConflitoIten2) * wc);

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

            ConflitoBin2Depois = (double)((bins[bin2].numConflitos + ConflitoIten1 - ConflitoIten2) * wc);

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

double calcula_delta_swap_2_1(const vector<Tbin> bins, const vector<Titem> itens, const int bin1, const int bin2, int *iten_1, int *iten_2, int*iten_3, const TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww, int tipoILS){
	double PhyAntes = 0;
	double PhyDepois = 0;
	double delta = 0;
	double PesoBin1LivreAntes = 0;
	double PesoBin2LivreAntes = 0;
	double PesoBin1LivreDepois = 0;
	double PesoBin2LivreDepois = 0;
    double ConflitoBin1Depois = 0;
    double ConflitoBin2Depois = 0;
    double ConflitoIten1 = 0;
    double ConflitoIten2 = 0;
    double melhor = 0;

    if(bins[bin1].pesoLivre < 0) PesoBin1LivreAntes = (double)((bins[bin1].pesoLivre * (-1))* ww);
    else PesoBin1LivreAntes = 0;

    if(bins[bin2].pesoLivre < 0) PesoBin2LivreAntes = (double)((bins[bin2].pesoLivre * (-1))* ww);
    else PesoBin2LivreAntes = 0;

    PhyAntes = PesoBin1LivreAntes + PesoBin2LivreAntes + (double)(bins[bin1].numConflitos * wc) + (double)(bins[bin2].numConflitos * wc);



	for(const auto& iten3: bins[bin2].items){
        for(const auto& iten2: bins[bin1].items){
            for(const auto& iten1: bins[bin1].items){
            	if(iten1 != iten2){

            		PesoBin1LivreDepois = (double)(bins[bin1].pesoLivre + itens[iten1-1].peso + itens[iten2-1].peso - itens[iten3-1].peso);
                    PesoBin2LivreDepois = (double)(bins[bin2].pesoLivre - itens[iten1-1].peso - itens[iten2-1].peso + itens[iten3-1].peso);

					if(PesoBin1LivreDepois < 0) PesoBin1LivreDepois = (double)((PesoBin1LivreDepois * -1) * ww);
					else PesoBin1LivreDepois = 0;

					if(PesoBin2LivreDepois < 0) PesoBin2LivreDepois = (double)((PesoBin2LivreDepois * -1) * ww);
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

                    ConflitoBin1Depois = (double)((bins[bin1].numConflitos - ConflitoIten1 + ConflitoIten2) * wc);

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

                    ConflitoBin2Depois = (double)((bins[bin2].numConflitos + ConflitoIten1 - ConflitoIten2) * wc);

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
