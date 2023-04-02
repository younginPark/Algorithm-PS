n = int(input())
dp = [0 for i in range(n)]
arr = list(map(int, input().split()))
dp[0] = 1
for i in range(1, n):
    tmp = 0
    for j in range(0, i):
        if arr[j] < arr[i]:
            tmp = max(tmp, dp[j])
    dp[i] = tmp+1
print(max(dp))
