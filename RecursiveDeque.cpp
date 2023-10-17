#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

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
    RecursiveDeque j;
};

struct par{
    void* first;
    void* second;
};


void* front(RecursiveDeque *d){
    if(d->prefix != nullptr){
        return d->prefix;
    }
    else if(d->center == nullptr){
        return d->sufix;
    }
    else{
        par resposta = *((par*) front(d->center)); 
        cout << "a resposta encontrada é" << *(int*)resposta.first << endl;
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
    return *(int*)back(d);
}

RecursiveDeque* push_front(RecursiveDeque *d, void* new_int){
    if(d == nullptr){
        return new RecursiveDeque(new_int, nullptr, nullptr, 1);
    }
    else if(d->prefix == nullptr){
        return new RecursiveDeque(new_int, d->center, d->sufix, d->size + 1);
    }
    else{
        par new_par = {new_int, &d->prefix};
        return new RecursiveDeque(nullptr, push_front(d->center, &new_par), d->sufix, d->size + 1);
    }
}

int push_back(RecursiveDeque *d){

}

int pop_front(RecursiveDeque *d, int x){

}

aux pop_front_aux(RecursiveDeque *d){

}

int pop_back(RecursiveDeque *d, int x){

}

aux pop_back_aux(RecursiveDeque *d){

}

int k_th(RecursiveDeque *d, int k){

}

void print(RecursiveDeque *d){
    //cout << 
}



int main() {
    RecursiveDeque* deque = new RecursiveDeque();

    int a = 4;
    deque->prefix = &a;

    std::cout << "achei o prefix da deque  =  " << *(int*)deque->prefix << std::endl;

    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;

    par primeiro_par = {&b, &c};
    par segundo_par = {&d, &e};

    std::cout << "achei o tchombers!!!!   " << *(int*)primeiro_par.first << " " << *(int*)primeiro_par.second << std::endl;

    /* par par_de_pares = {&primeiro_par, &segundo_par};
    par par_de_pares2 = {&segundo_par, &primeiro_par};

    par par_de_par_de_pares = {&par_de_pares, &par_de_pares2};

    int primeiro_elemento = *((int*)((par*)((par*)par_de_par_de_pares.first)->first)->first);
    int segundo_elemento =  *((int*)((par*)((par*)par_de_par_de_pares.first)->first)->second);
    int terceiro_elemento =  *((int*)((par*)((par*)par_de_par_de_pares.first)->second)->first);
    int quarto_elemento =  *((int*)((par*)((par*)par_de_par_de_pares.first)->second)->second);
    int quinto_elemento =  *((int*)((par*)((par*)par_de_par_de_pares.second)->first)->first);
    int sexto_elemento =  *((int*)((par*)((par*)par_de_par_de_pares.second)->first)->second);


    std::cout << "Primeiro elemento do primeiro par de par de pares: " << primeiro_elemento << std::endl;
    std::cout << "Primeiro elemento do primeiro par de par de pares: " << segundo_elemento << std::endl;
    std::cout << "Primeiro elemento do primeiro par de par de pares: " << terceiro_elemento << std::endl;
    std::cout << "Primeiro elemento do primeiro par de par de pares: " << quarto_elemento << std::endl;
    std::cout << "Primeiro elemento do primeiro par de par de pares: " << quinto_elemento << std::endl;
    std::cout << "Primeiro elemento do primeiro par de par de pares: " << sexto_elemento << std::endl;
    */

    RecursiveDeque *de = new RecursiveDeque();
    int init = 12;
    de->prefix = &init;

    int fim = 25;
    de->sufix = &fim;

    RecursiveDeque *se = new RecursiveDeque();
    se->center = de;

    RecursiveDeque *x = nullptr;
    int po = 2;
    RecursiveDeque *y = push_front(x,&po);
    cout << "o primeiro elemento de y é " << *(int*)y->prefix << endl;




    RecursiveDeque *initial = nullptr;
    vector<RecursiveDeque*> vector;
    vector.push_back(initial);

    int n,t;
    while(cin >> n){
        switch (n)
        {
        case 1:
            int t;
            cin >> t;
            int insert;
            cin >> insert;
            vector.push_back(push_front(vector[t],&insert));
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
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
            //cout << k_th(vector[t],x) << endl;
            break;
        case 8:
            //print(vector[t]);
            break;
        }
    }
}