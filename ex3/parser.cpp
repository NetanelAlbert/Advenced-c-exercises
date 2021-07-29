#include "parser.h"
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

void Parser::parse()
{
    //stack.push_back();
    Symbol a(END, TERM); // dummy value to construct a
    a = nextToken();
    Symbol X = Symbol(E, NONTERM);

    stack.push_back(dollar);
    stack.push_back(X);
    
    while (X != dollar)
    {
        if(X == eps)
        {
            stack.pop_back();
            X = stack.back();
            continue;
        }
        //cout << "[debug] X = " << X << ", a = " << a << '\n';
        printLM();
        if(X == a)
        {
            accepted.push_back(a);
            stack.pop_back();
            a = nextToken();
        }
        else if(X.getType() == TERM)
        {
            cout << "syntax error (1)\n";
            //cout << "X = " << X << '\n';
            return;
        }
        else if(table[X.getSymbol()][a.getSymbol()] == -1)
        {
            cout << "syntax error (2)\n";
            return;
        }
        else
        {
            int ruleNumber = table[X.getSymbol()][a.getSymbol()];
            vector<Symbol> rule = rules[ruleNumber];
            
            stack.pop_back();
            
            // for(auto it = rule.begin(); it != rule.end(); ++it)
            // {
            //     if(it->getType() == NONTERM)
            //         stack.push_back(*it);
            //     else
            //         accepted.push_back(*it);
            // }
            
            copy(rule.begin(), rule.end(), back_inserter(stack));
            //copy_if(rule.begin(), rule.end(), back_inserter(accepted), [](Symbol s){return s.getType() == TERM;});
        }
        
        X = stack.back();
    }
    
    printLM();
}

terminal Parser::nextToken ()
{
    string s;
    if(! (inputFile >> s))
        return END;
    
    if(s == "id")
        return ID;
    
    if(s == "+")
        return PLUS;
    
    if(s == "*")
        return ASTERISK;
    
    if(s == "(")
        return LPAREN;
    
    if(s == ")")
        return RPAREN;
    
    return EPSILON; // TODO - find what to do here


}

void Parser::printLM()
{
    for_each(accepted.begin(), accepted.end(), [](Symbol s){cout << s;});
    cout << "| ";
    for_each(stack.rbegin(), stack.rend(), [](Symbol s){cout << s;});
    cout << endl;
}