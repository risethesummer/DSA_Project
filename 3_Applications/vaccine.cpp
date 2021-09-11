#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Data {
	int s, f, id;
	int time() {
		return f - s + 1;
	}
};

bool cmp1(Data& u, Data& v) { return u.s < v.s; }
bool cmp2(Data& u, Data& v) { return u.f < v.f; }

int main() {
	vector<Data> S, F;
	
	cout << "Enter lab schedules (begin - end time, 0 to exit)\n";
	for (int cnt = 0;; ++cnt) {
		cout << " - (s, f): ";
		int s, f;
		cin >> s;
		if (s < 1) break;
		cin >> f;
		S.push_back({ s, f , cnt});
		F.push_back({ s, f , cnt});
	}

	//Init
	sort(S.begin(), S.end(), cmp1);
	sort(F.begin(), F.end(), cmp2);
	int n = S.size(), Result = -1;

	int* process1 = new int[n]; 
	int* process2 = new int[n];
	for (int i = 0; i < n; ++i) process1[i] = process2[i] = -1;

	//Find first process of fixed second process
	for (int i = 0, j = 0, tmp = -1; i < n; ++i) {
		for (; j < n && F[j].f < S[i].s; ++j)
			if (tmp == -1 || F[tmp].time() < F[j].time())
				tmp = j;
		process1[S[i].id] = tmp;
	}

	//Find second process of fixed third process
	for (int i = 0, j = 0, tmp = -1; i < n; ++i) {
		for (; j < n && F[j].f < S[i].s; ++j) {
			if (process1[F[j].id] == -1) continue;

			if (tmp == -1) tmp = (process1[F[j].id] != -1 ? j : -1);
			else {
				int total_time_tmp = F[process1[F[tmp].id]].time() + F[tmp].time();
				int total_time_j = F[process1[F[j].id]].time() + F[j].time();

				if (total_time_tmp < total_time_j)
					tmp = j;
			}
		}
		
		process2[S[i].id] = tmp;
		if (Result == -1) Result = (tmp != -1 ? i : -1);
		else {
			int total_time_tmp = F[process1[F[process2[S[Result].id]].id]].time() + F[process2[S[Result].id]].time() + S[Result].time();
			int total_time_i = F[process1[F[process2[S[i].id]].id]].time() + F[process2[S[i].id]].time() + S[i].time();

			if (total_time_tmp < total_time_i)
				Result = i;
		}
	}

	if (Result == -1) cout << "Unable to schedule!\n";
	else {
		cout << "Schedule:\n";
		cout << " - P1: " << F[process1[F[process2[S[Result].id]].id]].s << " " << F[process1[F[process2[S[Result].id]].id]].f << "\n";
		cout << " - P2: " << F[process2[S[Result].id]].s << " " << F[process2[S[Result].id]].f << "\n";
		cout << " - P3: " << S[Result].s << " " << S[Result].f << "\n";
	}

	delete[] process1;
	delete[] process2;
	return 0;
}
