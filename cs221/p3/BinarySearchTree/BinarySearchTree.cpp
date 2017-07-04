///////////////////////////////////////////////////////////////////////////
//
//  FILENAME: BinarySearchTree.cpp
//
//  PROJECT: CS 221 - Programming Assignment #3
//
//  AUTHOR: Jarrod Parkes
//
//  DEVELOPMENT COMPILER: Microsoft Visual Studio 2008 Express Edition
//
//  TARGET PLATFORM: Windows 32-Bit Operating System
//
//  DESCRIPTION: This file contains the implementation for the 
//				 methods included in the interface of the
//				 BinarySearchTree ADT located in the
//				 "BinarySearchTree.h" file.
//
//  USAGE RESTIRCTIONS: Client privileges strictly granted to: 
//                      Jarrod Parkes, Dr. Lois Harper, UAH CS Department
//
//  HISTORY:
//  Date        Version         Reason for Change
//  04-19-10    I               Started the initial version.
//  04-22-10	II				Reordered the listing of functions to emulate
//								the listing in "BinarySearchTree.h"
//
//  NOTES: - Ask Dr. Harper for the final format of possible dictionary.txt
//			 files to be read from during the execution of the
//			 ReadFromFile(...) function call.
//		   - Dr. Harper has confirmed with the class that dictionary.txt
//			 files will be seperated by the newline character '\n'.
//
///////////////////////////////////////////////////////////////////////////

#include <iostream>				// included for standard I/O support
#include "BinarySearchTree.h"	// included to access the BST ADT interface

using namespace std;

/*

PUBLIC METHODS

*/

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
BinarySearchTree::BinarySearchTree()
{
	// initialize all indexes of words[] with "-" or NULL value
	for(int x = 0; x < MAXNODES; x++)
	{
		words[x] = "-";
	}
}

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
int BinarySearchTree::GetSize() const
{
	// call recursive count function
	return Count(0);
}

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
bool BinarySearchTree::IsEmpty() const
{
	if(GetSize() == 0)
	{
		return true;
	}

	else
	{
		return false;
	}
}

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
bool BinarySearchTree::IsFull() const
{
	if(GetSize() == MAXNODES)
	{
		return true;
	}

	else
	{
		return false;
	}
}

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
void BinarySearchTree::MakeEmpty()
{
	// call recursive empty or "delete" function
	EmptyNode(0);
}

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
bool BinarySearchTree::SearchForItem(string word)
{
	bool found = false;
	int foundRoot = -1;

	// modify word to fit criteria of stored nodes
	word = FixWord(word);

	// start search at the root node
	SearchNodes(0, found, foundRoot, word);

	return found;
}

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
void BinarySearchTree::AddDictionaryFile(ifstream &inputFile)
{
	string word;
	
	//	get the first line from inputFile
	getline(inputFile, word);

	// continue to insert each line and read another line until EOF
	while(inputFile)
	{
		InsertItem(word);
		getline(inputFile, word);
	}

	inputFile.close();
}

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
void BinarySearchTree::PrintTree() const
{
	// call the recursive print function
	Print(0);
}

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
void BinarySearchTree::PrintTreeToFile(ofstream &outputFile)
{
	// call the recursive print function (for a file)
	PrintForFile(0, outputFile);
}

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
void BinarySearchTree::InsertItem(string word)
{
	// if the list is not full modify the word and call recursive insert
	if(!IsFull())
	{
		word = FixWord(word);

		// do not insert word if it is empty
		// this handles if user where to input "34653", "()*##@", etc.
		if(word != "")
		{
			Insert(0, word);
		}
	}
}

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
void BinarySearchTree::CheckFile(ifstream &inputFile, ofstream &outputFile)
{
	bool found = false;
	int foundRoot = -1;
	string word;

	// read input file until first encounter space
	getline(inputFile, word, ' ');

	// fix the input string, search for it, and handle accordingly
	while(inputFile)
	{
		word = FixWord(word);

		SearchNodes(0, found, foundRoot, word);

		// prints to "unknown.txt" or other outputFile
		if(!found)
		{
			if(word != "")
			{
				outputFile<<word<<endl;
			}
		}

		else
		{
			found = false;
		}

		getline(inputFile, word, ' ');
	}

	inputFile.close();
}

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
void BinarySearchTree::DeleteItem(string word)
{
	bool found = false;
	int foundRoot = -1;
	
	// does this node exist in this BST ADT?
	SearchNodes(0, found, foundRoot, word);

	// if so, delete it
	if(found)
	{
		Delete(foundRoot);
	}
}

/*

PRIVATE METHODS

*/

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
int BinarySearchTree::Count(int root) const
{
	// as long as the recursive call is not outside MAXNODES limit
	if(root < MAXNODES)
	{
		if(words[root] == "-")
		{
			return 0;
		}

		// count left subtree, right subtree, then count one for the root
		else
		{
			return Count(root * 2 + 1) + Count(root * 2 + 2) + 1;
		}
	}

	else
	{
		return 0;
	}
}

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
void BinarySearchTree::EmptyNode(int root)
{
	if(root < MAXNODES)
	{
		// if the key value is not NULL check left subtree, right subtree,
		// and then delete the key value at root node
		if(words[root] != "-")
		{
			EmptyNode(root * 2 + 1);
			EmptyNode(root * 2 + 2);
			Delete(root);
		}
	}
}

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
void BinarySearchTree::SearchNodes(int root, bool &found, int &foundRoot, string word)
{
	// only continue searching if not found or not at the end of the BST ADT
	if(root < MAXNODES && !found)
	{
		// skip over empty nodes
		if(words[root] != "-")
		{
			// store the location if this node's key value matches the search
			if(words[root] == word)
			{
				found = true;
				foundRoot = root;
			}

			// search the left subtree or right subtree depending on key value
			else
			{
				if(word < words[root])
				{
					SearchNodes(root * 2 + 1, found, foundRoot, word);
				}

				else
				{
					SearchNodes(root * 2 + 2, found, foundRoot, word);
				}
			}
		}
	}
}

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
void BinarySearchTree::Print(int root) const
{
	if(root < MAXNODES)
	{
		// check left subtree, print key value, check right subtree
		if(words[root] != "-")
		{
			Print(root * 2 + 1);
			cout<<words[root]<<endl;
			Print(root * 2 + 2);
		}
	}
}

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
void BinarySearchTree::PrintForFile(int root, ofstream &outputFile)
{
	if(root < MAXNODES)
	{
		// check left subtree, print key value, check right subtree
		if(words[root] != "-")
		{
			PrintForFile(root * 2 + 1, outputFile);
			outputFile<<words[root]<<endl;
			PrintForFile(root * 2 + 2, outputFile);
		}
	}
}

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
string BinarySearchTree::FixWord(string word)
{
	char wordStore[50] = "\0";
	int y = 0;

	// iterates through the word and analyzes each element
	for(unsigned int x = 0; x < word.length(); x++)
	{
		// if the element is a letter store it into wordStore
		// otherwise skip over non-letters
		if(isalpha(word[x]))
		{
			wordStore[y] = (char)tolower(word[x]);
			y++;

			// lowercase! =D!
			word[x] = (char)tolower(word[x]);
		}
	}

	return wordStore;
}

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
void BinarySearchTree::Insert(int root, string word)
{
	// do not look for empty nodes past MAXNODES capacity
	if(root < MAXNODES)
	{
		// this node is empty, insert value here
		if(words[root] == "-")
		{
			words[root] = word;
		}

		else
		{
			// find the next empty node depending on key value
			if(words[root] > word)
			{
				Insert(root * 2 + 1, word);
			}

			else if(words[root] < word)
			{
				Insert(root * 2 + 2, word);
			}
		}
	}
}

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
void BinarySearchTree::Delete(int root)
{
	string word = "-";
	int pRoot = 0;

	if(root < MAXNODES)
	{
		// only set root to NULL value if it has no children
		if(words[root * 2 + 1] == "-" && words[root * 2 + 2] == "-")
		{
			words[root] = "-";
		}

		else
		{
			// has two children, find predecessor to fill in for root
			if(words[root * 2 + 2] != "-" && words[root * 2 + 1] != "-")
			{
				GetPredecessor(root * 2 + 1, word, pRoot);
				words[root] = word;
				Delete(pRoot);
			}

			// has no right child, find predecessor to fill in for root
			else if(words[root * 2 + 2] == "-")
			{
				GetPredecessor(root * 2 + 1, word, pRoot);
				words[root] = word;
				Delete(pRoot);
			}

			// has no left child
			else
			{
				words[root] = words[root * 2 + 2];
				Delete(root * 2 + 2);
			}
		}
	}
}

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
void BinarySearchTree::GetPredecessor(int root, string &word, int &pRoot) const
{
	if(root < MAXNODES)
	{
		word = words[root];
		pRoot = root;

		// continue searching left subtree until the no right child exists
		while(words[root * 2 + 2] != "-")
		{
			root = root * 2 + 2;
			word = words[root];
			pRoot = root;
		}
	}
}