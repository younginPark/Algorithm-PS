def main():
    n = int(input())
    arr = [999999 for i in range(n+1)] #0~n까지
    arr[0] = 0
    arr[1] = 0
    for i in range(1, n+1): #1~n까지
        if i * 2 <= n:
            arr[i*2] = min(arr[i*2], arr[i]+1)
        if i * 3 <= n:
            arr[i*3] = min(arr[i*3], arr[i]+1)
        if i + 1 <= n:
            arr[i+1] = min(arr[i+1], arr[i]+1)
    print(arr[n])
if __name__ == "__main__":
    main()