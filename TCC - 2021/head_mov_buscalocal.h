/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 17/02/2021
*
***************************************************************/

#ifndef HEAD_MOV_BUSCALOCAL_H_INCLUDED
#define HEAD_MOV_BUSCALOCAL_H_INCLUDED
#pragma once

/**
 * Realoca o item de um bim X para um bim Y
 * @parametro Id do item realocado
 * @parametro Id do bim de onde o item vai ser retirado
 * @Parametro Id do bim que vai receber o item
 * @Parametro todos bins com seus itens
 * @Parametro vetor com todos itens/ informações de cada item
 * @Parametro matrix de conflito entre itens do bim
 */
void realocate(int id_item, int id_bin1, int id_bin2, vector<Tbin> &bins, const vector<Titem> itens, const int **matriz_adj, const int quant_itens);


/**
 * Envia o item para ultimo elemento de um vetor e exclui o ultimo elemento
 * @parametro vetor de items de um determinado bim
 * @parametro Posicao do item apagado
 */
void erase_int (vector<int> &v, int pos);

/**
 * Realiza uma troca de itens (id_item1, id_item2) entre 2 bins (id_bin1, id_bin2)
 * @parametro Id do item realocado
 * @parametro Id do bim de onde o item vai ser retirado
 * @Parametro Id do bim que vai receber o item
 * @Parametro todos bins com seus itens
 * @Parametro vetor com todos itens/ informações de cada item
 * @Parametro matrix de conflito entre itens do bim
 */
void Swap (const int id_item1, const int id_item2, const int id_bin1, const int id_bin2, vector<Tbin> &bins, const vector<Titem> itens, const int **matriz_adj, const int quant_itens);

/**
 * Realiza uma troca de itens (id_item1, id_item2) 2 pra 1, entre 2 bins (id_bin1, id_bin2)
 * @parametro Id do item realocado
 * @parametro Id do bim de onde o item vai ser retirado
 * @Parametro Id do bim que vai receber o item
 * @Parametro todos bins com seus itens
 * @Parametro vetor com todos itens/ informações de cada item
 * @Parametro matrix de conflito entre itens do bim
 */
void Swap2_1(const int id_item1, const int id_item2, const int id_item3, const int id_bin1, const int id_bin2, vector<Tbin> &bins, const vector<Titem> itens, const int **matriz_adj, const int quant_itens);


#endif // HEAD_MOV_BUSCALOCAL_H_INCLUDED
