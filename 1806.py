n, s = map(int, input().split())
arr = list(map(int, input().split()))
low = 0
high = 1
tot = arr[0]
answer = 100000001
while low <= high and high <= n:
    if tot < s:
        print("high: ", tot)
        tot += arr[high]
        high += 1
    elif tot >= s:
        print("low: ", tot)
        answer = min(answer, high-low)
        if low <= high:
            tot -= arr[low]
            low += 1
if answer == 100000001:
    print(0)
else:
    print(answer)