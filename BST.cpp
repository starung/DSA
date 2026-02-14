#include<iostream>
using namespace std;

class Node{
    public:
    int data;
    Node*left;
    Node*right;

    Node(int val){
        this->data=val;
        this->left=this->right=NULL;
    }

    
};

class BST{
    public:
    Node*root;

    //Insertion
    Node* insert(Node*root,int d){
            if(root==NULL){
                Node*temp=new Node(d);
                return temp;
            }
            if(d<root->data){
                root->left=insert(root->left,d);
            }
            else{
                root->right=insert(root->right,d);
            }

            return root;
        }

        void inorder(Node*root){
        if(root==NULL){
            return ;
        }

        inorder(root->left);
        cout<<root->data<<" ";
        inorder(root->right);
    }

    void preorder(Node*root){
        if(root==NULL){
            return ;
        }
        cout<<root->data<<" ";
        inorder(root->left);
        inorder(root->right);
    }

    void postorder(Node*root){
        if(root==NULL){
            return ;
        }
        
        inorder(root->left);
        inorder(root->right);
        cout<<root->data<<" ";
    }

    Node* findMin(Node*root){
        while(root->left!=NULL){
            root=root->left;
        }
        return root;
    }
    Node* remove(Node*root,int key){
        if(root==NULL){
            return NULL;
        }

        if(key<root->data){
            root->left=remove(root->left,key);
        }
        if(key>root->data){
            root->right=remove(root->right,key);
        }
        else{
            //NO child
            if(root->left==NULL&&root->right==NULL){
                delete root;
            }

            //1 child
            if(root->left==NULL){
                Node*temp=root->right;
                delete root;
                return temp;
            }
            else if(root->right==NULL){
                Node*temp=root->left;
                delete root;
                return temp;
            }
            
            // 2 child
            else{
                Node*temp=findMin(root->right);
                root->data=temp->data;
                root->right=remove(root->right,temp->data);

            }


        }
    }
    

    
};
    

    


int main(){
    BST t;
    Node*root=NULL;
   root=t.insert(root,50);
   root=t.insert(root,50);
   root=t.insert(root, 76);
   root=t.insert(root, 89);
   root=t.insert(root, 45);
   t.inorder(root);
    cout<<endl<<root->data<<endl;
    t.preorder(root);
    cout<<endl;
    t.postorder(root);
}