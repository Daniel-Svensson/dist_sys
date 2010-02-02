#include "CardDatabase.h"
#include <iostream>
#include <stdexcept>
#include <sstream>

CardDatabase::CardDatabase()
//	: NetworkBase(serverName,"7000")
{}

CardDatabase::~CardDatabase()
{
}



std::auto_ptr<Card> CardDatabase::GetCard(int id)
{
   std::auto_ptr<Card> res(new Card());


   
   return res;
}

int CardDatabase::GetNumCards()
{

   
   return 0;
}
