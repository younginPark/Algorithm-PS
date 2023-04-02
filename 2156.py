n = int(input())
wine = [0 for i in range(10001)]
dp = [0 for i in range(10001)]
for i in range(n):
    wine[i] = int(input())

dp[0] = wine[0]
dp[1] = max(wine[0]+wine[1], wine[1])
for i in range(2, n):
    dp[i] = max(dp[i-2]+wine[i], dp[i-1], dp[i-3]+wine[i-1]+wine[i])
print(max(dp))