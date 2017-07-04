///////////////////////////////////////////////////////////////////////////
//
//  FILENAME: UnsortedList.h
//
//  PROJECT: CS 221 - Programming Assignment #2
//
//  AUTHOR: Jarrod Parkes
//
//  DEVELOPMENT COMPILER: Microsoft Visual Studio 2008 Express Edition
//
//  TARGET PLATFORM: Windows 32-Bit Operating System
//
//  DESCRIPTION: This file contains the interface and implementation
//				 for the UnsortedList ADT which includes its data members, 
//				 methods, and underlying implementations for each method.
//
//  USAGE RESTIRCTIONS: Client privileges strictly granted to: 
//                      Jarrod Parkes, Dr. Lois Harper, UAH CS Department
//
//  HISTORY:
//  Date        Version         Reason for Change
//  03-21-10    I               Started the initial version.
//  03-22-10	II				Added requirement functions Add and DivideAt
//
//  NOTES: - Ask Dr. Harper if having both the implementation and interface
//		     of UnsortedList ADT in one header file is acceptable
//		   - Dr. Harper has confirmed that having both implementation
//			 and interface in the same header file is acceptable
//		   - Dr. Harper stated that only int, string, and char need be tested
//			 for templating capabilites of the UnsortedList ADT
//
///////////////////////////////////////////////////////////////////////////

#ifndef UNSORTEDLIST
#define UNSORTEDLIST

#include <fstream>			// included for file I/O support
#include <sstream>			// included for use of stringstream extraction of ints
#include <string>			// included to allow creation of string class and functions

using namespace std;

const int MAXITEMS = 50;	// maximum amount of nodes allowed in UnsortedList

/*

--AUTHOR'S NOTE--

The UnsortedList ADT is a templated class.  Please note that Dr. Harper only asked that
the template cover the cases of <int>, <char>, and <string>... so only those have been
accounted for; however, the ability to re-use this template to add other data types
to list of those that function correctly with this template does exist.

The UnsortedList ADT has an underlying data structure of the linked list type.  Allocations
of dynamic memory occur, as well as their own deallocations upon the destruction of any
object of the UnsortedList type.

*/

template <class type>
class UnsortedList
{
	public:

		///////////////////////////////////////////////////////////////////////////
		//
		//	Purpose: This struct acts as a templated node for the linked list.
		//
		///////////////////////////////////////////////////////////////////////////
		struct Node
		{
			type data;
			Node *next;
		};

		///////////////////////////////////////////////////////////////////////////
        //
        //  Method Name: UnsortedList()
        //
        //  Purpose: Initialize an instance of the UnsortedList ADT.
        //
        //  Inputs: None
        //
        //  Outputs: None
        //
        //  Returns: None
        //
        //  Preconditions: None 
        //
        //  Postconditions: An empty instance of the UnsortedList ADT
        //
        //  Method Type: Constructor        
        //
        //  Notes: - While there are no apparent inputs, do note that the user must
		//			 specify a type for the templated instance of UnsortedList ADT
        //
        ///////////////////////////////////////////////////////////////////////////
		UnsortedList();

		///////////////////////////////////////////////////////////////////////////
        //
        //  Method Name: UnsortedList(UnsortedList &secondList)
        //
        //  Purpose: Initialize an instance of the UnsortedList ADT that is an 
		//			 identical and DEEP copy of secondList.
        //
        //  Inputs: secondList - an instance of the UnsortedList ADT
        //
        //  Outputs: None
        //
        //  Returns: None
        //
        //  Preconditions: secondList has been initialized and is the same template
		//				   type as this UnsortedList to be constructed
        //
        //  Postconditions: An instance of UnsortedList has been created and is
		//					an identical and DEEP copy of secondList 
        //
        //  Method Type: Constructor [Copy]
        //
        //  Notes: - Both templated types of secondList and this UnsortedList to
		//			 be constructed must be the same
        //
        ///////////////////////////////////////////////////////////////////////////
		UnsortedList(UnsortedList&);

		///////////////////////////////////////////////////////////////////////////
        //
        //  Method Name: ~UnsortedList()
        //
        //  Purpose: Destroy an instance of the UnsortedList ADT properly by deleting
		//			 any existing dynamic memory and relinquishing it back to the OS
		//			 before destroying all instance variables.
        //
        //  Inputs: None
        //
        //  Outputs: None
        //
        //  Returns: None
        //
        //  Preconditions: An instance of the UnsortedList ADT has gone out of scope
        //
        //  Postconditions: This instance of UnsortedList ADT is completely destroyed
		//					and all memory has been properly relinquished
        //
        //  Method Type: Constructor [Destructor]      
        //
        //  Notes: - Automatically called
		//		   - Utilizes the MakeEmpty() function to deallocate all dynamic memory
        //
        ///////////////////////////////////////////////////////////////////////////
		~UnsortedList();

		///////////////////////////////////////////////////////////////////////////
        //
        //  Method Name: GetSize()
        //
        //  Purpose: Determine the size of this UnsortedList ADT.
        //
        //  Inputs: None
        //
        //  Outputs: None
        //
        //  Returns: The number of nodes within this UnsortedList ADT
        //
        //  Preconditions: UnsortedList has been initialized
        //
        //  Postconditions: UnsortedList is unchanged
		//					Function value = number of nodes in UnsortedList
        //
        //  Method Type: Observer      
        //
        //  Notes: None
        //
        ///////////////////////////////////////////////////////////////////////////
		int GetSize() const;

		///////////////////////////////////////////////////////////////////////////
        //
        //  Method Name: IsEmpty()
        //
        //  Purpose: Determines whether the UnsortedList ADT is empty or not.
        //
        //  Inputs: None
        //
        //  Outputs: None
        //
        //  Returns: Boolean value = (size == 0)
        //
        //  Preconditions: UnsortedList has been initialized
        //
        //  Postconditions: UnsortedList is unchanged
        //
        //  Method Type: Observer      
        //
        //  Notes: None
        //
        ///////////////////////////////////////////////////////////////////////////
		bool IsEmpty() const;

		///////////////////////////////////////////////////////////////////////////
        //
        //  Method Name: IsFull()
        //
        //  Purpose: Determines whether the UnsortedList ADT is full or not.
        //
        //  Inputs: None
        //
        //  Outputs: None
        //
        //  Returns: Boolean value = (size == MAXITEMS)
        //
        //  Preconditions: UnsortedList has been initialized
        //
        //  Postconditions: UnsortedList is unchanged
        //
        //  Method Type: Observer      
        //
        //  Notes: const int MAXITEMS = 50
        //
        ///////////////////////////////////////////////////////////////////////////
		bool IsFull() const;

		///////////////////////////////////////////////////////////////////////////
        //
        //  Method Name: MakeEmpty()
        //
        //  Purpose: To delete all existing nodes within this UnsortedList ADT and
		//			 reduce the size of this UnsortedList ADT to (size = 0).  Note,
		//			 this function correctly relinquishes all dynamic memory back
		//			 to the OS.
        //
        //  Inputs: None
        //
        //  Outputs: None
        //
        //  Returns: None
        //
        //  Preconditions: UnsortedList has been initialized
        //
        //  Postconditions: UnsortedList is completely empty and all pointer types
		//					are set to "NULL"
        //
        //  Method Type: Transformer      
        //
        //  Notes: None
        //
        ///////////////////////////////////////////////////////////////////////////
		void MakeEmpty();

		///////////////////////////////////////////////////////////////////////////
        //
        //  Method Name: ReadFromFile(ifstream &inputFile)
        //
        //  Purpose: Retrieve all the contents of a file and store them into this
		//			 instance of the UnsortedList ADT.
        //
        //  Inputs: inputFile - the ifstream variable which is referencing a valid
		//			file location with valid contents
        //
        //  Outputs: None
        //
        //  Returns: None
        //
        //  Preconditions: UnsortedList has been initialized and inputFile contains
		//				   the correct data that corresponds to this UnsortedList ADT's
		//				   template type
        //
        //  Postconditions: UnsortedList has been populated with the contents
		//					of inputFile up to the limit of MAXITEMS
        //
        //  Method Type: Transformer      
        //
        //  Notes: - If inputFile contains valid information, but exceeds the MAXITEMS
		//		     capacity of UnsortedList ADT then only the first 50 items will be
		//		     stored into this UnsortedList ADT
		//		   - There are three verisons of this function written that utilize
		//			 template specialization so to correctly read in values from a file
		//			 of types <int>, <char>, and <string>
		//		   - If this UnsortedList was already populated with data before ReadFromFile
		//			 was called, then all contents are overriden
        //
        ///////////////////////////////////////////////////////////////////////////
		void ReadFromFile(ifstream&);

		///////////////////////////////////////////////////////////////////////////
        //
        //  Method Name: PrintToScreen()
        //
        //  Purpose: Print the entire contents of this UnsortedList ADT to the screen.
        //
        //  Inputs: None
        //
        //  Outputs: A list seperated by commas (,) of each node within this UnsortedList
        //
        //  Returns: None
        //
        //  Preconditions: UnsortedList has been initialized
        //
        //  Postconditions: UnsortedList is unchanged
        //
        //  Method Type: Iterator      
        //
        //  Notes: None
        //
        ///////////////////////////////////////////////////////////////////////////
		void PrintToScreen() const;

		///////////////////////////////////////////////////////////////////////////
        //
        //  Method Name: PrintToFile(ofstream &outFile)
        //
        //  Purpose: Print the entire contents of this UnsortedList ADT to outFile.
        //
        //  Inputs: outFile - the ofstream variable which is referencing a valid
		//			file location for writing of contents to take place
        //
        //  Outputs: A list seperated by commas (,) of each node within this UnsortedList
        //
        //  Returns: None
        //
        //  Preconditions: UnsortedList has been initialized
        //
        //  Postconditions: UnsortedList is unchanged and outFile contains the entire
		//					contents of this UnsortedList ADT
        //
        //  Method Type: Iterator      
        //
        //  Notes: None
        //
        ///////////////////////////////////////////////////////////////////////////
		void PrintToFile(ofstream&) const;

		///////////////////////////////////////////////////////////////////////////
        //
        //  Method Name: Insert(const type &item)
        //
        //  Purpose: Insert a node with the value of item into this UnsortedList ADT 
		//			 as long as it has not exceeded capacity of MAXITEMS.
        //
        //  Inputs: item - a variable of one of the valid template types <int>, <char>
		//			or <string>
        //
        //  Outputs: None
        //
        //  Returns: None
        //
        //  Preconditions: UnsortedList has been initialized and item is a valid variable
		//				   of one of the templated types
        //
        //  Postconditions: Item has been stored into the UnsortedList ADT as long as MAXITEMS
		//					capacity has not been exceeded, otherwise item is not stored and
		//					no error is thrown (fails silently)
		//					Item is unchanged
        //
        //  Method Type: Transformer      
        //
        //  Notes: - const int MAXITEMS = 50
		//		   - Valid template types : <int>, <char>, and <string>
        //
        ///////////////////////////////////////////////////////////////////////////
		void Insert(const type&);

		///////////////////////////////////////////////////////////////////////////
        //
        //  Method Name: DivideAt(UnsortedList &secondList, const type &item)
        //
        //  Purpose: Divide this UnsortedList ADT at the first node that contains
		//			 the same value as item. The remaining part of the list and found
		//			 node will be added to the second list.  Note that if the item does 
		//			 not exist in this UnsortedList then both lists remain unchanged.
        //
        //  Inputs: secondList - the UnsortedList to be populated with the rest of
		//			this UnsortedList if a node is found with the same value as item
		//			item - a variable of one of the valid template types <int>, <char>
		//			or <string> to be searched for in this UnsortedList
        //
        //  Outputs: None
        //
        //  Returns: None
        //
        //  Preconditions: UnsortedList and secondList have been initialized
		//				   UnsortedList and secondList are of the same templated type
		//				   Item is a valid variable of one of the templated types
        //
        //  Postconditions: If item is found then this UnsortedList ADT has been split
		//					at the node containing that value and the rest of UnsortedList
		//					(including the found node) is stored into secondList
		//					Otherwise the item is not found and the function does nothing
		//					Item is unchanged 
        //
        //  Method Type: Transformer      
        //
        //  Notes: - Valid template types : <int>, <char>, and <string>
		//		   - If the item found is at the head of the list, then this UnsortedList
		//			 will be empty following the function execution
        //
        ///////////////////////////////////////////////////////////////////////////
		void DivideAt(UnsortedList&, const type&);

		///////////////////////////////////////////////////////////////////////////
        //
        //  Method Name: Add(const UnsortedList &secondList, UnsortedList &thirdList)
        //
        //  Purpose: Adds the contents of each node from this UnsortedList and secondList
		//			 into thirdList.
        //
        //  Inputs: secondList - an UnsortedList to be iterated through in order modify
		//			thirdList
		//			thirdList - the UnsortedList to be filled with added contents from
		//		    this UnsortedList and secondList
        //
        //  Outputs: None
        //
        //  Returns: None
        //
        //  Preconditions: UnsortedList, secondList, and thirdList have been initialized
		//				   UnsortedList, secondList, and thirdList are all of the same
		//				   templated type
        //
        //  Postconditions: thirdList contains the added contents of UnsortedList and
		//					secondList
		//					UnsortedList and secondList are unchanged
        //
        //  Method Type: Iterator      
        //
        //  Notes: - Valid template types : <int>, <char>, and <string>
		//		   - When adding ints the sum is a number
		//		   - When adding chars, it is adding the decimal value representation
		//		   - When adding strings, concatenation is preformed on both strings
		//		   - In the case the UnsortedList is larger than secondList all unaccounted
		//			 nodes in the smaller UnsortedList will act as an empty node with
		//			 a default empty value:
		//			 <int> = 0
		//			 <char> = NUL <-- the null character, same as char(0)
		//			 <string> = ""
        //
        ///////////////////////////////////////////////////////////////////////////
		void Add(const UnsortedList&, UnsortedList&);

	private:
		int size;			// numbers of nodes within this UnsortedList ADT
		Node *head;			// pointer to the first node of this UnsortedList ADT (by default = NULL)
};

#endif

template <class type>
UnsortedList<type>::UnsortedList()
{
	// initialize data members
	head = NULL;
	size = 0;
}

template <class type>
UnsortedList<type>::UnsortedList(UnsortedList &secondList)
{	
	head = NULL;
	size = 0;

	if(secondList.IsEmpty())
	{
		return;
	}

	// the secondList is not empty
	else
	{
		// start at the head of secondList
		Node* current = secondList.head;

		// add all nodes up to the last node to this UnsortedList
		while(current->next)
		{
			Insert(current->data);
			current = current->next;
		}

		// add the final node to this UnsortedList
		Insert(current->data);
	}
}

template <class type>
UnsortedList<type>::~UnsortedList()
{
	// relinquishes all dynamically allocated data
	MakeEmpty();
}

template <class type>
int UnsortedList<type>::GetSize() const
{
	return size;
}

template <class type>
bool UnsortedList<type>::IsEmpty() const
{
	if(size == 0)
	{
		return true;
	}
	
	else
	{
		return false;
	}
}

template <class type>
bool UnsortedList<type>::IsFull() const
{
	if(size == MAXITEMS)
	{
		return true;
	}
	
	else
	{
		return false;
	}
}

template <class type>
void UnsortedList<type>::MakeEmpty()
{
	Node* current = NULL;
	Node* trailer = NULL;

	if(!IsEmpty())
	{
		// start at the head of this UnsortedList ADT
		while(head->next != NULL)
		{
			current = head;
			trailer = head;

			// move to the last node, while keeping track of one node behind current
			while(current->next)
			{
				trailer = current;
				current = current->next;
			}

			// delete the last node in the list and if anything pointed to it, set it NULL
			delete current;
			trailer->next = NULL;
			size--;
		}
	}

	// remove to head, set it to NULL
	delete head;
	head = NULL;
	size = 0;
}

template <>
void UnsortedList<int>::ReadFromFile(ifstream &inputFile)
{
	// overwritting old contents, remove everything
	MakeEmpty();

	// read all lines from file, and parse them to ints for storage
	string inputLine;
	int value;

	getline(inputFile, inputLine);
	stringstream(inputLine) >> value;

	while(inputFile)
	{
		Insert(value);
		getline(inputFile, inputLine);
		stringstream(inputLine) >> value;
	}

	inputFile.close();
}

template <>
void UnsortedList<char>::ReadFromFile(ifstream &inputFile)
{
	// overwritting old contents, remove everything
	MakeEmpty();

	// read all lines from file, and take the first index of string for storage
	// NOTE: assume the user is reading from files with one char per line!
	string inputLine;
	char value;

	getline(inputFile, inputLine);
	value = inputLine[0];

	while(inputFile)
	{
		Insert(value);
		getline(inputFile, inputLine);
		value = inputLine[0];
	}

	inputFile.close();
}

template <>
void UnsortedList<string>::ReadFromFile(ifstream &inputFile)
{
	// overwritting old contents, remove everything
	MakeEmpty();

	// read each line from file and store it
	string inputLine;
	getline(inputFile, inputLine);

	while(inputFile)
	{
		Insert(inputLine);
		getline(inputFile, inputLine);
	}

	inputFile.close();
}

template <class type>
void UnsortedList<type>::PrintToScreen() const
{
	if(IsEmpty())
	{
		cout<<"List is empty!\n";
	}

	// iterate through every node and print the node value and a comma (,) to file
	else
	{
		Node* current = head;

		while(current->next)
		{
			cout<<current->data<<", ";
			current = current->next;
		}

		cout<<current->data<<"\n";
	}
}

template <class type>
void UnsortedList<type>::PrintToFile(ofstream &outputFile) const
{
	if(IsEmpty())
	{
		outputFile<<"List is empty!\n";
	}

	// iterate through every node and print the node value and a comma (,) to screen
	else
	{
		Node* current = head;

		while(current->next)
		{
			outputFile<<current->data<<", ";
			current = current->next;
		}

		outputFile<<current->data<<"\n";
	}
}

template <class type>
void UnsortedList<type>::Insert(const type &item)
{
	if(!IsFull())
	{
		// if this item is to be the first node
		if(IsEmpty())
		{
			head = new Node;
			head->data = item;
			head->next = NULL;
		}

		// find the end of the list
		else
		{
			Node* current = head;

			while(current->next)
			{
				current = current->next;
			}

			// add node to end of list and point to it
			current->next = new Node;
			current->next->data = item;
			current->next->next = NULL;
		}

		size++;
	}	
}

template <class type>
void UnsortedList<type>::DivideAt(UnsortedList &secondList, const type &item)
{
	Node* current = NULL;
	Node* currentCopy = NULL;
	Node* trailer = NULL;

	bool found = false;

	if(IsEmpty())
	{
		return;
	}

	// search for item
	else
	{
		current = head;
		
		// iterate through list until found or at end
		while(!found && current->next)
		{
			if(current->data == item)
			{
				found = true;
			}

			// keep track of previous node
			// NOTE: trailer is only important if empty or contains one node
			else
			{
				trailer = current;
				current = current->next;
			}
		}

		// is the last node the item?
		if(current->data == item)
		{
			found = true;
		}
	}

	if(found)
	{
		// if found, empty secondList's contents
		secondList.MakeEmpty();

		// if the item was found at the head of this UnsortedList
		if(current == head)
		{
			while(head != NULL)
			{
				head = head->next;
				secondList.Insert(current->data);
				delete current;
				size--;
				current = head;
			}
		}

		// if found anywhere else
		else
		{
			trailer->next = NULL;

			while(current != NULL)
			{
				currentCopy = current;
				secondList.Insert(current->data);
				current = current->next;
				delete currentCopy;
				size--;
			}
		}
	}
}

template <>
void UnsortedList<int>::Add(const UnsortedList &secondList, UnsortedList &thirdList)
{
	// empty thirdList
	thirdList.MakeEmpty();

	// which list is larger?
	int size2 = secondList.GetSize();
	int maxSize = (size > size2) ? size : size2;

	int value1 = 0;
	int value2 = 0;
	
	Node* current = head;
	Node* current2 = secondList.head;

	// iterate through each list, once one list is finished...
	// if the loop continues use empty values
	for(int x = 0; x < maxSize; x++)
	{
		if(current != NULL)
		{
			value1 = current->data;
			current = current->next;
		}

		else
		{
			value1 = 0;
		}

		if(current2 != NULL)
		{
			value2 = current2->data;
			current2 = current2->next;
		}

		else
		{
			value2 = 0;
		}

		thirdList.Insert(value1+value2);
	}
}

template <>
void UnsortedList<char>::Add(const UnsortedList &secondList, UnsortedList &thirdList)
{
	// empty thirdList
	thirdList.MakeEmpty();

	// which list is larger?
	int size2 = secondList.GetSize();
	int maxSize = (size > size2) ? size : size2;

	char value1 = char(0);
	char value2 = char(0);
	
	Node* current = head;
	Node* current2 = secondList.head;

	// iterate through each list, once one list is finished...
	// if the loop continues use empty values
	for(int x = 0; x < maxSize; x++)
	{
		if(current != NULL)
		{
			value1 = current->data;
			current = current->next;
		}

		else
		{
			value1 = char(0);
		}

		if(current2 != NULL)
		{
			value2 = current2->data;
			current2 = current2->next;
		}

		else
		{
			value2 = char(0);
		}

		thirdList.Insert((char)value1+value2);
	}
}

template <>
void UnsortedList<string>::Add(const UnsortedList &secondList, UnsortedList &thirdList)
{
	// empty thirdList
	thirdList.MakeEmpty();

	// which list is larger?
	int size2 = secondList.GetSize();
	int maxSize = (size > size2) ? size : size2;

	string value1 = "";
	string value2 = "";
	
	Node* current = head;
	Node* current2 = secondList.head;

	// iterate through each list, once one list is finished...
	// if the loop continues use empty values
	for(int x = 0; x < maxSize; x++)
	{
		if(current != NULL)
		{
			value1 = current->data;
			current = current->next;
		}

		else
		{
			value1 = "";
		}

		if(current2 != NULL)
		{
			value2 = current2->data;
			current2 = current2->next;
		}

		else
		{
			value2 = "";
		}

		thirdList.Insert(value1 + value2);
	}
}