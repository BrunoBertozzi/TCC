/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 06/08/2020
*
***************************************************************/
#include <iostream>
#include <vector>
#include <iostream>
#include<fstream>
#include <math.h>

using namespace std;

//HEADERS
#include "structs.h"
#include "arquivo.h"
#include "ILS_1.h"
#include "matriaz_Adj.h"
#include "bins.h"
#include "solucao_Inicial.h"
#include "algoritmo_Verificacao.h"
#include "Phy.h"

double somatorio_phi (const vector<Tbin> bins, const int wc, const int ww){
    double contador = 0, over_peso = 0;

    for(const auto& x: bins){
        over_peso = 0;

        if(x.pesoLivre < 0) over_peso = (double)(x.pesoLivre * (-1));

        contador +=(double)((x.numConflitos * wc) + (over_peso * ww));
    }
    return ((double)(contador + bins.size()));
}

int calcula_Klb(const vector<Titem> items, const TinfoBins infoBins){
    float klb = 0;

    for(const auto & item : items)
        klb += item.peso;

    klb = (float)klb / infoBins.pesoBin;
    klb = ceil(klb);

    return klb;
}
