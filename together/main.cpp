#include<fstream>
#include<vector>
#include<list>
#include<stack>
#include<algorithm>
#include<climits>
using namespace std;

string const iname = "in.txt";
string const oname = "output.txt";

class Graph
{
public:
	int v;
	int e;
	int f;

	struct edge
	{
		int v1;
		int v2;
		int w;
		edge(int a, int b, int c) : v1(a), v2(b), w(c) {}
	};

	vector<vector<pair<int,int>>> adj; // ind - from, first - to, second - weight
	vector<edge> edges;
	vector<int> distances; // 0 to all
	vector<bool> used; // for dijkstra
	vector<bool> in_spt;
	vector<int> labs;
	long long mask;
	vector<edge> reverse;
	Graph()
	{
		ifstream input;
		input.open(iname);
		input >> v;
		input >> e;
		input >> f;
		adj.resize(v);
		used.resize(v);
		distances.resize(v);
		labs.resize(f);
		in_spt.resize(e*2);
		for (int i = 0; i < f; i++)
			input >> labs[i];
		for (int i = 0; i < e; i++)
		{
			int to;
			int from;
			int w;
			input >> from;
			input >> to;
			input >> w;
			adj[from].emplace_back(to, w);
			adj[to].emplace_back(from, w);
			edge t1 = edge(from, to, w);
			edges.emplace_back(t1);
			edge t2 = edge(to, from, w);
			edges.emplace_back(t2);
		}
	}

	void dijkstra()
	{
		for (int i = 1; i < v; i++)
			distances[i] = INT_MAX;
		distances[0] = 0;
		////
		vector<int> p(v);
		for (int i = 0; i < v; ++i) {
			int curr = -1;
			for (int j = 0; j < v; ++j)
				if (!used[j] && (curr == -1 || distances[j] < distances[curr]))
					curr = j;
			if (distances[curr] == INT_MAX)
				break;
			used[curr] = true;

			for (size_t j = 0; j < adj[curr].size(); ++j) {
				int to = adj[curr][j].first,
					len = adj[curr][j].second;
				if (distances[curr] + len < distances[to]) {
					distances[to] = distances[curr] + len;
					p[to] = curr;
				}
			}
		}
		/////
	}

	void make_spt()
	{	
		for (int i = 0; i < e*2; i++)
			in_spt[i] = false;

		for (int i = 0; i < e*2; i++)
			if (distances[edges[i].v2] == distances[edges[i].v1] + edges[i].w)
				in_spt[i] = true;
	}

	void make_reverse()
	{
		for (int i = 0; i < in_spt.size(); i++)
			if (in_spt[i])
			{
				edge t = edge(edges[i].v2, edges[i].v1, edges[i].w);
				reverse.emplace_back(t);
			}
	}
};

int main()
{
	Graph graph = Graph();
	graph.dijkstra();
	graph.make_spt();
	graph.make_reverse();
	getchar();
}