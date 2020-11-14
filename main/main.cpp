#include <iostream>
#include "Cauldron.cpp"
#include "Deck.cpp"
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



int main()
{
    int number_of_cauldrons;
    std::cin >> number_of_cauldrons;
    assert((number_of_cauldrons >= 1) && (number_of_cauldrons <= 6));
    
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
    for (int i = 0; i < number_of_greens; i++) {
        std::cout << value_of_greens;
        std::cout <<" green ";
    }
    
    qsort(card_values, 0, number_of_cards - 1);
  
    
 for (int i = 0; i < number_of_cauldrons; i++) {
        for (int j = 0; j < number_of_cards; j++) {
            std::cout << " ";
            std::cout << card_values[j];
            std::cout << " ";
            std::cout << COLORS[i];
            std::cout << " ";
        }
    }
    
}
