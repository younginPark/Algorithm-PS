n, w = map(int, input().split())
arr = []
dp = [[0 for i in range(w+1)] for j in range(n)]
for i in range(n):
    arr.append(list(map(int, input().split())))
for i in range(n):
    for j in range(1, w+1):
        if arr[i][0] > j:
            dp[i][j] = dp[i-1][j] #담을 수 없으면 내꺼 안담고 현재 무게의 가방의 최대값 들고오기
        else:
            dp[i][j] = max(dp[i-1][j], dp[i-1][j-arr[i][0]]+arr[i][1])
print(dp[n-1][w])