#ifndef NETWORK_BASE
#define NETWORK_BASE

#include <string>
#include <asio.hpp>
using asio::ip::tcp;

class NetworkBase : public asio::noncopyable
{
protected:
	//Sockets
   asio::io_service io_service;
   tcp::socket _socket;
   asio::streambuf b;

   int readInt();
   std::string readLine();
   void writeLine(const std::string & str);

public:
	NetworkBase(std::string host, std::string port);
	~NetworkBase(void);
};

#endif 

