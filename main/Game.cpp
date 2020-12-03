#include "Deck.cpp"
#include "Player.cpp"
#include "Cauldron.cpp"
#define MAXPLAYERS 6
#define MAXCAULDRONS 6

struct Game {
	int explosion_threshold = 0;
	int number_of_players = 0;
	int number_of_cauldrons = 0;
	int number_of_greens = 0;
	int value_of_greens = 0;
	Deck main_deck;
	Player players[MAXPLAYERS];
	Deck cauldrons[MAXCAULDRONS];
	int active_index = 1;
};