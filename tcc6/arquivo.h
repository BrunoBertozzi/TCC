/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 20/07/2020
*
***************************************************************/
#ifndef ARQUIVO_H_INCLUDED
#define ARQUIVO_H_INCLUDED
#pragma once

/**
 * Ler e armazena todos dados da instancia
 * @parametro TinfoBins *infoBins - salva o peso maximo de um bim e a quantidade de itens.
 * @parametro const char *nome_arquivo - nome do arquivo de texto com as instancias
 * @retorno vector<Titem> - vetor com os itens/pesos
 */
vector<Titem> ler_arquivo_instancias (TinfoBins *infoBins, const char *nome_arquivo);

void imprimi_itens(const vector<Titem> items, const TinfoBins info_bins);

#endif // ARQUIVO_H_INCLUDED
