#include "book.h"
#include "flat.h"
#include <stdio.h>
#include <stdlib.h>


void BookFlat(struct flat*flats,int num) {

  int flatnumber;
  int found=0;

  printf("Enter flatnumber that you would like to book:");
  scanf("%d",&flatnumber);

  for (int i=0;i<flatnumber;i++)
  {
    if(flats[i].booked==flatnumber)
    {
        found=1

    if(flats[i].booked==false)
    {
        flats[i].booked=true;
        printf("Flat No %d booked successfully!\n")
    }    
    else
    {
        printf("Flat already booked!\n")
    }
    break;
  }
}
if(found==0)
{
    printf("flat not found\n")
}
}