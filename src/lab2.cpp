#include <iostream>

#include "CardDatabase.h"
#include "Card.h"

using namespace std;

int main()
{
	CardDatabase db;


	int num = -1;
	do
	{
		try
		{
			cout << "There are " << db.GetNumCards() << " numbers of cards" << endl;
			cout << "Select a card: ";
			cin >> num;

			if( num == -1)
				break;


			auto_ptr<Card> card = db.GetCard(num);      
		}
		catch(std::exception & ex)
		{
			cerr << ex.what() << endl;
		}
	}while(num != -1);

	cin.get();
	return 0;
}
