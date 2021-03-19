#include "Document.h"
#include <regex>
#include <fstream>

Document::Document(): m_linePointer(-1) {}

Document::Document(const string& fileName): Document(){
    ifstream infile(fileName);
    string line;
    while (getline(infile, line)){
        m_data.push_back(line);
    }
}

void Document::setToRealIndex(size_t index){
    //m_linePointer = index-1;
}
void Document::moveToLine(size_t line){
    if(line < m_data.size())
        m_linePointer = line;
    else
        throw "Can't move to line greater then document size\n" ;
}
void Document::moveForward(int amount){
    if(m_linePointer + amount > 0)
        moveToLine(m_linePointer+amount);
    else
        throw "Cant move to line smaller then 1\n";
}
void Document::moveToLastLine(){
    moveToLine(m_data.size()-1);
}
void Document::addLineAfter(string s){
    m_data.insert(m_data.begin() + m_linePointer, s);
    moveForward(1);
}
void Document::addLineBefoer(string s){
    m_data.insert(m_data.begin() + m_linePointer, s);
    moveForward(1);
}
void Document::replaceCurrentLine(string s){
    m_data.at(m_linePointer) = s;
}
void Document::deleteCurrentLine(){
    m_data.erase(m_data.begin() + m_linePointer);
    if(m_linePointer >= 0)
        --m_linePointer;
}
void Document::findAndMoveTo(string s){
    for(size_t i = (m_linePointer+1)%m_data.size(); i != m_linePointer; i = (i+1)%m_data.size()){
        if(m_data.at(i).find(s) != string::npos){
            m_linePointer = i;
            return;
        }
    }
}
void Document::replaceFirst(string oldString, string newString){
    m_data.at(m_linePointer) = 
        regex_replace(m_data.at(m_linePointer), 
            regex(oldString), 
            newString, 
            regex_constants::format_first_only);
}

void Document::concatCurrentWithNext(){
    if(m_linePointer >= m_data.size()-1)
        throw "Can't connect last line becous their is no next one\n";

    m_data.at(m_linePointer) += m_data.at(m_linePointer+1);    
    m_data.erase(m_data.begin() + m_linePointer+1);
}
void Document::writTofile(string fileName){
    ofstream output_file(fileName);
    ostream_iterator<string> output_iterator(output_file, "\n");
    copy(m_data.begin(), m_data.end(), output_iterator);
}