
#include "CardDatabase.h"
#include "CardWrite.h"
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
         CardWrite cw;
         auto_ptr<Card> card = db.GetCard(id);

         std::string url = cw.WriteCard( card, args["message"] );
         cout << "<IMG src=\"" << url << "\" />" << "<BR />\n";
         cout << "<A HREF=\"" << url << "\">"
              <<  "Use the address: \"" << url << "\" to view the card </A>\n";

      }
      catch(std::exception & e)
      {
         cout << e.what() << endl;
      }

   }
   else
      cout << "Du måste ange ett positivet heltal som id" << endl;
      
   
      
   cout     << "</BODY></HTML>" << endl;

    

   return 0;
}
