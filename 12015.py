import bisect
n = int(input())
arr = list(map(int, input().split()))
num = [arr[0]]
for i in range(1, n):
    if arr[i] > num[-1]:
        num.append(arr[i])
    else:
        insert = bisect.bisect_left(num, arr[i])
        num[insert] = arr[i]
print(len(num))