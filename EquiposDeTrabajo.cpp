#include<iostream>
#include<vector>

using namespace std;

/*
Una empresa tiene n equipos de trabajo para desarrollar n productos diferentes. 
Se estimó el costo de desarrollo de cada producto por cada equipo de trabajo y se lo
registró en una matriz de costos C. Si al equipo i se le asigna el producto j, entonces 
el costo de realizarlo será Cij. Se desea asignar un único producto a cada equipo de trabajo. 
El problema consiste en asignar los n productos de forma tal de minimizar el costo total de desarrollo.
*/

const int N = 4; //Cantidad de tareas

void back(vector<int>& actual, vector<int>& solucion, int& costoMin, int& costoTotal, int& tareasAsignadas,
        vector<vector<int>> equipos, int indice){

    if(tareasAsignadas == N){
        if(costoTotal < costoMin){
            costoMin = costoTotal;
            solucion = actual;
        }
        return;
        
    }else{
        for(int k=0; k < equipos.size(); k++){
            if(equipos[k][indice] + costoTotal < costoMin && actual[k] == -1){
                actual[k] = equipos[k][indice];
                costoTotal += equipos[k][indice];
                tareasAsignadas++;

                back(actual, solucion, costoMin, costoTotal, tareasAsignadas, equipos, indice + 1);

                actual[k] = -1;
                costoTotal -= equipos[k][indice];
                tareasAsignadas--;
            }
        }
    }
    return;
}

int main(){
    //La tarea 1 esta representada con la posicion 0 del vector
    vector<int> equipo1 = {11, 12, 18, 40};
    vector<int> equipo2 = {14, 15, 13, 22};
    vector<int> equipo3 = {11, 17, 19, 50};
    vector<int> equipo4 = {17, 14, 20, 28};

    //La posicion del vectro va a representar el numero del equipo
    vector<int> actual = {-1, -1, -1, -1};
    vector<int> solucion;
    
    vector<vector<int>> equipos;
    equipos.push_back(equipo1);
    equipos.push_back(equipo2);
    equipos.push_back(equipo3);
    equipos.push_back(equipo4);

    int cosotoMin;
    int costoTotal;
    int tareasAsignadas;

    
    return 0;
}