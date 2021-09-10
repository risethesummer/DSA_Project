#include <iostream>
#include <string>
#include <map>

#define long long long
#define Base 5			//A:1, G:2, C:3, T:4

using namespace std;
const int M = 1e9 + 7;

int func(char c) {
	return (c == 'A' ? 1 : (c == 'G' ? 2 : (c == 'C' ? 3 : (c == 'T' ? 4 : 0))));
}

class Hash_DNA {
public:
	int m_size;
	int* hash = nullptr;
	int* p = nullptr;

public:
	int size() {
		return m_size;
	}
	

	Hash_DNA(string& str) {
		m_size = str.size();
		hash = new int[str.size() + 5];
		p = new int[str.size() + 5];
		p[0] = 1;
		hash[0] = func(str[0]);

		for (int i = 1; i < m_size; ++i) {
			p[i] = 1LL * p[i - 1] * Base % M;
			hash[i] = (1LL * hash[i - 1] * Base + func(str[i])) % M;
		}
	}

	~Hash_DNA() {
		delete[] hash;
	}

	int get(int l, int r) {
		if (l == 0) return hash[r];
		return (1LL * M * M + hash[r] - 1LL * hash[l - 1] * p[r - l + 1]) % M;
	}
};

bool check(Hash_DNA& h1, Hash_DNA& h2, int len) {
	map <int, int> mp;
	for (int i = 0; i + len - 1 < h1.size(); ++i) {
		int hash = h1.get(i, i + len - 1);
		mp[hash] = i;
	}

	for (int i = 0; i + len - 1 < h2.size(); ++i) {
		int hash = h2.get(i, i + len - 1);
		if (mp.find(hash) != mp.end()) return true;
	}

	return false;
}


int main() {
	string A1, A2;
	cout << "First DNA: "; cin >> A1;
	cout << "Second DNA: "; cin >> A2;

	for (char &c:A1)
		if (func(c) == 0) {
			cout << "First DNA wrong!\n";
			return 0;
		}
	for (char& c : A2)
		if (func(c) == 0) {
			cout << "Second DNA wrong!\n";
			return 0;
		}
		

	Hash_DNA h1(A1);
	Hash_DNA h2(A2);

	int l = 0, r = h2.size() + 1;
	while (r > l + 1) {
		int mid = (l + r) >> 1;
		if (check(h1, h2, mid)) l = mid;
		else r = mid;
	}

	printf("Longest length: %d\n", l);
	return 0;
}
