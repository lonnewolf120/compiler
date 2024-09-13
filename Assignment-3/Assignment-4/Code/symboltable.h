#include <bits/stdc++.h>
using namespace std;

const int roll = 24, table_size = 29; // 24+5

int line_cnt=1, error_cnt=0;

void fcout(string token, string symbol="") {
    ofstream op2;
    op2.open("token.txt", ios::app);
    if (!op2.is_open()) {
        cerr << "Error opening file.\n";
    }
    (symbol=="")?op2<<"<"<<token<<">": op2<<"<"<<token<<", "<<symbol<<">";
    op2.close();
}

void logf(string msg=""){
    ofstream output;
    output.open("log_errpr.txt", ios::app);
    output<<msg;
    output.close();
}
/*explanation for ffcout:
int c is used to say how text will be added into output, 
0 for normal <Token, Lexeme> found
other values for "already exists" type of stuff...
*/
void ffcout(string token, string symbol="", int c=0){
    ofstream output;
    output.open("log_error.txt", ios::app);
    if (!output.is_open()) {
        cerr << "Error opening log_error.txt file.\n";
    }
    
    output << "Line No: " << line_cnt << " ";
    output << "Token <" << token << "> Lexeme " << symbol << " found\n";
    if(c){
        if (token=="ID") {
        output << symbol << " variable already exists\n";
        } else if (token=="CONST_INT" || token=="CONST_FLOAT") {
            output << symbol << " value already exists\n";
        } else if (token=="CONST_CHAR") {
            output << symbol << " character already exists\n";
        }
    } 
    output.close();
}

void yyerror(string msg) {
    error_cnt++;
    ofstream output;
    output.open("log_error.txt", ios::app);
    if (!output.is_open()) {
        cerr << "Error opening file.\n";
    }    
    output << "Error at Line No: " << line_cnt <<" ";
    output << msg << "\n";
    output.close();
}

void clearOutput() {
    ofstream output;
    output.open("log_error.txt", ios::trunc);
    if (!output.is_open()) {
        cerr << "Error delete file contents.\n";
    }
    output.close();
    output.open("token.txt", ios::trunc);
    if (!output.is_open()) {
        cerr << "Error delete file contents.\n";
    }
    output.close();
}


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
    void setsymbol(string t) { this->symbol = t; }
    void settoken(string t) { this->token = t; }
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
        ofstream output;
        output.open("202214024_log.txt", ios::app);
        for (int i = 0; i < table_size; ++i) {
            output << (string(to_string(i) + ((i < 10) ? "-->" : "->")));
            if (!snf[i].empty()) {
                for (int j = 0; j < snf[i].size(); ++j) {
                    output<<(("<" + snf[i][j]->getToken() + "," + snf[i][j]->getSymbol() + ">"));
                }
            }
            output<<("\n");
        }
        output.close();
    }

    Symbol_Info* lookUp(string si, string token, bool c = true) {
        int id = hash(si, token);
        if (!snf[id].empty()) {
            for (auto i:snf[id]) {
                if (i->getSymbol() == si) {
                    // fcout(((c) ? "Found at " : "Deleted from ") + to_string(id) + ", " + to_string(i) + "\n");
                    return i;
                }
            }
        }
        //fcout((c) ? "Not Found\n" : "Doesn't Exist\n");
        return nullptr;
    }


    void insert(Symbol_Info* newT) {
        string symbol = newT->getSymbol();
        string token = newT->getToken();
        int id = hash(symbol, token);

        if(snf[id].empty()){
            ffcout(token, symbol);
            snf[id].push_back(new Symbol_Info(symbol, token));
            print();
        }
        else{
            Symbol_Info* tmp = lookUp(symbol, token);
            if(tmp==nullptr) {
                snf[id].push_back(new Symbol_Info(symbol, token));    
                ffcout(token, symbol);
                print();
            }
            else{
                ffcout(token, symbol,2);
            }
        }

        // fcout("<" + token + ", " + symbol + ">");
        // print();
    }


    void insert(string symbol, string token) {
        int id = hash(symbol, token);

        if(snf[id].empty()){
            ffcout(token, symbol);
            snf[id].push_back(new Symbol_Info(symbol, token));
            print();
        }
        else{
            Symbol_Info* tmp = lookUp(symbol, token);
            if(tmp==nullptr) {
                snf[id].push_back(new Symbol_Info(symbol, token));    
                ffcout(token, symbol);
                print(); 
            }
            else{
                ffcout(token, symbol,2);
            }
        }

        // fcout("<" + token + ", " + symbol + ">");
        // print();
    }

    void del(string toDel, string token) {
        int id = hash(toDel, token);
        if (!snf[id].empty()) {
            for (int i = 0; i < snf[id].size(); ++i) {
                if (snf[id][i]->getSymbol() == toDel) {
                    snf[id].erase(snf[id].begin() + i);
                    // fcout("Deleted " + toDel + " from position " + to_string(id) + ", " + to_string(i) + "\n");
                    return;
                }
            }
        }
        // fcout("Couldn't delete " + toDel + " as it doesn't exist\n");
    }
};
