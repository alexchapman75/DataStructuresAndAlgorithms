#ifndef EXTENDEDAVLTREE_H
#define EXTENDEDAVLTREE_H

#include "AVLTree.h"
#include "ExtendedAVLNode.h"
#include <stdexcept>

class ExtendedAVLTree : public AVLTree {
protected:
   // Use ExtendedAVLNode
   virtual BSTNode* MakeNewNode(int key) override {
      return new ExtendedAVLNode(key);
   }

   // Override insert to fix subtree counts
   virtual void InsertNode(BSTNode* node) override {
      AVLTree::InsertNode(node);

      // Fix counts going upward
      ExtendedAVLNode* current = (ExtendedAVLNode*) node;
      while (current) {
         current->FixCountUpwards();
         current = (ExtendedAVLNode*) current->GetParent();
      }
   }

   // Override remove to fix subtree counts
   virtual bool RemoveNode(BSTNode* nodeToRemove) override {
      BSTNode* parent = nodeToRemove ? nodeToRemove->GetParent() : nullptr;

      bool result = AVLTree::RemoveNode(nodeToRemove);

      // Fix counts upward from parent
      while (parent) {
         ((ExtendedAVLNode*) parent)->FixCountUpwards();
         parent = parent->GetParent();
      }

      return result;
   }

public:
   virtual int GetNthKey(int n) override {
      ExtendedAVLNode* current = (ExtendedAVLNode*) root;

      while (current) {
         int leftCount = 0;

         if (current->GetLeft()) {
            leftCount = ((ExtendedAVLNode*) current->GetLeft())->GetSubtreeKeyCount();
         }

         if (n < leftCount) {
            current = (ExtendedAVLNode*) current->GetLeft();
         }
         else if (n == leftCount) {
            return current->GetKey();
         }
         else {
            n = n - leftCount - 1;
            current = (ExtendedAVLNode*) current->GetRight();
         }
      }

      throw std::out_of_range("n is out of range");
   }
};

#endif