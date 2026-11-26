#include <stdio.h>
#include <stdlib.h>
#include "menu.h"


struct Flat* DisplayFlats(int num) {
    struct Flat* flats = malloc(num * sizeof(struct Flat));

    if (flats == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    for (int i = 0; i < num; i++) {
        printf("Enter rooms for flat %d: ", i + 1);

        if (scanf("%d", &flats[i].rooms) != 1) {
            printf("Invalid input!\n");
            free(flats);
            return NULL;
        }
    }

    printf("\n********** ROOMS **********\n");

    for (int i = 0; i < num; i++) {
        printf("%d rooms\n", flats[i].rooms);
    }

    return flats;
}


void DisplayAll(struct Flat* flats, int num) {
    printf("\n********** ALL FLATS **********\n");

    for (int i = 0; i < num; i++) {
        printf("Flat number %d: %d rooms\n",
               i + 1, flats[i].rooms);
    }
}


int main(void) {
    int num = 0;
    int condition = 0;

    struct Flat* flats = NULL;

    do {
        printf("\n*************** MENU ***************\n");
        printf("1: Display Flats\n");
        printf("2: Display All\n");
        printf("3: EXIT\n");

        printf("\nEnter your choice: ");

        if (scanf("%d", &condition) != 1) {
            printf("Invalid input!\n");
            free(flats);
            return 1;
        }

        switch (condition) {

            case 1: {
                int newNum;

                printf("Enter the number of flats: ");

                if (scanf("%d", &newNum) != 1 || newNum <= 0) {
                    printf("Invalid number of flats!\n");
                    break;
                }

                struct Flat* newFlats = DisplayFlats(newNum);

                if (newFlats != NULL) {
                    free(flats);
                    flats = newFlats;
                    num = newNum;
                }

                break;
            }

            case 2:
                if (flats != NULL) {
                    DisplayAll(flats, num);
                } else {
                    printf("Please enter flats first!\n");
                }

                break;

            case 3:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid Choice!\n");
                break;
        }

    } while (condition != 3);

    free(flats);

    return 0;
}
