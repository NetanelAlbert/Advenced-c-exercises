#include "Document.h"

class Editor
{
private:
    Document m_doc;
public:
    Editor(){}
    Editor(const string& fileName): m_doc(fileName){}
    void loop();
};
