/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 20/07/2020
*
***************************************************************/
#ifndef ILS_3_H_INCLUDED
#define ILS_3_H_INCLUDED
#pragma once

void ILS_3(char *argv[]);
int busca_local_ILS3(vector<Tbin> &bins, const vector<Titem> itens, TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww, int start_time,int time_limit, int tipoILS);
void swap1 (int *a, int *b);
void randomize (int arr[], int n);

#endif // ILS_3_H_INCLUDED
