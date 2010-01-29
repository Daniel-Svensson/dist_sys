#include "CardDatabase.h"
#include <iostream>
#include <stdexcept>
#include <sstream>


using namespace std;
using namespace asio;
using asio::ip::tcp;

CardDatabase::CardDatabase(const std::string serverName)
   : _socket(io_service) , 
    net_stream(serverName,"7000")
{
  int port = 7000;

  cerr << "Connecting to " << serverName << " port " << port << endl;

  tcp::resolver resolver(io_service);
  tcp::resolver::query query(tcp::v4(), serverName.c_str(), "7000");
  tcp::resolver::iterator iterator = resolver.resolve(query);

  _socket.connect(*iterator);
  if(!_socket.is_open())
	  throw std::runtime_error("can't connect");

  if(!net_stream.good())
  		throw std::runtime_error("can't connect");

}

CardDatabase::~CardDatabase()
{
   _socket.close();
}



std::string CardDatabase::readLine()
{
	std::string result;

   //Get line
   cerr << "Receiving start, " << endl;

   /*static asio::streambuf b;
   asio::read_until(_socket, b, '\n');
   std::istream is(&b);
   std::getline(is, result);
   */

   getline(net_stream, result);
   
   cerr << "Received: \"" << result << "\"" << endl;

   for(size_t i=0;i < result.length();++i)
   {
      if(result[i] == '\0')
         result.erase(i,1);
   }

   if( result.find("ERROR:") != std::string::npos)
   {      
      throw std::runtime_error(result);
   }

   return result;
}

int CardDatabase::readInt()
{
   std::istringstream ss( readLine() );
   int result = -1;
   ss >> result;
   return result;
}

void CardDatabase::writeLine(const std::string & s)
{
   std::string str(s);

   cerr << "sending \"" << s << "\\n\"\n";
   net_stream << s << "\n";

//   fprintf(fsocket,"%s\n",str.c_str());
//   fflush(fsocket);
   cerr << "sent\n";
}


const std::string GET_CARDINFO = "getCardInfo";

std::auto_ptr<Card> CardDatabase::GetCard(int id)
{
   std::auto_ptr<Card> res(new Card());

   /* Send the command */
   std::ostringstream command;
   command << GET_CARDINFO << " " << id;
   writeLine(command.str());

   res->Name = readLine();      //Name
   res->FileName = readLine();  //Filename
   res->URL = readLine();      //URL
   res->ThumbURL = readLine(); //thumb URL
   //read x, y,w ,h
   res->x = readInt();
   res->y = readInt();
   res->w = readInt();
   res->h = readInt();

   return res;
}

int CardDatabase::GetNumCards()
{
   const std::string GET_NUM_CARDS = "getCardsNumber";
   writeLine(GET_NUM_CARDS);

   return readInt();
}
