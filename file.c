#include <stdio.h>
#include "file.h"
#include"contact.h"
void saveContactsToFile(AddressBook *addressBook)
{
   FILE *fptr=fopen("contact.txt","w");
   if(fptr==NULL)
   {
    printf("File not found\n");
    return;
   }
   for(int i=0;i<addressBook->contactCount;i++)
   {
    fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
   }
   printf("The contacts saved successfully\n");
   fclose(fptr);
}
