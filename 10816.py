import bisect
n = int(input())
num = list(map(int, input().split()))
m = int(input())
arr = list(map(int, input().split()))
num.sort()
for i in range(m):
    print(bisect.bisect(num, arr[i]) - bisect.bisect_left(num, arr[i]), end=" ")
print()