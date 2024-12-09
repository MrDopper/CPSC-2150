#include <iostream>

using namespace std;

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

class Node {
public:
    int data;
    Node* next;
    int id;
    Node(int value, int identity) : data(value), next(nullptr), id(identity) {}
};

class CircularLinkedList {
private:
    Node* last;

public:
    CircularLinkedList() : last(nullptr) {}
    ~CircularLinkedList(){
        if(last != nullptr)
            deleteList(last->next);
    }
    void deleteList(Node* h){
        if(h == last){
            delete h;
            last = nullptr;
            return;
        }
        deleteList(h->next);
        delete h;
        return;
    }
    // Insert a new node with data at the end of the circular linked list
    void insert(int data, int identity) {
        Node* new_node = new Node(data, identity);
        if (!last) {
            last = new_node;
            last->next = last;
        } else {
            new_node->next = last->next;
            last->next = new_node;
            last = new_node;
        }
    }

    // Delete a node with the given data
    // void deleteNode(int data) {
    //     if (!last)
    //         return;

    //     Node* current = last->next;
    //     Node* previous = nullptr;

    //     while (current->next != last->next) {
    //         if (current->data == data) {
    //             if (current == last->next)
    //                 last->next = last->next->next;
    //             if (current == last)
    //                 last = previous;
    //             if (previous)
    //                 previous->next = current->next;
    //             delete current;
    //             return;
    //         }
    //         previous = current;
    //         current = current->next;
    //     }
        
    //     if (current->data == data) {
    //         if (current == last->next)
    //             last->next = last->next->next;
    //         if (current == last)
    //             last = previous;
    //         if (previous)
    //             previous->next = current->next;
    //         delete current;
    //     }
    // }

    void deleteNode(int value){
            Node* a = deleteNode(value, last->next);
            if(last!=nullptr)
                last->next = a;
        }
        Node* deleteNode(int value, Node*h){
            if(h == last){
                if(h->data == value){
                    Node* a = (h != h -> next ? h->next : nullptr);
                    delete h;
                    last = nullptr;
                    return a;
                }
                return h;
            }
            h->next = deleteNode(value, h->next);
            if(last == nullptr)
                last = h;
            if(h -> data == value){
                Node* a = (h != h -> next ? h->next : nullptr);
                if(last == h)
                    last = nullptr;
                delete h;
                return a;
            }
            return h;
        }

    // Search for a node with the given data
    bool search(int data) {
        if (!last)
            return false;

        Node* current = last->next;

        do {
            if (current->data == data)
                return true;
            current = current->next;
        } while (current != last->next);

        return false;
    }

    // display all elements in the circular linked list
    void display() {
        if (!last)
            return;

        Node* current = last->next;

        do {
            cout << current->data << " ";
            current = current->next;
        } while (current != last->next);

        cout << endl;
    }
    int* cycle(int time_slice, int arr_len){
        int accum = 0;
        Node* a = last;
        int* arr = new int[arr_len];
        while(last!=nullptr){
            a = cycle(time_slice, accum, a, a->next);
            arr[(a->next)->id] = accum;
            if(a != a->next){
                if(a->next == last)
                    last = a->next->next;
                Node*next = a->next->next;
                delete a->next;
                a->next = next;
            }
            else{
                last = nullptr;
                delete a;
            }
        }
        return arr;
    }
    Node* cycle(int time_slice, int& count, Node*prev, Node*curr){
        if(prev == nullptr || curr == nullptr)
            return nullptr;
        curr->data -= time_slice;
        if(curr->data <= 0){
            count += curr->data+time_slice;
            return(prev);
        }
        Node*h = cycle(time_slice, count, curr, curr->next);
        count+=time_slice;
        return(h);
    }
};

#endif