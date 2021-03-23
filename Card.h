#pragma once

#include <stdlib.h>
#include <ctime>
#include <string>
using namespace std;

class Card
{
private:
	//attributes
	char suit;
	char face;
	short value;

	static bool randomizerSeeded; //class-wide variable (one copy in memory is shared by all Card objects)

public:
	//constructor and destructor
	Card();
	~Card();

	//behaviors
	string toString();
	bool flipAceToOne();

	//accessors and mutators
	inline char getSuit(){return suit;}
	inline char getFace(){return face;}
	inline short getValue(){return value;}

};

