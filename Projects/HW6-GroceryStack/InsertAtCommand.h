#ifndef INSERTATCOMMAND_H
#define INSERTATCOMMAND_H

#include <string>
#include <vector>
#include "UndoCommand.h"

class InsertAtCommand : public UndoCommand {
private:
   // TODO: Type your member variable declarations here
   std::vector<std::string>* sourceVector;
   std::string item;
   int index;

public:
   // TODO: Type your constructor code here
   InsertAtCommand(std::vector<std::string>* vector,
                     std::string itemToInsert, int insertIndex) 
    {
        sourceVector = vector;
        item = itemToInsert;
        index = insertIndex;
    }
    
   void Execute() override {
      // TODO: Type your code here
      if(sourceVector) {
        sourceVector->insert(sourceVector->begin() + index, item);
      }
   }
};

#endif
