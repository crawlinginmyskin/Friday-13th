#include <iostream>
#include "Cauldron.cpp"
#include "Deck.cpp"
#include "Player.cpp"
#include "Game.cpp"
#include <cassert>

#define MAXCAULDRONS 6

const char COLORS[MAXCAULDRONS][7] = { "blue", "red", "violet", "yellow", "white", "black" };

int segment(int arr[], int a, int b)
{
    //division of a table into two parts, one where all elements are smaller than arr[a], second where all elements are bigger or equal arr[a]
    
    int x = arr[a];
    int i = a, j = b, c;
    while (true) 
    {
        while (arr[j] > x) 
        {
            j--;
        }
        while (arr[i] < x) 
        {
            i++;
        }
        if (i < j)
        {
            c = arr[i];
            arr[i] = arr[j];
            arr[j] = c;
            i++;
            j--;
        }
        else 
        {
            return j;//j is the division point of the array    
        }
    }
}



void qsort(int arr[], int a, int b)
{
	//implementing quicksort algorithm to sort user input, in case the user's naughty and inputs values in non-increasing order
    int c;
    if (a < b) 
    {
        c = segment(arr, a, b);
        qsort(arr, a, c);
        qsort(arr, c + 1, b);
    }
}



int active_id(int current_id, int number_of_players)
{
    //first check next available id to be active, then return it
    if (current_id < number_of_players-1) 
    {
        return current_id + 1;
    }
    else 
    {
        return 0;
    }

}



void fill_greens(Deck* deck, int number_of_greens, int green_value)
{
	//fil a green_cards array in a Deck structure with values specified by the user 
    for (int i = 0; i < number_of_greens; i++) 
    {
        deck->green_cards[i] = green_value;
    }
}



void fill_deck(Deck* deck, int cauldrons, int card_values[MAXDECKSIZE])
{
    int i = 0;
	
    switch (cauldrons)
	{
    case 1:
        while (card_values[i] != 0) 
        {
            deck->blue_cards[i] = card_values[i];
            i++;
        }
		break;
    case 2:
        while(card_values[i] !=0) 
        {
            deck->blue_cards[i] = card_values[i];
            deck->red_cards[i] = card_values[i];
            i++;
        }
        break;
    case 3:
        while (card_values[i] != 0) 
        {
            deck->blue_cards[i] = card_values[i];
            deck->red_cards[i] = card_values[i];
            deck->violet_cards[i] = card_values[i];
            i++;
        }
        break;
    case 4:
        while (card_values[i] != 0) 
        {
            deck->blue_cards[i] = card_values[i];
            deck->red_cards[i] = card_values[i];
            deck->violet_cards[i] = card_values[i];
            deck->yellow_cards[i] = card_values[i];
            i++;
        }
        break;

    case 5:
        while (card_values[i] != 0) 
        {
            deck->blue_cards[i] = card_values[i];
            deck->red_cards[i] = card_values[i];
            deck->violet_cards[i] = card_values[i];
            deck->yellow_cards[i] = card_values[i];
            deck->white_cards[i] = card_values[i];
            i++;
        }
        break;
    case 6:
        while (card_values[i] != 0) 
        {
            
            deck->blue_cards[i] = card_values[i];
            deck->red_cards[i] = card_values[i];
            deck->violet_cards[i] = card_values[i];
            deck->yellow_cards[i] = card_values[i];
            deck->white_cards[i] = card_values[i];
            deck->black_cards[i] = card_values[i];
            i++;
        }
        break;
    }
} 



void deal_cards(Game* game, int number_of_greens)
//the function deals cards to players, starting from player 1 and with green cards
{
    int i = 0;
    int number_of_cards = 0;
    int last_dealt = 0;
	
    while (game->main_deck.blue_cards[i] != 0) 
    {
        i++;
        number_of_cards++;
    }
    
    for (int j = 0; j < number_of_greens; j++) 
    {
        game->players[j % game->number_of_players].hand.green_cards[j / game->number_of_players] = game->main_deck.green_cards[j];
        last_dealt = j % game->number_of_players;
    }

    
    
    for (int j = 0 ; j < number_of_cards * game->number_of_cauldrons; j++) 
    {
        last_dealt = active_id(last_dealt, game->number_of_players);
        int color =  j / number_of_cards; //UWAGA
        int position = 0;
        switch (color)
    	{
        case 0:
            game->players[last_dealt].hand.blue_cards[(j % number_of_cards) / game->number_of_players] = game->main_deck.blue_cards[j % number_of_cards];
            break;
        case 1:
            game->players[last_dealt].hand.red_cards[(j % number_of_cards) / game->number_of_players] = game->main_deck.red_cards[j % number_of_cards];
            break;
        case 2:
            game->players[last_dealt].hand.violet_cards[(j % number_of_cards)  / game->number_of_players] = game->main_deck.violet_cards[j % number_of_cards];
            break;
        case 3:
            game->players[last_dealt].hand.yellow_cards[(j % number_of_cards) / game->number_of_players] = game->main_deck.yellow_cards[j % number_of_cards];
            break;
        case 4:
            game->players[last_dealt].hand.white_cards[(j % number_of_cards) / game->number_of_players] = game->main_deck.white_cards[j % number_of_cards];
            break;
        case 5:
            game->players[last_dealt].hand.black_cards[(j % number_of_cards) / game->number_of_players] = game->main_deck.black_cards[j % number_of_cards];
            break;
        }     
    }
}


void print_deck(Game* game)
//this function prints all cards from each player's hand and deck, starting with the former
{
	for(int i = 0; i < game->number_of_players; i++)
	{
        std::cout << i+1 << " player hand cards: "; //start printing hand cards
        int j = 0;
		
		while (game->players[i].hand.green_cards[j] != 0)
		{
            std::cout << game->players[i].hand.green_cards[j] << " green ";
            j++;
		}
		
        j = 0;

		while (game->players[i].hand.blue_cards[j] != 0)
        {
            std::cout << game->players[i].hand.blue_cards[j] << " blue ";
            j++;
        }
		
		j = 0;
		
        while (game->players[i].hand.red_cards[j] != 0)
        {
            std::cout << game->players[i].hand.red_cards[j] << " red ";
            j++;
        }
		
        j = 0;
		
        while (game->players[i].hand.violet_cards[j] != 0)
        {
            std::cout << game->players[i].hand.violet_cards[j] << " violet ";
            j++;
        }
		
        j = 0;
		
        while (game->players[i].hand.yellow_cards[j] != 0)
        {
            std::cout << game->players[i].hand.yellow_cards[j] << " yellow ";
            j++;
        }
		
        j = 0;
		
        while (game->players[i].hand.white_cards[j] != 0)
        {
            std::cout << game->players[i].hand.white_cards[j] << " white ";
            j++;
        }
		
        j = 0;
		
        while (game->players[i].hand.black_cards[j] != 0)
        {
            std::cout << game->players[i].hand.black_cards[j] << " black ";
            j++;
        }
		
        std::cout << std::endl; // this marks the end of printing hand cards
		
        std::cout << i+1 << " player deck cards: "; //start printing deck cards

		while (game->players[i].deck.green_cards[j] != 0)
        {
            std::cout << game->players[i].deck.green_cards[j] << " green ";
            j++;
        }
		
        j = 0;
		
        while (game->players[i].deck.blue_cards[j] != 0)
        {
            std::cout << game->players[i].deck.blue_cards[j] << " blue ";
            j++;
        }
		
        j = 0;
		
        while (game->players[i].deck.red_cards[j] != 0)
        {
            std::cout << game->players[i].deck.red_cards[j] << " red ";
            j++;
        }
		
        j = 0;
		
        while (game->players[i].deck.violet_cards[j] != 0)
        {
            std::cout << game->players[i].deck.violet_cards[j] << " violet ";
            j++;
        }
		
        j = 0;
		
        while (game->players[i].deck.yellow_cards[j] != 0)
        {
            std::cout << game->players[i].deck.yellow_cards[j] << " yellow ";
            j++;
        }

		j = 0;
		
        while (game->players[i].deck.white_cards[j] != 0)
        {
            std::cout << game->players[i].deck.white_cards[j] << " white ";
            j++;
        }
		
        j = 0;
		
        while (game->players[i].deck.black_cards[j] != 0)
        {
            std::cout << game->players[i].deck.black_cards[j] << " black ";
            j++;
        }
		
        std::cout << std::endl;
	}
}



void print_cauldrons(Game* game)
{
	for(int i = 0; i < game->number_of_cauldrons; i++)
	{
        std::cout << i+1 << " pile cards: "<<std::endl;
	}
}



int main()
{
    int active = 1;
    Game game;

    
    std::cin >> game.number_of_players;
    assert((game.number_of_players >= 2) && (game.number_of_players <= 6));

    std::cin >> game.number_of_cauldrons;
    assert((game.number_of_cauldrons >= 1) && (game.number_of_cauldrons <= 6));
    
    int number_of_greens;
    std::cin >> number_of_greens;
    assert((number_of_greens >= 1) && (number_of_greens <=9));
    
    int value_of_greens; 
    std::cin >> value_of_greens;
    assert((value_of_greens >= 1) && (value_of_greens <= 10));
    
    int number_of_cards;
    std::cin >> number_of_cards;
    assert((number_of_cards >= 1) && (number_of_cards <= MAXDECKSIZE));
    
    int card_values[MAXDECKSIZE] ={0};
    
    for (int i = 0; i < number_of_cards; i++) 
    {
        int value;
        std::cin >> value;
        card_values[i] = value;
    }

    
    qsort(card_values, 0, number_of_cards - 1);
  
    fill_greens(&game.main_deck, number_of_greens, value_of_greens);
    fill_deck(&game.main_deck, game.number_of_cauldrons, card_values);
    deal_cards(&game, number_of_greens);

    int a = 0;
    
    std::cout << "active player = " << active << std::endl;
    std::cout << "players number = " << game.number_of_players << std::endl;
    print_deck(&game);
    print_cauldrons(&game);
	
	
    return 0;
}
