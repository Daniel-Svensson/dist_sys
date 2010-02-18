#include <OB/CORBA.h>
#include <Lock_impl.h>

using namespace std;

// ----------------------------------------------------------------------
// Lock_impl constructor and destructor
// ----------------------------------------------------------------------

Lock_impl::Lock_impl(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa)
    : orb_(CORBA::ORB::_duplicate(orb)),
      poa_(PortableServer::POA::_duplicate(poa)),
      m_State(NO_TOKEN),
      m_ID(0),
      m_LC(0)
    
{
}

Lock_impl::~Lock_impl() {
	delete objArray;	
}

// ----------------------------------------------------------------------
// Methods necessary for the CORBA framework
// ----------------------------------------------------------------------

PortableServer::POA_ptr Lock_impl::_default_POA()
{
    return PortableServer::POA::_duplicate(poa_);
}

// ----------------------------------------------------------------------
// Methods that can be called from other CORBA objects
// ----------------------------------------------------------------------

/*
	This method is used to request the token from a remote object.
*/
void Lock_impl::request_token(short id, long logical_time) throw(CORBA::SystemException)
{
   cout << "Token was requested by client ";
   cout << id << " at remote logical time " << logical_time << endl;
   
   // TODO: Implement code for handling token requests from remote objects
   m_Requests[id] = logical_time;
   
   scoped_lock lk(status_mtx);
   switch( m_State )
   {
      
      case TOKEN_PRESENT: //Hold it but don't use it, send it
         objArray[id]->acquire_token( token );
         m_State = NO_TOKEN;
         break;
      default:
         //We have alrady updated request
         break;
   };
         
}

/*
  This method is called by a remote object when it wants to hand the token to us.
*/
void Lock_impl::acquire_token(const OB::FixSeq<CORBA::Long, Lock::OBUnique_token_type>& token)
   throw(CORBA::SystemException)
{
   cout << "Token acquired!" << endl;
   // TODO: Implement code for acquiring the token from a remote object
   
   //Copy token
   this->token = token;
   this->token[m_ID] = m_LC; //Update our clock

   scoped_lock lk(status_mtx);
   m_State = TOKEN_PRESENT;
   status_changed.notify_all();
}


/*
	This function is called from any remote object that wants us to print
	some text on the screen (for instance to check if we are alive).
*/
void Lock_impl::print_message(short remote_id) throw (CORBA::SystemException)
{
		cout << "Received a message from client " << remote_id << endl;
}


// ----------------------------------------------------------------------
// Local methods that can be called only from the program that created
// this object
// ----------------------------------------------------------------------

/*
	This method must be called when all clients are started. It finds the references
	of remote objects and puts them into an array. It also initializes all variables
	necesary for the distributed mutual exclusion algorithm to work.
*/
void Lock_impl::initialize(int my_id, int number_of_clients, bool has_token, const char* name)
   throw(CORBA::SystemException)
{
   
   cout << "Initializing " << number_of_clients << " clients..." << endl;
   
   // Initialize object array
   objArray=new Lock_var[number_of_clients];

   // Get the NamingContext
   CORBA::Object_var obj = orb_ -> resolve_initial_references("NameService");
   CosNaming::NamingContext_var nc = CosNaming::NamingContext::_narrow(obj.in());

   for (short i=0; i<number_of_clients; i++)
   {
      // Only search for remote objects
      if (i!=my_id)
      {
         char buff[256];
				
         // The string buff will contain the name of the object to find.
         // For instance "Jakob1".
         sprintf(buff,"%s%d",name,i);

         // Use the CORBA name service to find the object
         cout << "Searching for client: " << buff << endl;
         CosNaming::Name dbName;
         dbName.length(1);
         dbName[0].id = CORBA::string_dup("Lock");
         dbName[0].kind = CORBA::string_dup(buff);
         CORBA::Object_var dbObj = nc -> resolve(dbName);
         
         // Store it into an array containing references to all
         // remote objects
         objArray[i]=Lock::_narrow(dbObj.in());
         
         // Function member_function() of the remote client i
         // can now be accessed by:
         // objArray[i]->member_function();
         objArray[i]->print_message(my_id);
      }
   }

   // The reference corresponding to this, local, object should be null
   // since we are not going to access our own member functions using CORBA
   objArray[my_id]=NULL;
   cout << "All remote objects are located." << endl;
		
   //
   // TODO: Initialization of variables
   
   if (has_token)
   {
      // Set the length of the token. It can then be accessed as an ordinary array.
      // token[i] contains the timestamp of client i, and so on...
      token.length(number_of_clients);
      for (int i=0; i<number_of_clients; i++)
      {
         token[i]=0;		// Accessed as an array of long ints
      }

      m_State = TOKEN_PRESENT;
   }

   m_ID = my_id;
   m_Requests.resize(number_of_clients,0); //Set all requests to 0
   
   // Initialize the rest of the variables here...		
}


/*
	This function is called from the local client whenever it wants to acquire
	the lock.
*/
void Lock_impl::acquire()
{
   cout << "Acquiring lock..." << endl;

   //
   // TODO:
   // Implement code for acquiring the lock. This means requesting the token
   // from all other clients, if we do not already have it.
   
   //Update LC
   ++m_LC;
   cout << "Sending requests. ID = " << m_ID << " LC = " << m_LC << endl;
   //Send request to everybody else
   for(size_t i=0; i < m_Requests.size(); ++i)
   {
      if(  objArray[i] != 0)
      {
         objArray[i]->request_token(m_ID,m_LC);
      }
   }

   cout << "Waiting for response..." << endl;

   //Wait util we have it
   scoped_lock lk(status_mtx);
   while( m_State == NO_TOKEN )
   {
      status_changed.wait(lk);
      cout << "wake" << endl;
   }
   
   m_State = TOKEN_HELD;

    cout << "Lock aquired..." << endl;
}


/**
 * Se if somebody else has requested the token, if so send it to them
 *  othewise return false
 */
bool Lock_impl::SendToken()
{     
   //Check if somebody else requested it
      
   //Check all with higher index
   for(unsigned int i = m_ID + 1; i < m_Requests.size(); ++i)
   {
      if( m_Requests[i] > token[i] )
      {
         objArray[i]->acquire_token( token );
         return true;
      }
   }

   //Check all with lower index
   for(int i = 0; i < m_ID; ++i)
   {
      if( m_Requests[i] > token[i] )
      {
         objArray[i]->acquire_token( token );
         return true;
      }
   }

   return false;
}


/*
	This function is called from the local client whenever it wants to release
	an acquired lock.
*/
void Lock_impl::release()
{
   //
   // TODO:
   // Implement code for releasing the lock.
   // If a remote object wants the token, send it!
   ++m_LC;
   
   cout << "Releasing lock!" << endl;

   scoped_lock lk(status_mtx);
   {
      if( SendToken() )
      {
         m_State = NO_TOKEN;
         cout << "Token sent" << endl;
      }
      else
      {
         m_State = TOKEN_PRESENT;
         cout << "Token not sent" << endl;
      }
   }
   
   cout << "Lock released!" << endl;
}
