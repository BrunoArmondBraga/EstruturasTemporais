#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <cstring>
#include <cmath>

#define DOIS 2.0

using namespace std;

class RecursiveDeque{
    public:

    void* prefix;
    RecursiveDeque *center;
    void* sufix;
    int size;

    RecursiveDeque(){
        prefix = nullptr;
        center = nullptr;
        sufix = nullptr;
        size = 0;
    }  

    RecursiveDeque(void* p, RecursiveDeque* c,void* s, int si){
        prefix = p;
        center = c;
        sufix = s;
        size = si;
    }    
};

struct aux{
    void* i;
    RecursiveDeque* new_deque;
};

struct par{
    void* first;
    void* second;
};

void* copy_int(const void* src) {
    void* new_int = malloc(sizeof(int));
    memcpy(new_int, src, sizeof(int));
    return new_int;
}

void* copy_par(const void* src) {
    void* new_par = malloc(sizeof(par));
    memcpy(new_par, src, sizeof(par));
    return new_par;
}


void* front(RecursiveDeque *d){
    if(d->prefix != nullptr){
        return d->prefix;
    }
    else if(d->center == nullptr){
        return d->sufix;
    }
    else{
        par resposta = *((par*) front(d->center));
        return resposta.first;
    }
}

int front_question(RecursiveDeque *d){
    if(d == nullptr){
        cout << "Deque vazia!!" << endl;
        return -1;
    }
    int final = *((int*)front(d));
    return final;
}

void* back(RecursiveDeque *d){
    if(d->sufix != nullptr){
        return d->sufix;
    }
    else if(d->center == nullptr){
        return d->prefix;
    }
    else{
        par resposta = *((par*) back(d->center));
        return resposta.second;
    }
}

int back_question(RecursiveDeque *d){
    if(d == nullptr){
        cout << "Deque vazia!!" << endl;
        return -1;
    }
    int final = *((int*)back(d));
    return final;
}

RecursiveDeque* push_front(RecursiveDeque *d, void* new_int){
    if(d == nullptr){
        return new RecursiveDeque(new_int, nullptr, nullptr, 1);
    }
    else if(d->prefix == nullptr){
        return new RecursiveDeque(new_int, d->center, d->sufix, d->size + 1);
    }
    else{
        par new_par = {new_int, d->prefix};
        return new RecursiveDeque(nullptr, push_front(d->center, copy_par(&new_par)), d->sufix, d->size + 1);
    }
}

RecursiveDeque* push_back(RecursiveDeque *d, void* new_int){
    if(d == nullptr){
        return new RecursiveDeque(nullptr, nullptr, new_int, 1);
    }
    else if(d->sufix == nullptr){
        return new RecursiveDeque(d->prefix, d->center, new_int, d->size + 1);
    }
    else{
        par new_par = {d->sufix, new_int};
        return new RecursiveDeque(d->prefix, push_back(d->center, copy_par(&new_par)), nullptr, d->size + 1);
    }
}

aux pop_front_aux(RecursiveDeque *d){
    if(d->prefix != nullptr && d->center == nullptr and d->sufix == nullptr){
        return aux{d->prefix, nullptr};
    }
    else if(d->prefix != nullptr){
        RecursiveDeque *new_deque = new RecursiveDeque(nullptr, d->center, d->sufix, d->size - 1); 
        return aux{d->prefix, new_deque};
    }
    else if(d->center == nullptr){
        return aux{d->sufix, nullptr};
    }
    else{
        aux auxiliar = pop_front_aux(d->center);

        par x = *(par*)auxiliar.i;

        RecursiveDeque *new_deque = new RecursiveDeque(x.second, auxiliar.new_deque, d->sufix, d->size - 1); 

        return aux{x.first, new_deque};
    }
}

RecursiveDeque* pop_front(RecursiveDeque *d){
    if(d == nullptr){
        cout << "Não é possível usar a operação PopFront em uma deque vazia" << endl;
        return nullptr;
    }
    return pop_front_aux(d).new_deque;
}

aux pop_back_aux(RecursiveDeque *d){
    if(d->sufix != nullptr && d->center == nullptr and d->prefix == nullptr){
        return aux{d->sufix, nullptr};
    }
    else if(d->sufix != nullptr){
        RecursiveDeque *new_deque = new RecursiveDeque(d->prefix, d->center, nullptr, d->size - 1); 
        return aux{d->sufix, new_deque};
    }
    else if(d->center == nullptr){
        return aux{d->prefix, nullptr};
    }
    else{
        aux auxiliar = pop_back_aux(d->center);

        par x = *(par*)auxiliar.i;

        RecursiveDeque *new_deque = new RecursiveDeque(d->prefix, auxiliar.new_deque, x.first, d->size - 1); 

        return aux{x.second, new_deque};
    }
}

RecursiveDeque* pop_back(RecursiveDeque *d){
    if(d == nullptr){
        cout << "Não é possível usar a operação PopFront em uma deque vazia" << endl;
        return nullptr;
    }
    return pop_back_aux(d).new_deque;
}

void* k_th(RecursiveDeque *d, int k){
    if(k == 1 && d->prefix != nullptr){
        return d->prefix;
    }
    if(k == d->size && d->sufix != nullptr){
        return d->sufix;
    }
    int index = k;
    if(d->prefix != nullptr){
        index = k - 1;
    }
    
    par aux = *(par*)k_th(d->center, (index+1)/2);

    if(index % 2 != 0){
        return aux.first;
    }
    else{
        return aux.second;
    }
}

int k_th_question(RecursiveDeque *d, int k){
    if(k > d->size){
        cout << "Esta deque não possui " << k << " elementos!" << endl;
        return -1;
    }
    return *(int*)k_th(d,k);
}

void print(RecursiveDeque *d){
    if(d == nullptr){
        cout << "Deque vazia!" << endl;
        return;
    }
    int k = d->size;

    for(int i = 1; i <= k; i ++){
        cout << k_th_question(d, i) << " ";
    }
    cout << endl;
}

void print_instructions(){
    cout << "Codificação das operações:" << endl;
    cout << " 1 <t> <x> significa d_ultima+1 = push_front(d_t, x)" << endl;
    cout << " 2 <t> <x> significa d_ultima+1 = push_back(d_t, x)" << endl;
    cout << " 3 <t>     significa d_ultima+1 = pop_front(d_t)" << endl;
    cout << " 4 <t>     significa d_ultima+1 = pop_back(d_t)" << endl;
    cout << " 5 <t>     significa println(front(d_t))" << endl;
    cout << " 6 <t>     significa println(back(d_t))" << endl;
    cout << " 7 <t> <k> significa println(k_th(d_t, k))" << endl;
    cout << " 8 <t>     significa print(d_t)" << endl;
    cout << " 9         significa print_all()" << endl;
    cout << "10         significa print_instructions" << endl;
    cout << endl;
}


int main() {
    print_instructions();
    vector<RecursiveDeque*> vector;
    vector.push_back(nullptr);

    bool continuar = true;

    int n, t, k;
    while(continuar && cin >> n){
        switch (n)
        {
        case 1:
            int a;
            cin >> t;
            cin >> a;
            vector.push_back(push_front(vector[t],copy_int(&a)));
            break;
        case 2:
            int b;
            cin >> t;
            cin >> b;
            vector.push_back(push_back(vector[t],copy_int(&b)));
            break;
        case 3:
            cin >> t;
            vector.push_back(pop_front(vector[t]));
            break;
        case 4:
            cin >> t;
            vector.push_back(pop_back(vector[t]));
            break;
        case 5:
            cin >> t;
            cout << front_question(vector[t]) << endl;
            break;
        case 6:
            cin >> t;
            cout << back_question(vector[t]) << endl;
            break;
        case 7:
            cin >> t;
            cin >> k;
            cout << k_th_question(vector[t],k) << endl;
            break;
        case 8:
            cin >> t;
            print(vector[t]);
            break;
        case 9:
            for(int i = 0; i < vector.size(); i++){
                print(vector[i]);
            }
            break;
        case 10:
            print_instructions();
            break;
        }
    }

    return 0;
}
