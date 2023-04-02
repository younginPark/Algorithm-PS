n = int(input())
arr = []
for i in range(0,n):
	tmp = input()
	arr.append((len(tmp), tmp))

arr.sort()
tmp = ''
for i,j in arr:
	if tmp == j:
		continue
	tmp = j
	print(j)