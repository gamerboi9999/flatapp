#include <stdio.h>
#include <stdlib.h>
#include "writeandread.h"

void WriteToFile(const struct Flat *flats, int num)
{
    FILE *file = fopen("flats.txt", "w");

    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < num; i++) {
        fprintf(file, "%d|%d|%s|%s|%d|%s|%.2f\n",
        flats[i].number,
        flats[i].rooms,
        flats[i].name,
        flats[i].owner,
        flats[i].booked ? 1 : 0,
        flats[i].street,
        flats[i].Rent);
    }

    fclose(file);
    printf("Flats saved successfully!\n");
}

int ReadFromFile(struct Flat *flats, int num)
{
    FILE *file = fopen("flats.txt", "r");

    if (file == NULL)
    {
        printf("File not found!\n");
        return 0;
    }

    int count = 0;
    int bookedValue;

    while (count < num && fscanf(file, "%d|%d|%49[^|]|%49[^|]|%d|%49[^|]|%f",
    &flats[count].number,
    &flats[count].rooms,
    flats[count].name,
    flats[count].owner,
    &bookedValue,
    flats[count].street,
    &flats[count].Rent) == 7)
    {
        flats[count].booked = bookedValue != 0;
        count++;
    }

    fclose(file);
    printf("Loaded %d flat(s) successfully!\n", count);
    return count;
}