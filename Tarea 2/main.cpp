#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

class Grammar {
private:
    vector<char> nonterminals;
    map<char, vector<string>> productions;

    char getNewNonterminal() {
        for (char c = 'A'; c <= 'Z'; c++) {
            if (find(nonterminals.begin(), nonterminals.end(), c) == nonterminals.end() && c != 'S') {
                return c;
            }
        }
        for (char c = 'A'; c <= 'Z'; c++) {
            if (c != 'S') return c;
        }
        return 'X';
    }
    
    void eliminateImmediateLeftRecursion(char A) {
        vector<string>& currentProds = productions[A];
        vector<string> alpha;
        vector<string> beta;
        
        for (const string& prod : currentProds) {
            if (!prod.empty() && prod[0] == A) {
                alpha.push_back(prod.substr(1));
            } else {
                beta.push_back(prod);
            }
        }
        
        if (alpha.empty()) return;
        
        char newNT = getNewNonterminal();
        nonterminals.push_back(newNT);
        
        vector<string> newAProds;
        for (const string& b : beta) {
            newAProds.push_back(b + string(1, newNT));
        }
        productions[A] = newAProds;
        
        vector<string> newNTProds;
        for (const string& a : alpha) {
            newNTProds.push_back(a + string(1, newNT));
        }
        newNTProds.push_back("e");
        productions[newNT] = newNTProds;
    }
    
    void replaceProductions(int i, const vector<char>& orderedNonterminals) {
        char Ai = orderedNonterminals[i];
        vector<string> newProds;
        
        for (const string& prod : productions[Ai]) {
            if (prod.empty()) {
                newProds.push_back(prod);
                continue;
            }
            
            bool replaced = false;
            for (int j = 0; j < i; j++) {
                char Aj = orderedNonterminals[j];
                if (prod[0] == Aj) {
                    replaced = true;
                    string gamma = prod.substr(1);
                    
                    for (const string& delta : productions[Aj]) {
                        if (delta == "e") {
                            newProds.push_back(gamma.empty() ? "e" : gamma);
                        } else {
                            newProds.push_back(delta + gamma);
                        }
                    }
                    break;
                }
            }
            
            if (!replaced) {
                newProds.push_back(prod);
            }
        }
        
        productions[Ai] = newProds;
    }

public:
    void addProduction(char nonterminal, const vector<string>& alternatives) {
        if (find(nonterminals.begin(), nonterminals.end(), nonterminal) == nonterminals.end()) {
            nonterminals.push_back(nonterminal);
        }
        productions[nonterminal] = alternatives;
    }
    
    void eliminateLeftRecursion() {
        vector<char> orderedNonterminals;
        
        if (productions.find('S') != productions.end()) {
            orderedNonterminals.push_back('S');
        }
        
        for (char c = 'A'; c <= 'Z'; c++) {
            if (c != 'S' && productions.find(c) != productions.end()) {
                orderedNonterminals.push_back(c);
            }
        }
        
        for (int i = 0; i < orderedNonterminals.size(); i++) {
            replaceProductions(i, orderedNonterminals);
            eliminateImmediateLeftRecursion(orderedNonterminals[i]);
        }
    }
    
    void printGrammar() const {
        vector<char> outputOrder;
        
        if (productions.find('S') != productions.end()) {
            outputOrder.push_back('S');
        }
        
        for (char c = 'A'; c <= 'Z'; c++) {
            if (c != 'S' && productions.find(c) != productions.end()) {
                outputOrder.push_back(c);
            }
        }
        
        for (char nt : outputOrder) {
            const vector<string>& prods = productions.at(nt);
            if (prods.empty()) continue;
            
            cout << nt << " -> ";
            for (size_t i = 0; i < prods.size(); i++) {
                cout << prods[i];
                if (i < prods.size() - 1) {
                    cout << " ";
                }
            }
            cout << endl;
        }
    }
};

vector<string> parseAlternatives(const string& altStr) {
    vector<string> alternatives;
    string current;
    
    for (char c : altStr) {
        if (c == ' ') {
            if (!current.empty()) {
                alternatives.push_back(current);
                current.clear();
            }
        } else {
            current += c;
        }
    }
    
    if (!current.empty()) {
        alternatives.push_back(current);
    }
    
    return alternatives;
}

int main() {
    int n;
    cin >> n;
    
    for (int caseNum = 0; caseNum < n; caseNum++) {
        if (caseNum > 0) {
            cout << endl;
        }
        
        int k;
        cin >> k;
        cin.ignore();
        
        Grammar grammar;
        
        for (int i = 0; i < k; i++) {
            string line;
            getline(cin, line);
            
            size_t arrowPos = line.find("->");
            if (arrowPos == string::npos) {
                continue;
            }
            
            char nonterminal = line[0];
            string alternativesStr = line.substr(arrowPos + 2);
            
            // Limpiar espacios
            alternativesStr.erase(0, alternativesStr.find_first_not_of(" "));
            alternativesStr.erase(alternativesStr.find_last_not_of(" ") + 1);
            
            vector<string> alternatives = parseAlternatives(alternativesStr);
            grammar.addProduction(nonterminal, alternatives);
        }
        
        grammar.eliminateLeftRecursion();
        grammar.printGrammar();
    }
    
    return 0;
}