
#include "CardDatabase.h"
#include "Card.h"
#include "arg.h"

#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <map>



using namespace std;

int main()
{
   cout << "Content-type: text/html" << "\n\n";

   std::map<string,string> args = get_arguments(getenv("QUERY_STRING"));

   //Get the id of the image as a string
   istringstream ss(args["id"]);
   int id = -1;
   ss >> id;
   
   cout << "<HTML>\n"
        << "<BODY>\n";

   
   if(id > 0)
   {
      try
      {
         CardDatabase db;
         auto_ptr<Card> card = db.GetCard(id);     
         cout << "<IMG src=\"" << card->URL << "\" />" << endl;         
      }
      catch(std::exception & e)
      {
         cout << e.what() << endl;
      }

      
   cout << "<FORM METHOD=\"GET\" ACTION=\"createcard.cgi?id=" << id << "\">\n"
        << " <TEXTAREA NAME=\"message\" ROWS=6 COLS=60> "
        <<   "Write your message here.."
        << " </TEXTAREA>\n"
        << " <INPUT TYPE=\"submit\" /> \n"
        << "</FORM>\n";
   
   }
   else
      cout << "Du måste ange ett positivet heltal som id" << endl;
      
   
      
   cout     << "</BODY></HTML>" << endl;

    

   return 0;
}
