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
void generatePassword(int length, int useUppercase, int useLowercase, int useDigits, int useSpecialChars, FILE *file)
{
    char uppercaseLetters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char lowercaseLetters[] = "abcdefghijklmnopqrstuvwxyz";
    char digits[] = "0123456789";
    char specialChars[] = "!@#$%^&*()";

    char charset[100] = "";
    if (useUppercase)
    {
        strcat(charset, uppercaseLetters);
    }
    if (useLowercase)
    {
        strcat(charset, lowercaseLetters);
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
        return;
    }

    char password[length + 1];
    for (int i = 0; i < length; i++)
    {
        password[i] = charset[rand() % charsetSize];
    }
    password[length] = '\0';

    shuffle(password, length);

    printf("Generated password: %s\n", password);
    analyzePasswordStrength(password);

    // Encrypt the password
    encrypt(password, 3);

    if (file != NULL)
    {
        fprintf(file, "%s\n", password);
    }
}

int main()
{
    srand(time(0)); // seed the random number generator

    int length;
    printf("Enter the length of the password: ");
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
    printf("Enter the name of the file to save the passwords (leave blank to not save): ");
    scanf(" %99[^\n]", filename); // The space before % is necessary to skip any leftover newline character

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
        printf("Generated password %d: ", i + 1);
        generatePassword(length, useUppercase, useLowercase, useDigits, useSpecialChars, file);
    }

    if (file != NULL)
    {
        fclose(file);
    }

    return 0;
}