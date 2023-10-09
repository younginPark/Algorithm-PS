#include <iostream>
#include <string>
using namespace std;

int main(){
	string result = "true";
	char arr[1001];
	char first[1001];
	char last[1001];
	cin.getline(arr, 1001);
	//cout << arr;
	int i = 0, j = 0;
	while(arr[i] != '\0'){
		if(97 <= arr[i] && arr[i] <= 122){
			first[j] = arr[i] - 32;
			j++; i++;
		}
		else if((48 <= arr[i] && arr[i] <= 57) || (65 <= arr[i] && arr[i] <= 90)){
			first[j] = arr[i];
			j++; i++;
		}
		else{
			i++;
			continue;
		}
	}
	j = 0;
	for(int i = strlen(first) - 1; i >= 0; i--){
		last[i] = first[j];
		j++;
	}
	//cout << last;
	for(int i = 0; i < strlen(first); i++){
		if(last[i] == first[i]){
			continue;
		}
		else{
			result = "false";
			break;
		}
	}

	cout << result;
	return 0;
}