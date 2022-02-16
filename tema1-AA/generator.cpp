#include<bits/stdc++.h>
using namespace std;
  
#define RUN 1
  
// numar maxim de noduri
#define MAX_VERTICES 3000
  
// numar maxim de muchii
#define MAX_EDGES 3000
  
// numar maxim de capacitati
#define MAXWEIGHT 10000

vector<int> G[MAX_VERTICES + 1];
bool visited[MAX_VERTICES + 1];

void dfs(int index)
{
	visited[index] = 1;

	for (int i = 0; i < G[index].size(); i++) {
		if (visited[G[index][i]] == 0)
			dfs(G[index][i]);
	}
}

int main()
{
	set<pair<int, int>> container;
	set<pair<int, int>>::iterator it;
  
	// For random values every time
	srand(time(NULL));
  
	int NUM;    // Number of Vertices
	int NUMEDGE; // Number of Edges
  
	for (int i = 1; i <= RUN; i++)
	{
		// initializam numarul noduri si muchii
		NUM = 1 + rand() % MAX_VERTICES;
		NUMEDGE = 1 + rand() % MAX_EDGES;

		// cream nr de muchii in functie de o restrictie
		while (NUMEDGE > pow(NUM, 1.25))
			NUMEDGE = 1 + rand() % MAX_EDGES;
  
		// generam perechile de muchii
		for (int j = 1; j <= NUMEDGE; j++)
		{
			int a = 1 + rand() % NUM;
			int b = 1 + rand() % NUM;
			pair<int, int> p = make_pair(a, b);
  
			// cauta o noua muchie
			while (container.find(p) != container.end()) {
				a = 1 + rand() % NUM;
				b = 1 + rand() % NUM;
				p = make_pair(a, b);
			}
			container.insert(p);
		}
  
		// verificam sa fie graf conex si care sa inceapa din nodul 1
		// si sa termine in nr_noduri - 1
		for (it = container.begin(); it!=container.end(); ++it) {
			G[it->first].push_back(it->second);
		}

		dfs(1);

		if (visited[NUM] == 0) {
			i--;
			container.clear();
			continue;
		}

		// verificam daca graful gasit de noi respecta conditiile
		// si continuam sa ne jucam cu el
		printf("%d %d\n", NUM, NUMEDGE);

		// pentru fiecare muchie atribuim si o cantitate
		for (it = container.begin(); it != container.end(); ++it) {
			int wt = 1 + rand() % MAXWEIGHT;
			printf("%d %d %d\n", it->first, it->second, wt);
		}

		container.clear();
	}
  
	return(0);
}