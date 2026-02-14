#include<iostream>
using namespace std;

class Node{
    public:
    int data;
    Node*next;

    Node(int d) {
        this->data = d;
        this->next = NULL;
    }

};

void print(Node*head){
    
    if(head==NULL){
        return;
        cout<<"LL is empty";
    }
    else{
        Node*temp=head;
        while(temp!=NULL){
            cout<<temp->data<<" ";
            temp=temp->next;
    }
}
    cout<<endl;
}
void insertAtHead(Node* &head,Node* &tail,int d){
    Node*temp=new Node(d);
    if(head==NULL){
        head=temp;
        tail=temp;
    }
    else{
    temp->next=head;
    head=temp;

    cout<<"Inserted"<<endl;
}

}

void insertAtTail(Node* &head,Node* &tail,int d){
    Node*temp=new Node(d);
    if(head==NULL){
        head=temp;
        tail=temp;
    }
    else{
    tail->next=temp;
    tail=temp;
    }

}

void insertAtPos(Node*&head,Node*&tail,int pos,int d){
    if(pos==1){
        insertAtHead(head,tail,d);
        return;
    }
    
    Node*temp=head;
    int count=0;
    while(count<pos-1){
        temp=temp->next;
        count++;
    }

    if(temp->next==NULL){
        insertAtTail(head,tail,d);
    }

    else{
    Node*newNode=new Node(d);
    newNode->next=temp->next;
    temp->next=newNode;}

}

void del(Node*head,Node*tail,int pos){

    if(head==NULL){
        return;
    }

    if(pos==1){
        Node*temp=head;
        head=head->next;

        if(head==NULL){
            tail=NULL;
        }

        temp->next=NULL;
        delete temp;
        }
    else{
        Node*temp=head;
        Node*curr=NULL;
        int count=1;
        while(temp!=NULL&&count<pos){
            count++;
            curr=temp;
            temp=temp->next;
        }

        curr->next=temp->next;
        if(temp->next==NULL){
            tail=temp;
        }

        temp->next=NULL;
        delete temp;


    }
    }

int main(){
    Node*head=NULL;
    Node*tail=NULL;

    insertAtHead(head,tail,9);
    insertAtHead(head,tail,67);
    insertAtHead(head,tail,45);
    insertAtHead(head,tail,78);
    print(head);
    insertAtTail(head,tail,68);
    print(head);
    insertAtPos(head,tail,1,32);
    print(head);
    insertAtHead(head,tail,78);
    print(head);
    insertAtTail(head,tail,56);
    print(head);
    insertAtPos(head,tail,3,0);
    print(head);
    del(head,tail,3);
    print(head);
    
}