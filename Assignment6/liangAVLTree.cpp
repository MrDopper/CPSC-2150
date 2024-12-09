/*
 * Name: Jackson Vi
 * Id: 100372502
 * Instructor: Muntaseer Salahuddin
 * Section: 001
 */
#include "liangAVLTree.hpp"

// default contructor
AVLTree::AVLTree()
{
    // There is no node in the root
    root = nullptr;
    size = 0;
    height = 0;
}
// Pass an array of tree
AVLTree::AVLTree(int elements[], int arraySize)
{

    root = nullptr;
    size = 0;
    // Keep insert all the element inside an tree with avaible element in a given array
    for (int i = 0; i < arraySize; i++)
    {
        insert(elements[i]);
    }
}
// It will start from left node, current node and right node
void AVLTree::inorder() const
{
    inorder(root);
}
void AVLTree::inorder(const TreeNode *root) const
{
    // Base case if the root is empty return
    if (root == nullptr)
    {
        return;
    }
    // get all the left hand side node first
    inorder(root->left);
    cout << root->element << " ";
    inorder(root->right);
}
/*
    For example;
        12
       /  \
    10     23
    It should return an array of [12, 10, 23]
*/
///////EXERCISE////////
// return a queue of nodes in level order
queue<TreeNode *> AVLTree::LevelOrderNodes(TreeNode *someNode)
{
    queue<TreeNode *> nodeQueue;   // Queue to store nodes for level order
    queue<TreeNode *> resultQueue; // Queue to store the final result in level order

    if (someNode == nullptr)
        return resultQueue; // If the tree is empty, return an empty queue

    nodeQueue.push(someNode); // Start with the root node

    while (!nodeQueue.empty())
    {
        TreeNode *current = nodeQueue.front();
        nodeQueue.pop();

        resultQueue.push(current); // Add the current node to the result queue

        // Enqueue left and right children if they exist
        if (current->left != nullptr)
            nodeQueue.push(current->left);
        if (current->right != nullptr)
            nodeQueue.push(current->right);
    }

    return resultQueue;
}
///////EXERCISE////////
// display tree with level indices
void AVLTree::DisplayTreeWithLevelIndices(queue<TreeNode *> q)
{
    int level = 0;
    while (!q.empty())
    {
        int nodesAtCurrentLevel = q.size(); // Get the number of nodes at the current level
        cout << "Level " << level << ": ";

        for (int i = 0; i < nodesAtCurrentLevel; i++)
        {
            TreeNode *node = q.front();
            q.pop();
            cout << node->element << " ";

            // Re-enqueue children for the next level if you want to display them again
            if (node->left != nullptr)
                q.push(node->left);
            if (node->right != nullptr)
                q.push(node->right);
        }
        cout << endl;
        level++; // Move to the next level
    }
}
// The function will return the node within the current level
void AVLTree::LevelOrderDisplay()
{
    if (root == nullptr)
    {
        cout << "Tree is empty." << endl;
    }
    else
    {
        // An array that will store all the node from each level
        queue<TreeNode *> q = LevelOrderNodes(root);
        DisplayTreeWithLevelIndices(q);
    }
}
// display tree like a tree, horizontally
void AVLTree::DisplayTreeHorizontally()
{
    cout << "==========tree/horizontal view==========\n";
    DisplayTreeHorizontally(root, 0);
}
// display the tree rooted at someNode like a tree, horizontally
void AVLTree::DisplayTreeHorizontally(TreeNode *someNode, int space)
{

    if (someNode == nullptr)
    {
        return;
    }
    else
    {
        space += 10;

        DisplayTreeHorizontally(someNode->right, space);

        cout << endl;
        for (int i = 10; i < space; i++)
        {
            cout << " ";
        }
        cout << someNode->element << endl;

        DisplayTreeHorizontally(someNode->left, space);
    }
}
/* Get the number of nodes in the tree */
int AVLTree::getSize() const
{
    return size;
}
bool AVLTree::binaryTreeInsert(const int &e)
{
    if (root == nullptr)
    {
        root = createNewNode(e); // Create a new root
    }
    else
    {
        // Locate the parent node
        TreeNode *parent = nullptr;
        TreeNode *current = root;
        while (current != nullptr)
            if (e < current->element)
            {
                parent = current;
                current = current->left;
            }
            else if (e > current->element)
            {
                parent = current;
                current = current->right;
            }
            else
            {
                return false; // Duplicate node not inserted
            }
        // Create the new node and attach it to the parent node
        if (e < parent->element)
        {
            parent->left = createNewNode(e);
        }
        else
        {
            parent->right = createNewNode(e);
        }
    }

    size++;
    return true; // Element inserted
}
vector<TreeNode *> *AVLTree::path(const int &e) const
{
    vector<TreeNode *> *v = new vector<TreeNode *>();
    TreeNode *current = root;

    while (current != nullptr)
    {
        v->push_back(current);
        if (e < current->element)
        {
            current = current->left;
        }
        else if (e > current->element)
        {

            current = current->right;
        }
        else
        {
            break;
        }
    }
    return v;
}

// insert element into AVLTree
bool AVLTree::insert(int element)
{
    bool successful = binaryTreeInsert(element);
    if (!successful)
        return false; // element is already in the tree
    else
        // Balance from element to the root if necessary
        balancePath(element);

    return true; // element is inserted
}

// remove element from AVLTree
bool AVLTree::remove(int element)
{
    if (root == nullptr)
    {
        return false; // Element is not in the tree
    }
    // Locate the node to be deleted and also locate its parent node
    TreeNode *parent = nullptr;
    TreeNode *current = root;
    while (current != nullptr)
    {
        if (element < current->element)
        {
            parent = current;
            current = current->left;
        }
        else if (element > current->element)
        {
            parent = current;
            current = current->right;
        }
        else
        {
            break; // Element is in the tree pointed by current
        }
    }

    if (current == nullptr)
    {
        return false; // Element is not in the tree
    }
    // Case 0: current is a leaf
    if (current->left == nullptr && current->right == nullptr)
    {
        if (parent == nullptr)
        {
            root = nullptr;
        }
        else
        {
            if (element < parent->element)
            {
                parent->left = nullptr;
            }
            else
            {
                parent->right = nullptr;
            }
        }

        delete current; // Delete current
    }
    // Case 1: current has no left children
    else if (current->left == nullptr)
    {
        // Connect the parent with the right child of the current node
        if (parent == nullptr)
        {
            root = current->right;
        }
        else
        {
            if (element < parent->element)
            {
                parent->left = current->right;
            }
            else
            {
                parent->right = current->right;
            }

            // Balance the tree if necessary
            balancePath(parent->element);
        }

        delete current; // Delete current
    }
    else
    {
        // Case 2: The current node has a left child
        // Locate the rightmost node in the left subtree of
        // the current node and also its parent
        TreeNode *parentOfRightMost = current;
        TreeNode *rightMost = current->left;

        while (rightMost->right != nullptr)
        {
            parentOfRightMost = rightMost;
            rightMost = rightMost->right; // Keep going to the right
        }

        // Replace the element in current by the element in rightMost
        current->element = rightMost->element;

        // Eliminate rightmost node
        if (parentOfRightMost->right == rightMost)
        {
            parentOfRightMost->right = rightMost->left;
        }
        else
        {
            // Special case: parentOfRightMost is current
            parentOfRightMost->left = rightMost->left;
        }
        // Balance the tree if necessary
        balancePath(parentOfRightMost->element);

        delete rightMost; // Delete rightMost
    }

    size--;
    return true; // Element inserted
}

///////EXERCISE////////
/* Return the address of the node if the element is in the tree; returns nullptr otherwise */
TreeNode *AVLTree::search(const int &e) const
{
}
// create a new AVLTreeNode
TreeNode *AVLTree::createNewNode(int element)
{
    return new TreeNode(element);
}

///////EXERCISE////////
/** Balance the nodes in the path from the specified node to the root if necessary */
void AVLTree::balancePath(int element)
{
    vector<TreeNode *> *p = path(element);
    for (int i = p->size() - 1; i >= 0; i--)
    {
        TreeNode *A = (*p)[i];
        TreeNode *parentOfA = (A == root) ? nullptr : (*p)[i - 1];

        updateHeight(A); // ensure that height is updated first

        // WRITE CODE HERE
        // hint: we need to check if the tree is balanced at A i.e. use balanceFactors of A and A's children to determine if rotations are needed (if needed then perform rotations by calling the appropriate balance methods [SEE BELOW])
        int balance = balanceFactor(A);
        if (balance > 1)
        { // Right-heavy case
            if (balanceFactor(A->right) >= 0)
            {
                // Perform RR rotation
                balanceRR(A, parentOfA);
            }
            else
            {
                // Perform RL rotation
                balanceRL(A, parentOfA);
            }
        }
        else if (balance < -1)
        { // Left-heavy case
            if (balanceFactor(A->left) <= 0)
            {
                // Perform LL rotation
                balanceLL(A, parentOfA);
            }
            else
            {
                // Perform LR rotation
                balanceLR(A, parentOfA);
            }
        }
    }
}
/** Update the height of a specified node */
void AVLTree::updateHeight(TreeNode *node)
{
    if (node->left == nullptr && node->right == nullptr)
    { // node is a leaf
        node->height = 0;
    }
    else if (node->left == nullptr)
    { // node has no left subtree
        node->height = 1 + (*(node->right)).height;
    }
    else if (node->right == nullptr)
    { // node has no right subtree
        node->height = 1 + (*(node->left)).height;
    }
    else
    {
        node->height = 1 + max((*(node->right)).height, (*(node->left)).height);
    }
}
///////EXERCISE////////
/** Return the balance factor of the node */
int AVLTree::balanceFactor(TreeNode *node)
{
    // use right subtree height - left subtree height
    if (node == nullptr)
    {
        return 0;
    }
    int leftHeight = (node->left != nullptr) ? node->left->height : -1;
    int rightHeight = (node->right != nullptr) ? node->right->height : -1;

    return rightHeight - leftHeight;
}

/** Balance LL */
void AVLTree::balanceLL(TreeNode *A, TreeNode *parentOfA)
{
    TreeNode *B = A->left; // A is left-heavy and B is left-heavy

    if (A == root)
        root = B;
    else if (parentOfA->left == A)
        parentOfA->left = B;
    else
        parentOfA->right = B;

    A->left = B->right; // Make T2 the left subtree of A
    B->right = A;       // Make A the left child of B
    updateHeight(A);
    updateHeight(B);
}
/** Balance LR */
void AVLTree::balanceLR(TreeNode *A, TreeNode *parentOfA)
{
    TreeNode *B = A->left;  // A is left-heavy
    TreeNode *C = B->right; // B is right-heavy

    if (A == root)
        root = C;
    else if (parentOfA->left == A)
        parentOfA->left = C;
    else
        parentOfA->right = C;

    A->left = C->right; // Make T3 the left subtree of A
    B->right = C->left; // Make T2 the right subtree of B
    C->left = B;
    C->right = A;

    // Adjust heights
    updateHeight(A);
    updateHeight(B);
    updateHeight(C);
}

///////EXERCISE////////
/** Balance RR */
void AVLTree::balanceRR(TreeNode *A, TreeNode *parentOfA)
{
    TreeNode *B = A->right;
    if (A == root)
    {
        root = B;
    }
    else if (parentOfA->right == A)
    {
        parentOfA->right = B;
    }
    else
    {
        parentOfA->left = B;
    }
    A->right = B->left;
    B->left = A;
    updateHeight(A);
    updateHeight(B);
}

///////EXERCISE////////
/** Balance RL */
void AVLTree::balanceRL(TreeNode *A, TreeNode *parentOfA)
{
    TreeNode *B = A->right;
    TreeNode *C = B->left;

    if (A == root)
    {
        root = C;
    }
    else if (parentOfA->right == A)
    {
        parentOfA->right = C;
    }
    else
    {
        parentOfA->left = C;
    }
    A->right = C->left;
    B->left = C->right;
    C->left = A;
    C->right = B;
    updateHeight(A);
    updateHeight(B);
    updateHeight(C);
}
// returns the number of nodes at level level in the tree
int AVLTree::CountNodesAtLevel(int level)
{
    int count = 0;
    CountNodesAtLevel(root, level, count);
    return count;
}
///////EXERCISE////////
// helper function for CountNodesAtLevel
void AVLTree::CountNodesAtLevel(TreeNode *someNode, int level, int &count)
{
    if (someNode == nullptr)
    {
        return;
    }
    if (level == 0)
    {
        count++;
    }
    else
    {
        CountNodesAtLevel(someNode->left, level - 1, count);
        CountNodesAtLevel(someNode->right, level - 1, count);
    }
}
// returns the number of nodes in the tree that are between min and max (inclusive)
int AVLTree::Count(int min, int max)
{
    int count = 0;
    Count(root, min, max, count);
    return count;
}
///////EXERCISE////////
// helper function for Count
void AVLTree::Count(TreeNode *someNode, int min, int max, int &count)
{
    if (someNode == nullptr)
    {
        return;
    }
    if (someNode->element >= min && someNode->element <= max)
    {
        count++;
    }
    if (someNode->element > min)
    {
        Count(someNode->left, min, max, count);
    }
    if (someNode->element < max)
    {
        Count(someNode->right, min, max, count);
    }
}
///////EXERCISE////////
// right rotates the tree at node someNode if possible (if someNode is nullptr or someNode->left is nullptr, no rotation is performed)
void AVLTree::RotateRight(TreeNode *someNode)
{
    if (someNode == nullptr || someNode->left == nullptr)
    {
        return; // Rotation not possible
    }

    TreeNode *B = someNode->left;
    someNode->left = B->right;
    B->right = someNode;

    updateHeight(someNode);
    updateHeight(B);

    if (someNode == root)
    {
        root = B;
    }
}
///////EXERCISE////////
// left rotates the tree at node someNode if possible (if someNode is nullptr or someNode->right is nullptr, no rotation is performed)
void AVLTree::RotateLeft(TreeNode *someNode)
{
    if (someNode == nullptr || someNode->right == nullptr)
    {
        return; // Rotation not possible
    }

    TreeNode *B = someNode->right;
    someNode->right = B->left;
    B->left = someNode;

    updateHeight(someNode);
    updateHeight(B);

    if (someNode == root)
    {
        root = B;
    }
}
// returns the diameter of the tree
// diameter is the number of nodes along the longest path between any two leaves in the tree
// see https://leetcode.com/problems/diameter-of-binary-tree/
int AVLTree::Diameter()
{
    return Diameter(root);
}

///////EXERCISE////////
// helper function for Diameter
int AVLTree::Diameter(TreeNode *someNode)
{
    if (someNode == nullptr)
    {
        return 0;
    }

    int leftHeight = someNode->left ? someNode->left->height : -1;
    int rightHeight = someNode->right ? someNode->right->height : -1;

    int leftDiameter = Diameter(someNode->left);
    int rightDiameter = Diameter(someNode->right);

    int rootDiameter = leftHeight + rightHeight + 2;

    return max(rootDiameter, max(leftDiameter, rightDiameter));
}