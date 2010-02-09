// **********************************************************************
//
// Copyright (c) 2002
// IONA Technologies, Inc.
// Waltham, MA, USA
//
// All Rights Reserved
//
// **********************************************************************

#include <OB/CORBA.h>

#include <Database_impl.h>

#include <fstream>
#include <sstream>


#ifdef HAVE_STD_IOSTREAM
using namespace std;
#endif

// ----------------------------------------------------------------------
// Database_impl constructor
// ----------------------------------------------------------------------

Database_impl::Database_impl(
    CORBA::ORB_ptr orb,
    PortableServer::POA_ptr poa
)
    : orb_(CORBA::ORB::_duplicate(orb)),
      poa_(PortableServer::POA::_duplicate(poa))
{
}

// ----------------------------------------------------------------------
// Database_impl public member implementation
// ----------------------------------------------------------------------

//Load the cards
void Database_impl::LoadCards(const char * const filename)
{
   ifstream fin(filename);
   if(!fin.is_open())
      throw "FEEL";

   string temp;
   do
   {
      while(fin.peek() == '#')
         fin.ignore(65000,'\n');

      Card card;
      getline(fin,card.Name,',');
      getline(fin,card.FileName,',');
      getline(fin,card.ThumbURL,',');

      card.URL = std::string("http://www.ida.liu.se/~trapo/TDDB37/cards/")
         + card.FileName;
      card.ThumbURL =
         std::string("http://www.ida.liu.se/~trapo/TDDB37/cards/thumbs/")
         + card.ThumbURL;
      
      fin >> card.x;
      fin.ignore(6500,',');
      fin >> card.y;
      fin.ignore(6500,',');
      fin >> card.h;
      fin.ignore(6500,',');
      fin >> card.w;
      fin.ignore(6500,'\n');

      if(fin.eof())
         break;

      m_Cards.push_back(card);
   }while(fin.good());        
         
}

void
Database_impl::shutdown()
    throw(CORBA::SystemException)
{
    orb_ -> shutdown(false);
}

PortableServer::POA_ptr
Database_impl::_default_POA()
{
    return PortableServer::POA::_duplicate(poa_);
}


//
// IDL:Database/getCardsNumber:1.0
//
CORBA::Short Database_impl::getCardsNumber()
   throw (CORBA::SystemException)
{
   return m_Cards.size();
}

//
// IDL:Database/getCardName:1.0
//
char* Database_impl::getCardName(CORBA::Short cardNumber)
   throw (CORBA::SystemException)
{
   if( (unsigned int)cardNumber > m_Cards.size() )
      throw CORBA::BAD_PARAM("Invalid card number");
   
   return CORBA::string_dup(m_Cards.at(cardNumber).Name.c_str());
}

//
// IDL:Database/getCardFile:1.0
//
char* Database_impl::getCardFile(CORBA::Short cardNumber)
   throw (CORBA::SystemException)
{
   if( (unsigned int)cardNumber > m_Cards.size() )   
      throw CORBA::BAD_PARAM("Invalid card number");
   
   return CORBA::string_dup(m_Cards.at(cardNumber).FileName.c_str());
   
}

//
// IDL:Database/getCardURL:1.0
//
char* Database_impl::getCardURL(CORBA::Short cardNumber)
   throw (CORBA::SystemException)
{
   if( (unsigned int)cardNumber > m_Cards.size() )
      throw CORBA::BAD_PARAM("Invalid card number");
   
   return CORBA::string_dup(m_Cards.at(cardNumber).URL.c_str());
}

//
// IDL:Database/getCardThumb:1.0
//
char* Database_impl::getCardThumb(CORBA::Short cardNumber)
    throw (CORBA::SystemException)
{
   if( (unsigned int)cardNumber > m_Cards.size() )
      throw CORBA::BAD_PARAM("Invalid card number");
   
   return CORBA::string_dup(m_Cards.at(cardNumber).ThumbURL.c_str());
}

//
// IDL:Database/getCardArea:1.0
//
CORBA::Boolean Database_impl::getCardArea(CORBA::Short cardNumber,
                                          CORBA::Short_out x,
                                          CORBA::Short_out y,
                                          CORBA::Short_out width,
                                          CORBA::Short_out height)
   throw (CORBA::SystemException)
{
   if( (unsigned int)cardNumber > m_Cards.size() )
      throw CORBA::BAD_PARAM("Invalid card number");

   Card & card = m_Cards.at(cardNumber);
   x = card.x;
   y = card.y;
   width = card.w;
   height = card.h;
      
   return true;
}
