#ifndef SWAPCOMMAND_H
#define SWAPCOMMAND_H

#include <string>
#include <vector>
#include "UndoCommand.h"

class SwapCommand : public UndoCommand {
private:

   std::vector<std::string>* sourceVector;
   int index1;
   int index2;

public:

   SwapCommand(std::vector<std::string>* vector, int i1, int i2) {
    sourceVector = vector;
    index1 = i1;
    index2 = i2;
   }
   
   void Execute() override {

      if (sourceVector) {
        std::swap((*sourceVector)[index1], (*sourceVector)[index2]);
      }
   }
};

#endif
