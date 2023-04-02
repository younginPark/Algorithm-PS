tc = int(input())
for i in range(tc):
    rep, s = input().split(" ")
    rep = int(rep)
    ans = ""
    for j in range(len(s)):
        for k in range(rep):
            ans += s[j]
    print(ans)