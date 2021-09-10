#include <iostream>
#include <string>
#include <map>
#define long long long

using namespace std;

class stack {
public:
	int m_top;
	int* data = nullptr;

public:
	stack(int size) {
		m_top = -1;
		data = new int[size];
	}

	~stack() {
		delete data;
	}

	bool empty() {
		return m_top == -1;
	}

	int top() {
		return data[m_top];
	}

	void clear() {
		m_top = -1;
	}

	void pop() {
		m_top--;
	}

	void push(int value) {
		data[++m_top] = value;
	}
};


int main() {
	int n, * height = nullptr, * lenght = nullptr;

	cout << "The length of the fence: "; cin >> n;

	height = new int[n + 5];
	lenght = new int[n + 5];
	for (int i = 1; i <= n; ++i) {
		cout << "Height of plank " << i << ": ";
		cin >> height[i];
	}

	long maxArea = 0;
	int l = 0, r = 0, h = 0;

	stack s(n);
	s.push(0);
	height[0] = -1;
	for (int i = 1; i <= n; ++i) {
		while (!s.empty() and height[s.top()] >= height[i]) s.pop();
		lenght[i] = s.top() + 1;
		s.push(i);
	}

	s.clear();
	s.push(n + 1);
	height[n + 1] = -1;
	for (int i = n; i >= 1; --i) {
		while (!s.empty() and height[s.top()] >= height[i]) s.pop();

		long plank_lenght = s.top() - lenght[i];
		if (maxArea < plank_lenght * height[i]) {
			maxArea = plank_lenght * height[i];
			l = lenght[i];
			r = s.top() - 1;
			h = height[i];
		}

		s.push(i);
	}

	cout << "The maximum area that can be retained is " << maxArea << "(m2)\n";
	cout << "From plank " << l << " to plank " << r << " with a height of " << h << "(m)\n";
	return 0;
}
