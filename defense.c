#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <regex.h>

void getValidName(char *buffer);
int getValidNum();
void getValidFileName(char *buffer);
int match(const char *string, const char *pattern);

int main()
{
    // get first and last name
    char firstName[50];
    char lastName[50];
    printf("Enter your first name: ");
    getValidName(firstName);
    printf("Enter your last name: ");
    getValidName(lastName);
    printf("Hello, %s %s\n", firstName, lastName);

    // get 2 nums
    int num1 = getValidNum();
    int num2 = getValidNum();
    printf("You entered %d and %d\n", num1, num2);

    // open input file
    char inputFile[50];
    getValidFileName(inputFile);
    printf("You entered %s", inputFile);
    FILE *inputFilePtr = fopen(inputFile, "r");

    char outputFile[50];
    getValidFileName(outputFile);
    printf("You entered %s", outputFile);
    FILE *outputFilePtr = fopen(outputFile, "w");

    // get, store, and validate password

    // write first, last name, sum of numbers, product of numbers, input file contents to output file
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
        scanf("%s", buffer);
        valid = match(buffer, ""); //regex here
    } while (valid == 0);
}

int match(const char *string, const char *pattern)
{
    regex_t regex;
    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0)
        return 0;
    int status = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);
    if (status != 0)
        return 0;
    return 1;
}