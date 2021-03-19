#include <iostream>
#include <vector>
using namespace std;
class Document{
private:
    vector<string> m_data;
    int m_linePointer;
    void setToRealIndex(int index);
    
public:
    Document();
    Document(const string& fileName);
    void moveToLine(int line);
    void moveForward(int amount);
    void moveToLastLine();
    void addLineAfter(string s);
    void addLineBefoer(string s);
    void replaceCurrentLine(string s);
    void deleteCurrentLine();
    void findAndMoveTo(string s);
    void replaceFirst(string oldString, string newString);
    void concatCurrentWithNext();
    void writTofile(string fileName);
};

