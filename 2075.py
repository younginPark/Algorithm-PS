import heapq
n = int(input())
pq = []
for i in range(n):
    tmp = list(map(int, input().split()))
    for j in range(n):
        if len(pq) < n:
            heapq.heappush(pq, tmp[j])
        else:
            if pq[0] < tmp[j]:
                heapq.heappop(pq)
                heapq.heappush(pq, tmp[j])

print(pq[0])