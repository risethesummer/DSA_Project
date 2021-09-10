#include <iostream>

using namespace std;

class Queue {
	int l, r;
	int* data;

public:
	Queue(int size) {
		l = 1;
		r = 0;
		data = new int[size + 5];
	}
	~Queue() {
		delete[] data;
	}

	bool empty() {
		return l > r;
	}

	int size() {
		return r - l + 1;
	}

	int top() {
		return data[l];
	}

	void pop() {
		l++;
	}

	void push(int value) {
		data[++r] = value;
	}
};

int main() {

	int n, M, Result = 0;
	int* power = nullptr;

	cout << "Enter number of students: ";
	cin >> n;
	power = new int[n + 1];
	power[0] = 0;
	Queue que(n);

	cout << "Enter the maximum power of a continuous sequence of students: ";
	cin >> M;

	for (int i = 1; i <= n; ++i) {
		cout << "Power of student " << i << ": ";
		cin >> power[i];
		power[i] += power[i - 1];
	}

	
	for (int i = n; i > 0; --i) {
		que.push(i);

		while (!que.empty() && power[que.top()] - power[i - 1] > M)
			que.pop();
		Result += que.size();
	}

	cout << "Number of a continuous sequence of students: " << Result;

	delete[] power;
	return 0;
}
