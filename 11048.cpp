#include <iostream>
#include <algorithm>
using namespace std;

int N, M;
int arr[1001][1001];

int main(){
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> arr[i][j];
        }
    }
    for(int i = 1; i < M; i++){
        arr[0][i] += arr[0][i-1];
    }
    for(int i = 1; i < N; i++){
        arr[i][0] += arr[i-1][0];
    }
    for(int i = 1; i < N; i++){
        for(int j = 1; j < M; j++){
            int max_num = max(arr[i-1][j], arr[i][j-1]);
            arr[i][j] += max(max_num, arr[i-1][j-1]);
        }
    }
    printf("%d\n", arr[N-1][M-1]);
    return 0;
}