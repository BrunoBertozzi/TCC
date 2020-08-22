/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 20/07/2020
*
***************************************************************/
#ifndef SOLUCAO_INICIAL_H_INCLUDED
#define SOLUCAO_INICIAL_H_INCLUDED
#pragma once

/**
 * Funcao auxiliar ordenação dos itens. Compara o peso de 2 itens
 * @parametro Iten 1
 * @parametro Iten 2
 * @retorno Maior iten entre os passados por parametro
 */
int confere_conflito(int id_obj, const vector<Tbin> bins, int j , const int **matriz_adj);

/**
 * Funcao auxiliar ordenação dos itens. Compara o peso de 2 itens
 * @parametro Iten 1
 * @parametro Iten 2
 * @retorno Maior iten entre os passados por parametro
 */
bool sort_peso (const Titem &a, const Titem &b);

/**
 * Algoritmos para gerar solução inicial do problema
 */
void bestFit_ordenado (vector<Tbin> &bins, const vector<Titem> itens, const TinfoBins infoBins, const int **matriz_adj);
void firstFit_ordenado (vector<Tbin> &bins, const vector<Titem> itens, const TinfoBins infoBins, const int **matriz_adj);
void bestFit (vector<Tbin> &bins, const vector<Titem> itens, const TinfoBins infoBins, const int **matriz_adj);

#endif // SOLUCAO_INICIAL_H_INCLUDED
