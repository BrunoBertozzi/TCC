/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 17/02/2021
*
***************************************************************/

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

#include "head_struct.h"

int somatorio_phi (const vector<Tbin> bins, const int wc, const int ww){
    int contador = 0, over_peso = 0;

    for(const auto& x: bins){
        over_peso = 0;

        if(x.pesoLivre < 0) over_peso = x.pesoLivre * (-1);

        contador +=(x.numConflitos * wc) + (over_peso * ww);
    }
    return (contador + bins.size());
}

int calcula_Klb(const vector<Titem> items, const TinfoBins infoBins){
    float klb = 0;

    for(const auto & item : items)
        klb += item.peso;

    klb = (float)klb / infoBins.pesoBin;
    klb = ceil(klb);

    return klb;
}
