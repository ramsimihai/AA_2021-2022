// 321CA - Soare Mihai Daniel - Maximum Flow
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <list>
#include <queue>

using namespace std;

struct Edge {
	int vertices;
	int flow;
	int capacity;
	long unsigned int rev;
};

class Graph
{
	int nr_vertices;
	int *level;
	vector<Edge> *adjency;

public:
	Graph(int nr_vertices) {
		adjency = new vector<Edge>[nr_vertices];
		this->nr_vertices = nr_vertices;
		level = new int[nr_vertices];
	}

	void addEdge(int u, int v, int capacity) {
		Edge newEdgeA{v, 0, capacity, adjency[v].size()};

		Edge newEdgeB{u, 0, 0, adjency[u].size()};

		adjency[u].push_back(newEdgeA);
		adjency[v].push_back(newEdgeB);
	}

	bool bfs(int source, int destination);
	int sendFlow(int source, int flow, int destination, int ptr[]);
	int dinics(int source, int destination);
};

bool Graph::bfs(int source, int destination) {
	for (int i = 0; i < nr_vertices; i++)
		level[i] = -1;

	level[source] = 0;

	queue<int> q;
	q.push(source);

	while(!q.empty()) {
		int current = q.front();
		q.pop();

		for (Edge next : adjency[current]) {
			Edge& edge = next;
			if (level[edge.vertices] < 0 && edge.flow < edge.capacity) {
				level[edge.vertices] = level[current] + 1;
				q.push(edge.vertices);
			}	
		}
	}

	return level[destination] < 0 ? false : true;
}

int Graph::sendFlow(int vertices, int flow, int destination, int start[]) {
	if (vertices == destination)
		return flow;
	
	while (start[vertices] < (int) adjency[vertices].size()) {
		Edge &edge = adjency[vertices][start[vertices]];

		if (level[edge.vertices] == level[vertices] + 1 &&
			edge.flow < edge.capacity) {
			int current_flow = min(flow, edge.capacity - edge.flow);

			int temp_flow = sendFlow(edge.vertices, current_flow, destination, start);
			if (temp_flow > 0) {
				edge.flow += temp_flow;
				adjency[edge.vertices][edge.rev].flow -= temp_flow;

				return temp_flow;
			}
		}
		
		start[vertices]++;
	}

	return 0;
}

int Graph::dinics(int source, int destination) {
	if (source == destination)
		return -1;

	int total = 0;

	while(bfs(source, destination) == true) {
		int* start = new int[nr_vertices + 1]{0};

		while (int flow = sendFlow(source, 1e9, destination, start))
			total += flow;
	}

	return total;
}
int main()
{
	int vertices, edges;

	cin >> vertices >> edges;

	Graph g(vertices);

	for (int i = 1; i <= edges; i++) {
		int to, from, capacity;

		cin >> to >> from >> capacity;
		g.addEdge(to - 1, from - 1, capacity);
	}

	cout << g.dinics(0, vertices - 1) << endl;

	return 0;
}
