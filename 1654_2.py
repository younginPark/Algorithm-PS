k = 0
n = 0
arr = []

def main():
    global k, n, arr
    k, n = map(int, input().split())
    for i in range(k):
        tmp = int(input())
        arr.append(tmp)
    left = 1
    right = max(arr)
    ans = 0
    while left <= right:
        mid = (left + right) // 2
        ans = 0
        for i in range(k):
            ans += arr[i] // mid
        if ans < n:
            right = mid - 1
        else:
            left = mid + 1
    mid = (left + right) // 2
    print(mid)

if __name__ == "__main__":
    main()