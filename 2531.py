n, d, k, c = 0, 0, 0, 0
arr = []
cnt = [0 for i in range(30001)]
now = 0

def goRight(a):
    global cnt, now
    if cnt[a] == 0:
        now += 1
    cnt[a] += 1

def goLeft(a):
    global cnt, now
    cnt[a] -= 1
    if cnt[a] == 0:
        now -= 1

def main():
    global n, d, k, c, arr, cnt, now
    answer = 0
    n, d, k, c = map(int, input().split()) #접시 수, 초밥 가짓수, 연속먹는접시수, 쿠폰초밥 
    for i in range(n):
        tmp = int(input())
        arr.append(tmp)
    for i in range(k):
        arr.append(arr[i])
    goRight(c)
    for i in range(k-1):
        goRight(arr[i])
    for i in range(n):
        goRight(arr[i+k-1])
        answer = max(answer, now)
        goLeft(arr[i])
    print(answer)

if __name__ == "__main__":
    main()