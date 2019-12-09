/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 24/10/2019
*
***************************************************************/

#ifndef GERAL_H_INCLUDED
#define GERAL_H_INCLUDED
#pragma once

void criar_bins (vector<Tbin> &bins, const TinfoBins infoBins);
void imprimir_info_bins(const vector<Tbin> bins);
void imprimir_bins(const vector<Tbin> bins, const vector<Titem> items);
void imprimi_itens(const vector<Titem> items);
void erase_int (vector<int> &v, int pos);
vector<int> erase_int1 (vector<int> v, int pos);
void erase_bin (vector<Tbin> &v, int pos);
void confere_peso (const vector<Tbin> bins, const vector<Titem> items);
void confere_conflitos(const vector<Tbin> bins, const int **matriz_adj);
void imprimir_bins_2(const vector<Tbin> bins, const vector<Titem> items, double cpu_time_used);
#endif // GERAL_H_INCLUDED
