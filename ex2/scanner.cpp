#include "scanner.h"
#include <regex>

//regex numRegE("[Ee][\+-]?\\d+");

regex numReg("[1-9]\\d*");
regex numRegE1("\\d+[Ee][\\+-]?\\d+");
regex numRegE2("\\d*\\.\\d+([Ee][\\+-]?\\d+)?");
regex numRegE3("\\d+\\.\\d*([Ee][\\+-]?\\d+)?");

bool isDigit(char c){
    return '0' <= c && c <= '9';
}

bool isPartOfNum(char c)
{
    return isDigit(c) || c == '.' || c == 'E' || c == 'e';
}

bool isLetter(char c){
    return ('a' <= c && c <= 'z') 
        || ('A' <= c && c <= 'Z')
        || c == '_';
}

shared_ptr<Token> next2charOperatorToken(string op)
{
    if(op == "++") return shared_ptr<Token>(new Token(INC_OP, op));
    else if(op == "--") return shared_ptr<Token>(new Token(DEC_OP, op));
    else if(op == "->") return shared_ptr<Token>(new Token(PTR_OP, op));
    else if(op == "&&") return shared_ptr<Token>(new Token(AND_OP, op));
    else if(op == "||") return shared_ptr<Token>(new Token(OR_OP, op));
    else if(op == "<=") return shared_ptr<Token>(new Token(LE_OP, op));
    else if(op == ">=") return shared_ptr<Token>(new Token(GE_OP, op));
    else if(op == "==") return shared_ptr<Token>(new Token(EQ_OP, op));
    else if(op == "!=") return shared_ptr<Token>(new Token(NE_OP, op));
    else return nullptr;
}


shared_ptr<Token> Scanner::nextToken()
{
    do // skip white spaces
    {
        if(!nextChar()) return nullptr;
    } while(isspace(ch));

    switch (ch)
    {
    case '/':
    {
        if(!nextChar()) return nullptr; // TODO return ERROR?
        if(ch == '/') // case of "//"
        {
            do // skip current line
            {
                if(!nextChar()) return nullptr;
            } while(ch != '\n');
        } 
        else if(ch == '*') // case of "/*", need to skip until "*/"
        {
            if(!nextChar()) return nullptr; // TODO return ERROR?
            char prev;
            do 
            {
                prev = ch;
                if(!nextChar()) return nullptr; // TODO return ERROR?
            } while(prev != '*' || ch != '/');
        } 
        else // case of just "/"
        {
            // TODO return ERROR?
        }
        return nextToken(); // To skip more whitespaces and comments if there are
        break;
    }
    case ';' : case '{' : case '}' : case ',' : case ':' : case '=' : \
    case '(' : case ')' : case '[' : case ']' : case '&' : \
    case '!' : case '~' : case '-' : case '+' : case '<' : case '>' : \
    case '|' : case '*' : case '%' : case '^' : case '?' : 
    //case '/':  // TODO - why needed here? this is a comment
    {
        const char tmp1 = ch;
        nextChar();
        const char tmp2 = ch;

        auto ptr = next2charOperatorToken(string(1, tmp1)+tmp2);
        if(ptr != nullptr) return ptr;
        else inputFile.unget();

        return shared_ptr<Token>(new Token(static_cast<tokenType>(tmp1),string(1,tmp1)));
    }
    case '\'' : 
    {
        nextChar();
        char ans = ch;
        nextChar();
        if(ch == '\'') return shared_ptr<Token>(new Token(CONSTANT, string(1, ans)));
        else return shared_ptr<Token>(new Token(ERROR, "\'"+ans+ch)); // 'ans'
        break;
    }
    case '\"' : 
    {
        nextChar();
        string str = "";
        while(ch != '\"')
        {
            str += ch;
            nextChar();
        } 
        return shared_ptr<Token>(new Token(STRING_LITERAL, str));
    }
    default:
        if(isdigit(ch) || ch == '.')
        {
            string str = "";
            do 
            {
                str += ch;
                nextChar();
            } while(isPartOfNum(ch));
            inputFile.unget();
            if(str == ".")
            {
                return shared_ptr<Token>(new Token(static_cast<tokenType>('.'),str));
            }
            else if(regex_match(str, numReg)
                || str == "0"
                || regex_match(str, numRegE1)
                || regex_match(str, numRegE2)
                || regex_match(str, numRegE3))
            {
                return shared_ptr<Token>(new Token(CONSTANT, str));
            } 
            else
            {
                return shared_ptr<Token>(new Token(ERROR, str));
            }

        }
        else if(isLetter(ch))
        {
            string str = "";
            do 
            {
                str += ch;
                nextChar();
            } while(isLetter(ch) || isDigit(ch));
            inputFile.unget();
            auto tokenp = symTab.lookupToken(str);
            if(tokenp == nullptr)
            {
                tokenp = shared_ptr<Token>(new varToken(str));
                symTab.insertToken(str, tokenp);
            }
            tokenp->add_line(lineno);
            return tokenp;
        }
        break;
    }
    //return shared_ptr<Token>(new Token(ERROR, "not a match"));
    return nullptr;
} 