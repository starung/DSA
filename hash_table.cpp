#include<iostream>
#include<string.h>
using namespace std;

class Node{
    public:
    int roll;
    string name;
    int batch;
    Node*next;

    //constructor
    Node(int r,string n,int b){
        this->roll=r;
        this->name=n;
        this->batch=b;
        this->next=NULL;
    }
};


class hashTable{
    private:
    Node**table;
    int capacity;

    int hashFun(int roll){
        return roll%capacity;
    }

    public:

    hashTable(int cap){
        this->capacity=cap;
        table=new Node*[capacity];
        

        //elements are garbage value

        for(int i=0;i<capacity;i++){
            table[i]=NULL;
        }
    }

    void print(){

        for(int j=0;j<capacity;j++){
        
        Node*temp=table[j];
        cout<<"printing elemet "<< j <<"of array"<<endl;
        while(temp!=NULL){
            cout<<temp->roll<<" "<<temp->name<<" "<<temp->batch<<endl;
            temp=temp->next;
        }
    }
    }

    void insert(int r,string n,int b){
        int index=hashFun(r);

        Node*newNode=new Node(r,n,b);

        //insert at begining of linked list
        newNode->next=table[index];
        table[index]=newNode;


        cout<<"inserted"<<endl;
    }

    void del(int roll){

        int index=hashFun(roll);
        Node*temp=table[index];
        if(temp==NULL){
            return;
        }
        else{

        Node*temp2=NULL;
        while(temp!=NULL && temp->roll!=roll){
            temp2=temp;
            temp=temp->next;

        }

        if(temp2==NULL){     //deleting 1st node
            table[index]=temp->next;
        }
        else{
        temp2->next=temp->next;
        temp->next=NULL;
        }

        delete temp;
        cout<<"The entry with roll no "<<roll<<" is deleted"<<endl;

        
    }
    cout<<endl;
    }
    
    
};


int main(){
    hashTable ht(5);
    ht.insert(24117,"Gaurav",2024);
    ht.insert(24130,"Harish",2024);
    ht.insert(24225,"Naman",2024);
    ht.insert(24051,"Anish",2024);
    ht.print();
    ht.del(24225);
    ht.print();
}