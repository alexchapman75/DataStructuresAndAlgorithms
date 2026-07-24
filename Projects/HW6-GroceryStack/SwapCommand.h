#ifndef SWAPCOMMAND_H
#define SWAPCOMMAND_H

#include <string>
#include <vector>
#include "UndoCommand.h"

class SwapCommand : public UndoCommand {
private:
   // TODO: Type your member variable declarations here
   std::vector<std::string>* sourceVector;
   int index1;
   int index2;

public:
   // TODO: Type your constructor code here
   SwapCommand(std::vector<std::string>* vector, int i1, int i2) {
    sourceVector = vector;
    index1 = i1;
    index2 = i2;
   }
   
   void Execute() override {
      // TODO: Type your code here
      if (sourceVector) {
        std::swap((*sourceVector)[index1], (*sourceVector)[index2]);
      }
   }
};

#endif
