#include "CardDatabase.h"
#include <iostream>
#include <stdexcept>
#include <sstream>

CardDatabase::CardDatabase(const std::string serverName)
	: NetworkBase(serverName,"7000")
{}

CardDatabase::~CardDatabase()
{
}



const std::string GET_CARDINFO = "getCardInfo";

std::auto_ptr<Card> CardDatabase::GetCard(int id)
{
   std::auto_ptr<Card> res(new Card());

   /* Send the command */
   std::ostringstream command;
   command << GET_CARDINFO << " " << id;
   writeLine(command.str());

   res->Name = readLine();      //Name
   res->FileName = readLine();  //Filename
   res->URL = readLine();      //URL
   res->ThumbURL = readLine(); //thumb URL
   //read x, y,w ,h
   res->x = readInt();
   res->y = readInt();
   res->w = readInt();
   res->h = readInt();

   return res;
}

int CardDatabase::GetNumCards()
{
   const std::string GET_NUM_CARDS = "getCardsNumber";
   writeLine(GET_NUM_CARDS);

   return readInt();
}
