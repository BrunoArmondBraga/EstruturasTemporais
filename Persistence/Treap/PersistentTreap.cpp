#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

class NodeTR{
    public:
        int val;
        NodeTR *esq;
        NodeTR *dir;
        int priority;

        NodeTR() { 
            esq = nullptr;
            dir = nullptr;
            priority = 0;
        }

        NodeTR(int val){
            esq = nullptr;
            dir = nullptr;
            priority = rand() % 1000;
            this->val = val;
        }

        ~NodeTR(){
            if(esq != nullptr){
                delete esq;
            }
            if(dir != nullptr){
                delete dir;
            }
        }
        
        NodeTR *copy(){
            NodeTR *new_node = new NodeTR();
            new_node->esq = this->esq;
            new_node->dir = this->dir;
            new_node->priority = this->priority;
            new_node->val = this->val;
            return new_node;
        }
};

class PersistentTreap {
    private: 
        NodeTR *raiz;

        NodeTR* right_rotation(NodeTR *node){
            NodeTR *new_root = node->esq;
            NodeTR *son = new_root->dir;

            new_root->dir = node;
            node->esq = son;

            return new_root;
        }

        NodeTR* left_rotation(NodeTR *node){
            NodeTR *new_root = node->dir;
            NodeTR *son = new_root->esq;

            new_root->esq = node;
            node->dir = son;

            return new_root;
        }

        NodeTR* put(NodeTR *node,int val){
            if(node == nullptr){
                NodeTR *insert = new NodeTR(val); 
                return insert;
            }
            NodeTR *new_node = node->copy();
            //nao faz tratamento de chaves iguais!
            if(new_node->val > val){ //vai pra esquerda!
                new_node->esq = put(new_node->esq,val);
                if (new_node->esq->priority > new_node->priority){
                    new_node = right_rotation(new_node);
                }
            } 
            else{ //vai pra direita!!
                new_node->dir = put(new_node->dir,val);
                if (new_node->dir->priority > new_node->priority){
                    new_node = left_rotation(new_node);
                }
            }
            return new_node;
        }

        NodeTR* remove_rec(NodeTR *node,int val, int copy){
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

                NodeTR *current_node = node;
                if(copy == 0){
                    NodeTR *new_node = node->copy();
                    current_node = new_node;
                }

                if(current_node->dir->priority > current_node->esq->priority){ // direita sobe
                    current_node->dir = current_node->dir->copy();
                    NodeTR *aux_node = left_rotation(current_node);
                    aux_node->esq = remove_rec(aux_node->esq, val,1);
                    return aux_node;
                }
                else{
                    current_node->esq = current_node->esq->copy();
                    NodeTR *aux_node = right_rotation(current_node);
                    aux_node->dir = remove_rec(aux_node->dir, val,1);
                    return aux_node;
                }
            }
            NodeTR *new_node = node->copy();
            if(new_node->val > val){ //vá pra esquerda!
                new_node->esq = remove_rec(new_node->esq, val,0);
                return new_node;
            }
            else{ //vá pra direita!
                new_node->dir = remove_rec(new_node->dir, val,0);
                return new_node;
            }
        }

        void debug_rec(NodeTR *u, int i){
            if(u->esq != nullptr){
                debug_rec(u->esq, i+3);
            }

            for(int j=0;j<i;j++){
                cout << " ";
            }
            cout << u->val << " " << u->priority;
            cout << endl;

            if(u->dir != nullptr){
                debug_rec(u->dir, i+3);
            }
            
        } 

        int min(NodeTR *u){
            if(u->esq == nullptr){
                return u->val;
            }
            return min(u->esq);
        }

        bool search(NodeTR *u, int x){
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

    public:
        PersistentTreap() {
            raiz = nullptr;
        }
        PersistentTreap(NodeTR *root) {
            raiz = root;
        }
        ~PersistentTreap() {
            delete raiz;
        }

        bool is_null(){
            if(raiz == nullptr){
                return true;
            }
            return false;
        }

        PersistentTreap *add(int val){
            NodeTR *new_root = new NodeTR();
            new_root = put(this->raiz,val);
            PersistentTreap *new_treap = new PersistentTreap(new_root); 
            return new_treap;
        }

        PersistentTreap *remove(int val){
            NodeTR *new_root = new NodeTR();
            new_root = remove_rec(this->raiz, val,0);
            if(new_root == nullptr){
                PersistentTreap *null_treap = new PersistentTreap();
                return null_treap;
            }
            PersistentTreap *new_treap = new PersistentTreap(new_root); 
            return new_treap;
        }

        void print(){
            debug_rec(this->raiz,0);
        }

        int print_min(){
            if(raiz == nullptr){
                cout << "PersistentTreap vazia!" << endl;
                return -1;
            }
            return min(this->raiz);
        }

        int print_search(int x){
            return (search(this->raiz, x)? 1 : 0);
        }
};

int main(){
    srand(time(0));
    vector<PersistentTreap*> vector;
    int numero, t, x;
    PersistentTreap *initial = new PersistentTreap();
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
            for(int i = 0; i < vector.size(); i++){
                cout << "PRINTA A TREAP  " << i << ": " << endl;
                if(vector[i]->is_null()){
                    cout << "Treap " << i << " é uma treap nula!" << endl;
                }
                else{
                    vector[i]->print();
                }
                cout << endl;
            }
            cout << "--------------------------" << endl;
            break;
        }
    }
}
