#include <bits/stdc++.h>
using namespace std; 

class Node {
public:
    int key;
    string value;
    Node *next;
    Node(int k, string v) : key(k), value(v), next(nullptr) {}  //parameterized constructor
};

class Dictionary {
private:
    Node **table; /*This is a pointer to a pointer to Node.        ****DOUBT****  pointer of Node* type
                    This suggests that table is intended to be an array of pointers to Node objects.
                    Each element of this array represents a bucket in the hash table. 
                    Each bucket may contain multiple Node objects, forming a linked list in case of collision resolution. */
    int tableSize;
    /*0->first elemen
    1
    2
    3
    */

    int hash(int key) {
        return (3 * key + 5) % tableSize;
    }


public:
    Dictionary(int n){
        tableSize = n;
        table = new Node *[tableSize];
        for (int i = 0; i < tableSize; i++) {
            table[i] = nullptr;
        }
    }      //******DOUBT******
        
        
    

    void insert(int key, string value) {
        int hashAddress = hash(key);
        if (table[hashAddress] == nullptr) {
            table[hashAddress] = new Node(key, value); //parameterized constructor will be called
        } else {
            Node* curr = table[hashAddress];
            while(curr->next != nullptr){
                curr = curr->next;
            }
            Node* newNode = new Node(key, value);
            curr->next = newNode;
            //insertLL(table[hashAddress], key, value);
        }
    }

    void display() {
        for (int i = 0; i < tableSize; i++) {
            cout << "|-------|\n|   " << i << "   | -> ";
            Node* curr = table[i];
            while (curr != nullptr) {
                cout << "(" << curr->key << ", " << curr->value << ") ->";
                curr = curr->next;
            }
            
            cout << endl;
        }
        cout << "|_______|";
        cout << endl << endl;
    }

    Node* search(int key1) {
        int hashAddress = hash(key1);
        Node* curr = table[hashAddress];
        while(curr != nullptr){
            if(curr->key == key1){
                return curr;
            }
            curr = curr->next;
        }
        return nullptr;   
    }

    void del(int key) {
        int hashAddress = hash(key);
        //deleteLL(hashAddress, table[hashAddress], key);
        Node* headNode = table[hashAddress];
        //void deleteLL(int index, Node *headNode, int key) {
        if (headNode == NULL)
            cout << "No such record exists to be deleted!" << endl;
        else if (headNode->key == key) {
            Node *nextNode = headNode->next;
            delete table[hashAddress];
            table[hashAddress] = nextNode;
            cout << "Deleted." << endl;
        } 
        else {
            Node *currentNode = headNode;
            Node *prevNode = NULL;
            while (currentNode != nullptr) {
                if (currentNode->key == key)
                    break;
                prevNode = currentNode;
                currentNode = currentNode->next;
            }

            if (currentNode != nullptr) {
                prevNode->next = currentNode->next;
                delete currentNode;
            } 
            else{
                cout << "No such element" << endl;
            }
                
        }
    }
    
};

int main() {
    Dictionary dict(10);

    while (true) {
        cout << "1. Insert key:value pair" << endl;
        cout << "2. Search for value with key" << endl;
        cout << "3. Delete the key:value pair" << endl;
        cout << "4. Display the dictionary" << endl;
        cout << "Enter your choice (any other input to exit): ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            int key;
            string value;
            cout << "Enter key: ";
            cin >> key;
            cout << "Enter corresponding value: ";
            cin >> value;
            dict.insert(key, value);
        } else if (choice == 2) {
            int key;
            cout << "Enter key: ";
            cin >> key;
            Node* nodeFound = dict.search(key);
             
            if (nodeFound == nullptr){
            cout << "No record found" << endl;
            }
            else {
            cout << "\nKey: " << key << endl;
            cout << "Value: " << nodeFound->value << endl;
            }

        } else if (choice == 3) {
            int key;
            cout << "Enter key: ";
            cin >> key;
            dict.del(key);
        } else if (choice == 4) {
            dict.display();
        } else
            break;
    }

    return 0;
}