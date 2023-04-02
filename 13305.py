n = int(input())
dis = list(map(int, input().split()))
oil = list(map(int, input().split()))
answer = (dis[0] * oil[0])
now = oil[0]
for i in range(1, n-1):
    now = min(now, oil[i])
    answer += now * dis[i]
print(answer)