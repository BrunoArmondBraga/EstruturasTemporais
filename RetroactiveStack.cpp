#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

class Node{
    private:        
    public:

        int max; //maior chave entre as chaves menores. max pai = max do filho direito.
        int sum;
        int smax;
        int priority;

        Node *esq;
        Node *dir;

        bool is_leaf;
        int time;
        int val;
        bool is_push;

        Node() { 
            esq = nullptr;
            dir = nullptr;
        }

        Node(int t, int key, bool pp){
            esq = nullptr;
            dir = nullptr;
            val = key;
            time = t;
            is_leaf = true;
            is_push = pp;
            max = time;
            if(is_push){
                sum = 1;
                smax = 1;
            }
            else{
                sum = -1;
                smax = -1;
                val = -99;
            }
        }

        Node(Node *e, Node *d){
            esq = e;
            dir = d;
            is_leaf = false;

            priority = rand() % 1000;
            this->Update();
        }

        ~Node() {
            if(esq != nullptr){
                delete esq;
            }
            if(dir != nullptr){
                delete dir;
            }
        }

        int maxim(int a, int b){
            if(a > b){
                return a;
            }
            return b;
        }

        void Update(){
            if(this->is_leaf){
                return;
            }
            this->max = this->dir->max;
            this->sum = this->dir->sum + this->esq->sum;
            this->smax = maxim(this->dir->smax, this->dir->sum + this->esq->smax);
        }  
};

struct struct_kth{
    int k;
    int result;
    Node* found;
};

class RetroactiveStack {  
    private:
        Node *root;

        Node* right_rotation(Node *node){
            Node *new_root = node->esq;
            Node *son = new_root->dir;

            new_root->dir = node;
            node->esq = son;

            node->Update();
            new_root->Update();

            return new_root;
        }

        Node* left_rotation(Node *node){
            Node *new_root = node->dir;
            Node *son = new_root->esq;

            new_root->esq = node;
            node->dir = son;

            node->Update();
            new_root->Update();

            return new_root;
        }

        Node* put(Node *node, int t, int item, bool is_push){
            if(node->is_leaf){
                Node *new_leaf = new Node(t, item, is_push);
                Node *new_root;
                if(t > node->time){
                    new_root = new Node(node, new_leaf);
                }
                else{
                    new_root = new Node(new_leaf, node);
                }
                new_root->Update();
                return new_root;
            }

            if(node->esq->max > t){ //vai pra esquerda!
                node->esq = put(node->esq, t, item, is_push);
                if (node->esq->priority > node->priority){
                    node = right_rotation(node);
                }
            } 
            else{ //vai pra direita!!
                node->dir = put(node->dir, t, item, is_push);
                if (node->dir->priority > node->priority){
                    node = left_rotation(node);
                }
            }
            node->Update();
            return node;
        }

        Node* delete_operation(Node* node, int t){
            if(node->esq->max >= t){ //vai pra esquerda!
                if(node->esq->is_leaf){ //chegando na última chamada!
                    if(node->esq->time == t){
                        node->dir->Update();
                        return node->dir;
                    }
                    cout << "não achamos uma operação no tempo t = " << t << endl;
                    node->Update();
                    return node;
                }
                node->esq = delete_operation(node->esq, t);
            } 
            else{ //vai pra direita!!
                if(node->dir->is_leaf){ //chegando na última chamada!
                    if(node->dir->time == t){
                        node->esq->Update();
                        return node->esq;
                    }
                    cout << "não achamos uma operação no tempo t = " << t << endl;
                    node->Update();
                    return node;
                }
                node->dir = delete_operation(node->dir, t);
            }
            node->Update();
            return node;
        }

        void debug_rec(Node *u, int i){
            if(u->dir != nullptr){
                debug_rec(u->dir, i+3);
            }

            for(int j=0;j<i;j++){
                cout << " ";
            }
            if(u->is_leaf){
                cout << u->val;
            }
            else{
                cout << "max=" << u->max << "sum=" << u->sum;
                cout << "smax=" << u->smax;
                // << u->priority;
                //cout << "-";
            }
            cout << endl;

            if(u->esq != nullptr){
                debug_rec(u->esq, i+3);
            }
        } 

        int search_size(Node* node, int t, int sum){
            if(node->is_leaf){
                if(node->time <= t){
                    if(node->is_push){
                        return sum + 1;
                    }
                    return sum -1;
                }
                return sum;
            }
            if(node->esq->max >= t){ //vai pra esquerda!
                return search_size(node->esq, t, sum);
            }
            else {
                return search_size(node->dir, t, sum + node->esq->sum);
            }
        }

        int find_push(Node *node, int k){
            if(k == 1 && node->is_leaf){
                return node->val;
            }
            if(node->dir->smax >= k){
                return find_push(node->dir, k);
            }
            return find_push(node->esq, k - node->dir->sum);
        }

        struct_kth search_kth(Node *node, int t, struct_kth s_kth){
            if(node->is_leaf){
                if(node->time <= t){
                    if(node->is_push){
                        if(s_kth.k == 1){
                            return struct_kth{-1, node->val, node};
                        }
                        return struct_kth{s_kth.k - 1, -1, nullptr};
                    }
                    else{
                        return struct_kth{s_kth.k + 1, -1, nullptr};
                    }
                }
                return s_kth;
            }
            bool went_left = false;
            if(node->esq->max >= t){ //vai pra esquerda!
                went_left = true;
                s_kth = search_kth(node->esq, t, s_kth);
            } 
            else{ //vai pra direita!!
                s_kth = search_kth(node->dir, t, s_kth);
            }
            if(s_kth.found != nullptr || went_left){
                return s_kth;
            }
            if(node->esq->smax >= s_kth.k){
                return struct_kth{s_kth.k, this->find_push(node->esq,s_kth.k), node};
            }
            else{
                return struct_kth{s_kth.k - node->esq->sum, -1, nullptr};
            }
        }

    public:
        RetroactiveStack(){
            root = nullptr;
        }   

        ~RetroactiveStack(){
            if(root != nullptr){
                delete root;
            }
        }

        void insert(int t, bool is_push, int item){
            if(root == nullptr){
                if(is_push == false){
                    cout << "impossivel fazer pop em uma pilha retroativa vazia" << endl;
                    return;
                }
                //caso pilha retroativa sem push or pops
                Node *new_root = new Node(t, item, is_push);
                root = new_root;
                return;
            }
            root = put(this->root, t, item, is_push);
        }

        void remove(int t){
            if(root == nullptr){
                cout << "impossível retirar operações em pilha retroativa vazia" << endl;
                return;
            }
            if(this->root->is_leaf){
                this->root = nullptr;
                return;
            }
            root = delete_operation(this->root, t);
        }

        void print_test(){
            if(this->root == nullptr){
                cout << "pilha retroativa vazia!" << endl;
                return;
            }
            cout << "--------------" << endl;
            debug_rec(this->root,0);
            cout << "--------------" << endl;
        }

        void print(int t){
            int total = this->size(t);
            for(int i = 1; i <= total; i++){
                cout <<  this->kth(t,i) << " ";
            }
            cout << endl;
        }

        int size(int t){
            return search_size(this->root, t, 0);
        }

        int kth(int t, int k){
            int total = this->size(t);
            if(total < k){ //tratamento de impossiveis!
                cout << "kth(" << k << ")" << " impossível porque a pilha no tempo " << t << " so possui " << total << " elementos!" << endl;
                return -1;
            }
            struct_kth first = {k, -1, nullptr};
            return(search_kth(this->root, t, first).result); 
        }
};

int main(){
    //srand(time(0));
    srand(1211);
    int numero, t, x;
    RetroactiveStack *stack = new RetroactiveStack();

    while(cin >> numero){
        switch (numero)
        {
        case 1:
            cin >> t;
            cin >> x;
            stack->insert(t, true, x);
            break;
        case 2:
            cin >> t;
            stack->insert(t, false, 0);
            break;
        case 3:
            cin >> t;
            stack->remove(t);
            break;
        case 4:
            cin >> t;
            cout << stack->size(t) << endl;
            break;
        case 5:
            cin >> t;
            cout << stack->kth(t, 1) << endl;
            break;
        case 6:
            cin >> t;
            cin >> x;
            cout << stack->kth(t, x) << endl;
            break;
        case 7:
            cin >> t;
            stack->print(t);
            break;
        case 8:
            stack->print_test();
            break;
        }
    }
    delete stack;
}