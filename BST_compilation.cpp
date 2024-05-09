//create a bst. print numbers in ascending and descending order(iterative method).
//min max value in tree and max number of comparisons req 
//searching and finding number of comparisons

#include <iostream>
#include <stack>
using namespace std;

class Node{
public:
    int data;
    Node* left;
    Node* right;

    Node(int val){
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class BST{
public:
    Node* root;
    BST(){
        root = nullptr;
    }

    Node* InsertBst(Node* root, int val){
        if(root == nullptr){
            root = new Node(val);
        }
        else if(val > root->data){
            root->right = InsertBst(root->right, val);
        }
        else{
            root->left = InsertBst(root->left, val);
        }
        return root;
    }


    Node* DeleteNode(Node* root, int key){
        if(root == nullptr){
            return nullptr;
        }

        //reach till that node first
        if(key > root->data){
            root->right = DeleteNode(root->right,key);
            return root;
        }

        else if(key < root->data){
            root->left = DeleteNode(root->left,key);
            return root;
        }

        if(root->left == nullptr){
            Node* temp = root->right;
            delete root;
            return temp;
        }

        if(root->right == nullptr){
            Node* temp = root->left;
            delete root;
            return temp;
        }

        //case for 2 child nodes
        Node* succ = root->right;
        Node* succpar = root;

        while(succ->left != nullptr){  
            succpar = succ;
            succ = succ->left;
        }

        //copy succ's data in root
        root->data = succ->data;

        if(succpar->left == succ){
            succpar->left = succ->right;
        }
        else{
            succ->right = succ->right;
        }

        delete succ;
        return root;

    }

    void Ascending(Node* root){
        stack<Node*> stack;
        Node* curr = root;

        while(curr != nullptr || stack.size() != 0){
            while(curr != nullptr){
                stack.push(curr);
                curr = curr->left;
            }

            curr = stack.top();
            stack.pop();
            cout << curr->data << " ";

            curr = curr->right;
        }
    }

    void Descending(Node* root){
        stack<Node*> stack;
        Node* curr = root;

        while(curr != nullptr || stack.size() != 0){
            while(curr != nullptr){
                stack.push(curr);
                curr = curr->right;
            }

            curr = stack.top();
            stack.pop();
            cout << curr->data << " ";

            curr = curr->left;
        }
    }

    void CreateBst(){
        cout <<"Enter data to put in BST(-1 to stop): ";
        int data;
        cin>> data;

        while(data != -1){
            root = InsertBst(root,data);
            cout<< "Enter data: ";
            cin>> data;
        }
    }

    //search an element in BST and returns the number of comparisons
    int SearchBst(Node* root, int key){
        int comparisons = -1;
        Node* curr = root;
        while(curr != nullptr){
            comparisons++;
            if(curr->data == key){
                return comparisons;
            }
            else if (curr->data > key){
                curr = curr->left;
            }
            else{
                curr = curr->right;
            }
        }
        return -1;
    }

    Node* MinValue(Node* root){
        if(root == nullptr){
            return nullptr;
        }

        Node* curr = root;

        while(curr->left != nullptr){
            curr = curr->left;
        }
        return curr;
    }

    int BinaryTreeHeight(Node* root){
    if(root == NULL){
        return 0;
    }
    else{
        int LeftHeight = BinaryTreeHeight(root->left);
        int RightHeight = BinaryTreeHeight(root->right);

        if(LeftHeight>RightHeight){
            return (LeftHeight+1);
        }
        else{
            return (RightHeight+1);
        }
    }
    }

    void swap(Node* root){
        if(root == NULL){
            return;
        }
        else{
            swap(root->left);
            swap(root->right);
            Node* temp=root->left;
            root->left=root->right;
            root->right=temp;
        }
    }

    void LevelOrder(Node* root){
        int h = BinaryTreeHeight(root);
        for (int i=0; i<h; i++){
            cout << "\nElements in level "<<i<<" are: ";
            currlevel(root, i+1);
            
        }
    }

    void currlevel(Node* root, int l){
        if(root == nullptr){
            return ;
        }

        if(l == 1){
            cout << root->data<< " ";
        }
        else if(l > 1){
            currlevel(root->left, l-1);
            currlevel(root->right, l-1);
        }
    }

    Node* getRoot(){
        return root;
    }

    Node* Insert(int data){
        return InsertBst(root, data);
    }

    Node* Delete(int data){
        return DeleteNode(root, data);
    }
};

int main(){
    BST bst;

    bst.CreateBst();

    cout<<"Enter data to insert: ";
    int data1;
    cin>> data1;
    bst.Insert(data1);

    bst.Ascending(bst.getRoot());
    bst.Descending(bst.getRoot());

    //cout<<"Enter key to search: ";
    //int key;
    //cin>> key;
    //int comparisons = bst.SearchBst(bst.getRoot(),key);
    //cout << "The key "<< key <<" found in "<< comparisons <<" comparisons" << endl;

    Node* curr = bst.MinValue(bst.getRoot());
    cout<< "Min value is: " << curr->data<< endl;

    //int nodes = bst.BinaryTreeHeight(bst.getRoot());
    //cout << nodes<< endl;

    cout<<"Enter data to delete: ";
    int data2;
    cin>> data2;
    bst.Delete(data2);

    bst.Ascending(bst.getRoot());
    //swapping the tree
    //bst.swap(bst.getRoot());

    //print level order
    //bst.LevelOrder(bst.getRoot());
};

