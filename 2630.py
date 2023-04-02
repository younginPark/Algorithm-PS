import sys
input = sys.stdin.readline
n = 0
arr = []
blue = 0
white = 0
def div(y, x, N):
    global arr, blue, white
    cnt = 0
    for i in range(y, y + N):
        for j in range(x, x + N):
            if arr[i][j] == 1:
                cnt += 1
    if cnt == N * N:
        blue += 1
    elif cnt == 0:
        white += 1
    else:
        div_n = N // 2
        div(y, x, div_n)
        div(y + div_n, x, div_n)
        div(y, x + div_n, div_n)
        div(y+ div_n, x+ div_n, div_n)

def main():
    global n, arr, blue, white
    n = int(input())
    for i in range(n):
        tmp = list(map(int, input().split()))
        arr.append(tmp)
    div(0, 0, n)
    print(white)
    print(blue)

if __name__ == "__main__":
    main()
