/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 24/10/2019
*
***************************************************************/

#ifndef GERAL_H_INCLUDED
#define GERAL_H_INCLUDED
#pragma once

vector<Tbin> criar_bins (const TinfoBins infoBins);
void imprimir_info_bins(const vector<Tbin> bins);
void imprimir_bins(const vector<Tbin> bins, const vector<Titem> items);
void imprimi_itens(const vector<Titem> items);
vector<int> erase_int (vector<int> v, int pos);
vector<Tbin> erase_bin (vector<Tbin> v, int pos);
#endif // GERAL_H_INCLUDED
