/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 20/07/2020
*
***************************************************************/
#ifndef ILS_1_H_INCLUDED
#define ILS_1_H_INCLUDED
#pragma once

void ILS_1(char *argv[]);
vector<int> carrega_vetor_bins_conflito(const vector<Tbin> &bins);
double buscaLocalILS1 (vector<Tbin> &bins, const vector<Titem> itens, TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww, int tipoILS);

#endif // ILS_1_H_INCLUDED
