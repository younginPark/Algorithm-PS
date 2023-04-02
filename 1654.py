k, n = map(int, input().split())
arr = [0 for i in range(k)]
for i in range(k):
    arr[i] = int(input())
left = 1
right = max(arr)
while left <= right:
    mid = (left+right) // 2
    answer = 0
    for i in range(k):
        answer += arr[i] // mid
    if answer >= n:
        left = mid + 1
    else:
        right = mid - 1
print(right)