#include <iostream>
#include <vector>
#include <utility>
#define pii pair <int, int>

using namespace std;
const int maxn = 1e5 + 5, M = 1e9 + 7;

template <typename T>
T* Init(int size) {
	T* tmp = new T[size];
	memset(tmp, 0, sizeof(T) * size);
	return tmp;
}

// Global variables
vector<pii>* a, edge;
int n, m, K, L, * A, * B;
int cnt, * Num, * Lowc;
bool* fg;

void DFS(int u) {
	Num[u] = ++cnt; Lowc[u] = n + 1;
	for (pii& i : a[u]) {
		if (!fg[i.second]) {
			int v = i.first;
			
			//edge i.second and i.second^1 is 2 two-ways of 1 edge
			fg[i.second ^ 1] = 1; 
			
			if (Num[v])
				// tarjan algorithm
				Lowc[u] = min(Lowc[u], Num[v]);
			else {
				DFS(v);
				
				// tarjan algorithm
				Lowc[u] = min(Lowc[u], Lowc[v]);
				
				A[u] += A[v];
				B[u] += B[v];
				if (Lowc[v] >= Num[v])
					//bridge has been found
					if (!A[v] || A[v] == K || !B[v] || B[v] == L)
						edge.push_back({ u, v });
			}
		}
	}
}

void Tarjan() {
	//Init
	cnt = 0;
	fg = Init<bool>(2 * m + 5);
	Num = Init<int>(n + 5);
	Lowc = Init<int>(n + 5);

	DFS(1);

	//Release
	delete[] fg;
	delete[] Num;
	delete[] Lowc;
}

int main() {
	cout << "Enter the number of vertices (N): ";
	cin >> n;
	cout << "Enter the number of edges (M): ";
	cin >> m;

	//Init
	a = new vector<pii>[n + 5];
	A = Init<int>(n + 5);
	B = Init<int>(n + 5);
	
	//Input
	cout << "Enter service vertices A (1<= ai <= " << n << ", 0 to exit): ";
	while (1) {
		int a;
		cin >> a;
		if (a < 1 || a > n) break;
		K += (A[a] == 0);
		A[a] = 1;
	}
	cout << "Enter service vertices B (1<= bi <= " << n << ", 0 to exit): ";
	while (1) {
		int b;
		cin >> b;
		if (b < 1 || b > n) break;
		L += (B[b] == 0);
		B[b] = 1;
	}
	cnt = 0;
	for (int i = 1, u, v; i <= m; ++i) {
		cout << "Enter edge " << i << " (u, v): ";
		cin >> u >> v;
		a[u].push_back({ v, cnt++ });
		a[v].push_back({ u, cnt++ });
	}
	
	//Tarjan
	Tarjan();

	//Output
	cout << "Important connecting edges:\n";
	for (pii& i : edge) {
		cout << '(' << i.first << ',' << i.second << ")\n";
	}

	//Release
	delete[] a;
	delete[] A;
	delete[] B;
	return 0;
}
