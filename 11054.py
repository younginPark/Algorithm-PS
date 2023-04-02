n = int(input())
arr = list(map(int, input().split()))

dp1 = [0 for i in range(n)]
dp2 = [0 for i in range(n)]
dp3 = [0 for i in range(n)]

dp1[0] = 1
dp2[n-1] = 1

for i in range(1, n):
    tmp = 0
    for j in range(0, i):
        if arr[j] < arr[i]:
            tmp = max(tmp, dp1[j])
    dp1[i] = tmp+1

for i in range(n-1, 0, -1):
    tmp = 0
    for j in range(n-1, i, -1):
        if arr[j] < arr[i]:
            tmp = max(tmp, dp2[j])
    dp2[i] = tmp+1

for i in range(n):
    dp3[i] = dp1[i] + dp2[i] - 1

print(max(dp3))