def main():
    croatia = ['c=', 'c-', 'dz=', 'd-', 'lj', 'nj', 's=', 'z=']
    s = input()
    ans = 0
    i = 0
    while i < len(s):
        if i < len(s)-1 and (s[i]+s[i+1] in croatia):
            ans += 1
            i += 2
        elif i < len(s)-2 and (s[i]+s[i+1]+s[i+2] in croatia):
            ans += 1
            i += 3
        else:
            ans += 1
            i += 1
    print(ans)

if __name__ == "__main__":
    main()