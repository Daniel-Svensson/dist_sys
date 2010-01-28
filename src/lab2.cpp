#include <iostream>

#include "CardDatabase.h"
#include "Card.h"

using namespace std;

int main()
{
   CardDatabase db;

 

   int num = -1;
   do
   {

      cout << "There is " << db.GetNumCards() << "numbers of cards" << endl;
      cout << "Select a card: ";
      cin >> num;

      auto_ptr<Card> card = db.GetCard(num);      
   }while(num != -1);
             
   
   return 0;
}
