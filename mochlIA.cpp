#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Solucion {
    long long peso = 0;
    vector<int> objetos;
};

// Se supone que los pesos y la capacidad son no negativos.
void back(const vector<int>& objetos, const vector<long long>& sumaRestante,
          long long capacidad, size_t i, long long pesoActual,
          vector<int>& actual, Solucion& mejor) {
    if (pesoActual > mejor.peso) {
        mejor.peso = pesoActual;
        mejor.objetos = actual;
    }

    // Ya se decidio sobre todos los objetos o se lleno la mochila.
    if (i == objetos.size() || mejor.peso == capacidad) return;

    // Ni agregando todos los objetos restantes se mejora la solucion.
    if (pesoActual + sumaRestante[i] <= mejor.peso) return;

    // Opcion 1: incluir el objeto, si entra.
    if (pesoActual + objetos[i] <= capacidad) {
        actual.push_back(objetos[i]);
        back(objetos, sumaRestante, capacidad, i + 1,
             pesoActual + objetos[i], actual, mejor);
        actual.pop_back(); // Deshacer la eleccion.
    }

    // Opcion 2: no incluir el objeto.
    back(objetos, sumaRestante, capacidad, i + 1,
         pesoActual, actual, mejor);
}

Solucion resolverMochila(vector<int> objetos, long long capacidad) {
    // Probar primero los mas pesados puede ayudar a encontrar antes un buen peso.
    sort(objetos.rbegin(), objetos.rend());

    // sumaRestante[i] contiene la suma de los pesos desde i hasta el final.
    vector<long long> sumaRestante(objetos.size() + 1, 0);
    for (size_t i = objetos.size(); i > 0; --i) {
        sumaRestante[i - 1] = sumaRestante[i] + objetos[i - 1];
    }

    Solucion mejor;
    vector<int> actual;
    back(objetos, sumaRestante, capacidad, 0, 0, actual, mejor);
    return mejor;
}

int main() {
    const long long capacidad = 100;
    vector<int> objetos = {12, 34, 50, 20, 25, 88};

    Solucion mejor = resolverMochila(objetos, capacidad);

    cout << "Objetos elegidos (pesos): ";
    for (int peso : mejor.objetos) {
        cout << peso << ' ';
    }
    cout << "\nPeso total: " << mejor.peso << '\n';
    cout << "Capacidad: " << capacidad << '\n';
    return 0;
}
