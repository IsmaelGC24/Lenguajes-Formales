#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <sstream>
#include <string>

using namespace std;

int main() {
    int numCases;
    cin >> numCases;
    
    for (int caseNum = 0; caseNum < numCases; caseNum++) {
        int numStates;
        cin >> numStates;
        
        // Leer alfabeto
        vector<char> alphabet;
        string line;
        cin.ignore(); // Limpiar el buffer
        getline(cin, line);
        stringstream ss(line);
        string symbol;
        while (ss >> symbol) {
            alphabet.push_back(symbol[0]);
        }
        
        // Leer estados finales
        set<int> finalStates;
        getline(cin, line);
        stringstream ss2(line);
        int state;
        while (ss2 >> state) {
            finalStates.insert(state);
        }
        
        // Leer tabla de transiciones
        vector<vector<int>> transitions(numStates, vector<int>(alphabet.size()));
        for (int i = 0; i < numStates; i++) {
            for (int j = 0; j < alphabet.size(); j++) {
                cin >> transitions[i][j];
            }
        }
        
        // Algoritmo de minimización
        vector<vector<bool>> marked(numStates, vector<bool>(numStates, false));
        
        // Paso 1: Marcar estados finales vs no finales
        for (int i = 0; i < numStates; i++) {
            for (int j = i + 1; j < numStates; j++) {
                bool iFinal = (finalStates.find(i) != finalStates.end());
                bool jFinal = (finalStates.find(j) != finalStates.end());
                if (iFinal != jFinal) {
                    marked[i][j] = true;
                    marked[j][i] = true;
                }
            }
        }
        
        // Paso 2: Marcar recursivamente
        bool changed;
        do {
            changed = false;
            for (int i = 0; i < numStates; i++) {
                for (int j = i + 1; j < numStates; j++) {
                    if (!marked[i][j]) {
                        for (int k = 0; k < alphabet.size(); k++) {
                            int nextI = transitions[i][k];
                            int nextJ = transitions[j][k];
                            if (marked[nextI][nextJ]) {
                                marked[i][j] = true;
                                marked[j][i] = true;
                                changed = true;
                                break;
                            }
                        }
                    }
                }
            }
        } while (changed);
        
        // Recolectar pares equivalentes
        vector<pair<int, int>> equivalentPairs;
        for (int i = 0; i < numStates; i++) {
            for (int j = i + 1; j < numStates; j++) {
                if (!marked[i][j]) {
                    equivalentPairs.push_back({i, j});
                }
            }
        }
        
        // Ordenar lexicográficamente
        sort(equivalentPairs.begin(), equivalentPairs.end());
        
        // Imprimir en formato requerido
        for (size_t i = 0; i < equivalentPairs.size(); i++) {
            cout << "(" << equivalentPairs[i].first << "," << equivalentPairs[i].second << ")";
            if (i < equivalentPairs.size() - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
    
    return 0;
}
