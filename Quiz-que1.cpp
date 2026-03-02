

/*

Based on the provided lab examination document, here is a point-by-point breakdown of exactly what you need to do to build this Student Service Portal backend:

**Initial Setup**
* Write a single C++ program that takes an initial input of $n$ (number of requests), followed by $n$ lines of `reqID`, `priority` (1-5), and `time`.


**Part A: Insertion Sort**
* Store the $n$ requests in an array.
* Sort the array using the Insertion Sort algorithm.
* Sort primarily by `priority` in ascending order (where 1 is highest priority and 5 is lowest).
* If two requests have the same priority, sort them by `time` in ascending order (smaller time comes first).
* Print the sorted list.



**Part B: Stack & Queue Processing**
* Take the sorted array from Part A.
* Push all emergency requests (where `priority == 1`) into a Stack.
* Enqueue all standard requests (where `priority > 1`) into a Queue.
* Process the requests one by one: always pop from the Stack first; if the Stack is empty, dequeue from the Queue.
* Print a trace showing the currently processed ID and the contents of both the Stack and the Queue after every single step.



**Part C: Doubly Linked List (DLL)**
* As you process each `reqID` in Part B, insert it at the tail of a Doubly Linked List to maintain an audit log.
* Take a new input, `reqID_del`, from the user.
* Print the DLL in the forward direction, then in the backward direction.
* Delete the node matching `reqID_del` and print the DLL one last time.



**Part D: Hash Table (Linear Probing)**
* Insert all the processed `reqID`s into a Hash Table of size $m=10$.
* Use the hash function $h(k) = k \bmod 10$ and resolve any collisions using Linear Probing.
* Take inputs for $q$ (number of searches), followed by $q$ search keys, and finally one key to delete (`kdel`).
* Search for each of the $q$ keys, printing whether it was found, the index, and the total number of probes it took.
* Delete `kdel` using "tombstone" marking (marking the slot as DELETED rather than completely emptying it).
* Print the final state of the entire Hash Table from index 0 to 9, showing values, EMPTY slots, and DELETED tombstones.



**Part E: Binary Search Tree (BST)**
* Build a Binary Search Tree by inserting the processed `reqID`s in the exact order they were processed in Part B.
* Perform and print three traversals of the BST: Preorder, Inorder, and Postorder.


*/








//student service portal

#include <iostream>
using namespace std;

// ==========================================
// DATA STRUCTURES & CLASSES
// ==========================================

// Structure for a Service Request
struct Request {
    int reqID;
    int priority;
    int time;
};

// 1. Stack (Array-based)
class Stack {
public:
    int* arr;
    int top;
    int space;

    Stack(int s) {
        space = s;
        arr = new int[space];
        top = -1;
    }
    bool isEmpty() { return top == -1; }
    void push(int d) {
        if (top < space - 1) arr[++top] = d;
    }
    int pop() {
        if (isEmpty()) return -1;
        return arr[top--];
    }
    void print() {
        if (isEmpty()) {
            cout << "Empty";
        } else {
            // Print top-to-bottom
            for (int i = top; i >= 0; i--) {
                cout << arr[i] << (i == 0 ? "" : " ");
            }
        }
    }
};

// 2. Queue (Simple Array-based for processing)
class Queue {
public:
    int* arr;
    int front;
    int rear;
    int size;

    Queue(int s) {
        size = s;
        arr = new int[size];
        front = -1;
        rear = -1;
    }
    bool isEmpty() { return front == -1 || front > rear; }
    void enqueue(int d) {
        if (front == -1) front = 0;
        arr[++rear] = d;
    }
    int dequeue() {
        if (isEmpty()) return -1;
        return arr[front++];
    }
    void print() {
        if (isEmpty()) {
            cout << "Empty";
        } else {
            // Print front-to-rear
            for (int i = front; i <= rear; i++) {
                cout << arr[i] << (i == rear ? "" : " ");
            }
        }
    }
};

// 3. Doubly Linked List Node & Class
class DLLNode {
public:
    int data;
    DLLNode* prev;
    DLLNode* next;

    DLLNode(int d) {
        this->data = d;
        this->prev = NULL;
        this->next = NULL;
    }
};

class DoublyLinkedList {
public:
    DLLNode* head;
    DLLNode* tail;

    DoublyLinkedList() { head = tail = NULL; }

    void insertTail(int d) {
        DLLNode* newNode = new DLLNode(d);
        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void deleteByID(int id) {
        DLLNode* temp = head;
        while (temp != NULL && temp->data != id) {
            temp = temp->next;
        }
        if (temp == NULL) return; // Not found

        if (temp->prev != NULL) temp->prev->next = temp->next;
        else head = temp->next; // Deleting head

        if (temp->next != NULL) temp->next->prev = temp->prev;
        else tail = temp->prev; // Deleting tail

        delete temp;
    }

    void displayForward() {
        DLLNode* temp = head;
        while (temp != NULL) {
            cout << temp->data;
            if (temp->next != NULL) cout << " <-> ";
            temp = temp->next;
        }
        cout << endl;
    }

    void displayBackward() {
        DLLNode* temp = tail;
        while (temp != NULL) {
            cout << temp->data;
            if (temp->prev != NULL) cout << " <-> ";
            temp = temp->prev;
        }
        cout << endl;
    }
};

// 4. Hash Table (Linear Probing)
class HashTable {
private:
    int table[10];
    int status[10]; // 0: EMPTY, 1: OCCUPIED, 2: DELETED
    int capacity;

public:
    HashTable() {
        capacity = 10;
        for (int i = 0; i < capacity; i++) {
            status[i] = 0; 
        }
    }

    void insert(int key) {
        int index = key % 10;
        for (int i = 0; i < capacity; i++) {
            int probeIdx = (index + i) % capacity;
            if (status[probeIdx] == 0 || status[probeIdx] == 2) {
                table[probeIdx] = key;
                status[probeIdx] = 1;
                return;
            }
        }
    }

    void search(int key) {
        int index = key % 10;
        int probes = 0;
        for (int i = 0; i < capacity; i++) {
            int probeIdx = (index + i) % capacity;
            probes++;
            if (status[probeIdx] == 0) {
                cout << "Search " << key << ": Not Found, Probes: " << probes << endl;
                return;
            }
            if (status[probeIdx] == 1 && table[probeIdx] == key) {
                cout << "Search " << key << ": Found at Index " << probeIdx << ", Probes: " << probes << endl;
                return;
            }
        }
        cout << "Search " << key << ": Not Found, Probes: " << probes << endl;
    }

    void deleteKey(int key) {
        int index = key % 10;
        for (int i = 0; i < capacity; i++) {
            int probeIdx = (index + i) % capacity;
            if (status[probeIdx] == 0) return; // Stop at empty
            if (status[probeIdx] == 1 && table[probeIdx] == key) {
                status[probeIdx] = 2; // Tombstone
                return;
            }
        }
    }

    void print() {
        cout << "FINAL HASH TABLE:" << endl;
        for (int i = 0; i < capacity; i++) {
            cout << i << ": ";
            if (status[i] == 0) cout << "EMPTY" << endl;
            else if (status[i] == 2) cout << "DELETED" << endl;
            else cout << table[i] << endl;
        }
    }
};

// 5. Binary Search Tree (BST)
class BSTNode {
public:
    int data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int val) {
        data = val;
        left = right = NULL;
    }
};

class BST {
public:
    BSTNode* root;
    BST() { root = NULL; }

    BSTNode* insert(BSTNode* node, int d) {
        if (node == NULL) return new BSTNode(d);
        if (d < node->data) node->left = insert(node->left, d);
        else if (d > node->data) node->right = insert(node->right, d);
        return node;
    }

    void preorder(BSTNode* node, bool& first) {
        if (node == NULL) return;
        if (!first) cout << " ";
        cout << node->data;
        first = false;
        preorder(node->left, first);
        preorder(node->right, first);
    }

    void inorder(BSTNode* node, bool& first) {
        if (node == NULL) return;
        inorder(node->left, first);
        if (!first) cout << " ";
        cout << node->data;
        first = false;
        inorder(node->right, first);
    }

    void postorder(BSTNode* node, bool& first) {
        if (node == NULL) return;
        postorder(node->left, first);
        postorder(node->right, first);
        if (!first) cout << " ";
        cout << node->data;
        first = false;
    }
};

// ==========================================
// MAIN DRIVER
// ==========================================

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;

    Request* arr = new Request[n];
    cout << "Enter " << n << " lines (reqID priority time):" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i].reqID >> arr[i].priority >> arr[i].time;
    }

    // --- PART A: Insertion Sort ---
    for (int i = 1; i < n; i++) {
        Request key = arr[i];
        int j = i - 1;
        // Compare priority first, then time if priorities are equal
        while (j >= 0 && (arr[j].priority > key.priority || 
              (arr[j].priority == key.priority && arr[j].time > key.time))) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }

    cout << "SORTED REQUESTS:" << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i].reqID << " " << arr[i].priority << " " << arr[i].time << endl;
    }

    // --- PART B: Stack & Queue Processing ---
    Stack s(n);
    Queue q(n);

    // Populate Data structures
    for (int i = 0; i < n; i++) {
        if (arr[i].priority == 1) s.push(arr[i].reqID);
        else q.enqueue(arr[i].reqID);
    }

    cout << "PROCESSING TRACE:" << endl;
    int* processedOrder = new int[n];
    int pIdx = 0;

    while (!s.isEmpty() || !q.isEmpty()) {
        int currentReq;
        if (!s.isEmpty()) {
            currentReq = s.pop();
        } else {
            currentReq = q.dequeue();
        }
        
        processedOrder[pIdx++] = currentReq;

        cout << "Process: " << currentReq << " | Stack: ";
        s.print();
        cout << " | Queue: ";
        q.print();
        cout << endl;
    }

    // --- PART C: Doubly Linked List ---
    int reqID_del;
    cin >> reqID_del;

    DoublyLinkedList dll;
    for(int i = 0; i < n; i++) {
        dll.insertTail(processedOrder[i]);
    }

    cout << "DLL FORWARD:" << endl;
    dll.displayForward();
    
    cout << "DLL BACKWARD:" << endl;
    dll.displayBackward();
    
    dll.deleteByID(reqID_del);
    cout << "DLL AFTER DELETION:" << endl;
    dll.displayForward();

    // --- PART D: Hash Table Rapid Lookup ---
    HashTable ht;
    for(int i = 0; i < n; i++) {
        ht.insert(processedOrder[i]);
    }

    int queries;
    cin >> queries;
    int* searchKeys = new int[queries];
    for(int i = 0; i < queries; i++) {
        cin >> searchKeys[i];
    }
    
    int kdel;
    cin >> kdel;

    cout << "HASH SEARCH RESULTS:" << endl;
    for(int i = 0; i < queries; i++) {
        ht.search(searchKeys[i]);
    }

    ht.deleteKey(kdel);
    ht.print();

    // --- PART E: Hierarchical View (BST) ---
    BST bst;
    for(int i = 0; i < n; i++) {
        bst.root = bst.insert(bst.root, processedOrder[i]);
    }

    cout << "BST TRAVERSALS:" << endl;
    
    bool first = true;
    cout << "Preorder: ";
    bst.preorder(bst.root, first);
    cout << endl;

    first = true;
    cout << "Inorder: ";
    bst.inorder(bst.root, first);
    cout << endl;

    first = true;
    cout << "Postorder: ";
    bst.postorder(bst.root, first);
    cout << endl;

    // Cleanup
    delete[] arr;
    delete[] processedOrder;
    delete[] searchKeys;

    return 0;
}
