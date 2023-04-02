n = int(input())
arr = []
stack = []
result = []
record = []
ptr = 0
check = 0
for i in range(n):
    arr.append(int(input()))

for i in range(1, n+1):
    stack.append(i)
    record.append('+')
    while ptr < n and stack and stack[-1] == arr[ptr]:
        ptr += 1
        result.append(stack[-1])
        del stack[-1]
        record.append('-')
if len(arr) == len(result):
    for i in range(n):
        if arr[i] != result[i]:
            check = 1
            break
else:
    check = 1
if check == 1:
    print("NO")
else:
    for i in range(len(record)):
        print(record[i])