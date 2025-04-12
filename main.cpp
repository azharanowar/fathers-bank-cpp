#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Global balance (shared for simplicity; can later be per-user)
float currentBalance = 2254560.0f;

// Constants
const int MAX_USERS = 100;

// Global user storage
string users[MAX_USERS][4]; // [i][0] = username, [i][1] = fullName, [2] = phone, [3] = email
int userCount = 0;

// Session management
string sessionUser = "";

// Function to return colored text
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

// Clear console
void clearConsole() {
    cout << "\033[2J\033[H";
}

// Header
void printMainHeader(string section = "Dashboard") {
    string fullTitle = "Father's Bank - " + section;
    int width = 50;

    cout << getColoredText(string(width, '='), "white", "blue", "dim") << endl;

    int padding = (width - fullTitle.length()) / 2;
    cout << getColoredText(string(padding, ' '), "white", "blue");
    cout << getColoredText(fullTitle, "white", "blue", "bold");
    cout << getColoredText(string(padding + (width - fullTitle.length()) % 2, ' '), "white", "blue") << endl;

    cout << getColoredText(string(width, '='), "white", "blue", "dim") << endl;
}

// Get number input
float getInputNumber(string prompt) {
    float num;
    while (true) {
        cout << getColoredText(prompt, "white", "", "bold");
        cin >> num;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << getColoredText("Invalid number. Try again.\n", "red");
        } else {
            cin.ignore(1000, '\n');
            return num;
        }
    }
}

// Get text input
string getInputText(string prompt) {
    string input;
    while (true) {
        cout << getColoredText(prompt, "white", "", "bold");
        getline(cin, input);

        if (input.empty()) {
            cout << getColoredText("Input cannot be empty. Try again.\n", "red");
        } else {
            return input;
        }
    }
}

// Register
void registerUser() {
    clearConsole();
    printMainHeader("Register");

    string username = getInputText("Enter a unique username: ");

    for (int i = 0; i < userCount; i++) {
        if (users[i][0] == username) {
            cout << getColoredText("Username already exists! Please choose a unique username.\n", "red");
            return;
        }
    }

    string fullName = getInputText("Enter full name: ");
    string phone = getInputText("Enter phone number (Korea): ");

    // Validate phone number format
    if (phone.length() != 11 || phone.substr(0, 2) != "01") {
        cout << getColoredText("Phone number must start with '01' and be exactly 11 digits.\n", "red");
        return;
    }

    // Check for duplicate phone number
    for (int i = 0; i < userCount; i++) {
        if (users[i][2] == phone) {
            cout << getColoredText("Phone number already registered!\n", "red");
            return;
        }
    }
    
    string password = getInputText("Enter a password: ");

    // Encrypt register password into cipher password (shift ASCII by 4)
    string cipherPassword = "";
    for (int i = 0; i < password.length(); i++) {
        char originalChar = password[i];         // Get each character from password
        char encryptedChar = originalChar + 4;   // Shift it by 4 in ASCII
        cipherPassword += encryptedChar;         // Add it to the encrypted string
    }

    users[userCount][0] = username;
    users[userCount][1] = fullName;
    users[userCount][2] = phone;
    users[userCount][3] = cipherPassword;
    userCount++;

    cout << getColoredText("Registration successful!\n", "green");
}

// Login
void loginUser() {
    clearConsole();
    printMainHeader("Login");

    string username = getInputText("Enter username: ");
    string password = getInputText("Enter password: ");

    // Encrypt password into cipher password for matching login password (shift ASCII by 4)
    string cipherPassword = "";
    for (int i = 0; i < password.length(); i++) {
        char originalChar = password[i];         // Get each character from password
        char encryptedChar = originalChar + 4;   // Shift it by 4 in ASCII
        cipherPassword += encryptedChar;         // Add it to the encrypted string
    }


    for (int i = 0; i < userCount; i++) {
        if (users[i][0] == username && users[i][3] == cipherPassword) {
            sessionUser = username;
            cout << getColoredText("Login successful!\n", "green");
            return;
        }
    }

    cout << getColoredText("Incorrect username or password.\n", "red");
}

// Check balance
void checkBalance() {
    clearConsole();
    printMainHeader("Check Balance");

    cout << getColoredText("\nYour current balance is: ", "white", "", "bold");
    cout << "\033[47m\033[1m " << fixed << setprecision(2) << currentBalance << " won " << "\033[0m" << endl;

    // Funny reactions
    if (currentBalance < 1000) {
        cout << getColoredText("You're broke. Stop checking balance every few minutes later, this won't magically go up!\n", "yellow");
    }
    else if (currentBalance < 5000) {
        cout << getColoredText("Ask your father for money. This is embarrassing.\n", "yellow");
    }
    else if (currentBalance < 20000) {
        cout << getColoredText("That's pocket money level. Don't get too excited.\n", "yellow");
    }
    else if (currentBalance < 100000) {
        cout << getColoredText("Okay okay, now you're middle class rich.\n", "yellow");
    }
    else if (currentBalance >= 1000000) {
        cout << getColoredText("You're a rich kid number two. Respect!\n", "yellow");
    }
}


void depositMoney() {
    clearConsole();
    printMainHeader("Deposit Money");

    float amount = getInputNumber("Enter amount to deposit: ");

    if (amount <= 0) {
        cout << getColoredText("Trying to deposit negative cash? The system is not fool as you think!\n", "yellow");
        return;
    }

    currentBalance += amount;

    cout << getColoredText("\nDeposited the amount successfully!\n\n", "green");
    cout << getColoredText("Amount deposited: ", "white", "", "bold") << "\033[47m\033[1m " << fixed << setprecision(2) << amount << " won " << "\033[0m\n";
    cout << getColoredText("New balance is: ", "white", "", "bold") << "\033[44m\033[1m " << currentBalance << " won " << "\033[0m\n";
}

void withdrawMoney() {
    clearConsole();
    printMainHeader("Withdraw Money");

    cout << getColoredText("\nCurrent balance is: ", "white", "", "bold") << "\033[47m\033[1m " << fixed << setprecision(2) << currentBalance << " won " << "\033[0m\n";
    float amount = getInputNumber("Enter amount to withdraw: ");

    if (amount <= 0) {
        cout << getColoredText("You're trying to withdraw air? Nice try.\n", "yellow");
        return;
    }

    if (amount > currentBalance) {
        cout << getColoredText("Insufficient funds! Stop acting rich, you're not Elon Musk.\n", "red");
        if (currentBalance < 500) {
            cout << getColoredText("Even your balance is shy to show up. Time to hustle!\n", "magenta");
        }
        return;
    }

    currentBalance -= amount;

    cout << getColoredText("\nWithdrawal amount successfully!\n", "green");
    cout << getColoredText("Amount withdrawn: ", "white", "", "bold") << "\033[47m\033[1m " << amount << " won " << "\033[0m\n\n";
    cout << getColoredText("New balance is: ", "white", "", "bold") << "\033[44m\033[1m " << currentBalance << " won " << "\033[0m\n";

    if (currentBalance < 10000) {
        cout << getColoredText("Now your wallet is on a diet. Good luck surviving!\n", "yellow");
    }
}


void logoutUser() {
    sessionUser = "";
    cout << getColoredText("\nLogging out...\n", "green");
    cout << getColoredText("Remember, money doesn't grow on trees unless you're coding for Apple.\n", "yellow");
    cout << getColoredText("You’ve logged out successfully. Now go touch some grass or earn some cash!\n", "cyan");
}


// Main menu
void mainMenu() {
    while (true) {
        clearConsole();

        if (sessionUser == "") {
            printMainHeader("Login/Register");
            cout << getColoredText("1. Login\n", "white", "", "bold");
            cout << getColoredText("2. Register\n", "white", "", "bold");
            cout << getColoredText("3. Exit\n", "white", "", "bold");

            int choice = (int)getInputNumber("Choose an option (1-3): ");
            if (choice == 1) loginUser();
            else if (choice == 2)registerUser();
            else if (choice == 3) break;
            else cout << getColoredText("Invalid choice!\n", "red");
        } else {
            printMainHeader("Dashboard - " + sessionUser);
            cout << getColoredText("1. Check Balance\n", "white", "", "bold");
            cout << getColoredText("2. Deposit Money\n", "white", "", "bold");
            cout << getColoredText("3. Withdraw Money\n", "white", "", "bold");
            cout << getColoredText("4. Logout\n", "white", "", "bold");

            int choice = (int)getInputNumber("Choose an option (1-4): ");
            if (choice == 1) checkBalance();
            else if (choice == 2) depositMoney();
            else if (choice == 3) withdrawMoney();
            else if (choice == 4) logoutUser();
            else cout << getColoredText("Invalid choice!\n", "red");
        }

        cout << getColoredText("\nPress Enter to continue...", "white", "", "dim");
        cin.get();
    }
}

// Main
int main() {
    mainMenu();
    return 0;
}
