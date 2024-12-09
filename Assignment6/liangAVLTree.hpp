/*
 * Name: Jackson Vi
 * Id: 100372502
 * Instructor: Muntaseer Salahuddin
 * Section: 001
 */
#ifndef AVLTREE_H
#define AVLTREE_H
#include "TreeNode.hpp"
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

class AVLTree
{
public:
  AVLTree();
  AVLTree(int elements[], int arraySize);
  /* Inorder traversal */
  void inorder() const;
  /* Inorder traversal from a subtree */
  void inorder(const TreeNode *root) const;
  ///////EXERCISE////////
  // return a queue of nodes in level order
  queue<TreeNode *> LevelOrderNodes(TreeNode *someNode);
  ///////EXERCISE////////
  // display tree with level indices
  void DisplayTreeWithLevelIndices(queue<TreeNode *> q);
  // level order display
  void LevelOrderDisplay();
  /** SAMPLE OUTPUT
    After inserting 25, 20, 5:
    level 0: 20
    level 1: 5 25

    After inserting 34, 50:
    level 0: 20
    level 1: 5 34
    level 2: 25 50

    After inserting 30
    level 0: 25
    level 1: 20 34
    level 2: 5 30 50

    After inserting 10
    level 0: 25
    level 1: 10 34
    level 2: 5 20 30 50

    After removing 34, 30, 50:
    level 0: 10
    level 1: 5 25
    level 2: 20

    After removing 5:
    level 0: 20
    level 1: 10 25
  */
  // display tree like a tree, horizontally
  void DisplayTreeHorizontally();
  // display the tree rooted at someNode like a tree, horizontally
  void DisplayTreeHorizontally(TreeNode *someNode, int space);
  /* Get the number of nodes in the tree */
  int getSize() const;
  // Insert element e into the binary tree
  // Return true if the element is inserted successfully
  // Return false if the element is already in the list
  bool binaryTreeInsert(const int &e);
  // Return a path from the root leading to the specified element
  vector<TreeNode *> *path(const int &e) const;
  // insert element into AVLTree
  bool insert(int element);
  // remove element from AVLTree
  bool remove(int element);
  ///////EXERCISE////////
  /* Return the address of the node if the element is in the tree; returns nullptr otherwise */
  TreeNode *search(const int &e) const;
  // create a new AVLTreeNode
  TreeNode *createNewNode(int element);
  ///////EXERCISE////////
  /** Balance the nodes in the path from the specified node to the root if necessary */
  void balancePath(int element);
  /** Update the height of a specified node */
  void updateHeight(TreeNode *node);
  ///////EXERCISE////////
  /** Return the balance factor of the node */
  int balanceFactor(TreeNode *node);
  /** Balance LL */
  void balanceLL(TreeNode *A, TreeNode *parentOfA);
  /** Balance LR */
  void balanceLR(TreeNode *A, TreeNode *parentOfA);
  ///////EXERCISE////////
  /** Balance RR */
  void balanceRR(TreeNode *A, TreeNode *parentOfA);
  ///////EXERCISE////////
  /** Balance RL */
  void balanceRL(TreeNode *A, TreeNode *parentOfA);
  // returns the number of nodes at level level in the tree
  int CountNodesAtLevel(int level);
  ///////EXERCISE////////
  // helper function for CountNodesAtLevel
  void CountNodesAtLevel(TreeNode *someNode, int level, int &count);
  // returns the number of nodes in the tree that are between min and max (inclusive)
  int Count(int min, int max);
  ///////EXERCISE////////
  // helper function for Count
  void Count(TreeNode *someNode, int min, int max, int &count);
  ///////EXERCISE////////
  // right rotates the tree at node someNode if possible (if someNode is nullptr or someNode->left is nullptr, no rotation is performed)
  void RotateRight(TreeNode *someNode);
  ///////EXERCISE////////
  // left rotates the tree at node someNode if possible (if someNode is nullptr or someNode->right is nullptr, no rotation is performed)
  void RotateLeft(TreeNode *someNode);
  // returns the diameter of the tree
  // diameter is the number of nodes along the longest path between any two leaves in the tree
  // see https://leetcode.com/problems/diameter-of-binary-tree/
  int Diameter();
  ///////EXERCISE////////
  // helper function for Diameter
  int Diameter(TreeNode *someNode);

private:
  TreeNode *root;
  int size;
  int height;
  vector<TreeNode *> backups;
};

#endif
