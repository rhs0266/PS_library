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
	for (int i = n; i >= 1; i--) for (int j = m; j >= 1;j--) fscanf(in, "%d", &a[i][j]);
}
void pro(){
	FOR(i, 1, n) FOR(j, 1, m) {
		if (i == 1 && j == 1) dy[i][j] = a[i][j];
		else if (i == 1) dy[i][j] = dy[i][j - 1] + a[i][j];
		else if (j == 1) dy[i][j] = dy[i - 1][j] + a[i][j];
		else dy[i][j] = max(dy[i - 1][j], dy[i][j - 1]) + a[i][j];
	}
	double ans = 0.0;
	FOR(i, 1, n) FOR(j, 1, m) ans += dy[i][j];
	ans = ans / n / m;
	fprintf(out, "%.6lf", ans);
}
int main() {
	input();
	pro();
	return 0;
}
