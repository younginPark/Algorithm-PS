def main():
	answer = 0
	place = int(input())
	student_num = list(map(int, input().split()))
	boss, vice = map(int, input().split())

	for i in range(place):
		student_num[i] -= boss
		if student_num[i] > 0:
			if student_num[i] % vice == 0:
				answer += student_num[i] // vice
			else:
				answer += (student_num[i] // vice) + 1
	print(answer+place)

if __name__ == "__main__":
	main()
