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

    ~Node(){
        if(next != nullptr){
            delete next;
        }
    }
};

class PersistentQueue {
private:
    Node* root;
    int size;

public:
    PersistentQueue() {
        this->size = 0;
        root = nullptr;
    }

    PersistentQueue(Node* pai) {
        this->size = 0;
        this->root = pai;
    }

    PersistentQueue(Node* pai, int tam) {
        this->size = tam;
        this->root = pai;
    }

    ~PersistentQueue() {
    }

    void DeleteNode(){
        //Essa função foi criada para tratar do vazamento de memória.
        //Ela deve ser chamada ao fim da execução em todas as "cabeças" de filas diferentes.
        //Depois dessa chamada, apenas use delete p* em todas as filas.
        delete root;
    }

    PersistentQueue* Push(int data) {
        Node* newNode = new Node(data, this->root);
        PersistentQueue* newQueue = new PersistentQueue(newNode, this->size + 1);
        return newQueue;
    }

    PersistentQueue* Pop() {
        if (this->root == nullptr || this->size == 0) {
            cout << "Erro, não é possível executar o Pop em filas vazias!" << endl;
            PersistentQueue* placeHolder = new PersistentQueue();
            return placeHolder;
        }
        PersistentQueue* newQueue = new PersistentQueue(this->root, this->size - 1);
        return newQueue;
    }

    int Size() {
        return this->size;
    }

    int First() {
        return K_TH(this->size - 1);
    }

    int Top() {
        if (this->size == 0) {
            cout << "Não é possível fazer um top de uma fila vazia!" << endl;
            return -1;
        }
        return this->root->data;
    }

    int K_TH(int index) {
        int i = 0;
        Node* newNode = this->root;
        while (i != index) {
            if (newNode == nullptr) {
                cout << "Não há " << index << " itens na fila escolhida!" << endl;
                return -1;
            }
            newNode = newNode->next;
            i++;
        }
        if (newNode == nullptr) {
            cout << "Não há " << index << " itens na fila escolhida!" << endl;
            return -1;
        }
        return newNode->data;
    }

    void Print_All() {
        int i = this->size;
        Node* newNode = this->root;
        if (i == 0) {
            cout << "itens da fila = nullptr" << endl;
            return;
        }
        cout << "itens da fila = ";
        while (i > 0) {
            cout << " " << newNode->data;
            newNode = newNode->next;
            i--;
        }
        cout << endl;
    }
};

int main() {
    PersistentQueue* p0 = new PersistentQueue();

    PersistentQueue* p1 = p0->Push(2);
    PersistentQueue* p2 = p1->Push(3);

    PersistentQueue* p3 = p2->Push(12);
    PersistentQueue* p4 = p3->Pop();
    PersistentQueue* p5 = p4->Pop();
    PersistentQueue* p6 = p5->Pop();

    p0->Print_All();
    p1->Print_All();
    p2->Print_All();
    p3->Print_All();
    p4->Print_All();
    p5->Print_All();
    p6->Print_All();
    cout << endl;

    cout << "p4->size == " << p4->Size() << endl;
    cout << "p0->top == " << p0->Top() << endl;
    cout << "p2->kth(4) == " << p2->K_TH(4) << endl;

    cout << "p3->first() == " << p3->First() << endl;
    cout << "p4->first() == " << p4->First() << endl;

    p3->DeleteNode();
    delete p0;
    delete p1;
    delete p2;
    delete p3;
    delete p4;
    delete p5;
    delete p6;
    

    return 0;
}
