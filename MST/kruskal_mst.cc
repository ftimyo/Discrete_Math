/*Kruskal algorithm using Weighted Quick Union Find*/

#ifdef TEST
#include <cstdio>
#endif

#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
using uint = unsigned;
struct Edge {
	uint v, w; float d;
};

class Kruskal {
 public:
	std::vector<int> sz;
	std::vector<uint> vs;
	std::vector<Edge> mst;
	uint root(uint v);
	void union_pair(uint v, uint w);
	Kruskal(std::vector<Edge>& E, std::size_t N);
};

void Kruskal::union_pair(uint v, uint w) {
	auto i = root(v);
	auto j = root(w);
	if (i == j) return;
	if (sz[i] < sz[j]) {vs[i] = j; sz[j] += sz[i];}
	else {vs[j] = i; sz[i] += sz[j];}
}

uint Kruskal::root(uint v) {
	return v == vs[v] ? v : vs[v] = root(vs[v]);
}

/*
uint Kruskal::root(uint v) {
	while(v != vs[v]) {
		vs[v] = vs[vs[v]];
		v = vs[v];
	}
	return v;
}
*/

Kruskal::Kruskal(std::vector<Edge>& E, std::size_t N)
		: sz(N, 1),
			vs(N, 0) {


	std::iota(std::begin(vs), std::end(vs), 0);

	auto weight_cmp = [] (const auto& e1, const auto& e2) {
		return e1.d < e2.d;};
	std::sort(begin(E), end(E), weight_cmp);

	for (auto e : E) {
		if (root(e.v) == root(e.w)) continue;
		union_pair(e.v, e.w);
		mst.push_back(e);
	}
}

int main() {
#ifdef TEST
	std::vector<Edge> e_set{{0,3,3},{3,6,5},{3,6,6},{0,5,1},{5,0,2},{6,7,3},
		{5,7,1},{7,8,4},{1,0,5},{5,8,2},{5,4,0},{1,4,-3},{4,8,5},{8,8,2},{4,2,-1}};

	printf("input Edge set\n");
	for (const auto& e : e_set) {
		printf("%u->%u : %f\n", e.v, e.w, e.d);
	}

	Kruskal k(e_set, 9);

	printf("output Edge set\n");
	for (const auto& e : k.mst) {
		printf("%u->%u : %f\n", e.v, e.w, e.d);
	}
#endif
	return 0;
}
