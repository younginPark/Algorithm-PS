tc = int(input())
for i in range(tc):
    now = 0
    n, guess = map(int, input().split())
    arr = list(map(int, input().split()))
    lst = []
    for i in range(len(arr)):
        lst.append([arr[i], 0])
    arr.sort(reverse=True)
    lst[guess][1] = 1
    now = 0
    while arr:
        if arr[0] == lst[0][0]:
            now += 1
            if lst[0][1] == 1:
                print(now)
                break
            else:
                del arr[0]
                del lst[0]
        else:
            tmp = lst[0]
            del lst[0]
            lst.append(tmp)