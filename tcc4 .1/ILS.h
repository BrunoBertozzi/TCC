#ifndef ILS_H_INCLUDED
#define ILS_H_INCLUDED
#pragma once

void ILS();
int calcula_Klb(const vector<Titem> items, const TinfoBins infoBins);
TinfoBins copy_info (TinfoBins original);
void remove_bin(vector<Tbin> &bins, const vector<Titem> items,  const int **matriz_adj);
double conflito_por_bin(const vector<int> items, const int item, const int **matriz_adj);

#endif // ILS_H_INCLUDED
