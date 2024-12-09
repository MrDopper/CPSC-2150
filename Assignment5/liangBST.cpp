/*
 * Name: Jackson Vi
 * Id: 100372502
 * Instructor: Muntaseer Salahuddin
 * Section: 001
 */
#include "liangBST.h"

BST::BST()
{
    root = nullptr;
    size = 0;
}
BST::BST(int *elements, int arraySize)
{
    root = nullptr;
    size = 0;
    for (int i = 0; i < arraySize; i++)
    {
        insert(elements[i]);
    }
}

BST::BST(const BST &tree)
{
    root = nullptr;
    size = 0;
    // Copy the root of the tree
    copy(tree.root);
}
void BST::copy(const TreeNode *root)
{
    if (root != nullptr)
    {
        // Insert the node into a new tree recursively
        insert(root->element);
        // copy the left subtree
        copy(root->left);
        // Then move to the right and copy the right subtree
        copy(root->right);
    }
}
BST::~BST()
{
    clear();
}
TreeNode *BST::search(const int &e) const
{
    /* Return the address of the node if the element is in the tree; returns nullptr otherwise */
    TreeNode *current = root;
    while (current != nullptr)
        if (e < current->element)
        {
            current = current->left; // Move left
        }
        else if (e > current->element)
        {
            current = current->right; // Move right
        }
        else if (e == current->element)
        {
            return current;
        }
    return nullptr;
}
TreeNode *BST::createNewNode(const int &e)
{
    return new TreeNode(e);
}

bool BST::insert(const int &e)
{
    // Base case, if there isn't any node in a tree.
    if (root == nullptr)
        root = createNewNode(e); // Create a new root
    // If there is a node in a tree which is root node.
    else
    {
        // Locate the parent node
        TreeNode *parent = nullptr;
        TreeNode *current = root;
        while (current != nullptr)
            // locate the node to the left handside
            if (e < current->element)
            {
                parent = current;
                current = current->left;
            }
            // Locate the nod to the right handside
            else if (e > current->element)
            {
                parent = current;
                current = current->right;
            }
            else
                return false; // Duplicate node not inserted

        // Create the new node and attach it to the parent node
        if (e < parent->element)
            parent->left = createNewNode(e);
        else
            parent->right = createNewNode(e);
    }

    size++;
    return true; // Element inserted
}
void BST::inorder() const
{
    inorder(root);
}
void BST::inorder(const TreeNode *someNode) const
{
    if (someNode == nullptr)
    {
        return;
    }
    inorder(someNode->left);          // process all nodes in left sub-tree of someNode
    cout << someNode->element << " "; // process someNode
    inorder(someNode->right);         // process all nodes in right sub-tree of someNode
}
int BST::getSize() const
{
    return size;
}
void BST::clear()
{
    clear(root);
    root = nullptr;
    size = 0;
}
// An helper function to clean up the node
void BST::clear(TreeNode *rootNode)
{
    if (rootNode == nullptr)
    {
        return;
    }
    clear(rootNode->left);
    clear(rootNode->right);
    delete rootNode;
}
vector<TreeNode *> *BST::path(const int &e) const
{ // Create a new vector that is empty
    vector<TreeNode *> *result = new vector<TreeNode *>();
    // Start from the root node
    TreeNode *current = root;

    while (current != nullptr)
    {
        // Add the current node to the path
        result->push_back(current);
        if (e < current->element)
        {
            current = current->left; // Move left
        }
        else if (e > current->element)
        {
            current = current->right; // Move right
        }
        else
        {
            return result; // Element found, return the path
        }
    }
    // the element was not found. Put nullptr inside a result array then return it.
    result->push_back(nullptr);
    return result;
}
bool BST::remove(const int &e)
{
    // Locate the node to be deleted and also locate its parent node
    TreeNode *parent = nullptr;
    TreeNode *current = root;
    while (current != nullptr)
    {
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
            break; // Element e is in the tree pointed by current
    }

    if (current == nullptr)
        return false; // Element e is not in the tree

    // Case 0: current is a leaf
    if (current->left == nullptr && current->right == nullptr)
    {
        if (parent == nullptr)
        {
            root = nullptr;
        }
        else
        {
            // if the node you want to delete is less than the parent node of the node you try to delete
            if (e < parent->element)
            {
                // Set the left handside of it to be nullptr (mean delete the node)
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
            if (e < parent->element)
            {
                parent->left = current->right;
            }
            else
            {
                parent->right = current->right;
            }
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
            parentOfRightMost->right = rightMost->left;
        else
            // Special case: parentOfRightMost->right == current
            parentOfRightMost->left = rightMost->left;

        delete rightMost; // Delete rightMost
    }

    size--;
    return true; // Element inserted
}

int BST::GetHeight()
{
    // Base case return 0;
    if (root == nullptr)
    {
        return -1;
    }
    else
    {
        return GetHeight(root);
    }
}
int BST::GetHeight(TreeNode *someNode)
{
    // Base case for recursive call function.
    if (someNode == nullptr)
    {
        return -1;
    }
    int leftHeight = GetHeight(someNode->left);
    int rightHeight = GetHeight(someNode->right);
    return max(leftHeight, rightHeight) + 1;
}
// Return the highest number inside a tree
int BST::Max()
{
    // Mean the tree is empty and the highest number at current moment is zero.
    if (root == nullptr)
    {
        return 0;
    }
    TreeNode *current = root;
    // Because the highest node is always located in the right handside.
    while (current->right != nullptr)
    {
        current = current->right;
    }
    return current->element;
}
// Return the smallest number inside a tree
int BST::Min()
{
    // Mean the tree is empty and the smallest number at current moment is zero.
    if (root == nullptr)
    {
        return 0;
    }
    TreeNode *current = root;
    while (current->left != nullptr)
    {
        current = current->left;
    }
    return current->element;
}
bool BST::IsBST()
{
    if (root == nullptr)
    {
        return true;
    }
    TreeNode *current = root;
    TreeNode *prev = nullptr;
    TreeNode *predecessor = nullptr;
    while (current != nullptr)
    {
        if (current->left == nullptr)
        {
            // Process the current node
            if (prev != nullptr && current->element <= prev->element)
            {
                return false; // Not in sorted order, so it's not a BST
            }

            // Update prev to the current node
            prev = current;

            // Move to the right child
            current = current->right;
        }
        else
        {
            // Find the inorder predecessor of current
            predecessor = current->left;
            while (predecessor->right != nullptr && predecessor->right != current)
            {
                predecessor = predecessor->right;
            }

            // Make current the right child of its inorder predecessor
            if (predecessor->right == nullptr)
            {
                predecessor->right = current;
                current = current->left;
            }
            else
            {
                // Revert the changes made in the tree
                predecessor->right = nullptr;

                // Process the current node
                if (prev != nullptr && current->element <= prev->element)
                {
                    return false; // Not in sorted order, so it's not a BST
                }

                // Update prev to the current node
                prev = current;

                // Move to the right child
                current = current->right;
            }
        }
    }
    return true;
}
int BST::Height()
{
    if (root == 0)
    {
        return 0;
    }
    return Height(root);
}

int BST::Height(TreeNode *someNode)
{
    // Base case for recursive call function.
    if (someNode == nullptr)
    {
        return 0;
    }
    int leftHeight = Height(someNode->left);
    int rightHeight = Height(someNode->right);
    return max(leftHeight, rightHeight) + 1;
}

void BST::LevelOrderDisplay()
{
    LevelOrderDisplay(root);
}
void BST::LevelOrderDisplay(TreeNode *someNode)
{
    if (root == nullptr)
    {
        return;
    }
    std::queue<TreeNode *> q;
    q.push(someNode); // Start with the given node

    while (!q.empty())
    {
        // Get the current node from the queue
        TreeNode *current = q.front();
        q.pop();

        // Display the current node's element
        cout << current->element << " ";

        // Enqueue the left child
        if (current->left != nullptr)
        {
            q.push(current->left);
        }

        // Enqueue the right child
        if (current->right != nullptr)
        {
            q.push(current->right);
        }
    }
    cout << endl;
}
void BST::DisplayTreeHorizontally()
{
    DisplayTreeHorizontally(root, 0);
}
void BST::DisplayTreeHorizontally(TreeNode *someNode, int space)
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
vector<TreeNode> BST::NodesAtDistance(int k)
{
    std::vector<TreeNode> nodeLevel;
    // Return an empty array
    if (k < 0)
    {
        return nodeLevel;
    }
    NodesAtDistance(root, k, nodeLevel);

    return nodeLevel;
}

void BST::NodesAtDistance(TreeNode *node, int k, vector<TreeNode> &nodeLevel)
{
    if (node == nullptr)
    {
        return;
    }

    if (k == 0)
    {
        // If k is 0, add the current node to the result
        nodeLevel.push_back(*node);
        return;
    }

    // Recursive for the left and right
    NodesAtDistance(node->left, k - 1, nodeLevel);
    NodesAtDistance(node->right, k - 1, nodeLevel);
}
