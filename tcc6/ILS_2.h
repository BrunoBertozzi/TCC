/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 20/07/2020
*
***************************************************************/
#ifndef ILS_2_H_INCLUDED
#define ILS_2_H_INCLUDED
#pragma once

void ILS_2(char *argv[]);
double busca_local_ILS2(vector<Tbin> &bins, const vector<Titem> itens, TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww, int tipoILS);


#endif // ILS_2_H_INCLUDED
