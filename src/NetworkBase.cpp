#include "NetworkBase.h"
#include <iostream>
#include <stdexcept>
using namespace std;


NetworkBase::NetworkBase(std::string host, std::string port)
	: _socket(io_service)
{
  cerr << "Connecting to " << host << " port " << port << endl;

  tcp::resolver resolver(io_service);
  tcp::resolver::query query(tcp::v4(), host.c_str(), port);
  tcp::resolver::iterator iterator = resolver.resolve(query);

  _socket.connect(*iterator);

  if(!_socket.is_open())
	  throw std::runtime_error("Could not connect");
}


NetworkBase::~NetworkBase(void)
{
	_socket.close();
}


std::string NetworkBase::readLine()
{
   //Get line
   cerr << "Receiving start, " << endl;

   
   std::string result;


	asio::read_until(_socket, b, '\n');

	std::istream is(&b);
	std::getline(is, result);
	     
     

   
   cerr << "Received: \"" << result << "\"" << endl;

   for(int i=0;i < result.length();++i)
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

int NetworkBase::readInt()
{
   std::istringstream ss( readLine() );
   int result = -1;

   ss >> result;
   return result;
}

void NetworkBase::writeLine(const std::string & s)
{
   std::string str(s);

   cerr << "Sending: \"" << str << "\\n\"\n";
   str.append("\n");

   asio::write(_socket, asio::buffer(str));
   
//   fprintf(fsocket,"%s\n",str.c_str());
//   fflush(fsocket);
   cerr << "sent\n";
}

