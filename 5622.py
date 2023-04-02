def main():
    dial = ['ABC', 'DEF', 'GHI', 'JKL', 'MNO', 'PQRS', 'TUV', 'WXYZ']
    s = input()
    ans = 0
    for i in range(len(s)):
        for j in range(len(dial)):
            if s[i] in dial[j]:
                #print(s[i], dial[j], j+2)
                ans += j+2
    print(ans+len(s))
if __name__ == "__main__":
    main()