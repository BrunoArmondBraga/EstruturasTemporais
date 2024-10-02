/***************************************************************************************
 * This implementation is based on Chapter 6 of Yan Couto's Master's thesis.
 * His thesis can be acessed here:
 * https://www.teses.usp.br/teses/disponiveis/45/45134/tde-24092019-181655/pt-br.php
 * 
 * This implementation was presented by Kaplan and Tarjan in the article:
 * H. Kaplan and R.E. Tarjan, "Purely functional, real-time deques with catenation",
 * J. ACM, vol. 46, no. 5, pp. 577–603, Sept. 1999.
 * This article can be acessed here:
 * https://dl.acm.org/doi/10.1145/324133.324139
 ***************************************************************************************/

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

struct peer{
    void* first;
    void* second;
};

class SubDeque{
public:
    vector<void*> sequence;

    SubDeque(){}

    void push_front(void* insert_front){
        sequence.insert(sequence.begin(), insert_front);
    }

    void push_back(void* insert_back){
        sequence.push_back(insert_back);
    }

    void* pop_front(){
        if(sequence.size() < 1){
            cout << "Empty sub-Deque!" << endl;
            return nullptr;
        }
        void* pointer = sequence[0];
        sequence.erase(sequence.begin());
        return pointer;
    }

    void* pop_back(){
        if(sequence.size() < 1){
            cout << "Empty sub-Deque!" << endl;
            return nullptr;
        }
        void* finish = sequence[sequence.size() - 1];
        sequence.pop_back();
        return finish;
        
    }

    void* front(){
        if(sequence.size() < 1){
            cout << "Empty Deque!" << endl;
            return nullptr;
        }
        return sequence[0];
    }

    void* back(){
        if(sequence.size() < 1){
            cout << "Empty Deque!" << endl;
            return nullptr;
        }
        return sequence[sequence.size() - 1];
    }

    int size(){
        return sequence.size();
    }

    SubDeque* copy(){
        SubDeque* new_sub_deque = new SubDeque();
        for(int i = 0; i < sequence.size(); i++){
            new_sub_deque->sequence.push_back(sequence[i]);
        }
        return new_sub_deque;
    }
};

class EfficientDeque{
    public:

    SubDeque *prefix;
    EfficientDeque *child;
    EfficientDeque *next;
    SubDeque *suffix;

    int size;

    EfficientDeque(){
        size = 0;
        prefix = new SubDeque();
        suffix = new SubDeque();
        child = nullptr;
        next = nullptr;
    }     

    EfficientDeque* copy(){
      EfficientDeque *new_deque = new EfficientDeque();
      if(this->prefix != nullptr){
        new_deque->prefix = this->prefix->copy();
      }
      if(this->suffix != nullptr){
        new_deque->suffix = this->suffix->copy();
      }
      new_deque->child = this->child;
      new_deque->next = this->next;
      new_deque->size = this->size;
      return new_deque;
    }
    
    void debug_rec(void* pointer, int k){
        if(k == 1){
            int result = *(int*) pointer;
            cout << result << " ";
        }
        else{
            peer result_peer = *(peer*) pointer;
            cout << "( ";
            debug_rec(result_peer.first, k-1);
            debug_rec(result_peer.second, k-1);
            cout << ")";
            cout << " ";
        }
    }

    void print(){
        EfficientDeque* current = this;
        EfficientDeque* aux = this->next;
        int i = 1;
        while(current != nullptr || aux != nullptr){
            if(current == nullptr){
                current = aux;
                aux = nullptr;
            }
            cout << "( ";
            for(int j = 0; j < current->prefix->sequence.size(); j++){
                debug_rec(current->prefix->sequence[j],i);
            }
            cout << ")";
            cout << "      ";
            cout << "( ";
            for(int j = 0; j < current->suffix->sequence.size(); j++){
                debug_rec(current->suffix->sequence[j],i);
            }
            cout << ")";
            cout << endl;
            if(current->next != nullptr){
                aux = current->next;
            }
            current = current->child;
            i++;
        }
    }
};

void* copy_int(const void* src) {
    void* new_int = malloc(sizeof(int));
    memcpy(new_int, src, sizeof(int));
    return new_int;
}

void* copy_peer(const void* src) {
    void* new_peer = malloc(sizeof(peer));
    memcpy(new_peer, src, sizeof(peer));
    return new_peer;
}

void fix_deques(EfficientDeque* first, EfficientDeque* second){
    SubDeque* l = first->prefix;
    SubDeque* r = first->suffix;
    SubDeque* L = second->prefix;
    SubDeque* R = second->suffix;

    if(l->size() >= 4){
        void* b = l->pop_back();
        void* a = l->pop_back();
        //create peer
        peer new_peer = {a,b};
        L->push_front(copy_peer(&new_peer));
        second->size++;
    }

    if(r->size() >= 4){ 
        void* a = r->pop_front();
        void* b = r->pop_front();
        //create peer
        peer new_peer = {a,b};
        R->push_back(copy_peer(&new_peer));
        second->size++;
    }

    if(l->size() <= 1){
        void* a;
        void* b;
        if(L->size() != 0){
            void* pointer = L->pop_front();
            peer new_peer = *(peer*) pointer;
            a = new_peer.first;
            b = new_peer.second;
        }
        else{
            void* pointer = R->pop_front();
            peer new_peer = *(peer*) pointer;
            a = new_peer.first;
            b = new_peer.second;
        }

        l->push_back(a);
        l->push_back(b);
        second->size--;
    }

    if(r->size() <= 1){
        void* a;
        void* b;
        if(R->size() != 0){
            void* pointer = R->pop_back();
            peer new_peer = *(peer*) pointer;
            a = new_peer.second;
            b = new_peer.first;
        }
        else{
            void* pointer = L->pop_back();
            peer new_peer = *(peer*) pointer;
            a = new_peer.first;
            b = new_peer.second;
        }
        r->push_front(b);
        r->push_front(a);
        second->size--;
    }
}

int digit(EfficientDeque* a, bool last){
    vector<int> digito = {2, 1, 0, 0, 1, 2};
    if(a->prefix->size() == 0 && last){
        return digito[a->suffix->size()];
    }
    else if(a->suffix->size() == 0 && last){
        return digito[a->prefix->size()];
    }
    else{
        int um = digito[a->prefix->size()];
        int dois = digito[a->suffix->size()];
        if(um > dois){
            return um;
        }
        return dois;
    }
}

void fix(EfficientDeque* a){
    EfficientDeque* b;
    bool last = false;
    if(a->child != nullptr){
        b = a->child->copy();
        if(a->next == nullptr && b->child == nullptr){
            last = true;
        }
    }
    else if(a->next != nullptr){
        b = a->next->copy();
        if(b->next == nullptr && b->child == nullptr){
            last = true;
        }
    }
    else{
        b = new EfficientDeque();
        last = true;
    }

    if(a->prefix->size() + a->suffix->size() + 2 * b->prefix->size() + 2 * b->suffix->size() <= 3){
        void* x;
        void* y;
        if(b->prefix->size() != 0){
            void* pointer = b->prefix->pop_front();
            b->size--;
            peer new_peer = *(peer*) pointer;

            x = new_peer.first;
            y = new_peer.second;

            a->prefix->push_back(x);
            a->prefix->push_back(y);
        }
        if(b->prefix->size() != 0){
            void* pointer = b->suffix->pop_front();
            b->size--;
            peer new_peer = *(peer*) pointer;

            x = new_peer.first;
            y = new_peer.second;

            a->prefix->push_back(x);
            a->prefix->push_back(y);
        }
        if(a->suffix->size() != 0){
            a->prefix->push_back(a->suffix->pop_front());
        }
        b = nullptr;
    }
    else{
        fix_deques(a,b);
        if(b->prefix->size() == 0 && b->suffix->size() == 0 && last){
            b = nullptr;
        }
    }

    if(b != nullptr && digit(b, last) == 1){
        if(a->child == nullptr){
            a->next = b->next;
            b->next = nullptr;
        }
        a->child = b;
    }
    else{
        if(b != nullptr && a->child != nullptr){
            b->next = a->next;
        }
        a->next = b;
        a->child = nullptr;
    }
}

void check(EfficientDeque* a){
    bool last = false;
    if(a->child == nullptr && a->next == nullptr){
        last = true;
    }
    if(digit(a, last) == 2){
        fix(a);
    }
    else if(a->next != nullptr){
        if(a->next->child == nullptr && a->next->next == nullptr){
            last = true;
        }
        if(digit(a->next, last)){
            a->next = a->next->copy();
            fix(a->next);
        }
    }
}

EfficientDeque* push_front(EfficientDeque* a, void* x){
    EfficientDeque* b;
    if(a != nullptr){
        b = a->copy();
    }
    else{
        b = new EfficientDeque();
    }
    b->prefix->push_front(x);
    b->size++;
    check(b);
    return b;
}

EfficientDeque* push_back(EfficientDeque* a, void* x){
    EfficientDeque* b;
    if(a != nullptr){
        b = a->copy();
    }
    else{
        b = new EfficientDeque();
    }
    b->suffix->push_back(x);
    b->size++;
    check(b);
    return b;
}

EfficientDeque* pop_front(EfficientDeque* a){
    EfficientDeque* b = a->copy();
    if(b->prefix->size() != 0){
        b->prefix->pop_front();
    }
    else{
        b->suffix->pop_front();
    }
    b->size--;
    check(b);
    return b;
}

EfficientDeque* pop_back(EfficientDeque* a){
    EfficientDeque* b = a->copy();
    if(b->suffix->size() != 0){
        void *c = b->suffix->pop_back();
    }
    else{
        void *c = b->prefix->pop_back();
    }
    b->size--;
    check(b);
    return b;
}

int front(EfficientDeque* a){
    int result;
    if(a->prefix->size() != 0){
        result = *(int*) a->prefix->front();
    }
    else{
        result = *(int*) a->suffix->front();
    }
    return result;
}

int back(EfficientDeque* a){
    int result;
    if(a->suffix->size() != 0){
        result = *(int*) a->suffix->back();
    }
    else{
        result = *(int*) a->prefix->back();
    }
    return result;
}

void* k_th(EfficientDeque *current, EfficientDeque *next, int k){
    int index = k;
    int max = current->size;
    if(index <= current->prefix->size()){
        return current->prefix->sequence[index - 1];
    }
    if(index > max - current->suffix->size()){
        return current->suffix->sequence[index - max + current->suffix->size() - 1];
    }

    index = index - current->prefix->size();
    
    
    peer aux;
    EfficientDeque *jump = next;

    if(current->child != nullptr){
        aux = *(peer*)k_th(current->child, jump, (index+1)/2);
    }
    else{
        aux = *(peer*)k_th(jump, jump->next, (index+1)/2);
    }

    if(index % 2 != 0){
        return aux.first;
    }
    else{
        return aux.second;
    }
}

int k_th_question(EfficientDeque *d, int k){
    if(k > d->size){
        cout << "This deque doesn't have " << k << " elements!" << endl;
        return -1;
    }
    return *(int*)k_th(d, d->next, k);
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
    cout << "10        means print_all_with_kth()" << endl;
    cout << "11        means print_sizes()" << endl;
}

int main() {
    instructions();
    vector<EfficientDeque*> vector;
    vector.push_back(nullptr);

    int n, t, k;
    while(cin >> n){
        switch (n)
        {
        case 0:
            instructions();
            break;
        case 1:
            int a;
            cin >> t;
            cin >> a;
            if(t > vector.size() - 1){
                cout << "There is no Deque " << t << endl;
            }
            else{
                vector.push_back(push_front(vector[t],copy_int(&a)));
            }
            break;
        case 2:
            int b;
            cin >> t;
            cin >> b;
            vector.push_back(push_back(vector[t],copy_int(&b)));
            break;
        case 3:
            cin >> t;
            if(t > vector.size() - 1){
                cout << "There is no Deque " << t << endl;
            }
            else{
                vector.push_back(pop_front(vector[t]));
            }
            break;
        case 4:
            cin >> t;
            if(t > vector.size() - 1){
                cout << "There is no Deque " << t << endl;
            }
            else{
                vector.push_back(pop_back(vector[t]));
            }
            break;
        case 5:
            cin >> t;
            if(t < 0 || t > vector.size() - 1){
                cout << "There is no Deque " << t << endl;
            }
            else if(vector[t] == nullptr){
                cout << "Empty Deque!" << endl;
            }
            else{
                cout << front(vector[t]) << endl;
            }
            break;
        case 6:
            cin >> t;
            if(t < 0 || t > vector.size() - 1){
                cout << "There is no Deque " << t << endl;
            }
            else if(vector[t] == nullptr){
                cout << "Empty Deque!" << endl;
            }
            else{
                cout << back(vector[t]) << endl;
            }
            break;
        case 7:
            cin >> t;
            if(t < 0 || t > vector.size() - 1){
                cout << "There is no Deque " << t << endl;
            }
            else if(vector[t] == nullptr){
                cout << "Empty Deque!" << endl;
            }
            else{
                vector[t]->print();
            }
            break;           
        case 8:
            cin >> t;
            cin >> k;
            if(vector[t] == nullptr || vector[t]->size < k){
                cout << "No elements " << k << " in deque " << t << endl;
            }
            else{
                cout << k_th_question(vector[t], k) << endl;
            }
            break;
        case 9:
            {
            EfficientDeque* aux;
            for(int i = 0; i < vector.size(); i++){
                cout << "Deque  :  " << i << endl;
                aux = vector[i];
                if(aux != nullptr){
                    aux->print();
                }
                else{
                    cout << "Empty Deque!" << endl;
                }
                cout << endl;
            }
            break;
            }
        case 10:
            for(int i = 0; i < vector.size(); i++){
                if(vector[i] == nullptr || vector[i]->size == 0){
                    cout << "Empty Deque" << endl;
                }
                else{
                    int size = vector[i]->size;
                    for(int j = 1; j < size + 1; j++){
                        cout << k_th_question(vector[i],j) << " ";
                    }
                    cout << endl;
                }
            }
            break;
        case 11:
        {
            for(int i = 0; i < vector.size(); i++){
                cout << "Deque  :  " << i << endl;
                if(vector[i] == nullptr){
                    cout << "0" << endl;
                }
                else{
                    int j = 0;
                    EfficientDeque* current = vector[i];
                    EfficientDeque* next = vector[i]->next;
                    while(current != nullptr || next != nullptr){
                        if(current == nullptr){
                            current = next;
                            next = current->next;
                        }
                        cout << "level " << j << " has size = " << current->size << endl;
                        current = current->child;
                        j++;
                    }
                }
            }
        }
        }
    }

    return 0;
}