from collections import deque
arr = [100002 for i in range(100001)]
subin = 0
sis = 0
answer = 100001
q = deque()
def bfs():
    global sis, arr, answer, q
    while q:
        front = q.popleft()
        if front[0] == sis:
            answer = front[1]
            break
        if front[0]*2 <= 100000 and front[1]+1 < arr[front[0]*2]:
            arr[front[0]*2] = front[1]+1
            q.append([front[0]*2, front[1]+1])
        if front[0]+1 <= 100000 and front[1]+1 < arr[front[0]+1]:
            arr[front[0]+1] = front[1]+1
            q.append([front[0]+1, front[1]+1])
        if front[0]-1 >= 0 and front[1]+1 < arr[front[0]-1]:
            arr[front[0]-1] = front[1]+1
            q.append([front[0]-1, front[1]+1])

def main():
    global subin, sis, arr, answer, q
    subin, sis = map(int, input().split())
    arr[subin] = 0
    q.append([subin, 0])
    bfs()
    print(answer)


if __name__ == "__main__":
    main()