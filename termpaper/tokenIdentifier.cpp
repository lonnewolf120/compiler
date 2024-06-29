#include <bits/stdc++.h>

using namespace std;

enum TYPE
{
    NUM,    // 0
    CN,     // 1
    INVALID // 2
};

class TOKEN
{
private:
    string attribute;
    TYPE type;

public:
    TOKEN()
    {
        attribute = "";
        type = TYPE::CN;
    }
    TOKEN(string s, TYPE t)
    {
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

char nextChar()
{
    if (ind < inp.size())
    {
        return inp[ind++];
    }
    return '\0';
}

void retract()
{
    if (ind > 0)
        ind--;
}

void fail(int n = 1)
{
    if (n == 1)
        cerr << "ERROR: Invalid Complex Number & the numbers weren't properly formatted\n";
    else
        cerr << "ERROR: Invalid Complex number\n";
    exit(1);
}

TOKEN getNumber()
{
    TOKEN retToken;
    int state = 12;
    char c;
    string tokenValue = "";

    while (true)
    {
        switch (state)
        {
        case 12:
            c = nextChar();
            if (isdigit(c))
            {
                state = 13;
                tokenValue += c;
            }
            else
            {
                //FIXME: the other symbol can also be i, so can't use fail() here
                // cout<<"from case 12"<<endl;
                // fail();
                retract();
                retToken.setAttr(tokenValue);
                retToken.setType(TYPE::NUM);
                return retToken;
            }
            break;
        case 13:
            c = nextChar();
            if (isdigit(c))
            {
                state = 13;
                tokenValue += c;
            }
            else if (c == '.')
            {
                state = 14;
                tokenValue += c;
            }
            else if (toupper(c) == 'E')
            {
                state = 16;
                tokenValue += c;
            }
            else
            {
                retract();
                retToken.setType(TYPE::NUM);
                retToken.setAttr(tokenValue);
                return retToken;
            }
            break;
        case 14:
            c = nextChar();
            if (isdigit(c))
            {
                state = 15;
                tokenValue += c;
            }
            else
            {
                fail();
            }
            break;
        case 15:
            c = nextChar();
            if (isdigit(c))
            {
                state = 15;
                tokenValue += c;
            }
            else if (toupper(c) == 'E')
            {
                state = 16;
                tokenValue += c;
            }
            else
            {
                retract();
                retToken.setType(TYPE::NUM);
                retToken.setAttr(tokenValue);
                return retToken;
            }
            break;
        case 16:
            c = nextChar();
            if (isdigit(c))
            {
                state = 18;
                tokenValue += c;
            }
            else if (c == '+' || c == '-')
            {
                state = 17;
                tokenValue += c;
            }
            else
            {
                fail();
            }
            break;
        case 17:
            c = nextChar();
            if (isdigit(c))
            {
                state = 18;
                tokenValue += c;
            }
            else
            {
                fail();
            }
            break;
        case 18:
            c = nextChar();
            if (isdigit(c))
            {
                state = 18;
                tokenValue += c;
            }
            else
            {
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

TOKEN getCN()
{
    TOKEN retToken, tmp;
    int state = 22;
    string tokenValue = "";
    char c;
    while (1)
    {
        switch (state)
        {
        case 22:
            c = nextChar();
            if (c == '+' || c == '-')
            {
                state = 24;
                tokenValue += c;
            }
            else if (c == 'i')
            {
                state = 26;
                tokenValue += c;
            }
            else
            {
                tmp = getNumber();
                if (tmp.getType() == TYPE::NUM)
                {
                    state = 23;
                    tokenValue += tmp.getAttr();
                }
                else if (tmp.getType() == TYPE::INVALID)
                {
                    cout << "from case 22:" << endl;
                    fail(1);
                }
            }
            break;
        case 23:
            c = nextChar();
            if (c == '+' || c == '-')
            {
                state = 24;
                tokenValue += c;
            }
            else if (c == 'i')
            {
                state = 26;
                tokenValue += c;
            }
            else
            {
                cout << "from case 23:" << endl;
                fail(2);
            }
            break;
        case 24:
            c = nextChar();
            if (c == 'i')
            {
                state = 26;
                tokenValue += c;
            }
            else
            {
                tmp = getNumber();
                if (tmp.getType() == TYPE::NUM)
                {
                    state = 25;
                    tokenValue += tmp.getAttr();
                }
                else if (tmp.getType() == TYPE::INVALID)
                {
                    // retToken.setType(TYPE::INVALID);
                    // return retToken;
                    cout << "from case:24 " << endl;
                    fail(1);
                }
            }
            break;
        case 25:
            c = nextChar();
            if (c == 'i')
            {
                state = 26;
                tokenValue += c;
            }
            else
            {
                cout << "from case 25:" << endl;
                fail(2);
            }
            break;
        case 26:
            // no need to retract as we already got i
            //  retract()
            retToken.setType(TYPE::CN);
            retToken.setAttr(tokenValue);
            return retToken;
            break;
        default:
            cout << "from default:" << endl;
            fail(2);
        }
    }
}

int main()
{
    cin>>inp;
    // inp = "123.456E-78+123.456Ei"; // Example input
    TOKEN token = getCN();
    cout << "<";
    switch (token.getType())
    {
    case 0:
        cout << "NUMBER,";
        break;
    case 1:
        cout << "COMPLEX-NUMBER,";
        break;
    default:
        cout << "INAVLID-NUM,";
    }
    cout << token.getAttr() << ">" << endl;
    return 0;
}
