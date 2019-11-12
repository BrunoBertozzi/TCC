/***************************************************************
*   Nome: Bruno Oswaldo Bertozzi Oliveira
*   File name: main.cpp
*   Data 24/10/2019
*
***************************************************************/

#include <iostream>
#include <vector>
#include <iostream>
#include<fstream>

using namespace std;

#include "arquivo.h"
#include "matrizAdjacencia.h"
#include "geral.h"
#include "algoritmo_inicial.h"
#include "ILS.h"
#include "funcao_avaliacao.h"
#include "matriz_iten_bin.h"
#include "busca_local.h"
#include "delta.h"
#include "pertubacao.h"

int somatorio_phi (const vector<Tbin> bins, const int wc, const int ww){
    int contador = 0, over_peso = 0;

    for(const auto& x: bins){
        over_peso = 0;

        if(x.pesoLivre < 0) over_peso = x.pesoLivre * (-1);

        contador +=(x.numConflitos * wc) + (over_peso * ww);
    }
    return contador + bins.size();
}
