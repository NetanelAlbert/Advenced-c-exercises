#include "symtab.h"

void SymbolTable::initReserved()
{
    ifstream inputFile("reserved.txt");
    string text;
    int num;
    while (inputFile >> text)
    {
        inputFile >> num;
        insertToken(text, make_shared<Token>(static_cast<tokenType>(num), text));
    }
    
}

shared_ptr<Token> SymbolTable::lookupToken(string text)
{
    map<string,shared_ptr<Token>>::const_iterator it = symMap.find(text);
    if ( it == symMap.end() ) {
        return nullptr;
    }
    else {
        return it->second;
    }
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
