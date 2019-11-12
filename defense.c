#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <regex.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>

void getValidName(char *buffer, FILE *errorFile);
int getValidNum();
void getValidFileName(char *buffer, FILE *errorFile);
void getValidPassword(char *buffer);
int validatePassword(const char *buffer);
void writeToOutputFile(FILE *inputFile, FILE *outputFile, FILE *errorFile, const char *first, const char *last, int sum, int product);
int match(const char *string, const char *pattern, int ignoreCase, FILE *errorFile);


int main() // compile with: gcc -pedantic -Wall -Wextra -Werror defense.c -o defense
{
    char *errorFileName = "error.txt";
    if (!access(errorFileName, 0))
        remove(errorFileName);
    FILE *errorFile = fopen(errorFileName, "w");

    char firstName[50];
    char lastName[50];

    printf("Enter your first name: ");
    getValidName(firstName, errorFile);

    printf("Enter your last name: ");
    getValidName(lastName, errorFile);

    printf("Hello, %s %s\n", firstName, lastName);

    
    

    int num1 = getValidNum();

    int num2 = getValidNum();
    printf("You entered %d and %d\n", num1, num2);

    char inputFileName[50];
    getValidFileName(inputFileName, errorFile);
    char outputFileName[50];
    getValidFileName(outputFileName, errorFile);

    char password1[50];
    char password2[50];
    int result = 1;
    do
    {
        getValidPassword(password1);
        getValidPassword(password2);
        result = strcmp(password1, password2);
        if (result != 0)
            fprintf(errorFile, "Passwords do not match. Try again.\n");
    } while (result != 0);

    printf("You entered %s and %s", password1, password2);

    FILE *inputFile = fopen(inputFileName, "r");
    FILE *outputFile = fopen(outputFileName, "a");

    writeToOutputFile(inputFile, outputFile, errorFile, firstName, lastName, num1 + num2, num1 * num2);
}

int getValidNum()
{
    int num = 0;
    char buf[1024];

    while(num == 0)
    {
	printf("Enter any integer: ");
	if(fgets(buf, 1024, stdin) != NULL)
	{
		num = atoi(buf);
	}


    }



    printf("You entered %d.\n", num);
    return num;
}

void getValidName(char *buffer, FILE *errorFile) //currently buffer overflowing
{
    int valid = 0;
    do
    {
        scanf("%s", buffer);
        valid = match(buffer, "[[:alpha:]]\\{1,50\\}", 0, errorFile);
        if (valid == 0)
            printf("\nEnter a name: ");
    } while (valid == 0);

    printf("You entered %s\n", buffer);
    setbuf(stdin, NULL);
}

void getValidFileName(char *buffer, FILE *errorFile)
{
    int valid = 0;
    do
    {
        printf("Enter a file name in the current directory: ");
        scanf("%s", buffer);
        valid = match(buffer, "^(\\./)?[A-Za-z -_]+.txt$", 1, errorFile);
    } while (valid == 0);
    printf("You entered: %s\n", buffer);
}

void getValidPassword(char *buffer)
{
    int valid = 0;
    do
    {
        printf("Enter a password between 8 and 32 characters in length, that contains at least one upper case character, lower case character, digit, and punctuation mark: ");
        scanf("%s", buffer);
        valid = validatePassword(buffer);
    } while (valid == 0);
}

int validatePassword(const char *password)
{
    const char *p = password;
    char c;
    int count = 0;
    int upper = 0;
    int lower = 0;
    int digit = 0;
    int special = 0;
    while (*p)
    {
        count++;
        c = *p++;
        if (isupper(c))
            ++upper;
        else if (islower(c))
            ++lower;
        else if (isdigit(c))
            ++digit;
        else if (ispunct(c))
            ++special;
        else
            return 0; // invalid character
    }
    return upper && lower && digit && special && count > 7 && count < 33;
}

void writeToOutputFile(FILE *inputFile, FILE *outputFile, FILE *errorFile, const char *first, const char *last, int sum, int product)
{
    if (inputFile == NULL || outputFile == NULL)
    {
        fprintf(errorFile, "ERROR: could not open input or output file:\n");
        fclose(errorFile);
        return;
    }

    fprintf(outputFile, "First Name: %s\n", first);
    fprintf(outputFile, "Last Name: %s\n", last);
    fprintf(outputFile, "Sum: %d\n", sum);
    fprintf(outputFile, "Product: %d\n", product);

    char ch;
    while ((ch = getc(inputFile)) != EOF)
    {
        putc(ch, outputFile);
    }
    fclose(inputFile);
    fclose(outputFile);
    fclose(errorFile);
}

int match(const char *string, const char *pattern, int ignoreCase, FILE *errorFile)
{
    regex_t regex;
    if (ignoreCase == 1)
    {
        if (regcomp(&regex, pattern, REG_NOSUB | REG_ICASE | REG_EXTENDED) != 0)
        {
            return 0;
        }
    }
    else
    {
        if (regcomp(&regex, pattern, REG_NOSUB) != 0)
        {
            return 0;
        }
    }
    int status = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);
    if (status != 0)
    {
        printf("The supplied input \"%s\" did not match against the regex \"%s\"\n", string, pattern);
        fprintf(errorFile, "The supplied input \"%s\" did not match against the regex \"%s\"\n", string, pattern);
        return 0;
    }
    return 1;
}


