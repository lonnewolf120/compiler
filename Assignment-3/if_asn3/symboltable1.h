#include <bits/stdc++.h>
using namespace std;

const int roll = 24, table_size = 29; // 24 + 5

ofstream output("log.txt");
ofstream logErr("log_error.txt");

class Symbol_Info {
private:
    string symbol, token;

public:
    Symbol_Info() {
        this->symbol = "";
        this->token = "";
    }
    Symbol_Info(string n, string t) {
        this->symbol = n;
        this->token = t;
    }
    string getSymbol() { return symbol; }
    string getToken() { return token; }
    void setSymbol(string t) { this->symbol = t; }
    void setToken(string t) { this->token = t; }
};

class SymbolTable {
private:
    vector<Symbol_Info*> snf[table_size];

public:
    SymbolTable() {}

    int hash(string symbol, string token) {
        int s = 0;
        for (int i = 0; symbol[i]; i++) s += symbol[i];
        for (int i = 0; token[i]; i++) s += token[i];
        return (s * (roll)) % table_size;
    }

    void print() {
        for (int i = 0; i < table_size; ++i) {
            output << (string)(to_string(i) + ((i < 10) ? "-->" : "->"));
            if (!snf[i].empty()) {
                for (int j = 0; j < snf[i].size(); ++j) {
                    output << ("<" + snf[i][j]->getSymbol() + " " + snf[i][j]->getToken() + ">");
                }
            }
            output << "\n";
        }
        // Do not close output here, allow it to be used throughout the program
    }
    void clear() {
        for (int i = 0; i < table_size; ++i) {
            for (Symbol_Info* symbol : snf[i]) {
                delete symbol;  // Free dynamically allocated memory
            }
            snf[i].clear();  // Clear the vector for this bucket
        }
        logErr << ("Symbol table cleared.\n");  // Optionally log this operation
    }

    Symbol_Info* lookUp(string si, string token, bool c = true) {
        int id = hash(si, token);
        if (!snf[id].empty()) {
            for (auto i : snf[id]) {
                if (i->getSymbol() == si) {
                    return i;
                }
            }
        }
        return nullptr;
    }

    void insert(string symbol, string token) {
        int id = hash(symbol, token);

        if (snf[id].empty()) {
            snf[id].push_back(new Symbol_Info(symbol, token));
        } else {
            Symbol_Info* tmp = lookUp(symbol, token);
            if (tmp == nullptr) {
                snf[id].push_back(new Symbol_Info(symbol, token));
            }
            else{
                logErr << symbol << " is already declared\n";
            }
        }
    }

    void del(string toDel, string token) {
        int id = hash(toDel, token);
        if (!snf[id].empty()) {
            for (int i = 0; i < snf[id].size(); ++i) {
                if (snf[id][i]->getSymbol() == toDel) {
                    delete snf[id][i];  // Free the memory to prevent memory leaks
                    snf[id].erase(snf[id].begin() + i);
                    logErr << ("Deleted " + toDel + " from position " + to_string(id) + ", " + to_string(i) + "\n");
                    return;
                }
            }
        }
        logErr << ("Couldn't delete " + toDel + " as it doesn't exist\n");
    }

    ~SymbolTable() {
        // Clean up all dynamically allocated memory
        for (int i = 0; i < table_size; ++i) {
            for (Symbol_Info* symbol : snf[i]) {
                delete symbol;
            }
            snf[i].clear();
        }
        output.close(); // Close output in the destructor
        logErr.close(); // Close logErr in the destructor
    }
};
