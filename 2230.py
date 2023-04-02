n, m = map(int, input().split())
arr = []
for i in range(n):
    tmp = int(input())
    arr.append(tmp)
arr.sort()
low = 0
high = 0
answer = 2000000001
while low <= high and high < n:
    now = arr[high] - arr[low]
    if now >= m:
        answer = min(answer, now)
        low += 1
    else:
        high += 1
print(answer)