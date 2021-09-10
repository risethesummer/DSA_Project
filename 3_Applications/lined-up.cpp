#include <iostream>

using namespace std;
const int maxHeight = 300; 

class IT {
	int data[4 * maxHeight + 5];

public:
	IT() {
		memset(data, 0, sizeof(int) * (4 * maxHeight + 5));
	}
	
	int get(int s, int f, int l, int r, int id) {
		if (l >  f || r <  s) return 0;
		if (l >= s && r <= f) return data[id];

		int mid = (l + r) >> 1;
		return get(s, f, l, mid, 2 * id) + get(s, f, mid + 1, r, 2 * id + 1);
	}

	void update(int x, int l, int r, int id) {
		if (l > x || r < x) return;
		if (l >= x && r <= x) { 
			data[id]++; return; 
		}

		int mid = (l + r) >> 1; 
		update(x, l, mid, 2 * id); 
		update(x, mid + 1, r, 2 * id + 1);
		data[id] = data[2 * id] + data[2 * id + 1];
	}
};

int main() {
	int n, *height = nullptr;
	IT tree;

	cout << "Enter number of people: ";
	cin >> n;
	height = new int[n];


	cout << "Enter height of people (person 0 is first person, max Height: " << maxHeight << "):\n";
	for (int i = 0; i < n; ++i)
		cin >> height[i];


	cout << "The number of people standing in front of P is higher than P.\n";
	for (int i = 0; i < n; ++i) {
		cout << i + 1 << ": " << tree.get(height[i] + 1, maxHeight, 1, maxHeight, 1) << "\n";

		tree.update(height[i], 1, maxHeight, 1);
	}


	delete[] height;
	return 0;
}
