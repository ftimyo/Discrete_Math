#include <map>
#include <vector>
#include <queue>
#include <cfloat>
#include <climits>
#include <iterator>
#include <algorithm>
using uint = unsigned;

struct Digraph {
	/*map<vertex_id, capacity>*/
	std::vector<std::map<uint, float> > adj;
	size_t V() const {return adj.size();}
	Digraph(const Digraph& G) : adj{G.adj} {}
	Digraph() = default;
};

struct Edge {
	uint v1, v2;
	float c;
	Edge(uint v1, uint v2, float c) : v1{v1}, v2{v2}, c{c} {}
};

class Edmond_Karp {
	std::vector<bool> visit;
	std::vector<uint> path;
	uint s, t;
	Digraph R, F, C;
 public:
	std::vector<Edge> cuts;
	float max_flow;
	float BFS();
	Edmond_Karp(const Digraph& G, uint s, uint t);
};

float Edmond_Karp::BFS() {
	std::vector<float> flow(R.V(), FLT_MAX);
	std::queue<uint> Q;
	fill(std::begin(visit), std::end(visit), false);
	visit[s] = true; path[s] = s; Q.push(s);
	while (!Q.empty()) {
		auto v = Q.front(); Q.pop();
		for (const auto& f : R.adj[v])
			if (!visit[f.first] && f.second > 0.0f) {
				visit[f.first] = true; path[f.first] = v;
				flow[f.first] = std::min(flow[v], f.second);
				if (f.first == t) return flow[t];
				Q.push(f.first);
			}
	}
	return 0.0f;
}

Edmond_Karp::Edmond_Karp(const Digraph& G, uint s, uint t)
		: visit(G.V(), false), path(G.V(), UINT_MAX),
			s{s}, t{t}, R{G}, C{G}, max_flow{0} {
	F.adj.resize(G.V());
	for (float flow; (flow = BFS()) > 0.0f; max_flow += flow)
		for (auto v1 = path[t], v2 = t; v1 != v2; v1 = path[v2 = v1]) {
			F.adj[v1][v2] = F.adj[v1][v2] + flow;
			F.adj[v2][v1] = -F.adj[v1][v2];
			R.adj[v1][v2] = C.adj[v1][v2] - F.adj[v1][v2];
			R.adj[v2][v1] = C.adj[v2][v1] - F.adj[v2][v1];
		}
	for (uint v = 0; v < G.V(); ++v)
		if (visit[v])
			for (const auto& e : G.adj[v])
				if (!visit[e.first])
					cuts.emplace_back(v, e.first, e.second);
}

int main() {return 0;}
