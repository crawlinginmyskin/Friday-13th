#include "Deck.cpp""
#include "Player.cpp"
#define MAXPLAYERS 6

struct Game {
	int number_of_players;
	int number_of_cauldrons;
	Deck main_deck;
	Player players[MAXPLAYERS];
	int active_index;
};