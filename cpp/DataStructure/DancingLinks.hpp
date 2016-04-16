#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "../template.hpp"
#endif

// Dancing Links
template< typename DATA >
class DancingLinks {
private:
	struct Node {
		int r, c;
		DATA data;
		Node *lft, *rgt, *up, *dwn;
		Node() : r(-1), c(-1) {}
		Node(int _r_, int _c_, DATA _d_) : r(_r_), c(_c_), data(_d_) {}
	};
	
	int N, M;
	const Vec< Vec< DATA > >& mat;
	DATA zero;
	
	Node head;
	Vec< Node > row;
	Vec< Node > col;
	Vec< Node > cell;
	
private:
	void makeLinks() {
		row = Vec< Node >(N);		
		col = Vec< Node >(M);
		
		head.up = &row[N - 1]; row[N - 1].dwn = &head;
		head.dwn = &row[0]; row[0].up = &head;
		
		for_(r,0,N) row[r].lft = row[r].rgt = &row[r];
		
		for_(r,1,N) {
			row[r - 1].dwn = &row[r];
			row[r].up = &row[r - 1];
		}
		
		head.lft = &col[M - 1]; col[M - 1].rgt = &head;
		head.rgt = &col[0]; col[0].lft = &head;
		
		for_(c,0,M) col[c].up = col[c].dwn = &col[c];
		
		for_(c,1,M) {
			col[c - 1].rgt = &col[c];
			col[c].lft = &col[c - 1];
		}
		
		cell.clear();
		
		Vec< Node* > cur(M);
		for_(c,0,M) cur[c] = &col[c];
		
		int non_zero_cnt = 0;
		for_(r,0,N) for_(c,0,M) if (mat[r][c] != zero) ++non_zero_cnt;
		
		cell.assign(non_zero_cnt, Node());
		
		for_(r,0,N) {
			Node* p = &row[r];
			
			for_(c,0,M) {
				if (mat[r][c] != zero) {
					int i = --non_zero_cnt;
					cell[i] = Node(r, c, mat[r][c]);
					
					p->rgt = &cell[i];
					cell[i].lft = p;
					
					cell[i].rgt = &row[r];
					row[r].lft = &cell[i];
					
					cell[i].up = cur[c];
					cur[c]->dwn = &cell[i];
					
					col[c].up = &cell[i];
					cell[i].dwn = &col[c];
							
					p = cur[c] = &cell[i];
				}
			}
		}
	}
	
public:
	DancingLinks(const Vec< Vec< DATA > >& _mat_, DATA _zero_)
	: N(_mat_.size()), M(_mat_[0].size()), mat(_mat_), zero(_zero_) {
		makeLinks();
	}
	
	void deleteRow(int r) {
		Node* p = &row[r];
		
		do {
			(p->up)->dwn = p->dwn;
			(p->dwn)->up = p->up;
			p = p->rgt;
		} while (p != &row[r]);
	}
	
	void restoreRow(int r) {
		Node* p = &row[r];
		
		do {
			(p->up)->dwn = p;
			(p->dwn)->up = p;
			p = p->rgt;
		} while (p != &row[r]);
	}
	
	void deleteCol(int c) {
		Node* p = &col[c];
		
		do {
			(p->lft)->rgt = p->rgt;
			(p->rgt)->lft = p->lft;
			p = p->dwn;
		} while (p != &col[c]);
	}
	
	void restoreCol(int c) {
		Node* p = &col[c];
		
		do {
			(p->lft)->rgt = p;
			(p->rgt)->lft = p;
			p = p->dwn;
		} while (p != &col[c]);
	}
	
	Vec< Vec< DATA > > current() {
		Vec< Vec< DATA > > res(N, Vec< DATA >(M, zero));
		
		Node* p = &head;
		
		while (p->dwn != &head) {
			p = p->dwn;
			Node* q = p;
			
			while (q->rgt != p) {
				q = q->rgt;
				res[q->r][q->c] = q->data;
			}			
		}
		
		return res;
	}
};