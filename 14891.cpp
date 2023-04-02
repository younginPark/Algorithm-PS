#include <iostream>
using namespace std;

void clockWise(char gear[]){
	char tmparr[9];
	for(int i = 0; i < 8; i++){
		tmparr[i] = gear[i];
	}

	for(int i = 1; i < 8; i++){
		gear[i] = tmparr[i-1];
	}
	gear[0] = tmparr[7];
}

void counterClockWise(char gear[]){
	char tmparr[9];
	for(int i = 0; i < 8; i++){
		tmparr[i] = gear[i];
	}

	for(int i = 1; i < 8; i++){
		gear[i-1] = tmparr[i];
	}
	gear[7] = tmparr[0];
}

int main(){

	char gear1[9];
	char gear2[9];
	char gear3[9];
	char gear4[9];
	int cnt = 0;
	int num = 0, dir = 0;
	int result = 0;
	int one = 0, two = 0, three = 0; //같으면 3 다르면 4
	
	cin >> gear1 >> gear2 >> gear3 >> gear4;
	
	cin >> cnt;
	for(int i = 0; i < cnt; i++){
		cin >> num >> dir;

		if(gear1[2] == gear2[6]){
			one = 3;
		}
		else{
			one = 0;
		}

		if(gear2[2] == gear3[6]){
			two = 3;
		}
		else{
			two = 0;
		}

		if(gear3[2] == gear4[6]){
			three = 3;
		}
		else{
			three = 0;
		}


		if(num == 1){
			if(dir == 1){
				clockWise(gear1);

				if(one == 3){ //같으니까 안돌려, 뒤에 쭉 돌 일 없음
					continue;
				}
				else{
					counterClockWise(gear2); //2번째꺼 돌렸으면 3번째,4번째도 돌 가능성 있으 
					if(two == 3){
						continue;
					}
					else{
						clockWise(gear3);
						if(three == 3){
							continue;
						}
						else{
							counterClockWise(gear4);
						}
					}
				}
			}
			else{
				counterClockWise(gear1);
				if(one == 3){
					continue;
				}
				else{
					clockWise(gear2);
					if(two == 3){
						continue;
					}
					else{
						counterClockWise(gear3);
						if(three == 3){
							continue;
						}
						else{
							clockWise(gear4);
						}
					}
				}
			}
		}
		else if(num == 2){
			if(dir == 1){
				clockWise(gear2);
				if(one != 3){
					counterClockWise(gear1);
				}
				if(two != 3){
					counterClockWise(gear3);
					if(three != 3){
						clockWise(gear4);
					}
				}
				else{
					continue;
				}
			}
			else{
				counterClockWise(gear2);
				if(one != 3){
					clockWise(gear1);
				}
				if(two != 3){
					clockWise(gear3);
					if(three != 3){
						counterClockWise(gear4);
					}
				}
				else{
					continue;
				}
			}
			
		}
		else if(num == 3){
			if(dir == 1){
				clockWise(gear3);
				if(three != 3){
					counterClockWise(gear4);
				}
				if(two != 3){
					counterClockWise(gear2);
					if(one != 3){
						clockWise(gear1);
					}
				}
				else{
					continue;
				}

			}
			else{
				counterClockWise(gear3);
				if(three != 3){
					clockWise(gear4);
				}
				if(two != 3){
					clockWise(gear2);
					if(one != 3){
						counterClockWise(gear1);
					}
				}
				else{
					continue;
				}
			}
			
		}
		else if(num == 4){
			if(dir == 1){
				clockWise(gear4);
				if(three == 3){ 
					continue;
				}
				else{
					counterClockWise(gear3); 
					if(two == 3){
						continue;
					}
					else{
						clockWise(gear2);
						if(one == 3){
							continue;
						}
						else{
							counterClockWise(gear1);
						}
					}
				}

			}
			else{
				counterClockWise(gear4);
				if(three == 3){ 
					continue;
				}
				else{
					clockWise(gear3); 
					if(two == 3){
						continue;
					}
					else{
						counterClockWise(gear2);
						if(one == 3){
							continue;
						}
						else{
							clockWise(gear1);
						}
					}
				}

			}
			
		}
	}

	//이 아래부터는 톱니바퀴 점수 합산

	if(gear1[0] == '0'){
		result += 0;
	}
	else{
		result += 1;
	}

	if(gear2[0] == '0'){
		result += 0;
	}
	else{
		result += 2;
	}

	if(gear3[0] == '0'){
		result += 0;
	}
	else{
		result += 4;
	}

	if(gear4[0] == '0'){
		result += 0;
	}
	else{
		result += 8;
	}

	cout << result;
	return 0;
}

