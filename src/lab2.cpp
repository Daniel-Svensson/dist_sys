#include <iostream>

#include "CardDatabase.h"
#include "Card.h"

using namespace std;

#include <iostream> 
#include <string> 
#include <asio.hpp> 
 
int webb(int argc, char* argv[]) { 
    std::string host = argc > 1 ? argv[1] : "mir41.ida.liu.se"; 
    asio::ip::tcp::iostream stream(host, "7000"); 
    if (stream) { 
//        stream << "getCardsNumber\n" << flush;
//		stream << "getCardsNumber\n" << flush;
		stream << "getCardInfo 1\n" << flush;
		Sleep(100);
		stream << "exit\n"; 
        std::string line; 
		Sleep(100);
		while(std::getline(stream, line)) 
		{
            std::cout << line << std::endl; 
			if(line.find('\0') != string::npos)
				cerr << "hitta null";
		}

    } 
    return 0; 
}

int main(int argc, char* argv[]) 
{
	webb(argc,argv);

   CardDatabase db;


   int num = -1;
   do
   {

      cout << "There are " << db.GetNumCards() << " numbers of cards" << endl;
      cout << "Select a card: ";
      cin >> num;

      if( num == -1)
         break;
     
      auto_ptr<Card> card = db.GetCard(num);      
   }while(num != -1);
             
   
   return 0;
}
