/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 20/07/2020
*
***************************************************************/
#ifndef MOVIMENTO_BL_H_INCLUDED
#define MOVIMENTO_BL_H_INCLUDED
#pragma once

void realocate(int id_item, int id_bin1, int id_bin2, vector<Tbin> &bins, const vector<Titem> itens, const int **matriz_adj, const int quant_itens);
void Swap (const int id_item1, const int id_item2, const int id_bin1, const int id_bin2, vector<Tbin> &bins, const vector<Titem> itens, const int **matriz_adj, const int quant_itens);
void Swap2_1(const int id_item1, const int id_item2, const int id_item3, const int id_bin1, const int id_bin2, vector<Tbin> &bins, const vector<Titem> itens, const int **matriz_adj, const int quant_itens);
void erase_int (vector<int> &v, int pos);

#endif // MOVIMENTO_BL_H_INCLUDED
