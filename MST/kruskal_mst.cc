#include <map>
#include <vector>
#include <algorithm>
using uint = unsigned;
struct Edge {
	uint v, w; float d;
};

class Kruskal {
 public:
	std::map<uint, uint> group;
	std::vector<Edge> mst;
	uint find(uint v);
	Kruskal(const std::vector<Edge>& E);
};

uint Kruskal::find(uint v) {
	if (__builtin_expect(group.find(v) == end(group), false)) group[v] = v;
	return v == group[v] ? v : group[v] = find(v);
}

Kruskal::Kruskal(const std::vector<Edge>& E) {
	auto weight_cmp = [] (const auto& e1, const auto& e2) {
		return e1.d < e2.d;};
	std::sort(begin(E), end(E), weight_cmp);
	for (auto e : E) {
		if (find(e.v) == find(e.w)) continue;
		group[find(e.v)] = find(e.w);
		mst.push_back(e);
	}
}

int main() {return 0;}
