#include <iostream>
#include "PersistentStack.h"

int main() {
    PersistentStack *nula = new PersistentStack();
    
    PersistentStack *p2 = nula->Push(2);
    PersistentStack *p3 = p2->Push(3);

    PersistentStack *p4 = p3->Pop();

    nula->Print_All();
    cout << nula->Size() << endl;
    p2->Print_All();
    cout << p2->Size() << endl;
    p3->Print_All();
    cout << p3->Size() << endl;
    p4->Print_All();
    cout << p4->Size() << endl;
    //cout << p2->Top() << endl;
    cout << nula->Top() << endl;
    cout << p3->K_TH(4) << endl;
    return 0;
}

