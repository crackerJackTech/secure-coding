#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <regex.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>

void getValidName(char *buffer);
int getValidNum();
void getValidFileName(char *buffer);
void getValidPassword(char *buffer);
int validatePassword(const char *buffer);
void writeToOutput(FILE *file1, FILE *file2, const char *first, const char *last, int sum, int product);
int match(const char *string, const char *pattern);

int main() // compile with: gcc -pedantic -Wall -Wextra -Werror defense defense.c
{
    char firstName[50];
    char lastName[50];
    printf("Enter your first name: ");
    getValidName(firstName);
    printf("Enter your last name: ");
    getValidName(lastName);
    printf("Hello, %s %s\n", firstName, lastName);

    int num1 = getValidNum();
    int num2 = getValidNum();
    printf("You entered %d and %d\n", num1, num2);

    char inputFile[50];
    getValidFileName(inputFile);
    printf("You entered %s", inputFile);

    char outputFile[50];
    getValidFileName(outputFile);
    printf("You entered %s", outputFile);

    char password1[50];
    char password2[50];
    int result = 1;
    do
    {
        getValidPassword(password1);
        getValidPassword(password2);
        result = strcmp(password1, password2);
        if (result != 0)
            printf("Passwords do not match. Try again.\n");
    } while (result != 0);

    printf("You entered %s and %s", password1, password2);

    FILE *inputFilePtr = fopen(inputFile, "r");
    FILE *outputFilePtr = fopen(outputFile, "a");
    writeToOutput(inputFilePtr, outputFilePtr, firstName, lastName, num1 + num2, num1 * num2);
}

int getValidNum()
{
    int num;
    char buf[1024];
    do
    {
        printf("Enter any integer besides 0: ");
        if (!fgets(buf, 1024, stdin))
            return 1;
        num = atoi(buf);
    } while (num == 0);

    printf("You entered %d.\n", num);
    return num;
}

void getValidName(char *buffer)
{
    if (scanf("%49[^\n]%*c", buffer) == 1)
        printf("You entered %s\n", buffer);
}

void getValidFileName(char *buffer)
{
    int valid = 0;
    do
    {
        printf("Enter a file name in the current directory: ");
        scanf("%49[^\n]%*c", buffer);

        char *cwd;
        getcwd(cwd, 50);
        const char *regex = ")?[\\\\|/]?(?!.*\\.\\.(\\\\|/))[a-zA-Z0-9\\.]+\\.txt$";
        char *cwdAndRegex;
        cwdAndRegex = malloc(strlen("^(") + strlen(cwd) + strlen(regex));
        //strncpy(cwdAndRegex, ")?", );
        //strcat(cwdAndRegex, cwd, strlen(cwd));
        //strcat(cwdAndRegex, regex, strlen(regex));
        valid = match(buffer, cwdAndRegex);
    } while (valid == 0);
    printf("You entered: %s\n", buffer);
}

void getValidPassword(char *buffer)
{
    int valid = 0;
    do
    {
        printf("Enter a password between 8 and 32 characters in length, that contains at least one upper case character, lower case character, digit, and punctuation mark: ");
        scanf("%49[^\n]%*c", buffer);
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

void writeToOutput(FILE *file1, FILE *file2, const char *first, const char *last, int sum, int product)
{
    if (file1 == NULL || file2 == NULL)
    {
        printf("ERROR: could not open input or output file\n");
        printf("The error was: %s\n", strerror(errno));
        return;
    }

    fprintf(file2, "%s ", first);
    fprintf(file2, "%s\n", last);
    fprintf(file2, "%d", sum);
    fprintf(file2, "%d", product);

    char ch;
    while ((ch = getc(file1)) != EOF)
    {
        putc(ch, file2);
    }
    fclose(file1);
    fclose(file2);
}

int match(const char *string, const char *pattern)
{
    regex_t regex;
    if (regcomp(&regex, pattern, REG_NOSUB) != 0)
    {
        printf("Regex didn't compile...");
        return 0;
    }
    int status = regexec(&regex, string, 0, NULL, 0);
    printf("Regex Status (0 for match): %d\n", status);
    regfree(&regex);
    if (status != 0)
        return 0;
    return 1;
}