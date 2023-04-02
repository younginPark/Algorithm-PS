import sys
from collections import deque

arr = [[0 for i in range(1001)] for i in range(1001)]
visit = [0 for i in range(1001)]
n = 0
m = 0
q = deque()

def bfs():
    global arr, visit, n, m, q
    while len(q) > 0:
        num = q.popleft()
        for i in range(1, n+1):
            if arr[num][i] == 1 and visit[i] == 0:
                visit[i] = 1
                q.append(i)

def main():
    global arr, visit, n, m, q
    n, m=map(int,sys.stdin.readline().split())
    ans = 0
    for i in range(m):
        tmp1, tmp2 = map(int, input().split())
        arr[tmp1][tmp2] = 1
        arr[tmp2][tmp1] = 1
    for i in range(1, n+1):
        if visit[i] == 0:
            visit[i] = 1
            q.append(i)
            bfs()
            ans += 1
    print(ans)
if __name__ == "__main__":
    main()