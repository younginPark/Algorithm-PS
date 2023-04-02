def main():
    a, b = input().split()
    a = a[::-1]
    b = b[::-1]
    if a > b:
        print(a)
    else:
        print(b)
if __name__ == "__main__":
    main()