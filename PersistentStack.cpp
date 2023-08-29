#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        this->data = value;
        next = nullptr;
    }

    Node(int value, Node* next) {
        this->data = value;
        this->next = next;
    }
};

class PersistentStack {
private:
    Node* root;
    int size;

public:
    PersistentStack() {
        this->size = 0;
        root = nullptr;
    }

    PersistentStack(Node* pai) {
        this->size = 0;
        this->root = pai;
    }

    PersistentStack(Node* pai, int tam) {
        this->size = tam;
        this->root = pai;
    }

    ~PersistentStack() {
        delete root;
    }

    PersistentStack* Push(int data) {
        Node* newNode = new Node(data, this->root);
        PersistentStack* newStack = new PersistentStack(newNode, this->size + 1);
        return newStack;
    }

    PersistentStack* Pop() {
        if (this->root == nullptr) {
            cout << "Erro, não é possível executar o Pop em pilhas vazias!" << endl;
            PersistentStack* placeHolder = new PersistentStack();
            return placeHolder;
        }
        PersistentStack* newStack = new PersistentStack(root->next, this->size - 1);
        return newStack;
    }

    int Size() {
        return this->size;
    }

    int Top() {
        if (this->size == 0) {
            cout << "Não é possível fazer um top de uma pilha vazia!" << endl;
            return -1;
        }
        return this->root->data;
    }

    int KTH(int index) {
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

    void Print_All() {
        Node* newNode = this->root;
        if (newNode == nullptr) {
            cout << "itens da pilha = nullptr" << endl;
            return;
        }
        cout << "itens da pilha = " << newNode->data;
        newNode = newNode->next;
        while (newNode != nullptr) {
            cout << " " << newNode->data;
            newNode = newNode->next;
        }
        cout << endl;
    }
};

int main() {
    PersistentStack* p0 = new PersistentStack();

    PersistentStack* p1 = p0->Push(5);
    PersistentStack* p2 = p1->Push(7);
    PersistentStack* p3 = p2->Push(6);

    PersistentStack* p4 = p2->Pop();
    PersistentStack* p5 = p4->Push(9);
    PersistentStack* p6 = p0->Push(5);

    cout << endl;
    cout << "As pilhas possuem os seguintes elementos:" << endl;
    p0->Print_All();
    p1->Print_All();
    p2->Print_All();
    p3->Print_All();
    p4->Print_All();
    p5->Print_All();
    p6->Print_All();
    cout << endl;
    
    cout << "o tamanho das pilhas são:" << endl;
    cout << p0->Size() << endl;
    cout << p1->Size() << endl;
    cout << p2->Size() << endl;
    cout << p3->Size() << endl;
    cout << p4->Size() << endl;
    cout << p4->Size() << endl;
    cout << p5->Size() << endl;
    cout << p6->Size() << endl;
    cout << endl;

    cout << "o top da pilha p3 é = " << p3->Top() << endl;
    cout << "o top da pilha p4 é = " << p4->Top() << endl;
    cout << "o KTH da pilha p3 é = " << p3->KTH(2) << endl;
    
    delete p0;
    delete p1;
    delete p2;
    delete p3;
    delete p6;

    return 0;
}
