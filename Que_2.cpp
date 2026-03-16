#include<iostream>
using namespace std;

struct ticket{
    int type;
    int time;
    int ticket_id;
    int counter_no;
};

class stack{
    public:
    int*arr;
    int top;
    int size;

    stack(int s){
        size=s;
        arr=new int[size];
        top=-1;
    }
    bool isEmpty(){
        return top==-1;
    }
    bool isFull(){
        return top==size-1;
    }
    void push(int d){
        if(isFull()){
            cout<<"Stack OverFlow"<<endl;
        }
        arr[++top]=d;
    }
    int pop(){
        if(isEmpty()){
            cout<<"Stack: Empty  ";
            return -1;
        }
        else{
            return arr[top--];
        }
    }
    void print(){
        if(isEmpty()){
            cout<<"Stack: Empty  | ";
        }
        else{
            cout<<"Stack: ";
            for(int i=0;i<=top;i++){
                cout<<arr[i]<<" ";
            }
            cout<<" | ";
        }
    }
};
class queue{
    public:
    int*arr;
    int top;
    int front;
    int size;

    queue(int s){
        size=s;
        arr=new int[size];
        top=front=-1;
    }
    bool isEmpty(){
        return front==-1 || front>top ;
    }
    bool isFull(){
        return top==size-1;
    }
    void enqueue(int d){
        if(isFull()){
            cout<<"Queue is Full"<<endl;
            return;
        }
        if(front==-1){
            front=0;
        }
        arr[++top]=d;

    }
    int dequeue(){
        if(isEmpty()){
            cout<<"Empty"<<endl;
            return -1;
        }
        else{
            return arr[front++];
        }
        
    }
    void print(){
        if(isEmpty()){
            cout<<"Queue: Empty"<<endl;
            return;
        }
        else{
            cout<<"Queue: ";
            for(int i=front;i<=top;i++){
                cout<<arr[i]<<" ";
            }
        }
        
    }
};
class cirLLNode{
    public:
    int counter;
    int ticket[10]; 
    int count;  //no of tickets stored
    cirLLNode*next;

    cirLLNode(int id){

    }
};
class htNode{
    public:
    int reqId;
    int status;  //0 empty 1 occupied 2 deleted

    htNode(){
        reqId=-1;
        status=0;
    }
};
class ht{
    public:
    htNode*table;
    int size;

    ht(){
        size=10;
        table=new htNode[size];
    }

    void insert(int id){
        int index=id%size;
        while(table[index].status==1){
            index=(index+1)%size;
        }
        table[index].reqId=id;
        table[index].status=1;
    }
    void search(int id){
        cout<<"HASH SEARCH RESULTS :"<<endl;
        int index=id%size;
        int probe=1;
        for(int i=0;i<size;i++){
            if(table[index].status==1 && table[index].reqId==id){
                cout<< "Search "<<id<<": Found at Index "<<index<<" ,Probes : "<<probe<<endl;
                return;
            }
            probe++;
            index=(index+1)%size;
        }
        cout<<"Not found"<<", Probes : "<<probe<<endl;
    }
    void deleteById(int id){
        int index=id%size;
        int start=index;
        if(table[index].status==1){
            while(table[index].status==1 && table[index].reqId!=id){
            index=(index+1)%size;
        }
        table[index].status=2;
        table[index].reqId=-1;
        }
        else{
            cout<<"Not Found"<<endl;
        }
    }

    void print(){
        cout<<"FINAL HASH TABLE :"<<endl;
        for(int i=0;i<size;i++){
            cout<<"["<<i<<"] ";
            if(table[i].status==1){
                 cout<<table[i].reqId<<endl;
            }
            else if(table[i].status==0){
                cout<<"empty"<<endl;
            }
            else if(table[i].status==2){
                cout<<"deleted"<<endl;
            }
           
        }
    }
};
class bstNode{
    public:
    int reqId;
    bstNode*left;
    bstNode*right;

    bstNode(int d){
        reqId=d;
        left=right=NULL;
    }
};
class bst{
    public:
    bstNode*root;

    bst(){
        root=NULL;
    }
    bstNode* insert(bstNode*root ,int id){
        bstNode* newNode=new bstNode(id);
        if(root==NULL){
            root=newNode;
        }
        else if(root->reqId<id){
            root->left=insert(root->left,id);
        }
        else if(root->reqId>id){
            root->right=insert(root->right,id);
        }
    }
    void preorder(bstNode*root){
        if(root==NULL){
            return;
        }
        else{
            cout<<root->reqId<<" ";
            preorder(root->left);
            preorder(root->right);
        }
        
    }
    void inorder(bstNode*root){
        if(root==NULL){
            return;
        }
        else{
            inorder(root->left);
            cout<<root->reqId<<" ";
            inorder(root->right);
        }
        
    }
    void postorder(bstNode*root){
        if(root==NULL){
            return;
        }
        else{
            postorder(root->left);
            postorder(root->right);
            cout<<root->reqId<<" ";
        }
        
    }
    void print(){
        cout<<"BST TRAVERSALS :"<<endl;
        cout<<"Preorder :";
        preorder(root);
        cout<<endl;
        cout<<"Postorder : ";
        postorder(root);
        cout<<endl;
        cout<<"Inorder :";
        inorder(root);
    }
};

int main(){
    cout<<"Enter n ( number of tickets ) :"<<endl;
    int n;
    cin>>n;
    ticket*arr=new ticket[n];
    cout<<"Enter ticket id , type , time , Counter_no "<<endl;
    for(int i=0;i<n;i++){
        cin>>arr[i].ticket_id>>arr[i].type>>arr[i].time>>arr[i].counter_no;
    }
    
    for(int i=1;i<n;i++){
        ticket key=arr[i];
        int j=i-1;
        while(j>=0 && ((key.type<arr[j].type) || (key.type==arr[j].type && key.time<arr[j].time) || (key.type==arr[j].type && key.time==arr[j].time && key.ticket_id<arr[j].ticket_id))){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
    stack s(n);
    queue q(n);
    ht ht;
    bst bst;
    cout<<"Sorted tickets"<<endl;
    for(int i=0;i<n;i++){
        cout<<arr[i].ticket_id<<" "<<arr[i].type<<" "<<arr[i].time<<" "<<arr[i].counter_no<<endl;
    }
    for(int i=0;i<n;i++){
        if(arr[i].type==1){
            s.push(arr[i].ticket_id);
        }
        else{
            q.enqueue(arr[i].ticket_id);
        }
    }
    cout<<endl<<"DISPATCH TRACE :"<<endl;
    for(int i=0;i<n;i++){
        if(!s.isEmpty()){
            int processed_order=s.pop();
            ht.insert(processed_order);
            bst.root=bst.insert(bst.root,processed_order);
            cout<<endl<<"Serve : "<<processed_order<<" | ";
            s.print();
            q.print();
        }
        else{
            int processed_order=q.dequeue();
            ht.insert(processed_order);
            bst.root=bst.insert(bst.root,processed_order);
            cout<<endl<<"Serve : "<<processed_order<<" ";
            s.print();
            q.print();
        }
    }

    ht.print();
    ht.search(99);
    ht.deleteById(205);
    ht.print();
    bst.print();

}
