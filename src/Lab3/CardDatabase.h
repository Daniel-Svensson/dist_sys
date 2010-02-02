#ifndef CARD_DATABASE_H
#define CARD_DATABASE_H

#include "Card.h"
#include <memory>

class CardDatabase
{

protected:
public:
   CardDatabase();
   ~CardDatabase();

   int GetNumCards();

   std::auto_ptr<Card> GetCard(int cardNumber);

//   void dump(void);
};


#endif 
