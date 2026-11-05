#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Encontrar un conjunto minimo de llaves que abra todas las cerraduras.
// Cada vector abre tiene una posicion por cerradura.
struct Llave {
    string id;
    vector<bool> abre;
};

struct Solucion {
    bool encontrada = false;
    vector<size_t> indices;
};

void back(const vector<Llave>& llaves, size_t inicio,
          vector<bool>& puertas, size_t puertasAbiertas,
          vector<size_t>& actual, Solucion& mejor) {
    if (puertasAbiertas == puertas.size()) {
        if (!mejor.encontrada || actual.size() < mejor.indices.size()) {
            mejor.encontrada = true;
            mejor.indices = actual;
        }
        return;
    }

    // Agregar mas llaves ya no permitiria mejorar la solucion conocida.
    if (mejor.encontrada && actual.size() >= mejor.indices.size()) return;

    for (size_t k = inicio; k < llaves.size(); ++k) {
        vector<size_t> nuevasAbiertas;

        for (size_t i = 0; i < puertas.size(); ++i) {
            if (llaves[k].abre[i] && !puertas[i]) {
                puertas[i] = true;
                nuevasAbiertas.push_back(i);
            }
        }

        // Una llave que no abre ninguna puerta nueva no es necesaria.
        if (nuevasAbiertas.empty()) continue;

        actual.push_back(k);

        // k + 1 evita repetir llaves y probar la misma combinacion en otro orden.
        back(llaves, k + 1, puertas,
             puertasAbiertas + nuevasAbiertas.size(), actual, mejor);

        actual.pop_back();
        for (size_t i : nuevasAbiertas) {
            puertas[i] = false;
        }
    }
}

Solucion resolverPuertas(const vector<Llave>& llaves, size_t cantidadPuertas) {
    vector<bool> puertas(cantidadPuertas, false);
    vector<size_t> actual;
    Solucion mejor;
    back(llaves, 0, puertas, 0, actual, mejor);
    return mejor;
}

int main() {
    const size_t cantidadPuertas = 6;
    vector<Llave> llaves = {
        {"llave 1", {0, 0, 1, 0, 1, 0}},
        {"llave 2", {1, 1, 0, 1, 1, 0}},
        {"llave 3", {0, 1, 1, 0, 0, 0}},
        {"llave 4", {1, 1, 0, 0, 0, 1}},
        {"llave 5", {0, 1, 1, 1, 0, 1}}
    };

    Solucion mejor = resolverPuertas(llaves, cantidadPuertas);

    if (!mejor.encontrada) {
        cout << "No hay un conjunto de llaves que abra todas las puertas.\n";
        return 0;
    }

    cout << "Cantidad minima de llaves: " << mejor.indices.size() << '\n';
    cout << "Llaves elegidas:\n";
    for (size_t k : mejor.indices) {
        cout << "- " << llaves[k].id << '\n';
    }
    return 0;
}
