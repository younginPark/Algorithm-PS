s = input()
arr = []
tmp = ''
for i in range(len(s)):
    if s[i] == '+' or s[i] == '-':
        arr.append(int(tmp))
        tmp = ''
        arr.append(s[i])
    else:
        tmp += s[i]
arr.append(int(tmp))

answer = 0
minus = False
for i in range(len(arr)):
    if arr[i] != '+' and arr[i] !='-':
        if minus == True:
            answer -= arr[i]
        else:
            answer += arr[i]
    if arr[i] == '-':
        minus = True
print(answer)