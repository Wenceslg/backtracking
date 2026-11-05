#include <iostream>
#include <vector>
#include<string>

using namespace std;


/*
Supongamos tener M llaves y N cerraduras. Cada llave abre una o más cerraduras.

Implemente un algoritmo para encontrar un conjunto mínimo de llaves que abran todas las cerraduras.

Resuelva por la técnica Backtracking: explique cómo expresar la solución, determine las restricciones 
explícitas e implícitas, dibuje parcialmente el espacio de soluciones a partir del ejemplo (deben 
quedar claros los estados podados y solución) y escriba un algoritmo en C++ que resuelva el problema. 
Determine su complejidad temporal.
*/
struct Llaves{
    string id;
    vector<bool> abre;
};

const int cantidadPuertas = 6;
vector<bool> puertas = {0, 0, 0, 0, 0, 0};

bool abrePuerta(Llaves l){
    for(int i=0; i< l.abre.size(); i++){
        if(l.abre[i] && !puertas[i])
            return true;
    }
    return false;
}

void back(int& puertasAbiertas, vector<Llaves>& solucion,vector<Llaves>& actual, vector<Llaves> llaves){
    if(puertasAbiertas == cantidadPuertas){
        if(solucion.size() > actual.size() || solucion.empty()){ 
            solucion = actual;
        }
    } else{
        for(int k=0; k < llaves.size(); k++){
            Llaves nueva = llaves[k];
            if(abrePuerta(nueva)){

                vector<int> nuevasAbiertas;

                for(int i=0; i< nueva.abre.size(); i++){
                    if(nueva.abre[i] && !puertas[i]){
                        puertasAbiertas++;
                        puertas[i] = true;
                        nuevasAbiertas.push_back(i);
                    }       
                }
                actual.push_back(nueva);

                back(puertasAbiertas, solucion, actual, llaves);

                actual.pop_back();
                for (int i : nuevasAbiertas) {
                    puertas[i] = false;
                    puertasAbiertas--;
                }  
            }
        }
    }
}

int main(){
    int puertasAbiertas = 0;

    Llaves llave1 = {"llave 1", {0, 0, 1, 0, 1, 0}};
    Llaves llave2 = {"llave 2", {1, 1, 0, 1, 1, 0}};
    Llaves llave3 = {"llave 3", {0, 1, 1, 0, 0, 0}};
    Llaves llave4 = {"llave 4", {1, 1, 0, 0, 0, 1}};
    Llaves llave5 = {"llave 5", {0, 1, 1, 1, 0, 1}};

    vector<Llaves> solucion;
    vector<Llaves> actual;
    vector<Llaves> llaves;

    llaves.push_back(llave1);
    llaves.push_back(llave2);
    llaves.push_back(llave3);
    llaves.push_back(llave4);
    llaves.push_back(llave5);

    back(puertasAbiertas, solucion, actual, llaves);

    return 0;
}