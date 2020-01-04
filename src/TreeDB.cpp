/* 
 * File:   TreeDB.cpp
 * Author: najaomar
 *
 * Created on November 21, 2019, 4:34 PM
 */

#include <iostream>
#include <string>

using namespace std;

#include "TreeDB.h"

void print_tree_in_order(TreeNode* root);

// The default constructor, creates an empty database
TreeDB::TreeDB()
{
    root = NULL;
    probesCount = 0;
}

// The destructor, deletes all the entries in the database
TreeDB::~TreeDB()
{
    clear();
}

// Inserts the entry pointed to by newEntry into the database.
// If an entry with the same key as newEntry's exists 
// in the database, it returns false. Otherwise, it returns true.
bool TreeDB::insert(DBentry* newEntry)
{
    if (newEntry == NULL) 
    {
        return true; // Nothing to insert 
    }
    
    // Create new first node and insert entry if no tree.
    if (root == NULL) 
    {  
        root = new TreeNode(newEntry);
        return true; 
    } 
    
    // Helper function to facilitate the recursion 
    return insert_bst(root, newEntry); 
}

bool TreeDB::insert_bst(TreeNode* root, DBentry* newEntry)
{
    // If the entry being inserted already exists in the tree, don't continue
    if (root->getEntry()->getName() == newEntry->getName())
    {
        return false;
    } 
    else if (newEntry->getName() < root->getEntry()->getName()) 
    {   
        // Basis case: insert entry as a leaf node (to the left of its parent)
        if (root->getLeft() == NULL) 
        { 
            TreeNode* newNode = new TreeNode(newEntry);
            root->setLeft(newNode);
            return true;
        }
        else 
        {
            // Try insertion into the left subtree
            return insert_bst(root->getLeft(), newEntry); 
        }
        
    } else if (newEntry->getName() > root->getEntry()->getName()) 
    {  
        // Basis case: insert entry as a leaf node (to the right of its parent)
        if (root->getRight() == NULL) 
        { 
            TreeNode* newNode = new TreeNode(newEntry);
            root->setRight(newNode); 
            return true;
        } 
        else 
        {
            // Try insertion into the right subtree
            return insert_bst(root->getRight(), newEntry); 
        }
    } 
}

// Searches the database for an entry with a key equal to name.
// If the entry is found, a pointer to it is returned.
// If the entry is not found, the NULL pointer is returned.
// Also sets probesCount.
DBentry* TreeDB::find(string name)
{
    // Helper function to facilitate the recursion
    if (find_node(root, name) == NULL)
    {
        return NULL;
    }
    
    probesCount = 0;
    
    return find_node(root, name)->getEntry(); 
}

// Function to find a node with a a key equal to name.
// If the node is found, a pointer to it is returned.
// If the node is not found, the NULL pointer is returned.
// Also sets probesCount.
TreeNode* TreeDB::find_node(TreeNode* root, string name)
{
    // Empty tree
    if (root == NULL)
    {
        return NULL;
    }
    
    probesCount++;
    
    // Node found
    if (root->getEntry()->getName() == name)
    {
        return root;
    } 
    else if (name < root->getEntry()->getName()) 
    {
        // Search the left subtree
        return find_node(root->getLeft(), name);
    } 
    else if (name > root->getEntry()->getName()) 
    {
        // Search the right subtree
        return find_node(root->getRight(), name);
    }
}

// Deletes the entry with the specified name (key) from the database.
// If the entry was indeed in the database, it returns true.
// Returns false otherwise.
// See section 6 of the lab handout for the *required* removal method.
// If you do not use that removal method (replace deleted node by
// maximum node in the left subtree when the deleted node has two children),
// you will not match exercise's output.
bool TreeDB::remove(string name)
{ 
    if (find(name) == NULL)
    {
        return false;
    }

    TreeNode* unwantedNode = find_node(root, name); // Pointer to node to be deleted 
    TreeNode* parentNode = NULL;                    // Pointer to parent of node to be deleted
    TreeNode* replacementNode = NULL;               // Pointer to replacement for node to be deleted
    TreeNode* replacementParent = NULL;             // Pointer to parent of the replacement
        
    // Case 1: if the user is requesting to remove the root node
    if (unwantedNode == root)
    {
        // Case 1a: leaf node
        if (unwantedNode->getLeft() == NULL && unwantedNode->getRight() == NULL)
        {
            clear();
            return true;
        }
        // Case 1b: a node with only a left subtree 
        else if (unwantedNode->getLeft() != NULL && unwantedNode->getRight() == NULL) 
        {
            root = unwantedNode->getLeft();
        }
        // Case 1c: a node with only a right subtree 
        else if (unwantedNode->getLeft() == NULL && unwantedNode->getRight() != NULL) 
        {
            root = unwantedNode->getRight();
        }
        // Case 1d: a node with both a left and a right subtree 
        else if (unwantedNode->getLeft() != NULL && unwantedNode->getRight() != NULL)
        {
            // Function to find maximum node of a subtree
            replacementNode = find_max(unwantedNode->getLeft());
            // Function to find the parent of a node
            replacementParent = find_node_parent(root, replacementNode->getEntry()->getName());

            // If the replacement node is a left child,
            // make the left child of its parent NULL.
            if (replacementNode == replacementParent->getLeft())
            {
                replacementParent->setLeft(NULL);
            }
            // If the replacement node is a right child,
            // make the right child of its parent NULL.
            else if (replacementNode == replacementParent->getRight())
            {
                replacementParent->setRight(NULL);
            }

            // If the replacement node does not have a left child
            // and it is not the head of unwantedNode's left subtree,
            // make its left child to be the left child of unwantedNode.
            if ((replacementNode->getLeft() == NULL) && (replacementNode != unwantedNode->getLeft()))
            {
                replacementNode->setLeft(unwantedNode->getLeft());
            }
            // If the replacement node does not have a right child
            // make its right child to be the right child of unwantedNode.
            if(replacementNode->getRight() == NULL)
            {
                replacementNode->setRight(unwantedNode->getRight());
            }
                    
            root = replacementNode;
        }
            
    }
    // Case 2: if the user is requesting to remove a node other than the root node
    else
    {
        parentNode = find_node_parent(root, name); 
        
        // Case 2a: leaf node
        if (unwantedNode->getLeft() == NULL && unwantedNode->getRight() == NULL)
        {
            // If the node to be deleted is a left child,
            // make the left child of its parent NULL.
            if (unwantedNode == parentNode->getLeft())
            {
                parentNode->setLeft(NULL);
                
            }
            // If the unwanted node is a right child,
            // make the right child of its parent NULL.
            else if (unwantedNode == parentNode->getRight())
            {
                parentNode->setRight(NULL);
            }
            
            delete unwantedNode;
            return true;
            
        }
        // Case 2b: a node with only a left subtree 
        else if (unwantedNode->getLeft() != NULL && unwantedNode->getRight() == NULL)
        {
            replacementNode = unwantedNode->getLeft();   
            
        }
        // Case 2c: a node with only a right subtree 
        else if (unwantedNode->getLeft() == NULL && unwantedNode->getRight() != NULL)
        {
            replacementNode = unwantedNode->getRight();
            
        }
        // Case 2d: a node with both a left and a right subtree 
        else if ((unwantedNode->getLeft() != NULL && unwantedNode->getRight() != NULL))
        {
            replacementNode = find_max(unwantedNode->getLeft());
            replacementParent = find_node_parent(root, replacementNode->getEntry()->getName());
            
            // If the replacement node is a left child,
            // make the left child of its parent NULL.
            if (replacementNode == replacementParent->getLeft())
            {
                replacementParent->setLeft(NULL);
                
            }
            // If the replacement node is a right child,
            // make the right child of its parent NULL.
            else if (replacementNode == replacementParent->getRight())
            {
                replacementParent->setRight(NULL);
            }

            // If the replacement node does not have a left child
            // and it is not the head of unwantedNode's left subtree,
            // make its left child to be the left child of unwantedNode.
            if ((replacementNode->getLeft() == NULL) && (unwantedNode->getLeft() != replacementNode))
            {
                replacementNode->setLeft(unwantedNode->getLeft());
            }
            // If the replacement node does not have a right child,
            // make its right child to be the right child of unwantedNode.
            if(replacementNode->getRight() == NULL)
            {
                replacementNode->setRight(unwantedNode->getRight());
            }
        }
         
        // If the unwanted node is a left child,
        // make the replacement node the left child of the unwanted node's parent.
        if (unwantedNode == parentNode->getLeft())
        {
            parentNode->setLeft(replacementNode);
            
        }
        // If the unwanted node is a right child,
        // make the replacement node the right child of the unwanted node's parent.
        else if (unwantedNode == parentNode->getRight())
        {
            parentNode->setRight(replacementNode);
        }
    }
    
    delete unwantedNode;
    return true;

}   

// Function to find the maximum node of a subtree.
// If the node is found, a pointer to it is returned.
TreeNode* TreeDB::find_max(TreeNode* root)
{
    while (root->getRight() != NULL)
    {
        root = root->getRight();
    }
    
    return root;
}

// Function to find the parent of a node.
// If the parent node is found, a pointer to it is returned.
// If the node is not found, the NULL pointer is returned.
TreeNode* TreeDB::find_node_parent(TreeNode* root, string name)
{
    // Empty tree
    if(root == NULL)
    {
        return NULL;
    }
    
    // Node found
    if((root->getLeft() != NULL && root->getLeft()->getEntry()->getName() == name) || 
        (root->getRight() != NULL && root->getRight()->getEntry()->getName() == name))
    {
        return root;
    }
    else if(name < root->getEntry()->getName())
    {
        // Search the left subtree
        return find_node_parent(root->getLeft(), name);
    } 
    else if(name > root->getEntry()->getName())
    {
        // Search the right subtree
        return find_node_parent(root->getRight(), name);
    }
}
	
// Deletes all the entries in the database
void TreeDB::clear()
{
    // Helper function to facilitate the recursion
    delete_tree(root);
    
    root = NULL;
}

// Deletes all entries in the database
void TreeDB::delete_tree(TreeNode* root)
{
    // Basis case: nothing to do if no tree 
    if (root == NULL) 
    {
        return;
    }
    
    // Else there is at least one node 
    
    // Delete the left subtree
    delete_tree(root->getLeft()); 
    
    // Delete the right subtree
    delete_tree(root->getRight());
    
    // Now, delete the node 
    delete root; 
}
    
// Prints the number of probes stored in probesCount
void TreeDB::printProbes() const
{
    cout << probesCount << endl;
}
   
// Computes and prints out the total number of active entries
// in the database (i.e. entries with active == true).
void TreeDB::countActive() const
{
    int count = 0;
    
    // Helper function to facilitate the recursion
    active_count(root, count);
    
    cout << count << endl;
}

// Computes the total number of active entries 
// in the database (i.e. entries with active == true).
void TreeDB::active_count(TreeNode* root, int& count) const
{
    if (root != NULL) 
    {     
        // If the node's entry is active, increment count
        if (root->getEntry()->getActive())
        {
            count++;
        }
        
        // Check the left subtree
        active_count(root->getLeft(), count);
        
        // Check the right subtree
        active_count(root->getRight(), count); 
    } 
    
    return;
}

// Prints the entire tree, in ascending order of key/name
ostream& operator<< (ostream& out, const TreeDB& rhs)
{
    // Helper function to facilitate the recursion
    print_tree_in_order(rhs.root);
}

// Prints the entire tree, in ascending order of key/name
void print_tree_in_order(TreeNode* root)
{
    if (root != NULL) 
    {
        // Print the left subtree
        print_tree_in_order(root->getLeft()); 

        // Print the node's entry
        cout << *root->getEntry();
        
        // Print the right subtree
        print_tree_in_order(root->getRight()); 
    } 
}

