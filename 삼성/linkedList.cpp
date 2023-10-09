#include <iostream>
using namespace std;

// &x = x의 주소
// *x = x의 주소에 있는 값

typedef struct node {
    int x, y;
    Node* next;
    Node* prev;
} Node;

Node* head, tail;

Node nodes[100];
int nodeIdx = 0;

Node* makeNode(int x, int y){
    Node* new_node = &nodes[nodeIdx++]; // new_node라는 이름으로 새로운 노드를 생성하고 주소값 할당해줌
    new_node->x = x;
    new_node->y = y;
    return new_node;
}

void insert(Node* new_node){
    new_node->next = head; // 기존 head를 new_node의 next에 넣어주고
    head->prev = new_node; // head의 prev를 new_node에 넣어준다.
    head = new_node; // 
    if(*tail == NULL) {
        tail = new_node;
    }
}

int main(){

    return 0;
}