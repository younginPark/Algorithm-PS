#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    while(1){
        string str1;
        cin >> str1;
        if(str1 == "*"){
            break;
        }
        bool ans = true;
        for(int i = 1; i < str1.length(); i++){
            vector<pair<char, char> > v;
            for(int j = 0; j+i < str1.length(); j++){
                v.push_back(make_pair(str1[j], str1[j+i]));
            }
            // for(int j = 0; j < v.size(); j++){
            //     cout << i << " !!\n";
            //     cout << v[j].first << v[j].second << "\n";
            // }
            for(int j = 0; j < v.size()-1; j++){
                for(int k = j+1; k < v.size(); k++){
                    if(v[j].first == v[k].first && v[j].second == v[k].second){
                        ans = false;
                        //cout << "*** false : " << v[j].first << v[k].first << v[j].second << v[k].second << "\n";
                        break;
                    }
                }
                if(ans == false){
                    break;
                }
            }
            if(ans == false){
                break;
            }
        }
        if(ans == true){
            printf("%s is surprising.\n", str1.c_str());
        }
        else{
            printf("%s is NOT surprising.\n", str1.c_str());
        }
    }
    return 0;
}