#ifndef WRITEANDREAD_H
#define WRITEANDREAD_H

#include "flat.h"

void WriteToFile(const struct Flat *flats, int num);
int ReadFromFile(struct Flat *flats, int num);

#endif