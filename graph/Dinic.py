from collections import deque
import sys
import functools
si = sys.stdin.readline
wr = sys.stdout.write

n, m = map(int, si().split())


class Edge(object):
    def __init__(self, idx, c):
        self.idx = idx  # to-index
        self.c = c  # capacity


class Dinic(object):
    def __init__(self, N: int):
        self.N = N
        self.source = 0
        self.sink = N - 1
        self.visitNum = 0
        self.edges = []
        self.graph = [[] for _ in range(N)]
        self.level = [0 for _ in range(N)]

    def addEdge(self, x: int, y: int, c: int):
        self.graph[x].append(len(self.edges))
        self.edges.append(Edge(y, c))

        self.graph[y].append(len(self.edges))
        self.edges.append(Edge(x, 0))

    def solve(self):
        flow = 0
        while (self._bfs()):
            while (True):
                res = self._dfs(self.source, 1e6)
                if res == 0:
                    break
                flow += res
        return flow

    def _bfs(self):
        self.level = [-1 for _ in range(self.N)]
        Q = deque()
        Q.append(self.source)
        self.level[self.source] = 0
        while (Q):
            x = Q.popleft()
            for eIdx in self.graph[x]:
                y, c = self.edges[eIdx].idx, self.edges[eIdx].c
                if self.level[y] != -1 or c == 0:
                    continue
                Q.append(y)
                self.level[y] = self.level[x] + 1
        return self.level[self.sink] != -1

    def _dfs(self, cur, cap):
        if cur == self.sink:
            return cap

        for eIdx in self.graph[cur]:
            y, c = self.edges[eIdx].idx, self.edges[eIdx].c
            if c == 0 or self.level[y] != self.level[cur] + 1:
                continue
            _cap = self._dfs(y, min(cap, c))
            if _cap == 0:
                continue
            self.edges[eIdx].c -= _cap
            self.edges[eIdx ^ 1].c += _cap
            return _cap
        return 0


dinic = Dinic(2 + n + m)
for i in range(1, n + 1):
    Y = list(map(int, si().split()))
    for y in Y[1:]:
        dinic.addEdge(i, n + y, 1)

for i in range(1, n + 1):
    dinic.addEdge(0, i, 1)

for i in range(n + 1, n + m + 1):
    dinic.addEdge(i, n + m + 1, 1)


print(dinic.solve())
