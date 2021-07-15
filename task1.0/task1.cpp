#include <iostream>
#include "task1.h"
using namespace std;

int main()
{
    LinkedList l;
    Node* n = new Node(7);
    Node* n2 = new Node(2);
    Node* n3 = new Node(5);
    l.add(n, 0);
    l.add(n2, 1); //works
    l.remove(3); //works
    l.replace(n, n3);
    cout << l.search(n2) << endl; //works 
    cout << l.nodeAt(1)->getData() << endl; //works
    //l.displayForward(); //works
    l.displayBackward();
    return 0;
}
