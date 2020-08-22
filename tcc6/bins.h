/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 20/07/2020
*
***************************************************************/
#ifndef BINS_H_INCLUDED
#define BINS_H_INCLUDED
#pragma once

/**
 * Cria um vector tipod Tbin com a quantidade maxima de itens
 * @parametro Vector Tbin, vazio
 * @parametro TinfoBins, contem quantidade de itens e peso max
 */
void criar_bins (vector<Tbin> &bins, const TinfoBins infoBins);

/**
 * Imprime informações de cada bin (peso usado, peso livre, quant itens)
 * @parametro Vector Tbin
 */
void imprimir_info_bins(const vector<Tbin> bins);

void imprimir_bins(const vector<Tbin> bins, const vector<Titem> items);
void imprimir_bins_2(const vector<Tbin> bins, const vector<Titem> items, double cpu_time_used);

int remove_bin_phy(vector<Tbin> &bins, const vector<Titem> items,  const int **matriz_adj, int ww, int wc);
int remove_bin_phy2(vector<Tbin> &bins, const vector<Titem> items,  const int **matriz_adj, int ww, int wc, int phy);
void erase_bin (vector<Tbin> &v, int pos);
int conflito_por_bin(const vector<int> items, const int item, const int **matriz_adj);

#endif // BINS_H_INCLUDED

