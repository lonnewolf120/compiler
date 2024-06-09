#include <bits/stdc++.h>
using namespace std;
const int roll=24, table_size = 29; //24+5

int line_cnt=1, error_cnt=0;

void fcout(string out) {
    ofstream output;
    output.open("202214024_token.txt", ios::app);
    if (!output.is_open()) {
        cerr << "Error opening file.\n";
    }
    output << out;
    output.close();
}

void ffcout(string token, string symbol){
    ofstream output;
    output.open("202214024_log.txt", ios::app);
    if (!output.is_open()) {
        cerr << "Error opening file.\n";
    }
    output << "Line No. " << line_cnt <<": ";
    output << "Token <"<< token << "> Lexeme " << symbol << " found\n";
    output.close();
}

void yyerror(string msg) {
    error_cnt++;
    ofstream output;
    output.open("202214024_log.txt", ios::app);
    if (!output.is_open()) {
        cerr << "Error opening file.\n";
    }    
    output << "Error at Line No. " << line_cnt <<": ";
    output << msg;
    output.close();
}
void clearOutput() {
    ofstream output;
    output.open("202214024_log.txt", ios::trunc);
    if (!output.is_open()) {
        cerr << "Error delete file contents.\n";
    }
    output.close();
    output.open("202214024_token.txt", ios::trunc);
    if (!output.is_open()) {
        cerr << "Error delete file contents.\n";
    }
    output.close();
}


class Symbol_Info
{
private:
    string name, type;

public:
    Symbol_Info *next, *prev;
    Symbol_Info()
    {
        this->name = "";
        this->type = "";
        this->next = NULL;
        this->prev = NULL;
    }
    Symbol_Info(string n)
    {
        this->name = n;
        this->next = NULL;
        this->prev = NULL;
    }
    Symbol_Info(string n, string t)
    {
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
class SymbolTable
{
private:
    Symbol_Info *snf[table_size];

public:
    SymbolTable()
    {
        for (int i = 0; i < table_size; ++i)
            snf[i] = NULL;
    }

    int hash(string name)
    {
        int s=0;
        for (int i = 0; name[i] ; i++) s+=name[i];
        
        return (s * (roll)) % table_size;
    }
    
    void print()
    {
        ofstream op;
        op.open("202214024_log.txt", ios::app);
        for (int i = 0; i < table_size; ++i)
        {
            fcout(to_string(i) + ((i<10)?"-->":"->"));
            op << string((i) + ((i<10)?"-->":"->"));
            if (snf[i])
            {
                fcout(" < "+snf[i]->getName()+", "+  snf[i]->getType() + " > ");
                op << string(" < "+snf[i]->getName()+", "+  snf[i]->getType() + " > ");
                Symbol_Info *tmp = snf[i]->next;
                int ind = 1;
                while (tmp)
                {
                    fcout(" < " + tmp->getName() + ", " + tmp->getType() + " > ");
                    tmp = tmp->next;
                }
            }
            fcout("\n");
            op<<"\n";
        }
            
    }
    void insert(Symbol_Info *newT)
    {

        string newName = newT->getName(), newType = newT->getType();

        int id = hash(newName), the_ind = 1;
        //if null then make a new instance there
        if (!snf[id])
        {
            snf[id] = new Symbol_Info(newName, newType);
            // fcout("Inserted at position "+ to_string(id) + ", 0\n");
        }
        // chain
        else
        {
            // cout<<"Chaining index"<<endl;
            Symbol_Info *tmp = snf[id], *newS=NULL;
            if (tmp->getName() == newName && tmp->getType() == newType)
            {
                fcout("Already Exists\n");
                return;
            }
            //keep iterating until next elem is null
            while (tmp->next)
            {
                // tmp->prev = tmp;
                tmp = tmp->next;
                the_ind++;
            }
            newS = new Symbol_Info(newName, newType);
            newS->prev = tmp;
            tmp->next = newS;
            // fcout("Inserted at position "+ to_string(id) + ", " + to_string(the_ind) + "\n");
        }
        
        fcout("<"+ snf[id]->getName() + ", " +  snf[id]->getType() + ">");
        print();
    }
    void insert(string newName)
    {
        int id = hash(newName), the_ind = 1;
        //if null then make a new instance there
        if (!snf[id])
        {
            snf[id] = new Symbol_Info(newName);
            // fcout("Inserted at position "+ to_string(id) + ", 0\n");
        }
        // chain
        else
        {
            // cout<<"Chaining index"<<endl;
            Symbol_Info *tmp = snf[id], *newS=NULL;
            if (tmp->getName() == newName)
            {
                fcout("Already Exists\n");
                return;
            }
            //keep iterating until next elem is null
            while (tmp->next)
            {
                // tmp->prev = tmp;
                tmp = tmp->next;
                the_ind++;
            }
            newS = new Symbol_Info(newName);
            newS->prev = tmp;
            tmp->next = newS;
            // fcout("Inserted at position "+ to_string(id) + ", " + to_string(the_ind) + "\n");
        }
        fcout("<"+ newName + ">");
        print();
    }
void insert(string newName, string newType)
    {
        int id = hash(newName), the_ind = 1;
        //if null then make a new instance there
        if (!snf[id])
        {
            snf[id] = new Symbol_Info(newName, newType);
            // fcout("Inserted at position "+ to_string(id) + ", 0\n");
        }
        // chain
        else
        {
            // cout<<"Chaining index"<<endl;
            Symbol_Info *tmp = snf[id], *newS=NULL;
            if (tmp->getName() == newName && tmp->getType() == newType)
            {
                fcout("Already Exists\n");
                return;
            }
            //keep iterating until next elem is null
            while (tmp->next)
            {
                // tmp->prev = tmp;
                tmp = tmp->next;
                the_ind++;
            }
            newS = new Symbol_Info(newName, newType);
            newS->prev = tmp;
            tmp->next = newS;
            // fcout("Inserted at position "+ to_string(id) + ", " + to_string(the_ind) + "\n");
        }
        fcout("<"+ newName + ", " +  newType + ">");
        print();
    }

    Symbol_Info *lookUp(string si, bool c=true)
    {
        int id = hash(si);
        if (snf[id])
        {
            if (snf[id]->getName() == si)
            {
                fcout(((c)?"Found at ":"Deleted from ") + to_string(id) + ", 0\n");
                return snf[id];
            }
            else
            {
                Symbol_Info *tmp = snf[id];
                int newIndex = 0;
                while (tmp)
                {
                    if (tmp->getName() == si)
                    {
                        fcout(((c)?"Found at ":"Delete from ") + to_string(id) + "," + to_string(newIndex) + "\n");
                        return tmp;
                    }
                    tmp=tmp->next;
                    newIndex++;
                }
            }
        }
        else {
            fcout((c)?"Not Found\n":"Doesn't Exist\n");
        }
        return NULL;
    }

    void del(string toDel){
        Symbol_Info* tmp = lookUp(toDel, false);
        if(!tmp){
            return;
        }
        int id = hash(toDel);
        if(tmp->next){
            if(tmp->prev){
                tmp->next->prev = tmp->prev; 
                tmp->prev->next = tmp->next;
            }
            else {
                snf[id]=tmp->next;
            }
            // tmp->next = tmp->prev = NULL;
            delete tmp;
        }
        //handle when this is also the last node
        else{
            tmp->prev->next = NULL;
            delete tmp;
        }
    }

};
