#include <bits/stdc++.h>

using namespace std;

enum TYPE {
    NUM,
    CN,
    INVALID
};

class TOKEN {
private:
    string attribute;
    TYPE type;

public:
    TOKEN() {
        attribute = "";
        type = TYPE::INVALID;
    }
    TOKEN(string s, TYPE t) {
        attribute = s;
        type = t;
    }
    string getAttr() { return attribute; }
    TYPE getType() { return type; }
    void setAttr(string s) { attribute = s; }
    void setType(TYPE t) { type = t; }
};

static string inp;
static int ind = 0;

char nextChar() {
    if (ind < inp.size()) {
        return inp[ind++];
    }
    return '\0';
}

void retract() {
    if (ind > 0)
        ind--;
}

void fail() {
    cerr << "ERROR: Invalid Complex number\n";
    exit(1);
}

TOKEN getNumber() {
    TOKEN retToken;
    int state = 12;
    char c;
    string tokenValue = "";

    while (true) {
        switch (state) {
        case 12:
            c = nextChar();
            if (isdigit(c)) {
                state = 13;
                tokenValue += c;
            } else {
                fail();
            }
            break;
        case 13:
            c = nextChar();
            if (isdigit(c)) {
                state = 13;
                tokenValue += c;
            } else if (c == '.') {
                state = 14;
                tokenValue += c;
            } else if (toupper(c) == 'E') {
                state = 16;
                tokenValue += c;
            } else {
                retract();
                retToken.setType(TYPE::NUM);
                retToken.setAttr(tokenValue);
                return retToken;
            }
            break;
        case 14:
            c = nextChar();
            if (isdigit(c)) {
                state = 15;
                tokenValue += c;
            } else {
                fail();
            }
            break;
        case 15:
            c = nextChar();
            if (isdigit(c)) {
                state = 15;
                tokenValue += c;
            } else if (toupper(c) == 'E') {
                state = 16;
                tokenValue += c;
            } else {
                retract();
                retToken.setType(TYPE::NUM);
                retToken.setAttr(tokenValue);
                return retToken;
            }
            break;
        case 16:
            c = nextChar();
            if (isdigit(c)) {
                state = 18;
                tokenValue += c;
            } else if (c == '+' || c == '-') {
                state = 17;
                tokenValue += c;
            } else {
                fail();
            }
            break;
        case 17:
            c = nextChar();
            if (isdigit(c)) {
                state = 18;
                tokenValue += c;
            } else {
                fail();
            }
            break;
        case 18:
            c = nextChar();
            if (isdigit(c)) {
                state = 18;
                tokenValue += c;
            } else {
                retract();
                retToken.setType(TYPE::NUM);
                retToken.setAttr(tokenValue);
                return retToken;
            }
            break;
        default:
            fail();
        }
    }
}

TOKEN getComplexNumber() {
    TOKEN retToken;
    int state = 22;
    char c;
    string tokenValue = "";

    while (true) {
        switch (state) {
        case 22:
            c = nextChar();
            if (isdigit(c)) {
                state = 23;
                tokenValue += c;
            } else if (c == '+' || c == '-') {
                state = 24;
                tokenValue += c;
            } else if (c == 'i') {
                state = 26;
                tokenValue += c;
            } else {
                fail();
            }
            break;
        case 23:
            c = nextChar();
            if (isdigit(c)) {
                state = 23;
                tokenValue += c;
            } else if (c == 'i') {
                state = 26;
                tokenValue += c;
            } else if (c == '+' || c == '-') {
                state = 24;
                tokenValue += c;
            } else {
                fail();
            }
            break;
        case 24:
            c = nextChar();
            if (isdigit(c)) {
                state = 25;
                tokenValue += c;
            } else if (c == 'i') {
                state = 26;
                tokenValue += c;
            } else {
                fail();
            }
            break;
        case 25:
            c = nextChar();
            if (isdigit(c)) {
                state = 25;
                tokenValue += c;
            } else if (c == 'i') {
                state = 26;
                tokenValue += c;
            } else {
                fail();
            }
            break;
        case 26:
            retToken.setType(TYPE::CN);
            retToken.setAttr(tokenValue);
            return retToken;
        default:
            fail();
        }
    }
}

int main() {
    cin >> inp;
    // inp = "3+4i";  // Example input for complex number
    TOKEN token = getNumber();
    cout << "attribute: " << token.getAttr() << ", Type: " << token.getType() << endl;
    return 0;
}
