/*
 * Name: Jackson Vi
 * Id: 100372502
 * Instructor: Muntaseer Salahuddin
 * Section: 001
 */
#include <iostream>
#include "SkipList.h"

using namespace std;

class HashingChainingSkipList
{
public:
    HashingChainingSkipList(int size, double lft);
    ~HashingChainingSkipList();
    void Insert(int value);
    void Delete(int value);
    bool Search(int value, bool printResult = true);
    void ReHash();
    void Display();

    // Calculate the load factor based on nodes at level 0
    double CalculateLoadFactor();

private:
    SkipList **hashTable;
    int hashTableSize;
    int numberOfKeys;
    double loadFactorThreshold;

    int HashFunction(int value)
    {
        return value % hashTableSize;
    }
};

HashingChainingSkipList::HashingChainingSkipList(int size, double lft)
{
    hashTableSize = size;
    hashTable = new SkipList *[hashTableSize];
    for (int i = 0; i < hashTableSize; i++)
    {
        hashTable[i] = new SkipList();
    }
    numberOfKeys = 0;
    loadFactorThreshold = lft;
}

HashingChainingSkipList::~HashingChainingSkipList()
{
    for (int i = 0; i < hashTableSize; i++)
    {
        if (hashTable[i] != nullptr)
        {
            delete hashTable[i];
        }
    }
    delete[] hashTable;
}

void HashingChainingSkipList::Insert(int value)
{
    int hashTableIndex = HashFunction(value);

    if (hashTable[hashTableIndex] == nullptr)
    {
        std::cout << "Initializing SkipList at index " << hashTableIndex << std::endl;
        hashTable[hashTableIndex] = new SkipList();
    }

    if (!hashTable[hashTableIndex]->Search(value))
    {
        hashTable[hashTableIndex]->InsertElement(value);
        numberOfKeys++;

        std::cout << "Inserted " << value << " at index " << hashTableIndex << std::endl;

        double currentLoadFactor = static_cast<double>(numberOfKeys) / hashTableSize;
        if (currentLoadFactor > loadFactorThreshold)
        {
            ReHash();
        }
    }
    else
    {
        // If the value already exists, print a message
        std::cout << "The value " << value << " already exists in the table at index " << hashTableIndex << std::endl;
    }
}

bool HashingChainingSkipList::Search(int value, bool printResult)
{
    // Use the custom hash function to get an index
    int hashTableIndex = HashFunction(value);

    if (hashTable[hashTableIndex]->Search(value))
    {
        if (printResult)
        {
            cout << "The value " << value << " is found at index: " << hashTableIndex << ".\n";
        }
        return true;
    }
    else
    {
        if (printResult)
        {
            cout << "The value " << value << " is not found in the table.\n";
        }
        return false;
    }
}

// Delete a value from the appropriate skip list
void HashingChainingSkipList::Delete(int value)
{
    int hashTableIndex = HashFunction(value);

    // Delete the value from the skip list at that index
    if (hashTable[hashTableIndex]->Search(value))
    {
        hashTable[hashTableIndex]->Delete(value);
        numberOfKeys--;
    }
    else
    {
        cout << "The value " << value << " was not found in the table.\n";
    }
}

// Calculate the load factor by counting nodes at level 0 in all skip lists
double HashingChainingSkipList::CalculateLoadFactor()
{
    int totalNodesAtLevel0 = 0;

    // Iterate over all skip lists (buckets) in the hash table
    for (int i = 0; i < hashTableSize; i++)
    {
        Node *current = hashTable[i]->head->next[0];
        while (current != nullptr)
        {
            totalNodesAtLevel0++;
            current = current->next[0];
        }
    }

    // Load factor is the total number of nodes at level 0 divided by the hash table size
    return (double)totalNodesAtLevel0 / hashTableSize;
}
void HashingChainingSkipList::ReHash()
{
    int oldSize = hashTableSize;
    hashTableSize = 2 * oldSize;

    // Allocate a new table with the new size
    SkipList **newHashTable = new SkipList *[hashTableSize];

    // Initialize new skip lists for each element in the new table
    for (int i = 0; i < hashTableSize; i++)
    {
        newHashTable[i] = new SkipList();
    }

    // Rehash all elements from the old table into the new table
    for (int i = 0; i < oldSize; i++)
    {
        Node *current = hashTable[i]->head->next[0]; // Start at level 0 in the old skip list
        while (current != nullptr)
        {
            // Use the new table's size for rehashing
            int newHashTableIndex = current->value % hashTableSize;

            // Insert the element into the new table at the new hash index
            newHashTable[newHashTableIndex]->InsertElement(current->value);

            current = current->next[0];
        }
    }

    // Clean up old skip lists
    for (int i = 0; i < oldSize; i++)
    {
        delete hashTable[i];
    }

    // Free up memory for the old table
    delete[] hashTable;

    // Point hashTable to the new table
    hashTable = newHashTable;

    cout << "Rehashing completed. New table size: " << hashTableSize << endl;
}

// Display the contents of the hash table (skip lists)
void HashingChainingSkipList::Display()
{
    cout << "Hash Table Contents:\n";
    for (int i = 0; i < hashTableSize; i++)
    {
        cout << "index " << i << ": ";
        hashTable[i]->Show(); // Use your SkipList Display function to show each bucket
    }
    cout << "Number of keys: " << numberOfKeys << endl;
    double currentLoadFactor = CalculateLoadFactor();
    cout << "Current load factor: " << currentLoadFactor << endl;
    cout << "Load factor threshold: " << loadFactorThreshold << endl;
}
