#include "Deck.cpp"

#ifndef PLAYER
#define PLAYER


struct Player {
	int handcards = 0;
	int deckcards = 0;
	int points=0;
	Deck hand;
	Deck deck;
};

#endif