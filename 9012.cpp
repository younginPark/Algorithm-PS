#include <iostream>
using namespace std;

int size = -1;
char psarr[51];

void push(char v){
    size++;
    psarr[size] = v;

}

int pop(){
    if(size > -1){
        size--;
        return size;
    }
    else{
        return -2;
    }
}

int main() {

    char tmp[51];
    int num = 0;
    int popres = 0;
    cin >> num;
    for(int i = 0; i < num; i++){
        cin >> tmp;
        for(int j = 0; tmp[j] != '\0'; j++){
            if(tmp[j] == '('){
                push('(');
            }
            else{
                popres = pop();
                if(popres == -2){
                    cout << "NO";
                    cout << "\n";
                    break;
                }
            }
        }
        cout << "YES";
        cout << "\n";
    }


    return 0;
}