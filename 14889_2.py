import sys
sys.setrecursionlimit(10001)
def dfs(idx, cnt):
    global answer
    if cnt == n // 2:
        startSum = 0
        linkSum = 0
        for i in range(n-1):
            for j in range(i+1, n):
                if visited[i] == True and visited[j] == True:
                    startSum += arr[i][j] + arr[j][i]
                elif visited[i] == False and visited[j] == False:
                    linkSum += arr[i][j] + arr[j][i]
        answer = min(answer, abs(startSum-linkSum))
        return
    for i in range(idx, n):
        if visited[i] == False:
            visited[i] = True
            dfs(i, cnt+1)
            visited[i] = False

n = int(input())
arr = []
visited = [False for i in range(n)]
for i in range(n):
    arr.append(list(map(int, input().split())))
answer = 987654321
dfs(0, 0)
print(answer)