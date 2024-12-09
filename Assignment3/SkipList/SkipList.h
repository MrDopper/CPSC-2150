#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <climits>
#include "Node.h"

#ifndef SKIPLIST_H
#define SKIPLIST_H

using namespace std;

class SkipList
{
public:
    // Maximum allowed level index
    int MAXIMUM_ALLOWED_LEVEL_INDEX;

    // current maximum level amongst the inserted nodes
    int currentHighestLevelIndex;

    // the head node's next links are connected to the first node at every level
    Node *head;
    SkipList()
    {
        MAXIMUM_ALLOWED_LEVEL_INDEX = 0;
        head = nullptr;
        currentHighestLevelIndex = 0;
    }
    SkipList(int maxLevels)
    {
        MAXIMUM_ALLOWED_LEVEL_INDEX = maxLevels;

        // initially we have the bottom-most level only
        currentHighestLevelIndex = 0;

        // create the header node, value is irrelevant (as long as it doesn't match an inserted value - NO REPEATS), number of next links is important (initially this node is the first node at every level)
        head = new Node(INT_MIN, MAXIMUM_ALLOWED_LEVEL_INDEX);
    }

    int RandomLevel()
    {
        float probablity = (float)rand() / RAND_MAX; // flip a coin
        int lvl = 0;
        while (probablity < 0.5 && lvl < MAXIMUM_ALLOWED_LEVEL_INDEX)
        {
            lvl++;                                 // landed heads so increase level by 1
            probablity = (float)rand() / RAND_MAX; // flip a coin again
        }
        return lvl;
    }

    Node *CreateNode(int value, int level)
    {
        // create a new node with next links for every level that this node will be part of
        // it will use these links to connect to the next node at each level
        return new Node(value, level);
    }

    void InsertElement(int value)
    {
        Node *current = head;                                            // start at head node
        vector<Node *> update(MAXIMUM_ALLOWED_LEVEL_INDEX + 1, nullptr); // this will hold the nodes that need updating at every level after the insert takes place
        for (int i = currentHighestLevelIndex; i >= 0; i--)
        { // start at the highest level and move down so that more nodes may be skipped
            // for level i, if value is to be inserted here then find out where (i.e. after which node)
            while (current->next[i] != nullptr && current->next[i]->value < value)
            {
                current = current->next[i];
                // cout << "current level is: " << currentHighestLevelIndex << endl;
            }
            // found the node after which the value is to be placed at level i, move down a level, if possible
            update[i] = current;
        }

        // at level 0, where current is pointing to by the end of the preceding loop, move over one node to where the value is to be inserted to see if the value already exists there (NO REPEATS allowed)
        current = current->next[0];

        if (current == nullptr || current->value != value)
        {
            int ranLevel = RandomLevel(); // choose a random level upto where the new node will be placed

            if (ranLevel > currentHighestLevelIndex)
            {
                // if random level for current node is higher than the current maximum level for existing nodes; then set head as the node after which the new value is to be inserted for each level over current maximum to the level chosen for new value to be inserted (update currently contains nulls for these level(s)).
                for (int i = currentHighestLevelIndex + 1; i <= ranLevel; i++)
                {
                    update[i] = head;
                }

                // also change the current maximum level for the existing nodes
                currentHighestLevelIndex = ranLevel;
            }

            // create new node with next links for every level from ranLevel to zero
            Node *n = CreateNode(value, ranLevel);

            // placing new node in the correct place at every level
            for (int i = 0; i <= ranLevel; i++)
            {
                n->next[i] = update[i]->next[i];
                update[i]->next[i] = n;
            }
        }
    }

    // The node should be delete for all the level it praticipates in.
    void Delete(int value)
    {
        // TO BE COMPLETED
        // remove value from skip list (all levels) if it exists (output a message if it does not exist)
        Node *current = head;
        vector<Node *> update(MAXIMUM_ALLOWED_LEVEL_INDEX + 1, nullptr);
        for (int i = currentHighestLevelIndex; i >= 0; i--)
        {
            while (current->next[i] != nullptr && current->next[i]->value < value)
            {
                current = current->next[i];
            }
            update[i] = current;
        }
        // Move to the next node at level 0
        current = current->next[0];
        // Check if the node I want to delete exists
        if (current != nullptr && current->value == value)
        {
            // The node found, remove it from all levels
            cout << "I delete the node" << endl;
            for (int i = 0; i <= currentHighestLevelIndex; i++)
            {
                if (update[i]->next[i] != current)
                {
                    break;
                }
                update[i]->next[i] = current->next[i];
            }
            // Keep traversive
            while (currentHighestLevelIndex > 0 && head->next[currentHighestLevelIndex] == nullptr)
            {
                // Reduce the level if no more nodes exist at the highest level
                currentHighestLevelIndex--;
            }

            cout << "The value " << current->value << " has been deleted" << endl;
            delete current;
        }
        else
        {
            cout << "Node doesn't exist" << endl;
        }
    }

    bool Search(int value)
    {
        // TO BE COMPLETED
        // search for value in skip list and return true if it exists; false otherwise
        Node *current = head;
        for (int i = currentHighestLevelIndex; i >= 0; i--)
        {
            while (current->next[i] != nullptr && current->next[i]->value < value)
            {
                current = current->next[i];
            }
        }
        cout << "Before descending: " << current->value << endl;
        current = current->next[0];
        cout << "After descending: " << current->value << endl;

        if (current != nullptr && current->value == value)
        {
            cout << "There is an exist number you want to find: " << endl;
            return true;
        }
        else
        {
            cout << "There is not an exist number you try to find!!" << endl;
            return false;
        }
    }

    void Show()
    {
        for (int i = 0; i <= currentHighestLevelIndex; i++)
        {
            Node *node = head->next[i];
            cout << "Level " << i << ": ";
            while (node != nullptr && node->next[i] != nullptr)
            {
                cout << node->value << " -> ";
                node = node->next[i];
            }
            cout << node->value << " .\n";
        }
    }
    void Rescale(int newMaxLevelIndex)
    {
        if (MAXIMUM_ALLOWED_LEVEL_INDEX == newMaxLevelIndex)
        {
            cout << "The new level is the same as your old level" << endl;
            return;
        }

        if (newMaxLevelIndex <= 0)
        {
            return;
        }
        if(head == nullptr){
            MAXIMUM_ALLOWED_LEVEL_INDEX = newMaxLevelIndex;

            // initially we have the bottom-most level only
            currentHighestLevelIndex = 0;

            // create the header node, value is irrelevant (as long as it doesn't match an inserted value - NO REPEATS), number of next links is important (initially this node is the first node at every level)
            head = new Node(INT_MIN, MAXIMUM_ALLOWED_LEVEL_INDEX);

            return;
        }
        Node *current = head->next[0];
        vector<int> newData;
        while (current != nullptr)
        {
            Node *prev = current;
            newData.push_back(current->value);
            current = current->next[0];
            delete prev;
        }
        MAXIMUM_ALLOWED_LEVEL_INDEX = newMaxLevelIndex;
        currentHighestLevelIndex = 0;
        head->next = vector<Node *>(newMaxLevelIndex + 1, nullptr);
        for (int i = 0; i < newData.size(); i++)
        {
            InsertElement(newData[i]);
        }
    }
    void merge(SkipList &list1, SkipList &list2, int level)
    {
        Node *current1 = list1.head->next[0];
        Node *current2 = list2.head->next[0];

        SkipList mergeList(level);
        vector<int> newList;
        while (current1 != nullptr && current2 != nullptr)
        {
            if (current1->value < current2->value)
            {
                newList.push_back(current1->value);
                current1 = current1->next[0];
            }
            else
            {
                newList.push_back(current2->value);
                current2 = current2->next[0];
            }
        }
        while (current1 != nullptr)
        {
            newList.push_back(current1->value);
            current1 = current1->next[0];
        }
        while (current2 != nullptr)
        {
            newList.push_back(current2->value);
            current2 = current2->next[0];
        }
        for (int i = 0; i < newList.size(); i++)
        {
            mergeList.InsertElement(newList[i]);
        }
    }
    // should sorting in ascending level
    void Merge(SkipList *list)
    {
        Node *current1 = this->head->next[0]; // Current list starting node
        Node *current2 = list->head->next[0]; // Merging list starting node
        vector<int> mergedElements;           // To store merged values
        while (current1 != nullptr && current2 != nullptr)
        {
            if (current1->value < current2->value)
            {
                mergedElements.push_back(current1->value);
                current1 = current1->next[0];
            }
            else if (current2->value < current1->value)
            {
                mergedElements.push_back(current2->value);
                current2 = current2->next[0];
            }
            else
            {                                              // If values are equal
                mergedElements.push_back(current1->value); // Only add once
                current1 = current1->next[0];
                current2 = current2->next[0];
            }
        }
        // Add remaining elements from list1
        while (current1 != nullptr)
        {
            mergedElements.push_back(current1->value);
            current1 = current1->next[0];
        }

        // Add remaining elements from list2
        while (current2 != nullptr)
        {
            mergedElements.push_back(current2->value);
            current2 = current2->next[0];
        }

        // Rebuild the skip list with merged elements
        for (int i = 0; i < mergedElements.size(); i++)
        {
            this->InsertElement(mergedElements[i]);
        }
    }
};

#endif