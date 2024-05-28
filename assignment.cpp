#include <bits/stdc++.h>
using namespace std;

const int roll = 24, table_size = roll + 5; // 24 + 5

class Symbol_Info {
private:
    string name, type;

public:
    Symbol_Info *next, *prev;
    Symbol_Info(string n = "", string t = "") : name(n), type(t), next(nullptr), prev(nullptr) {}
    
    string getName() { return name; }
    string getType() { return type; }
    void setName(string t) { this->name = t; }
    void setType(string t) { this->type = t; }
};

class SymbolTable {
private:
    vector<Symbol_Info*> snf;

    int hash(string name) {
        int s = 0;
        for (char c : name) s += c;
        return (s * roll) % table_size;
    }

public:
    SymbolTable() : snf(table_size, nullptr) {}

    void insert(Symbol_Info *newT) {
        string newName = newT->getName(), newType = newT->getType();
        int id = hash(newName), the_ind = 0;

        if (!snf[id]) {
            snf[id] = new Symbol_Info(newName, newType);
            cout << "Inserted at position " << id << ", 0\n";
        } else {
            Symbol_Info *tmp = snf[id];
            while (tmp) {
                if (tmp->getName() == newName) {
                    cout << "Already Exists\n";
                    return;
                }
                if (!tmp->next) break;
                tmp = tmp->next;
                the_ind++;
            }
            Symbol_Info *newS = new Symbol_Info(newName, newType);
            tmp->next = newS;
            newS->prev = tmp;
            cout << "Inserted at position " << id << ", " << the_ind + 1 << "\n";
        }
    }

    Symbol_Info* lookUp(string si, bool print = true) {
        int id = hash(si);
        Symbol_Info *tmp = snf[id];
        int idx = 0;

        while (tmp) {
            if (tmp->getName() == si) {
                if (print) cout << "Found at " << id << ", " << idx << "\n";
                return tmp;
            }
            tmp = tmp->next;
            idx++;
        }
        if (print) cout << "Not Found\n";
        return nullptr;
    }

    void del(string toDel) {
        Symbol_Info* tmp = lookUp(toDel, false);
        if (!tmp) {
            cout << "Doesn't Exist\n";
            return;
        }
        int id = hash(toDel);

        if (tmp->prev) tmp->prev->next = tmp->next;
        else snf[id] = tmp->next;

        if (tmp->next) tmp->next->prev = tmp->prev;

        delete tmp;
        cout << "Deleted from " << id << "\n";
    }

    void print() {
        for (int i = 0; i < table_size; ++i) {
            cout << i << " -->";
            Symbol_Info *tmp = snf[i];
            while (tmp) {
                cout << " < " << tmp->getName() << ", " << tmp->getType() << " >";
                tmp = tmp->next;
            }
            cout << "\n";
        }
    }
};

int main() {
    cout << "------- INPUT Taken from input.txt -------\n";
    cout << "------- OUTPUT will be in output.txt -------\n";
    SymbolTable mySymbolTable;

    ifstream input("input.txt");
    if (!input) {
        cerr << "Error opening input file.\n";
        return 1;
    }

    ofstream output("output.txt", ios::trunc);
    if (!output) {
        cerr << "Error opening output file.\n";
        return 1;
    }

    streambuf *coutbuf = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    char c;
    while (input >> c) {
        if (c == 'I') {
            string n, t;
            input >> n >> t;
            Symbol_Info *tmp = new Symbol_Info(n, t);
            mySymbolTable.insert(tmp);
        } else if (c == 'P') {
            mySymbolTable.print();
        } else if (c == 'L') {
            string symbol;
            input >> symbol;
            mySymbolTable.lookUp(symbol);
        } else if (c == 'D') {
            string symbol;
            input >> symbol;
            mySymbolTable.del(symbol);
        } else {
            cout << "Invalid operation\n";
        }
    }

    cout.rdbuf(coutbuf);
    return 0;
}
