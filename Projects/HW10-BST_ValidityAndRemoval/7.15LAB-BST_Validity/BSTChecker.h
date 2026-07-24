#ifndef BSTCHECKER_H
#define BSTCHECKER_H

// TODO: Include any needed header files
#include "BSTNode.h"
#include <unordered_set>
#include <limits>

class BSTChecker {
public:
   static BSTNode* Validate(BSTNode* node, long min, long max, std::unordered_set<BSTNode*>& visited) {
    
    if(!node) return nullptr;

    //check for cycle
    if(visited.count(node)){
        return node;
    }
    visited.insert(node);

    //check for violate BST
    if(node->key <= min || node ->key >= max) {
        return node;
    }

    //check left
    BSTNode* leftResult = Validate(node->left, min, node->key, visited);
    if(leftResult) return leftResult;

    //check right
    BSTNode* rightResult = Validate(node->right, node->key, max, visited);
    if(rightResult) return rightResult;

    return nullptr;

   }

   // CheckBSTValidty() determines if the tree is a valid BST. If so, nullptr
   // is returned. If not, the first (in preorder traversal) node in violation
   // of BST requirements is returned. Such a node will be one of the following:
   // - A node in the left subtree of an ancestor with a lesser or equal key
   // - A node in the right subtree of an ancestor with a greater or equal key
   // - A node that is encountered more than once during traversal
   static BSTNode* CheckBSTValidity(BSTNode* rootNode) {
      std::unordered_set<BSTNode*> visited;

      return Validate(rootNode, std::numeric_limits<long>::min(), std::numeric_limits<long>::max(), visited);
   }
};

#endif
