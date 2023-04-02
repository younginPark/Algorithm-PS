from collections import deque
arr = []
dy = [-1, 0, 1, 0]
dx = [0, -1, 0, 1]
n = 0
m = 0
q = deque()
answer = 1000001

def bfs():
    global arr, n, m, q, answer
    while q:
        front = q.popleft()
        if front[0] == n-1 and front[1] == m-1:
            answer = min(answer, front[3])
        for i in range(4):
            if 0 <= front[0]+dy[i] and front[0]+dy[i] < n and 0 <= front[1]+dx[i] and front[1]+dx[i] < m:
                if arr[front[0]+dy[i]][front[1]+dx[i]] == 0:
                    q.append([front[0]+dy[i], front[1]+dx[i], front[2], front[3]+1])
                elif arr[front[0]+dy[i]][front[1]+dx[i]] == 1:
                    if front[2] > 0:
                        continue
                    else:
                        q.append([front[0]+dy[i], front[1]+dx[i], 1, front[3]+1])

def main():
    global arr, n, m, q, answer
    n, m = map(int, input().split())
    arr = [[0 for i in range(m)] for j in range(n)]
    for i in range(n):
        tmp = input()
        for j in range(m):
            arr[i][j] = int(tmp[j])
    q.append([0, 0, 0, 0]) #행, 열, 부쉈는지, 몇번째로 온건지
    bfs()
    print(answer)


if __name__ == "__main__":
    main()