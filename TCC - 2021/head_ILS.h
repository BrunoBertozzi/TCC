/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 17/02/2021
*
***************************************************************/

#ifndef ILS_H_INCLUDED
#define ILS_H_INCLUDED
#pragma once


vector<Tbin> ILS1(vector<Tbin> &S_inicial ,const int **matriz_adj, const TinfoBins info_bins, char *argv[], const vector<Titem> items, int *phyS_Inicial, int Klb);
vector<Tbin> ILS2(vector<Tbin> &S_inicial ,const int **matriz_adj, const TinfoBins info_bins, char *argv[], const vector<Titem> items, int *phyS_Inicial, int Klb);
vector<Tbin> ILS3(vector<Tbin> &S_inicial ,const int **matriz_adj, const TinfoBins info_bins, char *argv[], const vector<Titem> items, int *phyS_Inicial, int Klb);

#endif // ILS_H_INCLUDED
