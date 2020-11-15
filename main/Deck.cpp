
#ifndef DECK
#define DECK
#define MAXDECKSIZE 20

struct Deck {
	int green_cards[MAXDECKSIZE] = { 0 };
	int blue_cards[MAXDECKSIZE] = { 0 };
	int red_cards[MAXDECKSIZE] = { 0 };
	int violet_cards[MAXDECKSIZE] = { 0 };
	int yellow_cards[MAXDECKSIZE] = { 0 };
	int white_cards[MAXDECKSIZE] = { 0 };
	int black_cards[MAXDECKSIZE] = { 0 };
};

#endif