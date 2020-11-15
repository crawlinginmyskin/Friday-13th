#include "Deck.cpp"

#ifndef PLAYER
#define PLAYER


struct Player {
	int points=0;
	Deck hand;
	Deck deck;
};

#endif