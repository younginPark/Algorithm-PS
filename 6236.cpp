#include <iostream>
#include <algorithm>
using namespace std;

int n, m;
int arr[100001];

bool go(int num){
    int now = num;
    int cnt = 1;
    for(int i = 0; i < n; i++){
        if(num < arr[i]){
            return false;
        }
        if(now - arr[i] < 0){
            now = num;
            cnt += 1;
        }
        now -= arr[i];
    }
    return cnt <= m;
}

int main(){
    int mid = 0, left = 0, right = 0;
    int sum = 0;
    int result = 0;
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        sum += arr[i];
    }
    right = sum;
    while(left <= right){
        mid = (left+right) / 2;
        if(go(mid)){
            result = mid;
            right = mid-1;
        }
        else{
            left = mid+1;
        }
    }
    printf("%d", result);
    return 0;
}