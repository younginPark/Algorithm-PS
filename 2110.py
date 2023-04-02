n, c = map(int, input().split())
arr = []
for i in range(n):
    arr.append(int(input()))
arr.sort()
left = 0
right = arr[-1] - arr[0]
answer = 0
while left <= right:
    mid = (left+right) // 2
    cnt = 1
    old = arr[0]
    for i in range(1, n):
        if arr[i] - old >= mid:
            cnt += 1
            old = arr[i]
    if cnt >= c:
        answer = max(answer, mid)
        left = mid+1
    else:
        right = mid-1
print(answer)