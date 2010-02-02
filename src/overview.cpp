
#include "CardDatabase.h"
#include "Card.h"

#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <map>



using namespace std;

int main()
{
  std::auto_ptr<Card> res;
  CardDatabase db;
  int cardsNum; //Store total number of cards on server

  cout << "Content-type: text/html" << "\n\n";

  cardsNum = db.GetNumCards(); //Get total number of cards
  
  const char * arguments = getenv("QUERY_STRING");
   
  cout << "<HTML><BODY>"                      << endl
       << "The parameters are: " << arguments << endl
       << ""                                  << endl;

  //fetch all cards
  for (int i = 1; i <= cardsNum; i++)
    {
      res = db.GetCard(i);
      

      cout << "<DIV style=\"border: red 1px dashed; margin: 1em; min-height: 150px; float: left;\"><A HREF=\"viewimage.cgi?id=" << i << "\">"
	"<IMG SRC=\"" << res->ThumbURL << "\" ALT=\"" << res->Name << "\"</A><BR><B>" << res->Name << "</B></DIV>" << endl;
      
    }



  cout   << "</BODY></HTML>" << endl;

   

  return 0;
}
