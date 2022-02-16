#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <stack>
#include <climits>
#include <cstring>

using namespace std;

#define INF 2147483646
#define NMAX 10001

vector<int> adjency[NMAX]; 
int capacity[NMAX][NMAX];
int parents[NMAX];

int dfs(int source, int destination)
{
	memset(parents, -1, sizeof(int) * (destination + 1));
	parents[source] = -2;
	stack<pair<int, int>> s;

	s.push({source, INF});

	while (!s.empty()) {
		int current = s.top().first;
		int flow = s.top().second;
		s.pop();

		for (int next : adjency[current]) {
			if (parents[next] == -1 && capacity[current][next]) {
				parents[next] = current;
				int new_flow = min(flow, capacity[current][next]);
				
				if (next == destination)
					return new_flow;
				
				s.push({next, new_flow});
			}
		}

	}

	return 0;
}

int greedy_ford_fulkerson(int source, int destination)
{
	int new_flow, max_flow = 0;

	while ((new_flow = dfs(source, destination))) {
		max_flow += new_flow;

		int current = destination;
		while (current != source) {
			int prev = parents[current];

			capacity[prev][current] -= new_flow;

			current = prev;
		}
	}

	return max_flow;
}

int main() {
	int edges, vertices;

	cin >> vertices >> edges;

	memset(capacity, 0, sizeof(capacity));

	for (int i = 0; i < edges; i++) {
		int source, destination, cap;

		cin >> source >> destination >> cap;
		source--;
		destination--;

		adjency[source].push_back(destination);

		capacity[source][destination] += cap;
	}
	
	cout << greedy_ford_fulkerson(0, vertices - 1) << endl;
	return 0;
}
