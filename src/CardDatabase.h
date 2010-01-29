#ifndef CARD_DATABASE_H
#define CARD_DATABASE_H

#include <asio.hpp>
#include "Card.h"
#include <memory>

using asio::ip::tcp;


class CardDatabase
{
   //Socket
   asio::io_service io_service;
   tcp::socket _socket;
   asio::ip::tcp::iostream net_stream; 
   
   CardDatabase(const CardDatabase&);
   CardDatabase &operator=(const CardDatabase&);

protected:
   int readInt();
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
