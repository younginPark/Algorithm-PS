#include <iostream>
#include <string>
#include <vector>
using namespace std;

int N, M;
int dist[1001][1001];
vector<string> sentence;

void solve() {
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            int sum = 0;
            for(int k = 0; k < M; k++){
                if(sentence[i][k] != sentence[j][k]){
                    sum++;
                }
            }
            dist[i][j] = sum;
        }
    }
}

int main() {
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        string tmp;
        cin >> tmp;
        sentence.push_back(tmp);
    }
    solve();
    int ans_sum = 51;
    string ans_sentence;

    for(int i = 0; i < N; i++){
        int tot = 0;
        for(int j = 0; j < M; j++){
            cout << dist[i][j] << " ";
            tot += dist[i][j];
        }
        cout << tot << "\n";
        if(ans_sum > tot){
            ans_sum = tot;
            ans_sentence = sentence[i];
        }
    }
    cout << ans_sentence << "\n" << ans_sum;
    return 0;
}