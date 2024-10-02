/***************************************************************************************
 * This implementation is based on Beatriz Marouelli's undergraduate thesis.
 * Her work can be seen here:
 * https://bccdev.ime.usp.br/tccs/2019/bfm/
 ***************************************************************************************/

#include <iostream>

using namespace std;

class Node{
    private:        
    public:
        int max;
        int sum;
        int smax;
        int priority;

        Node *left;
        Node *right;

        bool is_leaf;
        int time;
        int val;
        bool is_push;

        Node(int t, int key, bool pp){
            left = nullptr;
            right = nullptr;
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
            left = e;
            right = d;
            is_leaf = false;

            priority = rand() % 1000;
            this->Update();
        }

        ~Node() {
            if(left != nullptr){
                delete left;
            }
            if(right != nullptr){
                delete right;
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
            this->max = this->right->max;
            this->sum = this->right->sum + this->left->sum;
            this->smax = maxim(this->right->smax, this->right->sum + this->left->smax);
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
            Node *new_root = node->left;
            Node *son = new_root->right;

            new_root->right = node;
            node->left = son;

            node->Update();
            new_root->Update();

            return new_root;
        }

        Node* left_rotation(Node *node){
            Node *new_root = node->right;
            Node *son = new_root->left;

            new_root->left = node;
            node->right = son;

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

            if(node->left->max > t){ //go left!
                node->left = put(node->left, t, item, is_push);
                if (node->left->priority > node->priority){
                    node = right_rotation(node);
                }
            } 
            else{ //go right!
                node->right = put(node->right, t, item, is_push);
                if (node->right->priority > node->priority){
                    node = left_rotation(node);
                }
            }
            node->Update();
            return node;
        }

        Node* delete_operation(Node* node, int t){
            if(node->left->max >= t){ //go left!
                if(node->left->is_leaf){ //last call!
                    if(node->left->time == t){
                        node->right->Update();
                        return node->right;
                    }
                    //no operation on time t found!
                    cout << "no operation on time t = " << t << endl;
                    node->Update();
                    return node;
                }
                node->left = delete_operation(node->left, t);
            } 
            else{ //go right!
                if(node->right->is_leaf){ //last call!
                    if(node->right->time == t){
                        node->left->Update();
                        return node->left;
                    }
                    //no operation on time t found!
                    cout << "no operation on time t = " << t << endl;
                    node->Update();
                    return node;
                }
                node->right = delete_operation(node->right, t);
            }
            node->Update();
            return node;
        }

        void debug_rec(Node *u, int i){
            if(u->right != nullptr){
                debug_rec(u->right, i+3);
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
            }
            cout << endl;

            if(u->left != nullptr){
                debug_rec(u->left, i+3);
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
            if(node->left->max >= t){
                return search_size(node->left, t, sum);
            }
            else {
                return search_size(node->right, t, sum + node->left->sum);
            }
        }

        int find_push(Node *node, int k){
            if(k == 1 && node->is_leaf){
                return node->val;
            }
            if(node->right->smax >= k){
                return find_push(node->right, k);
            }
            return find_push(node->left, k - node->right->sum);
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
            if(node->left->max >= t){
                went_left = true;
                s_kth = search_kth(node->left, t, s_kth);
            } 
            else{
                s_kth = search_kth(node->right, t, s_kth);
            }
            if(s_kth.found != nullptr || went_left){
                return s_kth;
            }
            if(node->left->smax >= s_kth.k){
                return struct_kth{s_kth.k, this->find_push(node->left,s_kth.k), node};
            }
            else{
                return struct_kth{s_kth.k - node->left->sum, -1, nullptr};
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
                    cout << "impossible to perform a pop on an empty retroactive stack" << endl;
                    return;
                }
                //case retroactivestack without pushs and pops
                Node *new_root = new Node(t, item, is_push);
                root = new_root;
                return;
            }
            root = put(this->root, t, item, is_push);
        }

        void remove(int t){
            if(root == nullptr){
                cout << "impossible to remove operations on an empty retroactive stack" << endl;
                return;
            }
            if(this->root->is_leaf){
                this->root = nullptr;
                return;
            }
            root = delete_operation(this->root, t);
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
            if(total < k){ 
                cout << "kth(" << k << ")" << " impossible because the stack on time " << t << " only has " << total << " elements!" << endl;
                return -1;
            }
            struct_kth first = {k, -1, nullptr};
            return(search_kth(this->root, t, first).result); 
        }
};

void instructions(){
    cout << "0         means instructions()" << endl;
    cout << "1 <t> <x> means insert(t, Push, x)" << endl;
    cout << "2 <t>     means insert(t, Pop)" << endl;
    cout << "3 <t>     means delete(t)" << endl;
    cout << "4 <t>     means print(size(t))" << endl;
    cout << "5 <t>     means print(top(t))" << endl;
    cout << "6 <t> <k> means print(kth(t, k))" << endl;
    cout << "7 <t>     means print(t)" << endl;
}

int main(){
    srand(time(0));
    int instruction, t, x;
    RetroactiveStack *stack = new RetroactiveStack();
    instructions();

    while(cin >> instruction){
        switch (instruction)
        {
        case 0:
            instructions();
            break;
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
        }
    }
    delete stack;
}