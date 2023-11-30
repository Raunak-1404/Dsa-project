#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

struct User
{
    char *userName;
    char *password;
    int contact;
    struct User *next;
};

struct User *allUser;     // head node of linked carrying all users info
struct User *currentUser; // current node

void dataTransferFromFile()
{
    FILE *file = fopen("UserData.txt", "r");
    if (file == NULL)
    {
        printf("\nError opening file");
        exit(0);
    }

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Split the line into username and password
        char *username = strtok(line, ",");
        char *password = strtok(NULL, ",");
        char *contact = (strtok(NULL, ","));
        // Remove newline character from password
        password[strcspn(password, "\n")] = 0;

        // Add the user information to the linked list
        createNode(username, password, contact);
    }
    fclose(file);
}

// void addNode(char *username, char *password, char *contact)
// {
//     struct User *newNode = createNode(username, password, contact);

// }

void createNode(char *username, char *password, int contact)
{
    struct User *newNode = (struct User *)malloc(sizeof(struct User));
    strcpy(username, newNode->userName);
    strcpy(password, newNode->password);
    newNode->contact = contact;
    newNode->next = NULL;
    if (allUser == NULL)
    {
        allUser = newNode;
    }
    else
    {
        struct User *ptr = allUser;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = newNode;
    }
}

int signIn()
{
    char *username, *password, *re_password;
    printf("\nEnter User Name - ");
    scanf("%s", username);
    if (isRegistered(username) != 1)
    {
        printf("\nEntered Username is not Valid");
        printf("\nTry Again Another Username");
        return -1;
    }
    strcpy(username, currentUser->userName);

jump:
    printf("\nEnter Password - ");
    scanf("%s", re_password);
    // strcpy(username, currentUser->userName);

    printf("\nConfirm Password - ");
    scanf("%s", password);
    if (strcmp(password, re_password) != 0)
    {
        printf("\nEntered Password is Incorrect\n Please Re-Enter the Password");
        goto jump;
        return -1;
    }
    printf("\nLogged In Successfully");
}

int isRegistered(char *username)
{
    if (search(username))
        return 1;
    else
        return -1;
}

int search(char *username)
{
    struct User *ptr = allUser;
    while (ptr != NULL)
    {
        if (strcmp(ptr->userName, username))
            return 1;
        ptr = ptr->next;
    }
    return -1;
}

void main()
{
    char str1[10] = 's';
    char str2[10] = 's';
    printf("New - %d", strcmp(str1, str2));
    struct User *allUser = (struct User *)malloc(sizeof(struct User));
    if (allUser == NULL)
    {
        printf("Memory Allocation is Not Successful");
    }
    struct User *currentUser = (struct User *)malloc(sizeof(struct User));
    dataTransferFromFile();
    signIn();
}