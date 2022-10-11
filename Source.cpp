//									    	   Project Name: Red-Black Tree Implementation
//										 	 	  	        Semester: 4th
//											         Project Type: Group Project
//												   	  Instructor: Sir Waqas Arshid
//											 	Lab Instructor: Sir Muhammad Zeeshan
//										 Group Member 1: Syed Ahmed Ali | Reg#: L1F20BSCS0207
//										 Group Member 2: Hamail Shahbaz | Reg#: L1F20BSCS0466

#include "RedBlackTree.h"
#include <conio.h>
void menu();
int main()
{
	RedBlackTree<int> tree;
	char color = '\0';
	int choice = 0, value = 0;
	bool flag = false;
	cout << "\t\t\t\t\t   ~~ Red-Black Tree Project ~~" << endl;
	while (choice != 13)
	{
		if (choice != 0)
		{
			cout << "\n\t\t\t\t\t ---------------------------------" << endl;
			cout << "\t\t\t\t\t     Press a Key to Continue.." << endl;
			cout << "\t\t\t\t\t ---------------------------------" << endl;
			_getch();
			system("cls");
		}
		menu();
		cout << "\t\t Enter Choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
				  cout << "\t\t Enter Value You Want to Insert: "; cin >> value;
				  tree.Insert(value);
				  break;
		}

		case 2:
		{

				  cout << "\t\t Enter Value You Want to Insert: "; cin >> value;
				  flag = tree.Search(value, color);
				 cout << "\t\t\t\t\t=======================================" << endl;
				 if (flag)
					 cout << "\t\t\t\t\t  Value '" << value << "' (" << color << ") is Found in the Tree." << endl;
				  else
					  cout << "\t\t\t\t\t  Value '" << value << "' is not Found in the Tree." << endl;
				  cout << "\t\t\t\t\t=======================================" << endl;
				  break;
		}

		case 3:
		{
				  tree.PreOrder(1);
				  break;
		}

		case 4:
		{
				  tree.InOrder(1);
				  break;
		}

		case 5:
		{
				  tree.PostOrder(1);
				  break;
		}

		case 6:
		{
				  tree.PreOrder(0);
				  break;
		}

		case 7:
		{
				  tree.InOrder(0);
				  break;
		}

		case 8:
		{
				  tree.PostOrder(0);
				  break;
		}

		case 9:
		{
			cout << "\t\t Enter Value You Want to Find Parent of: "; cin >> value;
			if (tree.Search(value,color))
				tree.DisplayParent(value);
			else
				cout << "\t\t Value Not Found in Tree." << endl;
			break;
		}

		case 10:
		{
				   //tree.DestroyTree();
				   tree.ReadFile();
				   break;
		}

		case 11:
		{
				   tree.RemoveDuplicates();
				   break;
		}

		case 12:
		{
				   if (!tree.isEmpty())
				   {
					   tree.DestroyTree();
					   cout << "\t\t\t\t\t\t ===================" << endl;
					   cout << "\t\t\t\t\t\t   Tree Destroyed." << endl;
					   cout << "\t\t\t\t\t\t ===================" << endl;
				   }
				   else
				   {
					   cout << "\t\t\t\t\t\t ===================" << endl;
					   cout << "\t\t\t\t\t\t   Tree is Empty.." << endl;
					   cout << "\t\t\t\t\t\t ===================" << endl;
				   }
				   break;
		}

		case 13:
		{
				   cout << "\t\t\t\t\t ====================================" << endl;
				   cout << "\t\t\t\t\t  Thank You for Testing our Project!" << endl;
				   cout << "\t\t\t\t\t ====================================" << endl;
				   break;
		}

		default:
		{
				   cout << "\n\t\t\t\t\t\t ---------------------" << endl;
				   cout << "\t\t\t\t\t\t     Wrong Choice !" << endl;
				   cout << "\t\t\t\t\t\t ---------------------" << endl;
				   choice = -1;
				   break;
		}
		}
	}
	system("pause");
	return 0;
}

void menu()
{
	cout << "\t\t--------------------------------------------------------------------------------" << endl;
	cout << "\t\t Press 1 to Insert Value in the Tree (one by one)" << endl;
	cout << "\t\t Press 2 for Search Value from the Tree." << endl;
	cout << "\t\t Press 3 for Pre-order Traversal (NLR)" << endl;
	cout << "\t\t Press 4 for In-Order traversal (LNR)" << endl;
	cout << "\t\t Press 5 for Post-Order Traversal (LRN)" << endl;
	cout << "\t\t Press 6 for Pre-Order Traversal 2 (NRL)" << endl;
	cout << "\t\t Press 7 for In-Order Traversal (RNL)" << endl;
	cout << "\t\t Press 8 for Post-Order Traversal (RLN)" << endl;
	cout << "\t\t Press 9 for Displaying Parent of a Node Present in the Tree." << endl;
	cout << "\t\t Press 10 to Read Integer Values from the File to Create a Red-Black Tree." << endl;
	cout << "\t\t Press 11 to Delete all Duplicate Values from the Tree." << endl;
	cout << "\t\t Press 12 to Destroy the Complete Tree." << endl;
	cout << "\t\t Press 13 to Exit Program." << endl;
	cout << "\t\t--------------------------------------------------------------------------------" << endl;
}
