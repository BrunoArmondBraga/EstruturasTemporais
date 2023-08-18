#include <iostream>
#include "PersistentStack.h"

int main() {
    PersistentStack *p0 = new PersistentStack();

    PersistentStack *p1 = p0->Push(5);
    PersistentStack *p2 = p1->Push(7);
    PersistentStack *p3 = p2->Push(6);

    PersistentStack *p4 = p2->Pop();
    PersistentStack *p5 = p4->Push(9);
    PersistentStack *p6 = p0->Push(5);

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


    cout << "tops" << endl;
    cout << "o top da pilha p3 é = " << p3->Top() << endl;
    cout << "o top da pilha p4 é = " << p4->Top() << endl;
    cout << "o K_TH da pilha p3 é = " << p3->K_TH(2) << endl;
    return 0;
}
