
#ifndef DECK
#define DECK
#define MAXDECKSIZE 20
#define MAXDECKUPDATED 129

struct Deck 
{
	int cards[MAXDECKUPDATED] = { 0 };
	int colors[MAXDECKUPDATED] = { 0 };
};


#endif