#include <cfloat>
#include <climits>
#include <queue>
#include <vector>
#include <map>
using namespace std;

struct Node {
	int v; float d;
	Node(int v, float d) : v{v}, d{d}{}
	bool operator<(const Node& n) const {
		return d > n.d;
	}
};

struct Graph {
	map<int, vector<Node> > adj;
	size_t V() const {return adj.size();}
};

class Prim {
	std::vector<int> parent;
	std::vector<float> dist;
	std::vector<bool> visit;
	std::priority_queue<Node> pq;
	Prim(Graph& G);
};

Prim::Prim(Graph& G)
		: parent(G.V(), INT_MAX),
			dist(G.V(), FLT_MAX),
			visit(G.V(), false) {
	auto v = G.adj.begin()->first;
	dist[v] = 0.0f; parent[v] = v;
	pq.emplace(v, 0.0f);
	while (!pq.empty()) {
		v = pq.top().v; pq.pop();
		if (visit[v]) continue;
		for (auto e : G.adj[v])
			if (dist[e.v] > e.d) {
				dist[e.v] = e.d;
				parent[e.v] = v;
				pq.push(e);
			}
	}
}

int main() {
	return 0;
}
