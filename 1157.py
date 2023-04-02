def main():
    s = input()
    ans = [0 for i in range(26)]
    for i in range(len(s)):
        if ord(s[i]) >= 97:
            ans[ord(s[i]) - 97] += 1
        else:
            ans[ord(s[i]) - 65] += 1
    ans_max = 0
    record = 0
    for i in range(26):
        if(ans[i]> 0 and ans_max < ans[i]):
            ans_max = ans[i]
            record = i
    #print(chr(record + 65))
    for i in range(26):
        if(ans_max == ans[i] and i != record):
            record = '?'
            print(record)
            return
    print(chr(record+65))

if __name__ == "__main__":
    main()