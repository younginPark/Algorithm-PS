#include <iostream>
#include <cmath>
using namespace std;

int main(){
	double d1, d2, d3;
	double x1, x2, x3;

	cin >> d1 >> d2 >> d3;

	x3 = (d2-d1+d3) / 2;
	x2 = d3 - x3;
	x1 = d1 - x2;

	if(x1 <= 0 || x2 <= 0 || x3 <= 0){
		cout << -1 << "\n";
	}
	else{
		x1 = round(x1 * 10) / 10;
		x2 = round(x2 * 10) / 10;
		x3 = round(x3 * 10) / 10;
		cout << "1" << "\n";
		printf("%0.1f %0.1f %0.1f\n", x1, x2, x3);
		//cout << x1 << " " << x2 << " " << x3 << "\n";
	}
	return 0;
}