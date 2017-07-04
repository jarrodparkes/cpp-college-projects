///////////////////////////////////////////////////////////////////////////
//
//  FILENAME: Driver.cpp
//
//  PROJECT: CS 221 - Programming Assignment #1
//
//  AUTHOR: Jarrod Parkes
//
//  DEVELOPMENT COMPILER: Microsoft Visual Studio 2008
//
//  TARGET PLATFORM: Windows 32-Bit Operating System
//
//  DESCRIPTION: This file contains the module-level testing for the
//               PrimeList ADT through instantiation and testing of
//               PrimeList's methods.
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

//include the PrimeList ADT
#include "PrimeList.h"

using namespace std;

int main()
{
    // access an externally declared integer n 
    extern int n;

    // delcare and allow appending for a file named primes.txt
    ofstream myOutFile("primes.txt", ios::app);
    
    // inistantiate a PrimeList of values 2 to n
    PrimeList p1(n);

    p1.PrintToScreen();
    p1.PrintToFile(myOutFile);

    // close the primes.txt
    myOutFile.close();

    system("pause");
}