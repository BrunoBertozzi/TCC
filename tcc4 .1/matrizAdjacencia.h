#ifndef MATRIZADJACENCIA_H_INCLUDED
#define MATRIZADJACENCIA_H_INCLUDED
#pragma once

int **alocar_matriz (const int linha, const int coluna);
int **libera_matriz (int **matriz, const  int quant_iten);
void imprime_matriz (const int **matriz_adj, const  int linha, const  int coluna);
void zerar_matriz (int **matriz_adj, const int linha, const int coluna);
void carrega_matrizAdj(int **matriz, const char *nome_arquivo);
const vector<string> explode(const string& s, const char& c);

#endif // MATRIZADJACENCIA_H_INCLUDED
