#include <OB/CORBA.h>
#include <OB/CosNaming.h> 

#include "Database_impl.h"
#include "Database_skel.h"
#include "Database.h"



#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <map>


using namespace std;

int run(CORBA::ORB_var orb)
{
   //
   // Resolve Root POA
   //
   CORBA::Object_var poaObj = orb -> resolve_initial_references("RootPOA");
   PortableServer::POA_var rootPOA = PortableServer::POA::_narrow(poaObj);
    
   //
   // Get a reference to the POA manager
   //
   PortableServer::POAManager_var manager = rootPOA -> the_POAManager();
    
   //
   // Create implementation object
    //
   Database_impl* databaseImpl = new Database_impl(orb, rootPOA);
   PortableServer::ServantBase_var servant = databaseImpl;
   Database_var database = databaseImpl -> _this();
   databaseImpl->LoadCards("cards.database");

 
    //Add to name service
   //Get name service ref
   CORBA::Object_var obj = orb -> resolve_initial_references("NameService");
   CosNaming::NamingContext_var nc = CosNaming::NamingContext::_narrow(obj.in());
   //Bind
   CosNaming::Name dbName;
   dbName.length(1);
   dbName[0].id = CORBA::string_dup("Database");
   dbName[0].kind = CORBA::string_dup("dansv693");

   try
   {
      nc -> bind(dbName, database.in());
   }
   catch(...)
   {
      nc->rebind(dbName, database.in());
   }
   
   
    //
    // Run implementation
    //
    manager -> activate();
    orb -> run();

    return EXIT_SUCCESS;
}

/*   CORBA::Object_var obj = orb -> resolve_initial_references("NameService");
   CosNaming::NamingContext_var nc = CosNaming::NamingContext::_narrow(obj.in());
   
   CosNaming::Name dbName;
   dbName.length(1);
   dbName[0].id = CORBA::string_dup("Database");
   dbName[0].kind = CORBA::string_dup("trapo");
   CORBA::Object_var dbObj = nc -> resolve(dbName);
   Database_var db = Database::_narrow(dbObj.in());


   CosNaming::Name cwName;
   cwName.length(1);
   cwName[0].id = CORBA::string_dup("Writer");
   cwName[0].kind = CORBA::string_dup("trapo");
   CORBA::Object_var cwObj = nc -> resolve(cwName);
   Writer_var cw = Writer::_narrow(cwObj.in());
   
   
   //fetch all cards
   while(true)
   {
      system("clear");
      cout 
           << "Select an option: " << endl
           << "1: List images" << endl
           << "2: View image information" << endl
           << "3: Write postcard" << endl
           << "0: Exit" << endl;
      int option = 0;
      cin >> option;
      cin.ignore();
      cout <<  endl;

      int cardsNum = db->getCardsNumber(); //Get total number of cards
      switch (option)
      {
         case 1:
         {
            //List all
            cout << "There is a total of " << cardsNum << " cards." << endl;
            cout << "Index" << setw(40) << left << "Name" << "Dimensions" << endl;
            for (int i = 0; i < cardsNum; i++)
            {
               short x,y,w,h;
               db->getCardArea(i,x,y,w,h);               
               cout << setw(3) << i <<": "
                    << setw(40) << db->getCardName(i)  << w << "x" << h << endl;

               if( i % 20 == 19)
               {
                  cout << "Press enter to continue" << endl;
                  cin.get();
               }
            }
           
         }break; //case 1

         case 2:
         {
            cout << "Enter a postcard [0," << cardsNum-1 << "]: ";
            int card = 0;
            cin >> card;
            cin.ignore();

            short x,y,w,h;
            db->getCardArea(card,x,y,w,h);
               
            cout << "Name : " << db->getCardName(card) << endl
                 << "File : " << db->getCardFile(card) << endl
                 << "URL  : " << db->getCardURL(card) << endl
                 << "Thumb: " << db->getCardThumb(card) << endl
                 << "Area : x=" << x << " y=" << y  << " w="  << w << " h=" << h << endl;
         }break; //case 2

         case 3:
         {
            cout << "Enter a postcard [0," << cardsNum-1 << "]: ";
            int card = 0;
            cin >> card;
            cin.ignore(255,'\n');

            cout << "Enter a message (end with a '.' on a single line) " << endl;
            std::string message,line;

            do
            {
               getline(cin,line);

               if( line == "." )
                  break;

               line.append("\n");
               message += line;
            }while(!line.empty());


            std::string name("temp_00000.jpg");
            cout << "Enter a output filename:";
            cin >> name;
           
            short x,y,w,h;
            db->getCardArea(card,x,y,w,h);

            cw->setCard( db->getCardFile(card), x, y, w, h );
            cw->setMessage( message.c_str() );            
            std::string url = cw-> writeCard(name.c_str());

            cout << "The card is now availible at \"" << url << "\"" << endl;

            std::string command("firefox ");
            command.append(url);
            system( command.c_str() );
         }break; //case 3

         default:
            cout << "Godbye" << endl;
            return 0;
      }

       cout << "Press enter to continue" << endl;
       cin.get();
   }//while
   

  return 0;
}
*/

int main(int argc, char* argv[])
{
    int status = EXIT_SUCCESS;
    CORBA::ORB_var orb;

    try
    {
	char *argv2[] = { argv[0],
			  "-ORBInitRef",
			 "NameService=corbaloc::styr3:10000/NameService",
			NULL };
	int argc2 = 3;
	orb = CORBA::ORB_init(argc2, argv2);
	status = run(orb);
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

