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

void CardWrite::SendCard(std::auto_ptr<Card> card)
{
  int count = 1;
  std::string msg;
  std::ostringstream coords;
  coords << card->x << " " << card->y << " " << card->w << " " << card->h;
  cerr << "Sending card " << card->Name << " to CardWrite server" << endl;
  writeLine(card->FileName);
  writeLine("Test-001.jpg");
  writeLine(coords.str());

  do{
    cerr << "Type a message a line, end with end-of-message: " << endl;
    std::getline(std::cin, msg);
    writeLine(msg);
 
    
  }while(msg != "end-of-message");

  msg = readLine();
  
}
