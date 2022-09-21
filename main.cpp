#include "testlib.h"
#include <iostream>
#include <time.h>
#include <assert.h>
#include <unordered_map>

using namespace std;

int n, m, K, L;

struct Z {
    int x1, y1, x2, y2;
};

vector<int> select_distinct(int low, int high, int num) {
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

vector<int> distribute(int pie, int num) {
    vector<int> res = select_distinct(1, pie - 1, num - 1);
    res.push_back(pie);

    sort(res.begin(), res.end());

    for (int i = num - 1; i >= 1; i--) res[i] -= res[i - 1];
    return res;
}


typedef long long int T;
#define vp vector<POINT>

struct POINT {
    T x, y, dis;

    POINT() {};
    POINT(T _x, T _y) : x(_x), y(_y) {};

    bool operator()(POINT A, POINT B) {
        if (A.y != B.y) return A.y < B.y;
        return A.x < B.x;
    }
};

int ccw(POINT a, POINT b, POINT c) {
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
        sort(a.begin(), a.end(), POINT());
        POINT pad = a[0];
        for (int i = 0; i < n; i++) {
            a[i].x -= pad.x;
            a[i].y -= pad.y;
            a[i].dis = a[i].x * a[i].x + a[i].y * a[i].y;
        }
        sort(a.begin(), a.end(), [](const POINT &A, const POINT &B) {
            int _ccw = ccw(POINT(0, 0), A, B);
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

int taxi_dist(POINT A, POINT B) {
    return abs(A.x - B.x) + abs(A.y - B.y);
}

int euclidean_dist(POINT A, POINT B) {
    return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
}

void make_boundary(vector<vector<int>> &maze, POINT A, POINT B, vector<pair<int, int>> &dirs) {
    while (A.x != B.x || A.y != B.y) {
        maze[A.x][A.y] = 1;
        vector<int> cands;
        int cur_dist = taxi_dist(A, B);
        for (int i = 0; i < dirs.size(); i++) {
            POINT C(A.x + dirs[i].first, A.y + dirs[i].second);
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

// K 개의 구역을 만들 것. 한 변의 길이 최대 L
vector<vector<int>> generate_map(int n, int m, int K, int L) {
    vector<vector<int>> a(n, vector<int>(m, 0));

    for (int rep = 1; rep <= K; rep++) {
        int x1 = rnd.next(1, n);
        int y1 = rnd.next(1, m);
        int x2 = min(x1 + L, n);
        int y2 = min(y1 + L, m);
        x1--, y1--, x2--, y2--;

        int cnt_points = rnd.next(3, 8);
        vector<POINT> points;
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

void make() {
    auto maze = generate_map(n, m, K, L);

    cout << n << " " << m << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << maze[i][j];
            if (j + 1 < m) cout << " ";
        }
        cout << "\n";
    }
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
//    n = atoi(argv[1]);
//    m = atoi(argv[2]);
//    E = atoi(argv[3]);
//    portion = atoi(argv[4]);
    n = 50, m = 50, K = 2, L = 30;
    make();
    return 0;
}