#include <iostream>
#include "PersistentQueue.h"

int main() {
    PersistentQueue *p1 = new PersistentQueue();
    
    PersistentQueue *p2 = p1->Push(2);
    PersistentQueue *p3 = p2->Push(3);

    PersistentQueue *p4 = p3->Push(12);
    PersistentQueue *p5 = p4->Pop();
    PersistentQueue *p6 = p5->Pop();
    PersistentQueue *p7 = p6->Pop();

    p1->Print_All();
    p2->Print_All();
    p3->Print_All();
    p4->Print_All();
    p5->Print_All();
    p6->Print_All();
    p7->Print_All();


    cout << "p5->size == " << p5->Size() << endl;
    cout << "p1->top == " << p1->Top() << endl;
    cout << "p3->kth(4) == " << p3->K_TH(4) << endl;

    cout << "p4->first() == " << p4->First() << endl;
    cout << "p5->first() == " << p5->First() << endl;
    return 0;
}

