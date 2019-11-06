#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <regex.h>
#include <unistd.h>

void getValidName(char *buffer);
int getValidNum();
void getValidFileName(char *buffer);
void getValidPassword(char *buffer);
int validatePassword(char *password1, char *password2);
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

    char cwd[50];
    size_t size = 50;
    getcwd(cwd, size);
    printf("cwd: %s", cwd);

    // open input file
    char inputFile[50];
    //getValidFileName(inputFile);
    //printf("You entered %s", inputFile);
    //FILE *inputFilePtr = fopen(inputFile, "r");

    char outputFile[50];
    //getValidFileName(outputFile);
    //printf("You entered %s", outputFile);
    //FILE *outputFilePtr = fopen(outputFile, "w");

    // get, store, and validate password
    char password1[50];
    char password2[50];
    do
    {
        getValidPassword(password1);
        getValidPassword(password2);
    } while (validatePassword(password1, password2) != 0);

    printf("You entered %s and %s", password1, password2);
    int sum = num1 + num2;
    int product = num1 * num2;

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
        scanf("%49[^\n]%*c", buffer);
        valid = match(buffer, "");
    } while (valid == 0);
    printf("You entered: %s\n", buffer);
}

void getValidPassword(char *buffer)
{
    int valid = 0;
    do
    {
        printf("Enter a password that contains at least 10 characters and includes at least one upper case character, lower case character, digit, punctuation mark: ");
        scanf("%49[^\n]%*c", buffer);
        printf("You entered %s\n", buffer);
        valid = match(buffer, "^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[\\@\\$\\!\\*\\?\\&\\#\\^])[A-Za-z\\d\\@\\$\\!\\*\\?\\&\\#\\^]{10,}$");
    } while (valid == 0);
    printf("You entered: %s\n", buffer);
}

int validatePassword(char *password1, char *password2)
{
    return strcmp(password1, password2);
}

int match(const char *string, const char *pattern)
{
    regex_t regex;
    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0)
        return 0;
    int status = regexec(&regex, string, 0, NULL, 0);
    printf("%d", status);
    regfree(&regex);
    if (status != 0)
        return 0;
    return 1;
}