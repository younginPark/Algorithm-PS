dp = [-1 for i in range(100010)]

def go(ptr, cnt, v):
    if ptr - v[ptr] >= 0:
      if dp[ptr - v[ptr]] == -1 or dp[ptr - v[ptr]] > cnt + 1:
         dp[ptr - v[ptr]] = cnt + 1
         go(ptr - v[ptr], cnt + 1, v)
    if (ptr + v[ptr]) < len(v):
       if dp[ptr + v[ptr]] == -1 or dp[ptr + v[ptr]] > cnt + 1 :
         dp[ptr + v[ptr]] = cnt + 1
         go(ptr + v[ptr], cnt + 1, v)
    return

def main():
    v = [4, 1, 2, 3, 1, 0, 5]
    n = len(v)
    go(0, 0, v)
    if dp[n-1] == -1:
        print(-1)
    else:
        print(dp[n-1])

    return 0

if __name__ == "__main__":
    main()