#ifndef MATRIZ_ITEN_BIN_H_INCLUDED
#define MATRIZ_ITEN_BIN_H_INCLUDED
#pragma once

void matriz_bin_item (vector<Tbin> bins, int **matriz_adj, int **matriz_iten_bin, int quant_itens);
void atualizar_conflito_iten_bin(int **matriz_adj, int **matriz_iten_bin, int quant_itens, int id_bin1, int id_bin2, int id_item);

#endif // MATRIZ_ITEN_BIN_H_INCLUDED
