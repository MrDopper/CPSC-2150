/*
 * Name: Jackson Vi
 * Id: 100372502
 * Instructor: Muntaseer Salahuddin
 * Section: 001
 */
#include "liangAVLTree.hpp"
#include <iostream>

int main()
{
    // Array of elements to initialize the AVL tree
    int elements[] = {25, 20, 5, 34, 50, 30, 10};
    int size = sizeof(elements) / sizeof(elements[0]);

    // Create an AVL tree with the array elements
    AVLTree avlTree(elements, size);
    avlTree.DisplayTreeHorizontally();
    avlTree.LevelOrderDisplay(); // Display level order after each insertion

    for (int level = 0; level <= 2; ++level)
    {
        int count = avlTree.CountNodesAtLevel(level);
        cout << "Nodes at Level " << level << ": " << count << "\n";
    }

    std::cout << "In-Order Traversal\n";
    avlTree.inorder();
    cout << "\n";

    cout << "\n Basic Insertion\n";
    int array2[] = {10, 30, 20};
    AVLTree tree2;
    for (int element : array2)
    {
        cout << "Inserting " << element << " into AVL tree\n";
        tree2.insert(element);
        tree2.LevelOrderDisplay(); // Display level order after each insertion
        cout << "\n";
    }
    tree2.DisplayTreeHorizontally();

    tree2.remove(20);
    tree2.remove(40);
    tree2.DisplayTreeHorizontally();
    cout << "\n";
    cout << "Diameter of the Tree2\n";
    tree2.insert(4);
    tree2.insert(15);
    tree2.DisplayTreeHorizontally();
    int diameter = tree2.Diameter();
    cout << "Diameter of the tree: " << diameter << "\n\n";

    std::cout << "Count Nodes in Range [10, 30]\n";
    int countInRange = tree2.Count(10, 30);
    std::cout << "Number of nodes with values between 10 and 30: " << countInRange << "\n\n";

    // LL
    AVLTree tree3;
    tree3.insert(4);
    tree3.insert(5);
    tree3.insert(6);
    tree3.insert(7);
    tree3.insert(8);
    tree3.insert(9);
    tree3.DisplayTreeHorizontally();
    return 0;
}
