#include "rent_h"
#include "flat_h"
#include <stdio.h>
#include <stdlib.h>

float calculateRent(struct Flat*flat,int month){
    float totalRent;

    totalRent=flat.rent*month;

    return totalRent;
}