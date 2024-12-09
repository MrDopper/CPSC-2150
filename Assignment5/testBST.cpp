/*
 * Name: Jackson Vi
 * Id: 100372502
 * Instructor: Muntaseer Salahuddin
 * Section: 001
 */
#include <iostream>
#include "liangBST.h"

using namespace std;

int main()
{
    BST tree;
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(5);
    tree.insert(2);
    tree.insert(1);
    tree.DisplayTreeHorizontally();
    // Copy tree
    BST tree2(tree);
    // Display the copy
    tree2.DisplayTreeHorizontally();
    // tree.insert(3);
    // tree.insert(8);
    int searchValue = 2;
    if (tree.search(searchValue) != nullptr)
    {
        vector<TreeNode *> *pathResult = tree.path(searchValue);
        cout << "Path to " << searchValue << ": ";
        for (TreeNode *node : *pathResult)
        {
            cout << node->element << " ";
        }
        cout << endl;
        delete pathResult;
    }
    else
    {
        cout << "Path to " << searchValue << " not found." << endl;
    }
    cout << "The height of the tree in terms of edges: " << tree.GetHeight() << endl;
    cout << "The height of the tree in terms of nodes: " << tree.Height() << endl;
    cout << "The highest number in the tree is: " << tree.Max() << endl;
    cout << "The smallest number in the tree is: " << tree.Min() << endl;
    if (tree.IsBST() == true)
    {
        cout << "Yes this is a binary tree." << endl;
    }
    else
    {
        cout << "It is not a binary tree." << endl;
    }

    // New test tree
    BST tree3;
    tree3.insert(50);
    tree3.insert(30);
    tree3.insert(20);
    tree3.insert(40);
    tree3.insert(70);
    tree3.insert(80);
    tree3.DisplayTreeHorizontally();
    int searchValue2 = 70;
    if (tree3.search(searchValue2) != nullptr)
    {
        vector<TreeNode *> *pathResult = tree3.path(searchValue2);
        cout << "Path to " << searchValue2 << ": ";
        for (TreeNode *node : *pathResult)
        {
            cout << node->element << " ";
        }
        cout << endl;
        delete pathResult;
    }
    else
    {
        cout << "Path to " << searchValue << " not found." << endl;
    }
    if (tree3.IsBST() == true)
    {
        cout << "Yes this is a binary tree." << endl;
    }
    else
    {
        cout << "It is not a binary tree." << endl;
    }
    cout << "The height of the tree in terms of edges: " << tree3.GetHeight() << endl;
    cout << "The height of the tree in terms of nodes: " << tree3.Height() << endl;
    cout << "The highest number in the tree is: " << tree3.Max() << endl;
    cout << "The smallest number in the tree is: " << tree3.Min() << endl;
    cout << "Display by level in tree3: ";
    tree3.LevelOrderDisplay();
    cout << "Display by level in tree3 using k value:" << endl;
    int k = 2;
    vector<TreeNode> nodes = tree3.NodesAtDistance(k);

    if (nodes.empty())
    {
        cout << "No nodes found at distance " << k << "." << endl;
    }
    else
    {
        cout << "Nodes at distance " << k << " from the root: ";
        for (const TreeNode &node : nodes)
        {
            cout << node.element << " ";
        }
        cout << endl;
    }
    return 0;
}