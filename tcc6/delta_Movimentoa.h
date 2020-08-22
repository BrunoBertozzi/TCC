/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 20/07/2020
*
***************************************************************/
#ifndef DELTA_MOVIMENTOA_H_INCLUDED
#define DELTA_MOVIMENTOA_H_INCLUDED
#pragma once

int calcula_delta_realocate(const vector<Tbin> bins, const vector<Titem> itens, const int bin1, const int bin2, int *iten_1, const TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww, int tipoILS);
int calcula_delta_swap(const vector<Tbin> bins, const vector<Titem> itens, const int bin1, const int bin2, int *iten_1, int *iten_2, const TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww, int tipoILS);
int calcula_delta_swap_2_1(const vector<Tbin> bins, const vector<Titem> itens, const int bin1, const int bin2, int *iten_1, int *iten_2, int*iten_3, const TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww, int tipoILS);

#endif // DELTA_MOVIMENTOA_H_INCLUDED
