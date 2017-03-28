#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "../template.hpp"
#endif

template< typename T >
class SetR {
private:
	unsigned int xor128() {
		static unsigned int x = 123456789, y = 362436069, z = 521288629, w = 88675123;
		unsigned int t = (x ^ (x << 11));
		x = y; y = z; z = w;
		return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
	}
	
	struct Node {
		T val;
		int pri, lch, rch, cnt; // priority, left child, right child, count
		Node(T __val__, int __pri__) : val(__val__), pri(__pri__), cnt(1) { lch = rch = -1; }
	};
	
	int root_id;
	vector< Node > node_pool;
	
private:
	int count(int node_id) { return node_id >= 0 ? node_pool[node_id].cnt : 0; }
	
	int update(int node_id) {
		if (node_id == -1) return node_id;
		Node& node = node_pool[node_id];
		node.cnt = count(node.lch) + count(node.rch) + 1;
		return node_id;
	}
	
	int merge(int lft_node_id, int rgt_node_id) {
		if (lft_node_id == -1 || rgt_node_id == -1) return lft_node_id >= 0 ? lft_node_id : rgt_node_id;
		
		Node& lft_node = node_pool[lft_node_id];
		Node& rgt_node = node_pool[rgt_node_id];
		
		if (lft_node.pri > rgt_node.pri) {
			lft_node.rch = merge(lft_node.rch, rgt_node_id);
			return update(lft_node_id);
		} else {
			rgt_node.lch = merge(lft_node_id, rgt_node.lch);
			return update(rgt_node_id);
		}
	}
	
	// pii(lft_root, rgt_root)
	pii split(int node_id, int k) {
		if (node_id == -1) return pii(-1, -1);
		
		Node& node = node_pool[node_id];
		if (k <= count(node.lch)) {
			pii s = split(node.lch, k);
			node.lch = s.second;
			return pii(s.first, update(node_id));
		} else {
			pii s = split(node.rch, k - count(node.lch) - 1);
			node.rch = s.first;
			return pii(update(node_id), s.second);
		}
	}
	
	int insert(int node_id, int k, T val, int pri) {
		pii s = split(node_id, k);
		int new_node_id = node_pool.size();
		node_pool.push_back(Node(val, pri));
		node_id = merge(s.first, new_node_id);
		node_id = merge(node_id, s.second);
		return update(node_id);
	}
	
	int erase(int node_id, int k) {
		pii s1 = split(node_id, k + 1);
		pii s2 = split(s1.first, k);
		node_id = merge(s2.first, s1.second);
		return update(node_id);
	}
	
	int range_erase(int node_id, int lft, int rgt) {
		pii s1 = split(node_id, rgt);
		pii s2 = split(s1.first, lft);
		node_id = merge(s2.first, s1.second);
		return update(node_id);
	}
	
	bool binary_search(int node_id, const T& val) {
		if (node_id == -1) return false;
		Node& node = node_pool[node_id];
		if (node.val > val) return binary_search(node.lch, val);
		if (node.val < val) return binary_search(node.rch, val);
		return true;
	}
	
	// pii(node_id, pos)
	pii lower_bound(int node_id, const T& val, int res_node, int pos) {
		if (node_id == -1) return pii(res_node, pos);		
		Node& node = node_pool[node_id];
		if (node.val < val) return lower_bound(node.rch, val, res_node, pos + count(node.lch) + 1);
		return lower_bound(node.lch, val, node_id, pos);
	}
	
	pii upper_bound(int node_id, const T& val, int res_node, int pos) {
		if (node_id == -1) return pii(res_node, pos);		
		Node& node = node_pool[node_id];
		if (node.val <= val) return upper_bound(node.rch, val, res_node, pos + count(node.lch) + 1);
		return upper_bound(node.lch, val, node_id, pos);
	}
	
	int find(int node_id, int k) {
		Node& node = node_pool[node_id];
		int c = count(node.lch);
		if (k < c) return find(node.lch, k);
		if (k > c) return find(node.rch, k - c - 1);
		return node_id;
	}
	
	void dump(int node_id, ostream& os) {
		if (node_id == -1) return;
		os << "(";
		Node& node = node_pool[node_id];
		dump(node.lch, os);
		os << node.val;
		dump(node.rch, os);
		os << ")";
	}
	
public:
	SetR() : root_id(-1) {}
	
	bool binary_search(T val) { return binary_search(root_id, val); }
	
	pii lower_bound(T val) { return lower_bound(root_id, val, root_id, 0); }
	
	pii upper_bound(T val) { return upper_bound(root_id, val, root_id, 0); }
	
	void insert_pos(int k, T val) { root_id = insert(root_id, k, val, xor128()); }
	
	void insert(T val) {
		pii p = lower_bound(val);
		if (p.first == -1 || node_pool[p.first].val != val) insert_pos(p.second, val);
	}
	
	void erase_pos(int k) { root_id = erase(root_id, k); }
	
	void erase_value(T val) {
		pii p = lower_bound(val);
		if (p.first >= 0 && node_pool[p.first].val == val) erase_pos(p.second);
	}
	
	void range_erase(int lft, int rgt) { root_id = range_erase(root_id, lft, rgt); }
	
	int find(int k) { return find(root_id, k); }
	
	void dump(ostream& os) { dump(root_id, os); os << endl; }
	
	T getValue(int node_id) { return node_pool[node_id].val; }
};