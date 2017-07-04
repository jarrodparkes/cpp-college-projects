///////////////////////////////////////////////////////////////////////////
//
//  FILENAME: PrimeList.cpp
//
//  PROJECT: CS 221 - Programming Assignment #1
//
//  AUTHOR: Jarrod Parkes
//
//  DEVELOPMENT COMPILER: Microsoft Visual Studio 2008
//
//  TARGET PLATFORM: Windows 32-Bit Operating System
//
//  DESCRIPTION: This file contains the definitions for all methods from 
//               the PrimeList ADT from the "PrimeList.h" header file.              
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

// include the PrimeList ADT interface
#include "PrimeList.h"

// include for use of cout, etc
#include <iostream>

using namespace std;

PrimeList :: PrimeList()
{
    ClearList();
}

PrimeList :: PrimeList(int n)
{
    if(n <= 1 || n > MAXNUM)
    {
        ClearList();
        cout<<"ERROR: OUT OF BOUNDS, LIST SET TO EMPTY"<<endl;
    }

    else
    {
        length = 0;
        highNum = n;
        PopulateList();
    }
}

void PrimeList :: NewPrimeList(int n)
{
    if(n <= 1 || n > MAXNUM)
    {
        ClearList();
        cout<<"ERROR: OUT OF BOUNDS, LIST SET TO EMPTY"<<endl;
    }

    else
    {
        length = 0;
        highNum = n;
        PopulateList();
    }
}

void PrimeList :: ClearList()
{
    length = 0;
    highNum = 0;
}

bool PrimeList :: IsFull()
{
    if(length == MAXNUM)
    {
        return true;
    }

    else
    {
        return false;
    }
}

int PrimeList :: GetLength()
{
    return length;
}

int PrimeList :: RetrieveItem(int n)
{
    if(n >= 0 && n < length)
    {
        return numbers[n];
    }

    else
    {
        return -1;
    }
} 
  
bool PrimeList :: IsEmpty()
{
    if(length == 0)
    {
        return true;
    }

    else
    {
        return false;
    }
}

void PrimeList :: PrintToScreen()
{
    cout<<"N = "<<highNum<<endl;

    cout<<"Primes = [";

    if(length > 0)
    {
        for(int i = 0; i < length; i++)
        {
            if(i == length - 1)
            {
                cout<<numbers[i];
            }
            
            else
            {
                cout<<numbers[i]<<", ";
            }
        }
    }

    else
    {
        cout<<"NONE";
    }

    cout<<"]"<<endl;
}

void PrimeList :: PrintToFile(ofstream &outputFile)
{
    outputFile<<"N = "<<highNum<<endl;

    outputFile<<"Primes = [";

    if(length > 0)
    {
        for(int i = 0; i < length; i++)
        {
            if(i == length - 1)
            {
                outputFile<<numbers[i];
            }
            
            else
            {
                outputFile<<numbers[i]<<", ";
            }
        }
    }

    else
    {
        outputFile<<"NONE";
    }

    outputFile<<"]"<<endl;
}

void PrimeList :: Add(int n)
{
    numbers[length] = n;
    length++;
}

void PrimeList :: PopulateList()
{
    int testNums[MAXNUM];

    for(int i = 0; i < highNum - 1 ; i++)
    {
        testNums[i] = (i + 2);
    }
    
    for(int j = 0; j < highNum - 1; j++)
    {
        if(testNums[j] * testNums[j] > highNum)
        {
            break;
        }

        if(testNums[j] != 0)
        {
            for(int k = (j+1); k <= highNum - 1; k++)
            {
                if(testNums[k]!=0)
                {
                    if((testNums[k]%testNums[j]==0))
                    {
                        testNums[k] = 0;
                    }
                }
            }
        }
    }

    for(int i = 0; i < highNum; i++)
    {
        if(testNums[i] != 0)
        {
            Add(testNums[i]);
        }
    }
}

