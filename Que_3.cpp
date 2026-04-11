#include<iostream>
using namespace std;

struct request{
    int custID;
    int serviceType;
    int arrivalTime;
    int tellerNo;
};

class stack{
    public:
    int *arr;
    int top;
    int size;

    stack(int n){
        size=n;
        arr=new int[size];
        top=-1;
    }
    bool isEmpty(){
        return top==-1;
    }
    bool isFull(){
        return top==size-1;
    }
    void push(int id){
        if(isFull()){
            cout<<"Full";
        }
        else{
            arr[++top]=id;
        }
    }
    int pop(){
        if(isFull()){
            cout<<"Full";
        }
        else{
            return arr[top--];
        }
    }
    void print(){
        if(isEmpty()){
            cout<<"Empty";
        }
        else{
            for(int i=top;i>=0;i--){
                cout<<arr[i]<<" ";
            }
        }
    }
};
class queue{
    public:
    int *arr;
    int top;
    int front;
    int size;

    queue(int n){
        size=n;
        arr=new int[size];
        top=front=-1;
    }
    bool isEmpty(){
        return front==-1 || front>top;
    }
    bool isFull(){
        return top==size-1;
    }
    void push(int id){
        if(isFull()){
            cout<<"Full";
            return;
        }
        if(isEmpty()){
            front=0;
        }
        arr[++top]=id;
    }
    int pop(){
        if(isEmpty()){
            cout<<"Empty";
            return-1;
        }
        else{
            return arr[front++];
        }
    }
    void print(){
        if(isEmpty()){
            cout<<"Empty";
        }
        else{
            for(int i=front;i<=top;i++){
                cout<<arr[i]<<" ";
            }
        }
    }
};
class htNode{
    public:
    int reqId;
    int status; //0-empty,1-full,2-deleted

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
        int count=0;
        while(table[index].status!=0 && count<size){
            index=(index+1)%size;
            count++;
        }
        if(count<size){
            table[index].reqId=id;
            table[index].status=1;
        }
    }
    void search_helper(int id){
        int index=id%size;
        int probes=1;
        for(int i=0;i<size;i++){
            
            if(table[index].status==0){
                break;
            }
            if(table[index].status==1 && table[index].reqId==id){
                cout<<"Search "<<id<<" : Found at Index "<<index<<" , Probes : "<<probes<<endl;
                return;
            }
            index=(index+i)%size;
            probes++;
        }
        cout<<"Search "<<id<<" : Not Found , Probes : "<<probes<<endl;
    }
    void search(){
        cout<<"Enter q ( number of search queries ) :"<<endl;
        int q;
        cin>>q;
        cout<<"Enter "<<q<<" query keys :"<<endl;
        int arr[q];
        for(int i=0;i<q;i++){
            cin>>arr[i];
        }
        cout<<"HASH SEARCH RESULTS :"<<endl;
        for(int i=0;i<q;i++){
            search_helper(arr[i]);
        }
    }
    void deleteById(){
        cout<<"Enter kdel ( ticket to delete from hash ) :"<<endl;
        int id;
        cin>>id;
        int index=id%size;
        int count=0; 
        while(table[index].status!=0 && count<size){
            if(table[index].status==1 && table[index].reqId==id){
                table[index].reqId=-1;
                table[index].status=2;
            }
            index=(index+1)%size;
            count++;
        }
    }
    void print(){
        cout<<"FINAL HASH TABLE :"<<endl;
        for(int i=0;i<size;i++){
            cout<<i<<" : ";
            if(table[i].status==0){
                cout<<"Empty"<<endl;
            }
            else if(table[i].status==1){
                cout<<table[i].reqId<<endl;
            }
            else if(table[i].status==2){
                cout<<"Deleted"<<endl;
            }
        }

    }
};

class bstNode{
    public:
    bstNode*left;
    bstNode*right;
    int reqId;

    bstNode(int id){
        reqId=id;
        left=right=NULL;
    }
};

class bst{
    public:
    bstNode*root;

    bst(){
        root=NULL;
    }
    bstNode*insert(bstNode*root,int id){
        bstNode*newNode=new bstNode(id);
        if(root==NULL){
            root=newNode;
        }
        else if(root->reqId>id){
            root->left=insert(root->left,id);
        }
        else if(root->reqId<id){
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
        cout<<"Preorder : ";
        preorder(root);
        cout<<endl<<"Inorder : ";
        inorder(root);
        cout<<endl<<"Postorder : ";
        postorder(root);
        cout<<endl;
    }
};
int main(){
    cout<<"Enter n ( number of tickets ) :"<<endl;
    int n;
    cin>>n;
    request*arr=new request[n];
    cout<<"Enter 4 tickets ( custID serviceType arrivalTime tellerNo ):"<<endl;
    for(int i=0;i<n;i++){
        cin>>arr[i].custID>>arr[i].serviceType>>arr[i].arrivalTime>>arr[i].tellerNo;
    }
    for(int i=0;i<n;i++){
        request key=arr[i];
        int j=i-1;
        while(j>=0 && ((arr[j].serviceType>key.serviceType) || (arr[j].serviceType==key.serviceType && arr[j].arrivalTime>key.arrivalTime) || (arr[j].serviceType==key.serviceType && arr[j].arrivalTime==key.arrivalTime && arr[j].custID>key.custID))){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
    cout<<"SORTED TICKETS :"<<endl;
    for(int i=0;i<n;i++){
        cout<<arr[i].custID<<" "<<arr[i].serviceType<<" "<<arr[i].arrivalTime<<" "<<arr[i].tellerNo<<endl;
    }
    stack s(n);
    queue q(n);
    bst bst;
    ht ht;
    for(int i=0;i<n;i++){
        if(arr[i].serviceType==1){
            s.push(arr[i].custID);
        }
        else{
            q.push(arr[i].custID);
        }
    }
    int trace[n];
    int p=0;
    cout<<"DISPATCH TRACE :"<<endl;
    while(!s.isEmpty() || !q.isEmpty()){
        if(!s.isEmpty()){
            trace[p]=s.pop();
            cout<<"Serve : "<<trace[p]<<" | Stack : ";
            s.print();
            cout<<" | Queue : ";
            q.print();
            cout<<endl;
            p++;
        }
        else{
            trace[p]=q.pop();
            cout<<"Serve : "<<trace[p]<<" | Stack : ";
            s.print();
            cout<<" | Queue : ";
            q.print();
            cout<<endl;
            p++;
        }
    }
    for(int i=0;i<n;i++){
        ht.insert(trace[i]);
        bst.root=bst.insert(bst.root,trace[i]);
    }
    ht.search();
    ht.deleteById();
    ht.print();
    bst.print();
}
