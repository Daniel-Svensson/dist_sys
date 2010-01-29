#include <iostream>

#include "CardDatabase.h"
#include "Card.h"

using namespace std;

int main()
{
	CardDatabase db;


	int num = -1;
	try
	{

		do
		{			int nums = db.GetNumCards();
		cout << "There are " << nums << " numbers of cards" << endl;
		cout << "Select a card: ";
		cin >> num;

		if( num == -1)
			break;


		auto_ptr<Card> card = db.GetCard(num);      
		}while(num != -1);
	}
	catch(std::exception & ex)
	{
		cerr << ex.what() << endl;
	}

	cin.get();
	return 0;
}
