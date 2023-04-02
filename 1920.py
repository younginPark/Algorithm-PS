n = int(input())
num = list(map(int, input().split()))
m = int(input())
arr = list(map(int, input().split()))
num.sort()
answer = [0 for i in range(m)]
for i in range(m):
    left = 0
    right = len(num)-1
    while left <= right:
        mid = (left+right) // 2
        if arr[i] == num[mid]:
            answer[i] = 1
            break
        elif arr[i] < num[mid]:
            right = mid-1
        elif arr[i] > num[mid]:
            left = mid+1
for i in range(len(answer)):
    print(answer[i])
