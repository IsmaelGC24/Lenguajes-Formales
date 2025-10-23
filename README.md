DFA Minimization Algorithm
Student Information
Full Name: Ismael García Ceballos - Santiago Arellano López

Class Number: 5730

Environment Specifications
Operating System: Windows 10/11

Programming Language: C++ (C++11 standard or higher)

Compiler: g++ (MinGW) or compatible C++ compiler

Terminal: PowerShell or Command Prompt

Development Tools: Visual Studio Code or Visual Studio

Implementation Instructions
Prerequisites
Ensure you have a C++ compiler installed (g++ from MinGW recommended)

Create an input file named input.txt in the same directory as the executable

Compilation
Open your terminal and navigate to the project directory, then run:

g++ main.cpp -o dfa_minimizer
Execution
Using PowerShell:

Get-Content input.txt | .\dfa_minimizer.exe
Using Command Prompt (traditional):

dfa_minimizer.exe < input.txt
Input File Format
The input file must follow this exact structure:

1               # Number of test cases
6               # Number of states in the DFA
a b             # Alphabet symbols (space-separated)
1 4 5           # Final states (space-separated)
0 1 2           # Transition table rows:
1 3 4           # - Each line represents a state
2 4 3           # - Columns correspond to alphabet symbols
3 5 5           #   in the order specified
4 5 5
5 5 5

Expected Output
The program outputs equivalent state pairs in lexicographical order on a single line:

(2,3)
Algorithm Explanation
This implementation follows the DFA minimization algorithm from Kozen's "Automata and Computability" (Lecture 14). The algorithm identifies equivalent states that can be collapsed to produce a minimal DFA.

Algorithm Steps
Initialization Phase

Create a table of all unordered state pairs {p,q} where p < q

Initialize all pairs as unmarked

Base Case Marking

Mark any pair {p,q} where one state is final and the other is non-final

These pairs are clearly non-equivalent since they differ on the empty string ε

Recursive Marking

Repeatedly scan unmarked pairs {p,q}

For each unmarked pair, check if there exists any symbol a ∈ Σ such that the transition δ(p,a) and δ(q,a) leads to a marked pair

If such a symbol exists, mark {p,q} as non-equivalent

Continue until no new pairs can be marked in a complete pass

Equivalent State Identification

After stabilization, unmarked pairs represent equivalent states

These states can be merged in the minimized automaton

Complexity Analysis
Time Complexity: O(n² × |Σ|) where n is the number of states and |Σ| is the alphabet size

Space Complexity: O(n²) for storing the marking table

Key Properties
The algorithm correctly identifies all equivalent state pairs

The resulting DFA is minimal and unique up to isomorphism

All inaccessible states are assumed to be removed prior to minimization (as per assignment requirements)

References
Kozen, D. C. (1997). Automata and Computability. Springer-Verlag. ISBN: 0387949070