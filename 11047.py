n, k = map(int, input().split())
arr = [0 for i in range(11)]
answer = 0
for i in range(n):
    arr[i] = int(input())
arr.sort(reverse=True)
for i in range(n):
    if k >= arr[i]:
        num = k // arr[i]
        k -= arr[i] * num
        answer += num
    if k == 0:
        break
        
print(answer)