/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 17/02/2021
*
***************************************************************/

#ifndef HEAD_BUSCALOCAL_H_INCLUDED
#define HEAD_BUSCALOCAL_H_INCLUDED
#pragma once

vector<int> carrega_vetor_bins_conflito(const vector<Tbin> &bins);
int buscaLocalILS1 (vector<Tbin> &bins, const vector<Titem> itens, TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww, int tipoILS); // Todos com todos
int busca_local_ILS2(vector<Tbin> &bins, const vector<Titem> itens, TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww, int tipoILS);
int busca_local_ILS3(vector<Tbin> &bins, const vector<Titem> itens, TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww, int start_time,int time_limit, int tipoILS); // Primeira melhora

void swap1 (int *a, int *b);
void randomize (int arr[], int n);
#endif // HEAD_BUSCALOCAL_H_INCLUDED
