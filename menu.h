#ifndef HEADER_1_H
#define HEADER_1_H

struct Flat {
    int rooms;
};

struct Flat* DisplayFlats(int num);
void DisplayAll(struct Flat* flats, int num);

#endif