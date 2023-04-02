n, k = map(int, input().split())
arr = [0 for i in range(101)]
dp = [0 for i in range(10001)]
for i in range(1, n+1):
    arr[i] = int(input())
dp[0] = 1
for i in range(1, n+1): #동전 종류
    for j in range(k+1): #k까지의 값들
        if arr[i] <= j:
            dp[j] += dp[j-arr[i]]

print(dp[k])