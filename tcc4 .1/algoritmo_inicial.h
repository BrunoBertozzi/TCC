#ifndef ALGORITMO_INICIAL_H_INCLUDED
#define ALGORITMO_INICIAL_H_INCLUDED
#pragma once

int confere_conflito(int id_obj, const vector<Tbin> bins, int j , const int **matriz_adj);
void bestFit (vector<Tbin> &bins, const vector<Titem> itens, const TinfoBins infoBins, const int **matriz_adj);
vector<Tbin> nextFit (vector<Tbin> bins, vector<Titem> itens, TinfoBins *infoBins, const int **matriz_adj);
vector<Tbin> firstFit (vector<Tbin> bins, vector<Titem> itens, TinfoBins *infoBins,  const int **matriz_adj);
bool sort_peso (const Titem &a, const Titem &b);
void bestFit_ordenado (vector<Tbin> &bins, const vector<Titem> itens, const TinfoBins infoBins, const int **matriz_adj);
void firstFit_ordenado (vector<Tbin> &bins, const vector<Titem> itens, const TinfoBins infoBins, const int **matriz_adj);

#endif // ALGORITMO_INICIAL_H_INCLUDED
