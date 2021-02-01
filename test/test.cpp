#include <cmath>
#include <iostream>

using namespace std;

struct Node { 
    const int data; 
    Node* next; 
    Node(int d) : data(d), next(NULL) {} 
};

Node* modifyLinkedList(Node* head){
    //Parameter: head (head node of a singlely linked list)
    Node* tempHead = head -> next -> next;
    head -> next -> next -> next -> next = head;
    head -> next -> next = NULL;
    head = tempHead;
    return head; 
}

int main() {
    Node *head = new Node(0);
    head -> next = new Node(1);
    head -> next -> next = new Node(2);
    head -> next -> next -> next = new Node(3);
    Node *temp = head;
    while(temp != NULL){
        printf("%d", temp -> data);
        printf("\n");
        temp = temp -> next;
    }
    Node *temp1 = modifyLinkedList(head);
    while(temp1 != NULL){
        printf("%d", temp1 -> data);
        temp1 = temp1 -> next;
    }
}