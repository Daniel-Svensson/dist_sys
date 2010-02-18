
#ifndef LOCK_IMPL_H
#define LOCK_IMPL_H

#include <Lock_skel.h>
#include <OB/CORBA.h>
#include <OB/CosNaming.h>
#include <vector>
#include <boost/thread.hpp>

class Lock_impl : public POA_Lock,
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

   boost::mutex status_mtx;
   typedef boost::mutex::scoped_lock scoped_lock;
   boost::condition status_changed;
private:
   // Declaration of the token (equivalent to an array!)
   OB::FixSeq<CORBA::Long, Lock::OBUnique_token_type> token;

   // Declaration of the array that stores the remote references
   Lock_var* objArray;
   
   //
   // TODO:
   // Declare necessary variables
   enum
   {
      NO_TOKEN,      
      TOKEN_PRESENT,
      TOKEN_HELD
   };

   //One of the above
   int m_State;
   std::vector<CORBA::Long> m_Requests;
   int m_ID;
   int m_LC;
      

   /**
    * Sends the token to another process.
    *
    * return true if the token was sent
    */
   bool SendToken();
public:
   // Constructor
   Lock_impl(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa);
   
   // Destructor
   ~Lock_impl();
   
   // General CORBA methods
   virtual PortableServer::POA_ptr _default_POA();
   
   // Methods available for remote objects
   virtual void print_message(short id) throw (CORBA::SystemException);

   //"Internal" message passing
   // Ask for the token from the lock
   virtual void request_token(short id, long logical_time)
      throw(CORBA::SystemException);
   //Give token to the lock
   virtual void acquire_token(
                    const OB::FixSeq<CORBA::Long, Lock::OBUnique_token_type>&)
      throw(CORBA::SystemException);
   

   // Local methods
   void acquire();
   void release();
   void initialize(int my_id, int number_of_clients, bool has_token, const char* name) throw(CORBA::SystemException);
   
	//
	// TODO:
	// Declare necessary (if any) local methods

};

#endif
