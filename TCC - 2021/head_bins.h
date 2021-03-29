/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 17/02/2021
*
***************************************************************/

#ifndef HEAD_BINS_H_INCLUDED
#define HEAD_BINS_H_INCLUDED
#pragma once

/**
 * Cria um vector tipod Tbin com a quantidade maxima de itens
 * @parametro Vector Tbin, vazio
 * @parametro TinfoBins, contem quantidade de itens e peso max
 */
void criar_bins (vector<Tbin> &bins, const TinfoBins infoBins);

/**
 * Imprime informações de cada bin (peso usado, peso livre, quant itens)
 * @parametro Vector Tbin
 */
void imprimir_info_bins(const vector<Tbin> bins);

/**
 * Imprime informações de cada bin (peso usado, peso livre, quant itens)
 * @parametro Vector Tbin
 * @parametro Vector itens
 */
void imprimir_bins(const vector<Tbin> bins, const vector<Titem> items);

/**
 * Envia um elemento para ultima posição do vetor e o apaga
 * @parametro Vector Tbin
 * @parametro Posição atual em que o bin que vai ser apagado esta
 */
void erase_bin (vector<Tbin> &v, int pos);

/**
 * Remove um bin e redistribui seus itens aleatoriamente entre os outros bins
 * @parametro Vector Tbin
 * @parametro Vector com todos itens e suas informações (peso)
 * @parametro Matrix de adjacencia com os conflitos entre os bins
 * @parametro ww = constante multiplicadora utilizada na formula de calculo do Phy
 * @parametro wc = constante multiplicadora utilizada na formula de calculo do Phy
 * @parametro Phy = valor de validação da solução atual de bins
 */
int remove_bin_phy(vector<Tbin> &bins, const vector<Titem> items,  const int **matriz_adj, int ww, int wc, int phy);

/**
 * Verifica a existencia de novos conflitos em um bin apos receber novos itens
 * @parametro Vector com todos itens de um determinado bin
 * @parametro Id do item que acabou de ser alocado
 * @parametro Matrix de adjacencia com os conflitos entre os bins
 */
int conflito_por_bin(const vector<int> items, const int item, const int **matriz_adj);

void imprimir_bins_2(const vector<Tbin> bins, const vector<Titem> items, double cpu_time_used);

#endif // HEAD_BINS_H_INCLUDED
