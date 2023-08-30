#include <iostream>
#include <stdlib.h>
#include <string>
#include <cmath>

using namespace std;

#define MAX 12

class Node
{
private:
    void addLeaf()
    {
        this->jump[0] = this->next;
        double result = log2(this->depth);
        int floor_log = static_cast<int>(floor(result));

        for (int i = 1; i <= floor_log; i++)
        {
            this->jump[i] = this->jump[i - 1]->jump[i - 1];
        }
    }

public:
    int depth;
    int data;
    Node *next;
    Node *jump[MAX];

    Node(int value, Node *next, int depth)
    {
        this->data = value;
        this->next = next;
        this->depth = depth;
        this->addLeaf();
    }
};

class PersistentStack
{
private:
    Node *root;
    int numberOfElements;

    int level_ancestor_n(int index){
        int i = 0;
        Node* newNode = this->root;
        while (i != index) {
            if (newNode == nullptr) {
                cout << "Não há " << index << " itens na pilha escolhida!" << endl;
                return -1;
            }
            newNode = newNode->next;
            i++;
        }
        if (newNode == nullptr) {
            cout << "Não há " << index << " itens na pilha escolhida!" << endl;
            return -1;
        }
        return newNode->data;
    }

    int level_ancestor_binary(int k){
        Node *u = this->root;
        if(k < 1){
            cout << "index inválido para função kth!" << endl;
        }
        else if (k > this->numberOfElements)
        {
            cout << "Não há " << k << " itens na pilha escolhida!" << endl;
            return -1;
        }
        k = k - 1;
        double result = log2(k);
        int floorLog = static_cast<int>(floor(result));
        for (int i = floorLog; i >= 0; i--)
        {
            int powVariable = pow(2.0, i);
            if (powVariable <= k)
            {
                k = k - powVariable;
                u = u->jump[i];
            }
        }
        return u->data;
    }

    int level_ancestor_skew_binary(int k){
        return -1;
    }

public:
    PersistentStack()
    {
        this->numberOfElements = 0;
        root = nullptr;
    }
    PersistentStack(Node *parent)
    {
        this->numberOfElements = 0;
        this->root = parent;
    }
    PersistentStack(Node *parent, int size)
    {
        this->numberOfElements = size;
        this->root = parent;
    }
    ~PersistentStack()
    {
        delete root;
    }

    PersistentStack *push(int data)
    {

        int newDepth = 1;
        if (this->root != nullptr)
        {
            newDepth = this->root->depth + 1;
        }
        Node *newNode = new Node(data, this->root, newDepth);
        PersistentStack *newStack = new PersistentStack(newNode, this->numberOfElements + 1);
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
        PersistentStack *newStack = new PersistentStack(root->next, this->numberOfElements - 1);
        return newStack;
    }

    int size()
    {
        return this->numberOfElements;
    }

    int top()
    {
        if (this->numberOfElements == 0)
        {
            cout << "Não é possível fazer um top de uma pilha vazia!" << endl;
            return -1;
        }
        return this->root->data;
    }

    int kth(int k, int mode)
    {
        if(mode == 1){
            return level_ancestor_n(k);
        }
        else if(mode == 2){
            return level_ancestor_binary(k);
        }
        else{
            return level_ancestor_skew_binary(k);
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

    void print()
    {
        cout << "====================" << endl;
        for (int i = 0; i <= 1; i++)
        {
            cout << this->root->data << endl;
            cout << "o ponteiro de valor i = " << i << " possui o valor " << this->root->jump[i]->data << endl;
        }
        cout << "====================" << endl;
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


    cout << "O KTH(-1) da pilha p3 é = " << p3->kth(-1,2) << endl;
    cout << "O KTH(0) da pilha p3 é = " << p3->kth(0,2) << endl;
    cout << "O KTH(1) da pilha p3 é = " << p3->kth(1,2) << endl;
    cout << "O KTH(2) da pilha p3 é = " << p3->kth(2,2) << endl;
    cout << "O KTH(3) da pilha p3 é = " << p3->kth(3,2) << endl;
    cout << "O KTH(4) da pilha p3 é = " << p3->kth(4,2) << endl;

    delete p0;
    delete p1;
    delete p2;
    delete p3;
    delete p6;

    return 0;
}
