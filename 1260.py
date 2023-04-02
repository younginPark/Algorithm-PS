arr = [[0 for i in range(1001)] for i in range(1001)]
visit = [False for i in range(1001)]
n = 0
q = []

def init():
    global visit
    for i in range(1001):
        visit[i] = False

def dfs(num):
    global arr
    global visit
    global n
    print(num, end=' ')
    visit[num] = True
    for i in range(1, n+1):
        if arr[num][i] == 1 and visit[i] == False:
            dfs(i)

def bfs():
    global arr
    global visit
    global n
    global q

    while q:
        front = q[0]
        #visit[front] = True
        print(front, end=' ')
        del(q[0])

        for i in range(1, n+1):
            if arr[front][i] == 1 and visit[i] == False:
                visit[i] = True
                q.append(i)


def main():
    global arr
    global visit
    global n
    n, m, v = map(int, input().split())
    for i in range(m):
        src, dest = map(int, input().split())
        arr[src][dest] = 1
        arr[dest][src] = 1
    dfs(v)
    print()
    init()
    q.append(v)
    visit[v] = True
    bfs()
    print()

if __name__ == "__main__":
    main()