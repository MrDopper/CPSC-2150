/*
 * Name: Jackson Vi
 * Id: 100372502
 * Instructor: Muntaseer Salahuddin
 * Section: 001
 */
#include "HashingChainingSkipList.h"
#include "iostream"
int main()
{
    // Initialize the hash table with skip lists and a load factor threshold of 0.75
    HashingChainingSkipList hashTable(8, 0.75);

    // Insert some values
    hashTable.Insert(10);
    hashTable.Insert(15);
    hashTable.Insert(20);
    hashTable.Insert(20);
    hashTable.Insert(12);
    hashTable.Insert(28);
    hashTable.Display();

    // Display the contents of the hash table
    cout << "Displaying Hash Table after Insertions:\n";
    hashTable.Display();

    // Search for some values
    cout << "\nSearching for values:\n";
    hashTable.Search(15);  // Should be found
    hashTable.Search(100); // Should not be found

    // Delete a value and display the table again
    cout << "\nDeleting 15 and Displaying Hash Table:\n";
    hashTable.Delete(15);
    hashTable.Display();
    cout << "Test reHash" << endl;
    hashTable.Insert(20);
    hashTable.Insert(22);
    hashTable.Insert(21);
    hashTable.Insert(30);
    hashTable.Insert(13);
    hashTable.Display();
    return 0;
}
