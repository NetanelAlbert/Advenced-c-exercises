#include "symbol.h"


ostream& operator<<(ostream& os, const Symbol& sy)
{
    if(sy != eps && sy != dollar)
        os << sy.toString() << ' ';
    return os;
}

string Symbol::toString() const
{
    string toPrint;
    if(type == TERM)
    {
        switch (symbol)
        {
        case ID:
            toPrint = "id";
            break;
        
        case PLUS:
            toPrint = "+";
            break;

        case ASTERISK:
            toPrint = "*";
            break;

        case LPAREN:
            toPrint = "(";
            break;

        case RPAREN:
            toPrint = ")";
            break;
        
        case END:
            toPrint = "$";
            break;
        
        case EPSILON:
            toPrint = "";
            break;
        
        default:
            break;
        }
    }
    else // nonterm
    {
        switch (symbol)
        {
        case E:
            toPrint = "E";
            break;
        
        case E_:
            toPrint = "E_";
            break;

        case T:
            toPrint = "T";
            break;

        case T_:
            toPrint = "T_";
            break;

        case F:
            toPrint = "F";
            break;
    
        case ERROR:
            toPrint = "ERROR";
            break;
        
        default:
            break;
        }
    }
    return toPrint;
}