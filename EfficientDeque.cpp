#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include <cmath>

#define DOIS 2.0

using namespace std;

struct par{
    void* first;
    void* second;
    int number;
};

class SubDeque{
    public:
    vector<void*> sequence;

    SubDeque(){
        
    }

    void push_front(void* insert_front){
        sequence.insert(sequence.begin(), insert_front);
    }

    void push_back(void* insert_back){
        sequence.push_back(insert_back);
    }

    void* pop_front(){
        if(sequence.size() < 1){
            cout << "Impossível dar pop_front em sub_deque vazia!" << endl;
            return nullptr;
        }
        void* pointer = sequence[0];
        sequence.erase(sequence.begin());
        return pointer;
    }

    void* pop_back(){
        if(sequence.size() < 1){
            cout << "Impossível dar pop_back em sub_deque vazia!" << endl;
            return nullptr;
        }
        void* finish = sequence[sequence.size() - 1];
        sequence.pop_back();
        return finish;
        
    }

    void* front(){
        if(sequence.size() < 1){
            cout << "Não é possível fazer a operação front em uma subdeque vazia!" << endl;
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

    SubDeque *preffix;
    EfficientDeque *child;
    EfficientDeque *next;
    SubDeque *suffix;

    EfficientDeque(){
        preffix = new SubDeque();
        suffix = new SubDeque();
        child = nullptr;
        next = nullptr;
    }  

    EfficientDeque(SubDeque* p,SubDeque* s){
        preffix = p;
        suffix = s;
        child = nullptr;
        next = nullptr;
    }    

    EfficientDeque* copy(){
      EfficientDeque *new_deque = new EfficientDeque();
      if(this->preffix != nullptr){
        new_deque->preffix = this->preffix->copy();
      }
      if(this->suffix != nullptr){
        new_deque->suffix = this->suffix->copy();
      }
      new_deque->child = this->child;
      new_deque->next = this->next;
      return new_deque;
    }

    void print(){
        EfficientDeque* current = this;
        EfficientDeque* aux = this->next;
        int i = 0;
        while(current != nullptr || aux != nullptr){
            if(current == nullptr){
                current = aux;
                aux = nullptr;
            }
            cout << "prefix = ";
            for(int j = 0; j < current->preffix->sequence.size(); j++){
                if(i == 0){
                    int resultado = *(int*) current->preffix->sequence[j];
                    cout << resultado << " ";
                }
                else if(i == 1){
                    par resultado_par = *(par*) current->preffix->sequence[j];
                    int resultado = *(int*) resultado_par.first;
                    cout << "(";
                    cout << resultado << " ";
                    resultado = *(int*) resultado_par.second;
                    cout << resultado;
                    cout << ") ";
                }
                else{
                    par major_resultado_par = *(par*) current->preffix->sequence[j];
                    par primeiro_par = *(par*) major_resultado_par.first;
                    par segundo_par = *(par*) major_resultado_par.second;

                    cout << "(";
                    int resultado = *(int*) primeiro_par.first;
                    cout << "(";
                    cout << resultado << " ";
                    resultado = *(int*) primeiro_par.second;
                    cout << resultado;
                    cout << ") ";

                    resultado = *(int*) segundo_par.first;
                    cout << "(";
                    cout << resultado << " ";
                    resultado = *(int*) segundo_par.second;
                    cout << resultado;
                    cout << ")";
                    cout << ")";
                }
            }
            cout << "      ";
            cout << "suffix = ";
            for(int j = 0; j < current->suffix->sequence.size(); j++){
                if(i == 0){
                    int resultado = *(int*) current->suffix->sequence[j];
                    cout << resultado << " ";
                }
                else if(i == 1){
                    par resultado_par = *(par*) current->suffix->sequence[j];
                    int resultado = *(int*) resultado_par.first;
                    cout << "(";
                    cout << resultado << " ";
                    resultado = *(int*) resultado_par.second;
                    cout << resultado;
                    cout << ") ";
                }
                else{
                    par major_resultado_par = *(par*) current->suffix->sequence[j];
                    par primeiro_par = *(par*) major_resultado_par.first;
                    par segundo_par = *(par*) major_resultado_par.second;

                    cout << "(";
                    int resultado = *(int*) primeiro_par.first;
                    cout << "(";
                    cout << resultado << " ";
                    resultado = *(int*) primeiro_par.second;
                    cout << resultado;
                    cout << ") ";

                    resultado = *(int*) segundo_par.first;
                    cout << "(";
                    cout << resultado << " ";
                    resultado = *(int*) segundo_par.second;
                    cout << resultado;
                    cout << ")";
                    cout << ")";
                }
            }
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
        par new_par = {a,b};
        L->push_front(copy_par(&new_par)); //tem que passar o void pointer!
    }
    if(r->size() >= 4){ 
        void* a = r->pop_front();
        void* b = r->pop_front();
        //criar par
        par new_par = {a,b};
        R->push_back(copy_par(&new_par)); //tem que passar o void pointer!
    }

    if(l->size() <= 1){
        void* a;
        void* b;
        if(L->size() != 0){
            void* pointer = L->pop_front();
            par new_par = *(par*) pointer;
            a = new_par.first;
            b = new_par.second;
        }
        else{
            void* pointer = R->pop_front();
            par new_par = *(par*) pointer;
            a = new_par.first;
            b = new_par.second;
        }

        l->push_back(a);
        l->push_back(b);
    }
    if(r->size() <= 1){
        void* a;
        void* b;
        if(R->size() != 0){
            void* pointer = R->pop_back();
            par new_par = *(par*) pointer;
            a = new_par.second;
            b = new_par.first;
        }
        else{
            void* pointer = L->pop_back();
            par new_par = *(par*) pointer;
            a = new_par.first;
            b = new_par.second;
        }
        r->push_front(b);
        r->push_front(a);
    }

}

int digit(EfficientDeque* a, bool last){
    vector<int> digito = {2, 1, 0, 0, 1, 2};
    if(a->preffix->size() == 0 && last){
        return digito[a->suffix->size()];
    }
    else if(a->suffix->size() == 0 && last){
        return digito[a->preffix->size()];
    }
    else{
        int um = digito[a->preffix->size()];
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

    if(a->preffix->size() + a->suffix->size() + 2 * b->preffix->size() + 2 * b->suffix->size() <= 3){
        void* x;
        void* y;
        if(b->preffix->size() != 0){
            void* pointer = b->preffix->pop_front();
            par new_par = *(par*) pointer;

            x = new_par.first;
            y = new_par.second;

            a->preffix->push_back(x);
            a->preffix->push_back(y);
        }
        if(b->preffix->size() != 0){
            void* pointer = b->suffix->pop_front();
            par new_par = *(par*) pointer;

            x = new_par.first;
            y = new_par.second;

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
        if(b != nullptr && b->child != nullptr && a->child != nullptr){ //b != nullptr
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
    b->preffix->push_front(x);
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

EfficientDeque* pop_back(EfficientDeque* a){
    EfficientDeque* b = a->copy();
    if(b->suffix->size() != 0){
        void *c = b->suffix->pop_back();
    }
    else{
        void *c = b->preffix->pop_back();
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
        resultado = *(int*) a->suffix->back();
    }
    else{
        resultado = *(int*) a->preffix->back();
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
            if(t > vector.size() - 1){
                cout << "Não há uma deque " << t << endl;
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
                cout << "Não há uma deque " << t << endl;
            }
            else{
                vector.push_back(pop_front(vector[t]));
            }
            break;
        case 4:
            cin >> t;
            if(t > vector.size() - 1){
                cout << "Não há uma deque " << t << endl;
            }
            else{
                vector.push_back(pop_back(vector[t]));
            }
            break;
        case 5:
            cin >> t;
            if(t < 0 || t > vector.size() - 1){
                cout << "Não há uma deque " << t << endl;
            }
            else if(vector[t] == nullptr){
                cout << "Não há elementos nessa deque!" << endl;
            }
            else{
                cout << front(vector[t]) << endl;
            }
            break;
        case 6:
            cin >> t;
            if(t < 0 || t > vector.size() - 1){
                cout << "Não há uma deque " << t << endl;
            }
            else if(vector[t] == nullptr){
                cout << "Não há elementos nessa deque!" << endl;
            }
            else{
                cout << back(vector[t]) << endl;
            }
            break;
        case 7:
            cin >> t;
            cin >> k;
            //cout << k_th_question(vector[t],k) << endl;
            break;
        case 8:
            cin >> t;
            if(t < 0 || t > vector.size() - 1){
                cout << "Não há uma deque " << t << endl;
            }
            else if(vector[t] == nullptr){
                cout << "Não há elementos nessa deque!" << endl;
            }
            else{
                cout << "("  << front(vector[t]) << "," << back(vector[t]) << ")" << endl;
            }
            break;
        case 9:
            EfficientDeque* aux;
            for(int i = 0; i < vector.size(); i++){
                cout << "Deque de numero  :  " << i << endl;
                aux = vector[i];
                if(aux != nullptr){
                    aux->print();
                }
                else{
                    cout << "Deque sem elementos!" << endl;
                }
                cout << endl;
            }
            break;
        case 11:
            for(int i = 0; i < vector.size(); i++){
                cout << "Deque " << i << endl;
                if(vector[i] != nullptr){
                    cout << "("  << front(vector[i]) << "," << back(vector[i]) << ")" << endl;
                }
                else{
                    cout << "Não há elementos nessa deque!" << endl;
                }
                cout << endl;
            }
        }
    }

    return 0;
}
