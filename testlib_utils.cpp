#include "testlib.h"
#include <iostream>
#include <time.h>
#include <assert.h>
#include <unordered_map>

using namespace std;

int n, m, K, L, portion;

/*
selecet_distinct := select distinct <num> numbers in [<low>, <high>].
*/
vector<int> select_distinct(int low, int high, int num) {
    assert(num <= high - low + 1);
    unordered_map<int, int> mem;
    vector<int> res;
    int s = low;
    for (int i = 1; i <= num; i++) {
        int trg = rnd.next(s, high);

        if (mem.find(s) == mem.end()) mem[s] = s;
        if (mem.find(trg) == mem.end()) mem[trg] = trg;
        swap(mem[s], mem[trg]);
        res.push_back(mem[s]);

        s++;
    }
    return res;
}

/*
distribute := distribute <pie> to the <num> people. each person has at least one pie.
*/
vector<int> distribute(int pie, int num) {
    vector<int> res = select_distinct(1, pie - 1, num - 1);
    res.push_back(pie);

    sort(res.begin(), res.end());

    for (int i = num - 1; i >= 1; i--) res[i] -= res[i - 1];
    return res;
}

/*
gen_names := generate names which length between <min_len> and <max_len>.
*/
vector<string> gen_names(int n, int min_len, int max_len, bool redundant) {
    vector<string> res;
    for (int i=0;i<n;i++){
        int len = rnd.next(min_len, max_len);
        string name = "";
        for (int j=0;j<len;j++){
            name += char('a' + rnd.next(0, 25));
        }
        
        bool flag = true;
        if (!redundant) {
            for (int j=0;j<i;j++){
                if (res[j] == name) flag = false;
            }
        }
        if (!flag){
            i--;
            continue;
        }
        res.push_back(name);
    }
    return res;
}

typedef long long int T;
#define vp vector<Point2D>

struct Point2D {
    T x, y, dis;

    Point2D() {};

    Point2D(T _x, T _y) : x(_x), y(_y) {};

    bool operator()(Point2D A, Point2D B) {
        if (A.y != B.y) return A.y < B.y;
        return A.x < B.x;
    }
};

int ccw(Point2D a, Point2D b, Point2D c) {
    T t = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (t > 0) return 1;
    if (t < 0) return -1;
    return 0;
}

struct SortByCCW {
private:
    vp a, output;
    int n;

    void calc() {
        sort(a.begin(), a.end(), Point2D());
        Point2D pad = a[0];
        for (int i = 0; i < n; i++) {
            a[i].x -= pad.x;
            a[i].y -= pad.y;
            a[i].dis = a[i].x * a[i].x + a[i].y * a[i].y;
        }
        sort(a.begin(), a.end(), [](const Point2D &A, const Point2D &B) {
            int _ccw = ccw(Point2D(0, 0), A, B);
            if (_ccw != 0) return _ccw == 1;
            return A.dis < B.dis;
        });
        for (int i = 0; i < n; i++) {
            a[i].x += pad.x;
            a[i].y += pad.y;
        }
        output = a;
    }

public:
    SortByCCW() {};

    SortByCCW(vp _input) {
        a.clear();
        output.clear();
        a = _input;
        n = a.size();
        calc();
    }

    vp result() {
        return output;
    }
};

int taxi_dist(Point2D A, Point2D B) {
    return abs(A.x - B.x) + abs(A.y - B.y);
}

int euclidean_dist(Point2D A, Point2D B) {
    return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
}

void make_boundary(vector<vector<int>> &maze, Point2D A, Point2D B, vector<pair<int, int>> &dirs) {
    while (A.x != B.x || A.y != B.y) {
        maze[A.x][A.y] = 1;
        vector<int> cands;
        int cur_dist = taxi_dist(A, B);
        for (int i = 0; i < dirs.size(); i++) {
            Point2D C(A.x + dirs[i].first, A.y + dirs[i].second);
            if (C.x < 0 || C.y < 0 || C.x >= n || C.y >= m) continue;
            if (cur_dist >= taxi_dist(C, B)) cands.push_back(i);
        }
        shuffle(cands.begin(), cands.end());
        int dir = cands[0];
        A.x += dirs[dir].first;
        A.y += dirs[dir].second;
    }
    maze[A.x][A.y] = 1;
}

/*
generate_map := create <K> closed areas. each area's side is at most <L> length.
*/
vector<vector<int>> generate_map(int n, int m, int K, int L) {
    vector<vector<int>> a(n, vector<int>(m, 0));

    for (int rep = 1; rep <= K; rep++) {
        int x1 = rnd.next(1, n);
        int y1 = rnd.next(1, m);
        int x2 = min(x1 + L, n);
        int y2 = min(y1 + L, m);
        x1--, y1--, x2--, y2--;

        int cnt_points = rnd.next(3, 8);
        vector<Point2D> points;
        for (int i = 0; i < cnt_points; i++) {
            int x = rnd.next(x1, x2);
            int y = rnd.next(y1, y2);
            points.push_back({x, y});
        }

        SortByCCW ch(points);
        points = ch.result();
        vector<pair<int, int>> dirs({{-1, -1},
                                     {-1, 0},
                                     {-1, 1},
                                     {0,  -1},
                                     {0,  1},
                                     {1,  -1},
                                     {1,  0},
                                     {1,  1}});
        points.push_back(points[0]);
        for (int i = 0; i + 1 < points.size(); i++) {
            make_boundary(a, points[i], points[i + 1], dirs);
        }
    }
    return a;
}


pair<int, int> Find(int x, int y, vector<vector<pair<int, int>>> &par) {
    if (x == par[x][y].first && y == par[x][y].second) return {x, y};
    par[x][y] = Find(par[x][y].first, par[x][y].second, par);
    return par[x][y];
}

bool Union(int x1, int y1, int x2, int y2, vector<vector<pair<int, int>>> &par) {
    pair<int, int> p1 = Find(x1, y1, par);
    pair<int, int> p2 = Find(x2, y2, par);
    if (p1 == p2) return false;
    par[p1.first][p1.second] = p2;
    return true;
}

/*
generate_maze := generate a maze.
*/

struct Z {
    int x1, y1, x2, y2;
};

vector<vector<int>> generate_maze(int n, int m) {
    vector<vector<int>> res(n, vector<int>(m));
    vector<vector<pair<int, int>>> par(n, vector<pair<int, int>>(m));

    vector<int> X, Y;
    for (int i = 0; i < n; i += 2) {
        if (i == n - 2) i = n - 1;
        if (i % 2 == n % 2 && rnd.next(0, 10) == 0) i++;
        X.push_back(i);
    }
    for (int i = 0; i < m; i += 2) {
        if (i == m - 2) i = m - 1;
        if (i % 2 == m % 2 && rnd.next(0, 10) == 0) i++;
        Y.push_back(i);
    }

    int xs = X.size(), ys = Y.size();

    vector<int> sel = select_distinct(1, xs * ys - 2, xs * ys - 2);
    sel.push_back(0);
    sel.push_back(xs * ys - 1);

    vector<pair<int, int>> points, sel_points;
    for (int i = 0; i < xs; i++) {
        for (int j = 0; j < ys; j++) {
            points.push_back({X[i], Y[j]});
        }
    }
    for (int i: sel) sel_points.push_back(points[i]);

    for (auto p: sel_points) {
        res[p.first][p.second] = 1;
    }

    vector<Z> edges;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (res[i][j] == 0) continue;
            for (int i2 = i + 1; i2 < n; i2++) {
                if (res[i2][j] == 1) {
                    edges.push_back({i, j, i2, j});
                    break;
                }
            }
            for (int j2 = j + 1; j2 < m; j2++) {
                if (res[i][j2] == 1) {
                    edges.push_back({i, j, i, j2});
                    break;
                }
            }
        }
    }

    shuffle(edges.begin(), edges.end());

    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) par[i][j] = {i, j};

    for (Z e: edges) {
        int x1 = e.x1, y1 = e.y1, x2 = e.x2, y2 = e.y2;
        if (Union(x1, y1, x2, y2, par)) {
            for (int x = min(x1, x2); x <= max(x1, x2); x++) {
                for (int y = min(y1, y2); y <= max(y1, y2); y++) {
                    res[x][y] = 1;
                }
            }
        }
    }

    return res;
}

void make(){
}

int main(int argc, char* argv[])
{
	registerGen(argc, argv, 1);
    
	make();
	return 0;
}
