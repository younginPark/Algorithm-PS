n = int(input())
arr = [1, 1]
for i in range(2, n):
    arr.append(arr[i-2]+arr[i-1])
print(arr[n-1])