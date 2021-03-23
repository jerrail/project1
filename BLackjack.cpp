/*Jerrail Mickens
CIS247C Week 2 lab
1/11/2021*/


#include <iostream>
#include <string>
#include <conio.h>
#include "Card.h"
#include <vector> //(STL)
using namespace std;

//prototypes
string showCards(vector<Card> cards);
short sumCardValues(vector<Card> cards);
void playHand(short &cash);		// & means "address of" --variable sent by reference

/// Entry point to the application
int main()
{

	// set starting cash and display it to the player
	short cash = 100;
	cout << "Welcome to BlackJack!" << endl;
	cout << "\nYou are starting out with $" << cash << endl;

	//pause
	cout << "\nPress any key to continue...";
	_getch();

	//create the loop
	short choice = 0;

	do
	{
		//Menu options and get player choice
		cout << "Menu\n" << endl;
		cout << "1) Play a hand" << endl;
		cout << "2) Current cash balance" << endl;
		cout << "3) Exit" << endl;

		cout << "\nEnter your choice: ";
		cin >> choice;

		//switch based on choice
		switch (choice)
		{
		case 1:
			playHand(cash);
			break;
		case 2:
			cout << "\nCurent cash balance: $" << cash << endl;
			break;
		case 3:
			cout << "\nThank you for playing BlackJack!" << endl;
			cout << "\nYour final cash balance: $" << cash << endl;
			break;
		default:
			cout << "\nError. Please select a menu option..." << endl;
			break;
		}
		//pause
		cout << "\nPress any key to continue..";
		_getch();

	} while (choice != 3);

	return 0;
}


	/// Show the card in the vector (resizeable array)
	string showCards(vector<Card> cards)
	{
		string output = " ";

		for (Card c : cards)
		{
			output += c.toString() + " ";
		}

		return output;
	}

	/// Add up the total value of the cards
	short sumCardValues(vector<Card> cards)
	{
		short total = 0;

		for(Card c : cards)
		{
			total = total + c.getValue();
		}
		return total;
	}

	/// Play a single hand of BlackJack
	void playHand(short& cash)
	{
		// Create two arrayLists that can hold Card objects
		// An ArrayList is a resizeable array (vector)
		vector<Card> dealerCards;
		vector<Card> playerCards;
		short dealerCardsTotal = 0;
		short playerCardsTotal = 0;

		//get bet amount
		short bet = 0;
		cout << "\nEnter bet amount: ";
		cin >> bet;

		// Create two cards for dealer and show the first one
		int mumber;
		Card card1;
		Card card2;
		dealerCards.push_back(card1);
		dealerCards.push_back(card2);
		dealerCardsTotal = sumCardValues(dealerCards);

		cout << "\nDealer is showing: " << dealerCards[0].toString() << endl;


		// create two cards for the player and show both
		playerCards.push_back(Card()); //create the card and put directly into ArrayList
		playerCards.push_back(Card());
		playerCardsTotal = sumCardValues(playerCards);

		cout << "\nHere are your cards: " << showCards(playerCards) << endl;

		//give cards to player until they stand ('S')
		char answer = '?';

		do
		{
			cout << "\nDo you want to hit or stand (H/S)? ";
			cin.sync();	//flush the input stream
			cin >> answer;
			cin.sync();

			if (toupper(answer) == 'H')
			{
				//give a card to the player
				Card c;
				cout << "\nYou were dealt this card: " << c.toString() << endl;
				playerCards.push_back(c);	//add card to players hand

				// sum up the card values
				playerCardsTotal = sumCardValues(playerCards);

				// did the player bust?
				if (playerCardsTotal > 21)
				{
					// do you have an Ace?
					for (Card c : playerCards)
					{
						if (c.getValue() == 11)
						{
							cout << "\nYour total is " << playerCardsTotal << endl;
							c.flipAceToOne();
							cout << "However, you have an Ace that was changed to a '1' value" << endl;
							playerCardsTotal = sumCardValues(playerCards);
							cout << "\nYour new total is " << playerCardsTotal << endl;

							// if we are good now, break out of loop. otherwise continue
							if (playerCardsTotal <= 21)
								break;
						}
					}
				}

				// show the cards and the total
				cout << "\nHere are your cards: " << showCards(playerCards) << endl;
				cout << "Your totatl is " << playerCardsTotal << endl;

				//if busted stop the loop
				if (playerCardsTotal > 21)
					answer = 'S';


			}
		} while (toupper(answer) != 'S');


		// if the players card total is more than 21 take money away
		if (playerCardsTotal > 21)
		{
			cout << "\nyou Busted!" << endl;
			cash = cash - bet;

		}
		else
		{
			//player stands so the dealer hits 17 or greater
			do
			{
				if (dealerCardsTotal < 17)
				{
					Card c;
					cout << "\nDealer was dealt: " << c.toString() << endl;
					dealerCards.push_back(c);	// add the card to the dealrs hand
					cout << "\nDealer cards: " << showCards(dealerCards) << endl;
					dealerCardsTotal = sumCardValues(dealerCards);
					cout << "Dealer total: " << dealerCardsTotal << endl;
				}
			} while (dealerCardsTotal < 17);

			// show the cards for the dealer and player
			cout << "\nYour cards: " << showCards(playerCards) << " (" << playerCardsTotal << ")" << endl;
			cout << "\nDealer Cards: " << showCards(dealerCards) << " (" << dealerCardsTotal << ")" << endl;

			//who wins?
			if (dealerCardsTotal > 21)
			{
				cout << "\nDealer Busted!" << endl;
				cash = cash + bet;
			}
			else if (dealerCardsTotal > playerCardsTotal)
			{
				cout << "\nDealer wins." << endl;
				cash = cash - bet;
			}
			else if (playerCardsTotal > dealerCardsTotal)
			{
				cout << "\nYou win!!" << endl;
				cash = cash + bet;
			}
			else
			{
				cout << "\nYou pushed the dealer (tie)" << endl;
			}
		}

		// show the current cash position
		cout << "\nYour current cash balance: $" << cash << endl;
	}
