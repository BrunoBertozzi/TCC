/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 20/07/2020
*
***************************************************************/
#ifndef PHY_H_INCLUDED
#define PHY_H_INCLUDED
#pragma once

/**
 * Funcao de avaliação dos resultados
 * @parametro vetor de bins
 * @parametro peso para conflito
 * @parametro peso para excesso de peso no bin
 * @retorno (x.numConflitos * wc) + (over_peso * ww) + bins.size()
 */
double somatorio_phi (const vector<Tbin> bins, const int wc, const int ww);

/**
 * Calcular o lower Bounde (menor quantidade de bins): Sum(peso itens) / (peso max por bin)
 * @parametro vetor de itens
 * @parametro Informações bin
 * @retorno Menor quantidade de bin
 */
int calcula_Klb(const vector<Titem> items, const TinfoBins infoBins);

#endif // PHY_H_INCLUDED
