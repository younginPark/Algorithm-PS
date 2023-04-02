from collections import deque
v = 0
e = 0
graph = [[] for i in range(10001)]
ans = [2147483647 for i in range(10001)]
visit = [False for i in range(10001)]
ans[1] = 0
visit[1] = True
def main():
    v, e = map(int, input().split())
    for i in range(e):
        tmp1, tmp2, tmp3 = map(int, input().split())
        graph[tmp1].append([tmp2, tmp3])
        graph[tmp2].append([tmp1, tmp3])
    for i in range(1, v+1):
        for j in range(len(graph[i])):
            if visit[graph[i][j][0]] == False:
                visit[graph[i][j][0]] = True
                ans[graph[i][j][0]] = ans[i] + graph[i][j][1]
            else:
                ans[graph[i][j][0]] = min(ans[graph[i][j][0]], ans[i]+graph[i][j][1])
    print(ans[v])
if __name__ == "__main__":
    main()