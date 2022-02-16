// 321CA -- Analiza Algoritmilor 2021 - 2022 -- Mihai Daniel Soare

Analiza Algoritmilor

Tema #2 - Reduceri polinomiale

------------------------------------------------------------------------------
2. Reclame Buclucase

Disclaimer: Voi incepe cu explicarea acestui task pentru ca a fost practic
starting point-ul rezolvarii temei pentru mine si restul au venit dupa ce am
inteles cum se rezolva / gandeste o rezolvare de genul pentru acest task.

Pentru a rezolva aceasta problema am redus polinomial problema NP-hard, Vertex
Cover (care reprezinta task-ul nostru) la problema NP-hard, SAT.

Putem face asta pentru ca ambele sunt NPC si sunt la fel de grele.

Algoritmul care sta la baza rezolvarii problemei este urmatorul:

- se citeste un graf
- crearea unei formule de tip FNC pentru SAT din nodurile grafului actual
- trimiterea inputului de tip FNC oracolului si primirea unor date
- descifrarea outputului primit de la oracol care poate fi considerat ca
adevarat, astfel incat sa fie extrase nodurile care reprezinta solutia
problemei noastre.
- scrierea raspunsului

Acest algoritm in mare se pastreaza si vor fi schimbati doar anumiti pasi
in functie de problema care va fi redusa la SAT.

A. Citirea unui graf
- se foloseste o matrice de adiacenta

B. Pentru problema actuala trebuie gasita o formula de tip FNC, astfel:

- se creaza o matrice de literali, pe care ii vom numerota in functie
de o ordine arbitrara
ex: literal[i][j] -> reprezinta valoarea de adevar a afirmatiei "nodul i
                    se afla pe j din acoperire"
- construim cu acesti literali urmatoarele categorii de constrangeri:
    -> clauza pentru a fi un nod pe fiecare pozitie din acoperire
    -> clauza pentru ca un nod sa se afle o singura data in acoperire
    -> clauza pentru a asigura ca cel putin unul dintre nodurile
    oricarei muchii se afla in acoperire
    -> clauza pentru a asigura ca nu pot exista pe aceeasi pozitie
    in acoperire mai multe noduri 
    
Complexitatea functiei de transformare a inputului problemei date in
inputului lui SAT este: O(N * K^2 + N^2 * K), unde N - nr de noduri si K -
nr de noduri acoperite.

Deoarece este o problema de optim, deci trebuie sa rulam reducerea
de mai multe ori si in cel mai rau caz, K ajunge sa fie egal cu N.

Obtinem complexitatea O(N^4).

C. Se translateaza pe baza formulei create la B. inputul primit in problema
k-acoperire in inputul problemei SAT si se trimite cererea la oracol.

D. Se interpreteaza raspunsul primit de la oracol si se extrag nodurile care
apartin acoperirii valide (daca exista) din graful initial.

E. Scrierea outputului la consola.
------------------------------------------------------------------------------
1. Reteaua sociala

Pentru a rezolva aceasta problema am redus polinomial problema NP-hard,
K-Clique (care reprezinta task-ul nostru) la problema NP-hard, SAT.

Putem face asta pentru ca ambele sunt NPC si sunt la fel de grele.

Se foloseste algoritmul mentionat anterior, doar ca vor ca apar urmatoarele
schimbari la functia de traducere a inputului. In schimb, vom rula acest
algoritm pentru un K fixat.

    literal[i][j] -> reprezinta valoarea de adevar a afirmatiei "nodul i
                    se afla pe j din clica"

- construim cu acesti literali urmatoarele categorii de constrangeri:
    -> clauza pentru a fi un nod pe fiecare pozitie din clica
    -> clauza pentru ca un nod sa se afle o singura data in clica
    -> clauza pentru a asigura ca ambele noduri ale unei legaturi
    care nu reprezinta o muchei nu sunt in acelasi timp in clica
    -> clauza pentru a asigura ca nu pot exista pe aceeasi pozitie
    in clica mai multe noduri 
    
Complexitatea functiei de transformare a inputului problemei date in
inputului lui SAT este: O(N * K^2 + N^2 * K), unde N - nr de noduri si K -
nr de noduri din clica.

Obtinem complexitatea O(N^4).

------------------------------------------------------------------------------
3. Alocarea registrilor

Pentru a rezolva aceasta problema am redus polinomial problema NP-hard,
K-color (care reprezinta task-ul nostru) la problema NP-hard, SAT.

Putem face asta pentru ca ambele sunt NPC si sunt la fel de grele.

Se foloseste algoritmul mentionat anterior, doar ca vor ca apar urmatoarele
schimbari la functia de traducere a inputului. In schimb, vom rula acest
algoritm pentru un K fixat.

    literal[i][j] -> reprezinta valoarea de adevar a afirmatiei "nodul i
                    este colorat cu culoarea j"

B. Pentru problema actuala trebuie gasita o formula de tip FNC, astfel:

- se creaza o matrice de literali, pe care ii vom numerota in functie
de o ordine arbitrara
ex: literal[i][j] -> reprezinta valoarea de adevar a afirmatiei "nodul i
                    se afla pe j din acoperire"
- construim cu acesti literali urmatoarele categorii de constrangeri:
    -> clauza pentru ca un nod sa fie colorat cu minim o culoare
    -> clauza pentru ca un nod sa fie colorat cu maxim o culoare
    -> clauza pentru a asigura pentru oricare muchie din graf cele doua
    capete nu sunt colorate cu aceeasi culoare.
    
Complexitatea functiei de transformare a inputului problemei date in
inputului lui SAT este: O(N * K^2 + N^2 * K), unde N - nr de noduri si K -
nr de culori.

D. Se interpreteaza raspunsul primit de la oracol si se extrag culorile
nodurilor.

------------------------------------------------------------------------------
