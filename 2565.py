n = int(input())
dp = [0 for i in range(n)]
dp[0] = 1
arr = []
for i in range(n):
    arr.append(list(map(int, input().split())))
arr.sort(key = lambda x:x[0])

for i in range(1, n):
    tmp = 0
    for j in range(0, i):
        if arr[j][1] < arr[i][1]:
            tmp = max(tmp, dp[j])
    dp[i] = tmp + 1

print(n-max(dp))