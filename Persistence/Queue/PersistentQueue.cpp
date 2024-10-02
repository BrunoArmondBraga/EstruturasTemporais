/***************************************************************************************
 * This implementation is based on Chapter 3 of Yan Couto's Master's thesis.
 * His thesis can be acessed here:
 * https://www.teses.usp.br/teses/disponiveis/45/45134/tde-24092019-181655/pt-br.php
 ***************************************************************************************/

#include <iostream>
#include <vector>   

using namespace std;

class Node {
public:
    int data;
    Node* next;

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
        delete root;
    }

    PersistentQueue* Push(int data) {
        Node* newNode = new Node(data, this->root);
        PersistentQueue* newQueue = new PersistentQueue(newNode, this->size + 1);
        return newQueue;
    }

    PersistentQueue* Pop() {
        if (this->root == nullptr || this->size == 0) {
            cout << "Empty Queue!" << endl;
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
        return k_th(this->size - 1);
    }

    int Last() {
        if (this->size == 0) {
            cout << "Empty Queue" << endl;
            return -1;
        }
        return this->root->data;
    }

    int k_th(int index) {
        int i = 0;
        Node* newNode = this->root;
        while (i != index) {
            if (newNode == nullptr) {
                cout << "This queue doesn't have " << index << " elements!" << endl;
                return -1;
            }
            newNode = newNode->next;
            i++;
        }
        if (newNode == nullptr) {
            cout << "This queue doesn't have " << index << " elements!" << endl;
            return -1;
        }
        return newNode->data;
    }

    void Print() {
        int i = this->size;
        Node* newNode = this->root;
        if (i == 0) {
            cout << "= nullptr" << endl;
            return;
        }
        cout << "= ";
        while (i > 0) {
            cout << " " << newNode->data;
            newNode = newNode->next;
            i--;
        }
        cout << endl;
    }
};

void instructions(){
    cout << "0         means instructions()" << endl;
    cout << "1 <t> <x> means queue(t, x)" << endl;
    cout << "2 <t>     means dequeue(t)" << endl;
    cout << "3 <t>     means size(t)" << endl;
    cout << "4 <t>     means first(t)" << endl;
    cout << "5 <t>     means last(t)" << endl;
    cout << "6 <t>     means kth(t)" << endl;
    cout << "7         means print()" << endl;
    cout << "8         means printAll()" << endl;
}

int main(){
    vector<PersistentQueue*> vector;
    int instruction, t, x;
    vector.push_back(new PersistentQueue());
    instructions();

    while(cin >> instruction){
        switch (instruction)
        {
        case 0:
            instructions();
            break;
        case 1:
            cin >> t;
            cin >> x;
            vector.push_back(vector[t]->Push(x));
            break;
        case 2:
            cin >> t;
            vector.push_back(vector[t]->Pop());
            break;
        case 3:
            cin >> t;
            if(t < 0 || t > vector.size() - 1){
                cout << "There is no Queue " << t << endl;
            }
            else{
                cout << vector[t]->Size() << endl;
            }
            break;
        case 4:
            cin >> t;
            if(t < 0 || t > vector.size() - 1){
                cout << "There is no Queue " << t << endl;
            }
            else{
                cout << vector[t]->First() << endl;
            }
            break;
        case 5:
            cin >> t;
            if(t < 0 || t > vector.size() - 1){
                cout << "There is no Queue " << t << endl;
            }
            else{
                cout << vector[t]->Last() << endl;
            }
            break;
        case 6:
            cin >> t;
            cin >> x;
            if(t < 0 || t > vector.size() - 1){
                cout << "There is no Queue " << t << endl;
            }
            else{
                cout << vector[t]->k_th(x) << endl;
            }
            break;
        case 7:
            cin >> t;
            vector[t]->Print();
            break;
        case 8:
            for(int i = 0; i < vector.size(); i++){
                cout << "Queue " << i << " ";
                vector[i]->Print();
            }
            break;
        }
    }
}