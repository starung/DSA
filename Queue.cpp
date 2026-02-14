#include<iostream>
using namespace std;

class queue {
        private:
            int* arr;
            int size;
            int front;
            int rear;
        
        public:
            queue(int s){
                size=s;
                arr=new int[size];
                front=0;
                rear=0;

            }

            bool isEmpty(){
                if(front==rear){
                    return true;
                }
                else {
                    return false;
                }
            }

            bool isFull(){
                if(rear==size-1){
                    return true;
                }
                else {
                    return false;
                }
            }

            void push(int x){
                if(isFull()){
                    cout<<"The Queue is Full"<<endl;
                }
                else{
                    arr[rear++]=x;
                }
            }
            int pop(){
                if(isEmpty()){
                    cout<<"The Queue is Empty"<<endl;
                    return -1;
                }
                else if (front==rear)
                {
                    front=0;
                    rear=0;
                }
                
                else{
                    return arr[front++];
            }
        }

    
};

int main(){

    int size=6;
    queue q(size);
    q.push(2);
    q.push(5);
    q.push(9);
    cout<<"The Pop element is "<<q.pop();
    cout<<"The Pop element is "<<q.pop();
    cout<<"The Pop element is "<<q.pop();
    cout<<"The Pop element is "<<q.pop();

}