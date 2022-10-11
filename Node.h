#include <iostream>
using namespace std;

template <class T>
struct Node
{
	T Data;
	Node* Left;
	Node* Right;
	char Color;
	int Count;
};