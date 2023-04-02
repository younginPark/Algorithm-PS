#include <iostream>
#include <cstring>
#define MAX_NUM 51
using namespace std;

int MIN(int a, int b){
	return a > b ? b : a;
}

int main(){
	char str1[MAX_NUM];
	char str2[MAX_NUM];
	int result = 0;
	int min = 100;
	int len1 = 0, len2 = 0;

	cin >> str1 >> str2;

	len1 = strlen(str1);
	len2 = strlen(str2);

	for(int i = 0; i <= (len2-len1); i++){
		for(int j = 0; j < len1; j++){
			if(str1[j] != str2[i+j]){
				result++;
			}
		}
		min = MIN(result, min);
		result = 0;
	}
	cout << min << "\n";
	return 0;
}