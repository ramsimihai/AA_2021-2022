// 321CA -- Analiza Algoritmilor 2021 - 2022 -- Mihai Daniel Soare
#include <iostream>
#include "task.h"
#include <fstream>
#include <vector>

#define NMAX 1000
using namespace std;

class Registre : public Task
{
    // numarul de noduri
    int no_nodes;
    // numarul de muchii
    int no_edges;
    // numarul de noduri acoperite
    int no_colour;
    int graph[NMAX][NMAX];
    int literals[NMAX][NMAX];
    vector<int> k_colour;
    string answer;

public:
    void solve();
    void read_problem_data();
    void formulate_oracle_question();
    void decipher_oracle_answer();
    void write_answer();
};

void Registre::solve()
{
    read_problem_data();
    formulate_oracle_question();
    ask_oracle();
    decipher_oracle_answer();
    write_answer();
}

void Registre::read_problem_data()
{
    cin >> no_nodes >> no_edges >> no_colour;
    for (int i = 1; i <= no_edges; i++) {
        int node_left, node_right;

        cin >> node_left >> node_right;
        graph[node_left][node_right] = 1;
        graph[node_right][node_left] = 1;
    }
}

void Registre::formulate_oracle_question()
{
    int value = 1;

    // se creaza 2d array-ul care contine literalii problemei
    // va fi de forma N * K, unde N = nr noduri pe linii, K = nr de culori
    // iar fiecare valoare din literali va fi crescatoare pana la N * K
    for (int i = 1; i <= no_nodes; i++) {
        for (int j = 1; j <= no_colour; j++) {
            literals[i][j] = value;
            value++;
        }
    }

    ofstream out("sat.cnf");

    int no_clauses = no_nodes // (1)
                     + no_nodes * no_colour * (no_colour - 1) // (2)
                     + 2 * no_edges * no_colour; // (3)
    
    out << "p cnf " << value - 1 << " " << no_clauses << '\n';

    // clauza pentru a fi cel putin un nod pentru fiecare culoare
    // complexitate: O(N * K) || clauze: (1)
    for (int i = 1; i <= no_nodes; i++) {
        for (int j = 1; j <= no_colour; j++)
            out << literals[i][j] << " ";

        out << "0\n";
    }

    // clauza pentru ca un nod sa nu aiba mai multe culori
    // complexitate: O(N * K^2) || clauze: (2)
    for (int v = 1; v <= no_nodes; v++) {
        for (int i = 1; i <= no_colour; i++) {
            for (int j = 1; j <= no_colour; j++) {
                // se da skip sa nu se compare acelasi nod cu el insusi
                if (i == j)
                    continue;

                out << "-" << literals[v][i] << " -" << literals[v][j] << " 0\n";
            }
        }
    }

    // clauza pentru a verifica daca nodurile oricarei muchii sunt colorate diferit
    // complexitate: O(N ^ 2 * K) || clauze: (3)
    for (int u = 1; u <= no_nodes; u++) {
        for (int v = 1; v <= no_nodes; v++) {
            if (graph[u][v] == 1) {
                for (int i = 1; i <= no_colour; i++) {
                    out << "-" << literals[u][i] << " -" << literals[v][i] << " 0\n";
                }
            }
        }
    } 
}

void Registre::decipher_oracle_answer()
{
    ifstream in("sat.sol");
    in >> answer;

    if (answer.compare("True") == 0) {
        int no_literals;
        in >> no_literals;

        for (int i = 1; i <= no_literals; i++) {
            // citim fiecare literal
            int literal;
            in >> literal;

            // extragem culoarea unui nod
            if (literal > 0 ) {
                literal = literal % no_colour;
                literal = literal == 0 ? no_colour : literal;

                // fiecare nod este colorat cu o singure culoare, deci
                // culorile vor fi adaugate in vector in ordine
                k_colour.push_back(literal);
            }             
        }

    }
}

void Registre::write_answer()
{
    cout << answer << "\n";

    if (answer.compare("True") == 0)
        for (int i = 0; i < no_nodes; i++)
            cout << k_colour[i] << " ";
}

int main() {
    Registre Registre;
    Registre.solve();

    return 0;
}