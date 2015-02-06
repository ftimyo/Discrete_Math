#include <vector>
#include <algorithm>

using uint = unsigned;

struct Node {
	uint v; float w;
};

struct Graph {
	std::vector<std::vector<Node> > adj;
	size_t V() {return adj.size();}
};

class AV {
 public:
	std::vector<uint> visit, low, av;
	uint order;
	void DFS(uint p, uint v, Graph& G);
	AV(Graph& G);
};

void AV::DFS(uint p, uint v, Graph& G) {
	visit[v] = low[v] = ++order;
	uint child{0}; bool isAV{false};
	for (const auto& w : G.adj[v]) {
		if (w.v == p) continue;
		if (!visit[w.v]) {
			++child;
			DFS(v, w.v, G);
			low[v] = std::min(low[w.v], low[v]);
			if (low[w.v] >= visit[v]) isAV = true;
		} else {
			low[v] = std::min(visit[w.v], low[v]);
		}
	}
	if ((p == v && child > 1) || (p != v && isAV))
		av.push_back(v);
}

AV::AV(Graph& G)
		: visit(G.V(), 0),
			low(G.V(), 0),
			order{0} {
	for (uint v = 0; v < G.V(); ++v)
		if (!visit[v]) DFS(v, v, G);
}

int main() {return 0;}
