#include "Tree.h"
#include <fstream>

template <class T>
class RedBlackTree : public Tree<T>
{
	// Wrapper/Helping Functions:
	void INSERT(Node<T>*, Node<T>*); 
	bool SEARCH(Node<T>*, Node<T>*&, T);  
	void PREORDER(Node<T>*); 
	void INORDER(Node<T>*);  
	void POSTORDER(Node<T>*);  
	void PREORDER2(Node<T>*);  
	void INORDER2(Node<T>*);  
	void POSTORDER2(Node<T>*); 
	void DESTROYTREE(Node<T>*); 
	void REMOVEDUPLICATES(Node<T>*); 
	void FindParent(Node<T>*, Node<T>*, Node<T>*&); 
	void FixTree(Node<T>*); 
	void FindNode(Node<T>*, Node<T>*&, T);
	Node<T>* InitializeNode(Node<T>*, T);
	void copyTree(Node<T>*);
public:

	// Required Functions:			 // Cases:
	void Insert(T);					 // 1
	bool Search(T, char&);			 // 2
	void PreOrder(int);				 // 3 & 6
	void InOrder(int);				 // 4 & 7
	void PostOrder(int);			 // 5 & 8
	void DisplayParent(T);			 // 9
	void ReadFile();				 // 10		
	void RemoveDuplicates();		 // 11
	void DestroyTree();				 // 12

	// Constructors and Destructor:
	RedBlackTree(); // Default Constructor
	RedBlackTree(const RedBlackTree<T>&);	// Copy Constructor
	~RedBlackTree(); // Destructor

	// Extra Functions:
	bool isEmpty();
};
					
													// Required Functions:
template <class T>
void RedBlackTree<T>::Insert(T value)
{
	Node<T>* newNode = InitializeNode(new Node<T>, value);
	if (this->root == nullptr)	 // Case 1: Root Node Color will always remain Black.
	{
		this->root = newNode;
		this->root->Color = 'B';
		newNode = nullptr;
	}
	else
	{
		Node<T>* trail = this->root;
		while (true)
		{
			if (value == trail->Data)
			{
				trail->Count++;
				delete newNode;
				newNode = nullptr;
				break;
			}
			else if (value < trail->Data)
			{
				if (trail->Left == nullptr)
				{
					trail->Left = newNode;
					break;
				}
				else
					trail = trail->Left;
			}
			else if (value > trail->Data)
			{
				if (trail->Right == nullptr)
				{
					trail->Right = newNode;
					break;
				}
				else
					trail = trail->Right;
			}
		}
		if (trail->Color == 'R' && newNode != nullptr) // If there are two consecutive Nodes colored "Red", then there must be
			FixTree(newNode);						   // an Unbalance. So, we'll fix the tree from here.
		newNode = nullptr;
		trail = nullptr;
	}
}

template <class T>
void RedBlackTree<T>::FixTree(Node<T>* N) // A Function for Balancing the Tree after Each Insertion.
{
	if (N != this->root)
	{
		int temp = 0;
		Node<T>* UG = nullptr;			// Parent Node (If Any) Of the Grand Parent of Child.
		Node<T>* G = nullptr;			// Grand Parent (if Any) Node of Child.
		Node<T>* P = nullptr;			// Parent Node of Child. (Child of Grandparent if there's any)
		Node<T>* U = nullptr;			// Uncle Node of Child. (Also, a Child of Grandparent if there's any) 

		// Assigning addresses to Pointers according to the Task.
		FindParent(this->root, N, P);			
		FindParent(this->root, P, G);
		FindParent(this->root, G, UG);
		if (G != nullptr)
		{
			if (P == G->Left)
				U = G->Right;
			else if (P == G->Right)
				U = G->Left;
			while (P->Color == 'R' && N->Color == 'R')
			{
				if (P == G->Right)
				{
					if (U == nullptr || U->Color == 'B')
					{
						if (N == G->Right->Left) // Case 4: If N is Left Child of P which is Right Child of G. Where N and P are both Colored "Red".
						{						 // Solution: Rotation of N and P where N becomes child of G and N becomes Parent of P. 
							G->Right = N;	  	 // And then Swapping N and P (We turn Case 4 into Case 5). Afterwards, we move to Case 5.
							P->Left = N->Right;
							N->Right = P;
							Node<T>* temp = P;
							P = N;
							N = temp;
						}
						// Case 5: If the Node 'N' is Right Child of Node 'P' which is Right Child of Node 'G'. 
						// Where Nodes 'N' and 'P' are both colored "Red".
						// Solution: Re-Structuring of Nodes. Where 'G' becomes Left Child of 'P' and other changes.
						P->Color = 'B';
						G->Color = 'R';

						G->Right = P->Left;

						if (G != this->root)
						{
							FindParent(this->root, G, UG);
							if (UG->Right == G)
								UG->Right = P;
							else
								UG->Left = P;
						}
						else
							UG = nullptr;
						
						P->Left = G;
						if (G == this->root)
						{
							this->root = P;
							break;
						}
					}
					else if (U->Color == 'R')
					{
						// Case 3: If the Nodes 'N' and 'P' are both Colored "Red". Whereas, the Node 'U' is also colored "Red".
						// Solution: Re-Colouring of Nodes 'P', 'U', 'G'.
						P->Color = 'B';
						U->Color = 'B';
						G->Color = 'R';
						if (G == this->root) // If 'G' is the Root Node. Then, we re-colour it back to Black.
							G->Color = 'B';

						// Re-colouring can create an Unbalance in the Upper Part of the Tree. 
						// Now, shifting the Nodes to the upper level to check if there's any Unbalance until we Reach Root Node.
						N = G;
						FindParent(this->root, N, P);
						FindParent(this->root, P, G);
						FindParent(this->root, G, UG);
						if (P == G->Right)
							U = G->Left;
						else
							U = G->Right;
					}
				}
				else
				{
					if (U == nullptr || U->Color == 'B')
					{
						if (N == G->Left->Right) // Case 4: If N is Right Child of P which is Left Child of G. Where N and P are both Colored "Red".
						{						 // Solution: Rotation of N and P where N becomes child of G and N becomes Parent of P. 
							G->Left = N;		 // And then Swapping N and P (We turn Case 4 into Case 5). Afterwards, we move to Case 5.
							P->Right = N->Left;
							N->Left = P;
							Node<T>* temp = P;
							P = N;
							N = temp;
						}

						// Case 5: If the Node 'N' is left Child of Node 'P'  which is Left Child of Node 'G'. 
						// Where Nodes 'N' and 'P' are both colored "Red".
						// Solution: Re-Structuring of Nodes. Where 'G' becomes Right Child of 'P' and other changes.
						P->Color = 'B';
						G->Color = 'R';
						G->Left = P->Right;
						if (G != this->root)
						{
							FindParent(this->root, G, UG);
							if (UG->Left == G)
								UG->Left = P;
							else
								UG->Right = P;
						}
						else
							UG = nullptr;
						
						P->Right = G;
						if (G == this->root)
						{
							this->root = P;
							break;
						}

					}
					else if (U->Color == 'R')
					{
						// Case 3: If the Nodes 'N' and 'P' are both Colored "Red". Whereas, the Node 'U' is also colored "Red".
						// Solution: Re-Colouring of Nodes 'P', 'U', 'G'.
						P->Color = 'B';
						U->Color = 'B';
						G->Color = 'R';
						if (G == this->root)
							G->Color = 'B';

						// Re-colouring can create an Unbalance in the Upper Part of the Tree. 
						// Now, shifting the Nodes to the upper level to check if there's any Unbalance until we Reach Root Node.
						N = G;
						FindParent(this->root, N, P);
						FindParent(this->root, P, G);
						FindParent(this->root, G, UG);
						if (P == G->Right)
							U = G->Left;
						else
							U = G->Right;
					}
				}
				if (N == this->root)
				{
					// If N reaches Root then We have Traversed the Unbalanced Side of the Tree.
					N = nullptr;
					P = nullptr;
					G = nullptr;
					U = nullptr;
					UG = nullptr;
					break;
				}
			}
		}
	}
}

template <class T>
bool RedBlackTree<T>::Search(T value, char& color) // This Functions calls the Wrapper Function 'SEARCH' if the Tree isn't Empty.
{
	Node<T>* t = this->root;
	if (this->root != nullptr)
	{
		if (SEARCH(this->root, t, value))
		{
			color = t->Color;
			return true;
		}
	}
	
	return false;
}

template <class T>
void RedBlackTree<T>::InOrder(int choice)
{
	if (this->root != nullptr)
	{
		if (choice)
			INORDER(this->root);		//LNR
		else
			INORDER2(this->root);		//RNL
	}
	else
	{
		cout << "\t\t\t\t\t\t ====================" << endl;
		cout << "\t\t\t\t\t\t    Tree is Empty." << endl;
		cout << "\t\t\t\t\t\t ====================" << endl;

	}
}

template <class T>
void RedBlackTree<T>::INORDER(Node<T>* n)	//LNR
{
	Node<T>* p = nullptr;
	if (n != nullptr)
	{
		INORDER(n->Left);
		this->FindParent(this->root, n, p);
		if (p != nullptr)
			cout << "\t\t "<< n->Data << " | Color: " << n->Color << " | Count: " << n->Count << " | Parent: " << p->Data << endl;
		else
			cout << "\t\t " << n->Data << " | Color: " << n->Color << " | Count: " << n->Count << " | Parent: None" << endl;
		INORDER(n->Right);
	}
}

template <class T>
void RedBlackTree<T>::INORDER2(Node<T>* n)	//RNL
{
	Node<T>* p = nullptr;
	if (n != nullptr)
	{
		INORDER2(n->Right);
		this->FindParent(this->root, n, p);
		if (p != nullptr)
			cout << "\t\t " <<  n->Data << " | Color: " << n->Color << " | Count: " << n->Count << " | Parent: " << p->Data << endl;
		else
			cout << "\t\t " << n->Data << " | Color: " << n->Color << " | Count: " << n->Count << " | Parent: None" << endl;
		INORDER2(n->Left);
	}
}


template <class T>
void RedBlackTree<T>::PreOrder(int choice)
{
	if (this->root != nullptr)
	{
		if (choice)
			PREORDER(this->root);		//NLR
		else
			PREORDER2(this->root);	//NRL
	}
	else
	{
		cout << "\t\t\t\t\t\t ====================" << endl;
		cout << "\t\t\t\t\t\t    Tree is Empty." << endl;
		cout << "\t\t\t\t\t\t ====================" << endl;
	}
}

template <class T>
void RedBlackTree<T>::PREORDER(Node<T>* n)		//NLR
{
	Node<T>* p = nullptr;
	if (n != nullptr)
	{
		this->FindParent(this->root, n, p);
		if (p != nullptr)
			cout << "\t\t " << n->Data << " | Color: " << n->Color << " | Count: " << n->Count << " | Parent: " << p->Data << endl;
		else
			cout << "\t\t " << n->Data << " | Color: " << n->Color << " | Count: " << n->Count << " | Parent: None" << endl;
		PREORDER(n->Left);
		PREORDER(n->Right);
	}
}

template <class T>
void RedBlackTree<T>::PREORDER2(Node<T>* n)		//NRL
{
	Node<T>* p = nullptr;
	if (n != nullptr)
	{
		this->FindParent(this->root, n, p);
		if (p != nullptr)
			cout << "\t\t " << n->Data << " | Color: " << n->Color << " | Count: " << n->Count << " | Parent: " << p->Data << endl;
		else
			cout << "\t\t " << n->Data << " | Color: " << n->Color << " | Count: " << n->Count << " | Parent: None" << endl;
		PREORDER2(n->Right);
		PREORDER2(n->Left);
	}
}

template <class T>
void RedBlackTree<T>::PostOrder(int choice) 
{
	if (this->root != nullptr)
	{
		if (choice)
			POSTORDER(this->root);		//LRN
		else
			POSTORDER2(this->root);		//RLN
	}
	else
	{
		cout << "\t\t\t\t\t\t ====================" << endl;
		cout << "\t\t\t\t\t\t    Tree is Empty." << endl;
		cout << "\t\t\t\t\t\t ====================" << endl;
	}
}

template <class T>
void RedBlackTree<T>::POSTORDER(Node<T>* n)	 //LRN
{
	Node<T>* p = nullptr;
	if (n != nullptr)
	{
		POSTORDER(n->Left);
		POSTORDER(n->Right);
		this->FindParent(this->root, n, p);
		if (p != nullptr)
			cout << "\t\t " << n->Data << " | Color: " << n->Color << " | Count: " << n->Count << " | Parent: " << p->Data << endl;
		else
			cout << "\t\t " << n->Data << " | Color: " << n->Color << " | Count: " << n->Count << " | Parent: None" << endl;
	}
}

template <class T>
void RedBlackTree<T>::POSTORDER2(Node<T>* n) //RLN
{
	Node<T>* p = nullptr;
	if (n != nullptr)
	{
		POSTORDER2(n->Right);
		POSTORDER2(n->Left);
		this->FindParent(this->root, n, p);
		if (p != nullptr)
			cout << "\t\t " << n->Data << " | Color: " << n->Color << " | Count: " << n->Count << " | Parent: " << p->Data << endl;
		else
			cout << "\t\t " << n->Data << " | Color: " << n->Color << " | Count: " << n->Count << " | Parent: None" << endl;
	}
}

template <class T>
void RedBlackTree<T>::DisplayParent(T value) // A Function that Displays the Parent of the Given Node (If the Parent is Available in the Tree)	
{
	char c;
	if (Search(value,c))
	{
		Node<T>* N = nullptr;
		Node<T>* pNode = nullptr;
		FindNode(this->root, N, value);
		FindParent(this->root, N, pNode);
		cout << "\t\t Node: " << N->Data << " | Color: " << N->Color;
		if (pNode != nullptr)
			cout << " | Parent: " << pNode->Data << endl;
		else
			cout << " | Parent: None" << endl;
	}
	else
		cout << "\t\t Node Not Found." << endl;

}

template <class T>
void RedBlackTree<T>::ReadFile()	// A Function that Reads the Values from 'Input.txt' File and Inserts them in the Tree.	
{
	ifstream fin("Input.txt");
	if (!fin.is_open())
	{
		cout << "\t\t\t\t\t\t==================" << endl;
		cout << "\t\t\t\t\t\t  File Not Found." << endl;
		cout << "\t\t\t\t\t\t==================" << endl;

	}
	else
	{
		T value = 0;
		while (!fin.eof())
		{
			fin >> value;
			this->Insert(value);
		}
	}
}

template <class T>
void RedBlackTree<T>::RemoveDuplicates()	//Removing Duplicate Values From Tree if there exists any using Recursive Wrapper Function.
{
	if (this->root != nullptr)
		this->REMOVEDUPLICATES(this->root);
	else
		cout << "\t\t Tree is Empty." << endl;
}

template <class T>
void RedBlackTree<T>::DestroyTree()		// Destroying the Tree using a Recursive Wrapper Function.
{
	if (this->root != nullptr)
		DESTROYTREE(this->root);
}

template <class T>
bool RedBlackTree<T>::isEmpty()		// To Check if the Tree is Empty or not.
{
	return (this->root == nullptr);
}



														// Essential Functions:
template <class T>
bool RedBlackTree<T>::SEARCH(Node<T>* n, Node<T>*& t, T value)		// A Recursive Wrapper Function that searches if there is a Node with 
{																	// the Given Value is available in the Tree or not.
	if (n == nullptr)
		return false;
	else if (value == n->Data)
	{
		t = n;
		return true;
	}

	return (SEARCH(n->Left, t, value) || SEARCH(n->Right, t, value));
}


template <class T>
void RedBlackTree<T>::DESTROYTREE(Node<T>* n) // A Recursive Wrapper Function for Deleting all the Nodes in the Tree.
{
	if (n == nullptr)
	{
		this->root = nullptr;
		return;
	}
	
	DESTROYTREE(n->Left);
	DESTROYTREE(n->Right);
	n->Left = nullptr;
	n->Right = nullptr;
	delete n;
	n = nullptr;
}

template <class T>
void RedBlackTree<T>::REMOVEDUPLICATES(Node<T>* n) // A Recursive Wrapper Function for resetting the Count of Nodes which is greater than 1.
{												
	if (n == nullptr)
		return;

	if (n->Count > 1)
		n->Count = 1;
	REMOVEDUPLICATES(n->Left);
	REMOVEDUPLICATES(n->Right);
}

template <class T>
RedBlackTree<T>::~RedBlackTree() // Destructor
{
	if (this->root != nullptr) // Destroying the Tree Nodes before the Object memory is released.
		this->DestroyTree();
}

template <class T>
RedBlackTree<T>::RedBlackTree() // Default Constructor
{

}

template <class T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T>& tree) // Copy Constructor
{
	copyTree(tree.root);
}



														// Extra Functions:

template <class T>
Node<T>* RedBlackTree<T>::InitializeNode(Node<T>* node, T value) // Initializing a Node with the Given Value.
{
	node->Data = value;
	node->Color = 'R';
	node->Count = 1;
	node->Left = nullptr;
	node->Right = nullptr;
	return node;
}

template <class T>
void RedBlackTree<T>::FindParent(Node<T>* n, Node<T>* node, Node<T>*& pNode) // Find Parent Node of a Provided Node and Stores it in pNode.
{																			 // Where 'n' is the this->root, 'node' is the node of which 
	if (node == this->root)														 // we're finding the parent of and pNode is the Parent of 'node'.
		return;

	if (n != nullptr)
	{
		if (n->Left == node || n->Right == node)
		{
			pNode = n;
			return;
		}
		FindParent(n->Left, node, pNode);
		FindParent(n->Right, node, pNode);
	}
	else
		return;
}

template <class T>
void RedBlackTree<T>::FindNode(Node<T>* n, Node<T>*& node, T value) // Find the Node matching with provided value. Stores it in 'node'. Where
{																	// n is the root.
	if (n != nullptr)
	{
		if (value == n->Data)
		{
			node = n;
			return;
		}
		else if (value < n->Data)
			FindNode(n->Left, node, value);
		else if (value > n->Data)
			FindNode(n->Right, node, value);
	}
}

template <class T>
void RedBlackTree<T>::copyTree(Node<T>* n) 
{
	if (n == nullptr)
		return;

	this->Insert(n->Data);
	copyTree(n->Left);
	copyTree(n->Right);
}
