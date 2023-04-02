n, m = map(int, input().split())
visit = [False for i in range(n+1)]
arr = [0 for i in range(m)]
def dfs(now, cnt):
    if cnt == m:
        for i in range(m):
            print(arr[i], end=" ")
        print()
        return
    for i in range(1, n+1):
            arr[cnt] = i
            dfs(i, cnt+1)

dfs(1, 0)