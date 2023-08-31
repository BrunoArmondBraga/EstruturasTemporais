#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;


class NodeTR{
    private:
        
    public:
        int val;
        NodeTR *esq;
        NodeTR *dir;
        int priority;
        NodeTR() { 
            esq = nullptr;
            dir = nullptr;
            priority = 0;
        };
        NodeTR(int val){
            esq = nullptr;
            dir = nullptr;
            priority = rand();
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

        int get(NodeTR *no,int val){
            if(no==nullptr) return -1;
            if(no->val == val){
                return no->val;
            }
            if(no->val > val){
                return get(no->esq,val);
            }
            return get(no->dir,val);
        }

        NodeTR* right_rotation(NodeTR *node){
            NodeTR* new_root = node->esq;
            NodeTR *son = new_root->dir;

            new_root->dir = node;
            node->esq = son;

            return new_root;
        }

        NodeTR* left_rotation(NodeTR *node){
            NodeTR* new_root = node->dir;
            NodeTR *son = new_root->esq;

            new_root->esq = node;
            node->dir = son;

            return new_root;
        }

        NodeTR* put(NodeTR *node,int val){
            NodeTR *novo;
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
                if (node->esq != nullptr && node->dir->priority > node->priority){
                    node = left_rotation(node);
                }
                return node;
            }
        }

        NodeTR* remove_rec(NodeTR *node,int val){
            if(node == nullptr){
                cout << "Não há o elemento com valor = " << val << " na treap atualmente!" << endl;
                return nullptr;
            }
            if(node->val == val){
                //tratamento de deleção
                if(node->dir == nullptr){
                    return node->esq;
                }
                else if(node->esq == nullptr){
                    return node->dir;
                }
                if(node->dir->priority > node->esq->priority){ // coloque 
                    if(node->dir != nullptr){
                        //node->
                    }
                    return node->dir;
                }
                else{

                }
            }
            else if(node->val > val){ //vá pra esquerda!
                node->esq = remove_rec(node->esq, val);
            }
            else{ //vá pra direita!
                node->dir = remove_rec(node->dir, val);
            }
        }

        void debug_rec(NodeTR *u, int i){
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
        int value(int val){ 
            return get(raiz,val);
        }

        void remove(int val){
            remove_rec(this->raiz, val);
        }

        void print(){
            debug_rec(this->raiz,0);
        }
};

int main(){
    Treap *tr = new Treap();
    tr->add(9);
    tr->add(1);
    tr->add(3);
    tr->add(2);
    tr->add(23);
    tr->add(7);
    tr->print();
}