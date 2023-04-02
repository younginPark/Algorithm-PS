n = input()
arr = []
for i in range(len(n)):
    arr.append(int(n[i]))
arr.sort(reverse=True)
answer = ''
for i in range(len(arr)):
    answer += str(arr[i])
print(answer)