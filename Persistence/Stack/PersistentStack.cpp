/***************************************************************************************
 * This implementation is based on Chapter 3 of Yan Couto's Master's thesis.
 * His thesis can be acessed here:
 * https://www.teses.usp.br/teses/disponiveis/45/45134/tde-24092019-181655/pt-br.php
 ***************************************************************************************/

#include <iostream>
#include <cmath>
#include <vector>

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
                cout << "There aren't " << k+1 << " itens in this stack!" << endl;
                return -1;
            }
            newNode = newNode->next;
            i++;
        }
        if (newNode == nullptr) {
            cout << "There aren't " << k+1 << " itens in this stack!" << endl;
            return -1;
        }
        return newNode->data;
    }

    int level_ancestor_binary(int k){
        Node *u = this->root;
        if(k < 0){
            cout << "invalid index!" << endl;
        }
        else if (k+1 > this->number_of_elements)
        {
            cout << "There aren't " << k+1 << " itens in this stack!" << endl;
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
            cout << "There aren't " << k+1 << " itens in this stack!" << endl;
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
            cout << "Empty Stack!" << endl;
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
            cout << "Empty Stack!" << endl;
            return -1;
        }
        return this->root->data;
    }

    int kth(int k, int mode)
    {
        if(k < 1){
            cout << "kth(" << k << ") with invalid k!" << endl;
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
            cout << "= nullptr" << endl;
            return;
        }
        cout << "= " << newNode->data;
        newNode = newNode->next;
        while (newNode != nullptr)
        {
            cout << " " << newNode->data;
            newNode = newNode->next;
        }
        cout << endl;
    }
};

void instructions(){
    cout << "0         means instructions()" << endl;
    cout << "1 <t> <x> means push(t, x)" << endl;
    cout << "2 <t>     means pop(t)" << endl;
    cout << "3 <t>     means size(t)" << endl;
    cout << "4 <t>     means top(t)" << endl;
    cout << "5 <t> <x> means kth(t,x) using linear level ancestor" << endl;
    cout << "6 <t> <x> means kth(t,x) using binary level ancestor" << endl;
    cout << "7 <t> <x> means kth(t,x) using jump pointers" << endl;
    cout << "8 <t>     means print(t)" << endl;
    cout << "9         means printAll()" << endl;
}

int main(){
    vector<PersistentStack*> vector;
    int instruction, t, x;
    vector.push_back(new PersistentStack());
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
            vector.push_back(vector[t]->push(x));
            break;
        case 2:
            cin >> t;
            vector.push_back(vector[t]->pop());
            break;
        case 3:
            cin >> t;
            if(t < 0 || t > vector.size() - 1){
                cout << "There is no Stack " << t << endl;
            }
            else{
                cout << vector[t]->size() << endl;
            }
            break;
        case 4:
            cin >> t;
            if(t < 0 || t > vector.size() - 1){
                cout << "There is no Stack " << t << endl;
            }
            else{
                cout << vector[t]->top() << endl;
            }
            break;
        case 5:
            cin >> t;
            cin >> x;
            if(t < 0 || t > vector.size() - 1){
                cout << "There is no Stack " << t << endl;
            }
            else{
                cout << vector[t]->kth(x,1) << endl;
            }
            break;
        case 6:
            cin >> t;
            cin >> x;
            if(t < 0 || t > vector.size() - 1){
                cout << "There is no Stack " << t << endl;
            }
            else{
                cout << vector[t]->kth(x,2) << endl;
            }
            break;
        case 7:
            cin >> t;
            cin >> x;
            if(t < 0 || t > vector.size() - 1){
                cout << "There is no Stack " << t << endl;
            }
            else{
                cout << vector[t]->kth(x,3) << endl;
            }
            break;
        case 8:
            cin >> t;
            vector[t]->printAll();
            break;
        case 9:
            for(int i = 0; i < vector.size(); i++){
                cout << "Stack " << i << " ";
                vector[i]->printAll();
            }
            break;
        }
    }
}