import math
n = int(input())
prime_num = []
arr = [True for i in range(n+1)]
arr[0] = False
arr[1] = False
low = 0
high = 0
answer = 0
#소수 찾기
for i in range(2, int(math.sqrt(n))+1):
    if arr[i] == False:
        continue
    for j in range(i+i, n+1, i):
        arr[j] = False
#소수만 리스트에 넣기
for i in range(len(arr)):
    if arr[i] == True:
        prime_num.append(i)
#투포인터로 연속합 구하기
while low <= high and high <= len(prime_num):
    tot = sum(prime_num[low:high])
    if tot == n:
        answer += 1
    if tot > n:
        low += 1
    elif tot <= n:
        high += 1
print(answer)