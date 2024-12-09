#include <iostream>

using namespace std;

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

class Node
{
public:
    int data;
    Node *next;

    Node(int value) : data(value), next(nullptr) {}
};

class CircularLinkedList
{
private:
    Node *last;

public:
    CircularLinkedList() : last(nullptr) {}

    ~CircularLinkedList()
    {
        if (last)
        {
            Node *current = last;
            Node *temp;
            do
            {
                temp = current;
                current = current->next;
                delete temp;
            } while (current != last);
        }
    }

    // Helper function
    Node *getLast()
    {
        return last;
    }
    // Insert a new node with data at the end of the circular linked list
    void insert(int data)
    {
        Node *new_node = new Node(data);
        if (!last)
        {
            last = new_node;
            last->next = last;
        }
        else
        {
            new_node->next = last->next;
            last->next = new_node;
            last = new_node;
        }
    }

    // Delete a node with the given data
    void deleteNode(int data)
    {
        if (!last)
            return;

        Node *current = last->next;
        Node *previous = nullptr;

        while (current->next != last->next)
        {
            if (current->data == data)
            {
                if (current == last->next)
                    last->next = last->next->next;
                if (current == last)
                    last = previous;
                if (previous)
                    previous->next = current->next;
                delete current;
                return;
            }
            previous = current;
            current = current->next;
        }

        if (current->data == data)
        {
            if (current == last->next)
                last->next = last->next->next;
            if (current == last)
                last = previous;
            if (previous)
                previous->next = current->next;
            delete current;
        }
    }

    // Search for a node with the given data
    bool search(int data)
    {
        if (!last)
            return false;

        Node *current = last->next;

        do
        {
            if (current->data == data)
                return true;
            current = current->next;
        } while (current != last->next);

        return false;
    }

    // display all elements in the circular linked list
    void display()
    {
        if (!last)
            return;

        Node *current = last->next;

        do
        {
            cout << current->data << " ";
            current = current->next;
        } while (current != last->next);

        cout << endl;
    }
};

#endif