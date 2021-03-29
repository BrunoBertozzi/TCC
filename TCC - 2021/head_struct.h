/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 17/02/2021
*
***************************************************************/

#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED
#pragma once


typedef struct Item{
    int peso;
    int idItem;
}Titem;

typedef struct Bin{
    int pesoUsado;
    int pesoLivre;
    int id_bin;
    int numConflitos;
    vector<int> items;
}Tbin;

typedef struct InfoBins{
    int quantItens;
    int pesoBin;
}TinfoBins;

typedef struct Custo{
    int phy;
}TCusto;

#endif // STRUCT_H_INCLUDED
