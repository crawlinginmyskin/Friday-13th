#include <iostream>
#include "Cauldron.cpp"
#include "Deck.cpp"
#include "Player.cpp"
#include "Game.cpp"
//#include <cassert>



#define MAXINPUTSIZE 10000
#define MAXCAULDRONS 6

const char COLORS[MAXCAULDRONS+1][7] = { "blue", "red", "violet", "yellow", "white", "black", "green" };

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



void fill_greens(Card deck[MAXDECKUPDATED], int number_of_greens, int green_value)
{
	//fil a green_cards array in a Deck structure with values specified by the user 
    for (int i = 0; i < number_of_greens; i++)
    {
        deck[i].value = green_value;
        //strcpy(deck[i].color, COLORS[6]);
    	
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
        while (card_values[i] != 0)
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
    int number_of_cards = 0;
    int last_dealt = 0;
	
	for(int i = 0; i < MAXDECKSIZE; i++)
	{
		if(game->main_deck.blue_cards[i] != 0)
		{
            number_of_cards++;
		}
	}

    
    for (int j = 0; j < number_of_greens; j++) 
    {
        game->players[j % game->number_of_players].hand.green_cards[j/ game->number_of_players] = game->main_deck.green_cards[j];
        last_dealt = j % game->number_of_players;
    }

    
    
    for (int j = 0 ; j < number_of_cards * game->number_of_cauldrons; j++) 
    {
        last_dealt = active_id(last_dealt, game->number_of_players);
        int color =  j / number_of_cards;
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

void count_cards(Game* game)
{
    int count_cards[MAXPLAYERS * 2] = {0};
	for (int i =0; i < game->number_of_players; i++)
	{
        for(int j=0; j<MAXDECKSIZE; j++)
        {
	        if(game->players[i].hand.blue_cards[j]!=0)
	        {
                count_cards[2 * i]++;
	        }
            if (game->players[i].hand.red_cards[j] != 0)
            {
                count_cards[2 * i]++;
            }
            if (game->players[i].hand.violet_cards[j] != 0)
            {
                count_cards[2 * i]++;
            }
            if (game->players[i].hand.yellow_cards[j] != 0)
            {
                count_cards[2 * i]++;
            }
            if (game->players[i].hand.white_cards[j] != 0)
            {
                count_cards[2 * i]++;
            }
            if (game->players[i].hand.black_cards[j] != 0)
            {
                count_cards[2 * i]++;
            }
            if (game->players[i].deck.blue_cards[j] != 0)
            {
                count_cards[(2 * i) +1]++;
            }
            if (game->players[i].deck.red_cards[j] != 0)
            {
                count_cards[(2 * i) + 1]++;
            }
            if (game->players[i].deck.violet_cards[j] != 0)
            {
                count_cards[(2 * i) + 1]++;
            }
            if (game->players[i].deck.yellow_cards[j] != 0)
            {
                count_cards[(2 * i) + 1]++;
            }
            if (game->players[i].deck.white_cards[j] != 0)
            {
                count_cards[(2 * i) + 1]++;
            }
            if (game->players[i].deck.black_cards[j] != 0)
            {
                count_cards[(2 * i) + 1]++;
            }
        	if (game->players[i].hand.green_cards[j] != 0)
        	{
                count_cards[2 * i]++;
        	}
        	if(game->players[i].deck.green_cards[j] !=0)
        	{
                count_cards[(2 * i) + 1]++;
        	}
        }
        std::cout << i+1 << " Player has " << count_cards[2 * i] << " cards in hand" << std::endl;
        std::cout << i+1 << " Player has " << count_cards[(2 * i) + 1] << " cards in front of him" << std::endl;
		
	}
}

void green_check(char input[MAXINPUTSIZE], Game &game)
{
    int i = 0;
	while(input[i])
	{
		if(input[i] == 'g')
        {
            if (game.value_of_greens == 0 && input[i-3] == 32) 
            {
                game.value_of_greens = input[i - 2] - 48;
            }
            else if (game.value_of_greens == 0 && input[i-3] != 32)
            {
                game.value_of_greens = ((input[i - 3] - 48) * 10) + (input[i - 2] - 48);
            }
            else if (game.value_of_greens != input[i - 2] - 48 && input[i-3] == 32)
            {
                game.value_of_greens = -1;
            }
            else if (input[i-3] != 32 && game.value_of_greens != ((input[i - 3] - 48) * 10) + (input[i - 2] - 48))
            {
                game.value_of_greens = -1;
            }
            
			
			game.number_of_greens++;
            
		}
        i++;
	}
}
/**/

void print_cauldrons(Game* game)
{
	for(int i = 0; i < game->number_of_cauldrons; i++)
	{
        std::cout << i+1 << " pile cards: "<<std::endl;
	}
}

void count_cards(char input[MAXINPUTSIZE], Game& game, int cards[2 * MAXPLAYERS], int cauldrons[MAXCAULDRONS] = { 0 })
{

    int playerToken = 0;
    int cardcounter = 0;
    if (input[0] >= '0' && input[0] <= '9') //
    {
        // green_check(input, game); this is required for passing TASK 4a
        if (input[3] == 'i') //pile card counting TASK 3b
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
            cauldrons[game.number_of_cauldrons++] = cardcounter;
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

void color_check(char input[MAXINPUTSIZE], int colorcheck[MAXCAULDRONS][MAXDECKSIZE], int j, int color )
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




int main()
{
    int active = 1;
    Game game;
    //Card main_deck[MAXDECKUPDATED];
    //game.number_of_greens = 4;
    //game.value_of_greens = 4;
    //fill_greens(main_deck, game.number_of_greens, game.value_of_greens);




   // std::cout << main_deck[0].value;



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
    char input[MAXINPUTSIZE];
    int cards[2 * MAXPLAYERS] = { 0 };
    int colorcounter[MAXCAULDRONS] = { 0 };
    int colorcheck[MAXCAULDRONS][MAXDECKSIZE] = { 0 };

    while (fgets(input, MAXINPUTSIZE, stdin))
    {
        if (input[0] == '\n')
        {
            break; //end loop if you encounter end of line symbol as the first letter of a line
        }
        if (input[0] == 'p')
        {
            game.number_of_players = input[17] - 48; //get amount of players from user input/save file
        }
        if (input[0] == 'e')
        {
            game.explosion_threshold = (input[22] - 48) * 10 + (input[23] - 48);
        }

        count_cards(input, game, cards, cauldrons);


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
    /*
    REQUIRED FOR TASK 4A
    int card_check = 1;
    for (int i = 1; i < MAXCAULDRONS; i++)
    {
        if (colorcounter[0] != colorcounter[i] && colorcounter[i] != 0)
        {
            card_check = 0;
        }
    }
    */
    for (int i = 0; i < MAXCAULDRONS; i++)
    {
        qsort(colorcheck[i], 0, MAXDECKSIZE - 1);
    }
    int cardsdifferent = 0;
    for (int i = 0; i < game.number_of_cauldrons-1; i++)
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
            std::cout<<std::endl;
        }
    }

    /*
    SOLUTION TO TASK 4A
    if (card_check==1)
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
    */
	
    /*
     SOLUTION TO TASK 3 ON STOS
	for (int i = 0; i < game.number_of_players ;i++)
	{
        std::cout << i + 1 << " player has " << cards[2 * i] << " cards on hand" << std::endl;
        std::cout << i + 1 << " player has " << cards[(2 * i) + 1] << " cards in front of him" << std::endl;
	}

    for (int i=0; i<game.number_of_cauldrons; i++)
    {
        std::cout << "there are " << cauldrons[i] << " cards on " << i + 1 << " pile " << std::endl;
    }
    
	*/

	/*
	 THIS IS REQUIRED TO PASS TASK 4A
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
        std::cout << "Found " << game.number_of_greens << " green cards, all with " << game.value_of_greens << " value";
    }
	*/
    /* SOLUTION TO TASKS 1/2 ON STOS
    print_deck(&game);
    print_cauldrons(&game);
    count_cards(&game);
    */
	
    return 0;
}
