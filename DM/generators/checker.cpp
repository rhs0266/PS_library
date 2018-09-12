#include <stdio.h>
#include <algorithm>
#define FOR(i,n,m) for (int i=(n);i<=(m);i++)
FILE *in = stdin, *out = stdout;
using namespace std;
int n, m;
int a[1005][1005];
int dy[1005][1005];
void input() {
	fscanf(in, "%d %d", &n, &m);
	FOR(i, 1, n) FOR(j, 1, m) fscanf(in, "%d", &a[i][j]);
}
int dp(int x,int y){
	FOR(i, 1, n) FOR(j, 1, m) dy[i][j] = 0;
	FOR(i, x, n) FOR(j, y, m) {
		if (i == x && j == y) dy[i][j] = a[i][j];
		else if (i == x) dy[i][j] = dy[i][j - 1] + a[i][j];
		else if (j == y) dy[i][j] = dy[i - 1][j] + a[i][j];
		else dy[i][j] = max(dy[i][j - 1], dy[i - 1][j]) + a[i][j];
	}
	return dy[n][m];
}
int main() {
	input();
	double ans = 0.0;
	FOR(i, 1, n) FOR(j, 1, m) ans += dp(i, j);
	ans = ans / n / m;
	fprintf(out, "%.6lf", ans);
	return 0;
}
