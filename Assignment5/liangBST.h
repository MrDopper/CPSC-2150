/*
 * Name: Jackson Vi
 * Id: 100372502
 * Instructor: Muntaseer Salahuddin
 * Section: 001
 */
#ifndef BST_H
#define BST_H

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include "TreeNode.h"
using namespace std;
class BST
{
public:
  // Default constructor
  BST();
  // Define constructor
  BST(int *elements, int arraySize);
  /* Copy constructor */
  // Recursively copy nodes to this tree
  BST(const BST &tree);
  /////EXERCISE
  /* Deep Copies all elements from the specified tree to this tree */
  void copy(const TreeNode *root);
  /* Destructor */
  ~BST();
  /////EXERCISE
  /* Return the address of the node if the element is in the tree; returns nullptr otherwise */
  TreeNode *search(const int &e) const;
  TreeNode *createNewNode(const int &e);
  // Insert element e into the binary tree
  // Return true if the element is inserted successfully
  // Return false if the element is already in the list
  bool insert(const int &e);
  /* Inorder traversal */
  void inorder() const;
  /* Inorder traversal from a subtree */
  void inorder(const TreeNode *someNode) const;
  /* Get the number of nodes in the tree */
  int getSize() const;
  /////EXERCISE
  /* Remove all nodes from the tree */
  void clear();

  /////EXERCISE
  /* Return a path from the root leading to the specified element.
  If specified element does not exist in the tree then add a nullptr to the vector and return it. */
  vector<TreeNode *> *path(const int &e) const;
  /* Delete an element e from the binary tree.
   * Return true if the element is deleted successfully
   * Return false if the element is not in the tree */
  bool remove(const int &e);
  /////ADDITIONAL EXERCISES/////
  // returns the height of the tree
  int GetHeight();
  /////EXERCISE
  // returns the height of someNode
  // height of a node is the number of edges on the longest path from the node to a leaf
  int GetHeight(TreeNode *someNode);
  /////EXERCISE
  // returns the maximum value in the tree
  int Max();
  // returns the minimum value in the tree
  int Min();
  // returns true if the tree is a binary search tree; false otherwise
  bool IsBST();
  // returns the number of nodes in the longest path from the root to a leaf
  int Height();
  // level order display
  void LevelOrderDisplay();
  /////EXERCISE
  // level order display of the tree rooted at someNode
  // use a queue, STL queue is fine
  void LevelOrderDisplay(TreeNode *someNode);

  // display tree like a tree horizontally
  void DisplayTreeHorizontally();

  // display the tree rooted at someNode like a tree, horizontally
  void DisplayTreeHorizontally(TreeNode *someNode, int space);

  // returns the nodes at distance k from the root
  // the distance from the root to the root is 0
  // the distance from the root to its children is 1
  // if k is negative, return an empty vector
  vector<TreeNode> NodesAtDistance(int k);

private:
  TreeNode *root;
  int size;
  // Helper function
  void clear(TreeNode *rootNode);
  int Height(TreeNode *someNode);
  void NodesAtDistance(TreeNode *node, int k, vector<TreeNode> &result);
};

#endif
