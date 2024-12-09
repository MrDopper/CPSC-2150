/*
 * Name: Jackson Vi
 * Id: 100372502
 * Instructor: Muntaseer Salahuddin
 * Section: 001
 */
#include "HashingLinearProbingDemo.h"
#include "iostream"

using namespace std;

int main()
{
    HashingLinearProbingDemo testHash(6, 0.75);
    testHash.Insert(5);
    testHash.Insert(4);
    testHash.Insert(55);
    testHash.Insert(8);
    testHash.Display();
    cout << "-----------------" << endl;
    cout << "Searching function" << endl;
    testHash.Delete(8);
    testHash.Search(8, true);
    testHash.Display();
    cout << "----------------------------" << endl;
    testHash.Insert(8);
    testHash.Display();
    cout << "----------------------------" << endl;
    testHash.Insert(14);
    testHash.Insert(12);
    testHash.Display();
    cout << "----------------------------" << endl;
    testHash.Insert(0);
    testHash.Display();
    cout << "----------------------------" << endl;
    return 0;
}