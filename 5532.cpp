#include <iostream>
using namespace std;

int max(int a, int b){
	return a > b ? a : b;
}

int main(){
	int total_day = 0;
	int math_p = 0, kor_p = 0;
	int can_math = 0, can_kor = 0;

	int kor_day = 0, math_day = 0;

	cin >> total_day >> kor_p >> math_p >> can_kor >> can_math;

	if(kor_p % can_kor > 0){
		kor_day = (kor_p / can_kor) + 1;
	}
	else{
		kor_day = (kor_p / can_kor);
	}

	if(math_p % can_math > 0){
		math_day = (math_p / can_math) + 1;
	}
	else{
		math_day = (math_p / can_math);
	}
	int result = total_day - max(kor_day, math_day);
	cout << result;
	return 0;
}