n = int(input())
arr = []
answer = 1
for i in range(n):
    tmp = list(map(int, input().split()))
    arr.append(tmp)
arr.sort(key=lambda x: (x[1], x[0]))
now = arr[0][1]
for i in range(1, n):
    if arr[i][0] >= now:
        now = arr[i][1]
        answer += 1
print(answer)