/*
 * Name: Jackson Vi
 * Id: 100372502
 * Instructor: Muntaseer Salahuddin
 * Section: 001
 */
#include "TreeNode.h"

TreeNode::TreeNode()
{
    element = 0;
    left = nullptr;
    right = nullptr;
}
// when assigns the first node. This node becomes root node or attaches that node to the root Node
TreeNode::TreeNode(const int &e)
{
    // current element is pointing to e
    this->element = e;
    left = nullptr;
    right = nullptr;
}
