#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main(){
    
    stack <char> v_left;
    stack <char> v_right;
    string s;
    int m;
    char comm;
    cin >> s>> m;
    for(int i = 0; i < s.length(); i++){
        v_left.push(s[i]);
    }
    for(int i = 0; i < m; i++){
        cin >> comm;
        if(comm == 'P'){
            char alpha;
            cin >> alpha;
            v_left.push(alpha);
        }
        else{
            if(comm == 'L'){
                if(!v_left.empty()){
                    char tmp = v_left.top();
                    v_left.pop();
                    v_right.push(tmp);
                }
            }
            else if(comm == 'D'){
                if(!v_right.empty()){
                    char tmp = v_right.top();
                    v_right.pop();
                    v_left.push(tmp);
                }
            }
            else if(comm == 'B'){
                if(!v_left.empty()){
                    v_left.pop();
                }
            }
        }
    }
    while(!v_left.empty()){
        char tmp2 = v_left.top();
        v_left.pop();
        v_right.push(tmp2);
    }
    while(!v_right.empty()){
        printf("%c", v_right.top());
        v_right.pop();
    }
    return 0;
}