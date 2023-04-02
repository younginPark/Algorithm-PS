import itertools
n = int(input())
answer = 987654321
tot = 0
mem = [i for i in range(1, n+1)]
arr = []
for i in range(n):
    tmp = list(map(int, input().split()))
    tot += sum(tmp)
    arr.append(tmp)
perm = list(itertools.combinations(mem, n//2))
for i in range(len(perm)):
    now = [0 for i in range(n+1)]
    a = 0
    b = 0
    for j in range(n//2):
        now[perm[i][j]] = 1
    for j in range(1, n+1):
        for k in range(j+1, n+1):
            if now[j] == 1 and now[k] == 1:
                a += arr[j-1][k-1]
                a += arr[k-1][j-1]
            elif now[j] != 1 and now[k] != 1:
                b += arr[j-1][k-1]
                b += arr[k-1][j-1]
    answer = min(answer, abs(a-b))
print(answer)