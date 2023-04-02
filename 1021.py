from collections import deque
def main():
    answer = 0
    n, m = map(int, input().split())
    arr = list(map(int, input().split()))
    dq = deque()
    for i in range(1, n+1):
        dq.append(i)
    for i in range(m):
        cnt = 0
        for j in range(len(dq)):
            if dq[j] == arr[i]:
                break
            else:
                cnt += 1
        if cnt > len(dq)//2:
            while dq[0] != arr[i]:
                answer += 1
                dq.rotate()
        else:
            while dq[0] != arr[i]:
                answer += 1
                dq.rotate(-1)
        dq.popleft()
    print(answer)
    
if __name__ == "__main__":
    main()