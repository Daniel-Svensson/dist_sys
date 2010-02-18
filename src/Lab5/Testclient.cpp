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
#include <OB/CosNaming.h>
#include <OB/BootManager.h>

#include <Lock_impl.h>

#include <stdlib.h>
#include <string>

#ifdef HAVE_STD_IOSTREAM
using namespace std;
#endif

int id;
int number_of_clients;
bool has_token;
string username;

/*
	Extract command line parameters
*/
string getParam(int argc, char** args, string arg) {
    for (int i=0; i<argc; i++) {
 		string argi(args[i]);
    	if (!argi.compare("-"+arg) || !argi.compare("--"+arg)) {
    		string result(args[i+1]);
    		return result;
    	}
    }
    return NULL;
}

int run(CORBA::ORB_ptr orb, int /* argc */, char* argv[])
{
    CORBA::Object_var obj;

    // Get the NamingContext
    CosNaming::NamingContext_var nc;
    try
    {
		CORBA::Object_var obj = orb -> resolve_initial_references("NameService");
		nc = CosNaming::NamingContext::_narrow(obj.in());
    }
    catch(const CORBA::BAD_PARAM&) {}

    // Resolve Root POA
    CORBA::Object_var poaObj = orb -> resolve_initial_references("RootPOA");
    PortableServer::POA_var rootPOA = PortableServer::POA::_narrow(poaObj);
    
    // Get a reference to the POA manager
    PortableServer::POAManager_var manager = rootPOA -> the_POAManager();

    // Create implementation object
    Lock_impl* lockImpl = new Lock_impl(orb, rootPOA);
    PortableServer::ServantBase_var servant = lockImpl;
    Lock_var lock = lockImpl -> _this();
	
    // Resolve the BootManager and register the server
    CORBA::Object_var bootObj = orb -> resolve_initial_references("BootManager");
    OB::BootManager_var bootManager = OB::BootManager::_narrow(bootObj);	
    PortableServer::ObjectId_var oid =
    PortableServer::string_to_ObjectId("Lock");
    bootManager -> add_binding(oid, lock);
	
	// Name the local lock object
	char buff[256];
	sprintf(buff,"%s%d",username.c_str(),id);
	cout << "Registering client: " << buff << endl; 
	
	// Bind the local lock object
	CosNaming::Name lockName;
	lockName.length(1);
	lockName[0].id = CORBA::string_dup("Lock");
	lockName[0].kind = CORBA::string_dup(buff);
	nc -> rebind(lockName, lock.in());

	// Activate POA manager
    manager -> activate();

	// Wait until all remote objects are activated.
	cout << "Wait until all clients show this message, and press enter to initialize" << endl;
    char message[2048];
    gets(message);

    // Now all remote clients should be available. Let's find them!
    lockImpl->initialize(id, number_of_clients, has_token, username.c_str());

    cout << "Type \"lock\" to acquire the lock, and \"release\" to release it again." << endl;
    cout << "Type \"exit\" to exit." << endl;
    
    // The main loop of the test client
    while(true) {

	   	// Wait until the user wants to acquire the lock
	    do {
	    	cout << "unlocked> ";
			gets(message);
			if (!strcmp(message,"release")) cout << "The lock must be acquired before it can be released" << endl;
			if (!strcmp(message,"exit")) return EXIT_SUCCESS;
		} while (strcmp(message,"lock"));
	    
		// acquire the lock
		lockImpl->acquire();
	
	   	// Wait until the user wants to release the lock
	    do {
	    	cout << "LOCKED> ";
			gets(message);
			if (!strcmp(message,"lock")) cout << "The lock is already acquired!" << endl;
			if (!strcmp(message,"exit")) return EXIT_SUCCESS;
		} while (strcmp(message,"release"));
	
		// Release the lock
		lockImpl->release();
	}

	// Exit
    return EXIT_SUCCESS;
}

int
main(int argc, char* argv[], char*[])
{
	if (argc<11) {
		cerr << "Error: not enough parameters" << endl;
		return EXIT_FAILURE;		
	}	
	
	// Extract the -username parameter
	username=getParam(argc, argv, "username");

	// Extract the -id parameter
	id=atoi(getParam(argc, argv, "id").c_str());

	// Extract the -n parameter
	number_of_clients=atoi(getParam(argc, argv, "n").c_str());

	// Extract the -token parameters
	if (!getParam(argc, argv, "token").compare("true"))
			has_token=true;
	else has_token=false;

	// Start the CORBA framework
	int status = EXIT_SUCCESS;
	CORBA::ORB_var orb;
	try
	{
		orb = CORBA::ORB_init(argc, argv, "Lock-Client");
		status = run(orb, argc, argv);
	}
	catch(const CORBA::Exception& ex)
	{
		cerr << ex << endl;
		status = EXIT_FAILURE;
	}

	if(!CORBA::is_nil(orb))
	{
		try
		{
			orb -> destroy();
		}
		catch(const CORBA::Exception& ex)
		{
			cerr << ex << endl;
			status = EXIT_FAILURE;
		}
    }

	return status;
}
