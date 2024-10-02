/***************************************************************************************
 * This implementation is based on the lecture notes by Cristina Gomes Fernandes,   
 * titled "Persistent Data Structures", from the Advanced Data Structures course, 2023.
 * The link to this course is:
 * https://www.ime.usp.br/~cris/aulas/23_2_6957/
 ***************************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

class Node{
    public:
        int key;
        int priority;

        Node *left;
        Node *right;

        Node() { 
            left = nullptr;
            right = nullptr;
            priority = 0;
        }

        Node(int key){
            left = nullptr;
            right = nullptr;
            priority = rand() % 1000;
            this->key = key;
        }

        ~Node(){
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
            new_node->priority = this->priority;
            new_node->key = this->key;
            return new_node;
        }
};

class PersistentTreap {
    private: 
        Node *root;

        Node* right_rotation(Node *node){
            Node *new_root = node->left;
            Node *son = new_root->right;

            new_root->right = node;
            node->left = son;

            return new_root;
        }

        Node* left_rotation(Node *node){
            Node *new_root = node->right;
            Node *son = new_root->left;

            new_root->left = node;
            node->right = son;

            return new_root;
        }

        Node* put(Node *node,int key){
            if(node == nullptr){
                Node *insert = new Node(key); 
                return insert;
            }
            Node *new_node = node->copy();
            if(new_node->key > key){
                new_node->left = put(new_node->left,key);
                if (new_node->left->priority > new_node->priority){
                    new_node = right_rotation(new_node);
                }
            } 
            else{
                new_node->right = put(new_node->right,key);
                if (new_node->right->priority > new_node->priority){
                    new_node = left_rotation(new_node);
                }
            }
            return new_node;
        }

        Node* remove_rec(Node *node,int key, int copy){
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

                Node *current_node = node;
                if(copy == 0){
                    Node *new_node = node->copy();
                    current_node = new_node;
                }

                if(current_node->right->priority > current_node->left->priority){
                    current_node->right = current_node->right->copy();
                    Node *aux_node = left_rotation(current_node);
                    aux_node->left = remove_rec(aux_node->left, key,1);
                    return aux_node;
                }
                else{
                    current_node->left = current_node->left->copy();
                    Node *aux_node = right_rotation(current_node);
                    aux_node->right = remove_rec(aux_node->right, key,1);
                    return aux_node;
                }
            }
            Node *new_node = node->copy();
            if(new_node->key > key){
                new_node->left = remove_rec(new_node->left, key,0);
                return new_node;
            }
            else{
                new_node->right = remove_rec(new_node->right, key,0);
                return new_node;
            }
        }

        void debug_rec(Node *u, int i){
            if(u->left != nullptr){
                debug_rec(u->left, i+3);
            }

            for(int j=0;j<i;j++){
                cout << " ";
            }
            cout << u->key << " " << u->priority;
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

    public:
        PersistentTreap() {
            root = nullptr;
        }
        PersistentTreap(Node *root) {
            root = root;
        }
        ~PersistentTreap() {
            delete root;
        }

        bool is_null(){
            if(root == nullptr){
                return true;
            }
            return false;
        }

        PersistentTreap *add(int key){
            Node *new_root = new Node();
            new_root = put(this->root,key);
            PersistentTreap *new_treap = new PersistentTreap(new_root); 
            return new_treap;
        }

        PersistentTreap *remove(int key){
            Node *new_root = new Node();
            new_root = remove_rec(this->root, key,0);
            if(new_root == nullptr){
                PersistentTreap *null_treap = new PersistentTreap();
                return null_treap;
            }
            PersistentTreap *new_treap = new PersistentTreap(new_root); 
            return new_treap;
        }

        void print(){
            if(!is_null()){
                debug_rec(this->root,0);
            }
            else{
                cout << "Empty treap!" << endl;
            }
        }

        int print_min(){
            if(root == nullptr){
                cout << "Empty treap!" << endl;
                return -1;
            }
            return min(this->root);
        }

        int print_search(int x){
            return (search(this->root, x)? 1 : 0);
        }
};

void instructions(){
    cout << "0         means instructions" << endl;
    cout << "1 <t> <x> means add(t, x)" << endl;
    cout << "2 <t> <x> means remove(t, x)" << endl;
    cout << "3 <t> <x> means println(search(t, x)? 1 : 0)" << endl;
    cout << "4 <t>     means println(min(t))" << endl;
    cout << "5 <t>     means print(t)" << endl;
    cout << "6         means printAll()" << endl;
}

int main(){
    srand(time(0));
    vector<PersistentTreap*> vector;
    int numero, t, x;
    PersistentTreap *initial = new PersistentTreap();
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
            vector.push_back(vector[t]->add(x));
            break;
        case 2:
            cin >> t;
            cin >> x;
            vector.push_back(vector[t]->remove(x));
            break;
        case 3:
            cin >> t;
            cin >> x;
            cout << vector[t]->print_search(x) << endl;
            break;
        case 4:
            cin >> t;
            cout << vector[t]->print_min() << endl;;
            break;
        case 5:
            cin >> t;
            if(t < 0 || vector.size() < t){
                cout << "invalid treap!" << endl;
            }
            else{
                vector[t]->print();
            }
            break;
        case 6:
            cout << "--------------------------" << endl;
            for(int i = 0; i < vector.size(); i++){
                cout << "PRINT TREAP  " << i << ": " << endl;
                if(vector[i]->is_null()){
                    cout << "Treap " << i << " is Empty!" << endl;
                }
                else{
                    vector[i]->print();
                }
                if(i < vector.size() - 1){
                    cout << endl;
                }
                else{
                    cout << "--------------------------" << endl;
                }
            }
            break;
        }
    }
}
