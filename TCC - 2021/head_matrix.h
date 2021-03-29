/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 17/02/2021
*
***************************************************************/

#ifndef HEAD_MATRIX_H_INCLUDED
#define HEAD_MATRIX_H_INCLUDED
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

/**
 * Cria uma copia de uma matriz ja existente
 * @parametro ponteiro para matriz ja existente
 * @parametro Quantidade de linhas da matriz
 */
int **copy_matriz (int **matriz, const int tam);

/**
 * Preenche uma matrix com os valores
 * @parametro ponteiro para matriz ja existente
 * @parametro Quantidade de linhas da matriz
 */
void carrega_matrizAdj_linux(int **matriz, const char *nome_arquivo);

#endif // HEAD_MATRIX_H_INCLUDED
