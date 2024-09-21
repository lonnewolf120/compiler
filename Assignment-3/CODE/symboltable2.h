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
    unordered_map<int, vector<Symbol_Info*>> snf;  // Change to unordered_map

public:
    SymbolTable() {}

    int hash(string symbol, string token) {
    int s = 0;
    int p_pow = 1;
    for (char c : symbol) {
        s = (s + (c - 'a' + 1) * p_pow) % table_size;
        p_pow = (p_pow * roll) % table_size;
    }
    for (char c : token) {
        s = (s + (c - 'a' + 1) * p_pow) % table_size;
        p_pow = (p_pow * roll) % table_size;
    }
    return s % table_size;
}

    void print() {
        for (int i = 0; i < table_size; ++i) {
            output << to_string(i) + ((i < 10) ? "-->" : "->");
            // Check if the bucket for this index exists in the unordered_map
            if (snf.find(i) != snf.end() && !snf[i].empty()) {
                // Print the index and the symbols in this bucket
                for (Symbol_Info* symbol_info : snf[i]) {
                    output << "<" + symbol_info->getSymbol() + " " + symbol_info->getToken() + ">";
                }
            }
            output << "\n";
        }
    }


    void clear() {
        for (auto& pair : snf) {
            for (Symbol_Info* symbol : pair.second) {
                delete symbol;  // Free dynamically allocated memory
            }
            pair.second.clear();  // Clear the vector for this bucket
        }
        snf.clear();  // Clear the entire unordered_map
        // logErr << "Symbol table cleared.\n";  // Optionally log this operation
    }

    Symbol_Info* lookUp(string si, string token, bool c = true) {
        int id = hash(si, token);
        if (snf.find(id) != snf.end()) {  // Check if the hash key exists in the map
            for (auto* i : snf[id]) {
                if (i->getSymbol() == si && i->getToken() == token) {
                    return i;
                }
            }
        }
        return nullptr;
    }

    bool insert(string symbol, string token, int line_number) {
        int id = hash(symbol, token);

        Symbol_Info* tmp = lookUp(symbol, token);
        if (tmp == nullptr) {
            snf[id].push_back(new Symbol_Info(symbol, token));  // Directly insert into the map
            return true;
        } else {
            // logErr << "Line Number: " << line_number << "\n" << symbol << " is already declared\n";
            return false;
        }
    }

    void del(string toDel, string token) {
        int id = hash(toDel, token);
        if (snf.find(id) != snf.end()) {
            for (int i = 0; i < snf[id].size(); ++i) {
                if (snf[id][i]->getSymbol() == toDel) {
                    delete snf[id][i];  // Free the memory to prevent memory leaks
                    snf[id].erase(snf[id].begin() + i);
                    logErr << "Deleted " + toDel + " from position " + to_string(id) + ", " + to_string(i) + "\n";
                    return;
                }
            }
        }
        logErr << "Couldn't delete " + toDel + " as it doesn't exist\n";
    }

    ~SymbolTable() {
        clear();  // Use the clear method to clean up memory
        output.close(); // Close output in the destructor
        logErr.close(); // Close logErr in the destructor
    }
};
