#include <iostream>
#include <stdlib.h>
#include <string>
#include <cmath>

using namespace std;

#define MAX 12

class Node
{
private:
    void addLeaf_b()
    {
        this->jump_b[0] = this->next;
        double result = log2(this->depth);
        int floor_log = static_cast<int>(floor(result));

        for (int i = 1; i <= floor_log; i++)
        {
            this->jump_b[i] = this->jump_b[i - 1]->jump_b[i - 1];
        }
    }

public:
    int depth;
    int data;
    Node *next;
    Node *jump_b[MAX];
    Node *jump_sb;

    Node(int value, Node *next, int depth)
    {
        this->data = value;
        this->next = next;
        this->depth = depth;
        this->addLeaf_b();
        this->AddLeaf_sb();
    }

    void AddLeaf_sb(){
        Node* u = this;
        Node* v = u->next;
        int jump_sb_jump_sb_depth = 0;
        if(v == nullptr){
            u->jump_sb = nullptr;
            return;
        }
        if(v->jump_sb == nullptr){
            u->jump_sb = v;
            return;
        }
        if(v->jump_sb->jump_sb != nullptr){
            jump_sb_jump_sb_depth = v->jump_sb->jump_sb->depth; 
        }
        if(v->jump_sb != nullptr && v->depth - v->jump_sb->depth == v->jump_sb->depth - jump_sb_jump_sb_depth){
            u->jump_sb = v->jump_sb->jump_sb;
        }
        else{
            u->jump_sb = v;
        }
    }
};

class PersistentStack
{
private:
    Node *root;
    int number_of_elements;

    int level_ancestor_linear(int k){
        int i = 0;
        Node* newNode = this->root;
        while (i != k) {
            if (newNode == nullptr) {
                cout << "Não há " << k+1 << " itens na pilha escolhida!" << endl;
                return -1;
            }
            newNode = newNode->next;
            i++;
        }
        if (newNode == nullptr) {
            cout << "Não há " << k+1 << " itens na pilha escolhida!" << endl;
            return -1;
        }
        return newNode->data;
    }

    int level_ancestor_binary(int k){
        Node *u = this->root;
        if(k < 0){
            cout << "index inválido para função kth!" << endl;
        }
        else if (k+1 > this->number_of_elements)
        {
            cout << "Não há " << k+1 << " itens na pilha escolhida!" << endl;
            return -1;
        }
        double result = log2(k);
        int floorLog = static_cast<int>(floor(result));
        int powVariable = pow(2.0, floorLog);
        for (int i = floorLog; i >= 0; i--)
        {
            if (powVariable <= k)
            {
                k = k - powVariable;
                u = u->jump_b[i];
            }
            powVariable /= 2;
        }
        return u->data;
    }

    int level_ancestor_skew_binary(int k){
        if (k+1 > this->number_of_elements)
        {
            cout << "Não há " << k+1 << " itens na pilha escolhida!" << endl;
            return -1;
        }
        Node *u = this->root;
        int y = u->depth - k;
        while(u->depth != y){
            int jump_sb_depth = 0;
            if(u->jump_sb != nullptr){
                jump_sb_depth = u->jump_sb->depth;
            }
            if(jump_sb_depth >= y){
                u = u->jump_sb;
            }
            else{
                u = u->next;
            }
        }
        return u->data;
    }

public:
    PersistentStack()
    {
        this->number_of_elements = 0;
        root = nullptr;
    }
    PersistentStack(Node *parent, int size)
    {
        this->number_of_elements = size;
        this->root = parent;
    }
    ~PersistentStack()
    {
        delete root;
    }

    PersistentStack *push(int data)
    {

        int newDepth = 0;
        if (this->root != nullptr)
        {
            newDepth = this->root->depth + 1;
        }
        Node *newNode = new Node(data, this->root, newDepth);
        PersistentStack *newStack = new PersistentStack(newNode, this->number_of_elements + 1);
        return newStack;
    }

    PersistentStack *pop()
    {
        if (this->root == nullptr)
        {
            cout << "Erro, não é possível executar o Pop em pilhas vazias!" << endl;
            PersistentStack *placeholder = new PersistentStack();
            return placeholder;
        }
        PersistentStack *newStack = new PersistentStack(root->next, this->number_of_elements - 1);
        return newStack;
    }

    int size()
    {
        return this->number_of_elements;
    }

    int top()
    {
        if (this->number_of_elements == 0)
        {
            cout << "Não é possível fazer um top de uma pilha vazia!" << endl;
            return -1;
        }
        return this->root->data;
    }

    int kth(int k, int mode)
    {
        if(k < 1){
            cout << "kth(" << k << ") com k inválido!" << endl;
            return -1;
        }
        if(mode == 1){
            return level_ancestor_linear(k-1);
        }
        else if(mode == 2){
            return level_ancestor_binary(k-1);
        }
        else{
            return level_ancestor_skew_binary(k-1);
        }
    }

    void printAll()
    {
        Node *newNode = this->root;
        if (newNode == nullptr)
        {
            cout << "itens da pilha = nullptr" << endl;
            return;
        }
        cout << "itens da pilha = " << newNode->data;
        newNode = newNode->next;
        while (newNode != nullptr)
        {
            cout << " " << newNode->data;
            newNode = newNode->next;
        }
        cout << endl;
    }
};

int main()
{
    PersistentStack *p0 = new PersistentStack();
    PersistentStack *p1 = p0->push(5);
    PersistentStack *p2 = p1->push(7);
    PersistentStack *p3 = p2->push(6);
    PersistentStack *p4 = p2->pop();
    PersistentStack *p5 = p4->push(9);
    PersistentStack *p6 = p0->push(5);

    cout << "As pilhas possuem os seguintes elementos:" << endl;
    p0->printAll();
    p1->printAll();
    p2->printAll();
    p3->printAll();
    p4->printAll();
    p5->printAll();
    p6->printAll();
    cout << endl;

    /* cout << "O tamanho das pilhas são:" << endl;
    cout << p0->size() << endl;
    cout << p1->size() << endl;
    cout << p2->size() << endl;
    cout << p3->size() << endl;
    cout << p4->size() << endl;
    cout << p5->size() << endl;
    cout << p6->size() << endl;
    cout << endl; */

    cout << "O top da pilha p3 é = " << p3->top() << endl;
    cout << "O top da pilha p4 é = " << p4->top() << endl;
    cout << endl;


    cout << "O KTH(-1) da pilha p3 é = " << p3->kth(-1,1) << endl;
    cout << "O KTH(0) da pilha p3 é = " << p3->kth(0,1) << endl;
    cout << "O KTH(1) da pilha p3 é = " << p3->kth(1,1) << endl;
    cout << "O KTH(2) da pilha p3 é = " << p3->kth(2,1) << endl;
    cout << "O KTH(3) da pilha p3 é = " << p3->kth(3,1) << endl;
    cout << "O KTH(4) da pilha p3 é = " << p3->kth(4,1) << endl;

    delete p0;
    delete p1;
    delete p2;
    delete p3;
    delete p6;

    return 0;
}
