#include <iostream>
#include "Cauldron.cpp"
#include "Deck.cpp"
#include "Player.cpp"
#include "Game.cpp"
#include <assert.h>

#define MAXCAULDRONS 6


const char COLORS[MAXCAULDRONS][7] = { "blue", "red", "violet", "yellow", "white", "black" };

int segment(int arr[], int a, int b) {
    //division of a table into two parts, one where all elements are smaller than arr[a], second where all elements are bigger or equal arr[a]
    
    int x = arr[a];
    int i = a, j = b, c;
    while (true) {
        while (arr[j] > x) {
            j--;
        }
        while (arr[i] < x) {
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
        else {
            return j;//j is the division point of the array
            
        }

    }
}

void qsort(int arr[], int a, int b) {
    int c;
    if (a < b) {
        c = segment(arr, a, b);
        qsort(arr, a, c);
        qsort(arr, c + 1, b);
    }
}

int active_id(int current_id, int number_of_players) {
    if (current_id < number_of_players) {
        return current_id + 1;
    }
    else {
        return 1;
    }

}
void fill_greens(Deck* deck, int number_of_greens, int green_value) {
    for (int i = 0; i < number_of_greens; i++) {
        deck->green_cards[i] = green_value;
    }
}




void fill_deck(Deck* deck, int cauldrons, int card_values[MAXDECKSIZE]) 
{
    int i = 0;
    switch (cauldrons) {
    case 1:
        while (card_values[i] != 0) {
            deck->blue_cards[i] = card_values[i];
            i++;
        }
        break;
    case 2:
        while(card_values[i] !=0) {
            deck->blue_cards[i] = card_values[i];
            deck->red_cards[i] = card_values[i];
            i++;
        }
        break;
    case 3:
        while (card_values[i] != 0) {
            deck->blue_cards[i] = card_values[i];
            deck->red_cards[i] = card_values[i];
            deck->violet_cards[i] = card_values[i];
            i++;
        }
        break;
    case 4:
        while (card_values[i] != 0) {
            deck->blue_cards[i] = card_values[i];
            deck->red_cards[i] = card_values[i];
            deck->violet_cards[i] = card_values[i];
            deck->yellow_cards[i] = card_values[i];
            i++;
        }
        break;

    case 5:
        while (card_values[i] != 0) {
            deck->blue_cards[i] = card_values[i];
            deck->red_cards[i] = card_values[i];
            deck->violet_cards[i] = card_values[i];
            deck->yellow_cards[i] = card_values[i];
            deck->white_cards[i] = card_values[i];
            i++;
        }
        break;
    case 6:
        while (card_values[i] != 0) {
            
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

void deal_cards(Game* game, int number_of_greens) {
    int i = 0;
    int number_of_cards = 0;
    int last_dealt = 0;
    while (game->main_deck.blue_cards[i] != 0) {
        i++;
        number_of_cards++;
    }
    
    for (int j = 0; j < number_of_greens; j++) {
        game->players[j % game->number_of_players].hand.green_cards[j / game->number_of_players] = game->main_deck.green_cards[j];
        last_dealt = j % game->number_of_players;
    }

    number_of_cards = number_of_cards * game->number_of_cauldrons;
    
    for (int j = 0 ; j < number_of_cards; j++) {
        last_dealt = active_id(last_dealt, game->number_of_players);
        int color = j / number_of_cards;
        switch (color){
        case 0:
            game->players[last_dealt].hand.blue_cards[j / game->number_of_players] = game->main_deck.blue_cards[j % number_of_cards];
            break;
        case 1:
            game->players[last_dealt].hand.red_cards[j / game->number_of_players] = game->main_deck.red_cards[j % number_of_cards];
            break;
        case 2:
            game->players[last_dealt].hand.violet_cards[j / game->number_of_players] = game->main_deck.violet_cards[j % number_of_cards];
            break;
        case 3:
            game->players[last_dealt].hand.yellow_cards[j / game->number_of_players] = game->main_deck.yellow_cards[j % number_of_cards];
            break;
        case 4:
            game->players[last_dealt].hand.white_cards[j / game->number_of_players] = game->main_deck.white_cards[j % number_of_cards];
            break;
        case 5:
            game->players[last_dealt].hand.black_cards[j / game->number_of_players] = game->main_deck.black_cards[j % number_of_cards];
            break;
        }
       



        
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
    
    int card_values[MAXDECKSIZE];
    
    for (int i = 0; i < number_of_cards; i++) {
        int value;
        std::cin >> value;
        card_values[i] = value;
    }

    
    qsort(card_values, 0, number_of_cards - 1);
  
    fill_greens(&game.main_deck, number_of_greens, value_of_greens);
    fill_deck(&game.main_deck, game.number_of_cauldrons, card_values);
    deal_cards(&game, number_of_greens);

    int a = 0;
    while (game.players[0].hand.green_cards[a] != 0) {
        std::cout << game.players[0].hand.green_cards[a];
        a++;

    }
    
    return 0;
}
