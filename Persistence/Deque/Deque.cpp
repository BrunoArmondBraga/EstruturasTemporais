/***************************************************************************************
 * This implementation is based on Chapter 4 of Yan Couto's Master's thesis.
 * His thesis can be acessed here:
 * https://www.teses.usp.br/teses/disponiveis/45/45134/tde-24092019-181655/pt-br.php
 ***************************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
    int val;
    int depth;

    Node *parent;
    Node *jump;

    Node(int value, Node *parent, int depth){
        this->val = value;
        this->parent = parent;
        this->depth = depth;
    }
};

struct deque{
    Node *first;
    Node *last;
};

deque Deque(){
    return deque{nullptr, nullptr};
}

void AddLeaf(Node *u){
    Node* v = u->parent;
    int jump_jump_depth = 0;
    if(v->jump == nullptr){
        u->jump = v;
        return;
    }
    if(v->jump->jump != nullptr){
        jump_jump_depth = v->jump->jump->depth; 
    }
    if(v->jump != nullptr && v->depth - v->jump->depth == v->jump->depth - jump_jump_depth){
        u->jump = v->jump->jump;
    }
    else{
        u->jump = v;
    }
}

Node* LevelAncestor(int k, Node *u){
    int y = u->depth - k;
    while(u->depth != y){
        int jump_depth = 0;
        if(u->jump != nullptr){
            jump_depth = u->jump->depth;
        }
        if(jump_depth >= y){
            u = u->jump;
        }
        else{
            u = u->parent;
        }
    }
    return u;
}

Node* LowestCommonAncestor(Node *u, Node *v){
    if(u->depth > v->depth){
        return LowestCommonAncestor(v,u);
    }
    v = LevelAncestor(v->depth - u->depth, v);
    if(u == v){
        return u;
    }
    while(u->parent != v->parent){
        if(u->jump != v->jump){
            u = u->jump;
            v = v->jump;
        }
        else{
            u = u->parent;
            v = v->parent;
        }
    }
    return u->parent;
}

Node* search(deque d, int k){
    Node *u = LowestCommonAncestor(d.first, d.last);
    int l1 = d.first->depth - u->depth;
    int l2 = d.last->depth - u->depth;

    if(k - 1 <= l1){
        return LevelAncestor(k-1, d.first);
    }
    else{
        return LevelAncestor((l2 - (k-1 - l1)), d.last);
    }
}

deque Swap(deque d){
    return deque{d.last, d.first};
}

deque PushFront(deque d, int x){
    if(d.first == nullptr){
        Node *newNode = new Node(x, nullptr, 1);
        return deque{newNode, newNode};
    }
    Node *newNode = new Node(x, d.first, d.first->depth+1);
    AddLeaf(newNode);
    return deque{newNode,d.last};

}

deque PushBack(deque d, int x){
    return Swap(PushFront(Swap(d),x));
}

deque PopFront(deque d){
    if(d.first == nullptr){
        cout << "Empty Deque!" << endl;
        return d;
    }
    if(d.first == d.last){
        return deque{nullptr, nullptr};
    }
    return deque{search(d,2), d.last};
}
deque PopBack(deque d){
    return Swap(PopFront(Swap(d)));
}

int Front(deque d){
    if(d.first == nullptr){
        cout << "Empty Deque!" << endl;
        return -1;
    }
    return d.first->val;

}
int Back(deque d){
    return Front(Swap(d));
}

int Kth(deque d, int k){
    if(d.first == nullptr){
        cout << "Invalid Deque!" << endl;
        return -1;
    }
    return search(d,k)->val;
}
void Print(deque d){
    if(d.first == nullptr){
        cout << "Empty Deque!" << endl;
        return;
    }
    Node *u = LowestCommonAncestor(d.first, d.last);
    
    if(u == d.first){ /* case \ */
        vector<int> vector;
        Node* v = d.last;
        while(v != u->parent){
            vector.push_back(v->val);
            v = v->parent;
        }
        while(vector.size() != 0){
            cout << vector.back() << " ";
            vector.pop_back();
        }
        cout << endl;
    }
    else if(u == d.last){ /* case / */
        Node* v = d.first;
        while(v != u->parent){
            cout << v->val << " ";
            v = v->parent;
        }
        cout << endl;
    }
    else{ //case ^
        vector<int> vector;
        Node* v = d.last;
        while(v != u){
            vector.push_back(v->val);
            v = v->parent;
        }
        v = d.first;
        while(v != u->parent){
            cout << v->val << " ";
            v = v->parent;
        }
        while(vector.size() != 0){
            cout << vector.back() << " ";
            vector.pop_back();
        }
        cout << endl;
    }
}

void instructions(){
    cout << "0         means instructions()" << endl;
    cout << "1 <t> <x> means pushFront(t, x)" << endl;
    cout << "2 <t> <x> means pushBack(t, x)" << endl;
    cout << "3 <t>     means popFront(t)" << endl;
    cout << "4 <t>     means popBack(t)" << endl;
    cout << "5 <t>     means front(t)" << endl;
    cout << "6 <t>     means back(t)" << endl;
    cout << "7 <t> <x> means kth(t, x)" << endl;
    cout << "8 <t>     means print(t)" << endl;
    cout << "9         means printAll()" << endl;
}

int main(){
    vector<deque> vector;
    int instruction, t, x;
    vector.push_back(Deque());
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
            vector.push_back(PushFront(vector[t],x));
            break;
        case 2:
            cin >> t;
            cin >> x;
            vector.push_back(PushBack(vector[t],x));
            break;
        case 3:
            cin >> t;
            vector.push_back(PopFront(vector[t]));
            break;
        case 4:
            cin >> t;
            vector.push_back(PopBack(vector[t]));
            break;
        case 5:
            cin >> t;
            cout << Front(vector[t]) << endl;
            break;
        case 6:
            cin >> t;
            cout << Back(vector[t]) << endl;
            break;
        case 7:
            cin >> t;
            cin >> x;
            cout << Kth(vector[t],x) << endl;
            break;
        case 8:
            cin >> t;
            Print(vector[t]);
            break;
        case 9:
            for(int i = 0; i < vector.size(); i++){
                cout << "Print Deque  " << i << ": " << endl;
                Print(vector[i]);
                cout << endl;
            }
            cout << "--------------------------" << endl;
            break;
        }
    }
}
