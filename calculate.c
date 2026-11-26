#include "rent.h"
#include "flat.h"

float calculateRent(struct Flat *flat, int month) {
    float totalRent;

    totalRent = flat->Rent * month;

    return totalRent;
}