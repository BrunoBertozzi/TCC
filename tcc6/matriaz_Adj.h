/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 20/07/2020
*
***************************************************************/
#ifndef MATRIAZ_ADJ_H_INCLUDED
#define MATRIAZ_ADJ_H_INCLUDED
#pragma once

/**
 * Aloca dinamicamente uma matriz 2D
 * @parametro Quantidade de linhas da matriz
 * @parametro Quantidade de Coluna da matriz
 * @retorno int **alocar_matriz - Matriz linhaXColuna
 */
int **alocar_matriz (const int linha, const int coluna);

/**
 * Set 0 em todas posições de uma matriz
 * @parametro ponteiro para matriz
 * @parametro Quantidade de linhas da matriz
 * @parametro Quantidade de Coluna da matriz
 */
void zerar_matriz (int **matriz_adj, const int linha, const int coluna);

/**
 * Carrega a matriz com os conflitos do arquivo de instancia
 * @parametro ponteiro para matriz
 * @parametro Nome/Caminho para o arquivo de instancia
 */
void carrega_matrizAdj(int **matriz, const char *nome_arquivo);

/**
 * Divide uma linha em sub strings por um separador
 * @parametro String completa
 * @parametro Separador de string
 */
const vector<string> explodes(const string& s, const char& c);

/**
 * Print a matriz 2D
 * @parametro ponteiro para matriz
 * @parametro Quantidade de linhas da matriz
 * @parametro Quantidade de Coluna da matriz
 */
void imprime_matriz (int **matriz_adj, const  int linha, const  int coluna);

/**
 * Libera/Desaloca a memoria usada pela matriz
 * @parametro ponteiro para matriz
 * @parametro Quantidade de linhas da matriz
 */
int **libera_matriz (int **matriz, const  int quant_iten);
void carrega_matrizAdj_linux(int **matriz, const char *nome_arquivo);

#endif // MATRIAZ_ADJ_H_INCLUDED
