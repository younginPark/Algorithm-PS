n = int(input())
k = int(input())

low = 1
high = n*n
result = 9999999999
while low <= high:
    cnt = 0
    mid = (low+high) // 2
    for i in range(1, n+1):
        cnt += min(mid//i, n)
    if cnt < k:
        low = mid + 1
    else:
        result = min(result, mid)
        high = mid -1
print(result)