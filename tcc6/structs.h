/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 20/07/2020
*
***************************************************************/
#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED
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


#endif // STRUCTS_H_INCLUDED
