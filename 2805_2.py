import sys
def main():
    n, m = map(int, sys.stdin.readline().split())
    arr = list(map(int, sys.stdin.readline().split()))
    left = 1
    right = max(arr)
    while left <= right:
        total = 0
        mid = (left + right) // 2
        for i in range(n):
            if arr[i] >= mid:
                total += arr[i] - mid
        if total < m:
            right = mid - 1
        else:
            left = mid + 1
    print((left+right)//2)
if __name__ == "__main__":
    main()