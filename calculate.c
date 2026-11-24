<<<<<<< HEAD
#include "rent.h"
=======
#include "calculaterent.h"
>>>>>>> c34cb322651284b4727f9fce3bc9f129b08b470e
#include "flat.h"
#include <stdio.h>
#include <stdlib.h>

float calculateRent(struct flat *flat,int month)
{
    float totalRent;

<<<<<<< HEAD
    totalRent=flat->rent*month;
=======
    totalRent = flat->Rent * month;
>>>>>>> c34cb322651284b4727f9fce3bc9f129b08b470e

    return totalRent;
}