#include <iostream>
#include <queue>
using namespace std;

int dy[4] = { 0, +1, 0, -1 };
int dx[4] = { +1, 0, -1, 0 };

int N, K;
int board[105][105];
queue<pair<int, char> > cmd;

// &x = x의 주소
// *x = x의 주소에 있는 값

typedef struct node {
    int y, x;
    node* next;
    node* prev;
} Node;

Node* head;
Node* tail;

Node nodes[10005];
int nodeIndex = 0;

Node* makeNode(int y, int x){ // 머리
    Node* new_node = &nodes[nodeIndex++];
    new_node->x = x;
    new_node->y = y;
    return new_node;
}

void insert(Node* new_node){
    if(head == NULL && tail == NULL){
        head = new_node;
        tail = new_node;
    }
    else{
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
    //cout << "Head: " << head->y << ", " << head->x << "\n";
    //cout << "Tail: " << tail->y << ", " << tail->x << "\n";
}

void userInput(){
    cin >> N;
    cin >> K;
    for(int i = 0; i < K; i++){
        int y, x;
        cin >> y >> x;
        y--; x--;
        board[y][x] = 1;
    }
    int cmd_cnt;
    cin >> cmd_cnt;
    for(int i = 0; i < cmd_cnt; i++){
        int t; char turn;
        cin >> t >> turn;
        cmd.push(make_pair(t, turn));
    }
}

void solution(){
    int time = 0;
    int cur_dy = 0, cur_dx = 0;
    while(1){
        time++;
        // 이동할 머리의 위치 찾기
        int ny = head->y + dy[cur_dy];
        int nx = head->x + dx[cur_dx];
        // 머리의 위치가 벽 또는 몸통인지 확인 후 벽 또는 몸통이면 게임 멈추기
        if(ny < 0 || nx < 0 || ny >= N || nx >= N || board[ny][nx] == 2){
            break;
        }
        // 사과면 머리를 그냥 삽입
        if(board[ny][nx] == 1){
            insert(makeNode(ny, nx));
            board[ny][nx] = 2;
        }
        // 빈칸이면 머리 삽입 후 꼬리 삭제 후 board에 몸통 흔적 2 -> 0 으로 수정
        else if(board[ny][nx] == 0){
            insert(makeNode(ny, nx));
            board[ny][nx] = 2;
            Node* delete_tail = tail; 
            board[delete_tail->y][delete_tail->x] = 0;
            tail = delete_tail->prev;
        }
        // 방향변환을 해야하는 타이밍인지 확인 후 필요하면 변환 후 cmd.pop() 아니면 그냥 넘기기
        //cout << "** cmd time: " << cmd.front().first << "\n";
        if(cmd.front().first == time){
            if(cmd.front().second == 'L'){
                cur_dy = (cur_dy - 1 + 4) % 4;
                cur_dx = (cur_dx - 1 + 4) % 4;
            }
            else if(cmd.front().second == 'D'){
                cur_dy = (cur_dy + 1) % 4;
                cur_dx = (cur_dx + 1) % 4;
            }
            //cout << cur_dy << ", " << cur_dx << "\n";
            cmd.pop();
        }
        // for(int i = 0; i < N; i++){
        //     for(int j = 0; j < N; j++){
        //         cout << board[i][j] << " ";
        //     }
        //     cout << "\n";
        // }
        // cout << "\n";
    }
    cout << time;
}

int main(){
    userInput();
    insert(makeNode(0, 0));
    board[0][0] = 2;
    solution();
    return 0;
}