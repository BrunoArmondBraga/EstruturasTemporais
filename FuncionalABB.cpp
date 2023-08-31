#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

class Node{
    private:
        
    public:
        int key;
        Node *esq;
        Node *dir;
        Node() { 
            esq = nullptr;
            dir = nullptr;
        };
        Node(int val){
            esq = nullptr;
            dir = nullptr;
            this->key = val;
        }
        ~Node() {
            if(esq != nullptr){
                delete esq;
            }
            if(dir != nullptr){
                delete dir;
            }
        }
};

class Abb {
    private: 
        Node *raiz;

        Node *put(Node *araiz,int val){
            if(araiz == nullptr){
                Node *inserir = new Node(val); 
                return inserir;
            }
            if(araiz->key == val){ //chave igual
                //tratamento chave igual!
                cout << "A árvore de busca binária não aceita chaves repetidas!" << endl;
            }
            else if(araiz->key > val){ //chave menor
                araiz->esq = put(araiz->esq,val);
            } 
            else{ //chave maior
                araiz->dir = put(araiz->dir,val);
            }
            return araiz;
        }

        int get(Node *no,int key){
            if(no==nullptr) return 0;
            if(no->key == key){
                return no->key;
            }
            if(no->key > key){
                return get(no->esq,key);
            }
            return get(no->dir,key);
        }

        void debug_rec(Node *u, int i){
            if(u->esq != nullptr){
                debug_rec(u->esq, i+3);
            }

            for(int j=0;j<i;j++){
                cout << " ";
            }
            cout << u->key;
            cout << endl;

            if(u->dir != nullptr){
                debug_rec(u->dir, i+3);
            }
            
        }        
        
    public:
        Abb() {
            raiz = nullptr;
        }
        ~Abb() {
            delete raiz;
        }
        
        void add (int val){
           raiz = put(raiz,val);
        }

        int value(int key){
            return get(raiz,key);
        }

        void print(){
            debug_rec(this->raiz,0);
        }
        
};

int main(){
    Abb *abb = new Abb();
    abb->add(2);
    abb->add(1);
    abb->add(3);
    abb->print();

    delete abb;
}