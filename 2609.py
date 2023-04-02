import math
n, m = map(int, input().split())
num = 2
min_answer = 1
while 1:
    if num > n or num > m:
        break
    if n % num == 0 and m % num == 0:
        min_answer *= num
        n //= num
        m //= num
    else:
        num += 1
print(min_answer)
print(min_answer * n * m)