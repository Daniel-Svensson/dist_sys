
#include "CardDatabase.h"
#include "Card.h"
#include "arg.h"

#include <iostream>
#include <string>
#include <stdlib.h>
#include <map>



using namespace std;

int main()
{
   cout << "Content-type: text/html" << "\n\n";

   std::map<string,string> args = get_arguments(getenv("QUERY_STRING"));

   cout << "<HTML><BODY>"                      << endl      
        << "The parameters are: " << endl;


   std::map<string,string>::iterator it = args.begin();
   for(; it != args.end(); ++it)
      cout << it->first << "\t: " << it->second << endl;
   
   cout     << "</BODY></HTML>" << endl;

   

   return 0;
}
