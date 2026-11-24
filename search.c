#include"search.h"
#include "flat.h"
#include<stdio.h>
#include<string.h>

void SearchFlat(char name[],struct flat*flats,int num)
{
    int found=0;
     for (int i=0;i<num;i++) {
        if(strcmp(flats[i].name,name)==0)
        {
            printf("A flat has been found!\n");

            printf("Flat number:%d\n",flats[i].number);
            printf("No of rooms:%d\n",flats[i].rooms);
            printf("Owner:%s",flats[i].owner);
            printf("Name:%s",flats[i].name);
            printf("Street:%s\n",flats[i].street);
            printf("TotalRent:%.2f\n",flats[i].Rent);

            found=1;
            break;
        }
    }
    if (found==0) {
        print("Flat not found!\n");
    }
}