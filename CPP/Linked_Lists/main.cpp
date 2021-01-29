#include "Header_Lib.h"

using namespace std;

int main(){
    node * A = new node;
    A -> song = "We Are";
    A -> artist = "Vertical Horizon";
    
    node * B = new node;
    B -> song = "I Stand Alone";
    B -> artist = "Godsmack";
    
    node * C = new node;
    C -> song = "Heir Apparent";
    C -> artist = "Opeth";
    
    node * D = new node;
    D -> song = "Fear of the Dark";
    D -> artist = "Iron Maiden";
    
    node * E = new node;
    E -> song = "Blue Monday";
    E -> artist = "New Order";
    
    node * F = new node;
    F -> song = "The Moth";
    F -> artist = "Aimee Mann";
    
    LinkedList myList;
    myList.insertNode(A, 1);
    myList.insertNode(B, 2);
    myList.insertNode(C, 3);
    myList.insertNode(D, 4);
    myList.printList();
    
    myList.insertNode(E, 2);
    myList.printList();
    
    myList.insertNode(F,1);
    myList.printList();
    
    myList.removeNode(6);
    myList.printList();
    
    myList.removeNode(1);
    myList.printList();
    
    myList.removeNode(3);
    myList.printList();
    
    return 0;
}

//Just simple, so if you want to use the looping in insert processes, you can edit this source code.

//Coded by : Yehezk34