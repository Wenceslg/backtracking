#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

const int CAPACIDAD = 300;

vector<int> piezas;

// Estado de la solución que estamos construyendo.
vector<int> espacioLibre;
vector<vector<int>> cortes;

// Mejor solución encontrada.
int mejorCantidad;
vector<vector<int>> mejorCortes;

void backtracking(int posicion) {
    int usadas = static_cast<int>(cortes.size());

    // Esta rama no puede mejorar la mejor solución.
    if (usadas >= mejorCantidad)
        return;

    // Ya ubicamos todas las piezas.
    if (posicion == static_cast<int>(piezas.size())) {
        mejorCantidad = usadas;
        mejorCortes = cortes;
        return;
    }

    int pieza = piezas[posicion];

    // Evita probar varillas con el mismo espacio libre.
    vector<int> espaciosProbados;

    // Opción 1: colocar la pieza en una varilla existente.
    for (int i = 0; i < usadas; ++i) {
        if (espacioLibre[i] < pieza)
            continue;

        if (find(espaciosProbados.begin(), espaciosProbados.end(),
                 espacioLibre[i]) != espaciosProbados.end())
            continue;

        espaciosProbados.push_back(espacioLibre[i]);

        // Elegir.
        espacioLibre[i] -= pieza;
        cortes[i].push_back(pieza);

        // Explorar.
        backtracking(posicion + 1);

        // Deshacer.
        cortes[i].pop_back();
        espacioLibre[i] += pieza;
    }

    // Opción 2: comprar una nueva varilla.
    // Solo tiene sentido si todavía podemos mejorar.
    if (usadas + 1 < mejorCantidad) {
        espacioLibre.push_back(CAPACIDAD - pieza);
        cortes.push_back({pieza});

        backtracking(posicion + 1);

        cortes.pop_back();
        espacioLibre.pop_back();
    }
}

int main() {
    int n;
    cin >> n;

    if (n < 0)
        return 1;

    piezas.resize(n);

    // Las longitudes se ingresan en metros, por ejemplo: 1.25.
    for (int i = 0; i < n; ++i) {
        double metros;
        cin >> metros;

        if (metros < 0.10 || metros > 3.0) {
            cout << "Longitud invalida\n";
            return 1;
        }

        piezas[i] = static_cast<int>(lround(metros * 100));
    }

    sort(piezas.rbegin(), piezas.rend());

    // Como máximo, necesitamos una varilla por pieza.
    // n + 1 permite registrar la primera solución completa.
    mejorCantidad = n + 1;

    backtracking(0);

    cout << "Cantidad minima de varillas: "
         << mejorCantidad << '\n';

    for (int i = 0; i < mejorCantidad; ++i) {
        cout << "Varilla " << i + 1 << ": ";

        int total = 0;
        for (int pieza : mejorCortes[i]) {
            cout << pieza << " cm ";
            total += pieza;
        }

        cout << "| Sobrante: " << CAPACIDAD - total << " cm\n";
    }

    return 0;
}