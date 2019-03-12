#include <fstream>
#include <list>
#include <queue>
#include <iostream>
using namespace std;
ifstream f("in.txt");
ofstream g("out.txt");
int times;
int status[100];
int dt[100];
int low[100];
int tata[100];
int crit[100];
list<int> L[100];
list<pair<int, int>> E;
list<int> S;
int dfs(int x) {
	int nrc = 0;
	times++;
	dt[x] = low[x] = times;
	status[x] = 1;
	S.push_front(x);
	for (int y : L[x]) {
		if (status[y] == 0) {
			nrc++;
			tata[y] = x;
			dfs(y);
			low[x] = min(low[x], low[y]);
			if (dt[x] <= low[y]) {
				crit[x] = 1;
			}
			if (dt[x] < low[y]) {
				E.push_back(make_pair(x, y));
			}
		}
		if (status[y] == 1) {
			if (y != tata[x]) {
				low[x] = min(low[x], dt[y]);
			}
		}
	}
	int k;
	if (crit[x]) {
		do {
			k = *S.begin();
			S.pop_front();
			g << k << " ";
		} while (k != x);
		g << "\n";
	}
	status[x] = 2;
	return nrc;
}
int main() {
	int n;
	int m;
	int i;
	int x;
	int y;
	f >> n;
	f >> m;
	for (i = 0; i < m; i++) {
		f >> x;
		f >> y;
		L[x].push_back(y);
		L[y].push_back(x);
	}
	int st;
	cin >> st;
	if (dfs(st) > 1)
		crit[st] = 1;
	else
		crit[st] = 0;
	for (i = 1; i <= n; i++) {
		if (crit[i] == 1)
			g << i << " ";
	}
	g << "\n";
	for (pair<int, int> p : E)
		g << p.first << "-" << p.second << "\n";
	return 0;
}