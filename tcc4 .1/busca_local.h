#ifndef BUSCA_LOCAL_H_INCLUDED
#define BUSCA_LOCAL_H_INCLUDED

void realocate(int id_item, int id_bin1, int id_bin2, vector<Tbin> &bins, const vector<Titem> itens, const int **matriz_adj, const int quant_itens);
void Swap (const int id_item1, const int id_item2, const int id_bin1, const int id_bin2, vector<Tbin> &bins, const vector<Titem> itens, const int **matriz_adj, const int quant_itens);
void Swap2_1(const int id_item1, const int id_item2, const int id_item3, const int id_bin1, const int id_bin2, vector<Tbin> &bins, const vector<Titem> itens, const int **matriz_adj, const int quant_itens);

vector<int> carrega_vetor_bins_conflito(const vector<Tbin> &bins);


int busca_local(vector<Tbin> &bins, const vector<Titem> itens, TinfoBins infoBins, const int **matriz_adj, int *phyI, const int wc, const int ww);
int busca_local_ILS2(vector<Tbin> &bins, const vector<Titem> itens, TinfoBins infoBins, const int **matriz_adj, int *phyI, const int wc, const int ww);
int busca_local_ILS3(vector<Tbin> &bins, const vector<Titem> itens, TinfoBins infoBins, const int **matriz_adj, int *phyI, const int wc, const int ww, int start_time,int time_limit);

#endif // BUSCA_LOCAL_H_INCLUDED
