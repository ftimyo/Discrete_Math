#include <vector>
#include <queue>
#include <climits>
#include <cfloat>
using uint = unsigned;
struct Node {
	uint v; float d;
	Node(uint v, float d) : v{v}, d{d} {}
	bool operator<(const Node& n) const {return d > n.d;}
};

struct Digraph {
	std::vector<std::vector<Node> > adj;
	size_t V() {return adj.size();}
};

class Dijkstra_SP {
 public:
	std::vector<uint> parent;
	std::vector<float> dist;
	std::vector<bool> visit;
	std::priority_queue<Node> pq;
	uint source;
	Dijkstra_SP(Digraph& G, uint s);
};

Dijkstra_SP::Dijkstra_SP(Digraph& G, uint s)
		: parent(G.V(), UINT_MAX),
			dist(G.V(), FLT_MAX),
			visit(G.V(), false),
			source{s} {
	parent[s] = s; dist[s] = 0.0f; pq.emplace(s, dist[s]);
	while (!pq.empty()) {
		auto v = pq.top().v; pq.pop();
		if (visit[v]) continue;
		visit[v] = true;
		for (const auto& e : G.adj[v])
			if (dist[e.v] > e.d + dist[v]) {
				dist[e.v] = e.d + dist[v];
				parent[e.v] = v;
				pq.emplace(e.v, dist[e.v]);
			}
	}
}

int main() {return 0;}
