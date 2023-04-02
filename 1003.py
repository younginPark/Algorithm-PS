n = int(input())
a0 = [0 for i in range(41)]
a1 = [0 for i in range(41)]
a0[0] = 1
a1[1] = 1
for i in range(2, 41):
    a0[i] = a0[i-1] + a0[i-2]
    a1[i] = a1[i-1] + a1[i-2]
for i in range(n):
    num = int(input())
    print(a0[num], a1[num])