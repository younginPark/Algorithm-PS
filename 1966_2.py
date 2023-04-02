from collections import deque
import heapq

def main():
    tc = int(input())
    for _ in range(tc):
        answer = 0
        n, m = map(int, input().split())
        tmp_arr = list(map(int, input().split()))
        priority = []
        dq = deque()
        for i in range(n):
            heapq.heappush(priority, (-tmp_arr[i], tmp_arr[i]))
            dq.append([tmp_arr[i], i])
        # print(priority)
        # print(list(dq))
        while 1:
            if priority[0][1] == dq[0][0]:
                if m == dq[0][1]:
                    answer += 1
                    print(answer)
                    break
                else:
                    heapq.heappop(priority)
                    dq.popleft()
                    answer += 1
            else:
                dq.rotate(-1)
            # print("***")
            # print(priority)
            # print(list(dq))
            # print(answer)
if __name__ == "__main__":
    main()