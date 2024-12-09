/*
 * Name: Jackson Vi
 * Id: 100372502
 * Instructor: Muntaseer Salahuddin
 * Section: 001
 */
#include "HashingLinearProbingDemo.h"

HashingLinearProbingDemo::HashingLinearProbingDemo()
{
    hashTable = nullptr;
    hashTableSize = 0;
    numberOfKeys = 0;
    loadFactorThreshold = 1.0;
}
HashingLinearProbingDemo::~HashingLinearProbingDemo()
{
    if (hashTable != nullptr)
    {
        delete[] hashTable;
        hashTable = nullptr;
    }
}
HashingLinearProbingDemo::HashingLinearProbingDemo(int size, double lft)
{
    hashTableSize = size;
    hashTable = new int[hashTableSize];
    for (int i = 0; i < hashTableSize; i++)
    {
        hashTable[i] = 0;
    }
    numberOfKeys = 0;
    loadFactorThreshold = lft;
}
void HashingLinearProbingDemo::Insert(int value)
{
    if (value == 0)
    {
        cout << "0 not allowed\n";
        return;
    }
    if (!Search(value, false))
    {
        double currentLoadFactor = (double)(numberOfKeys + 1) / hashTableSize;
        if (currentLoadFactor > loadFactorThreshold)
        {
            ReHash();
        }

        hash<int> builtInHashFunction;

        int hashCode = builtInHashFunction(value);

        int hashTableIndex = hashCode % hashTableSize;

        if (hashTable[hashTableIndex] == 0)
        {
            // no collision
            hashTable[hashTableIndex] = value;
            numberOfKeys++;
        }
        else
        {
            // use linear probing to resolve collision
            while (hashTable[hashTableIndex] != 0)
            {
                hashTableIndex = (hashTableIndex + 1) % hashTableSize;
            }
            hashTable[hashTableIndex] = value;
            numberOfKeys++;
        }
    }
    else
    {
        cout << value << " already exists!\n";
    }
}

void HashingLinearProbingDemo::Delete(int value)
{
    // Base case
    if (value == 0)
    {
        cout << "You cannot delete number zero" << endl;
        return;
    }
    if (!Search(value, false))
    {
        cout << "The value you want to delete doesn't exist" << endl;
        return;
    }
    hash<int> builtInHashFunction;
    int hashCode = builtInHashFunction(value);
    int hashTableIndex = hashCode % hashTableSize;
    while (hashTable[hashTableIndex] != 0)
    {
        if (hashTable[hashTableIndex] == value)
        {
            hashTable[hashTableIndex] = 0;
            numberOfKeys--;
            // Move to the new character
            hashTableIndex = (hashTableIndex + 1) % hashTableSize;
            while (hashTable[hashTableIndex] != 0)
            {
                // Temporary store the current index value
                int rehashedValue = hashTable[hashTableIndex];
                // Replace current index with zero
                hashTable[hashTableIndex] = 0;
                // Insert the value back (chaining those numbers together)
                Insert(rehashedValue);

                hashTableIndex = (hashTableIndex + 1) % hashTableSize;
            }

            return;
        }
        hashTableIndex = (hashTableIndex + 1) % hashTableSize;
    }
}

void HashingLinearProbingDemo::ReHash()
{
    int oldSize = hashTableSize;
    // double the size
    hashTableSize = 2 * oldSize;
    int *oldTable = hashTable;
    hashTable = new int[hashTableSize];

    for (int i = 0; i < hashTableSize; i++)
    {
        // Initialize the new table
        hashTable[i] = 0;
    }

    numberOfKeys = 0;
    for (int i = 0; i < oldSize; i++)
    {
        if (oldTable[i] != 0)
        {
            Insert(oldTable[i]);
        }
    }

    delete[] oldTable;
    cout << "Rehashing completed. New table size: " << hashTableSize << endl;
}
bool HashingLinearProbingDemo::Search(int value, bool check = true)
{

    hash<int> builtInHashFunction;
    int hashCode = builtInHashFunction(value);
    int hashIndex = hashCode % hashTableSize;

    while (hashTable[hashIndex] != 0 && hashTable[hashIndex] != value)
    {
        hashIndex = (hashIndex + 1) % hashTableSize;
    }
    if (hashTable[hashIndex] == value)
    {
        if (check)
        {
            cout << "The value " << value << " is found!" << endl;
        }
        return true;
    }
    else
    {
        if (check)
        {
            cout << "The value " << value << " is not found!" << endl;
        }
        return false;
    }
}
void HashingLinearProbingDemo::Display()
{
    cout << "Hashtable contents:" << endl;
    for (int i = 0; i < hashTableSize; i++)
    {
        if (hashTable[i] != 0)
        {
            cout << "Index " << i << ": " << hashTable[i] << endl;
        }
        else
        {
            cout << "Index " << i << ": " << "Empty" << endl;
        }
    }

    // Display additional information
    cout << "Current Table Size: " << hashTableSize << endl;
    cout << "Number of Keys: " << numberOfKeys << endl;
    double currentLoadFactor = (double)numberOfKeys / hashTableSize;
    cout << "Current Load Factor: " << currentLoadFactor << endl;
    cout << "Load Factor Threshold: " << loadFactorThreshold << endl;
}