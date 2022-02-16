// 321CA -- Analiza Algoritmilor 2021 - 2022 -- Mihai Daniel Soare
#include <iostream>
#include "task.h"
#include <fstream>
#include <vector>

#define NMAX 1000
using namespace std;

class Reclame : public Task
{
    // numarul de noduri
    int no_nodes;
    // numarul de muchii
    int no_edges;
    // numarul de noduri acoperite
    int no_cover;
    int graph[NMAX][NMAX];
    int literals[NMAX][NMAX];
    vector<int> lit_to_val;
    vector<int> k_cover;
    string answer;

public:
    void solve();
    void read_problem_data();
    void formulate_oracle_question();
    void decipher_oracle_answer();
    void write_answer();
};

void Reclame::solve()
{
    read_problem_data();

    // incercam pentru n valori, solutii pentru aflarea celei mai mici
    // valori de acoperire astfel incat problema sa fie rezolvata si
    // formula satisfiabila
    for (no_cover = 1; no_cover <= no_nodes; no_cover++) {
        formulate_oracle_question();
        ask_oracle();
        decipher_oracle_answer();
        if (answer.compare("True") == 0)
            break;
    }
    write_answer();
}

void Reclame::read_problem_data()
{
    cin >> no_nodes >> no_edges;
    for (int i = 1; i <= no_edges; i++) {
        int node_left, node_right;

        cin >> node_left >> node_right;
        graph[node_left][node_right] = 1;
        graph[node_right][node_left] = 1;
    }
}

void Reclame::formulate_oracle_question()
{
    int value = 1;

    // se creaza 2d array-ul care contine literalii problemei
    // va fi de forma N * K, unde N = nr noduri pe linii, K = nr de noduri acoperite
    // iar fiecare valoare din literali va fi crescatoare pana la N * K
    for (int i = 1; i <= no_nodes; i++) {
        for (int j = 1; j <= no_cover; j++) {
            literals[i][j] = value;
            value++;
        }
    }

    ofstream out("sat.cnf");

    int no_clauses = no_cover // (1)
                    + no_cover * no_cover * no_nodes
                                - no_cover * no_nodes // (2)
                    + 2 * no_edges // (3)
                    + no_nodes * no_nodes * no_cover 
                                - no_nodes * no_cover; // (4)

    out << "p cnf " << value - 1 << " " << no_clauses << '\n';

    // clauza pentru a fi cel putin un nod pe fiecare pozitie din acoperire
    // complexitate: O(N * K) || clauze: (1)
    for (int j = 1; j <= no_cover; j++) {
        for (int i = 1; i <= no_nodes; i++) {
            out << literals[i][j] << " ";
        }
        out << "0\n";
    }

    // clauza pentru ca un nod sa se afle o singura data in acoperire
    // complexitate: O(N * K^2) || clauze: (2)
    for (int v = 1; v <= no_nodes; v++) {
        for (int i = 1; i <= no_cover; i++) {
            for (int j = 1; j <= no_cover; j++) {
                // se da skip sa nu se compare acelasi nod cu el insusi
                if (i == j)
                    continue;

                out << "-" << literals[v][i] << " -" << literals[v][j] << " 0\n";
            }
        }
    }

    // clauza pentru a verifica daca cel putin unul dintre nodurile fiecarei muchii
    // se afla in acoperire
    // complexitate: O(N ^ 2 * K) || clauze: (3)
    for (int u = 1; u <= no_nodes; u++) {
        for (int v = 1; v <= no_nodes; v++) {
            // verificarea muchiilor
            if (graph[u][v] == 1) {
                for (int i = 1; i <= no_cover; i++) {
                    out << literals[u][i] << " ";
                }
                for (int i = 1; i <= no_cover; i++) {
                    out << literals[v][i] << " ";
                }
                out << "0\n";
            }
        }
    }

    // doua noduri nu pot exista pe aceeasi pozitie in acoperire
    // complexitate: O(N^2 * K) || clauze: (4)
    for (int i = 1; i <= no_cover; i++) {
        for (int u = 1; u <= no_nodes; u++) {
            for (int v = 1; v <= no_nodes; v++) {
                if (u == v)
                    continue;

                out << "-" << literals[u][i] << " -" << literals[v][i] << " 0\n";
            }
        }
    }    
}

void Reclame::decipher_oracle_answer()
{
    ifstream in("sat.sol");
    in >> answer;
    if (answer.compare("True") == 0) {
        int no_literals;
        in >> no_literals;

        // preluarea nodurilor corespunzatoare literalilor pozitivi
        for (int i = 1; i <= no_literals; i++) {
            int literal;
            in >> literal;
            if (literal > 0 ) {
                k_cover.push_back((literal - 1) / no_cover + 1);
            }             
        }

    }
}

void Reclame::write_answer()
{
    if (answer.compare("True") == 0)
        for (int i = 0; i < no_cover; i++)
            cout << k_cover[i] << " ";
}

int main() {
    Reclame reclame;
    reclame.solve();

    return 0;
}