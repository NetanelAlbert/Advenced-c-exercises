#include "token.h"
#include "tokenstrings.h"

tokenType Token::getType()
{
    return type;
}
string Token::getText()
{
    return text;
}
void Token::printToken()
{
    if(type < 258)
    {
        char c = type;
        cout << c;
    }
    else 
    {
        cout << tokenStrings[type-IDENTIFIER];
    }
    cout << '\t' << text << endl;
}

void varToken::add_line(int l) 
{
    lines->insert(l);
}
shared_ptr<set<int>> varToken::getLines() 
{
    return lines;
}