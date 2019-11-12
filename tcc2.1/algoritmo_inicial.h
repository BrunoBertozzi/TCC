#ifndef ALGORITMO_INICIAL_H_INCLUDED
#define ALGORITMO_INICIAL_H_INCLUDED
#pragma once

int confere_conflito(const int id_obj, const Tbin bin , const int **matriz_adj);
void bestFit (vector<Tbin> &bins, const vector<Titem> itens, const TinfoBins infoBins, const int **matriz_adj);
vector<Tbin> nextFit (vector<Tbin> bins, vector<Titem> itens, TinfoBins *infoBins, const int **matriz_adj);
vector<Tbin> firstFit (vector<Tbin> bins, vector<Titem> itens, TinfoBins *infoBins,  const int **matriz_adj);

#endif // ALGORITMO_INICIAL_H_INCLUDED
