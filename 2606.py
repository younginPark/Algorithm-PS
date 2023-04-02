arr = [[0 for i in range(101)] for j in range(101)]
visit = [False for i in range(101)]
com_num = 0
answer = 0

def dfs(num):
    global arr
    global visit
    global com_num
    global answer
    visit[num] = True
    for i in range(1, com_num+1):
        if arr[num][i] == 1 and visit[i] == False:
            answer += 1
            dfs(i)


def main():
    global arr
    global visit
    global com_num
    global answer
    com_num = int(input())
    connect = int(input())
    for i in range(connect):
        src, dest = map(int, input().split())
        arr[src][dest] = 1
        arr[dest][src] = 1
    dfs(1)
    print(answer)
if __name__ == "__main__":
    main()
