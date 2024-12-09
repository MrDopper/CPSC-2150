/*
 * Name: Jackson Vi
 * Id: 100372502
 * Instructor: Muntaseer Salahuddin
 * Section: 001
 */
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <climits>
#include "Node.h"

#ifndef SKIPLIST_H
#define SKIPLIST_H

using namespace std;

class SkipList
{
public:
    int MAXIMUM_ALLOWED_LEVEL_INDEX;
    int currentHighestLevelIndex;
    Node *head;

    SkipList()
    {
        MAXIMUM_ALLOWED_LEVEL_INDEX = 0;
        currentHighestLevelIndex = 0;
        head = new Node(INT_MIN, MAXIMUM_ALLOWED_LEVEL_INDEX);
    }

    SkipList(int maxLevels)
    {
        MAXIMUM_ALLOWED_LEVEL_INDEX = maxLevels;
        currentHighestLevelIndex = 0;
        head = new Node(INT_MIN, MAXIMUM_ALLOWED_LEVEL_INDEX);
    }

    int RandomLevel()
    {
        float probability = (float)rand() / RAND_MAX;
        int lvl = 0;
        while (probability < 0.5 && lvl < MAXIMUM_ALLOWED_LEVEL_INDEX)
        {
            lvl++;
            probability = (float)rand() / RAND_MAX;
        }
        return lvl;
    }

    Node *CreateNode(int value, int level)
    {
        return new Node(value, level);
    }

    void InsertElement(int value)
    {
        if (!head)
        {
            cout << "Error: SkipList is uninitialized!" << endl;
            return;
        }

        Node *current = head;
        vector<Node *> update(MAXIMUM_ALLOWED_LEVEL_INDEX + 1, nullptr);

        for (int i = currentHighestLevelIndex; i >= 0; i--)
        {
            while (current != nullptr && current->next[i] != nullptr && current->next[i]->value < value)
            {
                current = current->next[i];
            }
            update[i] = current;
        }

        if (current != nullptr && current->next[0] != nullptr)
            current = current->next[0];
        else
            current = nullptr;

        if (current == nullptr || current->value != value)
        {
            int ranLevel = RandomLevel();

            if (ranLevel > currentHighestLevelIndex)
            {
                for (int i = currentHighestLevelIndex + 1; i <= ranLevel; i++)
                {
                    update[i] = head;
                }
                currentHighestLevelIndex = ranLevel;
            }

            Node *n = CreateNode(value, ranLevel);

            for (int i = 0; i <= ranLevel; i++)
            {
                if (update[i] != nullptr)
                {
                    n->next[i] = update[i]->next[i];
                    update[i]->next[i] = n;
                }
            }
        }
    }

    void Delete(int value)
    {
        if (!head)
        {
            cout << "Error: SkipList is uninitialized!" << endl;
            return;
        }

        Node *current = head;
        vector<Node *> update(MAXIMUM_ALLOWED_LEVEL_INDEX + 1, nullptr);

        for (int i = currentHighestLevelIndex; i >= 0; i--)
        {
            while (current != nullptr && current->next[i] != nullptr && current->next[i]->value < value)
            {
                current = current->next[i];
            }
            update[i] = current;
        }

        if (current != nullptr && current->next[0] != nullptr)
            current = current->next[0];

        if (current != nullptr && current->value == value)
        {
            for (int i = 0; i <= currentHighestLevelIndex; i++)
            {
                if (update[i] != nullptr && update[i]->next[i] == current)
                {
                    update[i]->next[i] = current->next[i];
                }
            }

            while (currentHighestLevelIndex > 0 && head->next[currentHighestLevelIndex] == nullptr)
            {
                currentHighestLevelIndex--;
            }

            delete current;
            cout << "The value " << value << " has been deleted" << endl;
        }
        else
        {
            cout << "Node with value " << value << " doesn't exist." << endl;
        }
    }

    bool Search(int value)
    {
        if (!head)
        {
            cout << "Error: SkipList is uninitialized!" << endl;
            return false;
        }

        Node *current = head;

        for (int i = currentHighestLevelIndex; i >= 0; i--)
        {
            while (current != nullptr && current->next[i] != nullptr && current->next[i]->value < value)
            {
                current = current->next[i];
            }
        }

        if (current != nullptr && current->next[0] != nullptr)
            current = current->next[0];

        if (current != nullptr && current->value == value)
        {
            cout << "Found value: " << current->value << endl;
            return true;
        }
        else
        {
            cout << "Value " << value << " not found." << endl;
            return false;
        }
    }

    void Show()
    {
        if (!head)
        {
            cout << "Error: SkipList is uninitialized!" << endl;
            return;
        }

        for (int i = 0; i <= currentHighestLevelIndex; i++)
        {
            Node *node = head->next[i];
            cout << "Level " << i << ": ";
            while (node != nullptr)
            {
                cout << node->value << " -> ";
                node = node->next[i];
            }
            cout << "null" << endl;
        }
    }

    void Rescale(int newMaxLevelIndex)
    {
        if (MAXIMUM_ALLOWED_LEVEL_INDEX == newMaxLevelIndex)
        {
            cout << "The new level is the same as your old level." << endl;
            return;
        }

        if (newMaxLevelIndex <= 0)
        {
            return;
        }

        if (head == nullptr)
        {
            MAXIMUM_ALLOWED_LEVEL_INDEX = newMaxLevelIndex;
            currentHighestLevelIndex = 0;
            head = new Node(INT_MIN, MAXIMUM_ALLOWED_LEVEL_INDEX);
            return;
        }

        Node *current = head->next[0];
        vector<int> newData;

        while (current != nullptr)
        {
            newData.push_back(current->value);
            Node *temp = current;
            current = current->next[0];
            delete temp;
        }

        MAXIMUM_ALLOWED_LEVEL_INDEX = newMaxLevelIndex;
        currentHighestLevelIndex = 0;
        head->next = vector<Node *>(newMaxLevelIndex + 1, nullptr);

        for (int value : newData)
        {
            InsertElement(value);
        }
    }

    void Merge(SkipList *list)
    {
        if (!list || !list->head || !this->head)
        {
            cout << "Error: One or both of the SkipLists are uninitialized!" << endl;
            return;
        }

        Node *current1 = this->head->next[0];
        Node *current2 = list->head->next[0];
        vector<int> mergedElements;

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
            {
                mergedElements.push_back(current1->value);
                current1 = current1->next[0];
                current2 = current2->next[0];
            }
        }

        while (current1 != nullptr)
        {
            mergedElements.push_back(current1->value);
            current1 = current1->next[0];
        }

        while (current2 != nullptr)
        {
            mergedElements.push_back(current2->value);
            current2 = current2->next[0];
        }

        current1 = head->next[0];
        while (current1 != nullptr)
        {
            Node *temp = current1;
            current1 = current1->next[0];
            delete temp;
        }

        head->next = vector<Node *>(MAXIMUM_ALLOWED_LEVEL_INDEX + 1, nullptr);
        currentHighestLevelIndex = 0;

        for (int value : mergedElements)
        {
            this->InsertElement(value);
        }
    }
};

#endif
