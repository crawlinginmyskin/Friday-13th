#include <iostream>
#include "Deck.cpp"
#include "Player.cpp"
#include "Game.cpp"
#include <string.h>



#define MAXINPUTSIZE 10000
#define CARDSINCAULDRON 100

const char COLORS[MAXCAULDRONS + 1][7] = { "green", "blue", "red", "violet", "yellow", "white", "black" };

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


void deal_cards(Game* game)
{
    for (int i = 0; i < game->number_of_cauldrons * game->number_of_cards + game->number_of_greens; i++)
    {
        if (game->main_deck.cards[i] != 0)
        {


            game->players[i % game->number_of_players].hand.cards[i / game->number_of_players] = game->main_deck.cards[i];
            game->players[i % game->number_of_players].hand.colors[i / game->number_of_players] = game->main_deck.colors[i];
            game->players[i % game->number_of_players].handcards++;
        }
    }
}



int active_id(int current_id, int number_of_players)
{
    //first check next available id to be active, then return it
    if (current_id < number_of_players)
    {
        return current_id + 1;
    }
    else
    {
        return 1;
    }

}


void green_check(char input[MAXINPUTSIZE], Game& game)
{
    int i = 0;
    while (input[i])
    {
        if (input[i] == 'g')
        {
            if (game.value_of_greens == 0 && input[i - 3] == 32)
            {
                game.value_of_greens = input[i - 2] - 48;
            }
            else if (game.value_of_greens == 0 && input[i - 3] != 32)
            {
                game.value_of_greens = ((input[i - 3] - 48) * 10) + (input[i - 2] - 48);
            }
            else if (game.value_of_greens != input[i - 2] - 48 && input[i - 3] == 32)
            {
                game.value_of_greens = -1;
            }
            else if (input[i - 3] != 32 && game.value_of_greens != ((input[i - 3] - 48) * 10) + (input[i - 2] - 48))
            {
                game.value_of_greens = -1;
            }


            //game.number_of_greens++;

        }
        i++;
    }
}


void count_cards(char input[MAXINPUTSIZE], int number_cauldrons, int cards[2 * MAXPLAYERS], int cauldrons[MAXCAULDRONS] = { 0 })
{

    int playerToken = 0;
    int cardcounter = 0;
    if (input[0] >= '0' && input[0] <= '9') //
    {
        if (input[4] == 'l') //pile card counting TASK 3b
        {
            int i = 1;
            while (input[i])
            {
                if (input[i] >= '0' && input[i] <= '9')
                {
                    if (input[i + 1] >= '0' && input[i + 1] <= '9')
                    {
                        i++;
                    }
                    cardcounter++;
                }
                i++;
            }
            cauldrons[number_cauldrons++] = cardcounter;
        }
        else
        {
            int i = 1;
            while (input[i]) //player hand/deck counting TASK 3a
            {
                if (input[i] >= '0' && input[i] <= '9')
                {
                    if (input[i + 1] >= '0' && input[i + 1] <= '9')
                    {
                        i++;
                    }
                    cardcounter++;
                }
                i++;
            }
            cards[playerToken++] = cardcounter;
        }


    }
}

void color_check(char input[MAXINPUTSIZE], int colorcheck[MAXCAULDRONS][MAXDECKSIZE], int j, int color)
{
    int unique = 0;
    for (int k = 0; k < MAXDECKSIZE; k++) {
        if (colorcheck[color][k] == 0 && unique == 0)
        {
            if (input[j - 3] == 32)
            {
                colorcheck[color][k] = input[j - 2] - 48;
                unique = 1;
            }
            else
            {
                colorcheck[color][k] = (input[j - 3] - 48) * 10 + (input[j - 2] - 48);
                unique = 1;
            }
        }
    }

}
int card_checker(int cards[MAXPLAYERS], int number_of_players, int active_player)
{
    int card_differential = 0;
    for (int i = 1; i < number_of_players; i++)
    {
        if ((cards[i] > cards[0] && i > active_player) || (cards[0] - cards[i] > 2) || (cards[i] - cards[0] > 2))
        {
            return 1;
        }
    }
    return 0;
}



void color_count(int colorcounter[MAXCAULDRONS], int colorcheck[MAXCAULDRONS][MAXDECKSIZE], char input[MAXINPUTSIZE])
{
    int i = 1;
    while (input[i])
    {
        if (input[i] == ':')
        {
            int j = i;
            while (input[j])
            {
                if (input[j] == 'b' && input[j + 1] == 'l' && input[j + 2] == 'u')
                {
                    colorcounter[0]++;
                    color_check(input, colorcheck, j, 0);


                }
                else if (input[j] == 'r' && input[j + 1] == 'e' && input[j + 2] == 'd')
                {
                    colorcounter[1]++;
                    color_check(input, colorcheck, j, 1);
                }
                else if (input[j] == 'y' && input[j + 1] == 'e' && input[j + 2] == 'l')
                {
                    colorcounter[3]++;
                    color_check(input, colorcheck, j, 3);

                }
                else if (input[j] == 'v' && input[j + 1] == 'i' && input[j + 2] == 'o')
                {
                    colorcounter[2]++;
                    color_check(input, colorcheck, j, 2);
                }
                else if (input[j] == 'w' && input[j + 1] == 'h' && input[j + 2] == 'i')
                {
                    colorcounter[4]++;
                    color_check(input, colorcheck, j, 4);
                }
                else if (input[j] == 'b' && input[j + 1] == 'l' && input[j + 2] == 'a')
                {
                    colorcounter[5]++;
                    color_check(input, colorcheck, j, 5);
                }
                j++;
            }
        }
        i++;
    }

}

void cauldron_color_check(char input[MAXINPUTSIZE], int cauldron_colors[MAXCAULDRONS][CARDSINCAULDRON], int j, int i)
{
    if (input[j] == 'b' && input[j + 1] == 'l' && input[j + 2] == 'u')
    {
        cauldron_colors[input[0] - 49][i] = 1;
    }
    else if (input[j] == 'r' && input[j + 1] == 'e' && input[j + 2] == 'd')
    {
        cauldron_colors[input[0] - 49][i] = 2;
    }
    else if (input[j] == 'y' && input[j + 1] == 'e' && input[j + 2] == 'l')
    {
        cauldron_colors[input[0] - 49][i] = 3;

    }
    else if (input[j] == 'v' && input[j + 1] == 'i' && input[j + 2] == 'o')
    {
        cauldron_colors[input[0] - 49][i] = 4;
    }
    else if (input[j] == 'w' && input[j + 1] == 'h' && input[j + 2] == 'i')
    {
        cauldron_colors[input[0] - 49][i] = 5;
    }
    else if (input[j] == 'b' && input[j + 1] == 'l' && input[j + 2] == 'a')
    {
        cauldron_colors[input[0] - 49][i] = 6;
    }
}

void player_cards_count(char input[MAXINPUTSIZE], Game* game)
{
    if (input[0] > '0' && input[0] <= '9')
    {
        int i = 1;
        while (input[i])
        {
            if (input[i] > '0' && input[i] <= '9' && input[9] == 'h')
            {
                game->players[input[0] - 49].handcards++;
                if (input[i + 1] != 32)
                {
                    i++;
                }
            }
            if (input[i] > '0' && input[i] <= '9' && input[9] == 'd')
            {
                game->players[input[0] - 49].deckcards++;
                if (input[i + 1] != 32)
                {
                    i++;
                }
            }
            i++;
        }
    }
}

void players_read_cards(char input[MAXINPUTSIZE], Game* game, int j, int hand_or_deck)
{
    int last_hand_index = 0;
    int last_deck_index = 0;
    while (input[j])
    {
        if (hand_or_deck == 0)
        {
            if (input[j] == 'b' && input[j + 1] == 'l' && input[j + 2] == 'u')
            {
                game->players[input[0] - 49].hand.colors[last_hand_index] = 1;
                if (input[j - 3] == 32)
                {
                    game->players[input[0] - 49].hand.cards[last_hand_index++] = input[j - 2] - 48;
                }
                else
                {
                    game->players[input[0] - 49].hand.cards[last_hand_index++] = (input[j - 3] - 48)*10 + input[j-2] - 48;
                }
            }
            else if (input[j] == 'r' && input[j + 1] == 'e' && input[j + 2] == 'd')
            {
                game->players[input[0] - 49].hand.colors[last_hand_index] = 2;
                if (input[j - 3] == 32)
                {
                    game->players[input[0] - 49].hand.cards[last_hand_index++] = input[j - 2] - 48;
                }
                else
                {
                    game->players[input[0] - 49].hand.cards[last_hand_index++] = (input[j - 3] - 48) * 10 + input[j - 2] - 48;
                }
            }
            else if (input[j] == 'y' && input[j + 1] == 'e' && input[j + 2] == 'l')
            {
                game->players[input[0] - 49].hand.colors[last_hand_index] = 4;
                if (input[j - 3] == 32)
                {
                    game->players[input[0] - 49].hand.cards[last_hand_index++] = input[j - 2] - 48;
                }
                else
                {
                    game->players[input[0] - 49].hand.cards[last_hand_index++] = (input[j - 3] - 48) * 10 + input[j - 2] - 48;
                }
            }
            else if (input[j] == 'v' && input[j + 1] == 'i' && input[j + 2] == 'o')
            {
                game->players[input[0] - 49].hand.colors[last_hand_index] = 3;
                if (input[j - 3] == 32)
                {
                    game->players[input[0] - 49].hand.cards[last_hand_index++] = input[j - 2] - 48;
                }
                else
                {
                    game->players[input[0] - 49].hand.cards[last_hand_index++] = (input[j - 3] - 48) * 10 + input[j - 2] - 48;
                }
            }
            else if (input[j] == 'w' && input[j + 1] == 'h' && input[j + 2] == 'i')
            {
                game->players[input[0] - 49].hand.colors[last_hand_index] = 5;
                if (input[j - 3] == 32)
                {
                    game->players[input[0] - 49].hand.cards[last_hand_index++] = input[j - 2] - 48;
                }
                else
                {
                    game->players[input[0] - 49].hand.cards[last_hand_index++] = (input[j - 3] - 48) * 10 + input[j - 2] - 48;
                }
            }
            else if (input[j] == 'b' && input[j + 1] == 'l' && input[j + 2] == 'a')
            {
                game->players[input[0] - 49].hand.colors[last_hand_index] = 6;
                if (input[j - 3] == 32)
                {
                    game->players[input[0] - 49].hand.cards[last_hand_index++] = input[j - 2] - 48;
                }
                else
                {
                    game->players[input[0] - 49].hand.cards[last_hand_index++] = (input[j - 3] - 48) * 10 + input[j - 2] - 48;
                }
            }
            else if (input[j] == 'g' && input[j + 1] == 'r' && input[j + 2] == 'e')
            {
                if (input[j - 3] == 32)
                {
                    game->players[input[0] - 49].hand.cards[last_hand_index++] = input[j - 2] - 48;
                }
                else
                {
                    game->players[input[0] - 49].hand.cards[last_hand_index++] = (input[j - 3] - 48) * 10 + input[j - 2] - 48;
                }
            }
            
        }
        else if (hand_or_deck == 1)
        {
            if (input[j] == 'b' && input[j + 1] == 'l' && input[j + 2] == 'u')
            {
                game->players[input[0] - 49].deck.colors[last_deck_index] = 1;
                if (input[j - 3] == 32)
                {
                    game->players[input[0] - 49].deck.cards[last_deck_index++] = input[j - 2] - 48;
                }
                else
                {
                    game->players[input[0] - 49].deck.cards[last_deck_index++] = (input[j - 3] - 48) * 10 + input[j - 2] - 48;
                }
            }
            else if (input[j] == 'r' && input[j + 1] == 'e' && input[j + 2] == 'd')
            {
                game->players[input[0] - 49].deck.colors[last_deck_index] = 2;
                if (input[j - 3] == 32)
                {
                    game->players[input[0] - 49].deck.cards[last_deck_index++] = input[j - 2] - 48;
                }
                else
                {
                    game->players[input[0] - 49].deck.cards[last_deck_index++] = (input[j - 3] - 48) * 10 + input[j - 2] - 48;
                }
            }
            else if (input[j] == 'y' && input[j + 1] == 'e' && input[j + 2] == 'l')
            {
                game->players[input[0] - 49].deck.colors[last_deck_index] = 4;
                if (input[j - 3] == 32)
                {
                    game->players[input[0] - 49].deck.cards[last_deck_index++] = input[j - 2] - 48;
                }
                else
                {
                    game->players[input[0] - 49].deck.cards[last_deck_index++] = (input[j - 3] - 48) * 10 + input[j - 2] - 48;
                }
            }
            else if (input[j] == 'v' && input[j + 1] == 'i' && input[j + 2] == 'o')
            {
                game->players[input[0] - 49].deck.colors[last_deck_index] = 3;
                if (input[j - 3] == 32)
                {
                    game->players[input[0] - 49].deck.cards[last_deck_index++] = input[j - 2] - 48;
                }
                else
                {
                    game->players[input[0] - 49].deck.cards[last_deck_index++] = (input[j - 3] - 48) * 10 + input[j - 2] - 48;
                }
            }
            else if (input[j] == 'w' && input[j + 1] == 'h' && input[j + 2] == 'i')
            {
                game->players[input[0] - 49].deck.colors[last_deck_index] = 5;
                if (input[j - 3] == 32)
                {
                    game->players[input[0] - 49].deck.cards[last_deck_index++] = input[j - 2] - 48;
                }
                else
                {
                    game->players[input[0] - 49].deck.cards[last_deck_index++] = (input[j - 3] - 48) * 10 + input[j - 2] - 48;
                }
            }
            else if (input[j] == 'b' && input[j + 1] == 'l' && input[j + 2] == 'a')
            {
                game->players[input[0] - 49].deck.colors[last_deck_index] = 6;
                if (input[j - 3] == 32)
                {
                    game->players[input[0] - 49].deck.cards[last_deck_index++] = input[j - 2] - 48;
                }
                else
                {
                    game->players[input[0] - 49].deck.cards[last_deck_index++] = (input[j - 3] - 48) * 10 + input[j - 2] - 48;
                }
            }
            else if (input[j] == 'g' && input[j + 1] == 'r' && input[j + 2] == 'e')
            {
                if (input[j - 3] == 32)
                {
                    game->players[input[0] - 49].deck.cards[last_deck_index++] = input[j - 2] - 48;
                }
                else
                {
                    game->players[input[0] - 49].deck.cards[last_deck_index++] = (input[j - 3] - 48) * 10 + input[j - 2] - 48;
                }
            }
        }
        j++;
    }

}

void cauldron_read_cards(char input[MAXINPUTSIZE], Game* game)
{
    int last_cauldron_index = 0;
    int j = 1;
    while (input[j])
    {
        if (input[j] == 'b' && input[j + 1] == 'l' && input[j + 2] == 'u')
        {
            game->cauldrons[input[0] - 49].colors[last_cauldron_index] = 1;
            if (input[j - 3] == 32)
            {
                game->cauldrons[input[0] - 49].cards[last_cauldron_index++] = input[j - 2] - 48;
            }
            else
            {
                game->cauldrons[input[0] - 49].cards[last_cauldron_index++] = (input[j - 3] - 48) * 10 + input[j - 2] - 48;
            }
        
        }
        else if (input[j] == 'r' && input[j + 1] == 'e' && input[j + 2] == 'd')
        {
            game->cauldrons[input[0] - 49].colors[last_cauldron_index] = 2;
            if (input[j - 3] == 32)
            {
                game->cauldrons[input[0] - 49].cards[last_cauldron_index++] = input[j - 2] - 48;
            }
            else
            {
                game->cauldrons[input[0] - 49].cards[last_cauldron_index++] = (input[j - 3] - 48) * 10 + input[j - 2] - 48;
            }
        }
        else if (input[j] == 'y' && input[j + 1] == 'e' && input[j + 2] == 'l')
        {
            game->cauldrons[input[0] - 49].colors[last_cauldron_index] = 4;
            if (input[j - 3] == 32)
            {
                game->cauldrons[input[0] - 49].cards[last_cauldron_index++] = input[j - 2] - 48;
            }
            else
            {
                game->cauldrons[input[0] - 49].cards[last_cauldron_index++] = (input[j - 3] - 48) * 10 + input[j - 2] - 48;
            }
        }
        else if (input[j] == 'v' && input[j + 1] == 'i' && input[j + 2] == 'o')
        {
            game->cauldrons[input[0] - 49].colors[last_cauldron_index] = 3;
            if (input[j - 3] == 32)
            {
                game->cauldrons[input[0] - 49].cards[last_cauldron_index++] = input[j - 2] - 48;
            }
            else
            {
                game->cauldrons[input[0] - 49].cards[last_cauldron_index++] = (input[j - 3] - 48) * 10 + input[j - 2] - 48;
            }
        }
        else if (input[j] == 'w' && input[j + 1] == 'h' && input[j + 2] == 'i')
        {
            game->cauldrons[input[0] - 49].colors[last_cauldron_index] = 5;
            if (input[j - 3] == 32)
            {
                game->cauldrons[input[0] - 49].cards[last_cauldron_index++] = input[j - 2] - 48;
            }
            else
            {
                game->cauldrons[input[0] - 49].cards[last_cauldron_index++] = (input[j - 3] - 48) * 10 + input[j - 2] - 48;
            }
        }
        else if (input[j] == 'b' && input[j + 1] == 'l' && input[j + 2] == 'a')
        {
            game->cauldrons[input[0] - 49].colors[last_cauldron_index] = 6;
            if (input[j - 3] == 32)
            {
                game->cauldrons[input[0] - 49].cards[last_cauldron_index++] = input[j - 2] - 48;
            }
            else
            {
                game->cauldrons[input[0] - 49].cards[last_cauldron_index++] = (input[j - 3] - 48) * 10 + input[j - 2] - 48;
            }
        }
        else if (input[j] == 'g' && input[j + 1] == 'r' && input[j + 2] == 'e')
        {
            game->cauldrons[input[0] - 49].colors[last_cauldron_index] = 0;
            if (input[j - 3] == 32)
            {
                game->cauldrons[input[0] - 49].cards[last_cauldron_index++] = input[j - 2] - 48;
            }
            else
            {
                game->cauldrons[input[0] - 49].cards[last_cauldron_index++] = (input[j - 3] - 48) * 10 + input[j - 2] - 48;
            }
        }
        j++;
    }
}

void simple_move(Game* game, int cauldron_values[MAXCAULDRONS])
{

    int j = 0;
    int first_free_index = 0;
    int first_free_color = 0;
    int cauldron_colors[MAXCAULDRONS] = { 0 };
    int cauldron_index = 0;
    int card_value = 0;
    while (j < MAXDECKSIZE) 
    {
        if (game->players[game->active_index-1].hand.cards[j] != 0)
        {
            first_free_index = j;
            first_free_color = game->players[game->active_index-1].hand.colors[j];
            card_value = game->players[game->active_index - 1].hand.cards[first_free_index];
            break;
        }
        j++;
    }

    j = 0;
    int i = 0;
    while (j < game->number_of_cauldrons)
    {
        i = 0;
        while (i < MAXDECKUPDATED )
        {
            if (game->cauldrons[j].colors[i] != 0) 
            {
                cauldron_colors[j] = game->cauldrons[j].colors[i];
            }
            i++;
        }
        
        j++;
    }
    i = 0;
    j = 0;
    while (j < game->number_of_cauldrons)
    {
        if (first_free_color == 0 && cauldron_values[j] + game->players[game->active_index-1].hand.cards[first_free_index] < game->explosion_threshold)
        {
            
            while (i < MAXDECKUPDATED)
            {
                if (game->cauldrons[j].cards[i] == 0)
                {
                    
                    game->cauldrons[j].cards[i] = card_value;
                    game->cauldrons[j].colors[i] = first_free_color;
                    game->players[game->active_index-1].hand.cards[first_free_index] = 0;
                    game->players[game->active_index-1].hand.colors[first_free_index] = 0;
                    game->players[game->active_index - 1].handcards--;
                    return;
                }
                i++;
            }
        }
        else if (first_free_color != 0 && j == game->number_of_cauldrons - 1 )
        {
            while (i < game->number_of_cauldrons)
            {
                if (cauldron_colors[i] == 0)
                {
                    for (int k = 0; k < MAXDECKUPDATED; k++)
                    {
                        if (game->cauldrons[i].cards[k] == 0)
                        {
                            
                            game->cauldrons[i].cards[k] = card_value;
                            game->cauldrons[i].colors[k] = first_free_color;
                            game->players[game->active_index - 1].hand.cards[first_free_index] = 0;
                            game->players[game->active_index - 1].hand.colors[first_free_index] = 0;
                            game->players[game->active_index - 1].handcards--;
                            return;
                        }
                        
                    }
                }
                i++;
            }
        }
        else if (first_free_color == cauldron_colors[j])
        {
            while (i < MAXDECKUPDATED)
            {
                if (game->cauldrons[j].cards[i] == 0)
                {
                    
                    game->cauldrons[j].cards[i] = card_value;
                    game->cauldrons[j].colors[i] = first_free_color;
                    game->players[game->active_index - 1].hand.cards[first_free_index] = 0;
                    game->players[game->active_index - 1].hand.colors[first_free_index] = 0;
                    game->players[game->active_index - 1].handcards--;
                    return;
                }
                i++;
            }
        }

        j++;

    }
}

void print_gamestate(Game* game)
{
    std::cout << "active player = " << game->active_index << std::endl;
    std::cout << "players number = " << game->number_of_players << std::endl;
    std::cout << "explosion threshold = " << game->explosion_threshold << std::endl;
    for (int i = 0; i < game->number_of_players; i++)
    {
        std::cout << i + 1 << " player hand cards:";
        for (int j = 0; j < MAXDECKUPDATED; j++)
        {
            if (game->players[i].hand.cards[j] != 0)
            {
                std::cout <<" "<< game->players[i].hand.cards[j] << " " << COLORS[game->players[i].hand.colors[j]];
            }
            
        }
        std::cout << std::endl;
        std::cout << i + 1 << " player deck cards:";
        for (int j = 0; j < MAXDECKUPDATED; j++)
        {
            if (game->players[i].deck.cards[j] != 0)
            {
                std::cout << " " << game->players[i].deck.cards[j] << " " << COLORS[game->players[i].deck.colors[j]] << " ";
            }
            
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < game->number_of_cauldrons; i++)
    {
        std::cout << i + 1 << " pile cards:";
        for (int j = 0; j < MAXDECKSIZE; j++)
        {
            if (game->cauldrons[i].cards[j] != 0)
            {
                std::cout << " " << game->cauldrons[i].cards[j] << " " << COLORS[game->cauldrons[i].colors[j]];

            }
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    
}


void cauldron_explosion(Game* game, int cauldrons[MAXCAULDRONS])
{
    int cards_transferred = 0;
    for (int i = 0; i < MAXCAULDRONS; i++) 
    {
        int cauldron_sum = 0;
        for (int j = 0; j < MAXDECKUPDATED; j++)
        {
            if (game->cauldrons[i].cards[j] != 0)
            {
                cauldron_sum += game->cauldrons[i].cards[j];
            }
        }
        if (cauldron_sum > game->explosion_threshold)
        {
            int j = 0;
            while (game->cauldrons[i].cards[j] != 0)
            {
                if (game->active_index > 1)
                { 
                    game->players[game->active_index - 2].deck.cards[game->players[game->active_index - 2].deckcards + j] = game->cauldrons[i].cards[j];
                    game->players[game->active_index - 2].deck.colors[game->players[game->active_index - 2].deckcards + j] = game->cauldrons[i].colors[j];
                    game->cauldrons[i].cards[j] = 0;
                    game->cauldrons[i].colors[j] = 0;
                    j++;
                    cards_transferred++;
                    
                    
                }
                
                else if (game->active_index == 1)
                {
                    game->players[game->number_of_players-1].deck.cards[game->players[game->number_of_players - 1].deckcards + j] = game->cauldrons[i].cards[j];
                    game->players[game->number_of_players-1].deck.colors[game->players[game->number_of_players - 1].deckcards + j] = game->cauldrons[i].colors[j];
                    game->cauldrons[i].cards[j] = 0;
                    game->cauldrons[i].colors[j] = 0;
                    j++;
                    cards_transferred++;
                    
                    
                }
                if (game->active_index > 1)
                {
                    game->players[game->active_index - 2].deckcards += cards_transferred;
                }
                else if (game->active_index == 1)
                {
                    game->players[game->number_of_players - 1].deckcards += cards_transferred;
                }
            }
            return;
        }
    }
}

void round_end(Game* game)
{
    int card_scores[MAXPLAYERS][MAXCAULDRONS+1] = { 0 };
    for (int i = 0; i < game->number_of_players; i++)
    {
        if (game->players[i].handcards != 0)
        {
            
            return;
        }
    }
    game->end = 1;
    for (int i = 0; i < game->number_of_players; i++)
    {
        for (int j = 0; j < MAXDECKUPDATED; j++) 
        {
            if (game->players[i].deck.cards[j] != 0)
            {
                card_scores[i][game->players[i].deck.colors[j]]++;
            }
        }
    }

    for (int i = 0; i < game->number_of_players; i++)
    {
        for (int j = 0; j < MAXDECKUPDATED; j++)
        {
            
            if (game->players[i].deck.cards[j] != 0)
            {
                if (game->players[i].deck.colors[j] == 0)
                {
                    game->players[i].points+=2;
                }
                else 
                {
                    game->players[i].points++;
                }
            }
        }
    }
    for (int i = 0; i < MAXCAULDRONS + 1; i++)
    {
        int tempmax = card_scores[0][i];
        int tempindex = 0;
        int appearanceToken = 0;

        for (int j = 0; j < game->number_of_players; j++)
        {
            if (i == 0)
            {
                card_scores[j][i] = 0;
            } 
            if (card_scores[j][i] > tempmax)
            {
                tempmax = card_scores[j][i];
                appearanceToken = 1;
            }
            else if (card_scores[j][i] == tempmax)
            {
                appearanceToken++;
            }

        }
        for (int j = 0; j < game->number_of_players; j++)
        {
            if (card_scores[j][i] < tempmax)
            {
                card_scores[j][i] = 0;
            }
            else if ((card_scores[j][i] = tempmax) && appearanceToken > 1)
            {
                card_scores[j][i] = 0;
            }
        }
    }

    for (int j = 0; j < MAXCAULDRONS + 1; j++)
    {
        
        for (int i = 0; i < game->number_of_players; i++)
        {
            if (card_scores[i][j] != 0)
            {
                game->players[i].points -= card_scores[i][j];
                std::cout << "Na kolor " << COLORS[j] << " odporny jest gracz " << i+1 << std::endl;
            }

        }
       
    }

    for (int i = 0; i < game->number_of_players; i++)
    {
        std::cout << "Wynik gracza " << i + 1 << " = " << game->players[i].points << std::endl;
    }
}

void save_gamestate(Game* game, FILE* fp)
{
    fprintf(fp, "active player = %d \n", game->active_index);
    fprintf(fp, "players number = %d \n", game->number_of_players);
    fprintf(fp, "explosion threshold = %d \n", game->explosion_threshold);
    for (int i = 0; i < game->number_of_players; i++)
    {
        fprintf(fp, "%d player hand cards: ", i + 1);
        for (int j = 0; j < game->players[i].handcards; j++)
        {
            if (game->players[i].hand.cards[j] != 0)
            {
                fprintf(fp, "%d %s ", game->players[i].hand.cards[j], COLORS[game->players[i].hand.colors[j]]);
            }
        }
        fprintf(fp, "\n");
        fprintf(fp, "%d player deck cards: ", i + 1);
        for (int j = 0; j < game->players[i].deckcards; j++)
        {
            if (game->players[i].hand.cards[j] != 0)
            {
                fprintf(fp, "%d %s ", game->players[i].deck.cards[j], COLORS[game->players[i].deck.colors[j]]);
            }
            
        }
        fprintf(fp, "\n");
    }
    for (int i = 0; i < game->number_of_cauldrons; i++)
    {
        fprintf(fp, "%d pile cards: ", i + 1);
        for (int j = 0; j < game->cauldron_capacity[i]; j++)
        {
            if (game->cauldrons[i].cards[j] != 0)
            {
                fprintf(fp, "%d %s ", game->cauldrons[i].cards[j], COLORS[game->cauldrons[i].colors[j]]);

            }
        }
        fprintf(fp, "\n");
    }
}




void small_move(Game* game)
{
    int cauldron_values[MAXCAULDRONS] = { 0 };
    int cauldron_colors[MAXCAULDRONS] = { 0 };
    int lowest_handcards[MAXCAULDRONS + 1] = { 20, 20, 20, 20, 20, 20, 20 };
    for (int i = 0; i < game->number_of_cauldrons; i++)
    {
        for (int j = 0; j < MAXDECKUPDATED; j++)
        {
            if (game->cauldrons[i].colors[j] != 0)
            {
                game->cauldron_colors[i] = game->cauldrons[i].colors[j];

            }
        }

    }
    for (int i = 0; i < game->number_of_cauldrons; i++)
    {
        for (int j = 0; j < MAXDECKUPDATED; j++)
        {
            cauldron_values[i] += game->cauldrons[i].cards[j];
        }
    }
    int smallest_number = 20;
    int smallest_color = 0;
    int color_index = 0;
    int smallest_number_occurences = 0;
    int smallest_index = 0;
    int smallest_index_color = 0;
    for (int i = 0; i < MAXDECKUPDATED + 1; i++)
    {

        if (game->players[game->active_index - 1].hand.cards[i] < lowest_handcards[game->players[game->active_index - 1].hand.colors[i]] && game->players[game->active_index - 1].hand.cards[i] != 0)
        {
            lowest_handcards[game->players[game->active_index - 1].hand.colors[i]] = game->players[game->active_index - 1].hand.cards[i];
        }


    }
    for (int i = 0; i < MAXCAULDRONS + 1; i++)
    {
        if (lowest_handcards[i] < smallest_number)
        {
            smallest_number = lowest_handcards[i];
            smallest_color = i;
        }
    }
    ;
    for (int i = 0; i < MAXCAULDRONS + 1; i++)
    {
        if (lowest_handcards[i] == smallest_number)
        {
            smallest_number_occurences++;
        }
    }
    if (smallest_color == 0)
    {
        int cauldron_min = game->explosion_threshold;
        int cauldron_id = 0;
        for (int i = 0; i < game->number_of_cauldrons; i++)
        {
            if (cauldron_min > cauldron_values[i])
            {
                cauldron_min = cauldron_values[i];
                cauldron_id = i;
            }
        }
        for (int i = 0; i < MAXDECKUPDATED; i++)
        {
            if (game->players[game->active_index - 1].hand.cards[i] == smallest_number && smallest_number + cauldron_values[cauldron_id] < game->explosion_threshold)
            {
                for (int j = 0; j < MAXDECKUPDATED; j++)
                {
                    if (game->cauldrons[cauldron_id].cards[j] == 0)
                    {
                        game->cauldrons[cauldron_id].cards[j] = game->players[game->active_index - 1].hand.cards[i];
                        game->players[game->active_index - 1].hand.cards[i] = 0;
                        game->players[game->active_index - 1].handcards--;
                        return;
                    }
                }
            }
        }


    }
    if (smallest_number_occurences == 1)
    {
        for (int j = 0; j < game->number_of_cauldrons; j++)
        {
            if (game->cauldron_colors[j] == smallest_color || game->cauldron_colors[j] == 0)
            {
                for (int i = 0; i < MAXDECKUPDATED; i++)
                {
                    if (game->players[game->active_index - 1].hand.cards[i] == smallest_number)
                    {
                        for (int k = 0; k < MAXDECKUPDATED; k++)
                        {
                            if (game->cauldrons[j].cards[k] == 0)
                            {
                                smallest_index = i;
                                smallest_index_color = game->players[game->active_index - 1].hand.colors[i];
                                if (smallest_number + cauldron_values[j] < game->explosion_threshold)
                                {
                                    game->cauldrons[j].cards[k] = smallest_number;
                                    game->cauldrons[j].colors[k] = smallest_index_color;
                                    game->players[game->active_index - 1].hand.cards[smallest_index] = 0;
                                    game->players[game->active_index - 1].hand.colors[smallest_index] = 0;
                                    game->players[game->active_index - 1].handcards--;
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {

        int smallest_cauldron_id = 0;
        int smallest_cauldron_value = game->explosion_threshold;
        int smallest_cauldron_color = 0;
        int index = 0;
        for (int i = 0; i < MAXCAULDRONS + 1; i++)
        {
            if (lowest_handcards[i] != smallest_number)
            {
                lowest_handcards[i] = 0;
            }
        }
        for (int i = 0; i < MAXCAULDRONS + 1; i++)
        {
            int color_appearance = 0;
            if (lowest_handcards[i] != 0)
            {
                for (int j = 0; j < MAXCAULDRONS; j++)
                {
                    if (game->cauldron_colors[j] == i)
                    {
                        color_appearance++;
                        if (cauldron_values[j] < smallest_cauldron_value)
                        {
                            smallest_cauldron_value = cauldron_values[j];
                            smallest_cauldron_id = j;
                            smallest_cauldron_color = game->cauldron_colors[j];
                            index = i;
                        }
                    }
                    else if (color_appearance == 0)
                    {
                        for (int k = 0; k < MAXCAULDRONS; k++)
                        {
                            if (cauldron_values[k] < smallest_cauldron_value)
                            {
                                smallest_cauldron_value = cauldron_values[k];
                                smallest_cauldron_id = k;
                                smallest_cauldron_color = game->cauldron_colors[k];
                                index = i;
                            }
                        }
                    }

                }
            }
        }

        for (int i = 0; i < MAXDECKUPDATED; i++)
        {
            if (game->players[game->active_index - 1].hand.cards[i] == smallest_number && game->players[game->active_index - 1].hand.colors[i] == index)
            {
                smallest_index = i;
                smallest_index_color = game->players[game->active_index - 1].hand.colors[i];
            }
        }



        for (int i = 0; i < MAXDECKUPDATED; i++)
        {
            if (game->cauldrons[smallest_cauldron_id].cards[i] != 0 && smallest_number + cauldron_values[smallest_cauldron_id] < game->explosion_threshold)
            {
                game->cauldrons[smallest_cauldron_id].cards[i] = smallest_number;
                game->cauldrons[smallest_cauldron_id].colors[i] = smallest_index_color;
                game->players[game->active_index - 1].hand.cards[smallest_index] = 0;
                game->players[game->active_index - 1].hand.colors[smallest_index] = 0;
                game->players[game->active_index - 1].handcards--;
                return;
            }
        }


    }

    
    int hand_max = 0;
    int hand_max_id = 0;
    int hand_max_color = 0;
    for (int i = 0; i < MAXDECKUPDATED; i++)
    {
        if (game->players[game->active_index - 1].hand.cards[i] > hand_max)
        {
            hand_max = game->players[game->active_index - 1].hand.cards[i];
            hand_max_id = i;
            hand_max_color = game->players[game->active_index - 1].hand.colors[i];
        }
    }
   

    if (hand_max_color == 0)
    {
        int smallest_cauldron_value = game->explosion_threshold;
        int smallest_cauldron_id = 0;
        for (int j = 0; j < game->number_of_cauldrons; j++)
        {
            if (cauldron_values[j] < smallest_cauldron_value)
            {
                smallest_cauldron_value = cauldron_values[j];
                smallest_cauldron_id = j;
            }
        }
        for (int i = 0; i < MAXDECKUPDATED; i++)
        {
            if (game->cauldrons[smallest_cauldron_id].cards[i] == 0)
            {
                game->cauldrons[smallest_cauldron_id].cards[i] = hand_max;
                game->players[game->active_index - 1].hand.cards[hand_max_id] = 0;
                game->players[game->active_index - 1].handcards--;
                return;
            }
        }
    }
    for (int i = 0; i < game->number_of_cauldrons; i++)
    {

        if (game->cauldron_colors[i] == hand_max_color)
        {
            for (int j = 0; j < MAXDECKUPDATED; j++)
            {
                if (game->cauldrons[i].cards[j] == 0)
                {
                    game->cauldrons[i].cards[j] = hand_max;
                    game->cauldrons[i].colors[j] = hand_max_color;
                    game->players[game->active_index - 1].hand.cards[hand_max_id] = 0;
                    game->players[game->active_index - 1].hand.colors[hand_max_id] = 0;
                    game->players[game->active_index - 1].handcards--;
                    return;
                }
            }
        }

        if (i == game->number_of_cauldrons)
        {
            int smallest_cauldron_value = game->explosion_threshold;
            int smallest_cauldron_id = 0;
            for (int j = 0; j < game->number_of_cauldrons; j++)
            {
                if (cauldron_values[j] < smallest_cauldron_value && game->cauldron_colors[j] == 0)
                {
                    smallest_cauldron_value = cauldron_values[j];
                    smallest_cauldron_id = j;
                }
            }
            for (int j = 0; j < MAXDECKUPDATED; j++)
            {
                if (game->cauldrons[smallest_cauldron_id].cards[j] != 0)
                {
                    game->cauldrons[smallest_cauldron_id].cards[j] = hand_max;
                    game->cauldrons[smallest_cauldron_id].colors[j] = hand_max_color;
                    game->players[game->active_index - 1].hand.cards[hand_max_id] = 0;
                    game->players[game->active_index - 1].hand.colors[hand_max_id] = 0;
                    game->players[game->active_index - 1].handcards--;
                    return;
                }

                
            }

        }
        
    }


    
}






int main(int argc, char* argv[])
{

    Game game;
    
    
    FILE *fp = fopen(argv[1], "w");
    game.number_of_players = atoi(argv[2]);
    game.number_of_cauldrons = atoi(argv[3]);
    game.explosion_threshold = atoi(argv[4]);
    game.number_of_greens = atoi(argv[5]);
    game.value_of_greens = atoi(argv[6]);
    game.number_of_cards = atoi(argv[7]);
    
    for (int i = 0; i < game.number_of_greens; i++)
    {
        game.main_deck.cards[i] = game.value_of_greens;
    }
    
    int indextoken = 0;
    for (int j = 0; j < game.number_of_cauldrons; j++)
    {
        
        for (int i = 0; i < game.number_of_cards; i++)
        {
            game.main_deck.cards[game.number_of_greens + indextoken] = atoi(argv[8 + i]);
            game.main_deck.colors[game.number_of_greens + indextoken] = j+1;
            indextoken++;

        }
    }
    deal_cards(&game);
    print_gamestate(&game);
    save_gamestate(&game, fp);
    /*for (int i = 0; i < game.number_of_cauldrons*game.number_of_cards + game.number_of_greens; i++)
    {
        std::cout << game.main_deck.cards[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < game.number_of_cauldrons * game.number_of_cards + game.number_of_greens; i++)
    {
        std::cout << game.main_deck.colors[i] << " ";
    }
    */


    fclose(fp);
    FILE* fpr = fopen("game_state.txt", "r");
    
   /*
    THIS IS NEEDED FOR TASKS 1/2
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

    int card_values[MAXDECKSIZE+1] ={0};

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

    */
    int cauldrons[MAXCAULDRONS] = { 0 };
    int cauldrons_values[MAXCAULDRONS] = { 0 };
    int cauldrons_colors[MAXCAULDRONS][CARDSINCAULDRON] = { 0 };
    char input[MAXINPUTSIZE];
    int cards[2 * MAXPLAYERS] = { 0 };
    int colorcounter[MAXCAULDRONS] = { 0 };
    int colorcheck[MAXCAULDRONS][MAXDECKSIZE] = { 0 };
    int playercards[MAXPLAYERS] = { 0 };
    while (game.end == 0)
    {
        while (fgets(input, MAXINPUTSIZE, fpr))
        {
            if (input[0] == '\n')
            {
                break; //end loop if you encounter end of line symbol as the first letter of a line
            }
            if (input[0] == 'a')
            {
                game.active_index = input[16] - 48;
            }
            if (input[0] == 'p')
            {
                game.number_of_players = input[17] - 48; //get amount of players from user input/save file
            }
            if (input[0] == 'e')
            {
                if (input[24] - 48 >= 0 && input[24] - 48 <= 9)
                {
                    game.explosion_threshold = (input[22] - 48) * 100 + (input[23] - 48) * 10 + input[24] - 48;


                }
                else
                {
                    game.explosion_threshold = (input[22] - 48) * 10 + (input[23] - 48);

                }
            }

            //count_cards(input, game.number_of_cauldrons, cards, cauldrons);
            color_count(colorcounter, colorcheck, input);
            player_cards_count(input, &game);
            green_check(input, game);


            if (input[9] == 'h')
            {
                players_read_cards(input, &game, 1, 0);
            }
            else if (input[9] == 'd')
            {
                players_read_cards(input, &game, 1, 1);
            }


            if (input[4] == 'l')
            {
                cauldron_read_cards(input, &game);
                //game.number_of_cauldrons++;
                int i = 1;
                int j = 0;
                while (input[i]) {

                    if (input[i] > '0' && input[i] <= '9')
                    {
                        int a = input[i] - 48;
                        if (input[i + 1] == 32) {

                            cauldrons_values[input[0] - 49] += (input[i] - 48);
                            cauldron_color_check(input, cauldrons_colors, i + 2, j++);
                        }
                        else
                        {
                            cauldrons_values[input[0] - 49] += (input[i] - 48) * 10 + (input[i + 1] - 48);
                            cauldron_color_check(input, cauldrons_colors, i + 3, j++);
                            i++;
                        }


                    }





                    i++;
                }
            }



        }



        // FOR TASK 4A
        int card_check = 1;
        for (int i = 1; i < MAXCAULDRONS; i++)
        {
            if (colorcounter[0] != colorcounter[i] && colorcounter[i] != 0)
            {
                card_check = 0;
            }
        }


        for (int i = 0; i < game.number_of_players; i++)
        {
            playercards[i] = game.players[i].handcards;
        }
        int gamestate = 0;
        int card_differential = card_checker(playercards, game.number_of_players, game.active_index);
        if (card_differential != 0)
        {
            std::cout << "The number of players cards on hand is wrong" << std::endl;
            gamestate++;
        }


        //GAMESTATE CHECKING FOR TASK 6
        for (int i = 0; i < MAXCAULDRONS; i++)
        {
            for (int j = 1; j < CARDSINCAULDRON; j++)
            {
                if (cauldrons_colors[i][0] != cauldrons_colors[i][j] && cauldrons_colors[i][j] != 0)
                {
                    std::cout << "Two different colors were found on the " << i + 1 << " pile " << std::endl;
                    gamestate++;
                    break;
                }
            }
        }


        for (int i = 0; i < MAXCAULDRONS; i++)
        {
            if (cauldrons_values[i] >= game.explosion_threshold)
            {
                std::cout << "Pile number " << i + 1 << " should explode earlier" << std::endl;
                gamestate++;
            }
        }
        if (gamestate == 0)
        {

            std::cout << "Current state of the game is ok " << std::endl;
        }

        round_end(&game);
        fclose(fpr);
        FILE* fpw = fopen("game_state.txt", "w");
        if (gamestate != 0)
        {
            return 0;
        }
        if (game.end == 1)
        {
            save_gamestate(&game, fpw);
            fclose(fpw);
            return 0;
        }
        else
        {

            small_move(&game);
            
            //simple_move(&game, cauldrons_values);
            game.active_index = active_id(game.active_index, game.number_of_players);
            cauldron_explosion(&game, cauldrons);
            print_gamestate(&game);
            save_gamestate(&game, fpw);
            fclose(fpw);
            
            for (int i = 0; i < game.number_of_cauldrons; i++)
            {
                game.cauldron_capacity[i] = 0;
                for (int j = 0; j < MAXDECKUPDATED; j++)
                {
                    if (game.cauldrons[i].cards[j] != 0)
                    {
                        game.cauldron_capacity[i]++;
                    }
                }
            }
            for (int i = 0; i < game.number_of_players; i++)
            {
                game.players[i].deckcards = 0;
                for (int j = 0; j < MAXDECKUPDATED; j++)
                {
                    if (game.players[i].deck.cards[j] != 0)
                    {
                        game.players[i].deckcards++;
                    }
                }
            }
            for (int i = 0; i < game.number_of_players; i++)
            {
                game.players[i].handcards = 0;
                for (int j = 0; j < MAXDECKUPDATED; j++)
                {
                    if (game.players[i].hand.cards[j] != 0)
                    {
                        game.players[i].handcards++;
                    }
                }
            }






            //TASK 5
            for (int i = 0; i < MAXCAULDRONS; i++)
            {
                qsort(colorcheck[i], 0, MAXDECKSIZE - 1);
            }
            int cardsdifferent = 0;
            for (int i = 0; i < game.number_of_cauldrons - 1; i++)
            {
                for (int j = 0; j < MAXDECKSIZE; j++)
                {
                    if (colorcheck[i][j] != colorcheck[i + 1][j])
                    {
                        cardsdifferent = 1;
                    }
                }
            }

            if (cardsdifferent == 0) {
                std::cout << "The values of cards of all colors are identical:" << std::endl;
                for (int i = 0; i < MAXDECKSIZE; i++)
                {
                    if (colorcheck[0][i] != 0) {
                        std::cout << colorcheck[0][i] << " ";
                    }
                }
                std::cout << std::endl;
            }
            else
            {
                std::cout << "The values of cards of all colors are not identical:" << std::endl;
                for (int i = 0; i < game.number_of_cauldrons; i++)
                {
                    std::cout << COLORS[i] << " cards values: ";
                    for (int j = 0; j < MAXDECKSIZE; j++)
                    {
                        if (colorcheck[i][j] != 0)
                        {
                            std::cout << colorcheck[i][j] << " ";
                        }
                    }
                    std::cout << std::endl;
                }
            }




            //TASK 4A
            if (card_check == 1)
            {
                std::cout << "The number cards of all colors is equal: " << colorcounter[0] << std::endl;
            }
            else
            {
                std::cout << "At least two colors with a different number of cards were found:" << std::endl;
                for (int j = 0; j < MAXCAULDRONS; j++)
                {
                    if (colorcounter[j] != 0)
                    {
                        std::cout << COLORS[j] << " cards are " << colorcounter[j] << std::endl;

                    }
                }
            }



            //SOLUTION TO TASK 3 ON STOS
            for (int i = 0; i < game.number_of_players; i++)
            {
                std::cout << i + 1 << " player has " << game.players[i].handcards << " cards on hand" << std::endl;
                std::cout << i + 1 << " player has " << game.players[i].deckcards << " cards in front of him" << std::endl;
            }

            for (int i = 0; i < game.number_of_cauldrons; i++)
            {
                std::cout << "there are " << game.cauldron_capacity[i]<< " cards on " << i + 1 << " pile " << std::endl;
            }



        
             //THIS IS REQUIRED TO PASS TASK 4A
            if(game.value_of_greens == -1)
            {
                std::cout << "Different green cards values occurred";
            }
            else if (game.number_of_greens == 0)
            {
                std::cout << "Green cards does not exist";
            }
            else
            {
                std::cout << "Found " << game.number_of_greens << " green cards, all with " << game.value_of_greens << " value" <<std::endl;
            }

            std::cout << std::endl << std::endl;
        
        }
    }
    return 0;
}
