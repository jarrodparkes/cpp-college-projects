///////////////////////////////////////////////////////////////////////////
//
//  FILENAME: PrimeList.h
//
//  PROJECT: CS 221 - Programming Assignment #1
//
//  AUTHOR: Jarrod Parkes
//
//  DEVELOPMENT COMPILER: Microsoft Visual Studio 2008
//
//  TARGET PLATFORM: Windows 32-Bit Operating System
//
//  DESCRIPTION: This file contains the interface for the PrimeList ADT
//               which includes its data members and methods.
//
//  USAGE RESTIRCTIONS: Client privileges strictly granted to: 
//                      Jarrod Parkes, Dr. Lois Harper, UAH CS Department
//
//  HISTORY:
//  Date        Version         Reason for Change
//  02-10-10    I               This is the intial version.
//
//  NOTES:
//
///////////////////////////////////////////////////////////////////////////

#ifndef PRIMELIST_H
#define PRIMELIST_H

// include for use of ofstream (SEE PrintToFile(ofstream&))
#include <fstream>

using namespace std;

// maximum amount of elements allowed in a PrimeList
const int MAXNUM = 10000;

class PrimeList
{
    public:
        
        ///////////////////////////////////////////////////////////////////////////
        //
        //  Method Name: PrimeList()
        //
        //  Purpose: Initialize an instance of the PrimeList class
        //
        //  Inputs: None
        //
        //  Outputs: None
        //
        //  Returns: None
        //
        //  Preconditions: None 
        //
        //  Postconditions: An empty instance of the PrimeList class
        //
        //  Method Type: Constructor        
        //
        //  Notes: None              
        //
        ///////////////////////////////////////////////////////////////////////////
        PrimeList();

        ///////////////////////////////////////////////////////////////////////////
        //
        //  Method Name: PrimeList(int n)
        //
        //  Purpose: Initialize an instance of the PrimeList class
        //
        //  Inputs: n - the maximum bound to check for a prime number during initialization
        //
        //  Outputs: Prints an error if n is out of bounds
        //
        //  Returns: None
        //
        //  Preconditions: None 
        //
        //  Postconditions: The instance of the PrimeList class contains a list of 
        //                  prime numbers from 2 to n
        //
        //  Method Type: Constructor        
        //
        //  Notes: None              
        //
        ///////////////////////////////////////////////////////////////////////////
        PrimeList(int);

        ///////////////////////////////////////////////////////////////////////////
        //
        //  Method Name: NewPrimeList(int n)
        //
        //  Purpose: Resets a PrimeList to a list containing prime numbers from 2 to n          
        //
        //  Inputs: n - the maximum bound to check for a prime number during re-initialization
        //
        //  Outputs: Prints an error if n is out of bounds
        //
        //  Returns: None
        //
        //  Preconditions: PrimeList has been initialized  
        //
        //  Postconditions: The instance of the PrimeList class contains a list of 
        //                  prime numbers from 2 to n
        //
        //  Method Type: Transformer        
        //
        //  Notes: This does not return a new PrimeList, but modifies the instance
        //         from which the function was invoked          
        //
        ///////////////////////////////////////////////////////////////////////////
        void NewPrimeList(int);

        ///////////////////////////////////////////////////////////////////////////
        //
        //  Method Name: ClearList()
        //
        //  Purpose: Resets a PrimeList and its data members to empty
        //
        //  Inputs: None
        //
        //  Outputs: None
        //
        //  Returns: None
        //
        //  Preconditions: PrimeList has been initialized   
        //
        //  Postconditions: PrimeList is empty
        //
        //  Method Type: Transformer         
        //
        //  Notes: None             
        //
        ///////////////////////////////////////////////////////////////////////////
        void ClearList();

        ///////////////////////////////////////////////////////////////////////////
        //
        //  Method Name: IsFull()
        //
        //  Purpose: Determines whether the PrimeList is full
        //
        //  Inputs: None
        //
        //  Outputs: None
        //
        //  Returns: Boolean value = (list is full?)
        //
        //  Preconditions: PrimeList has been initiaized  
        //
        //  Postconditions: PrimeList is unchanged
        //
        //  Method Type: Observer         
        //
        //  Notes: None         
        //
        ///////////////////////////////////////////////////////////////////////////    
        bool IsFull();

        ///////////////////////////////////////////////////////////////////////////
        //
        //  Method Name: GetLength()
        //
        //  Purpose: Determines the number of elements in PrimeList
        //
        //  Inputs: None
        //
        //  Outputs: None
        //
        //  Returns: Number of elements in PrimeList
        //
        //  Preconditions: PrimeList has been initialized  
        //
        //  Postconditions: PrimeList is unchanged
        //                  Function value = number of elements in list
        //
        //  Method Type: Observer        
        //
        //  Notes: None              
        //
        ///////////////////////////////////////////////////////////////////////////    
        int GetLength();

        ///////////////////////////////////////////////////////////////////////////
        //
        //  Method Name: RetrieveItem(int n)
        //
        //  Purpose: Return an element from PrimeList at a certain index
        //
        //  Inputs: n - the index to be searched
        //
        //  Outputs: None
        //
        //  Returns: If n is a valid index, the element is returned (an integer)
        //           Else -1 is returned because n is an invalid index
        //
        //  Preconditions: PrimeList has been initialized 
        //
        //  Postconditions: PrimeList is unchanged, possible integer value is returned
        //
        //  Method Type: Observer         
        //
        //  Notes: A value is always returned           
        //
        ///////////////////////////////////////////////////////////////////////////    
        int RetrieveItem(int);

        ///////////////////////////////////////////////////////////////////////////
        //
        //  Method Name: IsEmpty()
        //
        //  Purpose: Determines whether the list is empty
        //
        //  Inputs: None
        //
        //  Outputs: None
        //
        //  Returns: Boolean value = (list is empty?)
        //
        //  Preconditions: PrimeList has been initialzed  
        //
        //  Postconditions: PrimeList is unchanged
        //
        //  Method Type: Observer        
        //
        //  Notes: None              
        //
        ///////////////////////////////////////////////////////////////////////////
        bool IsEmpty();

        ///////////////////////////////////////////////////////////////////////////
        //
        //  Method Name: PrintToScreen()
        //
        //  Purpose: Prints the entire contents of a PrimeList to the screen
        //
        //  Inputs: None
        //
        //  Outputs: A list of prime numbers from 2 to highNum for this PrimeList
        //
        //  Returns: None
        //
        //  Preconditions: PrimeList has been initialized 
        //
        //  Postconditions: PrimeList is unchanged
        //
        //  Method Type: Iterator
        //
        //  Notes: None             
        //
        ///////////////////////////////////////////////////////////////////////////
        void PrintToScreen();

        ///////////////////////////////////////////////////////////////////////////
        //
        //  Method Name: PrintToFile(ofstream outFile)
        //
        //  Purpose: Prints the entire contents of a PrimeList to outFile
        //
        //  Inputs: None
        //
        //  Outputs: A list of prime numbers from 2 to highNum for this PrimeList
        //
        //  Returns: None
        //
        //  Preconditions: PrimeList has been initialzed
        //
        //  Postconditions: PrimeList is unchanged
        //
        //  Method Type: Iterator         
        //
        //  Notes: None
        //
        ///////////////////////////////////////////////////////////////////////////
        void PrintToFile(ofstream&);

    private:

        ///////////////////////////////////////////////////////////////////////////
        //
        //  Method Name: Add(int n)
        //
        //  Purpose: Adds an item to the PrimeList
        //
        //  Inputs: n - the integer to be added to the PrimeList
        //
        //  Outputs: None
        //
        //  Returns: None
        //
        //  Preconditions: PrimeList has been initialized
        //                 n is a positive prime integer  
        //
        //  Postconditions: n has been added into the PrimeList
        //
        //  Method Type: Transformer        
        //
        //  Notes: This method is private to ensure n is never an invalid value           
        //
        ///////////////////////////////////////////////////////////////////////////
        void Add(int);

        ///////////////////////////////////////////////////////////////////////////
        //
        //  Method Name: PopulateList()
        //
        //  Purpose: To completely fill a PrimeList with all prime numbers from the
        //           2 to highNum range
        //
        //  Inputs: None
        //
        //  Outputs: None
        //
        //  Returns: None
        //
        //  Preconditions: PrimeList has been initialized  
        //
        //  Postconditions: All prime numbers from the 2 to highNum range are contained
        //                  within the PrimeList
        //
        //  Method Type: Transformer         
        //
        //  Notes: This method is invoked by both constructors and NewPrimeList(int)            
        //
        ///////////////////////////////////////////////////////////////////////////
        void PopulateList();

        // the length of the PrimeList
        int length;

        // the maximum bound of which to check for prime numbers when populating PrimeList
        int highNum;

        // the list of PrimeNumbers (statically allocated array)
        int numbers[MAXNUM];   
};

#endif