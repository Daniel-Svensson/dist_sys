#ifndef CARD_DATABASE_H
#define CARD_DATABASE_H

#include "Card.h"
#include <memory>

class CardDatabase
{
   //Socket
   int sockfd;
   FILE *fsocket;

   CardDatabase(const CardDatabase&);
   CardDatabase &operator=(const CardDatabase&);

protected:
   std::string readLine();
   void writeLine(const std::string & str);
public:
   CardDatabase(const std::string serverName = "mir41.ida.liu.se");
   ~CardDatabase();
//   int getCardsNumber(void);

   std::auto_ptr<Card> GetCard(int cardNumber);

   int GetNumCards();
//   void dump(void);
};


#endif 
