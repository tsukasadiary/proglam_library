#include "SaffixArray.hpp"

int main() {
	string str;
	getline(cin, str);
	
	SaffixArray sa(str);
	sa.dump(cout);
}
