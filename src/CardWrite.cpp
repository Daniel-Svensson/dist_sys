#include "NetworkBase.h"
#include "CardWrite.h"
#include "Card.h"
#include <iostream>
#include <stdexcept>
using namespace std;

CardWrite::CardWrite()
 : NetworkBase("sen8.ida.liu.se", "9000")
{
  cerr << "Connected" << endl;
}

std::string CardWrite::WriteCard(std::auto_ptr<Card> card, const std::string &msg)
{
   cerr << "Sending card " << card->Name << " to CardWrite server" << endl;

   //Send filiename
   writeLine(card->FileName);
//write destinamtion name
   ostringstream cardname;
   cardname << "das_card_" << card->FileName;
   writeLine(cardname.str());

//Write size
   std::ostringstream coords;
   coords << card->x << " " << card->y << " " << card->w << " " << card->h;
   writeLine(coords.str());
   
//Write message  
  writeLine(msg);   
  writeLine("end-of-message");

  return readLine();  
}
