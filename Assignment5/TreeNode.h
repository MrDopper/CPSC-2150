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
    int element;
    TreeNode *left;
    TreeNode *right;
    TreeNode();
    TreeNode(const int &e);
};
#endif