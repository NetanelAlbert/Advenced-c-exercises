#include "symtab.h"

void SymbolTable::initReserved()
{
    ifstream inputFile("reserved.txt");
    string text;
    int num;
    while (inputFile >> text)
    {
        inputFile >> num;
        insertToken(text, make_shared<Token>(num, text));
    }
    
}
shared_ptr<Token> SymbolTable::lookupToken(string text)
{
    return symMap.at(text);
}
void SymbolTable::insertToken(string text, shared_ptr<Token> tokenp)
{
    symMap.insert({text, tokenp});
}
void SymbolTable::xref()
{
    for(auto t : symMap)
    {
        if(t.second->getType() == IDENTIFIER) // TODO check if condition is correct
        {
            cout << t.first << '\t';
            for(auto line : *t.second->getLines())
            {
                cout << line << ' ';
            }
            cout << endl;
        }
    }
}
