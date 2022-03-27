#include <iostream>
#include <stdlib.h>
#include "Poker.hpp"

using namespace std;

int main()
{
	//cout << "Hello world!" << endl;
	DeckOfCards WholeDeck;
	WholeDeck.shuffleDeck();
	//WholeDeck.print();
	PokerHand one(WholeDeck, "Lukas"), two (WholeDeck, "Emilija");
	one.showHand();
	two.setPoints();
	cout << endl << one.findBest() << endl << endl;
	two.showHand();
	one.setPoints();
	cout << endl << two.findBest() << endl << endl;
	if (one.getPoints() > two.getPoints())
	{
		cout << one.getName() << " wins!" << endl;
	}
	else if (one.getPoints() < two.getPoints())
	{
		cout << two.getName() << " wins!" << endl;
	}
	else
	{
		if (one.getHighest() > two.getHighest())
		{
			cout << one.getName() << " wins!" << endl;
		}
		else if (one.getHighest() < two.getHighest())
		{
			cout << two.getName() << " wins!" << endl;
		}
		else cout << "Tie!" << endl;
	}
	return 0;
}
