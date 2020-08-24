/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 20/07/2020
*
***************************************************************/
#ifndef PERTUBACAO_H_INCLUDED
#define PERTUBACAO_H_INCLUDED
#pragma once

int pertubacao_iten_conflito(const vector<Tbin> &bins, const int **matriz_adj, const int bin_id);
double pertubacao(vector<Tbin> &bins, const vector<Titem> itens, int Sshack, const TinfoBins infoBins, const int **matriz_adj, int ww, int wc);
vector<int> carrega_vetor_bins_conflito_pertubacao(const vector<Tbin> &bins);

#endif // PERTUBACAO_H_INCLUDED
