#include<iostream>
using namespace std;


class stack{
    public:
    int*arr;
    int top;
    int space;

    stack(int s){
        space=s;
        arr=new int[space];
        top=-1;
    }

    bool isEmpty(){
        return top==-1;
    }
    bool isFull(){
        return top==space-1;
    }

    int peek(){
        cout<<arr[top]<<endl;
    }

    int push(int d){
        if(isFull()){
            cout<<"Stack overflow"<<endl;
        }
        else{
            arr[++top]=d;
        }
    }
    int pop(){
        if(isEmpty()){
            cout<<"Stack underflow"<<endl;
            return -1;
        }
        else{
            return arr[top--];
        }
    }

    void print(){
        if(isEmpty()){
            cout<<"Stack is Empty"<<endl;
        }
        else{
            for(int i=0;i<=top;i++){
                cout<<arr[i]<<" ";
            }
            cout<<endl;
        }
    }


};

int main(){
    stack s(10);
    s.push(5);
    s.push(4);
    s.push(8);
    s.push(23);
    s.push(45);
    s.print();
    s.pop();
    s.print();
    s.pop();
    s.print();
    s.peek();
}
