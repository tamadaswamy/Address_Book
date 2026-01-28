#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct
{
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;
void initialize(AddressBook *addressBook);
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
//----------------------------------------------------CHECKING FOR NAME,PHONR,EMAIL IS VALID OR NOT
int my_isalpha(char *name);
int my_isalnum(char *phone,AddressBook * addressBook);
int check_email(char *email,AddressBook *addressBook);
//-----------------------------------------------SEARCH FOR CONTACT
int search_by_name(char arr[],char *name,AddressBook *addressBook,int *count);
int search_by_phone(AddressBook *addressBook);
int search_by_email(AddressBook *addressBook);
//-----------------------------------------------DELECTING CONTACT
void delete_by_name(AddressBook *addressBook);
void delete_by_phone(AddressBook*addressBook);
void delete_by_email(AddressBook *addressBook);
//-----------------------------------------------EDITING CONTACT
void edit_by_name(AddressBook *addressBook);
void edit_by_email(AddressBook *addressBook);
void edit_by_phone(AddressBook *addressBook);

#endif
