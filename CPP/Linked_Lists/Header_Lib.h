#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include <string>
using namespace std;

struct node{
    string song;
    string artist;
    node * next;
};

class LinkedList{
	private:
		node * head;
		int listLength;
		
	public:
		LinkedList();
		bool insertNode( node * newNode, int position );
		bool removeNode( int position );
		void printList();
		~LinkedList();
};

#endif