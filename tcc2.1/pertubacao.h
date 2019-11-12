#ifndef PERTUBACAO_H_INCLUDED
#define PERTUBACAO_H_INCLUDED

int pertubacao_iten_conflito(const vector<Tbin> &bins, const int **matriz_adj, const int bin_id);
void pertubacao(vector<Tbin> &bins, const vector<Titem> itens, int Sshack, const TinfoBins infoBins, const int **matriz_adj);
#endif // PERTUBACAO_H_INCLUDED
