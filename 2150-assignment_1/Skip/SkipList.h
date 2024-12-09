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

class SkipList{
public:
    // Maximum allowed level index
    int MAXIMUM_ALLOWED_LEVEL_INDEX;
 
    // current maximum level amongst the inserted nodes
    int currentHighestLevelIndex;
    
    // the head node's next links are connected to the first node at every level
    Node *head;

    SkipList(int maxLevels){
        MAXIMUM_ALLOWED_LEVEL_INDEX = maxLevels;

        // initially we have the bottom-most level only
        currentHighestLevelIndex = 0;
    
        // create the header node, value is irrelevant (as long as it doesn't match an inserted value - NO REPEATS), number of next links is important (initially this node is the first node at every level)
        head = new Node(INT_MIN, MAXIMUM_ALLOWED_LEVEL_INDEX);
    }

    int RandomLevel(){
        float probablity = (float)rand()/RAND_MAX; // flip a coin
        int lvl = 0;
        while (probablity < 0.5 && lvl < MAXIMUM_ALLOWED_LEVEL_INDEX){
            lvl++; // landed heads so increase level by 1
            probablity = (float)rand()/RAND_MAX; // flip a coin again
        }
        return lvl;
    }

    Node* CreateNode(int value, int level){
        // create a new node with next links for every level that this node will be part of
        // it will use these links to connect to the next node at each level  
        return new Node(value, level);
    }

    void InsertElement(int value){
        Node *current = head; // start at head node
        vector<Node*> update(MAXIMUM_ALLOWED_LEVEL_INDEX+1, nullptr); // this will hold the nodes that need updating at every level after the insert takes place
        for (int i = currentHighestLevelIndex; i >= 0; i--){ // start at the highest level and move down so that more nodes may be skipped
            // for level i, if value is to be inserted here then find out where (i.e. after which node)
            while (current->next[i] != nullptr && current->next[i]->value < value){
                current = current->next[i];
            }
            // found the node after which the value is to be placed at level i, move down a level, if possible 
            update[i] = current;
        }
        
        // at level 0, where current is pointing to by the end of the preceding loop, move over one node to where the value is to be inserted to see if the value already exists there (NO REPEATS allowed)
        current = current->next[0];
    
        if (current == nullptr || current->value != value){
            int ranLevel = RandomLevel(); // choose a random level upto where the new node will be placed
    
            if (ranLevel > currentHighestLevelIndex){
                // if random level for current node is higher than the current maximum level for existing nodes; then set head as the node after which the new value is to be inserted for each level over current maximum to the level chosen for new value to be inserted (update currently contains nulls for these level(s)).
                for (int i = currentHighestLevelIndex+1; i <= ranLevel; i++){
                    update[i] = head;
                }
    
                // also change the current maximum level for the existing nodes
                currentHighestLevelIndex = ranLevel;
            }
    
            // create new node with next links for every level from ranLevel to zero
            Node* n = CreateNode(value, ranLevel);
    
            // placing new node in the correct place at every level
            for (int i = 0; i<=ranLevel; i++){
                n->next[i] = update[i]->next[i];
                update[i]->next[i] = n;
            }
        }
    }

    void Delete(int value){
        vector<Node*> list = vector<Node*>(MAXIMUM_ALLOWED_LEVEL_INDEX+1, nullptr);
        int j = currentHighestLevelIndex;
        Node* delNode = Delete(value, list, head, j);
        if(j<0)
            return;
        for(int i = j; i>=0; i--){
            Node*a = list[i]->next[i]->next[i];
            list[i]->next[i] = a;
            if(list[i] == head && a == nullptr){
                currentHighestLevelIndex = (i == 0 ? i : i-1);
            }
        }
        if(delNode != nullptr)
            delete delNode;
    }
    Node* Delete(int x, vector<Node*> &list, Node*h, int& i){
        if(i < 0){
            // i+=1;
            return nullptr;
        }
        Node*a;
        Node*next = h->next[i];
        if(next == nullptr || next->value > x){
            a = Delete(x, list, h, i-=1);
        }
        else if(next->value == x){
            list[i] = h;
            a = Delete(x, list, h, i-=1);
            i+=1;
            return (next);
        }
        else if(next->value < x){
            a = Delete(x, list, next, i);
        }
        return a;
    }
    
    bool Search(int value){
        return Search(value, head, currentHighestLevelIndex);
    }
    bool Search(int value, Node*h, int i){
        if(i<0)
            return false;
        if(h->next[i] == nullptr || h->next[i]->value > value)
            return Search(value, h, i-1);
        else if(h->next[i]->value == value)
            return true;
        else
            return Search(value, h->next[i], i);
        
    }
    void Show(){
        for (int i=0;i<=currentHighestLevelIndex;i++){
            Node *node = head->next[i];
            cout << "Level " << i << ": ";
            if(node == nullptr)
                return;
            while (node != nullptr && node->next[i] != nullptr){
                cout << node->value << " -> ";
                node = node->next[i];
            }
            cout << node->value << " .\n";
        }
    }
    void rescale(int newMAXLEVEL){
        if(newMAXLEVEL < 0){
            cout<<"Index must be 0 or higher."<<endl;
            return;
        }
        if(newMAXLEVEL == MAXIMUM_ALLOWED_LEVEL_INDEX)
            return;
        vector<int> list = vector<int>();
        reScale(head->next[0], list);
        head->next = vector<Node*>(newMAXLEVEL+1, nullptr);
        MAXIMUM_ALLOWED_LEVEL_INDEX = newMAXLEVEL;
        currentHighestLevelIndex = 0;
        for(int i = 0; i<list.size(); i++)
            InsertElement(list[i]);
        
    }
    void reScale(Node*h, vector<int> &list){
        if(h == nullptr)
            return;
        list.push_back(h->value);
        reScale(h->next[0], list);
        delete h;
    }
};

#endif