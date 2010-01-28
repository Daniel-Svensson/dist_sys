#include "CardDatabase.h"
#include <iostream>
#include <sstream>

using namespace std;

#include <memory.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>

CardDatabase::CardDatabase(const std::string serverName)
   : sockfd(0), fsocket(0)
{
  struct sockaddr_in serv_addr;
  struct hostent *host_ptr;
  int port = 7000;
 
  /* get the address of the host */
  if((host_ptr = gethostbyname(serverName.c_str())) == NULL) {
     perror("gethostbyname error");
     exit(1);
  }
  
  if(host_ptr->h_addrtype !=  AF_INET) {
     perror("unknown address type");
     exit(1);
  }
  
  memset((char *) &serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = 
     ((struct in_addr *)host_ptr->h_addr_list[0])->s_addr;
  serv_addr.sin_port = htons(port);
  

  /* open a TCP socket */
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
     perror("can't open stream socket");
     exit(1);
  }

  /* connect to the server */    
  if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
     perror("can't connect to server");
     exit(1);
  }

  fsocket = fdopen(sockfd,"rw+");
  
}

CardDatabase::~CardDatabase()
{
   fclose(fsocket);
   close(sockfd);
}



std::string CardDatabase::readLine()
{
   char buffer[512];
   int len = 0;

   //Get line
   fgets( buffer, sizeof(buffer) , fsocket );
   buffer[len] = 0;

   cerr << "Received: " << buffer;
   return std::string(buffer);
}

void CardDatabase::writeLine(const std::string & str)
{
   cerr << "Sending: " << str << "\\n\n";   
   fprintf(fsocket, "%s\n",str.c_str());
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
   fscanf(fsocket,"%d%d%d%d", res->x, res->y, res->w , res->h );

   return res;
}

int CardDatabase::GetNumCards()
{
   const std::string GET_NUM_CARDS = "getCardsNumber";
   writeLine(GET_NUM_CARDS);

   int nums = 42;
   fscanf(fsocket,"%d%d%d%d", nums );

   return nums;
}
