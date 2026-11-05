#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
/*
1. Para realizar un trabajo, un carpintero necesita n varillas de distintas longitudes que varían
entre 0,10 y 3 metros. En las madereras venden varillas de 3 m. de longitud. El carpintero
desea comprar la menor cantidad de varillas posibles.
Escriba un programa en C++ para determinar cuántas varillas necesita comprar y cómo
debe realizar los cortes.
a- Bactracking */

const int capacidad = 300;

void back(vector<int> varillas, vector<int>& solucion, vector<int>& actual,
         int compradas, int& minCompradas, int varillaActual){

    if(varillas.empty()){ //Si consegui las que necesito corto
        if(compradas < minCompradas){
            solucion = actual;
            minCompradas = compradas;
            return;
        }
    } else {
        sort(varillas.rbegin(), varillas.rend());
        bool necesitoComprar = true;  
        for(int k=0; k < varillas.size(); k++){
            int pieza = varillas[k];

            if(varillaActual >= pieza){
                necesitoComprar = false;

                varillas.erase(varillas.begin() + k);
                actual.push_back(pieza);

                varillaActual = varillaActual - pieza;

                back(varillas, solucion, actual, compradas, minCompradas, varillaActual);

                varillaActual = varillaActual + pieza;
                varillas.insert(varillas.begin() + k, pieza);
                actual.pop_back();
            }
        }
        if(compradas + 1 < minCompradas && necesitoComprar){
            varillaActual = capacidad;
            back(varillas, solucion, actual, compradas + 1, minCompradas, varillaActual);      
        }
    }

}

int main(){ 
    vector<int> varillas = {300, 200, 100, 10};

    vector<int> solucion; // el taminio reprecenta cantidad y ko que guarda los cortes
    vector<int> actual;
    int compradas =0;
    int minCompradas = 100;
    int varillaActual=0;

    back(varillas, solucion, actual, compradas, minCompradas, varillaActual);

    cout << "Cantidad minima: " << minCompradas << '\n';

    int numero = 0;

    for (int pieza : solucion) {
        if (pieza == 0) {
            cout << "\nVarilla " << ++numero << ": ";
        } else {
            cout << pieza << " cm ";
        }
    }

    cout << '\n';
    return 0;
}