/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 17/02/2021
*
***************************************************************/

#ifndef HEAD_FILE_H_INCLUDED
#define HEAD_FILE_H_INCLUDED
#pragma once

/**
 * Ler e armazena quantidade de itens e peso
 * @parametro TinfoBins *infoBins - salva o peso maximo de um bim e a quantidade de itens.
 * @parametro const char *nome_arquivo - nome do arquivo de texto com as instancias
 */
void ler_info_bins (TinfoBins *infoBins, const char *nome_arquivo);

/**
 * Ler e armazena todos itens/peso
 * @parametro TinfoBins *infoBins - salva o peso maximo de um bim e a quantidade de itens.
 * @parametro const char *nome_arquivo - nome do arquivo de texto com as instancias
 * @retorno vector<Titem> - vetor com os itens/pesos
 */
vector<Titem> ler_itens (const TinfoBins infoBins, const char *nome_arquivo);

/**
 * Imprime todas informações do arquivo
 * @parametro const vector<Titem> items - vetor contendo todos itens/peso
 * @parametro TinfoBins *infoBins - informações gerais do bin (peso maximo, quantidade de itens)
 */
void imprimi_itens(const TinfoBins info_bins,const vector<Titem> items);


#endif // HEAD_FILE_H_INCLUDED
