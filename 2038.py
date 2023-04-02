def main():
    n = int(input())
    fn = [0, 1]
    tot = fn[1]
    if n == 1:
        print(1)
        return
    else:
        for i in range(2, n+1):
            fn.append(1 + fn[i - fn[fn[i-1]]])
            tot += fn[i]
            if tot >= n:
                print(i)
                break
if __name__ == "__main__":
    main()