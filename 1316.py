def main():
    tc = int(input())
    ans = tc
    for i in range(tc):
        s = input()
        now = s[0]
        change = 0
        alpha = [0 for i in range(26)]
        for i in range(len(s)):
            if(now != s[i]):
                change = 1
                now = s[i]
            else:
                change = 0

            if change == 1 and alpha[ord(s[i])-97] > 0:
                ans -= 1
                break
            else:
                alpha[ord(s[i])-97] += 1
    print(ans)

if __name__ == "__main__":
    main()