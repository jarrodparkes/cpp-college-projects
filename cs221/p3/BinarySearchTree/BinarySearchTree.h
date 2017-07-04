///////////////////////////////////////////////////////////////////////////
//
//  FILENAME: BinarySearchTree.h
//
//  PROJECT: CS 221 - Programming Assignment #3
//
//  AUTHOR: Jarrod Parkes
//
//  DEVELOPMENT COMPILER: Microsoft Visual Studio 2008 Express Edition
//
//  TARGET PLATFORM: Windows 32-Bit Operating System
//
//  DESCRIPTION: This file contains the interface for the BinarySearchTree
//				 ADT including its data members and methods.
//
//  USAGE RESTIRCTIONS: Client privileges strictly granted to: 
//                      Jarrod Parkes, Dr. Lois Harper, UAH CS Department
//
//  HISTORY:
//  Date        Version         Reason for Change
//  04-19-10    I               Started the initial version.
//  04-21-10    II				Added the FixWord function.
//
//  NOTES: - Determine if implementing a copy constructor or overloaded
//			 equals operator should be included.
//		   - Dr. Harper has confirmed that NO copy constuctor or overloaded
//			 equals operator should be included.
//		   - Functions that should never be called by a user or file other
//			 than the file containing method implementations have been
//			 placed under private.
//
///////////////////////////////////////////////////////////////////////////

#ifndef BINARYSEARCHTREE
#define BINARYSEARCHTREE

#include <string>			// included to allow creation of string class and functions
#include <fstream>			// included for file I/O support

using namespace std;

const int MAXNODES = 16383;	// maximum amount of nodes allowed in this BST

/*

--AUTHOR'S NOTE--

The BST ADT is a graph structure with two important properties...

1) Binary Nodes

Unlike a singularly linked list, each node within a BST structure has the
capability of having two unique children.  Of those two children (left and right),
each child may also have two unique children, and so on.  However, in an array-based
implementation, adding new nodes to the BST will not be allowed after a certain
height.

2) Key Values

In order to implement a Searching algorithm of O(logn), every BST and
BST subtree follow these rules:
	
	- all children in the left subtree of the root node MUST be less
	  than the key value stored in the root node

	- all children in the right subtree of the root node MUST be greater
	  than the key value stored in the root node

Other important things to note about this implementation of the BST ADT...

- An empty or "NULL" node is represented by a dash (-) 
- No duplicates will exist in the BST
- All nodes will be completely lowercase
- All punctuation will be ignored for searching, deleting, and inserting algorithms
- User input will be handled behind the scenes for punctuation and CAPS

*/

class BinarySearchTree
{
	public:
		///////////////////////////////////////////////////////////////////////////
		//
		//  Method Name: BinarySearchTree()
		//
		//  Purpose: Initialize an instance of the BST ADT.
		//
		//  Inputs: None
		//
		//  Outputs: None
		//
		//  Returns: None
		//
		//  Preconditions: None
		//
		//  Postconditions: An empty instance of the BST ADT.
		//
		//  Method Type: Constructor        
		//
		//  Notes: - No inputs are required; however, note that every node within
		//			 the BST ADT will be defaulted to a dash (-) which translates
		//			 to a NULL value for the implementation.
		//
		///////////////////////////////////////////////////////////////////////////
		BinarySearchTree();

		///////////////////////////////////////////////////////////////////////////
		//
		//  Method Name: GetSize()
		//
		//  Purpose: Determines the number of elements in the BST ADT.
		//
		//  Inputs: None
		//
		//  Outputs: None
		//
		//  Returns: The number of non-empty nodes within this BST ADT.
		//
		//  Preconditions: BST has been initialized.
		//
		//  Postconditions: BST is unchanged.
		//					Function value = number of non-empty nodes in BST.
		//
		//  Method Type: Observer
		//
		//  Notes: - While tracking the number of insertions into the BST may be
		//			 a more simple approach to getting size, this implementation
		//			 follows the iterative approach found in the book for counting
		//			 nodes.
		//		   - This function is not available to be called in the menu GUI 
		//			 created in driver.cpp
		//
		///////////////////////////////////////////////////////////////////////////
		int GetSize() const;

		///////////////////////////////////////////////////////////////////////////
		//
		//  Method Name: IsEmpty()
		//
		//  Purpose: Determines whether the BST ADT is empty or not.
		//
		//  Inputs: None
		//
		//  Outputs: None
		//
		//  Returns: Boolean value = return GetSize() = 0.
		//
		//  Preconditions: BST has been initialized.
		//
		//  Postconditions: BST is unchanged.
		//
		//  Method Type: Observer
		//
		//  Notes: - This function is not available to be called in the menu GUI 
		//			 created in driver.cpp
		//
		///////////////////////////////////////////////////////////////////////////
		bool IsEmpty() const;
		
		///////////////////////////////////////////////////////////////////////////
		//
		//  Method Name: IsFull()
		//		
		//  Purpose: Determines whether the BST ADT is full or not.
		//
		//  Inputs: None
		//
		//  Outputs: None
		//
		//  Returns: Boolean value = return GetSize() = MAXNODES.
		//
		//  Preconditions: BST has been initialized.
		//
		//  Postconditions: BST is unchanged.
		//
		//  Method Type: Observer
		//
		//  Notes: - Based on this implementation, this function may never return a value
		//			 other than false because this BST will only be full under the
		//			 assumption that it is a full binary tree.  That scenario is
		//			 rarely possible based on the insertion order of nodes.
		//		   - This function is not available to be called in the menu GUI 
		//			 created in driver.cpp
		//
		///////////////////////////////////////////////////////////////////////////
		bool IsFull() const;
		
		///////////////////////////////////////////////////////////////////////////
		//
		//  Method Name: MakeEmpty()
		//
		//  Purpose: To delete all existing nodes within this BST ADT.
		//
		//  Inputs: None
		//
		//  Outputs: None
		//
		//  Returns: None
		//
		//  Preconditions: BST has been initialized.
		//
		//  Postconditions: BST is completely empty.
		//
		//  Method Type: Transformer
		//
		//  Notes: - Note, all nodes from 0 to MAXNODES still exist; however, 
		//			 each is populated with "-" or a NULL value.
		//		   - This function is not available to be called in the menu GUI 
		//			 created in driver.cpp
		//
		///////////////////////////////////////////////////////////////////////////
		void MakeEmpty();
		
		///////////////////////////////////////////////////////////////////////////
		//
		//  Method Name: SearchForItem(string word)
		//
		//  Purpose: Determine if word exists within this BST ADT.
		//
		//  Inputs: word - the key value to be searched for within this BST ADT
		//
		//  Outputs: None
		//
		//  Returns: Boolean value = (was word found in BST ADT?).
		//
		//  Preconditions: BST has been initialized.
		//				   word is a valid string arguement.
		//
		//  Postconditions: BST is unchanged.
		//
		//  Method Type: Observer
		//
		//  Notes: - [NO CONSTRAINTS] If the user calls this function with any
		//			 valid string arguement, all modifications for removing
		//			 punctuation and capital letter is preformed behind the scenes
		//			 before the searching takes place.
		//
		///////////////////////////////////////////////////////////////////////////
		bool SearchForItem(string);
		
		///////////////////////////////////////////////////////////////////////////
		//
		//  Method Name: AddDictionaryFile(ifstream &inputFile)
		//
		//  Purpose: Adds all the unique contents of a text input file into this BST ADT.
		//
		//  Inputs: inputFile - the ifstream variable which is referencing a valid
		//						file location with valid contents.
		//
		//  Outputs: None
		//
		//  Returns: None
		//
		//  Preconditions: BST has been initialized and inputFile contains the
		//				   correct data in the specified format.  The specified format
		//				   decided by Dr. Harper is a list of words seperated by
		//				   newline characters.
		//
		//  Postconditions: BST contains all the unique contents of inputFile in the form
		//					of individual strings. 
		//
		//  Method Type: Transformer
		//
		//  Notes: - [NO CONSTRAINTS] If the user calls this function with any
		//			 valid string arguement, all modifications for removing
		//			 punctuation and capital letter is preformed behind the scenes
		//			 before the searching takes place.
		//		   - If the inputFile contains more words than possible by the insertion
		//			 algorithm of this BST ADT (MAXNODES), then each insertion or 
		//			 add executed after the capacity is reached will fail silently.
		//
		///////////////////////////////////////////////////////////////////////////
		void AddDictionaryFile(ifstream&);
		
		///////////////////////////////////////////////////////////////////////////
		//
		//  Method Name: PrintTree()
		//
		//  Purpose: Print the non-empty nodes of this BST ADT to the screen.
		//
		//  Inputs: None
		//
		//  Outputs: A list of all the non-empty nodes key values stored within
		//			 this implementation of the BST ADT. Each value is seperated
		//			 by the newline character.
		//
		//  Returns: None
		//
		//  Preconditions: BST has been initialized.
		//
		//  Postconditions: BST is unchanged and the list of key values has been
		//					printed to the screen.
		//
		//  Method Type: Iterator
		//
		//  Notes: - Empty nodes or nodes with the key value of a dash (-) will
		//		     not be printed.
		//		   - This function is not available to be called in the menu GUI 
		//			 created in driver.cpp
		//
		///////////////////////////////////////////////////////////////////////////
		void PrintTree() const;
		
		///////////////////////////////////////////////////////////////////////////
		//
		//  Method Name: PrintTreeToFile(ofstream &outputFile)
		//
		//  Purpose: Print the non-empty nodes of this BST ADT to outputFile.
		//		
		//  Inputs: outputFile - the ofstream variable which is referencing a valid
		//						 file location for writing of contents to take place.
		//
		//  Outputs: A list of all the non-empty nodes key values stored within
		//			 this implementation of the BST ADT. Each value is seperated
		//			 by the newline character. Output occurs in outputFile.
		//
		//  Returns: None
		//
		//  Preconditions: BST has been initialized.
		//
		//  Postconditions: BST is unchanged and the list of key values has been
		//					printed to outputFile.
		//
		//  Method Type: Iterator
		//
		//  Notes: - Empty nodes or nodes with the key value of a dash (-) will
		//		     not be printed.
		//		   - This function is not available to be called in the menu GUI 
		//			 created in driver.cpp
		//
		///////////////////////////////////////////////////////////////////////////
		void PrintTreeToFile(ofstream&);
		
		///////////////////////////////////////////////////////////////////////////
		//
		//  Method Name: InsertItem(string word)
		//
		//  Purpose: Insert word into the structure of this BST ADT.
		//
		//  Inputs: word - the key value to be inserted into this BST ADT.
		//
		//  Outputs: None
		//
		//  Returns: None
		//
		//  Preconditions: BST has been initialized.
		//				   word is a valid string arguement.
		//
		//  Postconditions: word has been stored into this BST ADT at the correct
		//					location that ensures the key value property of a
		//					BST as long as the possible storage location does not
		//					exceed MAXNODES and word is not a duplicate key value.
		//
		//  Method Type: Transformer
		//
		//  Notes: - const int MAXNODES = 16383.
		//
		///////////////////////////////////////////////////////////////////////////
		void InsertItem(string);
		
		///////////////////////////////////////////////////////////////////////////
		//
		//  Method Name: CheckFile(ifstream &inputFile, ofstream &outputFile)
		//
		//  Purpose: Check for the correct spelling of the text from inputFile by
		//			 searching for each string (denoted by a space " ") to see if
		//			 it exists in this BST ADT. If it does not exist, then print
		//		     the incorrectly spelled words into outputFile. Otherwise,
		//			 do nothing.
		//
		//  Inputs: inputFile - the ifstream variable which is referencing a valid
		//						file location with valid contents.
		//			outputFile - the ofstream variable which is referencing a valid
		//						 file location for writing of contents to take place.
		//
		//  Outputs: All incorrectly spelled words are printed to outputFile on
		//			 individual lines seperated by the newline character.
		//
		//  Returns: None
		//
		//  Preconditions: BST has been initialized and inputFile contains any
		//				   number of valid character and string combinations.
		//
		//  Postconditions: BST is unchanged and outputFile contains all incorrectly
		//					spelled words as determined by the searches to this BST ADT.
		//
		//  Method Type: Observer
		//
		//  Notes: None
		//
		///////////////////////////////////////////////////////////////////////////
		void CheckFile(ifstream&, ofstream&);
		
		///////////////////////////////////////////////////////////////////////////
		//
		//  Method Name: DeleteItem(string word)
		//
		//  Purpose: To remove the node within this BST ADT if it exists and matches
		//			 word's key value.
		//
		//  Inputs: word - the key value to be removed from this BST ADT.
		//
		//  Outputs: None
		//
		//  Returns: None
		//
		//  Preconditions: BST has been initialized.
		//				   word is a valid string arguement.
		//
		//  Postconditions: If word was found at a node within this BST ADT, then
		//					that node has been removed and subsequent functions
		//					have been called to shift remaining nodes to
		//					satisfy the shape property of a BST.
		//
		//  Method Type: Transformer
		//
		//  Notes: - This function is not available to be called in the menu GUI 
		//			 created in driver.cpp
		//
		///////////////////////////////////////////////////////////////////////////
		void DeleteItem(string);
	
	private:
		///////////////////////////////////////////////////////////////////////////
		//
		//  Method Name: Count(int root)
		//
		//  Purpose: Recursively count all the non-emtpy nodes in this BST ADT.
		//
		//  Inputs: root - the current index being visited in words[].
		//
		//  Outputs: None
		//
		//  Returns: The sumlimation of all non-empty nodes in this BST ADT.
		//
		//  Preconditions: BST has been initialized.
		//
		//  Postconditions: The sum at this point of the recursion has been
		//					returned to the calling address of this function.
		//
		//  Method Type: Observer
		//
		//  Notes: - This function executes in a post order traversal.
		//		   - This function is called by the GetSize function.
		//
		///////////////////////////////////////////////////////////////////////////
		int Count(int) const;
		
		///////////////////////////////////////////////////////////////////////////
		//
		//  Method Name: EmptyNode(int root)
		//
		//  Purpose: Recursively empty all nodes in this BST ADT.
		//
		//  Inputs: root - the current index being visited in words[].
		//
		//  Outputs: None
		//
		//  Returns: None
		//
		//  Preconditions: BST has been initialized.
		//
		//  Postconditions: BST is completely empty.
		//
		//  Method Type: Transformer
		//
		//  Notes: - This function executes in a post order traversal.
		//		   - Note, all nodes from 0 to MAXNODES still exist; however, 
		//			 each is populated with "-" or a NULL value.
		//		   - This function is called by the MakeEmpty function.
		//
		///////////////////////////////////////////////////////////////////////////
		void EmptyNode(int);
		
		///////////////////////////////////////////////////////////////////////////
		//
		//  Method Name: SearchNodes(int root, bool &found, int &foundRoot, string word)
		//
		//  Purpose: Recursively check all nodes in this BST ADT until the searched
		//		     key value is found or all nodes have been checked. The searched
		//			 key value is the value of word.
		//
		//  Inputs: root - the current index being visited in words[].
		//
		//  Outputs: None
		//
		//  Returns: None
		//
		//  Preconditions: BST has been initialized.
		//				   found is set to false before function call.
		//				   foundRoot is a valid int arguement.
		//				   word is a valid string arguement.
		//
		//  Postconditions: found has been set to true if the searched key value
		//					was found in this BST ADT.  Also, if(found) then
		//					foundRoot contains the index location of the specific
		//					key value that matches word.
		//
		//  Method Type: Observer
		//
		//  Notes: - This is the algorithm for a binary search of 0(logn) efficiency.
		//		   - This function is called from several other functions which may
		//			 or may not use foundRoot for subsequent operations.
		//
		///////////////////////////////////////////////////////////////////////////
		void SearchNodes(int, bool&, int&, string);
		
		///////////////////////////////////////////////////////////////////////////
		//
		//  Method Name: Print(int root)
		//
		//  Purpose: Recursively prints all the non-empty nodes in this BST ADT
		//			 to the screen.
		//
		//  Inputs: root - the current index being visited in words[].
		//
		//  Outputs: A list of all the non-empty nodes key values stored within
		//			 this implementation of the BST ADT. Each value is seperated
		//			 by the newline character.
		//
		//  Returns: None
		//
		//  Preconditions: BST has been initialized.
		//
		//  Postconditions: All the non-empty nodes of this BST ADT have been
		//					printed to the screen.
		//
		//  Method Type: Iterator
		//
		//  Notes: - This function executes in an in-order traversal.
		//		   - This function is called by the PrintTree function.
		//
		///////////////////////////////////////////////////////////////////////////
		void Print(int) const;
		
		///////////////////////////////////////////////////////////////////////////
		//
		//  Method Name: PrintForFile(int root, ofstream &outputFile)
		//
		//  Purpose: Recursively prints all the non-empty nodes in this BST ADT
		//			 to outputFile.
		//
		//  Inputs: root - the current index being visited in words[].
		//			outputFile - the ofstream variable which is referencing a valid
		//						 file location for writing of contents to take place. 
		//
		//  Outputs: A list of all the non-empty nodes key values stored within
		//			 this implementation of the BST ADT. Each value is seperated
		//			 by the newline character. Output occurs in outputFile.
		//
		//  Returns: None
		//
		//  Preconditions: BST has been initialized.
		//
		//  Postconditions: All the non-empty nodes of this BST ADT have been
		//					printed to outputFile.
		//
		//  Method Type: Iterator
		//
		//  Notes: - This function executes in an in-order traversal.
		//		   - This function is called by the PrintTreeToFile function.
		//
		///////////////////////////////////////////////////////////////////////////
		void PrintForFile(int, ofstream&);
		
		///////////////////////////////////////////////////////////////////////////
		//
		//  Method Name: FixWord(string word)
		//
		//  Purpose: To alter word into a string value that only contains
		//			 lowercase letters and no punctuation for further operations.
		//
		//  Inputs: word - the key value to be edited before subsequent operations
		//				   on this BST ADT. 
		//
		//  Outputs: None
		//
		//  Returns: Return value = the modified version of word with no punctuation 
		//			 and all lowercase letters.
		//
		//  Preconditions: BST has been initialized.
		//				   word is a valid string arguement.
		//
		//  Postconditions: word has no punctuation or uppercase letters and now
		//					fits the criteria for this implementation of a BST.
		//
		//  Method Type: Transformer
		//
		//  Notes: - This function is a helper function that facilitates the need
		//			 of some type of consitant property for all nodes within
		//			 this BST ADT.
		//
		///////////////////////////////////////////////////////////////////////////
		string FixWord(string);
		
		///////////////////////////////////////////////////////////////////////////
		//
		//  Method Name: Insert(int root, string word)
		//
		//  Purpose: Recursively find the correct location and then insert word 
		//			 into the structure of this BST ADT.
		//
		//  Inputs: root - the current index being visited in words[]. 
		//			word - the key value to be inserted into this BST ADT.
		//
		//  Outputs: None
		//
		//  Returns: None
		//
		//  Preconditions: BST has been initialized.
		//				   word is a valid string arguement.
		//
		//  Postconditions: word has been stored into this BST ADT at the correct
		//					location that ensures the key value property of a
		//					BST as long as the possible storage location does not
		//					exceed MAXNODES and word is not a duplicate key value.
		//
		//  Method Type: Transformer
		//
		//  Notes: - const int MAXNODES = 16383.
		//
		///////////////////////////////////////////////////////////////////////////
		void Insert(int, string);

		///////////////////////////////////////////////////////////////////////////
		//
		//  Method Name: Delete(int root)
		//
		//  Purpose: To remove the node within this BST ADT at words[root].
		//
		//  Inputs: root - the current index being visited in words[].
		//
		//  Outputs: None
		//
		//  Returns: None
		//
		//  Preconditions: BST has been initialized.
		//
		//  Postconditions: The node at location words[root] has been emptied or
		//					stored with a dash (-).  Subsequent functions are called
		//					to reorder the BST so that it satisfies the shape and
		//					key properties of a BST.
		//
		//  Method Type: Transformer
		//
		//  Notes: - This function is called by the DeleteItem function.
		//		   - This function deletes nodes that fit into one of
		//			 three classifications:
		//			 1) the node has no children
		//			 2) the node atleast has one child
		//			 3) the node has both children
		//
		///////////////////////////////////////////////////////////////////////////
		void Delete(int);
		
		///////////////////////////////////////////////////////////////////////////
		//
		//  Method Name: GetPredecessor(int root, string &word, int &pRoot)
		//
		//  Purpose: To find the largest key value in the deleted root's left
		//			 subtree as to replace the node once it has been deleted.
		//
		//  Inputs: root - the current index being visited in words[].
		//			word - a string value to be populated with contents of root's
		//				   largest predecessor
		//			pRoot - the index location of root's largest predecessor
		//
		//  Outputs: None
		//
		//  Returns: None
		//
		//  Preconditions: BST has been initialized.
		//
		//  Postconditions: The largest predecessor of root is located and its
		//					key value and index have been stored into word and
		//					pRoot.
		//
		//  Method Type: Observer
		//
		//  Notes: - This function is called by the Delete function in cases
		//			 where a predecessor must be found to restructure this BST ADT.
		//
		///////////////////////////////////////////////////////////////////////////
		void GetPredecessor(int, string&, int&) const;

		string words[MAXNODES];		// the underlying data structure for this BST ADT
};

#endif