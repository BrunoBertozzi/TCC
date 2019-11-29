/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 24/10/2019
*
***************************************************************/

#ifndef ARQUIVO_H_INCLUDED
#define ARQUIVO_H_INCLUDED
#pragma once

typedef struct Item{
    int peso;
    int idItem;
}Titem;

typedef struct Bin{
    int pesoUsado;
    int pesoLivre;
    int id_bin;
    double numConflitos;
    vector<int> items;
}Tbin;

typedef struct InfoBins{
    int quantItens;
    int pesoBin;
}TinfoBins;



/**
 * Ler e armazena todos dados da instancia
 * @parametro TinfoBins *infoBins - salva o peso maximo de um bim e a quantidade de itens.
 * @parametro const char *nome_arquivo - nome do arquivo de texto com as instancias
 * @retorno vector<Titem> - vetor com os itens e seus pesos
 */
vector<Titem> ler_arquivo_instancias (TinfoBins *infoBins, const char *nome_arquivo);

#endif // ARQUIVO_H_INCLUDED
