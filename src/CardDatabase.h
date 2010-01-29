#ifndef CARD_DATABASE_H
#define CARD_DATABASE_H

#include "Card.h"
#include <memory>
#include "NetworkBase.h"

class CardDatabase : public NetworkBase
{

protected:
public:
   CardDatabase(const std::string serverName = "mir41.ida.liu.se");
   ~CardDatabase();

   int GetNumCards();

   std::auto_ptr<Card> GetCard(int cardNumber);

//   void dump(void);
};


#endif 
