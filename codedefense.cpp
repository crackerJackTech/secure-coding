#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
using namespace std;

string getValidName(string type);
int getValidNum();
string getValidFileName(string type);
bool isValidPassword(string password1, string password2);

int main()
{
    string firstName = getValidName("first");
    string lastName = getValidName("last");

    cout << "Hello, " << firstName << " " << lastName << "!" << endl;

    int num1 = getValidNum();
    int num2 = getValidNum();

    cout << "You entered " << num1 << endl
         << "You entered " << num2 << endl;

    ifstream inputFile;
    string inputFileName = getValidFileName("input");
    inputFile.open(inputFileName); // open file for reading

    ofstream outputFile;
    string outputFileName = getValidFileName("output");
    outputFile.open(outputFileName, ios::app); // open file for appending

    string password1;
    string password2;
    bool validPassword = false;
    while (!validPassword)
    {
        cout << "Enter a password: ";
        getline(cin, password1);
        cout << "Please re-enter the password: ";
        getline(cin, password2);
        validPassword = isValidPassword(password1, password2);
    }

    outputFile << firstName << " " << lastName << endl;
    outputFile << num1 + num2 << endl;
    outputFile << num1 * num2 << endl;

    string curr;
    while (!inputFile.eof())
    {
        getline(inputFile, curr);
        outputFile << curr << endl;
    }

    inputFile.close();
    outputFile.close();
    cout << "First Name, Last Name, product of numbers, sum of numbers, and input file contents have been appended to the output file specified" << endl;
}

string getValidName(string type)
{
    string name;
    regex regex("^[A-Z][a-z]{0,49}$");
    while (true)
    {
        cout << "Please enter a " << type << " name less no larger than 50 characters: ";
        getline(cin, name);
        if (regex_match(name, regex))
        {
            return name;
        }
    }
}

int getValidNum()
{
    int num;
    string input;
    regex regex("^[0-9]+$");
    while (true)
    {
        cout << "Please enter a valid number: ";
        getline(cin, input);
        if (regex_match(input, regex))
        {
            stringstream stream(input);
            stream >> num;
            break;
        }
        cout << "Invalid number, please try again." << endl;
    }
    return num;
}

string getValidFileName(string type)
{
    while (true)
    {
        cout << "Enter the name of an existing " << type << " file in the current directory: ";
        string fileName;
        getline(cin, fileName);
        ifstream src(fileName.c_str());
        if (src) // stream is valid
            return fileName;
        else
            cout << "The specified file name did not match any files in this directory. Try again." << endl;
    }
}

bool isValidPassword(string password1, string password2)
{
    int i = password1.compare(password2);
    if (i == 0)
        return true;
    cout << "Passwords do not match, please try again." << endl;
    return false;
}