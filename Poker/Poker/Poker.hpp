#include <iostream>
#include <vector>

using namespace std;

class Card //What a card is
{
public:
	Card(int type, int value, int color);
	Card();
	void setType(int type);
	void setValue(int value);
	void setColor(int color);
	int getType();
	int getValue();
	int getColor();
	string toString();

private:
	int type;
	int value;
	int color;
	const static string Types[4];
	const static string Points[13];
	const static string Colors[2];
};


class DeckOfCards //The whole deck of cards
{
public:
	DeckOfCards();
	void shuffleDeck();
	void print();
	bool moreCards();
	Card dealCard();
	static const int sizeOfDeck;
	vector<Card> deck;
	Card DealtCard;
};




class PokerHand //The given 5 cards per player
{
private:
	vector<Card> hand;
	string name;
	int points=1;
	int highestCard;
	static const string combinations[11];
public: 
	PokerHand(DeckOfCards& deck, string name);
	void setName(string name);
	void dealHand(DeckOfCards &deck);
	string findBest();
	int getHighest();
	int getPoints();
	void showHand();
	string getName();
	void setPoints();
	bool highCard();
	bool onePair();
	bool twoPair();
	bool threeOfAKind();
	bool straight();
	bool flush();
	bool fourOfAKind();
	bool straightFlush();
	bool royalFlush();
};