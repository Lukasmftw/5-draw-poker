#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include "Poker.hpp"
#include <assert.h>
#include <algorithm>

#define DEBUG assert(false)

using namespace std;

const string Card::Types[4] = { "Diamonds", "Hearts", "Spades", "Clubs"};
const string Card::Points[13] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
const string Card::Colors[2] = { "Red", "Black" };
const string PokerHand::combinations[11] = {"ERROR CARD COMBINATION", "High card", "Pair", "Two pair", "Three of a kind", "Straight", "Flush", "Full house", "Four of a kind", "Straight Flush", "Royal flush" };
const int DeckOfCards::sizeOfDeck = 52;

Card::Card(int type, int value, int color) { setType(type); setValue(value); setColor(color); }
Card::Card()                               { setType(0);    setValue(0);     setColor(0);     }

void Card::setType(int type)       { this->type = type;           }
void Card::setValue(int value)     { this->value = value;         }
void Card::setColor(int color)     { this->color = color;         }
int Card::getType()                { return type;                 }
int Card::getValue()               { return value;                }
int Card::getColor()               { return color;                }
string PokerHand::getName()        { return name;                 }
int PokerHand::getHighest()        { return highestCard;          }
int PokerHand::getPoints()         { return points;               }
string PokerHand::findBest()       { return combinations[points]; }

string Card::toString()
{
	stringstream ss;
	ss << setw(5) << left << Points[value] << " Of " << setw(10) << Types[type] << setw(10);
	return ss.str();
}

DeckOfCards::DeckOfCards()
{
	int k = 0;
	for (int i= 0; i < 4; i++)
	{
		if (i > 1)
			k = 1;
		for (int j=0; j<13; j++)
			deck.push_back(Card(i, j, k));
	}
}

void DeckOfCards::shuffleDeck()
{
	srand(time(0));
	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < deck.size(); i++)
		{
			swap(deck[i], deck[(rand() % 52 + 1)-1]);
		}
	}
	
}

void DeckOfCards::print()
{
	for (int i = 0; i < deck.size(); i++)
	{
		cout << deck[i].toString() << endl;
	}
}

bool DeckOfCards::moreCards()
{
	if (deck.size() != 0)
	{
		return true;
	}
	return false;
}

Card DeckOfCards::dealCard()
{
	Card DealtCard = deck[0];
	deck.erase(deck.begin());
	return DealtCard;
}

PokerHand::PokerHand(DeckOfCards& deck, string name)
{
	dealHand(deck);
	setName(name);
}

void PokerHand::setName(string name)
{
	this->name = name;
}

void PokerHand::dealHand(DeckOfCards &deck)
{
	if (deck.moreCards() == true)
	{
		for (int i = 0; i < 5; i++)
		{
			hand.push_back(deck.dealCard());
		}
	}
	else
	{
		cout << "Deck empty!" << endl;
		DEBUG;
	}
}

void PokerHand::showHand()
{
	cout << name << " has been dealt:" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << hand[i].toString() << endl;
	}
}

void PokerHand::setPoints()
{
	if (royalFlush())         { points = 10; }
	else if (straightFlush()) { points = 9;  }
	else if (fourOfAKind())   { points = 8;  }
	else if (flush())         { points = 6;  }
	else if (straight())      { points = 5;  }
	else if (threeOfAKind())  { points = 4;  } 
	else if (twoPair())       { points = 3;  }
	else if (onePair())       { points = 2;  }
	else if (highCard())      { points = 1;  }
}

bool PokerHand::highCard()
{
	highestCard = 0;
	for (int i = 0; i < 5; i++)
	{
		if (hand[i].getValue() > highestCard)
		{
			highestCard = hand[i].getValue();
		}
	}
	return true;
}

bool PokerHand::onePair()
{
	highestCard = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = i + 1; j < 5; j++)
		{
			if (hand[i].getValue() == hand[j].getValue()) 
			{
				highestCard = hand[i].getValue(); 
				return true;
			}
		}
	}
	return false;
}

bool PokerHand::twoPair()
{
	highestCard = 0;
	int counter = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = i + 1; j < 5; j++)
		{
			if (hand[i].getValue() == hand[j].getValue())
			{
				counter++;
				highestCard = hand[i].getValue();
				if (counter == 2)
				{
					if (hand[i].getValue() > highestCard)
					{
						highestCard = hand[i].getValue();
					}
					return true;
					break;
				}
			}
		}
	}
	return false;
}

bool PokerHand::threeOfAKind()
{
	highestCard = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = i + 1; j < 4; j++)
		{
			for (int k = j + 1; k < 5; k++)
			{
				if (hand[i].getValue() == hand[j].getValue() && hand[i].getValue() == hand[k].getValue())
				{
					highestCard = hand[i].getValue();
					return true;
				}
			}
		}
	}
	return false;
}

bool PokerHand::straight()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = i; j < 5; j++)
		{
			if (hand[i].getValue() > hand[j].getValue())
			{
				swap(hand[i], hand[j]);
			}
		}
	}
	if (hand[0].getValue() == (hand[1].getValue() + 1) && hand[1].getValue() == (hand[2].getValue() + 1) && hand[2].getValue() == (hand[3].getValue() + 1) && hand[3].getValue() == (hand[4].getValue() + 1))
	{
		highestCard = hand[4].getValue();
		return true;
	}
	return false;
}

bool PokerHand::flush()
{
	highestCard = 0;
	int counter = 1;
	int buffer=hand[0].getType();
	for (int i = 1; i < 5; i++)
	{
		if (hand[i].getValue() > highestCard) 
		{
			highestCard = hand[i].getValue();
		}
		if (hand[i].getType() == buffer) 
		{
			++counter;
		}
	}
	if (counter == 5)
	{ 
		return true;
	}
	else
	{
		return false;
	}
}


bool PokerHand::fourOfAKind()
{
	highestCard = 0;
	int counter = 0;
	for (int i = 0; i < 1; i++)
	{
		for (int j = i + 1; j < 5; j++)
		{
			if (hand[i].getValue() == hand[j].getValue())
			{
				counter++;
				break;
			}
		}
		if (counter == 4)
		{
			highestCard = hand[i].getValue();
			return true;
		}
		counter = 0;
	}
	return false;
}

bool PokerHand::straightFlush()
{
	if (straight() == true && flush() == true)
	{
		return true;
	}
	return false;
}

bool PokerHand::royalFlush()
{
	if (straight() == true && flush() == true && highestCard == 13)
	{
		highestCard = 14;
		return true;
	}
	return false;
}