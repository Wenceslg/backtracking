#include<iostream>
#include<vector>

using namespace std;

// Problema de la mochila
/*Dados n objetos de pesos pi (1 ≤ i ≤ n) y una
mochila de capacidad C, encontrar un subconjunto de objetos que maximice */

const int capacidad = 100;


void back(vector<int> objetos, vector<int>& solucion, vector<int>& actual, int pesoActual, int& pesoMax, 
            vector<bool>& utilizado){
    
    if(pesoActual > capacidad)
        return;

    if(pesoActual > pesoMax){
        pesoMax = pesoActual;
        solucion = actual;
    }

    for(int i=0; i < objetos.size(); i++){
        if(pesoActual + objetos[i] <= capacidad && !utilizado[i]){
            pesoActual += objetos[i];
            utilizado[i] = true; 
            actual.push_back(objetos[i]);
            
            back(objetos, solucion, actual, pesoActual, pesoMax, utilizado);

            utilizado[i] = false;
            actual.pop_back();
            pesoActual -= objetos[i];
        } 
    }
    return;
}

int main(){
    vector<int> objetos = {12, 34, 50, 20 , 25, 88};
    vector<int> solucion;
    vector<bool> utilizado = {0, 0, 0, 0, 0, 0};
    vector<int> actual;
    int pesoActual = 0;
    int pesoMax = 0;

    back(objetos, solucion, actual, pesoActual, pesoMax, utilizado);

    return 0;
}

