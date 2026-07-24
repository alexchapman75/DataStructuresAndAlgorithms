#ifndef EXTENDEDAVLNODE_H
#define EXTENDEDAVLNODE_H

#include "AVLNode.h"

class ExtendedAVLNode : public AVLNode {
private:
   int subtreeKeyCount;

   // Recalculate subtree size
   void UpdateSubtreeKeyCount() {
      int leftCount = 0;
      int rightCount = 0;

      if (GetLeft()) {
         leftCount = ((ExtendedAVLNode*) GetLeft())->GetSubtreeKeyCount();
      }

      if (GetRight()) {
         rightCount = ((ExtendedAVLNode*) GetRight())->GetSubtreeKeyCount();
      }

      subtreeKeyCount = 1 + leftCount + rightCount;
   }

public:
   ExtendedAVLNode(int nodeKey) : AVLNode(nodeKey) {
      subtreeKeyCount = 1;
   }
   
   virtual int GetSubtreeKeyCount() override {
      return subtreeKeyCount;
   }

   // Override to keep subtree counts correct
   virtual void SetLeft(BSTNode* newLeftChild) override {
      AVLNode::SetLeft(newLeftChild);
      UpdateSubtreeKeyCount();
   }

   virtual void SetRight(BSTNode* newRightChild) override {
      AVLNode::SetRight(newRightChild);
      UpdateSubtreeKeyCount();
   }

   // Allow tree to trigger updates upward
   void FixCountUpwards() {
      ExtendedAVLNode* current = this;
      while (current) {
         current->UpdateSubtreeKeyCount();
         current = (ExtendedAVLNode*) current->GetParent();
      }
   }
};

#endif