def main():
    tot = int(input())
    for j in range(tot):
        n = int(input())
        if n == 0:
            print(1, 0)
        elif n == 1:
            print(0, 1)
        else:
            print(1 , 2)
if __name__ == "__main__":
    main()