/*
 * Name: Jackson Vi
 * Id: 100372502
 * Instructor: Muntaseer Salahuddin
 * Section: 001
 */
#ifndef TREENODE_H
#define TREENODE_H

class TreeNode
{
public:
    int element;     // Element contained in the node
    int height;      // height of the node
    TreeNode *left;  // Pointer to the left child
    TreeNode *right; // Pointer to the right child
    TreeNode(int element)
    {
        this->element = element;
        height = 0;
        left = nullptr;
        right = nullptr;
    }
};
#endif