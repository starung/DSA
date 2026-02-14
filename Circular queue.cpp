#include<iostream>
using namespace std;

class cir_queue{
    public:
    int*arr;
    int size;
    int top;
    int front;

    cir_queue(int s){
        size=s;
        arr=new int[size];
        top=front=-1;
    }

    void enqueue(int d){
        if(front==-1){
            front=top=0;
            arr[top]=d;
            cout<<"Element inserted "<<endl;
        }

        else if((top+1)%size==front){
            cout<<"Circular Queue is Full "<<endl;
        }

        else{
            top=(top+1)%size;
            arr[top]=d;
            cout<<"Element inserted "<<endl;
        }

        
    }

    void dequeue(){
        if(front==-1){
            cout<<"Empty"<<endl;
            return;
        }
        else if(top==front){
            top=front=-1;
        }
        else{
            front=(front+1)%size;
        }

    }

    void print(){

       if(front==-1){
        cout<<"Empty"<<endl;
        return;
       }
       int i=front;
       while(true){
        cout<<arr[i]<<" ";
        if(i==top){
            break;
        }
        i=(i+1)%size;
       }
       cout<<endl;
            
        
    }
};

int main(){
    cir_queue c(10);
    c.enqueue(5);
    c.print();
    c.enqueue(65);
    c.print();
    c.dequeue();
    c.print();

}