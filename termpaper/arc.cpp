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
        type = TYPE::CN;
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

TOKEN getCN() {
    TOKEN retToken;
    int state = 26;
    char c;
    string tokenValue = "";

    while (true) {
        switch (state) {
        case 26:
            c = nextChar();
            if (isdigit(c)) {
                state = 25;
                tokenValue += c;
            } else if (c == 'i') {
                state = 22;
                tokenValue += c;
            } else if (c == '+' || c == '-') {
                state = 24;
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
                state = 22;
                tokenValue += c;
            } else if (c == '+' || c == '-') {
                state = 24;
                tokenValue += c;
            } else {
                retract();
                retToken.setType(TYPE::NUM);
                retToken.setAttr(tokenValue);
                return retToken;
            }
            break;
        case 24:
            c = nextChar();
            if (isdigit(c)) {
                state = 23;
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
                state = 22;
                tokenValue += c;
            } else {
                fail();
            }
            break;
        case 22:
            retToken.setType(TYPE::CN);
            retToken.setAttr(tokenValue);
            return retToken;
        default:
            fail();
        }
    }
}

int main() {
    inp = "3+4i";  // Example input
    TOKEN token = getCN();
    cout << "attribute: " << token.getAttr() << ", Type: " << token.getType() << endl;
    return 0;
}
