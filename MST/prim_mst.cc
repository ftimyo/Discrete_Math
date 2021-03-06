#include <cfloat>
#include <climits>
#include <queue>
#include <vector>
using uint = unsigned;
struct Node {
	uint v; float d;
	Node(uint v, float d) : v{v}, d{d}{}
	bool operator<(const Node& n) const {
		return d > n.d;
	}
};

struct Graph {
	std::vector<std::vector<Node> > adj;
	size_t V() const {return adj.size();}
};

class Prim {
	std::vector<uint> parent;
	std::vector<float> dist;
	std::vector<bool> visit;
	std::priority_queue<Node> pq;
	Prim(const Graph& G);
};

Prim::Prim(const Graph& G)
		: parent(G.V(), UINT_MAX),
			dist(G.V(), FLT_MAX),
			visit(G.V(), false) {
	uint v = 0;
	dist[v] = 0.0f; parent[v] = v;
	pq.emplace(v, 0.0f);
	while (!pq.empty()) {
		v = pq.top().v; pq.pop();
		if (visit[v]) continue;
		visit[v] = true;
		for (const auto& e : G.adj[v])
			if (dist[e.v] > e.d) {
				dist[e.v] = e.d;
				parent[e.v] = v;
				pq.push(e);
			}
	}
}

int main() {return 0;}
