import heapq
from sys import stdin
n = int(stdin.readline())
arr = []
for i in range(n):
    tmp = int(stdin.readline())
    heapq.heappush(arr, tmp)
for i in range(n):
    print(heapq.heappop(arr))