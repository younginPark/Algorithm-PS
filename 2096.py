import copy
n = int(input())
dp_max = list(map(int, input().split()))
dp_min = dp_max.copy()
for i in range(1, n):
    tmp = list(map(int, input().split()))
    tmp2 = tmp.copy()
    tmp[0] += max(dp_max[0], dp_max[1])
    tmp2[0] += min(dp_min[0], dp_min[1])

    tmp[1] += max(dp_max[0], dp_max[1], dp_max[2])
    tmp2[1] += min(dp_min[0], dp_min[1], dp_min[2])

    tmp[2] += max(dp_max[1], dp_max[2])
    tmp2[2] += min(dp_min[1], dp_min[2])

    dp_max = tmp.copy()
    dp_min = tmp2.copy()

print(max(dp_max), min(dp_min))