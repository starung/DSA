#include<iostream>
using namespace std;

struct Ticket{
    int ticketID;
    int type;
    int time;
    int counterNo;
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
    void push(int id){
        if(isFull()){
            cout<<"Full";
        }
        else{
            arr[++top]=id;
        }
    }
    int pop(){
        if(isEmpty()){
            cout<<" Empty ";
        }
        else{
            return arr[top--];
        }
    }
    void print(){
        if(isEmpty()){
            cout<<" Empty ";
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
        return front==-1 || front>top;
    }
    bool isFull(){
        return top==size-1;
    }
    void enqueue(int id){
        if(isFull()){
            cout<<"Full";
            return;
        }
        else if(isEmpty()){
            front=0;
        }
        arr[++top]=id;   
    }
    int dequeue(){
        if(isEmpty()){
            cout<<" Empty ";
        }
        else{
            return arr[front++];
        }
    }
    void print(){
        if(isEmpty()){
            cout<<" Empty ";
        }
        else{
            for(int i=front;i<=top;i++){
                cout<<arr[i]<<" ";
            }
        }
    }
};
class hashNode{
    public:
    int reqId;
    int status;  //0-empty ,1-occupied ,2-deleted
    
    hashNode(){
        reqId=-1;
        status=0;
    }
};
class ht{
    public:
    hashNode*table;
    int size;

    ht(){
        size=10;
        table=new hashNode[size];
    }
    void insert(int id){
        int count=0;
        int index=id%size;
        while(table[index].status==1 && count<size){
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
        int probe=0;
        for(int i=0;i<size;i++){
            probe++;
            if(table[index].status==0){
                break;
            }

            if(table[index].status==1 && table[index].reqId==id){
                cout<< "Search "<<id<<": Found at Index "<<index<<" ,Probes : "<<probe<<endl;
                return;
            }
            index=(index+1)%size;
        }
        cout<<"Not found"<<", Probes : "<<probe<<endl;
    }
    void search(){
        cout<<endl<<endl<<"Enter q ( number of hash searches ):"<<endl;
        int q;
        cin>>q;
        cout<<"Enter "<<q<<" search keys : key1 key2 ..."<<endl;
        int keys[q];
        for(int i=0;i<q;i++){
            cin>>keys[i];
        }
        cout<<endl<<endl<<"HASH SEARCH RESULTS :"<<endl;
        for(int i=0;i<q;i++){
            search_helper(keys[i]);
        }
    }
    void print(){
        cout<<endl<<"FINAL HASH TABLE :"<<endl;
        for(int i=0;i<size;i++){
            cout<<i<<" : ";
            if(table[i].status==1){
                cout<<table[i].reqId<<endl;
            }
            else if(table[i].status==0){
                cout<<"EMPTY"<<endl;
            }
            else if(table[i].status==2){
                cout<<"DELETED"<<endl;
            }
        }
    }
    void deleteById(int id){
        int index=id%size;
       if(table[index].status==1){
         while(table[index].status==1 && table[index].reqId!=id){
            index=(index+1)%size;
        }
        index[table].reqId=-1;
        index[table].status=2;

        print();        
       }

       else{
        cout<<" Not Found "<<endl;
       }
    }
};

class Counter {
public:
    int counterID;
    int assignedTickets[10]; // Max capacity is n=10 
    int ticketCount;         // Number of tickets currently held
    Counter* next;

    Counter(int id) {
        counterID = id;
        ticketCount = 0;
        next = NULL;
    }
};
class cll{
public:
    Counter* head;
    Counter* currentPointer; // Starts at Counter 1 
    int totalK;              // Number of counters (k)

    cll(int k) {
        totalK = k;
        head = NULL;
        currentPointer = NULL;

        if (k <= 0) {
            return;
        }

        Counter* tail = NULL;
        for (int i = 1; i <= k; i++) {
            Counter* newNode = new Counter(i);
            if (head == NULL) {
                head = newNode;
            } 
            else {
                tail->next = newNode;
            }
            tail = newNode;
        }

        if (tail != NULL) {
            tail->next = head;
        }

        currentPointer = head;
    }

    // Part C.1 & C.2: Append ticket and move pointer round-robin [cite: 91, 92]
    void insert(int ticketID) {
        if (currentPointer != NULL) {
            // Append ticketID to the current counter [cite: 91]
            currentPointer->assignedTickets[currentPointer->ticketCount] = ticketID;
            currentPointer->ticketCount++;

            // Move the pointer to the next counter node 
            currentPointer = currentPointer->next;
        }
    }

    // Part C.3: Print the final counter logs [cite: 93, 94]
    void print() {
        cout << "CIRCULAR COUNTER LOG :" << endl; // Required heading [cite: 94]
        Counter* temp = head;

        for (int i = 0; i < totalK; i++) {
            cout << "Counter " << temp->counterID << ": ";

            if (temp->ticketCount == 0) {
                cout << "EMPTY"; // Print EMPTY if no tickets assigned 
            } else {
                for (int j = 0; j < temp->ticketCount; j++) {
                    cout << temp->assignedTickets[j];
                    // Space-separated with no trailing space 
                    if (j < temp->ticketCount - 1) {
                        cout << " ";
                    }
                }
            }
            cout << endl;
            temp = temp->next; // Move to next for traversal [cite: 93]
        }
    }
};
class bstNode{
    public:
    int reqId;
    bstNode*left;
    bstNode*right;
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
    bstNode* insert(bstNode*root ,int id){
        bstNode*newNode=new bstNode(id);
        if(root==NULL){
            root=newNode;
        }
        else if(id<root->reqId){
            root->left=insert(root->left,id);
        }
        else{
            root->right=insert(root->right,id);
        }
        return root;
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
        cout<<endl<<endl<<"BST TRAVERSALS :"<<endl;
        cout<<"Preorder :";
        preorder(root);
        cout<<endl<<"Inorder :";
        inorder(root);
        cout<<endl<<"Postorder :";
        postorder(root);
    }

};
int main(){
    cout<<"Enter n ( number of tickets ) :"<<endl;
    int n;
    cin>>n;
    cout<<"Enter "<<n<<" tickets ( ticketID type time counterNo ) :"<<endl;
    Ticket*arr=new Ticket[n];
    for(int i=0;i<n;i++){
        cin>>arr[i].ticketID>>arr[i].type>>arr[i].time>>arr[i].counterNo;
    }
    for(int i=0;i<n;i++){
        Ticket key=arr[i];
        int j=i-1;
        while(j>=0 && ((arr[j].type>key.type) || (arr[j].type==key.type && arr[j].time>key.time) || (arr[j].type==key.type && arr[j].time==key.time && arr[j].ticketID>key.ticketID))){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
    stack s(n);
    queue q(n);
    ht ht;
    bst bst;
    cll cll(3);
    cout<<endl<<"SORTED TICKETS :"<<endl;
    for(int i=0;i<n;i++){
        cout<<arr[i].ticketID<<" "<<arr[i].type<<" "<<arr[i].time<<arr[i].counterNo<<endl;
        if(arr[i].type==1){
            s.push(arr[i].ticketID);
        }
        else{
            q.enqueue(arr[i].ticketID);
        }
    }
    int trace[n];
    int i=0;
    cout<<endl<<"PROCESSING TRACE :"<<endl;
    while(!s.isEmpty() || !q.isEmpty()){
            if(!s.isEmpty()){
            int process=s.pop();
            trace[i]=process;
            cout<<"Serve : "<<process<<"  | Stack : ";
            s.print();
            cout<<" | Queue : ";
            q.print();
            cout<<endl;
        }
        else{
            int process=q.dequeue();
            trace[i]=process;
            cout<<"Serve : "<<process<<"  | Stack : ";
            s.print();
            cout<<" | Queue : ";
            q.print();
            cout<<endl;
        }
        i++;
        }
        for(int i=0;i<n;i++){
        ht.insert(trace[i]);
        cll.insert(trace[i]);
        bst.root=bst.insert(bst.root,trace[i]);
    }
    ht.search();
    ht.deleteById(205);
    cll.print();
    bst.print();
}
