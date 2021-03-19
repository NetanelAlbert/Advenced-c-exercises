#include <iostream>
#include "Editor.h"
#include <regex>

using namespace std;

void Editor::loop(){
    string command;   
    regex numReg("([0-9]+)");
    regex addReg("([+-][0-9]+)");
    regex replaceReg("s/(.*)/(.*)/");
    regex findReg("/(.*)/");
    regex writToFileReg("w (.*)");
    
    while (true){
        
        getline(cin, command);
        cout << "command: " << command << endl;
        
        if(regex_match(command, addReg)){ // "+2", "-13"
            const int amount = stoi(command);
            cout << "->adding " << amount << endl;
            m_doc.moveForward(amount);
        
        } else if (regex_match(command, numReg)){
            const int line = stoi(command);
            cout << "->moving to " << line << endl;
            m_doc.moveToLine(line);
        
        } else if (command == "$"){
            m_doc.moveToLastLine();
            cout << "->moving to last line" << endl;

        } else if (command == "a"){ // add line/s after
            string line;
            getline(cin, line);
            do{
                m_doc.addLineAfter(line);
                getline(cin, line);
            } while (line != ".");
            m_doc.moveForward(-1);

        } else if (command == "i"){ // add line/s before
            string line;
            getline(cin, line);
            do{
                m_doc.addLineBefoer(line);
                getline(cin, line);
            } while (line != ".");
            m_doc.moveForward(-1);
        
        } else if (command == "c"){ // add line/s instead
            m_doc.deleteCurrentLine();
            string line;
            getline(cin, line);
            do{
                m_doc.addLineBefoer(line);
                getline(cin, line);
            } while (line != ".");
            m_doc.moveForward(-1);

        } else if (command == "d"){
            m_doc.deleteCurrentLine();            
        
        } else if (command == "j"){
            m_doc.concatCurrentWithNext();
        
        } else if (regex_match(command, replaceReg)){ // "s/old/new/"
            smatch match;
            regex_search(command, match, replaceReg);
            m_doc.replaceFirst(match[1], match[2]);

        } else if (regex_match(command, findReg)){ // "/text to search/"
            smatch match;
            regex_search(command, match, findReg);
            m_doc.findAndMoveTo(match[1]);

        } else if (regex_match(command, writToFileReg)){ // "w file"
            smatch match;
            regex_search(command, match, writToFileReg);
            m_doc.writTofile(match[1]);

        } else if (command == "q"){
            exit(0);
        } else {
            cout << "command \"" << command << "\" is unknone." << endl;    
        }

        
        printVec();

    }
    
}