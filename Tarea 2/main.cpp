#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Funcion que genera las formas sentenciales en una derivacion mas la izquierda
vector<string> derivation(const string &cadena) {
    vector<string> pasos;
    int n = cadena.size() / 2; 
    string s = "S";
    pasos.push_back(s);

    // reemplazar S por aSb n veces
    for (int i = 0; i < n; i++) {
        s = s.replace(s.find("S"), 1, "aSb");
        pasos.push_back(s);
    }

    // reemplazar la S final por ε
    s.replace(s.find("S"), 1, "");
    pasos.push_back(s);

    return pasos;
}

int main() {
    //utilizamos las cadenas aceptabas por el algoritmo 2
    string aceptadas[] = {"ab", "aabb"};

    for (auto &cadena : aceptadas) {
        cout << "\nLeftmost derivation for '" << cadena << "':\n";
        vector<string> pasos = derivation(cadena);
        for (auto &p : pasos) cout << p << endl;
    }

    return 0;
}