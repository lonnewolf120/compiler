#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

// Function to identify and classify tokens as complex numbers
void identifyTokens(const vector<string>& tokens) {
    // Regular expressions for the patterns
    regex digitPattern("[0-9]+");
    regex numberPattern(R"((([0-9]+)(\.[0-9]+)?(E[+-]?[0-9]+)?)|(\.[0-9]+(E[+-]?[0-9]+)?))");
    regex complexNumberPattern(R"((([0-9]+(\.[0-9]+)?(E[+-]?[0-9]+)?)|(\.[0-9]+(E[+-]?[0-9]+)?))[+-](([0-9]+(\.[0-9]+)?(E[+-]?[0-9]+)?)|(\.[0-9]+(E[+-]?[0-9]+)?))?i|[+-]?(([0-9]+(\.[0-9]+)?(E[+-]?[0-9]+)?)|(\.[0-9]+(E[+-]?[0-9]+)?))?i)");

    for (const string& token : tokens) {
        if (regex_match(token, complexNumberPattern)) {
            cout << "Complex Number: " << token << endl;
        } else if (regex_match(token, numberPattern)) {
            cout << "Number: " << token << endl;
        } else if (regex_match(token, digitPattern)) {
            cout << "Digit: " << token << endl;
        } else {
            cout << "Other: " << token << endl;
        }
    }
}

int main() {
    // Example tokens
    vector<string> tokens = {
        "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26",
        "3.14", "-3.14", "1.2E10", "2.5E-3", "-2.5E+3", "i", "3+2i", "-2.5E3-7.8i", "+5i"
    };

    // Identify and classify tokens
    identifyTokens(tokens);

    return 0;
}
