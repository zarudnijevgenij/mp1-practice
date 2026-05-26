#include <iostream>
#include "container.h"

using namespace std;

int main() {
    try {
        int step;
        cout << "Enter step: ";
        cin >> step;

        int* a1 = new int(1);
        int* a2 = new int(2);
        int* a3 = new int(3);

        container<int*> b1(1, step);
        b1.push(a2);
        b1.push(a1);
        cout << "After pushes: " << b1 << endl;
        b1.remove(a1);
        cout << "After removing a1: " << b1 << endl;



        container<int> d(2, step);
        d.push(42);
        d.push(45);
        d.push(78);
        cout << "Container d: " << d << endl;



        container<container<int>*> B(5, step);
        B.push(&d);
        cout << "Container B: " << B << endl;



        delete a1;
        delete a2;
        delete a3;

    }
    catch (const std::exception& ex) {
        cout << "Error: " << ex.what() << endl;
    }

    return 0;
}