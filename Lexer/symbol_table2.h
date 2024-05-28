#include <iostream>
#include <string>

using namespace std;

const int roll = 24, table_size = 29; // 24+5

class Symbol_Info {
private:
    string name, type;

public:
    Symbol_Info *next, *prev;
    Symbol_Info() {
        this->name = "";
        this->type = "";
        this->next = NULL;
        this->prev = NULL;
    }
    Symbol_Info(string n, string t) {
        this->name = n;
        this->type = t;
        this->next = NULL;
        this->prev = NULL;
    }
    string getName() { return name; }
    string getType() { return type; }
    void setName(string t) { this->name = t; }
    void setType(string t) { this->type = t; }
};

class SymbolTable {
private:
    Symbol_Info *snf[table_size];

public:
    SymbolTable() {
        for (int i = 0; i < table_size; ++i)
            snf[i] = NULL;
    }

    int hash(string name) {
        int s = 0;
        for (int i = 0; name[i]; i++) s += name[i];
        return (s * roll) % table_size;
    }

    void insert(Symbol_Info *newT) {
        string newName = newT->getName(), newType = newT->getType();
        int id = hash(newName), the_ind = 1;
        if (!snf[id]) {
            snf[id] = new Symbol_Info(newName, newType);
            cout << "Inserted at position " << id << ", 0\n";
        } else {
            Symbol_Info *tmp = snf[id], *newS = NULL;
            if (tmp->getName() == newName && tmp->getType() == newType) {
                cout << "Already Exists\n";
                return;
            }
            while (tmp->next) {
                tmp = tmp->next;
                the_ind++;
            }
            newS = new Symbol_Info(newName, newType);
            newS->prev = tmp;
            tmp->next = newS;
            cout << "Inserted at position " << id << ", " << the_ind << "\n";
        }
    }

    void insert(string newName, string newType) {
        int id = hash(newName), the_ind = 1;
        if (!snf[id]) {
            snf[id] = new Symbol_Info(newName, newType);
            cout << "Inserted at position " << id << ", 0\n";
        } else {
            Symbol_Info *tmp = snf[id], *newS = NULL;
            if (tmp->getName() == newName && tmp->getType() == newType) {
                cout << "Already Exists\n";
                return;
            }
            while (tmp->next) {
                tmp = tmp->next;
                the_ind++;
            }
            newS = new Symbol_Info(newName, newType);
            newS->prev = tmp;
            tmp->next = newS;
            cout << "Inserted at position " << id << ", " << the_ind << "\n";
        }
    }

    Symbol_Info *lookUp(string si, bool c = true) {
        int id = hash(si);
        if (snf[id]) {
            if (snf[id]->getName() == si) {
                cout << (c ? "Found at " : "Deleted from ") << id << ", 0\n";
                return snf[id];
            } else {
                Symbol_Info *tmp = snf[id];
                int newIndex = 0;
                while (tmp) {
                    if (tmp->getName() == si) {
                        cout << (c ? "Found at " : "Deleted from ") << id << "," << newIndex << "\n";
                        return tmp;
                    }
                    tmp = tmp->next;
                    newIndex++;
                }
            }
        } else {
            cout << (c ? "Not Found\n" : "Doesn't Exist\n");
        }
        return NULL;
    }

    void print() {
        for (int i = 0; i < table_size; ++i) {
            cout << i << (i < 10 ? "-->" : "->");
            if (snf[i]) {
                cout << " < " << snf[i]->getName() << ", " << snf[i]->getType() << " > ";
                Symbol_Info *tmp = snf[i]->next;
                int ind = 1;
                while (tmp) {
                    cout << " < " << tmp->getName() << ", " << tmp->getType() << " > ";
                    tmp = tmp->next;
                }
            }
            cout << "\n";
        }
    }

    void del(string toDel) {
        Symbol_Info* tmp = lookUp(toDel, false);
        if (!tmp) {
            return;
        }
        int id = hash(toDel);
        if (tmp->next) {
            if (tmp->prev) {
                tmp->next->prev = tmp->prev;
                tmp->prev->next = tmp->next;
            } else {
                snf[id] = tmp->next;
            }
            delete tmp;
        } else {
            if (tmp->prev) {
                tmp->prev->next = NULL;
            } else {
                snf[id] = NULL;
            }
            delete tmp;
        }
    }
};
