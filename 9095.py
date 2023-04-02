answer = 0
def go(soo, num):
    global answer
    if soo == num:
        answer += 1
        return
    if soo+1 <= num:
        go(soo+1, num)
    if soo+2 <= num:
        go(soo+2, num)
    if soo+3 <= num:
        go(soo+3, num)
tc = int(input())
arr = [1, 2, 3]
for i in range(tc):
    answer = 0
    num = int(input())
    go(0, num)
    print(answer)