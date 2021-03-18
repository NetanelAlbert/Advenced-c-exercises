#include <iostream>
#include <vector>
using namespace std;
class Document{
private:
    vector<string> m_data;
    size_t m_linePointer;
    void setToRealIndex(size_t index);
    
public:
    Document();
    Document(string fileName);
    void moveToLine(size_t line);
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

