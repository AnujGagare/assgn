#include<iostream>
#include <stack>

using namespace std;

class Node{
    public:
        int data;
        Node* left;
        Node* right;

        Node(int d){
            data = d;
            left = nullptr;
            right = nullptr;
        }
};

Node* CreateBinaryTree(Node* root){
    int data;
    cout<<"Enter Data: ";
    cin>>data;

    root = new Node(data);

    if(data == -1){
        return NULL;
    }

    cout<<"Enter the data for left root: "<<data<<endl;
    root->left=CreateBinaryTree(root->left);

    cout<<"Enter the data for right root: "<<data<<endl;
    root->right = CreateBinaryTree(root->right);

    return root;
}

void DisplayPreOrder(Node* root){
    if(root == NULL){
        return ;
    }
    cout<<root->data<<"  ";
    DisplayPreOrder(root->left);
    DisplayPreOrder(root->right);
}
/*
1.Create an empty stack nodeStack and push root node to stack. 
2.Do the following while nodeStack is not empty. 
    a.Pop an item from the stack and print it. 
    b.Push right child of a popped item to stack 
    c.Push left child of a popped item to stack

            10
          /   \
        8      2
      /  \    /
    3     5  4

stack = 
o/p = 10 8 3 5 2 4
*/

void IterativePreorder(Node* root){
    stack<Node*> stackPreorder;
    stackPreorder.push(root);
    cout<< "*************";
    while(stackPreorder.size()!= 0 ){
        Node* tempRoot = stackPreorder.top();
        stackPreorder.pop();
        cout << tempRoot->data;

        if(tempRoot->right != nullptr){
            stackPreorder.push(tempRoot->right);
        }
        
        if(tempRoot->left != nullptr){
            stackPreorder.push(tempRoot->left);
        }

    }
    cout<< "*************";
}

/*create an empty stack
push the root node in the stack
loop while stack is not empty
pop a node from stack and display its data
push its right and left children in the stack

*/


void DisplayInOrder(Node* root){
    if(root == NULL){
        return ;
    }
    DisplayInOrder(root->left);
    cout<<root->data<<"  ";
    DisplayInOrder(root->right);
}

/*

            10
          /   \
        8      2
      /  \    /
    3     5  4
in stack right root left
o/p = 3 8 5 10 4 2 9 100
stack = 2   
o/p = 3 8 5 10 4 2
1.right traversal until right is null
*/

/* create a empty stack
set current as root
while majha curr is not null push curr in stack and curr = curr->left
print the top element
pop a element and set curr = curr->right

*/

void IterativeInorder(Node* root){
    stack<Node*> stackInorder;
    Node* current = root;
    cout << "**********";
    while(current != nullptr || stackInorder.empty() == false){
        //left traversal condition
        while(current != nullptr){
            stackInorder.push(current);
            current = current->left;  
        }

        Node* top = stackInorder.top();
        cout << top->data << " ";
        stackInorder.pop();
        current = top->right;       
    }
    cout << "**********";
}


/*Postorder:
1. create 2 empty stacks
push root in stack 1
while stack1 is not empty
pop a node from stack1 and push in stack2
push the left and right children of popped node to stack1 if not null
display the elements of stack2
*/
void DisplayPostOrder(Node* root){
    if(root == NULL){
        return ;
    }
    DisplayPostOrder(root->left);
    DisplayPostOrder(root->right);
    cout<<root->data<<"  ";
    }
/*

            10
          /   \
        8      2
      /  \    /
    3     5  4
post order = 3 5 8 4 2 10


traverse left subtree (curr= curr -> left)
pop
if pop->right != null then curr = pop-> right, push right in stack
else print top

1. stack = [10 ] 
curr = 8
op= 3 5
*/

void IterativePostorder(Node* root){
    //place root in the first stack
    stack<Node*> stack1;
    stack<Node*> stack2;

    stack1.push(root);
    cout << "**********";
    while(stack1.empty() == false){
        Node* top = stack1.top();
        stack1.pop();
        stack2.push(top);
        if(top->left != nullptr){
            stack1.push(top->left);
        }
        
        if(top->right != nullptr){
            stack1.push(top->right);
        }      
    }

    while(stack2.size() != 0){
        cout << stack2.top()->data << " ";
        stack2.pop();
    }
    cout << "**********";

}
    
int getLeafNodeCount(Node* root){
    if(root == NULL){
        return 0;
    }
    if(root->left == NULL && root->right==NULL){
        return 1;
    }
    
    return getLeafNodeCount(root->left) + getLeafNodeCount(root->right);
}


/*
           10
          /   \
        8      2
      /  \    /
    3     5  4

*/

 
int countInternalNodes(Node* root){
    if(root == NULL || (root->left == NULL && root->right == NULL)){
        return 0;
    }
    else{
        cout<<"The Internal nodes in tree are: ";
        cout <<root->data<< " "<<endl;
        cout <<"Number of Internal nodes in tree are: ";
        return 1 + countInternalNodes(root->left) + countInternalNodes(root->right);
    }
    
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

Node* CopyBinaryTree(Node* root){
    if(root == NULL){
        return NULL;
    }
    
    Node* copy_tree = new Node(root->data);

    copy_tree->left = CopyBinaryTree(root->left);
    copy_tree->right = CopyBinaryTree(root->right);

    return copy_tree;
}

void swapBinaryTree(Node* root) {
    if (root == nullptr) {
        return;
    }

    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;

    swapBinaryTree(root->left);
    swapBinaryTree(root->right);
}

void deleteTree(Node* node) 
{ 
    if (node == NULL) return; 

    deleteTree(node->left); 
    deleteTree(node->right); 
    
    cout << "\n Deleting node: " << node->data; 
    delete node;
} 

int main(){
    Node* root;
    root = NULL;
    root = CreateBinaryTree(root);

    Node* copy = CopyBinaryTree(root);
    
    cout<<"PreOrder: ";
    DisplayPreOrder(root);
    //IterativePreorder(root);
    cout<<endl;

    cout<<"InOrder: ";
    DisplayInOrder(root);
    //IterativeInorder(root);
    cout<<endl;

    cout<<"PostOrder: ";
    DisplayPostOrder(root);
    IterativePostorder(root);
    cout<<endl;

    cout<<"Number of leaf nodes in tree are: "<<getLeafNodeCount(root)<<endl;

    cout<<countInternalNodes(root)<<endl;

    cout<<"Height of Binary Tree is: "<<BinaryTreeHeight(root)<<endl;

    cout<<"Inorder Traversal of a copied tree is: ";
    DisplayInOrder(copy);
    cout<<endl;

    swapBinaryTree(root);
    cout<<"Inorder Traversal of a swapped tree: ";
    DisplayInOrder(root);
    cout<<endl;

    deleteTree(root);
    root = NULL;
    cout<<endl;
    cout<<"Tree Deleted"<<endl;

    return 0;
}
