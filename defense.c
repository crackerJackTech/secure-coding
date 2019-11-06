#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <regex.h>
#include <unistd.h>
#include <ctype.h>

void getValidName(char *buffer);
int getValidNum();
void getValidFileName(char *buffer);
void getValidPassword(char *buffer);
int validatePassword(const char *buffer);
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
        char cwd[50];
        size_t size = 50;
        getcwd(cwd, size);
        printf("Enter a file name in the current directory: ");
        scanf("%49[^\n]%*c", buffer);

        //char *cwd;
        //getcwd(cwd, 50);
        //const char *regex = ")?[\\\\|/]?(?!.*\\.\\.(\\\\|/))[a-zA-Z0-9\\.]+\\.txt$";
        //char *cwdAndRegex;
        //cwdAndRegex = malloc(strlen("^(") + strlen(cwd) + strlen(regex));
        //strncpy(cwdAndRegex, ")?", )
        //strcat(cwdAndRegex, cwd, strlen(cwd));
        //strcat(cwdAndRegex, regex, strlen(regex));
        //valid = match(buffer, cwdAndRegex);
    } while (valid == 0);
    printf("You entered: %s\n", buffer);
}

void getValidPassword(char *buffer)
{
    int valid = 0;
    do
    {
        printf("Enter a password that is between 10 and 32 characters in length, and contains at least one upper case character, lower case character, digit, and punctuation mark: ");
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
            continue; // space character
    }
    return upper && lower && digit && special;
}

int match(const char *string, const char *pattern)
{
    regex_t regex;
    if (regcomp(&regex, pattern, REG_NOSUB) != 0)
    {
        printf("Didn't compile");
        return 0;
    }
    int status = regexec(&regex, string, 0, NULL, 0);
    printf("status: %d\n", status);
    regfree(&regex);
    if (status != 0)
        return 0;
    return 1;
}