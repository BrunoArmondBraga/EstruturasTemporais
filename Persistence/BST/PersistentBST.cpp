/***************************************************************************************
 * Implementation made by Bruno Braga.
 * This implementation is based on the functional technique described on the Chapter 7
 * of Yan Couto's Master's thesis.
 * His thesis can be acessed here:
 * https://www.teses.usp.br/teses/disponiveis/45/45134/tde-24092019-181655/pt-br.php
 ***************************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

class Node{
    public:
        int key;
        Node *left;
        Node *right;

        Node() { 
            left = nullptr;
            right = nullptr;
        }

        Node(int key){
            left = nullptr;
            right = nullptr;
            this->key = key;
        }

        ~Node() {
            if(left != nullptr){
                delete left;
            }
            if(right != nullptr){
                delete right;
            }
        }

        Node *copy(){
            Node *new_node = new Node();
            new_node->left = this->left;
            new_node->right = this->right;
            new_node->key = this->key;
            return new_node;
        }
};

class BST {
    private: 
        Node *root;

        Node* put(Node *node,int key){
            if(node == nullptr){
                Node *insert = new Node(key); 
                return insert;
            }
            Node *new_node = node->copy();
            if(new_node->key > key){
                new_node->left = put(new_node->left,key);
                return new_node;
            } 
            else{
                new_node->right = put(new_node->right,key);
                return new_node;
            }
        }

        bool search(Node *u, int x){
            if(u == nullptr){
                return false;
            }
            if(u->key == x){
                return true;
            }
            else if(u->key > x){
                return search(u->left,x);
            }
            else{
                return search(u->right,x);
            }
        }

        void debug_rec(Node *u, int i){
            if(u->left != nullptr){
                debug_rec(u->left, i+3);
            }

            for(int j=0;j<i;j++){
                cout << " ";
            }
            cout << u->key;
            cout << endl;

            if(u->right != nullptr){
                debug_rec(u->right, i+3);
            }
            
        }   

        int min(Node *u){
            if(u->left == nullptr){
                return u->key;
            }
            return min(u->left);
        }    

        Node* remove_rec(Node *node,int key){
            if(node == nullptr){
                return nullptr;
            }
            if(node->key == key){
                if(node->right == nullptr){
                    return node->left;
                }
                else if(node->left == nullptr){
                    return node->right;
                }
                else{
                    //case with right and left
                    int last = min(node->right);
                    Node *final_node = node->copy();
                    final_node->key = last;
                    final_node->right = remove_rec(final_node->right,last);
                    return final_node;
                }

                Node *current_node = node;
            }
            Node *new_node = node->copy();
            if(new_node->key > key){
                new_node->left = remove_rec(new_node->left, key);
                return new_node;
            }
            else{
                new_node->right = remove_rec(new_node->right, key);
                return new_node;
            }
        }
        
    public:
        BST() {
            root = nullptr;
        }

        BST(Node *u) {
            root = u;
        }

        ~BST() {
            delete root;
        }

        BST *add(int key){
            Node *new_root = new Node();
            new_root = put(this->root,key);
            BST *new_bst = new BST(new_root); 
            return new_bst;
        }

        void print(){
            if(root == nullptr){
                cout << "nullptr" << endl;
            }
            else{
                debug_rec(root,0);
            }
        }

        int print_search(int x){
            return (search(this->root, x)? 1 : 0);
        }

        int print_min(){
            if(root == nullptr){
                cout << "Empty BST!" << endl;
                return -1;
            }
            return min(this->root);
        }

        BST *remove(int key){
            Node *new_root = new Node();
            new_root = remove_rec(this->root, key);
            if(new_root == nullptr){
                BST *null_bst = new BST();
                return null_bst;
            }
            BST *new_bst = new BST(new_root); 
            return new_bst;
        }
};

void instructions(){
    cout << "0         means instructions()" << endl;
    cout << "1 <t> <x> means add(t, x)" << endl;
    cout << "2 <t>     means remove(t, x)" << endl;
    cout << "3 <t> <x> means print(search(t, x))" << endl;
    cout << "4 <t>     means print(min(t))" << endl;
    cout << "5 <t>     means print(t)" << endl;
    cout << "6         means printAll()" << endl;
}

int main(){
    vector<BST*> vector;
    int numero, t, x;
    BST *initial = new BST();
    vector.push_back(initial);
    instructions();

    while(cin >> numero){
        switch (numero)
        {
        case 0:
            instructions();
            break;
        case 1:
            cin >> t;
            cin >> x;
            if(t > vector.size() - 1){
                cout << "There is no deque in time " << t << endl;
            }
            else{
                vector.push_back(vector[t]->add(x));
            }
            break;
        case 2:
            cin >> t;
            cin >> x;
            if(t > vector.size() - 1){
                cout << "There is no deque in time " << t << endl;
            }
            else{
                vector.push_back(vector[t]->remove(x));
            }
            break;
        case 3:
            cin >> t;
            cin >> x;
            if(t > vector.size() - 1){
                cout << "There is no deque in time " << t << endl;
            }
            else{
                cout << vector[t]->print_search(x) << endl;
            }
            break;
        case 4:
            cin >> t;
            if(t > vector.size() - 1){
                cout << "There is no deque in time " << t << endl;
            }
            else{
                cout << vector[t]->print_min() << endl;;
            }
            break;
        case 5:
            cin >> t;
            if(t > vector.size() - 1){
                cout << "There is no deque in time " << t << endl;
            }
            else{
                vector[t]->print();
            }
            break;
        case 6:
            for(int i = 0; i < vector.size(); i++){
                cout << "Print BST  " << i << ": " << endl;
                vector[i]->print();
                cout << endl;
            }
            cout << "--------------------------" << endl;
            break;
        }
    }
}