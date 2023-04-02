n = int(input())
arr = [i for i in range(0, n+1)]
answer = []
low = 1
high = 1
while low <= high and high <= n:
    now = pow(arr[high], 2) - pow(arr[low], 2)
    if now == n:
        answer.append(high)
    if now >= n:
        low += 1
    else:
        high += 1
if answer:
    for i in range(len(answer)):
        print(answer[i])
else:
    print(-1)