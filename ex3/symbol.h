#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include "enums.h"
using namespace std;

class Symbol {
    int symbol;
    Type type; // TERM or NONTERM
public:
    Symbol(int s, Type t) : symbol(s), type(t) {}
    Type getType(){return type;}
    int getSymbol(){return symbol;}
    string toString() const;
    bool operator==(Symbol other) const {return type == other.type && symbol == other.symbol;}
    bool operator!=(Symbol other) const {return ! operator==(other);}
    void operator=(terminal t){type = TERM; symbol = t;}
    friend ostream& operator<<(ostream& os, const Symbol& dt);
};

const Symbol dollar = Symbol(END, TERM);
const Symbol eps = Symbol(EPSILON, TERM);
