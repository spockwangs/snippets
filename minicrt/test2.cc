#include "iostream"
#include "string"

using namespace std;

struct A {
    A() {
        cout << "Constructing A\n";
    }
    ~A() {
        cout << "Destructing A\n";
    }
};

A obj;

int main()
{
    string *ps = new string("Hello");
    cout << *ps << endl;
    delete ps;
    return 0;
}
