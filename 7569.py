from collections import deque
n = 0
m = 0
h = 0
arr = []
q = deque()
answer = 0
dy = [-1, 0, 1, 0]
dx = [0, 1, 0, -1]

def bfs():
    global n, m, h, arr, q, answer, dy, dx
    while q:
        front = q.popleft()
        for i in range(4):
            if 0 <= front[1]+dy[i] and front[1]+dy[i] < n and 0 <= front[2]+dx[i] and front[2]+dx[i] < m:
                if arr[front[0]][front[1]+dy[i]][front[2]+dx[i]] == 0:
                    arr[front[0]][front[1]+dy[i]][front[2]+dx[i]] = 1
                    next = [front[0], front[1]+dy[i], front[2]+dx[i], front[3]+1]
                    answer = max(answer, front[3]+1)
                    q.append(next)
        if 0 <= front[0]-1 and front[0]-1 < h:
            if arr[front[0]-1][front[1]][front[2]] == 0:
                arr[front[0]-1][front[1]][front[2]] = 1
                next = [front[0]-1, front[1], front[2], front[3]+1]
                answer = max(answer, front[3]+1)
                q.append(next)
        if 0 <= front[0]+1 and front[0]+1 < h:
            if arr[front[0]+1][front[1]][front[2]] == 0:
                arr[front[0]+1][front[1]][front[2]] = 1
                next = [front[0]+1, front[1], front[2], front[3]+1]
                answer = max(answer, front[3]+1)
                q.append(next)

def main():
    global n, m, h, arr, q, answer
    check = 0
    m, n, h = map(int, input().split())
    arr = [[ [] for i in range(n)] for j in range(h)]
    for i in range(h):
        for j in range(n):
                arr[i][j] = (list(map(int, input().split())))
                for k in range(m):
                    if arr[i][j][k] == 1:
                        q.append([i, j, k, 0])
                    elif arr[i][j][k] == 0:
                        check = 1
    if check == 0:
        print(0)
        return
    else:  
        bfs()
        for i in range(h):
            for j in range(n):
                for k in range(m):
                    if arr[i][j][k] == 0:
                        print(-1)
                        return
        print(answer)

if __name__ == "__main__":
    main()