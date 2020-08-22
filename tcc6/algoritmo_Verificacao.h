/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 20/07/2020
*
***************************************************************/
#ifndef ALGORITMO_VERIFICACAO_H_INCLUDED
#define ALGORITMO_VERIFICACAO_H_INCLUDED
#pragma once

void Vconfere_conflitos(const vector<Tbin> bins, int **matriz_adj);
void Vconfere_peso (const vector<Tbin> bins, const vector<Titem> items, int quant_iten_max);
void Vconfere_peso_limite (const vector<Tbin> bins, int peso_max);


#endif // ALGORITMO_VERIFICACAO_H_INCLUDED
