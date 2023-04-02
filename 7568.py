n = int(input())
arr = []
answer = [1 for i in range(n)]
for i in range(n):
    tmp = list(map(int, input().split()))
    arr.append(tmp)
for i in range(n):
    for j in range(n):
        if i != j:
            if arr[i][0] > arr[j][0] and arr[i][1] > arr[j][1]:
                answer[j] += 1
for i in range(n):
    print(answer[i], end = " ")
print()