#ifndef CARD_WRITE_H
#define CARD_WRITE_H

#include "Card.h"
#include "NetworkBase.h"
#include <string>

class CardWrite : public NetworkBase
{
public:
  CardWrite();

   //Write a ccard
   // return url of written card
   std::string WriteCard(std::auto_ptr<Card> card, const std::string & message);
};

#endif 
