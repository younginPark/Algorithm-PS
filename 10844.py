n = int(input())
arr = [[0 for i in range(10)] for j in range(n+1)]

for i in range(1, 10):
    arr[1][i] = 1
for i in range(2, n+1):
    for j in range(0, 10):
        if j == 0:
            arr[i][j] = arr[i-1][j+1] % 1000000000
        elif j == 9:
            arr[i][j] = arr[i-1][j-1] % 1000000000
        else:
            arr[i][j] = (arr[i-1][j-1] + arr[i-1][j+1]) % 1000000000

print(sum(arr[n]) % 1000000000)