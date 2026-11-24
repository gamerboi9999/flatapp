#include "bookflat.h"
#include "flat.h"
#include <stdio.h>
#include <stdbool.h>

void BookFlat(struct Flat *flats, int num)
{
    int flatnumber;

    printf("Enter flatnumber that you would like to book: ");
    if (scanf("%d", &flatnumber) != 1) {
        printf("Invalid input!\n");
        return;
    }

    if (flatnumber < 1 || flatnumber > num)
    {
        printf("Flat not found\n");
        return;
    }

    int index = flatnumber - 1;

    if (flats[index].booked)
    {
        printf("Flat already booked!\n");
    }
    else
    {
        flats[index].booked = true;
        printf("Flat No %d booked successfully!\n", flatnumber);
    }
}