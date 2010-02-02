
#include "arg.h"
#include <string.h>
#include <stdlib.h>
#include <cctype>
#include <sstream>
#include <iostream>

using namespace std;


void decode(std::string & arg)
{
   size_t pos = 0;

   //convert + to spaces
   while( (pos = arg.find("+"))  != string::npos)
   {
      arg.at(pos) = ' ';
   }

   pos = 0;
   while( (pos = arg.find("%"))  != string::npos)
   {
      //kolla att det är tre tecken 
      if( pos + 2 < arg.size()
          && isxdigit(arg.at(pos+1))
          && isxdigit(arg.at(pos+2)))
      {
         stringstream ss;
         int ascii;
         ss << arg[pos+1] << arg[pos+2];

         cerr << "decoding: " << ss.str() << endl;
         
         ss >> hex >> ascii;
         
         cerr << "res: " << ascii << endl;

         //change first char, and erase the rest
         arg[pos] = (char)ascii;
         arg.erase(pos+1,2); 
      }
   }
}

std::map<std::string,std::string> get_arguments(const char * querystring)
{
   std::map<string,string> result;

   if(querystring)
   {
      istringstream ss(querystring);
      std::string argument,value;
      
      while( getline(ss,argument,'=') )
      {
         getline(ss,value,'&');

         decode(argument);
         decode(value);
         
         if(!argument.empty())
            result[argument] = value;
      }
      
   }
   
   return result;
}
