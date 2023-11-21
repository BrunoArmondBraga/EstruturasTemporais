#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include <cmath>

#define DOIS 2.0

using namespace std;

//na verdade parando para pensar é necessário que as deques possuam as deques dentro delas.
//é necessário que as sub-deques sejam deques também se possível, ou haverá incoerência de
//implementações.

class SubDeque{
    public:
    vector<void*> sequence;

    SubDeque(){
        
    }

    void* push_front(void* insert_front){
        sequence.insert(sequence.begin(), insert_front);
    }

    void* push_back(void* insert_back){
        sequence.push_back(insert_back);
    }

    void* pop_front(){
        sequence.erase(sequence.begin());
    }

    void* pop_back(){
        sequence.pop_back();
    }

    void* front(){
        if(sequence.size() < 1){
            cout << "Não é possível fazer a operação front em uma deque vazia!" << endl;
            return nullptr;
        }
        return sequence[0];
    }

    void* back(){
        if(sequence.size() < 1){
            cout << "Não é possível fazer a operação back em uma deque vazia!" << endl;
            return nullptr;
        }
        return sequence[sequence.size() - 1];
    }

    int size(){
        return sequence.size();
    }

};

class EfficientDeque{
    public:

    SubDeque *preffix;
    EfficientDeque *child;
    EfficientDeque *next;
    SubDeque *suffix;

    EfficientDeque(){
        preffix = nullptr;
        child = nullptr;
        next = nullptr;
        suffix = nullptr;
    }  

    EfficientDeque(SubDeque* p,SubDeque* s){
        preffix = p;
        suffix = s;
        child = nullptr;
        next = nullptr;
    }    

    EfficientDeque* copy(){
      EfficientDeque *new_deque = new EfficientDeque();
      new_deque->preffix = this->preffix;
      new_deque->child = this->child;
      new_deque->next = this->next;
      new_deque->suffix = this->suffix;
    }
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

void fix_deques(SubDeque* l, SubDeque* r, SubDeque* L, SubDeque* R){
    if(l->size() >= 4){
        void* b = l->pop_back();
        void* a = l->pop_back();
        //criar par
        L->push_front((a,b)); //tem que passar o void pointer!
    }
    if(r->size() >= 4){ 
        void* a = r->pop_front();
        void* b = r->pop_front();
        //criar par
        R->push_front((a,b)); //tem que passar o void pointer!
    }
    
    if(l->size() <= 1){
        if(L->size() != 0){
            (a,b) = L->pop_front();
        }
        else{
            (a,b) = R->pop_front();
        }

        l->push_back(a);
        l->push_back(b);
    }
    if(r->size() <= 1){
        if(R->size() != 0){
            (a,b) = R->pop_back();
        }
        else{
            (a,b) = L->pop_back();
        }
        r->push_front(b);
        r->push_front(a);
    }

}

int digit(EfficientDeque* a, bool last){
    vector<int> digito = {2,1,0,0,1,2};
    if(a->preffix->size() == 0 && last){
        return digito[a->suffix->size() + 1];
    }
    else if(a->suffix->size() == 0 && last){
        return digito[a->preffix->size() + 1];
    }
    else{
        int um = digito[a->preffix->size() + 1];
        int dois = digito[a->suffix->size() + 1];
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

    if(a->preffix->size() + a->suffix->size() + 2 * b->preffix->size() + 2 * b->suffix->size()){
        if(b->preffix->size() != 0){
            (x,y) = b->preffix->pop_front();
            a->preffix->push_back(x);
            a->preffix->push_back(y);
        }
        if(b->preffix->size() != 0){
            (x,y) = b->suffix->pop_front();
            a->preffix->push_back(x);
            a->preffix->push_back(y);
        }
        if(a->suffix->size() != 0){
            a->preffix->push_back(a->suffix->pop_front());
        }
        b = nullptr;
    }
    else{
        fix_deques(a->preffix, a->suffix, b->preffix, b->suffix);
        if(b->preffix->size() == 0 && b->suffix->size() == 0 && last){
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
        if(b->child != nullptr && a->child != nullptr){
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

EfficientDeque* push_front(EfficientDeque* a, int x){
    EfficientDeque* b = a->copy();
    //fazer copia do inteiro!
    b->preffix->push_front(x);
    check(b);
    return b;
}

EfficientDeque* pop_front(EfficientDeque* a){
    EfficientDeque* b = a->copy();
    if(b->preffix->size() != 0){
        b->preffix->pop_front();
    }
    else{
        b->suffix->pop_front();
    }
    check(b);
    return b;
}

int front(EfficientDeque* a){
    int resultado;
    if(a->preffix->size() != 0){
        resultado = *(int*) a->preffix->front();
    }
    else{
        resultado = *(int*) a->suffix->front();
    }
    return resultado;
}

int back(EfficientDeque* a){
    int resultado;
    if(a->suffix->size() != 0){
        resultado = *(int*) a->suffix->front();
    }
    else{
        resultado = *(int*) a->preffix->front();
    }
    return resultado;
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
    vector<EfficientDeque*> vector;
    vector.push_back(nullptr);

    bool continuar = true;

    int n, t, k;
    while(continuar && cin >> n){
        switch (n)
        {
        case 0:
            print_instructions();
            break;
        case 1:
            int a;
            cin >> t;
            cin >> a;
            //vector.push_back(push_front(vector[t],copy_int(&a)));
            break;
        case 2:
            int b;
            cin >> t;
            cin >> b;
            //vector.push_back(push_back(vector[t],copy_int(&b)));
            break;
        case 3:
            cin >> t;
            //vector.push_back(pop_front(vector[t]));
            break;
        case 4:
            cin >> t;
            //vector.push_back(pop_back(vector[t]));
            break;
        case 5:
            cin >> t;
            //cout << front_question(vector[t]) << endl;
            break;
        case 6:
            cin >> t;
            //cout << back_question(vector[t]) << endl;
            break;
        case 7:
            cin >> t;
            cin >> k;
            //cout << k_th_question(vector[t],k) << endl;
            break;
        case 8:
            cin >> t;
            //print(vector[t]);
            break;
        case 9:
            for(int i = 0; i < vector.size(); i++){
                //print(vector[i]);
            }
            break;
        }
    }

    return 0;
}
