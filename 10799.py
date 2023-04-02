s = input()
answer = 0
arr = []
now = 0
for i in range(len(s)):
    if s[i] == '(':
        now = i
        arr.append(0)
    elif s[i] == ')':
        if i-1 == now:
            del arr[-1]
            answer += len(arr)
        else:
            answer += 1
            del arr[-1]
print(answer)