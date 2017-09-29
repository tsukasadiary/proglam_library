#include "SaffixArray.hpp"
#include "Trie.hpp"
#include "RollingHash.hpp"
#include "LongestCommonPrefixArray.hpp"
#include "KMP.hpp"

int main() {
	string str;
	getline(cin, str);
	
	SaffixArray sa(str);
	sa.dump(cout);
}
