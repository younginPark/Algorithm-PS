num = int(input())
house = []
for i in range(num):
    house.append(list(map(int, input().split())))
for i in range(1, num):
    house[i][0] += min(house[i-1][1], house[i-1][2])
    house[i][1] += min(house[i-1][0], house[i-1][2])
    house[i][2] += min(house[i-1][0], house[i-1][1])

answer = min(house[num-1][0], house[num-1][1], house[num-1][2])
print(answer)