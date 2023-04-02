a1 = 1
a2 = 2
n = int(input())
if n == 1:
    print(a1)
elif n == 2:
    print(a2)
else:
    for i in range(3, n+1):
        answer = (a2 + a1) % 15746
        a1 = a2
        a2 = answer
    print(answer)
