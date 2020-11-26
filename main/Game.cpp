#include "Deck.cpp""
#include "Player.cpp"
#define MAXPLAYERS 6

struct Game {
	int number_of_players =0;
	int number_of_cauldrons =0;
	int number_of_greens = 0;
	int value_of_greens = 0;
	Deck main_deck;
	Player players[MAXPLAYERS];
	int active_index = 1;
};