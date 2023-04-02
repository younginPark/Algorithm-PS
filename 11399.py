n = int(input())
arr = list(map(int, input().split()))
arr.sort()
now = 0
answer = 0
for i in range(len(arr)):
    now += arr[i]
    answer += now
print(answer)