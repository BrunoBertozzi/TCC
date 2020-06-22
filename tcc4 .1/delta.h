#ifndef DELTA_H_INCLUDED
#define DELTA_H_INCLUDED

int calcula_delta_swap(const vector<Tbin> bins, const vector<Titem> itens, const int bin1, const int bin2, int *iten_1, int *iten_2, const TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww);
int delta_peso(const vector<Tbin> bins, const vector<Titem> itens, const int bin1, const int bin2, const int iten1, const int iten2, const TinfoBins infoBins);
int delta_conflito(int id_item1, int id_item2, int pos_bin1, int pos_bin2, const int **matriz_adj);

int delta_peso_realocete(const vector<Tbin> bins, const vector<Titem> itens, const int item1, const int bin1, const int bin2, const int peso_bim);
int calcula_delta_realocate (const vector<Tbin> bins, const vector<Titem> itens, const int bin1, const int bin2, int *iten_1, const TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww);
int delta_conflito_realocate (int id_item1, int pos_bin1, int pos_bin2, const int **matriz_adj);


int delta_conflito_swap_2_1(int id_item1, int id_item2, int id_item3, int pos_bin1, int pos_bin2, const int **matriz_adj);
int delta_peso_swap_2_1(const vector<Tbin> bins, const vector<Titem> itens, const int bin1, const int bin2, const int iten1, const int iten2, const int iten3, const TinfoBins infoBins);
int calcula_delta_swap_2_1(const vector<Tbin> bins, const vector<Titem> itens, const int bin1, const int bin2, int *iten_1, int *iten_2, int *iten_3, const TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww);


//int delta_conflito2(int id_item1, int id_item2, int pos_bin1, int pos_bin2, int **matriz_adj, vector<Tbin> bins);
int delta_conflito2(const int id_item1, const int id_item2, const int pos_bin1, const int pos_bin2, const int **matriz_adj, const vector<Tbin> bins);
int delta_conflito_realocate2(const int id_item1, const int pos_bin1, const int pos_bin2, const int **matriz_adj, const vector<Tbin> bins);
int delta_conflito_swap_2_1_2(const int id_item1, const int id_item2, const int id_item3, const int pos_bin1, const int pos_bin2, const int **matriz_adj, const vector<Tbin> bins);

int delta_remove_peso(vector<Tbin> &bins, const vector<Titem> itens, const int iten, const int bin_recebe, const int peso_max_bin);
int delta_remove_conflito(const int id_item1, const int bin, const int **matriz_adj, const vector<int> itens);


int calcula_delta_swap_2_1_ILS3(const vector<Tbin> bins, const vector<Titem> itens, const int bin1, const int bin2, int *iten_1, int *iten_2, int *iten_3, const TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww);
int calcula_delta_realocate_ILS3 (const vector<Tbin> bins, const vector<Titem> itens, const int bin1, const int bin2, int *iten_1, const TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww);
int calcula_delta_swap_ILS3(const vector<Tbin> bins, const vector<Titem> itens, const int bin1, const int bin2, int *iten_1, int *iten_2, const TinfoBins infoBins, const int **matriz_adj, const int wc, const int ww);

int correcao_peso(int ww, int wc);
#endif // DELTA_H_INCLUDED
