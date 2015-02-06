#include <vector>
#include <stack>
#include <algorithm>

using uint = unsigned;
struct Node {
	uint v; float w;
};
struct Digraph {
	std::vector<std::vector<Node> > adj;
	size_t V() {return adj.size();}
};

class Tarjan_SCC {
 public:
 std::vector<uint> visit, low, scc;
 std::vector<bool> inStack_;
 std::stack<uint> stack_;
 uint order, id;
 void DFS(uint v, Digraph& G);
 Tarjan_SCC(Digraph& G);
};

void Tarjan_SCC::DFS(uint v, Digraph& G) {
	visit[v] = low[v] = ++order;
	stack_.push(v); inStack_[v] = true;
	for (auto w : G.adj[v]) {
		if (!visit[w.v]) DFS(w.v, G);
		if (inStack_[w.v]) low[v] = std::min(low[w.v], low[v]);
	}
	if (visit[v] == low[v]) {
		uint w; ++id;
		do {
			w = stack_.top(); stack_.pop(); inStack_[w] = false;
			scc[w] = id;
		} while(w != v);
	}
}

Tarjan_SCC::Tarjan_SCC(Digraph& G)
		: visit(G.V(), 0), low(G.V(), 0),
			scc(G.V(), 0), inStack_(G.V(), false),
			order{0}, id{0} {
	for (uint v = 0; v < G.V(); ++v)
		if (!visit[v]) DFS(v, G);
}

int main() {return 0;}
