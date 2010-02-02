
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
   cout << "Content-type: text/html" << "\n\n";

   const char * arguments = getenv("QUERY_STRING");

   cout << "<HTML><BODY>"                      << endl
        << "The parameters are: " << arguments << endl
        << "</BODY></HTML>" << endl;

   

   return 0;
}
