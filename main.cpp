#include <iostream>
#include <string>
using namespace std;

void mainMenu() {

}

float getInputNumber(string prompt) {
    float num;
    while (true) {
        cout << prompt;
        cin >> num;

        if (cin.fail()) {
            cin.clear(); // clear the error
            cin.ignore(1000, '\n'); // ignore wrong input
            cout << "Invalid number. Try again." << endl;
        } else {
            cin.ignore(1000, '\n'); // clean up
            return num;
        }
    }
}

string getInputText(string prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);

        if (input.empty()) {
            cout << "Input cannot be empty. Try again." << endl;
        } else {
            return input;
        }
    }
}

string getColoredText(const string& text, const string& color = "", const string& bg = "", const string& style = "") {
    string code = "";

    // Text colors
    if (color == "red") code += "\033[31m";
    else if (color == "green") code += "\033[32m";
    else if (color == "yellow") code += "\033[33m";
    else if (color == "blue") code += "\033[34m";
    else if (color == "magenta") code += "\033[35m";
    else if (color == "cyan") code += "\033[36m";
    else if (color == "white") code += "\033[37m";

    // Background colors
    if (bg == "red") code += "\033[41m";
    else if (bg == "green") code += "\033[42m";
    else if (bg == "yellow") code += "\033[43m";
    else if (bg == "blue") code += "\033[44m";
    else if (bg == "magenta") code += "\033[45m";
    else if (bg == "cyan") code += "\033[46m";
    else if (bg == "white") code += "\033[47m";

    // Text styles
    if (style == "bold") code += "\033[1m";
    else if (style == "underline") code += "\033[4m";

    // Final text with reset at the end
    return code + text + "\033[0m";
}


int main()
{
    mainMenu();
    int age = (int)getInputNumber("Enter your age: ");
    cout << age;

    system("pause>0");
    return 0;
}