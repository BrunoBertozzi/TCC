/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 17/02/2021
*
***************************************************************/

#ifndef HEAD_PERTUBACAO_H_INCLUDED
#define HEAD_PERTUBACAO_H_INCLUDED
#pragma once

int pertubacao_iten_conflito(const vector<Tbin> &bins, const int **matriz_adj, const int bin_id);
int pertubacao(vector<Tbin> &bins, const vector<Titem> itens, int Sshack, const TinfoBins infoBins, const int **matriz_adj, int ww, int wc);
vector<int> carrega_vetor_bins_conflito_pertubacao(const vector<Tbin> &bins);

#endif // HEAD_PERTUBACAO_H_INCLUDED
