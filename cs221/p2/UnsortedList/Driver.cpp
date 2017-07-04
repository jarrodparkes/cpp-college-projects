///////////////////////////////////////////////////////////////////////////
//
//  FILENAME: Driver.cpp
//
//  PROJECT: CS 221 - Programming Assignment #2
//
//  AUTHOR: Jarrod Parkes
//
//  DEVELOPMENT COMPILER: Microsoft Visual Studio 2008 Express Edition
//
//  TARGET PLATFORM: Windows 32-Bit Operating System
//
//  DESCRIPTION: This file contains the module-level testing for the
//               UnsortedList ADT through instantiation and testing of
//               UnsortedList's methods.
//
//  USAGE RESTIRCTIONS: Client privileges strictly granted to: 
//                      Jarrod Parkes, Dr. Lois Harper, UAH CS Department
//
//  HISTORY:
//  Date        Version         Reason for Change
//  03-21-10    I               Started the initial version.
//	03-22-10	II				Added code to preview UnsortedList ADT template.
//
//  NOTES: - Dr. Harper stated that only int, string, and char need be tested
//			 for templating capabilites of the UnsortedList ADT
//		   - Other external files were used for testing but are not included
//			 in the .sln Project File.  They are included in test docs!
//
///////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include "UnsortedList.h"

using namespace std;

void main()
{
	// the master output file
	ofstream myOutFile("ListOut.txt");

	// various input files with int data
	ifstream myIntFile1("input01.txt");
	ifstream myIntFile2("input02.txt");
	ifstream myIntFile3("input03.txt");

	// various input files with char data
	ifstream myCharFile1("input04.txt");
	ifstream myCharFile2("input05.txt");
	ifstream myCharFile3("input06.txt");

	// various input files with string data
	ifstream myStringFile1("input07.txt");
	ifstream myStringFile2("input08.txt");
	ifstream myStringFile3("input09.txt");

	/*
		
		Each of these modules help demonstate:
	
		1.) the declaration of templated UnsortedLists
		2.) the use of the copy constructor
		3.) the use of DivideAt and Add functions
		4.) the use of various UnsortedList functions

	*/
	
	// --------------------------- <int> MODULE -------------------------------------

	myOutFile<<"<int> MODULE\n\n";
	
	UnsortedList<int> intList1;
	intList1.ReadFromFile(myIntFile1);
	UnsortedList<int> intList2;
	UnsortedList<int> intList3;
	intList3.ReadFromFile(myIntFile3);

	myOutFile<<"List1: ";
	intList1.PrintToFile(myOutFile);
	myOutFile<<"List2: ";
	intList2.PrintToFile(myOutFile);
	myOutFile<<"List3: ";
	intList3.PrintToFile(myOutFile);
	myOutFile<<"\n\n";

	intList3.DivideAt(intList2, 34);

	myOutFile<<"List3: ";
	intList3.PrintToFile(myOutFile);
	myOutFile<<"List2: ";
	intList2.PrintToFile(myOutFile);
	myOutFile<<"\n\n";

	intList2.MakeEmpty();

	myOutFile<<"List2: ";
	intList2.PrintToFile(myOutFile);
	myOutFile<<"\n\n";

	intList2.ReadFromFile(myIntFile2);

	myOutFile<<"List2: ";
	intList2.PrintToFile(myOutFile);
	myOutFile<<"\n\n";

	UnsortedList<int> intList4;
	intList1.Add(intList3, intList4);

	myOutFile<<"List4: ";
	intList4.PrintToFile(myOutFile);
	myOutFile<<"\n\n";

	// ------------------------------------------------------------------------------

	// ---------------------------- <char> MODULE -----------------------------------

	myOutFile<<"<char> MODULE\n\n";

	UnsortedList<char> charList1;
	charList1.ReadFromFile(myCharFile1);
	UnsortedList<char> charList2(charList1);
	UnsortedList<char> charList3;
	charList3.ReadFromFile(myCharFile2);

	myOutFile<<"List1: ";
	charList1.PrintToFile(myOutFile);
	myOutFile<<"List2: ";
	charList2.PrintToFile(myOutFile);
	myOutFile<<"List3: ";
	charList3.PrintToFile(myOutFile);
	myOutFile<<"\n\n";

	charList2.DivideAt(charList3, 'f');

	myOutFile<<"List2: ";
	charList2.PrintToFile(myOutFile);
	myOutFile<<"List3: ";
	charList3.PrintToFile(myOutFile);
	myOutFile<<"\n\n";

	charList2.ReadFromFile(myCharFile3);
	charList2.Add(charList3, charList1);

	myOutFile<<"List1: ";
	charList1.PrintToFile(myOutFile);
	myOutFile<<"\n\n";

	// ------------------------------------------------------------------------------

	// ---------------------------- <string> MODULE ---------------------------------

	myOutFile<<"<string> MODULE\n\n";

	UnsortedList<string> stringList1;
	stringList1.ReadFromFile(myStringFile1);
	UnsortedList<string> stringList2(stringList1);
	UnsortedList<string> stringList3;
	stringList3.ReadFromFile(myStringFile2);

	myOutFile<<"List1: ";
	stringList1.PrintToFile(myOutFile);
	myOutFile<<"List2: ";
	stringList2.PrintToFile(myOutFile);
	myOutFile<<"List3: ";
	stringList3.PrintToFile(myOutFile);
	myOutFile<<"\n\n";

	stringList2.DivideAt(stringList3, "dog");
	stringList2.Insert("i added a node!");

	myOutFile<<"List2: ";
	stringList2.PrintToFile(myOutFile);
	myOutFile<<"List3: ";
	stringList3.PrintToFile(myOutFile);
	myOutFile<<"\n\n";

	stringList2.ReadFromFile(myStringFile3);
	stringList2.Add(stringList3, stringList1);

	myOutFile<<"List1: ";
	stringList1.PrintToFile(myOutFile);

	// ------------------------------------------------------------------------------

	myOutFile.close();
	system("pause");
}