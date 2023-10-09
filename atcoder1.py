from collections import deque
def bfs():
    global answer, q, m
    while q:
        front = q.popleft()
        if front[0] == m:
            answer = front[1]
            break
        if front[0]*2 < m+2 and front[1]+1 < dp[front[0]*2] and visited[front[0]*2] == False:
            dp[front[0]*2] = front[1]+1
            visited[front[0]*2] = True
            q.append([front[0]*2, front[1]+1])
        if front[0]+1 < m+2 and front[1]+1 < dp[front[0]+1] and visited[front[0]+1] == False:
            dp[front[0]+1] = front[1]+1
            visited[front[0]+1] = True
            q.append([front[0]+1, front[1]+1])
        if front[0]-1 >= 0 and front[1]+1 < dp[front[0]-1 and visited[front[0]-1] == False]:
            dp[front[0]-1] = front[1]+1
            visited[front[0]-1] = True
            q.append([front[0]-1, front[1]+1])
n, m = map(int,input().split())
q = deque()
answer = 0
if n == m:
    print(0)
else:
    dp = [123456789 for i in range(m+3)]
    visited = [False for i in range(m+3)]
    dp[n] = 0
    visited[n] = True
    q.append([n, 0])
    bfs()
    print(answer)