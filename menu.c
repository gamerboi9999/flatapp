#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"
#include "bookflat.h"
#include "rent.h"
#include "searchflat.h"
#include "writeandread.h"

struct Flat* DisplayFlats(int num) {
    struct Flat *flats = calloc((size_t)num, sizeof *flats);

    if (flats == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    for (int i = 0; i < num; i++) {
        flats[i].number = i + 1;
        flats[i].booked = false;
        
        printf("\n--- Flat %d ---\n", i + 1);
        
        printf("Enter rooms: ");
        if (scanf("%d", &flats[i].rooms) != 1) {
            printf("Invalid input!\n");
            free(flats);
            return NULL;
        }
        
        printf("Enter tenant name: ");
        scanf(" %49[^\n]", flats[i].name);
        
        printf("Enter owner: ");
        scanf(" %49[^\n]", flats[i].owner);
        
        printf("Enter street: ");
        scanf(" %49[^\n]", flats[i].street);
        
        printf("Enter rent: ");
        if (scanf("%f", &flats[i].Rent) != 1) {
            printf("Invalid input!\n");
            free(flats);
            return NULL;
        }
    }

    printf("\n********** ROOMS **********\n");
    for (int i = 0; i < num; i++) {
        printf("Flat %d: %d rooms\n", flats[i].number, flats[i].rooms);
    }

    return flats;
}

void DisplayAll(struct Flat* flats, int num) {
    printf("\n********** ALL FLATS **********\n");
    for (int i = 0; i < num; i++) {
        printf("Flat number: %d | Rooms: %d | Tenant: %s | Owner: %s | Street: %s | Rent: %.2f | Booked: %s\n",
               flats[i].number, flats[i].rooms, flats[i].name, flats[i].owner, 
               flats[i].street, flats[i].Rent, flats[i].booked ? "Yes" : "No");
    }
}

int main(void) {
    int num = 0;
    int condition = 0;

    struct Flat* flats = NULL;

    do {
        printf("\n*************** MENU ***************\n");
        printf("1: Add Flats\n");
        printf("2: Display All\n");
        printf("3: Book Flat\n");
        printf("4: Calculate Rent\n");
        printf("5: Search Flat\n");
        printf("6: Save to File\n");
        printf("7: Load from File\n");
        printf("8: EXIT\n");
        printf("************************************\n");
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
                if (flats != NULL) {
                    BookFlat(flats, num);
                } else {
                    printf("Please enter flats first!\n");
                }
                break;

            case 4:
                if (flats != NULL) {
                    int flatIndex, months;
                    printf("Enter flat number: ");
                    if (scanf("%d", &flatIndex) != 1 || flatIndex < 1 || flatIndex > num) {
                        printf("Invalid flat number!\n");
                        break;
                    }
                    printf("Enter number of months: ");
                    if (scanf("%d", &months) != 1 || months < 1) {
                        printf("Invalid number of months!\n");
                        break;
                    }
                    float total = calculateRent(&flats[flatIndex - 1], months);
                    printf("Total rent for Flat %d over %d months: %.2f\n", flatIndex, months, total);
                } else {
                    printf("Please enter flats first!\n");
                }
                break;

            case 5:
                if (flats != NULL) {
                    char searchName[50];
                    printf("Enter tenant name to search: ");
                    scanf(" %49[^\n]", searchName);
                    SearchFlat(searchName, flats, num);
                } else {
                    printf("Please enter flats first!\n");
                }
                break;

            case 6:
                if (flats != NULL) {
                    WriteToFile(flats, num);
                } else {
                    printf("Please enter flats first!\n");
                }
                break;

            case 7:
                if (flats == NULL) {
                    printf("Enter maximum number of flats to load: ");
                    if (scanf("%d", &num) != 1 || num <= 0) {
                        printf("Invalid number!\n");
                        num = 0;
                        break;
                    }
                    flats = calloc((size_t)num, sizeof(struct Flat));
                    if (flats == NULL) {
                        printf("Memory allocation failed!\n");
                        num = 0;
                        break;
                    }
                }
                int loaded = ReadFromFile(flats, num);
                if (loaded > 0) {
                    num = loaded;
                }
                break;

            case 8:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid Choice!\n");
                break;
        }

    } while (condition != 8);

    free(flats);
    return 0;
}