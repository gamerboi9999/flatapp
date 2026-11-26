#include <stdio.h>
#include <stdlib.h>
#include "flat.h"

void WriteToFile(struct Flat *flats)
{
    FILE *file = fopen("flats.txt", "w");

    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "%d|%d|%s|%s|%d|%s|%.2f\n",
    flats[0].number,
    flats[0].rooms,
    flats[0].name,
    flats[0].owner,
    flats[0].booked ? 1 : 0,
    flats[0].street,
    flats[0].Rent);

    fclose(file);

    printf("Flat saved successfully!\n");
}

void ReadFromFile(struct Flat *flats)
{
    FILE *file = fopen("flats.txt", "r");

    if (file == NULL)
    {
        printf("File not found!\n");
        return;
    }

    int bookedValue;

    if (fscanf(file, "%d|%d|%49[^|]|%49[^|]|%d|%49[^|]|%f",
    &flats[0].number,
    &flats[0].rooms,
    flats[0].name,
    flats[0].owner,
    &bookedValue,
    flats[0].street,
    &flats[0].Rent) == 7)
    {
        flats[0].booked = bookedValue != 0;
        printf("Flat loaded successfully!\n");
    }
    else
    {
        printf("Error reading flat data!\n");
    }

    fclose(file);
}