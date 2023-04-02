input_str = input()
ans = [-1 for i in range(26)]
for i in range(len(input_str)):
    if ans[ord(input_str[i])-97] == -1:
        ans[ord(input_str[i])-97] = i

for i in range(26):
    print(ans[i], end=" ")