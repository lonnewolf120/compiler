#include <bits/stdc++.h>
using namespace std;
const int roll=24, table_size = 29; //24+5

void fcout(string out){
    // cout<<out;
    ofstream output;
    output.open("output.txt", ios::app);
    if (!output.is_open()) {
        cerr << "Error opening file.\n";
    }
    output<<out;
    output.close();
}

void clearOutput(){
    ofstream output;
    output.open("output.txt", ios::trunc);
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
        this->next = nullptr;
        this->prev = nullptr;
    }
    Symbol_Info(string n, string t)
    {
        this->name = n;
        this->type = t;
        this->next = nullptr;
        this->prev = nullptr;
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
            snf[i] = nullptr;
    }

    int hash(string name)
    {
        int s=0;
        for (int i = 0; name[i] ; i++) s+=name[i];
        
        return (s * (roll)) % table_size;
    }
    void insert(Symbol_Info *newT)
    {

        string newName = newT->getName(), newType = newT->getType();

        int id = hash(newName), the_ind = 1;
        //if null then make a new instance there
        if (!snf[id])
        {
            snf[id] = new Symbol_Info(newName, newType);
            //fcout("<"+ snf[id]->getName() + ", " +  snf[id]->getType() + ">");
            fcout("Inserted at position "+ to_string(id) + ", 0\n");
        }
        // chain
        else
        {
            // cout<<"Chaining index"<<endl;
            Symbol_Info *tmp = snf[id], *newS=nullptr;
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
            // fcout("<"+ snf[id]->getName() + ", " +  snf[id]->getType() + "> ");
            fcout("Inserted at position "+ to_string(id) + ", " + to_string(the_ind) + "\n");
        }
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
        return nullptr;
    }

    void print()
    {
        for (int i = 0; i < table_size; ++i)
        {
            fcout(to_string(i) + ((i<10)?"-->":"->"));
            if (snf[i])
            {
                fcout(" < "+snf[i]->getName()+", "+  snf[i]->getType() + " > ");

                Symbol_Info *tmp = snf[i]->next;
                int ind = 1;
                while (tmp)
                {
                    fcout(" < " + tmp->getName() + ", " + tmp->getType() + " > ");
                    tmp = tmp->next;
                }
            }
            fcout("\n");
        }
            
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
            // tmp->next = tmp->prev = nullptr;
            delete tmp;
        }
        //handle when this is also the last node
        else{
            tmp->prev->next = nullptr;
            delete tmp;
        }
    }

};

int main()
{
    cout<<"------- INPUT Taken from input.txt -------\n";
    cout<<"------- OUTPUT will be in output.txt -------\n";
    SymbolTable mySymbolTable;
    clearOutput();
    ifstream input;
    input.open("input.txt");
    char c;
    while(input>>c)
    {
        if (c == 'I')
        {
            string n, t;  input >> n >> t;
            // cout<<"INP: "<<n<<" "<<t<<endl;
            Symbol_Info *tmp = new Symbol_Info(n, t);
            mySymbolTable.insert(tmp);
        }
        else if (c == 'P')
        {
            mySymbolTable.print();
        }
        else if (c == 'L')
        {
            string c;
            input >> c;
            Symbol_Info *tmp = mySymbolTable.lookUp(c);
            
        }
        else if (c == 'D')
        {
            string c;
            input >> c;
            mySymbolTable.del(c);
        }
        else
        {
            fcout("Invalid operation\n");
            continue;
        }
    }
    return 0;
}
