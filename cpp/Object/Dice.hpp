#include "../template.hpp"

enum DICE { TOP, BOTTOM, FRONT, BACK, LEFT, RIGHT, END };
enum ROLL { NORTH_R, SOUTH_R, EAST_R, WEST_R, LEFT_R, RIGHT_R, END_R };
	
const int right_by_tf[6][6] = {
	{ -1, 3, 5, 2, 4, -1 },
	{ 4, -1, 1, 6, -1, 3 },
	{ 2, 6, -1, -1, 1, 5 },
	{ 5, 1, -1, -1, 6, 2 },
	{ 3, -1, 6, 1, -1, 4 },
	{ -1, 4, 2, 5, 3, -1 }
};

const enum DICE rolls[6][4] = {// <-<-<-<-
	{ TOP, FRONT, BOTTOM, BACK }, // north
	{ BOTTOM, FRONT, TOP, BACK }, // south
	{ TOP, LEFT, BOTTOM, RIGHT }, // east
	{ TOP, RIGHT, BOTTOM, LEFT }, // west
	{ RIGHT, BACK, LEFT, FRONT }, // left
	{ LEFT, BACK, RIGHT, FRONT }  // right
};

class Dice {
private:
	int dice[6];
	
public:
	Dice() {
		dice[TOP] = 1; dice[BOTTOM] = 6;
		dice[FRONT] = 2; dice[BACK] = 5;
		dice[RIGHT] = 3; dice[LEFT] = 4;
	}
	
	Dice(int top, int front) {
		dice[TOP] = top; dice[BOTTOM] = 7 - top;
		dice[FRONT] = front; dice[BACK] = 7 - front;
		dice[RIGHT] = right_by_tf[top - 1][front - 1]; dice[LEFT] = 7 - dice[RIGHT];
	}
	
	void roll_to(enum ROLL ro) {
		int tmp = dice[ rolls[ro][0] ];
		for_(i,0,3) dice[ rolls[ro][i] ] = dice[ rolls[ro][i + 1] ];
		dice[ rolls[ro][3] ] = tmp;
	}
	
	vector< Dice > get_all_state() {
		vector< Dice > res;
		
		for_(k,0,6) {
			for_(i,0,4) {
				res.push_back(*this);
				roll_to(LEFT_R);
			}
			
			if (k % 2) roll_to(NORTH_R);
			else roll_to(EAST_R);
		}
		
		return res;
	}
	
	int at(enum DICE d) const { return dice[d]; }
	int at(int i) const { return dice[i]; }
	
	bool operator == (const Dice& a) {
		for_(i,TOP,END) if (this->at(i) != a.at(i)) return false;
		return true;
	}
};
