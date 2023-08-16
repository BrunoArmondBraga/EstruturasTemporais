#ifndef PERSISTENTSTACK_H
#define PERSISTENTSTACK_H

#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

class Node {
public:
    int data;
    Node *next;

    Node(int value){
        this->data = value;
        next = nullptr;
    }

    Node(int value, Node *next){
        this->data = value;
        this->next = next;
    }
};

class PersistentStack {
    private: 
        Node *root; 
        int size;
    public:
        PersistentStack() {
            this->size = 0;
            root = nullptr;
        }
        PersistentStack(Node *pai) {
            this->size = 0;
            this->root = pai;
        }
        PersistentStack(Node *pai, int tam) {
            this->size = tam;
            this->root = pai;
        }
        ~PersistentStack() {
            delete root;
        }

        PersistentStack* Push(int data){
            Node *newNode = new Node(data, this->root);
            PersistentStack *newStack = new PersistentStack(newNode, this->size + 1); 
            return newStack;
        }

        PersistentStack* Pop(){
            if(this->root == nullptr){
                cout << "Erro, não é possível executar o Pull em pilhas vazias!" << endl;
                PersistentStack *placeHolder = new PersistentStack();
                return placeHolder;
            }
            PersistentStack *newStack = new PersistentStack(root->next, this->size -1);
            return newStack;
        }


        int Size(){
            return this->size;
        }

        int Top(){
            if(this->size == 0){
                cout << "Não é possível fazer um top de uma pilha vazia!" << endl;
                return -1;
            }
            return this->root->data;
        }
        
        int K_TH(int index){
            //implementei 0 sendo o topo!
            int i = 0;
            Node *newNode = this->root;
            while(i != index){
                if(newNode == nullptr){
                    cout << "Não há " << index << " itens na pilha escolhida!" << endl;
                    return -1;
                }
                newNode = newNode->next;
                i++;
            }
            if(newNode == nullptr){
                cout << "Não há " << index << " itens na pilha escolhida!" << endl;
                return -1;
            }
            return newNode->data;
        } 

        void Print_All(){
            Node *newNode = this->root;
            if(newNode == nullptr){
                cout << "itens da pilha = nullptr" << endl;
                return;
            }
            cout << "itens da pilha = " << newNode->data;
            newNode = newNode->next;
            while(newNode != nullptr){
                cout << " " << newNode->data;
                newNode = newNode->next;
            }
            cout << endl;
        } 
        
};
#endif