#include <map>
#include <vector>
#include <queue>
#include <cfloat>
#include <climits>

struct Node {
	int v; float d;
	Node(int v, float d) : v{v}, d{d} {}
	bool operator<(const Node& n) const {
		return d > n.d;
	}
};

struct Graph {
	std::map<int, std::vector<Node>> adj;
	size_t V() {return adj.size();}
};

class Prim_Forest {
 public:
	std::vector<int> parent;
	std::vector<float> dist;
	std::vector<bool> visit;
	std::priority_queue<Node> pq;
	Prim_Forest(Graph& G);
};

Prim_Forest::Prim_Forest(Graph& G)
		: parent(G.V(), INT_MAX),
			dist(G.V(), FLT_MAX),
			visit(G.V(), false) {
	for (auto vertex : G.adj) {
		auto v = vertex.first;
		if (visit[v]) continue;
		parent[v] = v; dist[v] = 0.0f; pq.emplace(v, 0.0f);
		while (!pq.empty()) {
			v = pq.top().v; pq.pop();
			if (visit[v]) continue;
			visit[v] = true;
			for (auto e : G.adj[v])
				if (e.d < dist[e.v]) {
					dist[e.v] = e.d; parent[e.v] = v; pq.push(e);
				}
		}
	}
}

int main() {
	return 0;
}
