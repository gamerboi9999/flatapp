#include "searchflat.h"
#include "flat.h"
#include <stdio.h>
#include <string.h>

void SearchFlat(const char name[], const struct Flat *flats, int num)
{
    int found = 0;
    for (int i = 0; i < num; i++) {
        if (strcmp(flats[i].name, name) == 0) {
            printf("\nA flat has been found!\n");
            printf("Flat number: %d\n", flats[i].number);
            printf("No of rooms: %d\n", flats[i].rooms);
            printf("Owner: %s\n", flats[i].owner);
            printf("Name: %s\n", flats[i].name);
            printf("Street: %s\n", flats[i].street);
            printf("TotalRent: %.2f\n", flats[i].Rent);
            printf("Booked: %s\n", flats[i].booked ? "Yes" : "No");

            found = 1;
            break;
        }
    }
    if (found == 0) {
        printf("Flat not found!\n");
    }
}