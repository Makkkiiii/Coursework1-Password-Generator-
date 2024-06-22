/*

STUDENT NAME: DENISH MAHARJAN
PROJECT ASSIGNED DATE : 23/05/2024
PROJECT SUBMISSION DATE : 23/06/2024
PROJECT TITLE : PASSWORD GENERATOR

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Function to shuffle a string
void shuffle(char *str, int length)
{
    for (int i = length - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

// Function to analyze the strength of a password
void analyzePasswordStrength(char *password)
{
    int length = strlen(password);
    int hasUppercase = 0, hasLowercase = 0, hasDigit = 0, hasSpecialChar = 0;

    for (int i = 0; i < length; i++)
    {
        if ('A' <= password[i] && password[i] <= 'Z')
        {
            hasUppercase = 1;
        }
        else if ('a' <= password[i] && password[i] <= 'z')
        {
            hasLowercase = 1;
        }
        else if ('0' <= password[i] && password[i] <= '9')
        {
            hasDigit = 1;
        }
        else
        {
            hasSpecialChar = 1;
        }
    }

    if (length >= 8 && hasUppercase && hasLowercase && hasDigit && hasSpecialChar)
    {
        printf("Strength: Strong\n");
    }
    else if (length >= 6 && ((hasUppercase && hasLowercase && hasDigit) || (hasUppercase && hasLowercase && hasSpecialChar) || (hasUppercase && hasDigit && hasSpecialChar) || (hasLowercase && hasDigit && hasSpecialChar)))
    {
        printf("Strength: Medium\n");
    }
    else
    {
        printf("Strength: Weak\n");
    }
}

// Function to encrypt a string using Caesar cipher
void encrypt(char *str, int key)
{
    int length = strlen(str);
    for (int i = 0; i < length; i++)
    {
        str[i] = str[i] + key;
    }
}

// Function to generate a random password
char *generatePassword(int length, int useUppercase, int useLowercase, int useDigits, int useSpecialChars)
{
    const char uppercase[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char lowercase[] = "abcdefghijklmnopqrstuvwxyz";
    const char digits[] = "0123456789";
    const char specialChars[] = "!@#$%^&*()";

    char *password = (char *)malloc((length + 1) * sizeof(char)); // +1 for the null terminator
    if (password == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }

    char charset[100] = "";
    if (useUppercase)
    {
        strcat(charset, uppercase);
    }
    if (useLowercase)
    {
        strcat(charset, lowercase);
    }
    if (useDigits)
    {
        strcat(charset, digits);
    }
    if (useSpecialChars)
    {
        strcat(charset, specialChars);
    }

    int charsetSize = strlen(charset);
    if (charsetSize == 0)
    {
        printf("Error: No character types selected!\n");
        free(password);
        return NULL;
    }

    for (int i = 0; i < length; i++)
    {
        password[i] = charset[rand() % charsetSize];
    }
    password[length] = '\0';

    shuffle(password, length);

    return password;
}

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

int main()
{
    srand(time(0)); // seed the random number generator

    int length;
    printf("\n");
    printf("******************** Welcome to the Password Generator! ******************** \n\n");
    printf("Enter the length you want your password to be: ");
    scanf("%d", &length);

    int useUppercase, useLowercase, useDigits, useSpecialChars;
    printf("Should the password include uppercase letters? (1 = yes, 0 = no): ");
    scanf("%d", &useUppercase);
    printf("Should the password include lowercase letters? (1 = yes, 0 = no): ");
    scanf("%d", &useLowercase);
    printf("Should the password include digits? (1 = yes, 0 = no): ");
    scanf("%d", &useDigits);
    printf("Should the password include special characters? (1 = yes, 0 = no): ");
    scanf("%d", &useSpecialChars);

    int numPasswords;
    printf("How many passwords do you want to generate? ");
    scanf("%d", &numPasswords);

    char filename[100];
    printf("Enter the file name to save passwords:");
    printf("!!! LEAVE BLANK IF YOU DO NOT WANT TO SAVE!!!\n");

    clearInputBuffer();
    fgets(filename, sizeof(filename), stdin);
    if ((strlen(filename) > 0) && (filename[strlen(filename) - 1] == '\n'))
    {
        filename[strlen(filename) - 1] = '\0';
    }

    FILE *file = NULL;
    if (strlen(filename) > 0)
    {
        file = fopen(filename, "w");
        if (file == NULL)
        {
            printf("Error: Could not open file %s\n", filename);
            return 1;
        }
    }

    for (int i = 0; i < numPasswords; i++)
    {
        char *password = generatePassword(length, useUppercase, useLowercase, useDigits, useSpecialChars);
        if (password != NULL)
        {
            printf("Generated password: %s\n", password);
            analyzePasswordStrength(password);

            encrypt(password, 3);

            printf("Encrypted password: %s\n", password);

            if (file != NULL)
            {
                fprintf(file, "%s\n", password);
            }

            free(password);
        }
    }

    if (file != NULL)
    {
        fclose(file);
    }

    return 0;
}

