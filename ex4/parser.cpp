#include "scanner.h"
#include "symtab.h"
// globals
Token_stream ts;
Symbol_table st; 
//map<string, int> names;

int statement()
{
    //cout << "statement, ";
	Token t = ts.get();        // get the next token from token stream
	switch (t.kind) {
	case INT:
		return declaration();
	default:
		ts.putback(t);     // put t back into the token stream
		return binOp();
	}
}

int declaration()
{
    //cout << "declaration, ";
	Token t = ts.get();
	if (t.kind != ID) throw runtime_error("name expected in declaration");
	string name = t.name;
        st.declare(name, 0);
	return 0;
}

// | and &
int binOp()
{
    int left = comparation();      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream
// if (1<2 | 1<3) 2 else 3

    int right;
    while(true)
    {
        switch (t.kind) 
        {
            case '|':
                right = comparation();
                left = left || right;
                t = ts.get();
                break;
            case '&':
                right = comparation();
                left = left && right;
                t = ts.get();
                break;
            default:
                ts.putback(t);     // put t back into the token stream
                return left;       // finally: no more + or -: return the answer
        }
    }
}


// < and >
int comparation()
{
    int left = expression();      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream

    switch (t.kind) {
        case '<':
            return left < expression();
        case '>':
            return left > expression();
        default:
            ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
    }
}

// + and -
int expression()
{
    //cout << "expression, ";
    int left = term();      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
        case '+':
            left += term();    // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left -= term();    // evaluate Term and subtract
            t = ts.get();
            break;
        default:
            ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}

// * and /
int term()
{
    //cout << "term, ";
    int left = primary();
    Token t = ts.get();

    while (true) {
        switch (t.kind) {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
        {
            int d = primary();
            if (d == 0) throw runtime_error("divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);
            return left;
        }
    }
}

int primary()
{
    //cout << "primary, ";
    Token t = ts.get();
    int result;
    switch (t.kind) {
    case '(':    // handle '(' expression ')'
    {
        int d = binOp();
        t = ts.get();
        if (t.kind != ')') throw runtime_error("')' expected");
        return d;
    }
    case '-':
	    return - primary();
    case '+':
	    return primary();
    case '!':
	    return !primary();
    case NUM:
        return t.value;  // return the number value
    case ID:
    {
        string n = t.name;
        Token next = ts.get();
        if (next.kind == '=') 
        {	// name = expression
            int d = expression();
            st.set(n, d);
            return d; // return the assignment value
        }
        else 
        {
            ts.putback(next);		// not an assignment
            return st.get(t.name).value;  // return the id value
        }
    }
    case SAVED:
        if(t.name == "if")
            return ifExp(); 
    default:
        throw runtime_error("primary expected");
    }
}

int ifExp()
{
    int cond = binOp();

    int trueStmt = binOp();

    // read 'else'
    Token elseStmt = ts.get();
    if(elseStmt.kind != SAVED || elseStmt.name != "else") throw runtime_error("'else' expected after 'if'");
    
    int falseStmt = binOp();
    if(cond) 
        return trueStmt;
    else
        return falseStmt;
}
