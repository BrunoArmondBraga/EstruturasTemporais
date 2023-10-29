#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

class Node{
    private:
        
    public:
        int val;
        Node *esq;
        Node *dir;
        Node() { 
            esq = nullptr;
            dir = nullptr;
        };
        Node(int key){
            esq = nullptr;
            dir = nullptr;
            this->val = key;
        }
        ~Node() {
            if(esq != nullptr){
                delete esq;
            }
            if(dir != nullptr){
                delete dir;
            }
        }
        Node *copy(){
            Node *new_node = new Node();
            new_node->esq = this->esq;
            new_node->dir = this->dir;
            new_node->val = this->val;
            return new_node;
        }
};

class Abb {
    private: 
        Node *root;

        Node* put(Node *node,int val){
            if(node == nullptr){
                Node *insert = new Node(val); 
                return insert;
            }
            Node *new_node = node->copy();
            if(new_node->val > val){ //vai pra esquerda!
                new_node->esq = put(new_node->esq,val);
                return new_node;
            } 
            else{ //vai pra direita!
                new_node->dir = put(new_node->dir,val);
                return new_node;
            }
        }

        bool search(Node *u, int x){
            if(u == nullptr){
                return false;
            }
            if(u->val == x){
                return true;
            }
            else if(u->val > x){
                return search(u->esq,x);
            }
            else{
                return search(u->dir,x);
            }
        }

        void debug_rec(Node *u, int i){
            if(u->esq != nullptr){
                debug_rec(u->esq, i+3);
            }

            for(int j=0;j<i;j++){
                cout << " ";
            }
            cout << u->val;
            cout << endl;

            if(u->dir != nullptr){
                debug_rec(u->dir, i+3);
            }
            
        }   

        int min(Node *u){
            if(u->esq == nullptr){
                return u->val;
            }
            return min(u->esq);
        }    

        Node* remove_rec(Node *node,int val){
            if(node == nullptr){
                return nullptr;
            }
            if(node->val == val){
                //tratamento de deleção;
                if(node->dir == nullptr){
                    return node->esq;
                }
                else if(node->esq == nullptr){
                    return node->dir;
                }
                else{
                    //CASO COM DOIS FILHOS!!
                    int last = min(node->dir);
                    Node *final_node = node->copy();
                    final_node->val = last;
                    final_node->dir = remove_rec(final_node->dir,last);
                    return final_node;
                }

                Node *current_node = node;
            }
            Node *new_node = node->copy();
            if(new_node->val > val){ //vá pra esquerda!
                new_node->esq = remove_rec(new_node->esq, val);
                return new_node;
            }
            else{ //vá pra direita!
                new_node->dir = remove_rec(new_node->dir, val);
                return new_node;
            }
        }
        
    public:
        Abb() {
            root = nullptr;
        }
        Abb(Node *u) {
            root = u;
        }
        ~Abb() {
            delete root;
        }

        Abb *add(int val){
            Node *new_root = new Node();
            new_root = put(this->root,val);
            Abb *new_abb = new Abb(new_root); 
            return new_abb;
        }

        void print(){
            debug_rec(this->root,0);
        }

        int print_search(int x){
            return (search(this->root, x)? 1 : 0);
        }

        int print_min(){
            if(root == nullptr){
                cout << "ABB vazia!" << endl;
                return -1;
            }
            return min(this->root);
        }

        Abb *remove(int val){
            Node *new_root = new Node();
            new_root = remove_rec(this->root, val);
            if(new_root == nullptr){
                Abb *null_treap = new Abb();
                return null_treap;
            }
            Abb *new_treap = new Abb(new_root); 
            return new_treap;
        }
        
};

int main(){
    vector<Abb*> vector;
    int numero, t, x;
    Abb *initial = new Abb();
    vector.push_back(initial);

    while(cin >> numero){
        switch (numero)
        {
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
            vector[t]->print();
            break;
        case 6:
            for(int i = 1; i < vector.size(); i++){
                cout << "PRINTA A ABB  " << i << ": " << endl;
                vector[i]->print();
                cout << endl;
            }
            cout << "--------------------------" << endl;
            break;
        }
    }
}