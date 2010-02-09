// **********************************************************************
//
// Copyright (c) 2002
// IONA Technologies, Inc.
// Waltham, MA, USA
//
// All Rights Reserved
//
// **********************************************************************

#ifndef HELLO_IMPL_H
#define HELLO_IMPL_H

#include <Database_skel.h>
#include "Card.h"
#include <vector>

class Database_impl : public POA_Database,
		   public PortableServer::RefCountServantBase
{
    //
    // The ORB
    //
    CORBA::ORB_var orb_;

    //
    // The servants default POA
    //
    PortableServer::POA_var poa_;

   //The cards
   std::vector<Card> m_Cards;
public:

    Database_impl(
	CORBA::ORB_ptr orb,
	PortableServer::POA_ptr poa
    );

//Load the cards
   void LoadCards(const char * const filename);
   
     //
    // IDL:Database/getCardsNumber:1.0
    //
    CORBA::Short getCardsNumber() throw (CORBA::SystemException);

    //
    // IDL:Database/getCardName:1.0
    //
    char* getCardName(CORBA::Short cardNumber) throw (CORBA::SystemException);

    //
    // IDL:Database/getCardFile:1.0
    //
    char* getCardFile(CORBA::Short cardNumber) throw (CORBA::SystemException);

    //
    // IDL:Database/getCardURL:1.0
    //
    char* getCardURL(CORBA::Short cardNumber) throw (CORBA::SystemException);

    //
    // IDL:Database/getCardThumb:1.0
    //
    char* getCardThumb(CORBA::Short cardNumber) throw (CORBA::SystemException);

    //
    // IDL:Database/getCardArea:1.0
    //
    CORBA::Boolean getCardArea(CORBA::Short cardNumber,
                               CORBA::Short_out x,
                               CORBA::Short_out y,
                               CORBA::Short_out width,
                               CORBA::Short_out height)
       throw (CORBA::SystemException);

    virtual PortableServer::POA_ptr
    _default_POA();

   void
Database_impl::shutdown()
      throw(CORBA::SystemException);

};

#endif
