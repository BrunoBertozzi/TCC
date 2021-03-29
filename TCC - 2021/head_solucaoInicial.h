/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 17/02/2021
*
***************************************************************/

#ifndef HEAD_SOLUCAOINICIAL_H_INCLUDED
#define HEAD_SOLUCAOINICIAL_H_INCLUDED
#pragma once

/**
 * Funcao auxiliar ordenação dos itens. Compara o peso de 2 itens
 * @parametro Posicao do item verificado no vetor (id-1)
 * @parametro Vetor de bins
 * @parametro matriz com os conflitos
 * @retorno Se existe ou nao conflito em determinado bin
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
 * Funcao para gerar solução inicial do problema
 * @parametro vector de bins vazio
 * @parametro vector com todos os itens dos arquivos
 * @parametro informações dos bins
 * @parametro matriz com os conflitos
 */
void firstFit_ordenado (vector<Tbin> &bins, const vector<Titem> itens, const TinfoBins infoBins, const int **matriz_adj);


#endif // HEAD_SOLUCAOINICIAL_H_INCLUDED
