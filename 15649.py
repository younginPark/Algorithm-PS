import itertools
n, m = map(int, input().split())
arr = []
for i in range(n):
    arr.append(i+1)
result = list(itertools.permutations(arr, m))
for i in range(len(result)):
    for j in range(m):
        print(result[i][j], end = " ")
    print()