// 321CA - Soare Mihai Daniel - Maximum Flow
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>

using namespace std;

#define INF 2147483646
#define NMAX 10001

vector<int> adjency[NMAX]; 
int capacity[NMAX][NMAX];
int parents[NMAX];

int bfs(int source, int destination)
{
	memset(parents, -1, sizeof(int) * (destination + 1));
	parents[source] = -2;
	queue<pair<int, int>> q;

	q.push({source, INF});

	while (!q.empty()) {
		int current = q.front().first;
		int flow = q.front().second;
		q.pop();

		for (int next : adjency[current]) {
			if (parents[next] == -1 && capacity[current][next]) {
				parents[next] = current;
				int new_flow = min(flow, capacity[current][next]);
				
				if (next == destination)
					return new_flow;
				
				q.push({next, new_flow});
			}
		}

	}

	return 0;
}

int edmonds_karp(int source, int destination)
{
	int new_flow, max_flow = 0;

	while ((new_flow = bfs(source, destination))) {
		max_flow += new_flow;

		int current = destination;
		while (current != source) {
			int prev = parents[current];

			capacity[prev][current] -= new_flow;
			capacity[current][prev] += new_flow;

			current = prev;
		}
	}

	return max_flow;
}

int main() {
	int edges, vertices;

	ifstream in("test.in");
	ofstream out("test.out");

	cin >> vertices >> edges;

	memset(capacity, 0, sizeof(capacity));

	for (int i = 0; i < edges; i++) {
		int source, destination, cap;

		cin >> source >> destination >> cap;
		source--;
		destination--;

		adjency[source].push_back(destination);
		adjency[destination].push_back(source);

		capacity[source][destination] += cap;
	}

	cout << edmonds_karp(0, vertices - 1) << endl;

	return 0;
}
