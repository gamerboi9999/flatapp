#include "calculaterent.h"
#include "flat.h"
#include <stdio.h>
#include <stdlib.h>

float calculateRent(struct flat *flat,int month)
{
    float totalRent;

    totalRent = flat->Rent * month;

    return totalRent;
}