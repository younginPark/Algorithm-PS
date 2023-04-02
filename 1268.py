n = int(input())
arr = []
check = [[0 for i in range(n)] for i in range(n)]
student = 0
now = 0
for i in range(n):
    tmp = list(map(int, input().split()))
    arr.append(tmp)
for i in range(5):
    for j in range(n):
        cnt = 0
        for k in range(n):
            if j == k:
                continue
            elif j != k and arr[j][i] == arr[k][i]:
                check[j][k] = 1
for i in range(n):
    if now < sum(check[i]):
        student = i+1
        now = sum(check[i])
if now == 0:
    print(1)
else:
    print(student)