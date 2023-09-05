#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class NodeTR{
    public:
        int val;
        int priority;
        NodeTR *esq;
        NodeTR *dir;
        NodeTR() { 
            esq = nullptr;
            dir = nullptr;
            priority = 0;
        };
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
};

class Treap {
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
                NodeTR *inserir = new NodeTR(val); 
                return inserir;
            }
            //nao faz tratamento de chaves iguais!
            if(node->val > val){ //vai pra esquerda!
                node->esq = put(node->esq,val);
                if (node->esq != nullptr && node->esq->priority > node->priority){
                    node = right_rotation(node);
                }
                return node;
            } 
            else{ //vai pra direita!!
                node->dir = put(node->dir,val);
                if (node->dir != nullptr && node->dir->priority > node->priority){
                    node = left_rotation(node);
                }
                return node;
            }
        }

        NodeTR* remove_rec(NodeTR *node,int val){
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
                if(node->dir->priority > node->esq->priority){ // direita sobe
                    NodeTR *new_node = left_rotation(node);
                    new_node->esq = remove_rec(new_node->esq, val);
                    return new_node;
                }
                else{
                    NodeTR *new_node = right_rotation(node);
                    new_node->dir = remove_rec(new_node->dir, val);
                    return new_node;
                }
            }
            else if(node->val > val){ //vá pra esquerda!
                node->esq = remove_rec(node->esq, val);
                return node;
            }
            else{ //vá pra direita!
                node->dir = remove_rec(node->dir, val);
                return node;
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
        Treap() {
            raiz = nullptr;
            srand(time(0));
        }
        ~Treap() {
            delete raiz;
        }
        void add (int val){
            raiz = put(raiz,val);
        }

        void remove(int val){
            this->raiz = remove_rec(this->raiz, val);
        }

        void print(){
            debug_rec(this->raiz,0);
        }

        int print_min(){
            if(raiz == nullptr){
                cout << "Treap vazia!" << endl;
                return -1;
            }
            return min(this->raiz);
        }

        int print_search(int x){
            return (search(this->raiz, x)? 1 : 0);
        }
};

int main(){
    int numero, x;
    Treap *tr = new Treap();

    while(cin >> numero){
        switch (numero)
        {
        case 1:
            cin >> x;
            tr->add(x);
            break;
        case 2:
            cin >> x;
            tr->remove(x);
            break;
        case 3:
            cin >> x;
            cout << tr->print_search(x) << endl;
            break;
        case 4:
            cout << tr->print_min() << endl;;
            break;
        case 5:
            tr->print();
            break;
        }
    }
}