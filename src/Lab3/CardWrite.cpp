#include "CardWrite.h"
#include "Card.h"
#include <iostream>
#include <stdexcept>
using namespace std;

CardWrite::CardWrite()
// : NetworkBase("sen8.ida.liu.se", "9000")
{

}

std::string CardWrite::WriteCard(std::auto_ptr<Card> card, const std::string &msg)
{
   cerr << "Sending card " << card->Name << " to CardWrite server" << endl;

   return std::string("url");  
}
