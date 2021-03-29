/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 17/02/2021
*
***************************************************************/

#ifndef HEAD_PHI_H_INCLUDED
#define HEAD_PHI_H_INCLUDED
#pragma once

/**
 * Funcao de avaliação dos resultados
 * @parametro vetor de bins
 * @parametro peso para conflito
 * @parametro peso para excesso de peso no bin
 * @retorno (x.numConflitos * wc) + (over_peso * ww) + bins.size()
 */
int somatorio_phi (const vector<Tbin> bins, const int wc, const int ww);
int calcula_Klb(const vector<Titem> items, const TinfoBins infoBins);
#endif // HEAD_PHI_H_INCLUDED
