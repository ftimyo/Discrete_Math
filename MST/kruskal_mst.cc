#include <map>
#include <vector>
#include <algorithm>
struct Edge {
	int v, w; float d;
};

class Kruskal {
 public:
	std::map<int, int> group;
	std::vector<Edge> mst;
	int find(int v);
	Kruskal(std::vector<Edge>& E);
};

int Kruskal::find(int v) {
	if (__builtin_expect(group.find(v) == end(group), false)) group[v] = v;
	return v == group[v] ? v : group[v] = find(v);
}

Kruskal::Kruskal(std::vector<Edge>& E) {
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
