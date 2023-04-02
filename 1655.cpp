#include <iostream>
#include <queue>
using namespace std;

int N;
priority_queue<int> max_heap; // max heap
priority_queue<int, vector<int>, greater<int> > min_heap; //min heap
int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        int tmp;
        scanf("%d", &tmp);
        if(max_heap.size() == 0){
            max_heap.push(tmp);
        }
        else{
            if(max_heap.size() > min_heap.size()){
                min_heap.push(tmp);
            }
            else{
                max_heap.push(tmp);
            }
            if(max_heap.top() > min_heap.top()){
                int max_top = max_heap.top();
                int min_top = min_heap.top();
                max_heap.pop();
                min_heap.pop();
                max_heap.push(min_top);
                min_heap.push(max_top); 
            }
        }
        printf("%d\n", max_heap.top());
    }
    return 0;
}