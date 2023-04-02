tc = int(input())
arr = [ 1, 1, 1, 2, 2, 3, 4, 5, 7, 9] #0~9
for i in range(10, 100):
    arr.append(arr[i-5] + arr[i-1])
for i in range(tc):
    n = int(input())
    print(arr[n-1])