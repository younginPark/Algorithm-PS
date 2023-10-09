def solution(expression):
    answer = 0
    rank = [['+', '-', '*'], ['+', '*', '-'], ['-', '+', '*'],
           ['-', '*', '+'], ['*', '+', '-'], ['*', '-', '+']]
    for i in range(6):
        for j in range(3):
            new_expression = ""
            for k in range(1, len(expression), 2):
                if expression[k] == rank[i][j]:
                    if expression[k] == "*":
                        new_expression += str(int(expression[k-1]) * int(expression[k+1]))
                    elif expression[k] == "+":
                        new_expression += str(int(expression[k-1]) + int(expression[k+1]))
                    elif expression[k] == "-":
                        new_expression += str(int(expression[k-1]) - int(expression[k+1]))
                else:
                    new_expression += expression[k-1] + expression[k]
            expression = new_expression
            print(expression)
        # if abs(int(expression)) > answer:
        #     answer = int(expression)
    return answer

def main():
    print(solution("100-200*300-500+20"))

if __name__ == "__main__":
    main()