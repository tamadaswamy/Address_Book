#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include<ctype.h>

void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    
    printf("%-8s %-10s %-15s %-30s\n", "SI.NO","Name","Phone","Email.id");
    printf("-------------------------------------------------------------\n");
    for(int i=0;i<addressBook->contactCount;i++)
    {
        printf("%-8d %-15s %-15s %s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    printf("-------------------------------------------------------------\n");
}

void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    FILE *fptr=fopen("contact.txt","r");
    if(fptr==NULL)
    {
        printf("the file doesn't open\n");
        return;
    }
    while(fscanf(fptr,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[addressBook->contactCount].name,addressBook->contacts[addressBook->contactCount].phone,addressBook->contacts[addressBook->contactCount].email)==3)
    {
        
        addressBook->contactCount++;
    }
    fclose(fptr);
   //fprintf(,"%s,%s,%s",addressBook->contacts[addressBook->contactCount].name,addressBook->contacts[addressBook->contactCount].phone,addressBook->contacts[addressBook->contactCount].email);
    //addressBook->contacts[addressBook->contactCount]
    
}
void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
  
   // Exit the program
}
//------------------------------------------validation for NAME,PHONE NUMBER,EMAIL.ID--------------
void createContact(AddressBook *addressBook)
{
    if(addressBook->contactCount<MAX_CONTACTS)
    {
        Contact newcontact;
        printf("Enter the name: ");
        scanf(" %[^\n]",newcontact.name);
        if(my_isalpha(newcontact.name))
        {
            printf("Enter correct name\n");
            return;
        }
        printf("Enter the phone number: ");
        scanf("%s",newcontact.phone);
        if(my_isalnum(newcontact.phone,addressBook))
        {
            printf("This number allready exists (or) Invalid number\n");
            return;
        }
        printf("Enter the email.id: ");
        scanf("%s",newcontact.email);
        newcontact.email[50];
        if(check_email(newcontact.email,addressBook))
        {  
            printf("Enter the valid email\n");
            return ;
        }
        printf("1.To save the conatact press 1\n2.Do not saving the contact press 2\n");
        printf("Enter your choice: ");
        int ch;
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
            addressBook->contacts[addressBook->contactCount]=newcontact;
            addressBook->contactCount++;
            printf("Contact stored sccessfully \n");
            break;
            case 2:
            printf("contact not stored exiting...\n");
            break;
        }
    }
    else
    {
        printf("The AddressBook is full\n");
    }
    
}
//------------NAME,PHONE,EMAIL Validation
int my_isalpha(char *name)
{
    if(!isalpha(name[0]))
    {
       
        return 1;
            
    } 
    return 0;
}
int my_isalnum(char *phone,AddressBook * addressBook)
{
    int count1=0;
    int static count=0;
    int i=0;
    while(phone[i]!='\0')
    {
        count1++;
        if(!isdigit(phone[i]))
        {   
            count++;
            if(count<3)
            {
                my_isalnum(phone,addressBook);
            }
            count=0;
            return 1;
        }
        i++;
    }
    if(count1!=10)
    {
        count++;
        if(count<3)
        {    
            my_isalnum(phone,addressBook);
        }
        return 1;
    }
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].phone,phone)==0)
        {
           // printf("This number is already stored\n");
            return 1;
        }
    }
    return 0;
    
}
int check_email(char *email,AddressBook *addressBook)
{
    // printf("Enter the email.id: ");
    // scanf("%s",newcontact.email);
    int tag=0;
    int len_str=strlen(email);
    for(int i=0;email[i]!='\0';i++)
    {
        if(email[i]>='A'&&email[i]<='Z')
        {
            return 1;
        }
        if(email[i]=='@')
        {
            tag++;
            for(int j=i+1;j<len_str-4;j++)
            {
                if(!islower(email[j]))
                {
                    return 1;
                }
            }
        }
        if(email[i]=='.')
        {
            int k=strcmp(email+len_str-4,".com");
            if(k!=0)
            { 
                return 1;
            }
        }
    }
    int i=0;
    if(tag==1)
    {
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(!strcmp(addressBook->contacts[i].email,email))
            {
                return i;
            }
        }   
    }
    return 0;
}
void searchContact(AddressBook *addressBook) 
{
    int option;
    int res;
    int count=0;
    do
    {
        printf("1.Search by Name\n");
        printf("2.Search by Phone\n");
        printf("3.Search by email.id\n");
        printf("4.exiting...\n");
        printf("Enter your option: ");
        scanf("%d",&option);
        switch(option)
        {
            case 1:
                char arr[50];
                printf("Enter the name: ");
                char Name[50];
                scanf(" %[^\n]",Name);
                res=search_by_name(arr,Name,addressBook,&count);
                if(res!=0)
                {
                    for(int i=0;i<count;i++)
                    {
                        int j=arr[i];
                        printf("%d %s %s %s\n", i+1,addressBook->contacts[j].name,addressBook->contacts[j].phone,addressBook->contacts[j].email);
                    //printf(" successfully edit\n");
                    }
                }
                else
                {
                    printf("contact not found\n");
                }
                break;
            case 2:
                res=search_by_phone(addressBook);
                if(res>=0)
                {
                    printf("The contact found\n");
                    printf("%s %s %s\n",addressBook->contacts[res].name,addressBook->contacts[res].phone,addressBook->contacts[res].email);
                    //printf(" successfully edit\n"); 
                }
                else
                {
                printf("contact not found\n");
                }
                break;
            case 3:
                int k=0;
                res=search_by_email(addressBook);
                if(res>=0)
                {
                    printf("The contact found\n");
                    printf("%s %s %s\n",addressBook->contacts[res].name,addressBook->contacts[res].phone,addressBook->contacts[res].email);
                    //printf(" successfully edit\n");
                
                }
                else
                {
                    printf("contact not found\n");
                }
                break;
            case 4:
                printf("EXITING...\n");
                break;
            default:
                printf("Enter the valid option\n");
        }
    } while (option!=4);
    
}
//---------------------------------------------Search contact in addressBook-------
int search_by_name(char arr[],char *name,AddressBook*addressBook,int *count)
{
    int flag=0,i=0;
    for(i=0;i<addressBook->contactCount;i++)
    {
        if(!strcmp(addressBook->contacts[i].name,name))
        {
            arr[*count]=i;
            *count=*count+1;
            flag=1; 
        }
    }
    if(flag==0)
    {
        printf("The contact not found\n");
        return 0; 
    }
    else
    {
        printf("The contact found\n");
        return i;
    }   
}
int search_by_phone(AddressBook *addressBook)
{
    printf("Enter the Phone: ");
    char phone[15];
    scanf("%s",phone);
    int flag=0;
    int i;
    if( my_isalnum(phone,addressBook))
    {
        for(i=0;i<addressBook->contactCount;i++)
        {
            if(!strcmp(addressBook->contacts[i].phone,phone))
            {
                return i;
            }
        }
    }
    if(flag==0)
    {
        printf("The contact was not found\n");
    }   
}
int search_by_email(AddressBook *addressBook)
{
    printf("Enter the Email.id: ");
    char email[50];
    scanf("%s",email);
    return check_email(email,addressBook);;
}
void editContact(AddressBook *addressBook)
{
    int option;
    do
    {
        printf("1.Edit by Name\n");
        printf("2.Edit by Phone\n");
        printf("3.Edit by Email.id\n");
        printf("4.exiting...\n");
        printf("Choose your option: ");
        /* code */
        scanf("%d",&option);
        switch(option)
        {
            case 1:
            edit_by_name(addressBook);
            break;
            case 2:
            edit_by_phone(addressBook);//
            break;
            case 3:
            edit_by_email(addressBook);
            break;
            case 4:
            printf("Exiting...\n");
            break;
            default:
            printf("Enter valid option\n");
        }
    } while (option!=4);   
}
void edit_by_name(AddressBook *addressBook)
{
    int count=0;
    char arr[count];
    printf("Enter the name: ");
    char name[20];
    scanf(" %[^\n]",name);
    int res=search_by_name(arr,name,addressBook,&count);
    int j;
    if(res!=0)
    {
        if(count==1)
        {
            char new_name[50];
            printf("Enter the new_name: ");
            scanf(" %[^\n]",new_name);
            int k=arr[0];
            strcpy(addressBook->contacts[k].name,new_name);
            printf("The contact modify successfully\n");
        }
        else if(count>1)
        {
            printf("Multiple contact found\n");
            printf("index  si.no  name      phone     email\n");
            for(int i=0;i<count;i++)
            {
                j=arr[i];
                printf("%-6d %-10s %-12s %-20s\n",i+1,addressBook->contacts[j].name,addressBook->contacts[j].phone,addressBook->contacts[j].email);
            }
            printf("Enter which contact you want to editi: ");
            int s;
            scanf("%d",&s);
            printf("Enter the new_name: ");
            char new_name[50];
            scanf(" %[^\n]",new_name);
            int k=arr[0];
            for(int i=k;i<addressBook->contactCount;i++)
            {
                if(i==arr[s-1])
                {
                    strcpy(addressBook->contacts[i].name,new_name);
                    printf("The contact modify successfully\n");
                }
            }   
        }    
    }
    else
    {
        printf("contact not found\n");
    }
}
void edit_by_phone(AddressBook *addressBook)
{
    int i=search_by_phone(addressBook);
    printf("Enter the new number: ");
    char new_number[15];
    scanf("%s",new_number);
    if(i!=0)
    {
        strcpy(addressBook->contacts[i].phone,new_number);
        printf("Phone number updated successfully\n");
    }
    else
    {
        printf("Enter unique number\n ");
    }     
}
void edit_by_email(AddressBook *addressBook)
{
    int i=search_by_email(addressBook);
    printf("Enter new email: ");
    char new_email[50];
    scanf("%s",new_email);
    if(i!=0)
    {
        strcpy(addressBook->contacts[i].email,new_email);
        printf("The email is modify successfully\n");
    }
    else
    {
        printf("Enter the unique email\n");
    }   
}
void deleteContact(AddressBook *addressBook)
{
    int option;
    do
    {
        printf("1.Delete by using Name\n");
        printf("2.Delete by using Phone\n");
        printf("3.Delete by using Email\n");
        printf("4.Exting...\n");
        printf("Enter your choice: ");
        /* code */
        scanf("%d",&option);
        switch(option)
        {
            case 1:
            delete_by_name(addressBook);
            break;
            case 2:
            delete_by_phone(addressBook);
            break;
            case 3:
            delete_by_email(addressBook);
            break;
            case 4:
            printf("Exiting...\n");
            default:
            printf("Enter valid option\n");
        }
    } while (option!=4);  
}
void delete_by_name(AddressBook * addressBook)
{
    int count=0;
    char arr[count];
    printf("Enter the name: ");
    char name[20];
    scanf("%s",name);
    int res=search_by_name(arr,name,addressBook,&count);
    if(res!=0)
    {
        if(count==1)
        {
            int j=arr[0];
            printf("%d %s %s %s\n",j+1,addressBook->contacts[j].name,addressBook->contacts[j].phone,addressBook->contacts[j].email);
            for(int i=j;i<(addressBook->contactCount);i++)
            {
                addressBook->contacts[i]=addressBook->contacts[i+1];
                addressBook->contactCount--;
                printf("contact successfully delete\n");
            }
        }
        else if(count>1)
        {
            int k=arr[0];
            printf("Multiple contact found\n");
            printf("index  si.no  name  phone  email\n");
            for(int i=0;i<count;i++)
            {
                int j=arr[i];
                printf("%-6d %-10s %-12s %-20s\n",i+1,addressBook->contacts[j].name,addressBook->contacts[j].phone,addressBook->contacts[j].email);
            }
            printf("select which one u want to delete: ");
            int s;
            scanf("%d",&s);    
            for(int i=k;i<(addressBook->contactCount);i++)
            {
                if(i=arr[s-1])
                {
                    for(int j=i;j<(addressBook->contactCount);j++)
                    {
                        addressBook->contacts[j]=addressBook->contacts[j+1];
                        addressBook->contactCount--;
                        printf("Contact sucessfully delete\n");
                    }
                }
            }
        }
    }
    else
    {
        printf("contact not found\n");
    }
}
void delete_by_phone(AddressBook * addressBook)
{
    int j=search_by_phone(addressBook);
    if(j==0)
    {
        printf("The contact not found Enter\n");
        return;
    }
    else
    {
        for(int i=j;i<(addressBook->contactCount)-1;i++)
        {
            addressBook->contacts[i]=addressBook->contacts[i+1];
        }
        addressBook->contactCount--;
        printf("The contact successfuuly delete\n");
    }   
}
void delete_by_email(AddressBook *addressBook)
{
    int j=search_by_email(addressBook);
    if(j>=1&&j<=addressBook->contactCount)
    {
        for(int i=j;i<(addressBook->contactCount)-1;i++)
        {
            addressBook->contacts[i]=addressBook->contacts[i+1];
        }
        addressBook->contactCount--;
        printf("The contact successfully delete.\n");
    }
}
