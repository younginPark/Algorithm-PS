n = int(input())
arr = []
for i in range(n):
    tmp = list(map(int, input().split()))
    arr.append(tmp)
arr.sort(key = lambda x: (x[0], x[1]))
for i in range(n):
    print(arr[i][0], arr[i][1])