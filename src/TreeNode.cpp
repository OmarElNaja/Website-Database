/* 
 * File:   TreeNode.cpp
 * Author: najaomar
 *
 * Created on November 21, 2019, 4:35 PM
 */

#include "TreeNode.h"

// A useful constructor
TreeNode::TreeNode(DBentry* _entryPtr)
{
    entryPtr = _entryPtr;
    right = NULL;
    left = NULL;
}

// The destructor
TreeNode::~TreeNode()
{
    delete entryPtr;
    entryPtr = NULL;
    left = NULL;
    right = NULL;
}

// Sets the left child of the TreeNode
void TreeNode::setLeft(TreeNode* newLeft)
{
    left = newLeft;
}

// Sets the right child of the TreeNode
void TreeNode::setRight(TreeNode* newRight)
{
    right = newRight;
}

// Gets the left child of the TreeNode
TreeNode* TreeNode::getLeft() const
{
    return left;
}

// Gets the right child of the TreeNode
TreeNode* TreeNode::getRight() const
{
    return right;
}

// Returns a pointer to the DBentry the TreeNode contains
DBentry* TreeNode::getEntry() const
{
    return entryPtr;
}

