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

void fail(int n) {
    if(n==1)cerr<<"ERROR: Invalid Complex Number & the numbers weren't properly formatted\n";
    else cerr << "ERROR: Invalid Complex number\n";
    exit(1);
}

TOKEN getNumber() {
    TOKEN retToken;
    int state = 12;
    char c;

    while (true) {
        switch (state) {
        case 12:
            c = nextChar();
            if (isdigit(c))
                state = 13;
            else{
                // fail();
                retToken.setType(TYPE::INVALID);
                return retToken;
            }
            break;
        case 13:
            c = nextChar();
            if (isdigit(c)) {
                state = 13;
            } else if (c == '.') {
                state = 14;
            } else if (toupper(c) == 'E') {
                state = 16;
            } else {
                state = 20;
            }
            break;
        case 14:
            c = nextChar();
            if (isdigit(c))
                state = 15;
            else{
                // fail();
                retToken.setType(TYPE::INVALID);
                return retToken;            
            }
            break;
        case 15:
            c = nextChar();
            if (isdigit(c)) {
                state = 15;
            } else if (toupper(c) == 'E') {
                state = 16;
            } else {
                state = 21;
            }
            break;
        case 16:
            c = nextChar();
            if (isdigit(c)) {
                state = 18;
            } else if(c == '+' || c == '-'){
                state = 17;
            }
             else {
                // fail();
                retToken.setType(TYPE::INVALID);
                return retToken;            
            }
            break;
        case 17:
            c = nextChar();
            if (isdigit(c)) {
                state = 18;
            } else{
                // fail();
                retToken.setType(TYPE::INVALID);
                return retToken;
            }
            break;
        case 18:
            c = nextChar();
            if(isdigit(c))
                state = 18;
            else {
                // fail();
                retToken.setType(TYPE::INVALID);
                return retToken;
            }
            break;
        case 19:
            retract();
            retToken.setType(TYPE::NUM);
            return retToken;
            break;
        case 20:
            retract();
            retToken.setType(TYPE::NUM);
            return retToken;
            break;
        case 21:
            retract();
            retToken.setType(TYPE::NUM);
            return retToken;
            break;
        default:
            // fail();
            retToken.setType(TYPE::INVALID);
            return retToken;
        }
    }
}

TOKEN getCN(){
    TOKEN retToken, tmp;
    int state = 22;
    char c;
    while(1){
        switch(state){
            case 22:
                c=nextChar();
                if(c=='+'||c=='-') state = 24;
                else if(c=='i') state = 26;
                else {
                    //FIXME: getNumber() has an infinite loop (while(1)) inside it
                    tmp = getNumber();
                    if(tmp.getType()==TYPE::NUM){
                        state = 23;
                    }
                    else if(tmp.getType()==TYPE::INVALID){
                        fail(1);
                    }
                }
                break;
            case 23:
                c=nextChar();
                if(c=='+'||c=='-') state = 24;
                else if(c=='i') state = 26;
                else {
                    fail(2);
                }
                break;
            case 24:
                c=nextChar();
                if(c=='i') state = 26;
                else{
                    tmp=getNumber();
                    if(tmp.getType()==TYPE::NUM){
                        state = 25;
                    }
                    else if(tmp.getType()==TYPE::INVALID){
                        // retToken.setType(TYPE::INVALID);
                        // return retToken;
                        fail(1);
                    }
                }
                break;
            case 25:
                c=nextChar();
                if(c=='i'){
                    state = 26;
                }
                else{
                    fail(2);
                }
                break;
            case 26:
                //no need to retract as we already got i
                // retract()
                retToken.setType(TYPE::CN);
                return retToken;
                break;
            default:
                fail(2);
        }
    }
}

int main() {
    inp = "123.456E-78+123.456E-78i";  // Example input
    TOKEN token = getCN();
    cout << "attribute: " << token.getAttr() << ", Type: " << token.getType() << endl;
    return 0;
}
