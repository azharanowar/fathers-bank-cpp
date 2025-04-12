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