#ifndef CARD_WRITE_H
#define CARD_WRITE_H

#include "Card.h"
#include "NetworkBase.h"
#include <string>
#include <asio.hpp>

class CardWrite : public NetworkBase
{
public:
  CardWrite();
  void SendCard(std::auto_ptr<Card> card);
};

#endif 
